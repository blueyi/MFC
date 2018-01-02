#if !defined(AFX_PGLGRAPHDLG_H__38C26E0A_DB09_405D_BB35_1CB762916549__INCLUDED_)
#define AFX_PGLGRAPHDLG_H__38C26E0A_DB09_405D_BB35_1CB762916549__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLGraphDlg.h : header file
//
#include "PGLGraph.h"
#include "PGLView2D.h"
#include "PGLMouse.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphDlg dialog

class PGL_EXT_CLASS CPGLGraphDlg : public CDialog
{
// Construction
public:
	CPGLGraphDlg(CWnd* pParent = NULL, CPGLGraph* _graph = NULL);   // standard constructor
	~CPGLGraphDlg();

	//! return graph pointer
	CPGLGraph* GetGraph()
	{	return m_pGraph;};
	//! Set graphGL.
	void SetGraph(CPGLGraph* _graph)
	{	ASSERT_VALID(_graph); m_pGraph=_graph;};


// Dialog Data
	//{{AFX_DATA(CPGLGraphDlg)
	enum { IDD = IDD_PGL_DIALOG_GRAPH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGLGraphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Implementation
	void ExportToVectors();

	void Serialize(CArchive &archive);

	// Generated message map functions
	//{{AFX_MSG(CPGLGraphDlg)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CPGLMouse m_mouse;
	CPGLGraph* m_pGraph;
	int m_iMouseMode;
	HICON m_hIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLGRAPHDLG_H__38C26E0A_DB09_405D_BB35_1CB762916549__INCLUDED_)
