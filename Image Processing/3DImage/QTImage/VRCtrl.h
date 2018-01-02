#if !defined(AFX_DLGVOLUMESETTING_H__246639B5_3FDE_4218_AD34_77E86642E8D9__INCLUDED_)
#define AFX_DLGVOLUMESETTING_H__246639B5_3FDE_4218_AD34_77E86642E8D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVolumeSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVRCtrl dialog
#include "Resource.h"
#include "LineChartCtrl.h"
#include "vtkHeader.h"
#include "VRView.h"
 
#define VR_OPACITY_CTRL_LEFT 550

class CDlgVRCtrl : public CDialog
{
// Construction
public:
	void Update();
	CDlgVRCtrl(CWnd* pParent = NULL);   // standard constructor
		
	CDlgVRView *m_pVRView;
	

// Dialog Data
	//{{AFX_DATA(CDlgVRCtrl)
	enum { IDD = IDD_IMAGE_VRCTRL };
	CSliderCtrl	m_lodSlider;
	CLineChartCtrl	m_ctrlGrad;
	CLineChartCtrl	m_ctrlOpacity;
	int		m_iMode;
	int		m_iEngine;
	BOOL	m_bUseGrad;
	BOOL	m_bUseShade;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVRCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVRCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOpacity();
	afx_msg void OnRadioMip();
	afx_msg void OnRadioComposite();
	afx_msg void OnRadioSoftware();
	afx_msg void OnRadioHardware();
	afx_msg void OnButtonGrad();
	afx_msg void OnCheckGradon();
	afx_msg void OnCheckShade();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLoad();
	afx_msg LRESULT OnCallCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetfocusComboGrad();
	afx_msg void OnSetfocusComboOpacity();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnReleasedcaptureSliderLod(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioFixpoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetPixelRange();
	void SendCommand(int nCmdID,CString sPara);
	BOOL m_bRealUpdate;  //是否实施更新

	VOLRENDER_CONFIG *m_pVolConfig;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVOLUMESETTING_H__246639B5_3FDE_4218_AD34_77E86642E8D9__INCLUDED_)
