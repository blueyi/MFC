// XxDoc.h : interface of the CXxDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XXDOC_H__3B54148F_61A8_11D2_86B6_0040055C08D9__INCLUDED_)
#define AFX_XXDOC_H__3B54148F_61A8_11D2_86B6_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CXxDoc : public CDocument
{
protected: // create from serialization only
	CXxDoc();
	DECLARE_DYNCREATE(CXxDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXxDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXxDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XXDOC_H__3B54148F_61A8_11D2_86B6_0040055C08D9__INCLUDED_)
