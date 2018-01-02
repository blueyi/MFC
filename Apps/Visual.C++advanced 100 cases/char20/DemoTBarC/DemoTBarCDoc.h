// DemoTBarCDoc.h : interface of the CDemoTBarCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOTBARCDOC_H__1C58786E_9927_11D2_ABA4_B4FFFFC00000__INCLUDED_)
#define AFX_DEMOTBARCDOC_H__1C58786E_9927_11D2_ABA4_B4FFFFC00000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDemoTBarCDoc : public CDocument
{
protected: // create from serialization only
	CDemoTBarCDoc();
	DECLARE_DYNCREATE(CDemoTBarCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoTBarCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoTBarCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoTBarCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTBARCDOC_H__1C58786E_9927_11D2_ABA4_B4FFFFC00000__INCLUDED_)
