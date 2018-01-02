// MriLogAnalyserDoc.h : interface of the CMriLogAnalyserDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MRILOGANALYSERDOC_H__D20BD5A2_542C_4AEF_A85B_AA443D09F976__INCLUDED_)
#define AFX_MRILOGANALYSERDOC_H__D20BD5A2_542C_4AEF_A85B_AA443D09F976__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMriLogAnalyserDoc : public CDocument
{
protected: // create from serialization only
	CMriLogAnalyserDoc();
	DECLARE_DYNCREATE(CMriLogAnalyserDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMriLogAnalyserDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMriLogAnalyserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMriLogAnalyserDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRILOGANALYSERDOC_H__D20BD5A2_542C_4AEF_A85B_AA443D09F976__INCLUDED_)
