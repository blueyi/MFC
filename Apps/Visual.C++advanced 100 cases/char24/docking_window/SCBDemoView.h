// SCBDemoView.h : interface of the CSCBDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCBDEMOVIEW_H__50CDA4EF_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_)
#define AFX_SCBDEMOVIEW_H__50CDA4EF_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSCBDemoView : public CEditView
{
protected: // create from serialization only
    CSCBDemoView();
    DECLARE_DYNCREATE(CSCBDemoView)

// Attributes
public:
    CSCBDemoDoc* GetDocument();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSCBDemoView)
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
    virtual ~CSCBDemoView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CSCBDemoView)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SCBDemoView.cpp
inline CSCBDemoDoc* CSCBDemoView::GetDocument()
   { return (CSCBDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCBDEMOVIEW_H__50CDA4EF_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_)
