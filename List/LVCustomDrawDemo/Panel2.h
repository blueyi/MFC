#if !defined(AFX_PANEL2_H__4EC7FCB0_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
#define AFX_PANEL2_H__4EC7FCB0_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Panel2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanel2 dialog

class CPanel2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPanel2)

// Construction
public:
	CPanel2();
	~CPanel2();

// Dialog Data
	//{{AFX_DATA(CPanel2)
	enum { IDD = IDD_PANEL2 };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPanel2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPanel2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    afx_msg void OnCustomdrawList(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEL2_H__4EC7FCB0_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
