// PPDlg.h : header file
//

#pragma once
#include <afxcmn.h>
#include <afxwin.h>
#include <afxcoll.h>
#include "WifiPeek.h"

#include "CustomTabCtrl.h"
#include "ColoredDlg.h"
#include "CustomButton.h"

#include "ScannerDlg.h"
#include "OptionsDlg.h"

// CPPDlg dialog
class CPPDlg : public CColoredDlg
{
// Construction
public:
	CPPDlg(CWnd* pParent = NULL);	// standard constructor
	~CPPDlg();
// Dialog Data
	enum { IDD = IDD_PEEKPOCKET_DLG };
	int m_iRefreshRate;					//refresh speed
	DisplayInfoMap m_data;				//map of APs, keyed by MAC add

	CCustomTabContainer m_tab;			//the tab control (a container)

	CRITICAL_SECTION m_DataLock;		//access to data will be protected with a CS object
	
	CScannerDlg *m_pScannerDlg;			//child dlg
	COptionsDlg *m_pOptionsDlg;			//child dlg

	//options
	bool m_bSoundOff, m_bHideSecure, m_bHidePeer;

	CString SplitString(CString strIn, TCHAR cSplitAt, int &iPos);	//Tokenize replacement for old MFC versions (eVC4)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void ProcessInfo(struct BSSIDInfo *pInfo, DWORD dwNum);

	CString m_strCurrentAdapter;
	CWifiPeek m_wp;
	bool m_bRunning;		//suspend/resume

	CCustomButton m_btnSusRes;
	CCustomButton m_btnExit;
	CStatic m_apicon;

	DWORD m_dwTickCounter;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	
private:
	afx_msg void OnBnClickedExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedSuspendResume();
	afx_msg void OnCbnSelchangeAdaptersCombo();
};
