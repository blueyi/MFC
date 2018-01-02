#if !defined(AFX_IMAGEVIEWER_H__83817EC5_04E4_4968_ADCE_41AF5189B359__INCLUDED_)
#define AFX_IMAGEVIEWER_H__83817EC5_04E4_4968_ADCE_41AF5189B359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageViewer.h : header file
//
#include "vtkHeader.h"
#include "vtkMFCWindow.h"
/////////////////////////////////////////////////////////////////////////////
// CImageViewer dialog

class CImageViewer : public CDialog
{
// Construction
public:
	CImageViewer(UINT IDD,CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageViewer();

	vtkRenderer            *m_pRenderer;
	BOOL m_bSelected;

// Dialog Data
	//{{AFX_DATA(CImageViewer)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageViewer)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	
	vtkMFCWindow          *m_pMFCWindow;
	vtkRenderWindowInteractor *m_pInteractor;
	int           m_Type; //=0 2D Viewer =1 3D Viewer
	BOOL m_bEnableSlider;
	COLORREF m_groundColor;

	// Generated message map functions
	//{{AFX_MSG(CImageViewer)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEWER_H__83817EC5_04E4_4968_ADCE_41AF5189B359__INCLUDED_)
