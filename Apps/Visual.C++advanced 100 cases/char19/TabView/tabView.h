class CTabDoc;

class CTabView : public CView
{
protected: // create from serialization only
	CTabView();
	DECLARE_DYNCREATE(CTabView)

// Attributes
public:
	CTabDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in tabView.cpp
inline CTabDoc* CTabView::GetDocument()
   { return (CTabDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
