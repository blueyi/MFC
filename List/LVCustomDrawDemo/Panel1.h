#if !defined(AFX_PANEL1_H__4EC7FCAE_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
#define AFX_PANEL1_H__4EC7FCAE_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Panel1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanel1 dialog

class CPanel1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPanel1)

// Construction
public:
	CPanel1();
	~CPanel1();

// Dialog Data
	//{{AFX_DATA(CPanel1)
	enum { IDD = IDD_PANEL1 };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPanel1)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPanel1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    afx_msg void OnCustomdrawList(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEL1_H__4EC7FCAE_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
