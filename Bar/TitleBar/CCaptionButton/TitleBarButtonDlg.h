// TitleBarButtonDlg.h : Header-Datei
//

#if !defined(AFX_TITLEBARBUTTONDLG_H__3805A4AB_1A54_4E6B_8362_E30D3FB5B823__INCLUDED_)
#define AFX_TITLEBARBUTTONDLG_H__3805A4AB_1A54_4E6B_8362_E30D3FB5B823__INCLUDED_

#include "CaptionButton.h"	// Hinzugefügt von der Klassenansicht

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////

// CTitleBarButtonDlg Dialogfeld

class CTitleBarButtonDlg : public CDialog
{
// Konstruktion
public:
	CTitleBarButtonDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CTitleBarButtonDlg)
	enum { IDD = IDD_TITLEBARBUTTON_DIALOG };
	CButton	m_btnEnable;
	CStatic	m_static3;
	CStatic	m_static2;
	CStatic	m_static1;
	CButton	m_btnOK;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CTitleBarButtonDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CTitleBarButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBEnable();
	//}}AFX_MSG
	afx_msg LRESULT OnWMU_Hitcapbutton(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bSwitch;
	void OnCapButton3(BOOL bBtnState);
	void OnCapButton2(BOOL bBtnState);
	void OnCapButton1(BOOL bBtnState);
	CFont m_cfStatic1;
	CCaptionButton *m_pCapBtn1;
	CCaptionButton *m_pCapBtn2;
	CCaptionButton *m_pCapBtn3;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_TITLEBARBUTTONDLG_H__3805A4AB_1A54_4E6B_8362_E30D3FB5B823__INCLUDED_)
