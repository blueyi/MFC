// HeaderCtrlExDoc.h : interface of the CHeaderCtrlExDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEADERCTRLEXDOC_H__F005FAA3_A54D_43B1_A677_1E527AE76D12__INCLUDED_)
#define AFX_HEADERCTRLEXDOC_H__F005FAA3_A54D_43B1_A677_1E527AE76D12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHeaderCtrlExDoc : public CDocument
{
protected: // create from serialization only
	CHeaderCtrlExDoc();
	DECLARE_DYNCREATE(CHeaderCtrlExDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlExDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHeaderCtrlExDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderCtrlExDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCTRLEXDOC_H__F005FAA3_A54D_43B1_A677_1E527AE76D12__INCLUDED_)
