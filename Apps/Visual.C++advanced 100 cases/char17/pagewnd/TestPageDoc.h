// TestPageDoc.h : interface of the CTestPageDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPAGEDOC_H__A2438D3B_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_)
#define AFX_TESTPAGEDOC_H__A2438D3B_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTestPageDoc : public CDocument
{
protected: // create from serialization only
	CTestPageDoc();
	DECLARE_DYNCREATE(CTestPageDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPageDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestPageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestPageDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPAGEDOC_H__A2438D3B_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_)
