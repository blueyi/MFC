// DibDoc.h : interface of the CDibDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBDOC_H__A2E75B3D_086D_11D2_8A46_0000E81D3D27__INCLUDED_)
#define AFX_DIBDOC_H__A2E75B3D_086D_11D2_8A46_0000E81D3D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDibDoc : public CDocument
{
protected: // create from serialization only
	CDibDoc();
	DECLARE_DYNCREATE(CDibDoc)

// Attributes
public:
	CPalette* GetDocPalette() const { return m_DIB.m_pPalette; }
	BOOL IsValid() const { return m_DIB.IsValid(); }
	DWORD Width() const { return m_DIB.Width(); }
	DWORD Height() const { return m_DIB.Height(); }
	BOOL  PaintDIB(HDC hDC, LPRECT pDCRect, LPRECT pDIBRect) const { return m_DIB.Paint(hDC, pDCRect, pDIBRect); }
	HGLOBAL CopyDIBToHandle() const { return m_DIB.CopyToHandle(); }

// Operations
public:
	DWORD ReadDIBFromHandle(HGLOBAL hGlobal);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDibDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDibDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CDib m_DIB;

// Generated message map functions
protected:
	//{{AFX_MSG(CDibDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBDOC_H__A2E75B3D_086D_11D2_8A46_0000E81D3D27__INCLUDED_)
