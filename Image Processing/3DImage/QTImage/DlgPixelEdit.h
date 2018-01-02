#if !defined(AFX_DLGHISTOGRAM_H__C0ACEA9F_23F7_4D09_8147_64949FF62E15__INCLUDED_)
#define AFX_DLGHISTOGRAM_H__C0ACEA9F_23F7_4D09_8147_64949FF62E15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHistogram.h : header file
//
#include "resource.h"
#include "LineChartCtrl.h"
#include "vtkImageData.h"
#include "SeriesShower.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPixelEdit dialog

class CDlgPixelEdit : public CDialog
{
// Construction
public:
	void UpdateImage();

	CDlgPixelEdit(CWnd* pParent = NULL);   // standard constructor

	CWnd *m_pView;

// Dialog Data
	//{{AFX_DATA(CDlgPixelEdit)
	enum { IDD = IDD_PIXELEDIT };
	CSeriesShower	m_image;
	CLineChartCtrl	m_ctrlOpacity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPixelEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPixelEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SendCommand(int nCmdID,CString& sPara);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHISTOGRAM_H__C0ACEA9F_23F7_4D09_8147_64949FF62E15__INCLUDED_)
