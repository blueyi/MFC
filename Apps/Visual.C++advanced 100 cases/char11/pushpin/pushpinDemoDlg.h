#include "pushpin.h"


class CPushpin2Dlg : public CDialog
{
public:
	CPushpin2Dlg(CWnd* pParent = NULL);	// standard constructor

protected:
	//{{AFX_DATA(CPushpin2Dlg)
	enum { IDD = IDD_PUSHPIN2_DIALOG };
	CButton	m_ctrlCheck;
	CPushPinButton m_ctrlPushPin;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPushpin2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	HICON m_hIcon;

	//{{AFX_MSG(CPushpin2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysColorChange();
	afx_msg void OnEdge();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
