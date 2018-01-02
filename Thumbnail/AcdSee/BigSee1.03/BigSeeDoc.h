// BigSeeDoc.h : interface of the CBigSeeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIGSEEDOC_H__65FC334B_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_BIGSEEDOC_H__65FC334B_C244_11D6_AFCA_001088A02FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBigSeeDoc : public CDocument
{
protected: // create from serialization only
	CBigSeeDoc();
	DECLARE_DYNCREATE(CBigSeeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigSeeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strFilePath;
	virtual ~CBigSeeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBigSeeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGSEEDOC_H__65FC334B_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
