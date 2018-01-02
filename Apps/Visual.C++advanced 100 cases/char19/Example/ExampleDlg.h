// ExampleDlg.h : Header-Datei
//

#if !defined(AFX_EXAMPLEDLG_H__B5C9BF29_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_)
#define AFX_EXAMPLEDLG_H__B5C9BF29_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CExampleDlg Dialogfeld


class CExampleDlg : public CDialog
{
// Konstruktion
public:
	CExampleDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CExampleDlg)
	enum { IDD = IDD_EXAMPLE_DIALOG };
		// HINWEIS: der Klassenassistent fügt an dieser Stelle Datenelemente (Members) ein
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CExampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;
	PropPage1			m_propPage1;
	PropPage2			m_propPage2;
	CMyPropertySheet	m_propertySheet;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_EXAMPLEDLG_H__B5C9BF29_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_)
