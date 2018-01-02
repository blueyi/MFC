// MainFrm.h : interface of the CMainFrame class
//
#if !defined(AFX_MAINFRM_H__9ED70A69_C975_4F20_9D4E_B2877E3575D0__INCLUDED_)
#define AFX_MAINFRM_H__9ED70A69_C975_4F20_9D4E_B2877E3575D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ------------------------------------------------------------------------------------------
#include "trayicon.h"
#include "CommonDefine.h"

#include "ComSocket_SysDiagnosis.h"
#include "LogFileAccess.h"


//#include "UGC\\UGCtrl.h"


///////////////////////////////////////////////////////
#ifndef _CHEN_SHI_
#define _CHEN_SHI_
#endif
#ifdef _CHEN_SHI_
//#include "log.h"
#endif


// ------------------------------------------------------------------------------------------
#define BKCOLOR RGB(192, 192, 192)

// ------------------------------------------------------------------------------------------
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
//ZXN	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//ZXN	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Code();
	
	
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;

	CTrayIcon	m_trayIcon;		// my tray icon
	CEdit		m_wndEdit;		// to display tray notifications
	int			m_iWhichIcon;	// 0/1 which HICON to use
	BOOL		m_bShutdown;	// OK to terminate LogServer
	BOOL		m_bShowTrayNotifications;	// display info in main window

	CFont m_Font;
	CBrush m_BrushBk;

	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg LRESULT OnTrayNotification(WPARAM wp, LPARAM lp);
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewClear();
	afx_msg void OnUpdateViewClear(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnAppOpen();
	afx_msg void OnAppSuspend();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnAcceptRequestForIntervention(UINT wParam,LONG lParam);
	afx_msg void OnAcceptRequestForDicomPrinter(UINT wParam,LONG lParam);
	afx_msg void OnMenuOptions();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// 通信类对象
	CComSocket_SysDiagnosis*		m_pComSocket_SysDiagnosis;

	void InitComObjects();
	void ReleaseComObjects();
		
	// 消息类型
	ENUM_TYPE_OF_PACKET m_nTypeOfPacket;
	// 分发消息到相应设备实体
	void DispatchPacket( PVOID pData, CWnd* pCallingWnd );
	
	// 日志文件存取
	CLogFileAccess* m_pLogFileAccess;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__9ED70A69_C975_4F20_9D4E_B2877E3575D0__INCLUDED_)
