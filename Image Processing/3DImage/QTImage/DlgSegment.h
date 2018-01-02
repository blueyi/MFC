#if !defined(AFX_DLGSEGMENT_H__9A49F5BE_262C_4973_B5D2_637859B32D8A__INCLUDED_)
#define AFX_DLGSEGMENT_H__9A49F5BE_262C_4973_B5D2_637859B32D8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSegment.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSegment dialog
#include "RoiManager.h"
#include "vtkImageData.h"
#include "vvPluginApi.h"

typedef void (__cdecl *vvITKSimpleThresholdInit)(void*);
typedef void (__cdecl *vvITKMedianInit)(void*);
typedef void (__cdecl *vvITKConnectedThresholdInit)(void*);
typedef void (__cdecl *vvITKConfidenceConnectedInit)(void*);

class CDlgMPR;
class CDlgSR;
class CDlgSegment : public CDialog
{
// Construction
public:
	void Clear();
	void UpdateLog(CString sMsg);
	CROI* GetROIAt(int index);
	int GetROICount();
	CROI* GetCurROI();

	CDlgMPR *m_pDlgMPR;
	CDlgSR *m_pDlgSR;

	void SetSeries(vtkImageData *pImage);
	CDlgSegment(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSegment();

	vtkImageData *m_pSegmentedImage;
	vtkImageData *m_pSegmentingImage;
	BOOL m_bEnableDrawROIInProcess;

	CList<CWnd *,CWnd *> m_wndList;
	int m_iCtrlCount,m_iMaxCtrlCount;

	vtkVVPluginInfo m_vvInfo;	
	vtkVVProcessDataStruct m_vvData;
	vvPluginProperty m_vvProp;

// Dialog Data
	//{{AFX_DATA(CDlgSegment)
	enum { IDD = IDD_DIALOG_SEGMENT };
	CButton	m_btnUpdate;
	CButton	m_btnBox;
	CStatic	m_log;
	CStatic	m_algorithmText;
	CComboBox	m_algorithmList;
	CButton	m_btnApply;
	CBitmapButton	m_btnMesh;
	CBitmapButton	m_btnManual;
	CBitmapButton	m_btnCross;
	CBitmapButton	m_btnBrush;
	CBitmapButton	m_btnAuto;
	CEdit	m_ROIName;
	CComboBox	m_ROIList;
	CSliderCtrl	m_OpacitySlider;
	CStatic	m_Opacity;
	CButton	m_Options;
	CButton	m_btnAddROI;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSegment)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSegment)
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSliderRoiOpacity(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboRoi();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonAddroi();
	afx_msg void OnChangeEditRoiname();
	afx_msg void OnButtonCross();
	afx_msg void OnButtonManualSeg();
	afx_msg void OnButtonBrushSeg();
	afx_msg void OnButtonAutoSeg();
	afx_msg void OnButtonMesh();
	afx_msg void OnButtonApply();
	afx_msg LONG OnImageProcessEnd( UINT wParam, LONG lParam );
	afx_msg LONG OnIntimeSegmented( UINT wParam, LONG lParam );
	afx_msg void OnSelchangeComboMethod();
	afx_msg void OnButtonUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void initLib();
	void InitInputData();
	void InitOutputData();
	void ClearGUICtrl();
	void ResetGUICtrl();
	void ResetVVData();

	BOOL m_bInitialized;
	CROIManager *m_pROIManager;

	vtkImageData *m_pImage;
	
	int m_iCurSelectROI;

	HMODULE m_hItkPlug;
	vvITKSimpleThresholdInit m_vvITKSimpleThresholdInit;
	vvITKMedianInit m_vvITKMedianInit;
	vvITKConnectedThresholdInit m_vvITKConnectedThresholdInit;
	vvITKConfidenceConnectedInit m_vvITKConfidenceConnectedInit;

	int m_iLastPos;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSEGMENT_H__9A49F5BE_262C_4973_B5D2_637859B32D8A__INCLUDED_)
