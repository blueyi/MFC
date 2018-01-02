#if !defined(AFX_EXLISTCTRL_H__E5106B21_2325_4D5C_82A3_2DC2166303DA__INCLUDED_)
#define AFX_EXLISTCTRL_H__E5106B21_2325_4D5C_82A3_2DC2166303DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExListCtrl window

//自动调整列的宽度，使不出现水平滚动条的ListCtrl控件。(该控件最多只能有1列)

class CExListCtrl : public CListCtrl
{
private:
	int nBorder;   //GetWindowRect().Width()-GetClientRect().Width()

// Construction
public:
	CExListCtrl();

// Attributes
public:

// Operations
public:
	int InsertItem(const LVITEM* pItem);
	int InsertItem(int nItem, LPCTSTR lpszItem);
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,
		UINT nStateMask, int nImage, LPARAM lParam);
	BOOL DeleteItem(int nItem);
	BOOL DeleteAllItems();

	int InsertColumn(int nCol, const LVCOLUMN* pColumn);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);  

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	void ResetColumnWidth();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXLISTCTRL_H__E5106B21_2325_4D5C_82A3_2DC2166303DA__INCLUDED_)
