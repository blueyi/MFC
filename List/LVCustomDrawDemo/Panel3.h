#if !defined(AFX_PANEL3_H__A1A33FE2_379D_11D3_B9D2_00C04FAC114C__INCLUDED_)
#define AFX_PANEL3_H__A1A33FE2_379D_11D3_B9D2_00C04FAC114C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Panel3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanel3 dialog

class CPanel3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPanel3)

// Construction
public:
	CPanel3();
	~CPanel3();

// Dialog Data
	//{{AFX_DATA(CPanel3)
	enum { IDD = IDD_PANEL3 };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPanel3)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CImageList m_imglist;

	// Generated message map functions
	//{{AFX_MSG(CPanel3)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    afx_msg void OnCustomdrawList(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEL3_H__A1A33FE2_379D_11D3_B9D2_00C04FAC114C__INCLUDED_)
