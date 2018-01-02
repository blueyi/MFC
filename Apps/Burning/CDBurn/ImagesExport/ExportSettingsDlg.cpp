// ExportSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExportSettingsDlg.h"
#include "../BIGLobals/ConfigManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString strFileType[] = {"DCM",
						 "BMP",
						 /*"IMG"*/};

/////////////////////////////////////////////////////////////////////////////
// CExportSettingsDlg dialog


CExportSettingsDlg::CExportSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExportSettingsDlg)
	m_strFileType = _T("");
	m_strFilePathName = _T("");
	m_bPrintMethod=FALSE;//0 default,1 bu folder
	//}}AFX_DATA_INIT
}


void CExportSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportSettingsDlg)
	DDX_CBString(pDX, IDC_COMBO1, m_strFileType);
	DDX_Text(pDX, IDC_EDIT1, m_strFilePathName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExportSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CExportSettingsDlg)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT_SAVE, OnRadioDefaultSave)
	ON_BN_CLICKED(IDC_RADIO_BY_FOLDER, OnRadioSaveByFolder)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportSettingsDlg message handlers

BOOL CExportSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int nTotal = sizeof(strFileType)/sizeof(CString);
	CComboBox  *pBox = (CComboBox  *)GetDlgItem(IDC_COMBO1);
	for(int i = 0;i < nTotal; i++)
	{
		pBox->AddString(strFileType[i]);
	}
	m_strFileType = strFileType[0];
	//////////////////////////////////////////////////////////////////////////
	//初始化系统路径
    CString TmpDicomPath;
	CString szDicom= CConfigManager::GetHandle().GetHomePath();
	if(szDicom.Right(2)=="\\\\")
	{
		szDicom=szDicom.Left(szDicom.GetLength()-1);

	}
	TmpDicomPath.Format("%sdicom\\" , szDicom);
	m_strFilePathName = TmpDicomPath; 
	////////////////////////////////////////////////////////////////////////////
	//add chenshi 06-09-04
	CheckRadioButton(IDC_RADIO_DEFAULT_SAVE,IDC_RADIO_BY_FOLDER,IDC_RADIO_DEFAULT_SAVE);
	//end chenshi
	UpdateData(FALSE);

	return TRUE;
}

void CExportSettingsDlg::OnButton2() 
{
	CDialog::OnOK();
}

void CExportSettingsDlg::OnButton3() 
{
	CDialog::OnCancel();	
}

void CExportSettingsDlg::OnButton1() 
{
	UpdateData(TRUE);
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory( &bi,sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.pszDisplayName = name;
	bi.lpszTitle = "选择导出文件的路径：";
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST idl = SHBrowseForFolder( &bi );
   	
	if (idl == NULL )
		return;
	if (!SHGetPathFromIDList(idl,m_strFilePathName.GetBuffer(MAX_PATH)))
	{
		DWORD d = GetLastError();
		return;
	} 
	m_strFilePathName.ReleaseBuffer();
	UpdateData(FALSE);
}
void CExportSettingsDlg::OnRadioDefaultSave()
{
	this->m_bPrintMethod=FALSE;

}
void CExportSettingsDlg::OnRadioSaveByFolder()
{
	this->m_bPrintMethod=TRUE;
}
