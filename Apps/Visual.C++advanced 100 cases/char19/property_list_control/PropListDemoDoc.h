// PropListDemoDoc.h : interface of the CPropListDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPLISTDEMODOC_H__5B23486D_2251_11D2_94BD_00207811FA68__INCLUDED_)
#define AFX_PROPLISTDEMODOC_H__5B23486D_2251_11D2_94BD_00207811FA68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPropListDemoDoc : public CDocument
{
protected: // create from serialization only
	CPropListDemoDoc();
	DECLARE_DYNCREATE(CPropListDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropListDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropListDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPropListDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPLISTDEMODOC_H__5B23486D_2251_11D2_94BD_00207811FA68__INCLUDED_)
