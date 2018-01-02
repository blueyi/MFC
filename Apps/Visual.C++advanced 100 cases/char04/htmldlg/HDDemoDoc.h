// HDDemoDoc.h : interface of the CHDDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HDDEMODOC_H__00C5432D_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
#define AFX_HDDEMODOC_H__00C5432D_702E_11D2_ABF7_CCFAF0973072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHDDemoDoc : public CDocument
{
protected: // create from serialization only
	CHDDemoDoc();
	DECLARE_DYNCREATE(CHDDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHDDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHDDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDDEMODOC_H__00C5432D_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
