// MRI_DataBackupDlg.h : header file
//

#if !defined(AFX_MRI_DATABACKUPDLG_H__A68F6250_295D_439C_972D_5501F4EAD515__INCLUDED_)
#define AFX_MRI_DATABACKUPDLG_H__A68F6250_295D_439C_972D_5501F4EAD515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include"vector"
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CMRI_DataBackupDlg dialog

class CMRI_DataBackupDlg : public CDialog
{
// Construction
public:
	CMRI_DataBackupDlg(CWnd* pParent = NULL);	// standard constructor
	~CMRI_DataBackupDlg();

// Dialog Data
	//{{AFX_DATA(CMRI_DataBackupDlg)
	enum { IDD = IDD_DIALOG_CD_PARAM };
	CEdit	m_sCDName;
	CComboBox	m_Combo_CDSpeed;
	CProgressCtrl	m_Pro_Burn;
	CListBox	m_List_Info;
	CButton	m_btnCancel;
	CButton	m_Btn_Burn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRI_DataBackupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMRI_DataBackupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBurn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditchangeComboSpeed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CWnd*m_pParentPatientWnd;
	long m_nSelStudySize;
	CString m_sBurnPath;
	
	/*********zyh add 2008.2.27*********/
	void * m_pExportBlock;
	BOOL m_bExport;		//是否已经导出到文件
// 	CString GetInstallDirectory();
	/**********************************************/
	int m_nProParam;
	
	int m_BurnByte;
	int m_BurnTime;
	int m_BurnParam;
	std::vector<CString> m_vStudyID;
	CString m_LocalName;
	CString m_sDataName;
	long m_CurFolderSize;//统计文件夹大小
public:
	bool OnBurnDoingProcess();
 	bool CreateIMGFileSystemForBurn(CString csDirPath, void* pStg1/*IStorage *pStg*/);
 	void PackDCMView(char *szPath, void *pStorage);	//zyh add 2008.2.27 打包dicomview软件
// 	long GetFolderSize(CString sFolderPath);
// 	void CalculateFolderSize(CString csDirPath);
 	CString CheckForFreeDisc();
// 	//zyh add param bPackDb,是否打包数据库， 2008.2.27
 	bool MultiFolderToImage(CString sLocalPath, CString sDatabaseName, std::vector<CString> vStudyId, void* pStorage1/*IStorage*pStorage*/, BOOL bPackDb = TRUE);
	
	
	
public:
// 	/** [SHCH:28-12-2007 TITLE:XABW/CX-31-11-0097/PUR:确定光驱内存在磁盘] **/
 	CString GetCD_ROM_DISK_INFO();
// 	/** [SHCH:28-12-2007 TITLE:XABW/CX-31-11-0097/PUR:确定光驱内存在磁盘] **/
// 	
// 	
 	BOOL CheckDiskAlready();
// 	void SetLangCharRes();
 	int m_vCDSpeed;
 	bool DisplayRecordDiskInfo();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRI_DATABACKUPDLG_H__A68F6250_295D_439C_972D_5501F4EAD515__INCLUDED_)
