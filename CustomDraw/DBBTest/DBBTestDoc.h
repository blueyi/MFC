// DBBTestDoc.h : interface of the CDBBTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBBTESTDOC_H__982C708F_E22D_4EE9_A489_B9B945BF81ED__INCLUDED_)
#define AFX_DBBTESTDOC_H__982C708F_E22D_4EE9_A489_B9B945BF81ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDBBTestDoc : public CDocument
{
protected: // create from serialization only
	CDBBTestDoc();
	DECLARE_DYNCREATE(CDBBTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBBTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDBBTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDBBTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBBTESTDOC_H__982C708F_E22D_4EE9_A489_B9B945BF81ED__INCLUDED_)
