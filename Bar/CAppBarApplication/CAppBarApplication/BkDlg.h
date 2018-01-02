#pragma once
#include "afxwin.h"
#include "AppBar.h"

class CBkDlg :	public CAppBar
{
public:

	CBkDlg(UINT nIDTemplate, CWnd* pParentWnd = NULL, BYTE bAlpha = 128, COLORREF bkColour = RGB(250, 0, 0));
	virtual~CBkDlg(void);


public:
	void getTransparentHwnd(HWND *hwnd);	
	void SetAlpha(BYTE bAlpha);
	void SetColor(COLORREF bkColour);

private:
	BYTE m_bAlpha;
	COLORREF m_BkColour;
	HWND m_transparent_hwnd;
public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMove(int x, int y);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
};
