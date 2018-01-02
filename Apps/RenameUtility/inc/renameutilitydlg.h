// RenameUtilityDlg.h : header file
//
#pragma once
#include "afxcmn.h"
#include "SkinProgress.h"
#include "afxwin.h"
#include "bulkrenameclass.h"
#include "PPTooltip.h"

#define WM_USER_THREAD_FINISHED WM_USER + 0x100

// CRenameUtilityDlg dialog
class CRenameUtilityDlg : public CDialog
{
// Construction
private:
	static volatile int m_nPercent;
	static CString		m_strStatus;
	static BOOL			m_bCancelled;
public:
	CRenameUtilityDlg(CWnd *pParent = NULL);			// standard constructor
	static BOOL		m_bResult;
	static double	m_bTotalFileCount;

	// Dialog Data
	enum
	{
		IDD = IDD_RENAMEUTILITY_DIALOG
	};
	BOOL RecChangeCase(CString strPath, CRenameOption :: enCaseType nCaseType, BOOL bIncDir = FALSE);
protected:
	virtual void	DoDataExchange(CDataExchange *pDX); // DDX/DDV support
private:
	void	AddToolTips();

	//BOOL RenameOP(CString strScrFileName , int nCaseType )   ;

// Implementation
protected:
	HICON			m_hIcon;

	// Generated message map functions
	virtual BOOL	OnInitDialog();
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LONG	OnThreadFinished(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnBnClickedButRootfolderDir();
protected:
	CString			m_strDirectory;
	CSkinProgress	*m_poSkinProgress;	// The object within
	CWnd			*poProgress;
	CWnd			*poProgressText;
public:
	afx_msg void			OnBnClickedButUppercase();
	static BOOL CALLBACK	CancelProc(LPCTSTR strStatus, int nPercent);

	BOOL					bCheckFolderRename;

	// //Reflect if rename to Lowercase , Uppercase or Titel Case
	int						nNameState;

	//CProgressCtrl RenameProgressBar;
	afx_msg void			OnTimer(UINT nIDEvent);
	CStatic					m_CEProgress;
	CStatic					m_cSprogresstext;
	afx_msg void			OnBnClickedCheckFolder();
	CString					c_strFindWhat;
	CString					c_strReplaceWith;
	CString					c_strAddSuffix;
	afx_msg void			OnBnClickedButReplaceRename();
	afx_msg void			OnBnClickedButSuffix();
	int						cv_Suffix;

	//CPP Tooltips Object
	CPPToolTip				m_tooltip;
	virtual BOOL			PreTranslateMessage(MSG *pMsg);

	// //Radio button Var for Replace name
	int						cv_incext;
	afx_msg void			OnBnClickedRadRmvTxt();
	afx_msg void			OnBnClickedRadExclExt();
	afx_msg void			OnBnClickedRadIncext();
	void					DisableUI();
	void					EnableUI();
};
