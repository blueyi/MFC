// TestList6Doc.h : interface of the CTestList6Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLIST6DOC_H__D33CF0C1_A213_11E0_9065_0050BF29759A__INCLUDED_)
#define AFX_TESTLIST6DOC_H__D33CF0C1_A213_11E0_9065_0050BF29759A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestList6Doc : public CDocument
{
protected: // create from serialization only
	CTestList6Doc();
	DECLARE_DYNCREATE(CTestList6Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestList6Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestList6Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestList6Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLIST6DOC_H__D33CF0C1_A213_11E0_9065_0050BF29759A__INCLUDED_)
