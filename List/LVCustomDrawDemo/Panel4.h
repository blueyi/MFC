#if !defined(AFX_PANEL4_H__95CB60A0_2A8F_11D3_8D3B_CC2D74981531__INCLUDED_)
#define AFX_PANEL4_H__95CB60A0_2A8F_11D3_8D3B_CC2D74981531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Panel4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanel4 dialog

class CPanel4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPanel4)

// Construction
public:
	CPanel4();
	~CPanel4();

// Dialog Data
	//{{AFX_DATA(CPanel4)
	enum { IDD = IDD_PANEL4 };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPanel4)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CImageList m_imglist;

	// Generated message map functions
	//{{AFX_MSG(CPanel4)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    afx_msg void OnCustomdrawList(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEL4_H__95CB60A0_2A8F_11D3_8D3B_CC2D74981531__INCLUDED_)
