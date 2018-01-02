#if !defined(AFX_DLGCONTOURLINE_H__3FE5E69B_755E_4B6A_95A5_F5C86FD9D847__INCLUDED_)
#define AFX_DLGCONTOURLINE_H__3FE5E69B_755E_4B6A_95A5_F5C86FD9D847__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgContourLine.h : header file
//

#include "resource.h"
#include "LineChartCtrl.h"
#include "DlgSR.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgContourLine dialog
class CDlgContourLine : public CDialog
{
// Construction
public:
	CDlgContourLine(CWnd* pParent = NULL);   // standard constructor

	CList<IA_PIXEL_ITEM,IA_PIXEL_ITEM&> m_contourList;

	CWnd *m_pView;
	BOOL m_bLargest;

// Dialog Data
	//{{AFX_DATA(CDlgContourLine)
	enum { IDD = IDD_CONTOUR_CONFIG };
	CLineChartCtrl	m_ctrlContour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgContourLine)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgContourLine)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUpdate();
	afx_msg void OnClose();
	afx_msg void OnCheckLargest();
	afx_msg void OnButtonMesh();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SendCommand(int nCmdID,CString sPara);

	CDlgSR m_srDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONTOURLINE_H__3FE5E69B_755E_4B6A_95A5_F5C86FD9D847__INCLUDED_)
