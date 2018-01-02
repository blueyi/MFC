// WzdDoc.h : interface of the CWzdDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WZDDOC_H__CA9038EE_B0DF_11D1_A18C_DCB3C85EBD34__INCLUDED_)
#define AFX_WZDDOC_H__CA9038EE_B0DF_11D1_A18C_DCB3C85EBD34__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CWzdDoc : public CDocument
{
protected: // create from serialization only
	CWzdDoc();
	DECLARE_DYNCREATE(CWzdDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWzdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWzdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWzdDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WZDDOC_H__CA9038EE_B0DF_11D1_A18C_DCB3C85EBD34__INCLUDED_)
