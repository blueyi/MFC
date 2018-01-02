// EasyFavoriteDlg.h : header file
//
//////////////////////////////////////////////////////////
//
//  만든이 : 서우석
// ----------------------------------------------------
//  이 소스는 공개 소스이며, 이 소스를 사용할 경우
//  반드시 저의 이름을 같이 올려주시면 감사하겠습니다. ^^.
//
//  e-mail : seaousak@hotmail.com
//////////////////////////////////////////////////////////



#if !defined(AFX_EASYFAVORITEDLG_H__8DA5DE98_E89A_40A9_AA27_EFFA258D4138__INCLUDED_)
#define AFX_EASYFAVORITEDLG_H__8DA5DE98_E89A_40A9_AA27_EFFA258D4138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ThumbBtn.h"
#include "CtrView.h"
#include "HyperLink.h"

#define CONTROL_VIEW	33335		

/////////////////////////////////////////////////////////////////////////////
// CEasyFavoriteDlg dialog

class CEasyFavoriteDlg : public CDialog
{
// Construction
public:
	CEasyFavoriteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEasyFavoriteDlg)
	enum { IDD = IDD_EASYFAVORITE_DIALOG };
	CHyperLink	m_ctrEmail;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyFavoriteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEasyFavoriteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CCtrView		m_ctrView;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYFAVORITEDLG_H__8DA5DE98_E89A_40A9_AA27_EFFA258D4138__INCLUDED_)
