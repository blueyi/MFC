//////////////////////////////////////////////////////////////////////////
//
// CCustomSlider - Win32/WinCE/PocketPC compatible bitmapped slider
//
// Coded by dzolee
// http://dzolee.blogspot.com
//
//////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>

class CCustomSlider : public CWnd
{
	DECLARE_DYNAMIC(CCustomSlider)

public:
	CCustomSlider();
	virtual ~CCustomSlider();

	void GetRange(DWORD& dwMin, DWORD& dwMax);
	DWORD GetRangeMin();
	DWORD GetRangeMax();
	void SetRange(DWORD dwMin, DWORD dwMax);
	void SetRangeMin(DWORD dwMin);
	void SetRangeMax(DWORD dwMax);
	
	DWORD GetPos();
	void SetPos(DWORD dwPos);

	void SetReverse(bool bRev);
	bool GetReverse();

	void SetBkgColor(COLORREF crBkg);
	COLORREF GetBkgColor();

	void SetBitmaps(HBITMAP hBmpChannel, HBITMAP hBmpThumbInactive, HBITMAP hBmpThumbActive = NULL);

private:
	DWORD m_dwRangeMin;
	DWORD m_dwRangeMax;
	DWORD m_dwPos;

	//channel/thumb bitmap handles
	HANDLE m_hBmpChannel;
	HANDLE m_hBmpThumbInactive;
	HANDLE m_hBmpThumbActive;

	//channel/thumb bitmap dimensions
	DWORD m_dwChW;
	DWORD m_dwChH;
	DWORD m_dwTW;
	DWORD m_dwTH;

	bool m_bIsHorz;
	bool m_bActive;
	bool m_bIsReverse;
	bool m_bInitialized;

	COLORREF m_crBkg;

	//coordinate conversions
	DWORD PosToX(DWORD dwPos);
	DWORD PosToY(DWORD dwPos);
	DWORD XToPos(DWORD dwX);
	DWORD YToPos(DWORD dwY);

	//control class registration
	bool RegisterWindowClass();

	//display BMP with transparency
	void DisplayTransparentBMP(CDC *pDestDC, HBITMAP hBmp, DWORD dwW, DWORD dwH, int nX, int nY);

	//flicker-free drawing
	CDC m_DrawDC;
	CBitmap m_DrawBitmap;
	HGDIOBJ m_hOldDCBmp;	

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

