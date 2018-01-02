#if !defined(AFX_DLGSR_H__F6214617_9587_4F6A_9700_9D2E4B942670__INCLUDED_)
#define AFX_DLGSR_H__F6214617_9587_4F6A_9700_9D2E4B942670__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSR dialog
#include "DlgSRCtrl.h"
#include "DlgSRView.h"

class CDlgSR : public CDialog
{
// Construction
public:
	void SetGroundColor(COLORREF color);
	void AddActor(vtkActor *pActor);
	void ClearMesh();
	void AddMesh(vtkImageData *pImage,MESH_OPTIONS option);
	void UpdateMesh();
	void SetSeries(vtkImageData *pImage);
	CDlgSR(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSR();

// Dialog Data
	//{{AFX_DATA(CDlgSR)
	enum { IDD = IDD_IMAGE_SR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSR)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSR)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDlgSRCtrl *m_pSRCtrl;
	CDlgSRView *m_pSRView;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSR_H__F6214617_9587_4F6A_9700_9D2E4B942670__INCLUDED_)
