// splittstDoc.h : interface of the CSplittstDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTSTDOC_H__FA98B711_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_)
#define AFX_SPLITTSTDOC_H__FA98B711_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSplittstDoc : public CDocument
{
protected: // create from serialization only
	CSplittstDoc();
	DECLARE_DYNCREATE(CSplittstDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplittstDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplittstDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplittstDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTSTDOC_H__FA98B711_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_)
