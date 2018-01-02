// VGisDoc.h : interface of the CVGisDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VGISDOC_H__64AA22DD_E396_4E2A_A574_D4D9425C390C__INCLUDED_)
#define AFX_VGISDOC_H__64AA22DD_E396_4E2A_A574_D4D9425C390C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVGisDoc : public CDocument
{
protected: // create from serialization only
	CVGisDoc();
	DECLARE_DYNCREATE(CVGisDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGisDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVGisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVGisDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGISDOC_H__64AA22DD_E396_4E2A_A574_D4D9425C390C__INCLUDED_)
