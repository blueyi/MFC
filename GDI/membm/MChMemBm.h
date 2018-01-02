///////////////////////////////////////////////////////////////////////////////
// ExacT Soft (tm) 2001																											//
// Author: Vsevolod Gromov email: gromov@eti.co.ru;													//
// MChMemBm class. implements memory bitmap, is able to copy part of source	//
// bitmap to MemBm, or copy source DC contents to MemBm (screen capture)		//
// use _WIN32_WINDOWS for conditional compiles (necessary for proper Brush	//
// origin adjustment operations	and proper transparent draw calls						//
///////////////////////////////////////////////////////////////////////////////
#ifndef _MChMemBm_H_
#define _MChMemBm_H_

//{ memory bitmap class MChMemBm
class MChMemBm
{
public:
	// create memory bitmap from source bitmap.
	// !REMEMBER! hbmSrc MUST NOT be selected into any DC before calling this function
	// or following will just create copy of hDC contents, not the hbmSrc.
	bool Create(HDC hDC, HBITMAP hbmSrc, int iLeft, int iTop,
		int iWidth, int iHeight, DWORD dwRop = SRCCOPY );
	// create memory bitmap from explicit data
	bool Create( HDC hDC, int iWidth, int iHeight, UINT cPlanes, UINT cBitsPerPel, 
		const LPVOID lpvBits = NULL, const LPRGBQUAD pColorTable = NULL);

	//copy creation
	bool Create( const MChMemBm& bmSrc, DWORD dwRop = SRCCOPY );
	//create from bitmap resource by name
	bool Create( HINSTANCE hInst, LPCTSTR pszName );
	//create from bitmap resource by ID
	bool Create( HINSTANCE hInst, UINT nID ){ return Create( hInst, MAKEINTRESOURCE(nID) ); };

	// default constructor
	MChMemBm() { Initialize(); };
	// inplace constructor
	MChMemBm(HDC hDC, HBITMAP hbmSrc, int iLeft, int iTop,
		int iWidth, int iHeight, DWORD dwRop = SRCCOPY )
	{
		Initialize();
		Create(hDC, hbmSrc, iLeft, iTop, iWidth, iHeight, dwRop);
	};
	//copy constructor
	MChMemBm( const MChMemBm& bmSrc, DWORD dwRop = SRCCOPY )
	{
		Initialize();
		Create(bmSrc, dwRop);
	};

	// create memory bitmap from explicit data (default is monochrome bitmap)
	MChMemBm( HDC hDC, int iWidth, int iHeight,
			UINT cPlanes, UINT cBitsPerPel, const LPVOID lpvBits, const LPRGBQUAD pColorTable )
	{
		Initialize();

#ifndef MCH_USE_DDB
		if( cBitsPerPel != MCH_DIB_BPP )
			MException::Throw( M_L("Explicit DIB creation with bit depth other than ")
				M_L( MCH_TO_STRING( MCH_DIB_BPP ) )
				M_L(" is not supported") );
		if( cPlanes != 1 )
			MException::Throw( M_L("Explicit DIB creation with planes count other than 1 is not supported") );
#endif

		Create( hDC, iWidth, iHeight, cPlanes, cBitsPerPel, lpvBits, pColorTable );
	};

	//construct from resource by name
	MChMemBm( HINSTANCE hInst, LPCTSTR pszName )
	{
		Initialize();
		Create(hInst, pszName);
	};
	//construct from resource by ID
	MChMemBm( HINSTANCE hInst, UINT nID )
	{
		Initialize();
		Create(hInst, nID);
	};
	virtual ~MChMemBm(){	Cleanup();	};

public:
	//cleanup object data
	void Cleanup();
	//get bitmap width
	int GetWidth() const;
	//get bitmap height
	int GetHeight() const;
	// get bits per pixel for our bitmap
	int GetBpp() const;
	// get color planes for our bitmap
	int GetPlanes() const;
	//return our memory dc with bitmap selected in it
	//(Blt operations - ready)
	operator HDC() const { return m_hdcImg; };
	//boolean validation operator !
	bool operator !() const { return !m_bCreated; };
	//perform pattern fill, adjusting brush origin if neccessary
	void Fill( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight,
		bool bAdjustBrushOrg = false, DWORD dwRop = PATCOPY );
	//do 1-to-1 draw
	void Draw( HDC hDC, int iLeft, int iTop, DWORD dwRop = SRCCOPY ) const;

	//perform draw (simple or stretched)
	void Draw( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight,
		DWORD dwRop = SRCCOPY, int iStretchMode =	
#ifndef UNDER_CE
			COLORONCOLOR
#else	
			0
#endif //UNDER_CE
			) const;

	//do transparent drawing
	void DrawTrans( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight,
				COLORREF crTransparent ) const;

#ifndef UNDER_CE
	//do alpha blending draw (works only when _WIN32_WINDOWS > 0x0400 else do nothing)
	void DrawAlpha( HDC hDC, int iLeft, int iTop, int iWidth, int iHeight,
		const BLENDFUNCTION& blendFunc ) const;
#endif
	//get as DIB, stuffed into byte array
	void GetAsDIB(MByteString& refDIB) const;
	//pixel manipulation
	COLORREF GetPixel(int iX, int iY) const;
	void SetPixel( int iX, int iY, COLORREF clPixel );
	//special effects support
#ifndef MCH_USE_DDB
	typedef signed short MChFilter[9];
	void ApplyFilter( const MChFilter& crefFilter );
#endif

//intrinsic typedefs
protected:
	//rgbquad wrapper helper
	struct MCH_RGBQUAD : public RGBQUAD
	{
		MCH_RGBQUAD() { Initialize(); }

		inline void Initialize() { ZeroMemory( this, sizeof(RGBQUAD) ); }

		inline operator RGBQUAD () const { return *this; }
		inline operator COLORREF () const { return RGB(rgbRed, rgbGreen, rgbBlue); }

		void operator = (COLORREF clColor) 
		{ rgbRed = ((LPBYTE)&clColor)[0]; rgbGreen = ((LPBYTE)&clColor)[1]; rgbBlue = ((LPBYTE)&clColor)[2]; }

		inline BYTE GetR() const { return rgbRed; }
		inline BYTE GetG() const { return rgbGreen; }
		inline BYTE GetB() const { return rgbBlue; }
		inline void SetR(BYTE bRed) { rgbRed = bRed; }
		inline void SetG(BYTE bGreen) { rgbGreen = bGreen; }
		inline void SetB(BYTE bBlue) { rgbBlue = bBlue; }
	};
	//bitmapinfoheader wrapper helper
	struct MCH_BITMAPINFOHEADER : public BITMAPINFOHEADER
	{
		MCH_BITMAPINFOHEADER() { Initialize(); }
		inline void Initialize() { ZeroMemory( this, sizeof(MCH_BITMAPINFOHEADER) ); biSize = sizeof(BITMAPINFOHEADER); }
		//if pTable != NULL, method uses color table data from external buffer for initialization
		//the buffer must contain at least iNumColors elements. otherwise, the default initialization
		//is used. (b\w monochrome, system 16 colors palette, etc.)
		void InitColorTable(int iNumColors, const LPRGBQUAD pTable = NULL );
		int GetNumColors() const;
		int GetPaletteByteSize() const;
		int GetImageByteSize() const;

		MCH_RGBQUAD m_Colors[256];
	};


//data members
protected:
	HANDLE	m_hbmOld;
	HBITMAP m_hbmImg;
	MChDC		m_hdcImg;
#ifdef MCH_USE_DDB
	//bitmap dimensions
	int		m_iWidth;
	int		m_iHeight;
	// number of color planes in our bitmap
	int		m_iPlanes;
	// bits per pixel in our bitmap
	int		m_iBpp;
#else
	//internal bit depth by default
	enum { MCH_DIB_BPP = 32 };

	MCH_BITMAPINFOHEADER m_bmiHeader;
	LPVOID m_pImgBuff;
#endif //MCH_USE_DDB
	
	//"object created" flag
	bool	m_bCreated;

	//reset data members to 0
	void Initialize();
	//stretching required
	bool RequireStretch( int iWidth, int iHeight ) const;
};
//} memory bitmap class MChMemBm

#endif //_MChMemBm_H_