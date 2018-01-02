// ThumbViewerView.h : interface of the CThumbViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THUMBVIEWERVIEW_H__CA5ED4AC_832E_4B39_B538_0E76AAC95ED9__INCLUDED_)
#define AFX_THUMBVIEWERVIEW_H__CA5ED4AC_832E_4B39_B538_0E76AAC95ED9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	90

class CThumbViewerView;
class CThumbViewerDoc;

class CThumbViewerView : public CListView
{
protected: // create from serialization only
	CThumbViewerView();
	DECLARE_DYNCREATE(CThumbViewerView)

// Attributes
public:
	bool IsRunning() { return m_bRunning;}
	CThumbViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbViewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL TerminateThread();
	void LoadThumbImages();
	virtual ~CThumbViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_bRunning;			// Flag to whether thread is on running or not
	bool m_bTerminate;			// Flag to Thread to be terminated
	unsigned int m_dwThreadID;	// Thread ID
	HANDLE m_hThread, m_hEvent; // Thread and Event handle
	static unsigned __stdcall	LoadThumbNail(LPVOID lpParam);
	CImageList				m_ImageListThumb;		// image list holding the thumbnails
// Generated message map functions
protected:
	//{{AFX_MSG(CThumbViewerView)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ThumbViewerView.cpp
inline CThumbViewerDoc* CThumbViewerView::GetDocument()
   { return (CThumbViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBVIEWERVIEW_H__CA5ED4AC_832E_4B39_B538_0E76AAC95ED9__INCLUDED_)
