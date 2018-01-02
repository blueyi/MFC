// MultiWindowDoc.h : interface of the CMultiWindowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTIWINDOWDOC_H__32913E2B_6D4A_11D0_B063_E8509A000000__INCLUDED_)
#define AFX_MULTIWINDOWDOC_H__32913E2B_6D4A_11D0_B063_E8509A000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMultiWindowDoc : public CDocument
{
protected: // create from serialization only
	CMultiWindowDoc();
	DECLARE_DYNCREATE(CMultiWindowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiWindowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultiWindowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultiWindowDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIWINDOWDOC_H__32913E2B_6D4A_11D0_B063_E8509A000000__INCLUDED_)
