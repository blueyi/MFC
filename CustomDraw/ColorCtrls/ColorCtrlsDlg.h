#ifndef _CCOLORCTRLS_DLG_H_
#define _CCOLORCTRLS_DLG_H_

#include "ColorButton.h"
#include "ColorEdit.h"
#include "ColorStatic.h"
#include "ColorComboBox.h"

class CColorCtrlsDlg : public CDialog
{

public:

        CColorCtrlsDlg(CWnd* pParent = NULL);	// standard constructor

	//{{AFX_DATA(CColorCtrlsDlg)
	enum { IDD = IDD_COLORCTRLS_DIALOG };
	CColorStatic	m_stcColor;
	CColorButton	m_btnDisabled;
	CColorEdit	m_edtColor;
	CColorComboBox	m_cbColor;
	CColorButton	m_btnColor;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CColorCtrlsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

        HICON m_hIcon;

	//{{AFX_MSG(CColorCtrlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
