// FlatSplitter_DemoDoc.h : interface of the CFlatSplitter_DemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLATSPLITTER_DEMODOC_H__88213D35_9947_435A_A063_6EE36EF2D0E4__INCLUDED_)
#define AFX_FLATSPLITTER_DEMODOC_H__88213D35_9947_435A_A063_6EE36EF2D0E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFlatSplitter_DemoDoc : public CDocument
{
protected: // create from serialization only
	CFlatSplitter_DemoDoc();
	DECLARE_DYNCREATE(CFlatSplitter_DemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatSplitter_DemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlatSplitter_DemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlatSplitter_DemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATSPLITTER_DEMODOC_H__88213D35_9947_435A_A063_6EE36EF2D0E4__INCLUDED_)
