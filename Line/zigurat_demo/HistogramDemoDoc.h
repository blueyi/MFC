// HistogramDemoDoc.h : interface of the CHistogramDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTOGRAMDEMODOC_H__77F3AFAC_402C_47A7_83D0_516E82185D17__INCLUDED_)
#define AFX_HISTOGRAMDEMODOC_H__77F3AFAC_402C_47A7_83D0_516E82185D17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHistogramDemoDoc : public CDocument
{
protected: // create from serialization only
	CHistogramDemoDoc();
	DECLARE_DYNCREATE(CHistogramDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHistogramDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHistogramDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMDEMODOC_H__77F3AFAC_402C_47A7_83D0_516E82185D17__INCLUDED_)
