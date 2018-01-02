//////////////////////////////////////////////////////////////////////////
//
// CCustomButton - Win32/WinCE/PocketPC compatible button-based controls
//
// Coded by dzolee
// http://dzolee.blogspot.com
//
//////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>

//just in case
#ifndef RGB_AVERAGE
#define RGB_AVERAGE(a, b)   ( ((((a) ^ (b)) & 0xfffefefeL) >> 1) + ((a) & (b)) )
#endif

#ifndef BS_TYPEMASK
	#define BS_TYPEMASK 0x0fL
#endif

//basic buttom types
enum ButtonType
{
	btCustomButton=0,
	btCustomRadio,
	btCustomCheckBox,
	btCustomGroup
};

//custom button additional flags
#define	bfNone			0
#define bfMask			15		//mask value that contains all flags
#define bfTextLeft		1
#define bfTextRight		2
#define bfTextTop		4
#define bfTextBottom	8
#define bfHGradient		16		//horizontal gradient coloring

/////////////////////////////////////////////////////////////////////////////
class CCustomButton : public CButton
{
	DECLARE_DYNAMIC(CCustomButton)
public:
	CCustomButton();
	virtual ~CCustomButton();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

private:
	bool m_bTransparent;
	bool m_bFlat;
	bool m_bHGradient;
	bool m_bPressed;
	bool m_bDisabled;
	bool m_bIsGroup;

	COLORREF m_crBkgIdle;
	COLORREF m_crTxtIdle;
	COLORREF m_crBkgPressed;
	COLORREF m_crTxtPressed;
	COLORREF m_crHGStart;
	COLORREF m_crHGEnd;
	COLORREF m_crFrame;

	HANDLE m_hBmpActive;		//bitmap handle
	HANDLE m_hBmpInactive;		//bitmap handle
	DWORD m_dwBmpW;				//bitmap width
	DWORD m_dwBmpH;				//bitmap height
	DWORD m_cfFlags;			//framework flags
	DWORD m_ctType;

	CString m_strCaption, m_strActiveCaption;

	bool RegisterCustomClass();

	//flicker-free drawing
	CDC m_DrawDC;
	CBitmap m_DrawBitmap;
	HGDIOBJ m_hOldDCBmp;	

	//custom font support
	HFONT m_hCustomFont;

	// Generated message map functions
protected:
	virtual void PreSubclassWindow();
	//push button drawing
	void DrawPB(CDC* pDC, CRect* pRect);
	void DrawPBBorder(CDC* pDC, CRect* pRect);

	//radio button/checkbox drawing
	void DrawRBCB(CDC* pDC, CRect* pRect);

	//group box drawing
	void DrawGB(CDC* pDC, CRect* pRect);

	//DrawText() flag from button style
	DWORD GetDTFlag(DWORD dwStyle);

	//gradient drawing
	void DrawGradient(CDC *pDC);

	//display BMP
	void DisplayTransparentBMP(CDC *pDestDC, HBITMAP hBmp, DWORD dwW, DWORD dwH, int nX, int nY);

	//color util
	COLORREF OffsetColor(COLORREF crColorIn, double dOffs);

	//{{AFX_MSG(CCustomButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnBMSetCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBMGetCheck(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void SetCaption(CString strCaption, CString strActiveCaption = _T(""));
	void SetFlags(DWORD dwFlags);
	void SetBitmaps(HBITMAP hBmpInactive, HBITMAP hBmpActive = NULL);

	void SetBkgIdleColor(COLORREF crBkgIdle);
	void SetBkgActiveColor(COLORREF crBkgActive);
	void SetFrgIdleColor(COLORREF crFrgIdle);
	void SetFrgActiveColor(COLORREF crFrgActive);
	void SetGradientColors(COLORREF crStart, COLORREF crEnd);
	void SetFrameColor(COLORREF crFrame);
	void SetFont(HFONT hFont);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
