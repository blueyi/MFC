// MyInterfaceDoc.h : interface of the CMyInterfaceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYINTERFACEDOC_H__E1B4C9CB_DF44_11D4_AF84_18E6A0000000__INCLUDED_)
#define AFX_MYINTERFACEDOC_H__E1B4C9CB_DF44_11D4_AF84_18E6A0000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyInterfaceDoc : public CDocument
{
protected: // create from serialization only
	CMyInterfaceDoc();
	DECLARE_DYNCREATE(CMyInterfaceDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyInterfaceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyInterfaceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyInterfaceDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYINTERFACEDOC_H__E1B4C9CB_DF44_11D4_AF84_18E6A0000000__INCLUDED_)
