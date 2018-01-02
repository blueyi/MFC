// Demo_DevStudioDoc.h : interface of the CDemo_DevStudioDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO_DEVSTUDIODOC_H__AC8E720F_6379_11D2_9582_0040053E0F5B__INCLUDED_)
#define AFX_DEMO_DEVSTUDIODOC_H__AC8E720F_6379_11D2_9582_0040053E0F5B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDemo_DevStudioDoc : public CDocument
{
protected: // create from serialization only
	CDemo_DevStudioDoc();
	DECLARE_DYNCREATE(CDemo_DevStudioDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_DevStudioDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemo_DevStudioDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo_DevStudioDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_DEVSTUDIODOC_H__AC8E720F_6379_11D2_9582_0040053E0F5B__INCLUDED_)
