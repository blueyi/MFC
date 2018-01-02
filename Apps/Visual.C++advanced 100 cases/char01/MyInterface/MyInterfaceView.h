// MyInterfaceView.h : interface of the CMyInterfaceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYINTERFACEVIEW_H__E1B4C9CD_DF44_11D4_AF84_18E6A0000000__INCLUDED_)
#define AFX_MYINTERFACEVIEW_H__E1B4C9CD_DF44_11D4_AF84_18E6A0000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyInterfaceView : public CView
{
protected: // create from serialization only
	CMyInterfaceView();
	DECLARE_DYNCREATE(CMyInterfaceView)

// Attributes
public:
	CMyInterfaceDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyInterfaceView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyInterfaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyInterfaceView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyInterfaceView.cpp
inline CMyInterfaceDoc* CMyInterfaceView::GetDocument()
   { return (CMyInterfaceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYINTERFACEVIEW_H__E1B4C9CD_DF44_11D4_AF84_18E6A0000000__INCLUDED_)
