// TestList6View.h : interface of the CTestList6View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLIST6VIEW_H__D33CF0C3_A213_11E0_9065_0050BF29759A__INCLUDED_)
#define AFX_TESTLIST6VIEW_H__D33CF0C3_A213_11E0_9065_0050BF29759A__INCLUDED_

#include "ListViewExt.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestList6View : public CListViewExt
{
protected: // create from serialization only
	CTestList6View();
	DECLARE_DYNCREATE(CTestList6View)

// Attributes
public:
	CTestList6Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestList6View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestList6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CEdit m_Edit;
	CComboBox m_Combo;
	CDateTimeCtrl m_DT;
	static BOOL EndEditor(CWnd** pWnd, int nRow, int nColumn, CString &strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
	static BOOL InitEditor(CWnd** pWnd, int nRow, int nColumn, CString &strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);

// Generated message map functions
protected:
	void RefreshList();
	void PopulateList();
	//{{AFX_MSG(CTestList6View)
	afx_msg void OnDestroy();
	afx_msg void OnViewRefresh();
	afx_msg void OnViewLineup();
	//}}AFX_MSG
	afx_msg void OnListStyle(UINT nCommandID);
	afx_msg void OnUpdateListStyles(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

private:
	CFont* m_pFont;
};

#ifndef _DEBUG  // debug version in TestList6View.cpp
inline CTestList6Doc* CTestList6View::GetDocument()
   { return (CTestList6Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLIST6VIEW_H__D33CF0C3_A213_11E0_9065_0050BF29759A__INCLUDED_)
