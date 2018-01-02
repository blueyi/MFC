#include "stdafx.h"
#include "MChMemBm.h"

#if !defined(UNDER_CE) && (_WIN32_WINDOWS >= 0x0410)	//msimg32 library is provided only for winver > 95
#pragma comment( lib, "msimg32" )
#endif

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.
#define WIDTHBYTES(bits)    (( ((bits) + 31) & (~31) ) / 8)

//if pTable != NULL, method uses color table data from external buffer for initialization
//the buffer must contain at least iNumColors elements. otherwise, the default initialization
//is used. (b\w monochrome, system 16 colors palette, etc.)
void MChMemBm::MCH_BITMAPINFOHEADER::InitColorTable(int iNumColors, const LPRGBQUAD pTable /*= NULL*/ )
{
	if( pTable )
		CopyMemory( &m_Colors, pTable, iNumColors );
	else
	{
		switch( iNumColors )
		{
		case 2: //monochrome
			m_Colors[0] = RGB(0,0,0);
			m_Colors[1] = RGB(255,255,255);
			break;
		}
	}
}

int MChMemBm::MCH_BITMAPINFOHEADER::GetNumColors() const
{	
	if( biClrUsed != 0 )
		return biClrUsed;

	switch( biBitCount )
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		return 0;
	}
}

int MChMemBm::MCH_BITMAPINFOHEADER::GetPaletteByteSize() const
{
	return GetNumColors() * sizeof(RGBQUAD);
}

int MChMemBm::MCH_BITMAPINFOHEADER::GetImageByteSize() const
{
	return WIDTHBYTES(biWidth * biBitCount) * biHeight;
}

/////////////////////////// MChMemBm implementation //////////////////////////////////////
//reset data members to 0
void MChMemBm::Initialize()
{	
	m_hbmOld = m_hbmImg = NULL;
#ifdef MCH_USE_DDB
	m_iWidth = m_iHeight = 0;
	m_iPlanes = m_iBpp = 0; 
#else
	m_bmiHeader.Initialize();
	m_pImgBuff = NULL;
#endif //MCH_USE_DDB
	m_bCreated = false; 
}

// create memory bitmap from source bitmap
bool MChMemBm::
Create(HDC hDC, HBITMAP hbmSrc, int iLeft, int iTop,
			 int iWidth, int iHeight, DWORD dwRop )
{
	//if already created - do nothing
	if( !m_bCreated )
	{
		//we cannot use NULL hDC and NULL hbmSrc at the same time-
		//result will be nonsense (copy empty MemDC contents to our bitmap)
		//use appropriate DC as source DC

		MChDC hdcTmpSrc;
		if( !hDC )
		{
			//use this only if input hDC is NULL - get screen DC
			hdcTmpSrc.GetDC();
			M_ASSERT(hdcTmpSrc);
		}

		m_hdcImg.CreateCompatibleDC( hDC ? hDC : hdcTmpSrc );
		M_ASSERT(m_hdcImg);

		if( m_hdcImg )
		{
#ifdef MCH_USE_DDB
			m_hbmImg = CreateCompatibleBitmap( hDC ? hDC : hdcTmpSrc, iWidth, iHeight );
#else
			m_bmiHeader.biBitCount = MCH_DIB_BPP;
			m_bmiHeader.biCompression = BI_RGB;
			m_bmiHeader.biPlanes = 1;
			m_bmiHeader.biHeight = iHeight;
			m_bmiHeader.biWidth = iWidth;
			m_bmiHeader.biSizeImage = m_bmiHeader.GetImageByteSize();

			m_hbmImg = CreateDIBSection( hDC ? hDC : hdcTmpSrc, (const BITMAPINFO*)&m_bmiHeader, DIB_RGB_COLORS, &m_pImgBuff, NULL, 0);
#endif //MCH_USE_DDB
			M_ASSERT( m_hbmImg );

			if(m_hbmImg)
			{
				//select our memory bitmap
				m_hbmOld = SelectObject( m_hdcImg, m_hbmImg );

				//select source bitmap if it's not NULL
				HANDLE hbmOldSrc = NULL;
				//check if we actually need selection of src image in src DC
				//(it may be already selected in it in case of copying contents of
				//another MChMemBm object )
				bool bNeedSrcSelect = 
					hbmSrc && (GetCurrentObject( hDC ? hDC : hdcTmpSrc, OBJ_BITMAP) != hbmSrc );
				if( bNeedSrcSelect )
					hbmOldSrc = SelectObject( hDC ? hDC : hdcTmpSrc, hbmSrc );

				//copy bitmap bits
				BitBlt( m_hdcImg, 0, 0, iWidth, iHeight,
					hDC ? hDC : hdcTmpSrc, iLeft, iTop, dwRop );

#ifdef MCH_USE_DDB
				//setup sizes of our image
				m_iWidth = iWidth;
				m_iHeight = iHeight;
				//setup color information
				BITMAP bmInfo;
				ZeroMemory( &bmInfo, sizeof(BITMAP) );
				GetObject( m_hbmImg, sizeof(BITMAP), &bmInfo );
				m_iPlanes = bmInfo.bmPlanes;
				m_iBpp = bmInfo.bmBitsPixel;
#endif //MCH_USE_DDB

				//set "created" flag
				m_bCreated = true;

				//deselect source bitmap
				if( bNeedSrcSelect )
					SelectObject( hDC ? hDC : hdcTmpSrc, hbmOldSrc );
			}
		}
	}

	return m_bCreated;
};

bool MChMemBm::
Create( HDC hDC, int iWidth, int iHeight,
			 UINT cPlanes, UINT cBitsPerPel, const LPVOID lpvBits, const LPRGBQUAD pColorTable )
{
	//if already created - do nothing
	if( !m_bCreated )
	{
		m_hdcImg.CreateCompatibleDC( hDC );
		M_ASSERT(m_hdcImg);
		if( m_hdcImg )
		{
#ifdef MCH_USE_DDB
			m_hbmImg = CreateBitmap( iWidth, iHeight, cPlanes, cBitsPerPel, lpvBits );
#else
			m_bmiHeader.biBitCount = cBitsPerPel;
			m_bmiHeader.biCompression = BI_RGB;
			m_bmiHeader.biPlanes = cPlanes;
			m_bmiHeader.biHeight = iHeight;
			m_bmiHeader.biWidth = iWidth;
			m_bmiHeader.biSizeImage = m_bmiHeader.GetImageByteSize();
			m_bmiHeader.InitColorTable( m_bmiHeader.GetNumColors(), pColorTable );

			m_hbmImg = CreateDIBSection( m_hdcImg, (const BITMAPINFO*)&m_bmiHeader, 0, &m_pImgBuff, NULL, 0);
			if( lpvBits )
				CopyMemory(m_pImgBuff, lpvBits, m_bmiHeader.biSizeImage);
#endif //MCH_USE_DDB
			M_ASSERT( m_hbmImg );

			if(m_hbmImg)
			{
				//select our memory bitmap
				m_hbmOld = SelectObject( m_hdcImg, m_hbmImg );

#ifdef MCH_USE_DDB
				//setup sizes of our image
				m_iWidth = iWidth;
				m_iHeight = iHeight;
				m_iPlanes = cPlanes;
				m_iBpp = cBitsPerPel;
#endif //MCH_USE_DDB

				//set "created" flag
				m_bCreated = true;
			}
		}
	}

	return m_bCreated;
};

bool MChMemBm::
Create( const MChMemBm& bmSrc, DWORD dwRop )
{
	return Create( bmSrc, bmSrc.m_hbmImg, 0, 0, bmSrc.GetWidth(), bmSrc.GetHeight(), dwRop );
};

bool MChMemBm::
Create( HINSTANCE hInst, LPCTSTR pszName )
{
	if( !m_bCreated )
	{
		UINT nLoadFlags = LR_DEFAULTCOLOR
#ifndef UNDER_CE			
			| LR_DEFAULTSIZE 
#endif //#ifndef UNDER_CE
			;

		if( !hInst )
#ifndef UNDER_CE
			nLoadFlags |= LR_LOADFROMFILE;
#else
			MException::Throw( M_L("Load image from file is not supported in CE") );
#endif //#ifndef UNDER_CE

		MChGDIObj hbmImg( LoadImage(hInst, pszName,	IMAGE_BITMAP, 0, 0, nLoadFlags) );
		M_ASSERT( hbmImg );
		if( hbmImg )
		{
			BITMAP bmInfo;
			//prepare structure for bitmap parameters query
			ZeroMemory( &bmInfo, sizeof(BITMAP) );
#ifdef MCH_USE_DDB
			m_hbmImg = (HBITMAP)(HGDIOBJ)hbmImg;

			m_hdcImg.CreateCompatibleDC();
			M_ASSERT( m_hdcImg );
			if( m_hdcImg && GetObject( m_hbmImg, sizeof(BITMAP), &bmInfo ) )
			{
				m_hbmOld = SelectObject( m_hdcImg, m_hbmImg );

				m_iWidth = bmInfo.bmWidth;
				m_iHeight = bmInfo.bmHeight;
				m_iPlanes = bmInfo.bmPlanes;
				m_iBpp = bmInfo.bmBitsPixel;

				m_bCreated = true;
			}
#else //MCH_USE_DDB
			MChDC hdcImg;
			hdcImg.CreateCompatibleDC();
			M_ASSERT( hdcImg );
			if( hdcImg && GetObject( hbmImg, sizeof BITMAP, &bmInfo ) )
			{
				m_bCreated = Create(hdcImg, (HBITMAP)(HGDIOBJ)hbmImg, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight);
			}
#endif //MCH_USE_DDB
		}
	}

	return m_bCreated;
}

//cleanup object data
void MChMemBm::
Cleanup()
{
	if( m_hdcImg )
	{
		SelectObject( m_hdcImg, m_hbmOld );
		m_hdcImg.Cleanup();
	}

	//this "if" is not necessary,
	//as we can call DeleteObject on non valid handles, but just in case
	if( m_hbmImg )
	{
		DeleteObject(m_hbmImg);
	}

	//reset data members to 0
	Initialize();
};

//stretching required
bool MChMemBm::RequireStretch( int iWidth, int iHeight ) const
{
	return ( (GetWidth() != iWidth) || (GetHeight() != iHeight) );
}

//perform pattern fill, adjusting brush origin if neccessary
void MChMemBm::
Fill( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight,
		 bool bAdjustBrushOrg, DWORD dwRop )
{
	//if image is absent - do nothing
	if( !m_bCreated )
		return;

	//create brush from image
	MChGDIPattBrush gdiPattBrush( CreatePatternBrush( m_hbmImg ) );
	gdiPattBrush.Select( hDC, bAdjustBrushOrg, iLeft, iTop );

	//do patterned fill
	PatBlt( hDC, iLeft, iTop, iWidth, iHeight, dwRop );
};

//do 1-to-1 draw
void MChMemBm::
Draw( HDC hDC, int iLeft, int iTop, DWORD dwRop ) const
{
	//if not created - do nothing
	if( !m_bCreated )
		return;

	::BitBlt( hDC, iLeft, iTop, GetWidth(), GetHeight(), m_hdcImg, 0, 0, dwRop );
}

//perform draw (simple or stretched)
void MChMemBm::
Draw( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight,
		 DWORD dwRop, int iStretchMode ) const
{
	//if not created - do nothing
	if( !m_bCreated )
		return;

	//check if we need stretching
	if( RequireStretch(iWidth, iHeight) )
	{
#ifndef UNDER_CE
		//set new stretch mode
		MChGDIStretchBltMode gdiStretchMode( hDC, iStretchMode );
#endif //UNDER_CE

		//do stretch blt
		::StretchBlt( hDC, iLeft, iTop, iWidth, iHeight,
			m_hdcImg, 0, 0, GetWidth(), GetHeight(), dwRop );
	}
	else
	{
		//do 1-to-1 drawing
		Draw( hDC, iLeft, iTop, dwRop ); 
	}
}

//get bitmap width
int MChMemBm::
GetWidth() const
{
#ifdef MCH_USE_DDB
	return m_iWidth;
#else
	return m_bmiHeader.biWidth;
#endif
}

//get bitmap height
int MChMemBm::
GetHeight() const
{
#ifdef MCH_USE_DDB
	return m_iHeight;
#else
	return m_bmiHeader.biHeight;
#endif
}

//get bitmap's bpp
int MChMemBm::GetBpp() const
{
#ifdef MCH_USE_DDB
	return m_iBpp;
#else
	return m_bmiHeader.biBitCount;
#endif
}

//get bitmap's color planes
int MChMemBm::GetPlanes() const
{
#ifdef MCH_USE_DDB
	return m_iPlanes;
#else
	return m_bmiHeader.biPlanes;
#endif
}

//draws bitmap transparently (stretching it when necessary)	
//non-API realization of stretching - capable transparent drawing
void MChMemBm::DrawTrans( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight,
					COLORREF crTransparent ) const
{
	//if our object is uninitialized - do nothing
	if( !m_bCreated )
		return;

	MChDC hdcAnd, hdcXor;
	hdcAnd.CreateCompatibleDC( m_hdcImg );
	hdcXor.CreateCompatibleDC( m_hdcImg );

	if( hdcAnd && hdcXor )
	{
		MChGDIObj bmAnd( CreateBitmap(GetWidth(), GetHeight(), 1, 1, NULL) );
		MChGDIObj bmXor( CreateCompatibleBitmap(m_hdcImg, GetWidth(), GetHeight()) );	

		if( bmAnd && bmXor )
		{
			// create AND mask 
			bmAnd.SelectIn( hdcAnd );

			MChGDIBkColor gdiBkColor( m_hdcImg, crTransparent );
			Draw( hdcAnd, 0, 0 );

			// create XOR mask
			bmXor.SelectIn( hdcXor );
			Draw( hdcXor, 0, 0 );
			//0x220326 is Dest not and Source
			::BitBlt( hdcXor, 0, 0, GetWidth(), GetHeight(), hdcAnd, 0, 0, 0x220326 ); 

			//"collation" bitmap for flicker-free drawing
			MChDC hdcTmp;
			hdcTmp.CreateCompatibleDC(hDC);
	
			if( hdcTmp )
			{
				MChGDIObj bmTemp( CreateCompatibleBitmap(hDC, iWidth, iHeight) );

				if( bmTemp )
				{
					bmTemp.SelectIn(hdcTmp);
					//copy hDC contents to temporary
					::BitBlt(hdcTmp, 0, 0, iWidth, iHeight, hDC, iLeft, iTop, SRCCOPY);

					// blend the AND and XOR masks into the temporary bitmap
					::StretchBlt(hdcTmp, 0, 0, iWidth, iHeight, 
						hdcAnd, 0, 0, GetWidth(), GetHeight(), SRCAND);
					::StretchBlt(hdcTmp, 0, 0, iWidth, iHeight, 
						hdcXor, 0, 0, GetWidth(), GetHeight(), SRCINVERT); 

					// draw the resulting image back to the hDC
					::BitBlt(hDC, iLeft, iTop, iWidth, iHeight, hdcTmp, 0, 0, SRCCOPY);
				}
			}
		}
	}
}

#ifndef UNDER_CE
void MChMemBm::DrawAlpha( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight, const BLENDFUNCTION& blendFunc ) const
{	
	//if our object is uninitialized - do nothing
	if( !m_bCreated )
		return;

#if _WIN32_WINDOWS >= 0x0410	//msimg library is provided only for winver > 95
	AlphaBlend( hDC, iLeft, iTop, iWidth, iHeight, m_hdcImg, 0, 0, GetWidth(), GetHeight(), blendFunc );
#endif
}

#endif //#ifndef UNDER_CE

//get as DIB, stuffed into byte array
void MChMemBm::GetAsDIB(MByteString& refDIB) const
{
#if !defined(UNDER_CE)
	GdiFlush();
#endif

	SelectObject( m_hdcImg, m_hbmOld );

#ifdef MCH_USE_DDB
	MCH_BITMAPINFOHEADER bmiHeader;
#endif //MCH_USE_DDB

	MCH_BITMAPINFOHEADER* pBmih = 
#ifdef MCH_USE_DDB
		&bmiHeader;

#if defined(UNDER_CE)
	#error GetAsDIB functionality cannot be implemented for DDB in UNDER_CE because GetDIBits is omitted from WinCE API!
#endif

#else //MCH_USE_DDB
		const_cast<MCH_BITMAPINFOHEADER*>(&m_bmiHeader);
#endif //MCH_USE_DDB

#ifdef MCH_USE_DDB
	//request bitmap parameters
	GetDIBits( m_hdcImg, m_hbmImg, 0, m_iHeight, NULL, (LPBITMAPINFO)pBmih, DIB_RGB_COLORS );
	//correct compression member - by default it's being set by GetDIBits to BI_BITFIELDS
	pBmih->biCompression = BI_RGB;
#endif //MCH_USE_DDB

	//get color info size
	int iColorInfoSize = pBmih->GetPaletteByteSize();
	//calc correct image size
	pBmih->biSizeImage = pBmih->GetImageByteSize();
	//size of image headers
	int iHeadersSize = sizeof(BITMAPFILEHEADER) + pBmih->biSize + iColorInfoSize;

	//init file header
	//allocate buffer for DIB data
	refDIB.resize( iHeadersSize + pBmih->biSizeImage, 0 );

	LPBITMAPFILEHEADER pBmfh = (LPBITMAPFILEHEADER)refDIB.data();
	pBmfh->bfType = MAKEWORD('B','M');
	pBmfh->bfOffBits = iHeadersSize;
	pBmfh->bfSize = refDIB.size();

	//copy BITMAPINFO + ColorInfo
	CopyMemory( (LPVOID)(refDIB.data() + sizeof(BITMAPFILEHEADER)), pBmih, pBmih->biSize + iColorInfoSize );

#ifdef MCH_USE_DDB
	//obtain bitmap as DIB
	GetDIBits( m_hdcImg, m_hbmImg, 0, m_iHeight, (LPVOID)(refDIB.data() + iHeadersSize), (LPBITMAPINFO)pBmih, DIB_RGB_COLORS );
#else // MCH_USE_DDB
	//set bitmap bits
	CopyMemory( (LPVOID)(refDIB.data() + iHeadersSize), m_pImgBuff, pBmih->biSizeImage );
#endif // MCH_USE_DDB

	//restore bitmap selection in internal hdc
	SelectObject( m_hdcImg, m_hbmImg );
}

//pixel manipulation
COLORREF MChMemBm::GetPixel(int iX, int iY) const
{
	if( !m_bCreated )
		return -1;

	M_ASSERT(iX >= 0 && iX < GetWidth()); 	
	M_ASSERT(iY >= 0 && iY < GetHeight());

#if !defined(UNDER_CE)
	GdiFlush();
#endif

	return ::GetPixel(m_hdcImg, iX, iY);
}

void MChMemBm::SetPixel( int iX, int iY, COLORREF clPixel )
{
	if( !m_bCreated )
		return;

	M_ASSERT(iX >= 0 && iX < GetWidth()); 	
	M_ASSERT(iY >= 0 && iY < GetHeight());

#if !defined(UNDER_CE)
	GdiFlush();
#endif

	::SetPixel(m_hdcImg, iX, iY, clPixel);
}

#ifndef MCH_USE_DDB
void MChMemBm::ApplyFilter( const MChFilter& crefFilter )
{
#if !defined(UNDER_CE)
	GdiFlush();
#endif

	//don't support non-truecolor bitmaps filtering
	if( m_bCreated && ((m_bmiHeader.biBitCount == 24) || (m_bmiHeader.biBitCount == 32)) &&
		(GetWidth() >= 3) && (GetHeight() >= 3) ) 
	{
		int iWidthBytes = WIDTHBYTES( m_bmiHeader.biWidth*m_bmiHeader.biBitCount );
		signed short nSum = crefFilter[0]+crefFilter[1]+crefFilter[2]+
			crefFilter[3]+crefFilter[4]+crefFilter[5]+crefFilter[6]+crefFilter[7]+crefFilter[8];

		//check Zero condition
		if( !nSum )
			MException::Throw( M_L("Sum of image filter elements shouldn't be 0") );

		//temporary buffer for filtering
		int iPixelByteSize = m_bmiHeader.biBitCount / 8;
		int iFilteredBuffLineSize = (m_bmiHeader.biWidth-2) * iPixelByteSize;
		LPBYTE pFilteredRows[3] = {
			new BYTE[iFilteredBuffLineSize]
			,	new BYTE[iFilteredBuffLineSize]
			,	new BYTE[iFilteredBuffLineSize] 
		};
		int iFilteredRowIdx = 0;

		LPBYTE pPrevRowStart = reinterpret_cast<LPBYTE>(m_pImgBuff);
		for( int iY = 2; iY < GetHeight()-1; ++iY )
		{
			LPBYTE pCurFilteredRow = pFilteredRows[iFilteredRowIdx];
			for( int iXOffs = iPixelByteSize; iXOffs < iWidthBytes-iPixelByteSize; iXOffs += iPixelByteSize )
			{
				LPBYTE pPrevRowPixel = pPrevRowStart + iXOffs;
				LPBYTE pCurRowPixel = pPrevRowPixel + iWidthBytes;
				LPBYTE pNextRowPixel = pCurRowPixel + iWidthBytes;

#define MCH_APPLY_FILTER_TO_COLOR_COMPONENT( iColorIdx )																						\
	pCurFilteredRow[iColorIdx] = static_cast<BYTE>(																							\
	(																																													\
	crefFilter[0]*static_cast<signed short>( (pPrevRowPixel-iPixelByteSize)[iColorIdx] ) +	\
	crefFilter[1]*static_cast<signed short>( pPrevRowPixel[iColorIdx] ) +										\
	crefFilter[2]*static_cast<signed short>( (pPrevRowPixel+iPixelByteSize)[iColorIdx] ) +	\
	crefFilter[3]*static_cast<signed short>( (pCurRowPixel-iPixelByteSize)[iColorIdx] ) +		\
	crefFilter[4]*static_cast<signed short>( pCurRowPixel[iColorIdx] ) +										\
	crefFilter[5]*static_cast<signed short>( (pCurRowPixel+iPixelByteSize)[iColorIdx] ) +		\
	crefFilter[6]*static_cast<signed short>( (pNextRowPixel-iPixelByteSize)[iColorIdx] ) +	\
	crefFilter[7]*static_cast<signed short>( pNextRowPixel[iColorIdx] ) +										\
	crefFilter[8]*static_cast<signed short>( (pNextRowPixel+iPixelByteSize)[iColorIdx] )		\
	) / nSum )

				MCH_APPLY_FILTER_TO_COLOR_COMPONENT( 0 );
				MCH_APPLY_FILTER_TO_COLOR_COMPONENT( 1 );
				MCH_APPLY_FILTER_TO_COLOR_COMPONENT( 2 );

				pCurFilteredRow += iPixelByteSize;
			}

			//update filtered row index
			++iFilteredRowIdx;

			//if filtered buffer is full - save the first row from it to the source bitmap's row
			//that goes before prevrow and update pFilteredBuff contents
			if( iFilteredRowIdx >= M_NUMBER_OF_ARRAY_ELEMENTS(pFilteredRows) )
			{
				iFilteredRowIdx = 2;

				CopyMemory(pPrevRowStart+iPixelByteSize, pFilteredRows[0], iFilteredBuffLineSize);
				LPBYTE pTmp = pFilteredRows[0];
				pFilteredRows[0] = pFilteredRows[1];
				pFilteredRows[1] = pFilteredRows[2];
				pFilteredRows[2] = pTmp;
			}

			//update row pointers
			pPrevRowStart += iWidthBytes;
		}

		delete[] pFilteredRows[0];
		delete[] pFilteredRows[1];
		delete[] pFilteredRows[2];
	}
}
#endif
/////////////////////////// MChMemBm implementation end///////////////////////////////////