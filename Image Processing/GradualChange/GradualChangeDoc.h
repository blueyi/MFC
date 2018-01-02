// GradualChangeDoc.h : interface of the CGradualChangeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRADUALCHANGEDOC_H__F909E32E_9386_47EC_AEC0_B5D5FB3825DD__INCLUDED_)
#define AFX_GRADUALCHANGEDOC_H__F909E32E_9386_47EC_AEC0_B5D5FB3825DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGradualChangeDoc : public CDocument
{
protected: // create from serialization only
	CGradualChangeDoc();
	DECLARE_DYNCREATE(CGradualChangeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGradualChangeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGradualChangeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGradualChangeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRADUALCHANGEDOC_H__F909E32E_9386_47EC_AEC0_B5D5FB3825DD__INCLUDED_)
