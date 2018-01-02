// QTImageDlg.h : header file
//

#if !defined(AFX_QTIMAGEDLG_H__CCFBE5E9_59EE_4B67_A7F9_3701FA1DB526__INCLUDED_)
#define AFX_QTIMAGEDLG_H__CCFBE5E9_59EE_4B67_A7F9_3701FA1DB526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTToolkitPro.h"
#include "SeriesManager.h"
#include "ImageViewerManager.h"
#include "DlgVR.h"
#include "DlgContourLine.h"
#include "DlgPixelEdit.h"
#include "DlgMPR.h"
#include "ROIManager.h"

/////////////////////////////////////////////////////////////////////////////
// CQTImageDlg dialog
#define CDialogSampleDlgBase CXTPDialogBase<CXTResizeDialog>

class CQTImageDlg : public CDialogSampleDlgBase
{
// Construction
public:
	
	

	CQTImageDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CQTImageDlg();

	CSeriesManager m_seriesManager;
	C2DViewerManager m_view2DManager;
	CDlgContourLine *m_pDlgContour;
	CDlgPixelEdit *m_pDlgPixelEdit;
	CString m_sNewOpenSeriesPath;
	CDlgMPR *m_pDlgMPR;

	CROIManager m_roiManager;

	COLORREF m_2DBKColor;

// Dialog Data
	//{{AFX_DATA(CQTImageDlg)
	enum { IDD = IDD_QTIMAGE_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQTImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQTImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSetMsgString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowSeries(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFileImportSeries();
	afx_msg void OnFileExit();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnView3dVolRender();
	afx_msg void OnView3dGroundColor();
	afx_msg void OnView2dGroundColor();
	afx_msg void OnFileSaveSeries();
	afx_msg void OnView2dResetWindowlevel();
	afx_msg void OnView2dContourline();
	afx_msg void OnEditPixel();
	afx_msg void OnView2dMpr();
	afx_msg void OnRoiSegment();
	afx_msg void OnView3dDelaunay();
	afx_msg void OnView3dPowercrust();
	afx_msg void OnView3dSolidSurface();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	
	CXTPStatusBar m_wndStatusBar;
	CDlgVR *m_pVRDlg;
	CDlgSR m_srDlg;
	void RepositionControls();
	CRect m_rcBorders;
	CRect m_clientRect;
	BOOL m_bInRepositionControls, m_bInitDone;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QTIMAGEDLG_H__CCFBE5E9_59EE_4B67_A7F9_3701FA1DB526__INCLUDED_)
