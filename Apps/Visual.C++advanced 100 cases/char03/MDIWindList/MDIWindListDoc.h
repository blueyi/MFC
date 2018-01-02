// MDIWindListDoc.h : interface of the CMDIWindListDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDIWINDLISTDOC_H__C67D439C_F890_11D1_83BA_0000B43382FE__INCLUDED_)
#define AFX_MDIWINDLISTDOC_H__C67D439C_F890_11D1_83BA_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMDIWindListDoc : public CDocument
{
protected: // create from serialization only
	CMDIWindListDoc();
	DECLARE_DYNCREATE(CMDIWindListDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIWindListDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMDIWindListDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDIWindListDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIWINDLISTDOC_H__C67D439C_F890_11D1_83BA_0000B43382FE__INCLUDED_)
