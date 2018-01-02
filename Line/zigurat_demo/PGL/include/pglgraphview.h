#if !defined(AFX_PGLGRAPHVIEW_H__D2A5BBE5_2C7A_41A6_8F22_9959D09CD057__INCLUDED_)
#define AFX_PGLGRAPHVIEW_H__D2A5BBE5_2C7A_41A6_8F22_9959D09CD057__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLGraphView.h : header file
//
#include "PGLGraph.h"

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphView view

class PGL_EXT_CLASS CPGLGraphView : public CView
{
protected:
	CPGLGraphView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPGLGraphView)

// Attributes
public:

// Operations
public:
	CMenu* LoadMenu();
	// Sets the CPGLGraph object to plot on view 
	void SetGraph(CPGLGraph* pGraph);
	CPGLGraph* GetGraph() {	return m_pGraph;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGLGraphView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPGLGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CPGLMouse m_mouse;
	CPGLGraph* m_pGraph;
	int m_iMouseMode;

	gfxinterface::CGDIpInterface m_GDIpInterface;
#ifndef _DEBUG
	Gdiplus::Bitmap* m_pMemBitmap;
#endif
	
	//{{AFX_MSG(CPGLGraphView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnEditCopy();
	afx_msg void OnObjectsExplorer();
	afx_msg void OnPglFileExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLGRAPHVIEW_H__D2A5BBE5_2C7A_41A6_8F22_9959D09CD057__INCLUDED_)
