// viewTwo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CviewTwo view

class CviewTwo : public CView
{
protected:
	CviewTwo();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CviewTwo)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CviewTwo)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CviewTwo();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CviewTwo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
