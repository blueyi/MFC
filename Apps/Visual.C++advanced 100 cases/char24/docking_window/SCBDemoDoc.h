// SCBDemoDoc.h : interface of the CSCBDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCBDEMODOC_H__50CDA4ED_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_)
#define AFX_SCBDEMODOC_H__50CDA4ED_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSCBDemoDoc : public CDocument
{
protected: // create from serialization only
    CSCBDemoDoc();
    DECLARE_DYNCREATE(CSCBDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSCBDemoDoc)
    public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CSCBDemoDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CSCBDemoDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCBDEMODOC_H__50CDA4ED_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_)
