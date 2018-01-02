// TestMyCanEditListDoc.h : interface of the CTestMyCanEditListDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMYCANEDITLISTDOC_H__F0EBC9CD_1393_449F_8ACB_77349B4687E3__INCLUDED_)
#define AFX_TESTMYCANEDITLISTDOC_H__F0EBC9CD_1393_449F_8ACB_77349B4687E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestMyCanEditListDoc : public CDocument
{
protected: // create from serialization only
	CTestMyCanEditListDoc();
	DECLARE_DYNCREATE(CTestMyCanEditListDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMyCanEditListDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestMyCanEditListDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestMyCanEditListDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMYCANEDITLISTDOC_H__F0EBC9CD_1393_449F_8ACB_77349B4687E3__INCLUDED_)
