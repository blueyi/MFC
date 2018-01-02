// DBBTestView.h : interface of the CDBBTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBBTESTVIEW_H__2CD8D2FC_AB25_4C98_B8F6_8C34C6987BDE__INCLUDED_)
#define AFX_DBBTESTVIEW_H__2CD8D2FC_AB25_4C98_B8F6_8C34C6987BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDBBTestView : public CView
{
protected: // create from serialization only
	CDBBTestView();
	DECLARE_DYNCREATE(CDBBTestView)

// Attributes
public:
	CDBBTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBBTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitialDBB();
	virtual ~CDBBTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDBBTestView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTestNormal();
	afx_msg void OnTestDbb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bStart;
	void DrawManyCircleUseDBB();
	int m_nRadius;
	void DrawManyCircle();
	CBitmap m_Bmp;
	CDC m_dcMemory;
	BOOL m_bUseDBB;
};

#ifndef _DEBUG  // debug version in DBBTestView.cpp
inline CDBBTestDoc* CDBBTestView::GetDocument()
   { return (CDBBTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBBTESTVIEW_H__2CD8D2FC_AB25_4C98_B8F6_8C34C6987BDE__INCLUDED_)
