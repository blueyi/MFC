// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LogServer.h"
#include "OptionsDlg.h"
#include "DataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_sWorkDirectory = _T("");
	m_bScanParams = FALSE;
	m_bMagnetTemp = FALSE;
	m_bRfAmp = FALSE;
	m_bGradientAmp = FALSE;
	m_bGradientPower = FALSE;
	m_bShimAmp = FALSE;
	m_bSpectrometer = FALSE;
	m_bSIU = FALSE;
	m_bGating = FALSE;
	m_bPatientTable = FALSE;
	m_bInformation = FALSE;
	m_iPermittedLogFileNum = 0;
	//}}AFX_DATA_INIT
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Text(pDX, IDC_EDIT_WORK_DIRECTORY, m_sWorkDirectory);
	DDX_Check(pDX, IDC_CHECK1, m_bScanParams);
	DDX_Check(pDX, IDC_CHECK2, m_bMagnetTemp);
	DDX_Check(pDX, IDC_CHECK3, m_bRfAmp);
	DDX_Check(pDX, IDC_CHECK4, m_bGradientAmp);
	DDX_Check(pDX, IDC_CHECK5, m_bGradientPower);
	DDX_Check(pDX, IDC_CHECK6, m_bShimAmp);
	DDX_Check(pDX, IDC_CHECK7, m_bSpectrometer);
	DDX_Check(pDX, IDC_CHECK8, m_bSIU);
	DDX_Check(pDX, IDC_CHECK9, m_bGating);
	DDX_Check(pDX, IDC_CHECK10, m_bPatientTable);
	DDX_Check(pDX, IDC_CHECK11, m_bInformation);
	DDX_Text(pDX, IDC_EDIT_PERMITTED_LOG_FILE_NUM, m_iPermittedLogFileNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_BTN_WORK_DIRECTORY, OnBtnWorkDirectory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::OnBtnWorkDirectory() 
{
	CString str, sWorkDirectory;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.lpszTitle="选择工作目录";
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)
	{
		return;
	}
	
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	
	int nSize = strlen(str);// add "\" on the filepath
	if ( nSize > 3)
	{
		sWorkDirectory = str.GetBuffer(str.GetLength());
		sWorkDirectory +="\\";
	}
	else
	{
		sWorkDirectory = str.GetBuffer(str.GetLength());
	}

	UpdateData( TRUE );
	m_sWorkDirectory = sWorkDirectory;
	UpdateData( FALSE );

	CDataManager::GetHandle().m_sWorkDirectory = sWorkDirectory;
}

void COptionsDlg::OnOK() 
{
	UpdateData( TRUE );

	// 从Dlg各项获取选项值
	CDataManager::GetHandle().m_sWorkDirectory = m_sWorkDirectory;
	CDataManager::GetHandle().m_iPermittedLogFileNum = m_iPermittedLogFileNum;

	CDataManager::GetHandle().m_mSaveRecordFlag["SW02"] = m_bScanParams;
	CDataManager::GetHandle().m_mSaveRecordFlag["MS01"] = m_bMagnetTemp;
	CDataManager::GetHandle().m_mSaveRecordFlag["RS01"] = m_bRfAmp;
	CDataManager::GetHandle().m_mSaveRecordFlag["GS01"] = m_bGradientAmp;
	CDataManager::GetHandle().m_mSaveRecordFlag["GS02"] = m_bGradientPower;
	CDataManager::GetHandle().m_mSaveRecordFlag["GS03"] = m_bShimAmp;
	CDataManager::GetHandle().m_mSaveRecordFlag["SP01"] = m_bSpectrometer;
	CDataManager::GetHandle().m_mSaveRecordFlag["OS01"] = m_bSIU;
	CDataManager::GetHandle().m_mSaveRecordFlag["OS02"] = m_bGating;
	CDataManager::GetHandle().m_mSaveRecordFlag["OS03"] = m_bPatientTable;
	CDataManager::GetHandle().m_mSaveRecordFlag["I000"] = m_bInformation;
	
	// 将选项值保存到配置文件
	CDataManager::GetHandle().WriteOptionsToFile();

	UpdateData( FALSE );

	
	// 删除冗余的Log文件
	CDataManager::GetHandle().FindLogFiles();
	CDataManager::GetHandle().DeleteRedundanceFiles();
	
	CDialog::OnOK();
}

BOOL COptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetOptionsToDlgItems();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDlg::SetOptionsToDlgItems()
{
	UpdateData( TRUE );

	m_sWorkDirectory = CDataManager::GetHandle().m_sWorkDirectory;
	m_iPermittedLogFileNum = CDataManager::GetHandle().m_iPermittedLogFileNum;

	m_bScanParams = CDataManager::GetHandle().m_mSaveRecordFlag["SW02"];
	m_bMagnetTemp = CDataManager::GetHandle().m_mSaveRecordFlag["MS01"];
	m_bRfAmp = CDataManager::GetHandle().m_mSaveRecordFlag["RS01"];
	m_bGradientAmp = CDataManager::GetHandle().m_mSaveRecordFlag["GS01"];
	m_bGradientPower = CDataManager::GetHandle().m_mSaveRecordFlag["GS02"];
	m_bShimAmp = CDataManager::GetHandle().m_mSaveRecordFlag["GS03"];
	m_bSpectrometer = CDataManager::GetHandle().m_mSaveRecordFlag["SP01"];
	m_bSIU = CDataManager::GetHandle().m_mSaveRecordFlag["OS01"];
	m_bGating = CDataManager::GetHandle().m_mSaveRecordFlag["OS02"];
	m_bPatientTable = CDataManager::GetHandle().m_mSaveRecordFlag["OS03"];
	m_bInformation = CDataManager::GetHandle().m_mSaveRecordFlag["I000"];
	
	UpdateData( FALSE );
}
