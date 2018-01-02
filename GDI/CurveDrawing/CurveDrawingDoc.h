// CurveDrawingDoc.h : interface of the CCurveDrawingDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEDRAWINGDOC_H__770F0C99_F562_4E99_888D_B2E7D935EFCA__INCLUDED_)
#define AFX_CURVEDRAWINGDOC_H__770F0C99_F562_4E99_888D_B2E7D935EFCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCurveDrawingDoc : public CDocument
{
protected: // create from serialization only
	CCurveDrawingDoc();
	DECLARE_DYNCREATE(CCurveDrawingDoc)

// Attributes
public:
	CString str;
	BOOL ifdrawcurve;
	int li;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveDrawingDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveDrawingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurveDrawingDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEDRAWINGDOC_H__770F0C99_F562_4E99_888D_B2E7D935EFCA__INCLUDED_)
