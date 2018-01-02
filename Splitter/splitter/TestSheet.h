#if !defined(AFX_TESTSHEET_H__B296B4D4_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
#define AFX_TESTSHEET_H__B296B4D4_D29B_11D4_AF20_00104B2CD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestSheet

class CTestSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTestSheet)

// Construction
public:
	CTestSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTestSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestSheet();

	// Generated message map functions
protected:
  
  BOOL OnInitDialog();

  CStatusBar m_statusBar;
  CRect m_PageRect;
  BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//{{AFX_MSG(CTestSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
  LONG OnResizePage(UINT, LONG);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSHEET_H__B296B4D4_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
