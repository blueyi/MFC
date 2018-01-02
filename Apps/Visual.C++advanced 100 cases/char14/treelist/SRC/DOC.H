// Doc.h : interface of the CTreeListDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CTreeListDoc : public CDocument
{
protected: // create from serialization only
	CTreeListDoc();
	DECLARE_DYNCREATE(CTreeListDoc)

// Attributes
public:


private:


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeListDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	//afx_msg void OnTreeSelect(WPARAM wParam, LPARAM lParam);

// Implementation
public:
	virtual ~CTreeListDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeListDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
