//*****************************************************************************//
//*                                                                           *//
//*               Sfx - Service Functions Extension                           *//
//*               Version 1.0 2002                                            *//
//*               Written by Adriano Asnaghi                                  *//
//*                                                                           *//
//*****************************************************************************//

#include "stdafx.h"

//#include "ijl.h"
#include "ximage.h"
#include "SfxApi.h"

//---- Library Need ----------------------------------------------//
#pragma comment(lib, "msimg32")
#pragma comment(lib, "jpeg")
#pragma comment(lib, "png")
#pragma comment(lib, "tiff")
#pragma comment(lib, "zlib")
#pragma comment(lib, "CxImage")

// Available format table entry
typedef struct FORMATS
{
	LPTSTR		extension;			// file extension
	DWORD		format;				// cximage format
}
	FORMATS;

FORMATS		AvailFormat[] =	{
								{_T(".jpg"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_JPG},
								{_T(".gif"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_GIF},
								{_T(".bmp"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_BMP},
								{_T(".dib"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_BMP},
								{_T(".ico"), OBJECT_FORMAT_ICO},
								{_T(".png"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_PNG},
								{_T(".tif"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_TIF},
								{_T(".tga"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_TGA},
								{_T(".pcx"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_PCX},
								{_T(".wmf"), OBJECT_FORMAT_IMG | CXIMAGE_FORMAT_WMF},
								{_T(".txt"), OBJECT_FORMAT_TXT},
								{_T(".htm"), OBJECT_FORMAT_TXT}
							};

#define	FORMAT_COUNT	(sizeof(AvailFormat)/sizeof(FORMATS))

//--------------------------------------------------------------------------------------//
//  Draws bitmap at the specifed position in DC                                         //
//--------------------------------------------------------------------------------------//
void SfxDrawImage(CDC* pDC, int x, int y, int w, int h, CBitmap* pBitmap, DWORD dwrop)
{
	int				bw, bh;
	CDC				TempDC;
    BITMAP			bm;
	CBitmap*		pOrigBitmap;

	pBitmap->GetObject(sizeof(bm), (LPVOID)&bm);
	bw = bm.bmWidth;
	bh = bm.bmHeight;
	if( w == 0 ) w = bw;
	if( h == 0 ) h = bh;

	if( dwrop == 0 ) dwrop = SRCCOPY;
	TempDC.CreateCompatibleDC(pDC);
	pOrigBitmap = (CBitmap*)TempDC.SelectObject(pBitmap);
	if( (w != bw) || (h != bh) )
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC->StretchBlt(x, y, w, h, &TempDC, 0, 0, bw, bh, dwrop);
	}
	else pDC->BitBlt(x, y, w, h, &TempDC, 0, 0, dwrop);
	TempDC.SelectObject(pOrigBitmap);
	return;	
}                

//--------------------------------------------------------------------------------------//
//  Copy a portion of a bitmap at the specifed position in DC                           //
//--------------------------------------------------------------------------------------//
void SfxCopyImage(CDC* pDC, int x, int y, int w, int h, CBitmap* pBitmap, int ix, int iy)
{
	int				bw, bh;
	CDC				TempDC;
    BITMAP			bm;
	CBitmap*		pOrigBitmap;

	pBitmap->GetObject(sizeof(bm), (LPVOID)&bm);
	bw = bm.bmWidth;
	bh = bm.bmHeight;
	if( ix + w > bw ) w = bw - ix;
	if( iy + h > bh ) h = bh - iy;

	TempDC.CreateCompatibleDC(pDC);
	pOrigBitmap = (CBitmap*)TempDC.SelectObject(pBitmap);
	pDC->BitBlt(x, y, w, h, &TempDC, ix, iy, SRCCOPY);
	TempDC.SelectObject(pOrigBitmap);
	return;	
}                

//--------------------------------------------------------------------------------------//
//  Draws bitmap <hbm> at the specifed position in DC                                   //
//--------------------------------------------------------------------------------------//
extern "C" void SfxDrawTransparent(HDC hdc, int x, int y, int w, int h, HBITMAP hBmp, COLORREF crColor)
{
	int				bw, bh;
	HDC				hdcTemp;
	HRGN			hrgn;
    BITMAP			bm;
	HBITMAP			hOldBmp1;
   	COLORREF		cTranspColor;

	GetObject(hBmp, sizeof(bm), (LPVOID)&bm);
	bw = bm.bmWidth;
	bh = bm.bmHeight;
	if( w == 0 ) w = bw;
	if( h == 0 ) h = bh;

	hdcTemp = CreateCompatibleDC(hdc);
	hOldBmp1 = (HBITMAP)SelectObject(hdcTemp, hBmp);
	if( crColor == CLR_NONE ) cTranspColor = GetPixel(hdcTemp, 0, 0);
	else cTranspColor = (COLORREF)crColor;
	SetStretchBltMode(hdc, COLORONCOLOR);
	hrgn = CreateRectRgn(x, y, x + w + 1, y + h + 1);
	SelectClipRgn(hdc, hrgn);
	TransparentBlt(hdc, x, y, w, h, hdcTemp, 0, 0, bw, bh, cTranspColor);
	SelectClipRgn(hdc, NULL);
   	SelectObject(hdcTemp, hOldBmp1);
   	DeleteDC(hdcTemp);
	return;	
}                

//--------------------------------------------------------------------------------------//
//  Draws bitmap with blending option at the specifed position in DC                    //
//--------------------------------------------------------------------------------------//
extern "C" void SfxDrawBlend(HDC hdc, int x, int y, int w, int h, HBITMAP hBmp, DWORD alpha)
{
	int				bw, bh;
	HDC				hdcTemp;
    BITMAP			bm;
	HBITMAP			hOldBmp1;
	BLENDFUNCTION	bf;

	GetObject(hBmp, sizeof(bm), (LPVOID)&bm);
	bw = bm.bmWidth;
	bh = bm.bmHeight;
	if( w == 0 ) w = bw;
	if( h == 0 ) h = bh;

	if( alpha > 100 ) alpha = 255;
	else alpha = (alpha*255)/100;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (BYTE)alpha;
	bf.AlphaFormat = 0;
  	hdcTemp = CreateCompatibleDC(hdc);
	hOldBmp1 = (HBITMAP)SelectObject(hdcTemp, hBmp);
	AlphaBlend(hdc, x, y, w, h, hdcTemp, 0, 0, bw, bh, bf);
	SelectObject(hdcTemp, hOldBmp1);
	DeleteDC(hdcTemp);
	return;	
}                

//--------------------------------------------------------------------------------------//
// Load image from file                                                                 //
// I use CxImage class (version 5.99a) by Davide Pizzolato                              //
//--------------------------------------------------------------------------------------//
CBitmap* SfxLoadImage(LPCTSTR pName)
{
	HDC			hDC;
	CBitmap*	pBitmap;
	HBITMAP		hBitmap;
	DWORD		dwType;
	CxImage		image;

	dwType = SfxGetFormat(pName);
	if( dwType == OBJECT_FORMAT_UNKNOWN ) return NULL;

	hDC = ::GetDC(NULL);
	image.Load(pName, dwType & OBJECT_CXIMAGE_MASK);
	if( image.IsValid() ) hBitmap = image.MakeBitmap(hDC);
	::ReleaseDC(NULL, hDC);
	pBitmap = new CBitmap;
	pBitmap->Attach(hBitmap);
	return pBitmap;
}

//--------------------------------------------------------------------------------------//
//  Get image format using filename extension                                           //
//--------------------------------------------------------------------------------------//
DWORD SfxGetFormat(LPCTSTR pName)
{
	int			i;
	LPTSTR		pext;

	pext = strrchr(pName, '.');
	if( pext != NULL )
	{
		for(i=0; i<FORMAT_COUNT; i++)
		{
			if( lstrcmpi(AvailFormat[i].extension, pext) == 0 ) return AvailFormat[i].format;
		}
	}
	return OBJECT_FORMAT_UNKNOWN;
}

//-------------------------------------------------------------------------//
// Create image's thumbnail                                                //
//-------------------------------------------------------------------------//
CBitmap* SfxCreateThumb(CDC *pDC, CBitmap* pImage, int wthumb, int hthumb)
{
	CDC			TempDC;
	CBitmap		*pBitmap, *pOrigBitmap;
	int			bw, bh, Grid_w, Grid_h;
	int			cbw, cbh, red;
	BITMAP		bm;

	pImage->GetObject(sizeof(bm), (LPVOID)&bm);
	bw = bm.bmWidth;
	bh = bm.bmHeight;
	if( (bw > wthumb) || (bh > hthumb) )
	{
		cbw = bw * 100;
		cbh = bh * 100;
		Grid_w = ((cbw*10)/wthumb + 5)/10;
		Grid_h = ((cbh*10)/hthumb + 5)/10;
		red = max(Grid_w,Grid_h);
		bw = (cbw/red);
		bh = (cbh/red);
	}

	TempDC.CreateCompatibleDC(pDC);
	pBitmap = new CBitmap;
	pBitmap->CreateCompatibleBitmap(pDC, bw, bh);
	pOrigBitmap = TempDC.SelectObject(pBitmap);
	::SfxDrawImage(&TempDC, 0, 0, bw, bh, pImage, 0);
	TempDC.SelectObject(pOrigBitmap);
	return pBitmap;
}

//-------------------------------------------------------------------------//
// Adjust window rect using random location coordinate                     //
// Window will be reduced until to fit on screen                           //
//-------------------------------------------------------------------------//
void SfxRandAdjustWindow(CRect* pWinRect, int nNeedWidth, int nNeedHeight, DWORD dwStyle, BOOL bMenu)
{
	int			ScreenW, ScreenH, nStartX, nStartY;
	int			nCalcWidth, nCalcHeight, reduc_w, reduc_h;
	int			cbw, cbh, zoom;
	double		dResult, dRange = (double)RAND_MAX;
	RECT		war;

	::SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&war, 0);
	ScreenW = war.right - war.left - 8;
    ScreenH = war.bottom - war.top - 8;

	pWinRect->SetRect(0, 0, nNeedWidth, nNeedHeight);
	::AdjustWindowRect((LPRECT)pWinRect, dwStyle, bMenu);
	nStartX = pWinRect->left;
	nStartY = pWinRect->top;
	pWinRect->OffsetRect(-nStartX,-nStartY); 

	nCalcWidth = pWinRect->Width();
	nCalcHeight = pWinRect->Height();
	if( (nCalcWidth > ScreenW) || (nCalcHeight > ScreenH) )
	{
		cbw = nCalcWidth * 100;
		cbh = nCalcHeight * 100;
		reduc_w = ((cbw*10)/ScreenW + 5)/10;
		reduc_h = ((cbh*10)/ScreenH + 5)/10;
		zoom = max(reduc_w,reduc_h);
		nCalcWidth = (cbw/zoom);
		nCalcHeight = (cbh/zoom);
		pWinRect->right = nCalcWidth;
		pWinRect->bottom = nCalcHeight;
	}

	dResult = ((double)rand()/dRange)*(double)(ScreenW - nCalcWidth);
	nStartX = (int)dResult;
	if( nStartX < 0 ) nStartX = 0;
	dResult = ((double)rand()/dRange)*(double)(ScreenH - nCalcHeight);
	nStartY = (int)dResult;
	if( nStartY < 0 ) nStartY = 0;
	pWinRect->OffsetRect(nStartX,nStartY); 
}

//-------------------------------------------------------------------------//
// Create a new font                                                       //
//-------------------------------------------------------------------------//
CFont* SfxCreateFont(LPCTSTR lpszFace, int nSize, int nBold, int nItalic, int nAngle)
{
	HDC			hdc;
	CFont*		pFont;
	int			nLogPixY;
	LOGFONT		lf;

	hdc = ::GetDC(NULL);
	nLogPixY = GetDeviceCaps(hdc, LOGPIXELSY);
	::ReleaseDC(NULL, hdc);

	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = -(nSize * nLogPixY )/72;
	lf.lfEscapement = nAngle*100;
	lf.lfOrientation = nAngle*100;
	lf.lfWeight = nBold;
	lf.lfItalic = nItalic;
	lf.lfCharSet = ANSI_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = PROOF_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	lstrcpy(&lf.lfFaceName[0], lpszFace);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	return pFont;
}

//-------------------------------------------------------------------------//
// Read a portion of the file                                              //
//-------------------------------------------------------------------------//
DWORD SfxGetTextFile(LPCTSTR szFileName, LPTSTR lpszBuffer, DWORD dwSize)
{
	HANDLE		hf;
	DWORD		dwBytesReaded;

	lpszBuffer[0] = NIL;
	hf = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if( hf == INVALID_HANDLE_VALUE ) return 0;
	ReadFile(hf, lpszBuffer, dwSize, &dwBytesReaded, NULL); 
	CloseHandle(hf);
	return dwBytesReaded;
}

//----------------------------------------------------------------------------------//
// Process backgroud starter                                                   		//
//----------------------------------------------------------------------------------//
HANDLE SfxRunProc(LPCTSTR lpszExe, LPCTSTR lpszArg)
{
	long				rc;
	STARTUPINFO			si;
	PROCESS_INFORMATION	pi;
	CString				sCmd;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	if( lpszArg == NULL ) sCmd.Format(_T("\"%s\""), lpszExe);
	else sCmd.Format(_T("\"%s\" \"%s\""), lpszExe, lpszArg);
	rc = CreateProcess(NULL, (LPTSTR)((LPCTSTR)sCmd), NULL, NULL, FALSE, DETACHED_PROCESS | NORMAL_PRIORITY_CLASS, 
						NULL, NULL, &si, &pi);
	if( rc == 0 ) return NULL;
	return pi.hProcess;
}

//----------------------------------------------------------------------------------//
// Convert an RGB color-space format to HSB color-space format                      //
//                                                                                  //
// RGB format 0x00BBGGRR                                                            //
// HSB format 0x00HHSSBB                                                            //
//                                                                                  //
//----------------------------------------------------------------------------------//
COLORREF SfxColorRGBtoHSB(COLORREF color)
{
	int		nHue, nSat, nBri;

	SfxRGBtoHSB(GetRValue(color), GetGValue(color), GetBValue(color),
				&nHue, &nSat, &nBri);

	return HSB(nHue,nSat,nBri);
}

//----------------------------------------------------------------------------------//
// Convert an HSB color-space format to RGB color-space format                      //
//                                                                                  //
// RGB format 0x00BBGGRR                                                            //
// HSB format 0x00HHSSBB                                                            //
//                                                                                  //
//----------------------------------------------------------------------------------//
COLORREF SfxColorHSBtoRGB(COLORREF color)
{
	int		nRed, nGreen, nBlue;

	SfxHSBtoRGB(GetHValue(color), GetSValue(color), GetLValue(color),
				&nRed, &nGreen, &nBlue);

	return RGB(nRed,nGreen,nBlue);
}

//----------------------------------------------------------------------------------//
// Convert the RGB components into HSB components                                   //
//                                                                                  //
// red, green, blue values are from 0 to 255                                        //
// hue = [0,240], sat = [0,100]%, bri = [0,100]%                                    //
//                                                                                  //
//----------------------------------------------------------------------------------//
void SfxRGBtoHSB(int nRed, int nGreen, int nBlue, int *nHue, int *nSat, int *nBri)
{
	double	dRed, dGreen, dBlue;
	double	dHue, dSat, dBri;
	double	dMin, dMax, dDelta;

	dRed = (double)nRed/255.0;
	dGreen = (double)nGreen/255.0;
	dBlue = (double)nBlue/255.0;
	dMin = min(dRed,dGreen);
	dMin = min(dMin,dBlue);
	dMax = max(dRed,dGreen);
	dMax = max(dMax,dBlue);
	dBri = dMax;
	if( dMax == dMin )
	{
		// achromatic color (i.e. grey, black or white)
		// r = g = b = x		
		// sat = 0, bri = x*100, hue is undefined
		*nSat = 0;
		*nHue = HUE_UNDEF;
		*nBri = (int)(dBri * 100.0);
		return;
	}
	dDelta = dMax - dMin;
	dSat = dDelta / dMax;
	if( dRed == dMax ) dHue = (dGreen - dBlue) / dDelta;				// between yellow & magenta
	else if( dGreen == dMax ) dHue = 2.0 + (dBlue - dRed) / dDelta;		// between cyan & yellow
	else dHue = 4.0 + (dRed - dGreen) / dDelta;							// between magenta & cyan
	dHue *= 40.0;
	if( dHue < 0 ) dHue += 240.0;
	*nHue = (int)dHue;
	*nSat = (int)(dSat * 100.0);
	*nBri = (int)(dBri * 100.0);
}

//----------------------------------------------------------------------------------//
// Convert the HSB components into RGB components                                   //
//                                                                                  //
// red, green, blue values are from 0 to 255                                        //
// hue = [0,240], sat = [0,100]%, bri = [0,100]%                                    //
//                                                                                  //
//----------------------------------------------------------------------------------//
void SfxHSBtoRGB(int nHue, int nSat, int nBri, int *nRed, int *nGreen, int *nBlue)
{
	int		nSector;
	double	dFract, dVal1, dVal2;
	double	dRed, dGreen, dBlue;
	double	dHue, dSat, dBri;

	if( (nSat == 0) || (nHue == HUE_UNDEF) )
	{
		// achromatic (grey, black or white)
		*nRed = *nGreen = *nBlue = (nBri * 255)/100;
		return;
	}

	dHue = (double)nHue;
	dSat = (double)nSat/100.0;
	dBri = (double)nBri/100.0;

	dHue /= 40.0;
	nSector = (int)floor(dHue);			// sector 0 to 5
	dFract = dHue - floor(dHue);		// factional part of hue
	if( !(nSector & 1) ) dFract = 1.0 - dFract;
	dVal1 = dBri * (1.0 - dSat);
	dVal2 = dBri * (1.0 - dSat * dFract);
	switch( nSector )
	{
	case 0: dRed = dBri;	dGreen = dVal2;		dBlue = dVal1;	break;
	case 1: dRed = dVal2;	dGreen = dBri;		dBlue = dVal1;	break;
	case 2: dRed = dVal1;	dGreen = dBri;		dBlue = dVal2;	break;
	case 3: dRed = dVal1;	dGreen = dVal2;		dBlue = dBri;	break;
	case 4: dRed = dVal2;	dGreen = dVal1;		dBlue = dBri;	break;
	case 5: dRed = dBri;	dGreen = dVal1;		dBlue = dVal2;	break;
	}
	*nRed = (int)(dRed * 255.0);
	*nGreen = (int)(dGreen * 255.0);
	*nBlue = (int)(dBlue * 255.0);
}

//--------------------------------------------------------------------------------------//
// Create a color that contrast a given color                                           //
// This algorithm is taken from article                                                 //
// Contrasting Colors by alucardx, 25 sep 2002                                          //
// at the Code Projects site (www.codeproject.com)                                      //
//--------------------------------------------------------------------------------------//
COLORREF SfxContrastColor(COLORREF col)
{
	if( abs(((col      ) & 0xFF) - 0x80) <= 0x40 &&
		abs(((col >>  8) & 0xFF) - 0x80) <= 0x40 &&
		abs(((col >> 16) & 0xFF) - 0x80) <= 0x40
	  ) return (0x007F7F7F + col) & 0x00FFFFFF;
	else return col ^ 0x00FFFFFF;
}

//--------------------------------------------------------------------------------------//
// Create a color that contrast a given color                                           //
// This algorithm is taken from my research on color science                            //
//--------------------------------------------------------------------------------------//
COLORREF SfxComplementColor(COLORREF color, int nThreshold)
{
	int		nOrigLum, nCalcLum, nLoop;
	int		nHue, nSat, nBri;
	int		nRed, nGreen, nBlue;

	nRed = GetRValue(color);
	nGreen = GetGValue(color);
	nBlue = GetBValue(color);
	nOrigLum = LUMINANCE(nRed,nGreen,nBlue);

	SfxRGBtoHSB(nRed, nGreen, nBlue, &nHue, &nSat, &nBri);

	if( nHue == HUE_UNDEF )
	{
		nRed = nGreen = nBlue = 0;
		if( nBri < 50 ) nRed = nGreen = nBlue = 255;
	}
	else
	{
		nHue = (nHue + 120) % 240;
		nLoop = 20;
		while( nLoop )
		{
			SfxHSBtoRGB(nHue, nSat, nBri, &nRed, &nGreen, &nBlue);
			nCalcLum = LUMINANCE(nRed,nGreen,nBlue);
			if( abs(nOrigLum - nCalcLum) >= nThreshold ) break;
			if( nOrigLum <= 50 )
			{
				nSat -= 5;
				if( nSat < 0 ) nSat += 5;
				nBri += 10; 
				if( nBri > 100 ) nBri = 100;
			}
			else
			{
				nSat += 5;
				if( nSat > 100 ) nSat = 100;
				nBri -= 5; 
				if( nBri < 10 ) nBri = 10;
			}
			nLoop--;
		}
	}
	return RGB(nRed,nGreen,nBlue);

}

//--------------------------------------------------------------------------------------//
// Retrieve a Luminance from RGB color                                                  //
//--------------------------------------------------------------------------------------//
int SfxGetLuminance(COLORREF crRGB)
{
	return 	LUMINANCE(GetRValue(crRGB),GetGValue(crRGB),GetBValue(crRGB));
}

//--------------------------------------------------------------------------------------//
// Return color info text                                                               //
//--------------------------------------------------------------------------------------//
void SfxGetColorInfo(COLORREF crRGB, COLORREF crHSB, LPTSTR lpBuffer, LPCTSTR lpSep)
{
	int		nLum;
	int		nHue, nSat, nBri;
	int		nRed, nGreen, nBlue;
	TCHAR	szHue[8];

	lpBuffer[0] = NIL;
	if( (crRGB == CLR_NONE) && (crHSB == CLR_NONE) ) return;
	nRed = GetRValue(crRGB);
	nGreen = GetGValue(crRGB);
	nBlue = GetBValue(crRGB);
	nHue = GetHValue(crHSB);
	nSat = GetSValue(crHSB);
	nBri = GetLValue(crHSB);
	if( crRGB == CLR_NONE ) SfxHSBtoRGB(nHue, nSat, nBri, &nRed, &nGreen, &nBlue);
	if( crHSB == CLR_NONE ) SfxRGBtoHSB(nRed, nGreen, nBlue, &nHue, &nSat, &nBri);
	nLum = LUMINANCE(nRed,nGreen,nBlue);

	if( nHue == HUE_UNDEF ) lstrcpy(szHue, _T("???"));
	else wsprintf(TPTR(szHue), _T("%d"), nHue);

	wsprintf(TPTR(lpBuffer), _T("RGB(%d,%d,%d)%sHSB(%s,%d%%,%d%%)%sLUM(%d%%)"),
				nRed, nGreen, nBlue, lpSep, szHue, nSat, nBri, lpSep, nLum);
}



