// testpglDoc.h : interface of the CTestpglDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPGLDOC_H__0299685A_8623_11D4_826B_00A024D26A1F__INCLUDED_)
#define AFX_TESTPGLDOC_H__0299685A_8623_11D4_826B_00A024D26A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestpglDoc : public CDocument
{
protected: // create from serialization only
	CTestpglDoc();
	DECLARE_DYNCREATE(CTestpglDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestpglDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestpglDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestpglDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPGLDOC_H__0299685A_8623_11D4_826B_00A024D26A1F__INCLUDED_)
