#pragma once
#include "afxwin.h"
#include "BkDlg.h"

class CTransparentDlg :	public CDialog
{
public:
	CTransparentDlg(UINT nIDTemplate, CWnd* pParentWnd = NULL, COLORREF transparentColour = RGB(255, 0, 0));
	virtual~CTransparentDlg(void);

private:
	CBrush    m_Brush;
	COLORREF  m_TransparentColour;
	

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();

public:
	void SetTransparentColour(COLORREF transparentColour );
public:
	CBkDlg *m_pBkDlg;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedClose();
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
