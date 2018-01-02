/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  de Halleux Jonathan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact: de Halleux Jonathan, pglinfo@patabelgos.org
*/
#if !defined(AFX_PGLGRAPHBITDLG_H__4D439DF6_83C2_11D4_8268_00A024D26A1F__INCLUDED_)
#define AFX_PGLGRAPHBITDLG_H__4D439DF6_83C2_11D4_8268_00A024D26A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphGLBitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphBitDlg dialog

#include "PGLGraphDlg.h"
#include "GDIpInterface.h"

/*! \brief A PGL graph dialog class with a DIB rendering context (SLOW).

\ingroup PGLGraphDlgGroup
\sa CPGLGraph
\sa CPGLGraphDCDlg
\sa CPGLGraphDlgList
*/
class PGL_EXT_CLASS CPGLGraphBitDlg : public CPGLGraphDlg
{
// Construction
public:
	CPGLGraphBitDlg(CWnd* pParent = NULL, CPGLGraph* _pGraph = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPGLGraphBitDlg)
	enum { IDD = IDD_PGL_DIALOG_GRAPH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGLGraphBitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPGLGraphBitDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFigureOpen();
	afx_msg void OnFigureSaveas();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	afx_msg void OnSelectionOrderMovedown();
	afx_msg void OnSelectionOrderMoveup();
	afx_msg void OnSelectionOrderToback();
	afx_msg void OnSelectionOrderTofront();
	afx_msg void OnSelectionSelectall();
	afx_msg void OnSelectionUnhideall();
	afx_msg void OnSelectionUnselect();
	afx_msg void OnToolsAddtext();
	afx_msg void OnToolsSelect();
	afx_msg void OnViewSelect();
	afx_msg void OnViewPan();
	afx_msg void OnViewProperties();
	afx_msg void OnAxeProperties();
	afx_msg void OnViewZoom();
	afx_msg void OnViewZoomAll();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	HICON m_hIcon;
	gfxinterface::CGDIpInterface m_GDIpInterface;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLGRAPHBITDLG_H__4D439DF6_83C2_11D4_8268_00A024D26A1F__INCLUDED_)
