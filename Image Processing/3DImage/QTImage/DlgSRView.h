#if !defined(AFX_DLGSRVIEW_H__4F26688E_8CC7_4775_8EAC_9D2C32C7F25B__INCLUDED_)
#define AFX_DLGSRVIEW_H__4F26688E_8CC7_4775_8EAC_9D2C32C7F25B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSRView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSRView dialog
#include "ImageViewer.h"
#include "vtkImageData.h"
#include "vtkOrientationMarkerWidget.h"
#include "GlobalHeader.h"
#include "ROI.h"

class CDlgSRView : public CImageViewer
{
// Construction
public:
	void SetGroundColor(COLORREF color);
	void AddActor(vtkActor *pActor);
	void ClearMesh();
	void AddMesh(vtkImageData *pImage,MESH_OPTIONS option);
	void UpdateMesh();
	void SetSeries(vtkImageData *pImage);
	CDlgSRView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSRView)
	enum { IDD = IDD_IMAGE_SRVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSRView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSRView)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateMesh(vtkImageData *pImage);
	void UpdateMesh(CROI *pROI);
	void UpdateMesh2(CROI *pROI);
	vtkOrientationMarkerWidget* m_pOMW;
	vtkImageData *m_pImage;
	vtkImageData *m_pSegmentedImage;

	MESH_OPTIONS m_meshOptions;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSRVIEW_H__4F26688E_8CC7_4775_8EAC_9D2C32C7F25B__INCLUDED_)
