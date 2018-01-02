// IGfxTestDoc.h : interface of the CIGfxTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IGFXTESTDOC_H__DE812558_D91C_4F8C_BEF3_440402E91F5D__INCLUDED_)
#define AFX_IGFXTESTDOC_H__DE812558_D91C_4F8C_BEF3_440402E91F5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIGfxTestDoc : public CDocument
{
protected: // create from serialization only
	CIGfxTestDoc();
	DECLARE_DYNCREATE(CIGfxTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIGfxTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIGfxTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIGfxTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CIGfxTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IGFXTESTDOC_H__DE812558_D91C_4F8C_BEF3_440402E91F5D__INCLUDED_)
