#if !defined(AFX_MYLISTCTRL_H__EC71BB08_E6A3_45E5_BFA1_ABF0B0EFB5CB__INCLUDED_)
#define AFX_MYLISTCTRL_H__EC71BB08_E6A3_45E5_BFA1_ABF0B0EFB5CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class  CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ClickColumn(int column, BOOL descent);
	void SortColumn(int column,BOOL descent);
	static int CALLBACK MyCompareProcNumD(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	static int CALLBACK MyCompareProcNumA(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	static int CALLBACK MyCompareProcStrD(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	static int CALLBACK MyCompareProcStrA(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
   
	CStringArray m_arrColType;

	virtual ~CMyListCtrl();
//protected:
	
	BOOL m_bMode;
	int m_nSortItem;
	////
	BOOL m_bSortColumn;
	// Generated message map functions
//protected:
public:
	void SetSortColumn(BOOL bSortColumn);
	BOOL IsSortColumn();
	void DeleteSelected();
	void DeleteNoSelected();
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__EC71BB08_E6A3_45E5_BFA1_ABF0B0EFB5CB__INCLUDED_)
