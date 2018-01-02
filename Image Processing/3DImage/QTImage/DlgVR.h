#if !defined(AFX_DLGVR_H__D1B37CAD_4AF5_41F5_AC95_69E785E8D8C3__INCLUDED_)
#define AFX_DLGVR_H__D1B37CAD_4AF5_41F5_AC95_69E785E8D8C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVR.h : header file
//
#include "VRView.h"
#include "VRCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVR dialog

#define VR_CTRL_HEIGHT 200

class CDlgVR : public CDialog
{
// Construction
public:
	void SetGroundColor(COLORREF color);
	void SetSeries(vtkImageData *pImage);
	CDlgVR(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgVR();

// Dialog Data
	//{{AFX_DATA(CDlgVR)
	enum { IDD = IDD_IMAGE_VR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVR)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDlgVRView *m_pView3D;
	CDlgVRCtrl *m_pVRCtrl;

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVR_H__D1B37CAD_4AF5_41F5_AC95_69E785E8D8C3__INCLUDED_)
