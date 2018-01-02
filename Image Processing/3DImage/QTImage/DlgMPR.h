#if !defined(AFX_DLGMPR_H__F3F45758_E151_4AA9_A204_0D52A6DB7801__INCLUDED_)
#define AFX_DLGMPR_H__F3F45758_E151_4AA9_A204_0D52A6DB7801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMPR.h : header file
//
#include "vtkImageData.h"
#include "memDC.h"
#include "mv.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgMPR dialog
#include "DlgSR.h"
#include "DlgSegment.h"
#include "RoiManager.h"

class CDlgMPR : public CDialog
{
// Construction
public:
	void DrawROI(int imageType=0);
	void EnableManualSeg(BOOL bEnable);
	void EnableCross(BOOL bEnable);
	void Layout();
	CDlgMPR(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMPR();
	int m_iCurSlice1,m_iCurSlice2,m_iCurSlice3;

	POINT m_pntCross1;

	int m_iViewMode;
	void SetSeries(vtkImageData* pData);

// Dialog Data
	//{{AFX_DATA(CDlgMPR)
	enum { IDD = IDD_DIALOG_MPR };
	CSliderCtrl	m_slider3;
	CSliderCtrl	m_slider2;
	CSliderCtrl	m_slider1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMPR)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMPR)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	
	void DefineCrossLine(CPoint point);
	void CalcMatrix(Matrix mOld,Matrix mOri,double *space,double *origin,Matrix &mNewImage);
	void CreateDraw1();
	void CreateDraw2();
	void CreateDraw3();
	vtkImageData *m_pImage;
	int m_Dim1[3],m_Dim2[3],m_Dim3[3];

	CMemDC m_memDC1,m_memDC2,m_memDC3;
	CRect m_rcSlice1,m_rcSlice2,m_rcSlice3;
	CRect m_rcRealDraw1,m_rcRealDraw2,m_rcRealDraw3;
	
	POINT m_pnt1,m_pnt2,m_pnt3;
	Matrix m_mSlice1,m_mSlice2,m_mSlice3;
	
	COLORREF m_bkColor;
	BOOL m_bLBDown;

	CDlgSR *m_pDlgSR;
	CDlgSegment *m_pDlgSeg;

	CROI *m_pROI;
	ROI m_TempROILine;

	BOOL m_bEnableCross;
	BOOL m_bEnableManualSeg;

	BOOL m_bDrawing;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMPR_H__F3F45758_E151_4AA9_A204_0D52A6DB7801__INCLUDED_)
