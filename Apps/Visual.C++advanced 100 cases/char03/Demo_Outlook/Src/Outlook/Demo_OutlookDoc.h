// Demo_OutlookDoc.h : interface of the CDemo_OutlookDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_Demo_OutlookDOC_H__7BB52B97_0704_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_Demo_OutlookDOC_H__7BB52B97_0704_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDemo_OutlookDoc : public CDocument
{
protected: // create from serialization only
	CDemo_OutlookDoc();
	DECLARE_DYNCREATE(CDemo_OutlookDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_OutlookDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemo_OutlookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo_OutlookDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Demo_OutlookDOC_H__7BB52B97_0704_11D2_AB9F_441100C10000__INCLUDED_)
