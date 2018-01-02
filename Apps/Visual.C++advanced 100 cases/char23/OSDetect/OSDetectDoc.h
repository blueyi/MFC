// OSDetectDoc.h : interface of the COSDetectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OSDETECTDOC_H__EBEB957C_3821_11D2_8B51_000000000000__INCLUDED_)
#define AFX_OSDETECTDOC_H__EBEB957C_3821_11D2_8B51_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class COSDetectDoc : public CDocument
{
protected: // create from serialization only
	COSDetectDoc();
	DECLARE_DYNCREATE(COSDetectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSDetectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COSDetectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COSDetectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSDETECTDOC_H__EBEB957C_3821_11D2_8B51_000000000000__INCLUDED_)
