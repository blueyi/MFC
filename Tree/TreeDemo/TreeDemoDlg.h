// TreeDemoDlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include "RHTree.h"

// CTreeDemoDlg dialog
class CTreeDemoDlg : public CDialog
{
// Construction
public:
	CTreeDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TREEDEMO_DIALOG };
	CRHTree				m_ctrlTree;
//	CTreeCtrl			m_ctrlTree;
	CScrollBar			m_ScrollGripper;		// Actually a scrollbar, but it provides our resizing gripper
	CImageList			m_ILTree;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
