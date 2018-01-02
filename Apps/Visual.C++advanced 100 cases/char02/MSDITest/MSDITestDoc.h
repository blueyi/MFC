// MSDITestDoc.h : interface of the CMSDITestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSDITESTDOC_H__58EAB96D_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_)
#define AFX_MSDITESTDOC_H__58EAB96D_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMSDITestDoc : public CDocument
{
protected: // create from serialization only
	CMSDITestDoc();
	DECLARE_DYNCREATE(CMSDITestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSDITestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMSDITestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMSDITestDoc)
	afx_msg void OnWindowCformview();
	afx_msg void OnWindowCview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSDITESTDOC_H__58EAB96D_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_)
