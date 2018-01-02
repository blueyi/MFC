/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// SfxApi.h : header file for SFX API functions                                //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#if !defined(_SFXAPI_H_INCLUDED_)
#define _SFXAPI_H_INCLUDED_

extern "C" {void	SfxDrawTransparent	(HDC, int, int, int, int, HBITMAP, COLORREF);}
extern "C" {void	SfxDrawBlend		(HDC, int, int, int, int, HBITMAP, DWORD);}

void		SfxDrawImage		(CDC*, int, int, int, int, CBitmap*, DWORD);
void		SfxCopyImage		(CDC*, int, int, int, int, CBitmap*, int, int);
CBitmap*	SfxLoadImage		(LPCTSTR pName);
DWORD		SfxGetFormat		(LPCTSTR pName);
CBitmap*	SfxCreateThumb		(CDC *pDC, CBitmap* pImage, int wthumb, int hthumb);
CFont*		SfxCreateFont		(LPCTSTR lpszFace, int nSize, int nBold, int nItalic, int nAngle);
DWORD		SfxGetTextFile		(LPCTSTR szFileName, LPTSTR lpszBuffer, DWORD dwSize);
HANDLE		SfxRunProc			(LPCTSTR lpszExe, LPCTSTR lpszArg);
void		SfxRandAdjustWindow	(CRect* pWinRect, int nNeedWidth, int nNeedHeight, DWORD dwStyle, BOOL bMenu);

#define	OBJECT_FORMAT_UNKNOWN	0x00010000
#define	OBJECT_FORMAT_TXT		0x00020000
#define	OBJECT_FORMAT_ICO		0x00030000
#define	OBJECT_FORMAT_IMG		0x00040000

#define	OBJECT_CXIMAGE_MASK		0x0000FFFF
#define	OBJECT_FORMAT_MASK		0xFFFF0000

#define HSB(h,s,b)				((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(s))<<8))|(((DWORD)(BYTE)(h))<<16)))
#define LUMINANCE(r,g,b)		((30*r+59*g+11*b)/255)

#define GetLValue(hsb)			((BYTE)(hsb))
#define GetSValue(hsb)			((BYTE)(((WORD)(hsb)) >> 8))
#define GetHValue(hsb)			((BYTE)((DWORD)(hsb)>>16))
#define	HUE_UNDEF				0x000000FF

void	SfxRGBtoHSB				(int red, int green, int blue, int *hue, int *sat, int *bri);
void	SfxHSBtoRGB				(int hue, int sat, int bri, int *red, int *green, int *blue);
COLORREF SfxColorRGBtoHSB		(COLORREF color);
COLORREF SfxColorHSBtoRGB		(COLORREF color);
int		SfxGetLuminance			(COLORREF crRGB);

COLORREF SfxComplementColor		(COLORREF color, int nThreshold);
COLORREF SfxContrastColor		(COLORREF col);
void	SfxGetColorInfo			(COLORREF crRGB, COLORREF crHSB, LPTSTR lpBuffer, LPCTSTR lpSep);


#endif	// _SFXAPI_H_INCLUDED_
