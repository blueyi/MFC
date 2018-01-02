
#if !defined(_DIALOG_H_INCLUDED_)
#define _DIALOG_H_INCLUDED_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSizeDlg dialog used for main control change

class CSizeDlg : public CDialog
{
public:
	CSizeDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_SIZEDLG };
	int		m_witem;
	int		m_hitem;
	int		m_fixval;
	int		m_dimcheck;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnDimClicked(UINT nCmdID);
	void OnFixedChanged();

	//{{AFX_MSG(CSizeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif	// _DIALOG_H_INCLUDED_
