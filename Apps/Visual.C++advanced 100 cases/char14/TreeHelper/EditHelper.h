#if !defined(AFX_EDITHELPER_H__5DD969DF_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_)
#define AFX_EDITHELPER_H__5DD969DF_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditHelper.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditHelper window

class CEditHelper : public CEdit
{
// Construction
public:
	CEditHelper();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditHelper)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetHelperFlags( LPCTSTR sSeparator, UINT nResID = 0 );
	virtual ~CEditHelper();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditHelper)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CString	m_sSeparator;
	UINT		m_nBitmapID ;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITHELPER_H__5DD969DF_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_)
