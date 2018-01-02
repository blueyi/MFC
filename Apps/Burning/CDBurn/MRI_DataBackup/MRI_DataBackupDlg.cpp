// MRI_DataBackupDlg.cpp : implementation file
//
#pragma once 

#include "stdafx.h"
#include "atlbase.h"
#include "MRI_DataBackup.h"
#include "MRI_DataBackupDlg.h"
#include "DataBackupInterface.h"
#include "ConfigManager.h"
#include "imapi.h"
#include "CIProgressEvent.h"
#include "BIMessages.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _IMAGE_EVENT_ 49997
#define _BURN_EVENT_ 49998
#define _ADD_DATA_  49989

UINT MyThreadBurnProc( LPVOID pParam );

CMRI_DataBackupDlg *pMainDlg=NULL;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMRI_DataBackupDlg dialog

CMRI_DataBackupDlg::CMRI_DataBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMRI_DataBackupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMRI_DataBackupDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMRI_DataBackupDlg::~CMRI_DataBackupDlg()
{
	if (pMainDlg)
	{
		delete pMainDlg;
		pMainDlg=NULL;
	}
}

void CMRI_DataBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMRI_DataBackupDlg)
	DDX_Control(pDX, IDC_COMBO_CDNAME, m_sCDName);
	DDX_Control(pDX, IDC_COMBO_SPEED, m_Combo_CDSpeed);
	DDX_Control(pDX, IDC_PROGRESS_BURN, m_Pro_Burn);
	DDX_Control(pDX, IDC_LIST_INFO, m_List_Info);
	DDX_Control(pDX, IDOK, m_btnCancel);
	DDX_Control(pDX, ID_BTN_BURN, m_Btn_Burn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMRI_DataBackupDlg, CDialog)
	//{{AFX_MSG_MAP(CMRI_DataBackupDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_BURN, OnBtnBurn)
	ON_WM_TIMER()
	ON_CBN_EDITCHANGE(IDC_COMBO_SPEED, OnEditchangeComboSpeed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMRI_DataBackupDlg message handlers

BOOL CMRI_DataBackupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Combo_CDSpeed.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMRI_DataBackupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMRI_DataBackupDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMRI_DataBackupDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMRI_DataBackupDlg::OnBtnBurn() 
{
	// TODO: Add your control notification handler code here
	pMainDlg=this;
// 	HWND hWnd=GetSafeHwnd();
// 	AfxBeginThread(MyThreadBurnProc,hWnd);
	OnBurnDoingProcess();
}

UINT MyThreadBurnProc( LPVOID pParam )
{	
	if (!pMainDlg)
		return 0;
 
	pMainDlg->OnBurnDoingProcess();
	
    return 0;   // thread completed successfully
}

bool CMRI_DataBackupDlg::OnBurnDoingProcess()
{
	m_Btn_Burn.EnableWindow(FALSE);
	m_btnCancel.EnableWindow(FALSE);
	/*********zyh add 2008.2.27*********/
	if((0 == m_sDataName.Compare("0"))&&(FALSE == m_bExport))
	{
		//导出dcm文件
		m_List_Info.AddString("Covert to DICOM format...");
		CDataExportInterface pExortDataTask;
		pExortDataTask.ExportSelectStudy2(m_pExportBlock, &m_Pro_Burn);	
		m_List_Info.AddString("Convert to DICOM format  complete!");
		m_bExport = TRUE;
		
	}
	/**********************************************/
	BOOL nRet=CheckDiskAlready();
	if(nRet==FALSE)
	{
		//ZYH DEL 2008.1.17
		//CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CONFIRM_DISK")/*"Please confirm the disk into cd-rom!"*/,MB_OK);
		CLang::GetHandle().ShowMessage("Please confirm the disk into cd-rom!",MB_OK);
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		return FALSE;
	}
	else if(nRet & 2)
	{	
		if(0 == m_sDataName.Compare("0"))
		{
			CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CD_HAVE_DATA_RETURN"));
			m_Btn_Burn.EnableWindow(TRUE);
			m_btnCancel.EnableWindow(TRUE);
			return FALSE;
		}	
		
		BOOL nResVal=CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CD_HAVE_DATA")/*"Please confirm the disk into cd-rom!"*/,MB_YESNO);
		//ZYH DEL 2008.1.17
		if(nResVal==7)
		{
			m_Btn_Burn.EnableWindow(TRUE);
			m_btnCancel.EnableWindow(TRUE);
			return FALSE;
		}
 	}
	else if(nRet & 4)
	{
		BOOL nResVal=CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_DATA_TOO_BIG")/*"Please confirm the disk into cd-rom!"*/,MB_YESNO);
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		return FALSE;
	}

	//烧录过程
	HRESULT hr;
	//IDiscMaster* pDiskMaster;
	IStorage * pStorage;
	m_Pro_Burn.SetRange(0, 100);
	m_Pro_Burn.SetPos(0);
	//	hr = CoInitialize(NULL);
	m_List_Info.AddString(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CREATE_IMAGE")/*"Start creating Image!"*/);
	m_nProParam=0;
	SetTimer(_IMAGE_EVENT_,2000,NULL);
	//寻找磁盘空间
	long dSize=this->m_nSelStudySize/*GetFolderSize(m_sBurnPath)*/;
	m_BurnTime=dSize/m_BurnByte;
	if(dSize>_MAX_CD_)
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_DATA_TOO_BIG")/*"Folder size too big!\nYou can't Burn it !"*/);
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		return FALSE;
	}
	/////////////////////////////////////////////
	/** [SHCH:28-12-2007 TITLE:XABW/CX-31-11-0097/PUR:确定光驱内存在磁盘] **/
	CString sStory=CheckForFreeDisc();
	WCHAR wszDomain[256];
	if(sStory=="")
	{
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		return FALSE;
	}
	else
	{
		if(sStory.Right(1)!="\\")
			sStory+="\\";
		int t=GetTickCount();
		CString tName;
		tName.Format("%d",t);
		sStory+="MyImage"+tName;
		
		MultiByteToWideChar( CP_ACP, 0, sStory,
			sStory.GetLength()+1, wszDomain, sizeof(wszDomain)/sizeof(wszDomain[0]) );
		
	}
	///////////////////////////////////////////
	hr = StgCreateStorageEx(/* L"D:\\MyImage"*/wszDomain,
							STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE,
							STGFMT_STORAGE,
							0, NULL, NULL,
							IID_IStorage,
							reinterpret_cast<void**>(&pStorage) );
	if( FAILED(hr) )
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_INIT_STORGE")/*"Can't Init Storage Container!"*/);
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;		
	}

	if(!m_sBurnPath)
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_PATH_NULL")/*"Path can't be NULL!"*/);
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	/////////////////////////////
	//std::vector<CString> m_vStudyID;
	//	CString m_LocalName;
	//	CString m_sDataName;
	//BUG
	//add a directory
	/////////////////////////////////////////////////////

	CString szFolderName = "";	
	
	IStorage *tStore;
	
	CTime lpszString = CTime::GetCurrentTime();
	if(0 != m_sDataName.Compare("0"))
	{
		szFolderName.Format("%04d-%02d-%02d-%02d-%02d-%02d",lpszString.GetYear(),lpszString.GetMonth(),lpszString.GetDay(),lpszString.GetHour(),lpszString.GetMinute(),lpszString.GetSecond());
		int iStr=szFolderName.GetLength();
		int s=-1;
		wchar_t *pwc= (wchar_t *)malloc((iStr+1)* sizeof( wchar_t ));
		s= mbstowcs( pwc, szFolderName, iStr );
		pwc[iStr]=0;
		hr=pStorage->CreateStorage(pwc,STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE,0,0,&tStore);

		/////////////////////////////////////////////////////	
		m_sBurnPath="d:\\1";//自定义刻盘的目录
		m_sDataName="Database.mdb";//需要的刻盘的文件名
		MultiFolderToImage(m_sBurnPath,m_sDataName,m_vStudyID,tStore);
		tStore->Release();
	
		free(pwc);
	}
	else
		MultiFolderToImage(m_sBurnPath,m_sDataName,m_vStudyID, pStorage, FALSE);

	//CreateIMGFileSystemForBurn(m_sBurnPath,pStorage);

	IDiscMaster* pDiskMaster;
	hr = CoCreateInstance(CLSID_MSDiscMasterObj, NULL,CLSCTX_LOCAL_SERVER, 
						  IID_IDiscMaster, (void**)&pDiskMaster);
	if(hr==0)
	{
		m_List_Info.AddString("Create Image Complete!");
	}
	else
	{
		m_List_Info.AddString("Create Image Failed!");
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	//m_List_Info.AddString("Create Image Complete!");
	m_Pro_Burn.SetPos(25);
	KillTimer(_IMAGE_EVENT_);
	/////////////////////////////////////////////////////////////////	
	hr = pDiskMaster->Open();
	if(hr==0)
	{
		m_List_Info.AddString("Disk Master Open!");
	}
	else
	{
		m_List_Info.AddString("Disk Master Open Failed!");
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	//m_List_Info.AddString("Disk Master Open!");
	m_Pro_Burn.SetPos(27);
	
	IJolietDiscMaster* joilet;
	hr = pDiskMaster->SetActiveDiscMasterFormat(IID_IJolietDiscMaster,(void**)&joilet );
	if(hr==0)
	{
		m_List_Info.AddString("Set Active Disc Master Format!");
	}
	else
	{
		m_List_Info.AddString("Set Active Disc Master Format Failed!");
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	//m_List_Info.AddString("Set Active Disc Master Format!");
	m_Pro_Burn.SetPos(31);
	
	
	IEnumDiscRecorders* recordersEnum;
	hr = pDiskMaster->EnumDiscRecorders(&recordersEnum);
	if(hr==0)
	{
		//m_List_Info.AddString("EnumDisc Recorders!");
	}
	else
	{
		//m_List_Info.AddString("EnumDisc Recorders Failed!");
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	//m_List_Info.AddString("EnumDisc Recorders!");
	m_Pro_Burn.SetPos(34);
	
	
	ULONG num;
	IDiscRecorder* recorder;
	hr = recordersEnum->Next(1,&recorder,&num);
	if(recorder==NULL)
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_NO_WRITER")/*"Can't Find CD-RW On Your System!"*/);
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
		
	}
	if(hr==0)
	{
		m_List_Info.AddString("EnumDisc Recorders!");
	}
	else
	{
		m_List_Info.AddString("EnumDisc Recorders Failed!");
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}

	
	hr = pDiskMaster->SetActiveDiscRecorder(recorder);
	if(hr==0)
	{
		m_List_Info.AddString("Set Active Disc Recorder!");
	}
	else
	{
		m_List_Info.AddString("Set Active Disc Recorder Failed!");
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_INSERT_DISK")/*"Please insert recordable disc! \nWriting process error"*/);
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	//m_List_Info.AddString("Set Active Disc Recorder!");
	m_Pro_Burn.SetPos(36);
	////////////////////////////////////////////////////
	//这个地方加入中间过程的返回	
	
	IDiscProgressEvents *pEventsObject = new IDiscProgressEvents();
	IDiscMasterProgressEvents  * pEvents;	
	
	hr = pEventsObject->QueryInterface(IID_IDiscMasterProgressEvents,(void **) &pEvents);	
	
	if(hr==0)
	{
		UINT_PTR pnCookie;
		//memset(&pnCookie,0,sizeof(pnCookie));
		hr = pDiskMaster-> ProgressAdvise( pEventsObject, &pnCookie);
		//		m_List_Info.AddString("pDiskMaster-> ProgressAdvise");
		//		
	}
	m_Pro_Burn.SetPos(40);
	m_nProParam=40;
	SetTimer(_ADD_DATA_,2000,NULL);	
	
	hr = joilet->AddData(pStorage,1); 
	m_Pro_Burn.SetPos(60);
	KillTimer(_ADD_DATA_);
	if(hr==0)
	{
		m_List_Info.AddString("AddData!");
	}
	else
	{
		m_List_Info.AddString("AddData Failed!");
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	//m_List_Info.AddString("AddData");
	///////////////////////////////////
	m_BurnParam=0;
	SetTimer(_BURN_EVENT_,1000,NULL);
	hr = pDiskMaster->RecordDisc(FALSE,TRUE);
	if(hr==0)
	{
		m_List_Info.AddString("Record Disk!");
	}
	else
	{
		m_List_Info.AddString("Record Disk Failed!");
		m_Btn_Burn.EnableWindow(TRUE);
		m_btnCancel.EnableWindow(TRUE);
		DeleteFile(sStory);
		return FALSE;
	}
	KillTimer(_BURN_EVENT_);
	
	pStorage->Release();
	//pDiskMaster->Close();
	m_List_Info.AddString("Data burn complete!");
	CString sInfo;
	sInfo.Format("Total Byte %d",dSize);
	m_List_Info.AddString(sInfo);
	sInfo.Format("Total Time %d Seconds",m_BurnTime);
	m_List_Info.AddString(sInfo);
	///////////////////////////////////////
	sInfo="Burning Process complete!";
	m_List_Info.AddString(sInfo);

	/////////////////////////////////
	m_Pro_Burn.SetPos(100);
	recorder->Release();
	pDiskMaster->Release();
	CoUninitialize();
	//if(0 == m_sDataName.Compare("0"))
	DeleteFile(szFolderName);
	/** [SHCH:4-1-2008 TITLE:XABW/CX-31-11-0143/PUR:将更新移出] **/
//	if((m_pParentPatientWnd!=NULL)&&(0 != m_sDataName.Compare("0")))
//		m_pParentPatientWnd->SendMessage(WM_NOTIFIED_BACKUP);
		/** [SHCH:4-1-2008 TITLE:XABW/CX-31-11-0143/PUR:将更新移出] **/
	m_Btn_Burn.EnableWindow(TRUE);
	m_btnCancel.EnableWindow(TRUE);
	DeleteFile(sStory);
	return 0;
	
}

CString CMRI_DataBackupDlg::CheckForFreeDisc()
{
	ULARGE_INTEGER h1;
	ULARGE_INTEGER h2;
	ULARGE_INTEGER h3;
	CString sDiscName="c:\\";
	
	GetDiskFreeSpaceEx(sDiscName,&h1,&h2,&h3);
	//long dCopySize=GetFolderSize(sSourcePath);
	long dDisc=h3.QuadPart;
	if(dDisc>_MAX_CD_|| h3.u.HighPart>0)
	{
		
		return sDiscName;
	}
	sDiscName="d:\\";
	
	GetDiskFreeSpaceEx(sDiscName,&h1,&h2,&h3);
	//long dCopySize=GetFolderSize(sSourcePath);
	dDisc=h3.QuadPart;
	if(dDisc>_MAX_CD_|| h3.u.HighPart>0)
	{
		
		return sDiscName;
	}
	///////////////////////////////
	sDiscName="e:\\";
	
	GetDiskFreeSpaceEx(sDiscName,&h1,&h2,&h3);
	//long dCopySize=GetFolderSize(sSourcePath);
	dDisc=h3.QuadPart;
	if(dDisc>_MAX_CD_|| h3.u.HighPart>0)
	{
		
		return sDiscName;
	}
	////////////////////////////////////
	sDiscName="f:\\";
	
	GetDiskFreeSpaceEx(sDiscName,&h1,&h2,&h3);
	//long dCopySize=GetFolderSize(sSourcePath);
	dDisc=h3.QuadPart;
	if(dDisc>_MAX_CD_|| h3.u.HighPart>0)
	{
		
		return sDiscName;
	}
	sDiscName="g:\\";
	
	GetDiskFreeSpaceEx(sDiscName,&h1,&h2,&h3);
	//long dCopySize=GetFolderSize(sSourcePath);
	dDisc=h3.QuadPart;
	if(dDisc>_MAX_CD_|| h3.u.HighPart>0)
	{
		
		return sDiscName;
	}
	CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_NO_DISK")/*"You Don't have suitable free disk!"*/);
	return "";	
}

bool CMRI_DataBackupDlg::MultiFolderToImage(CString sLocalPath, CString sDatabaseName, std::vector<CString> vStudyId,void* pStorage1/*IStorage*pStorage*/, BOOL bPackDb /* = TRUE*/)
{
	IStorage* pStorage = (IStorage*)pStorage1;
	
	HRESULT hr;
	//IDiscMaster* pDiskMaster;
	if(sLocalPath.Right(1)!="\\")
	{
		sLocalPath+="\\";
	}
	
	IStorage /** pStorage,*/*dstorage;
	IStream *dStream;
	//	hr = CoInitialize(NULL);
	//m_List_Info.AddString("Start creating Image!");
	
	int dCount=vStudyId.size();
	int i=0;
	while(i<dCount)
	{
		CString szStudyName=vStudyId.back();
		vStudyId.pop_back();
		int iStr=szStudyName.GetLength();
		int s=-1;
		wchar_t *pwc= (wchar_t *)malloc((iStr+1)* sizeof( wchar_t ));
		s= mbstowcs( pwc, szStudyName, iStr );
		pwc[iStr]=0;
		hr=pStorage->CreateStorage(pwc,STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE,0,0,&dstorage);
		if( FAILED(hr) )
		{
			CString szFailMsg=CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_FAIL");
			CLang::GetHandle().ShowMessage(szStudyName+/*"fail"*/szFailMsg);
			
		}
		CreateIMGFileSystemForBurn(sLocalPath+szStudyName,(void*)dstorage);
		dstorage->Release();
		i++;
		free(pwc);
	}
	if(bPackDb)
	{
		//打包数据库
		int iStr=sDatabaseName.GetLength();
		int s=-1;
		wchar_t *pwc= (wchar_t *)malloc((iStr+1)* sizeof( wchar_t ));
		s= mbstowcs( pwc, sDatabaseName, iStr );
		pwc[iStr]=0;
		//hr=pStorage->CreateStorage(L"tst",STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE,0,0,&dstorage);
		hr=pStorage->CreateStream(pwc,STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE,0,0,&dStream);
		if( FAILED(hr) )
		{
			//AfxMessageBox((CString)wfd.cFileName+"fail");
			/*throw L"Failed StgCreateStorageEx";*/  
		}
		
		CFileException e;
		CString dName("Database.mdb");
		CopyFile(sLocalPath+sDatabaseName,sLocalPath+dName,FALSE);
		CFile file(sLocalPath+dName/*+sDatabaseName*/,CFile::modeRead | CFile::shareExclusive);
		
		void * buf = new char[100*1024*1024];
		UINT read= file.Read(buf,100*1024*1024);
		if (read > 0)
		{
			ULONG written;
			dStream->Write(buf,read,&written);
		}else
		{
			exit(0);
		}
		free(pwc);
		free(buf);
		dStream->Release();
	}
	else
	{
		//打包dicom浏览器软件
		PackDCMView(sLocalPath.GetBuffer(sLocalPath.GetLength()), pStorage);
	}
	
	/*free(pwc);*/
	/////////////////////////////////////////////////
	
	//AfxMessageBox("complete");
	if(hr==0)
		return TRUE;
	else
		return FALSE;
	
}

//这个函数的独立性不好，但是目前只能这样做，因为递归很大的文件系统传递文件系统效果会很差
//建议加大内存
bool CMRI_DataBackupDlg::CreateIMGFileSystemForBurn(CString csDirPath,void* pStg1/*IStorage *pStg*/)
{
	IStorage *pStg = (IStorage*)pStg1;

	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString csText = _T("");
	HRESULT hr;
	IStream* pStream;
	IStorage *dstorage=0;
	
	// Check if the last char is a back-slash
	// (If not, put it there)
	if (csDirPath.Right(1) != "\\")
		csDirPath += _T("\\");
	
	// set the variable and add an astrix for 
	// the beginning of the directory search.
	csText = csDirPath + _T("*");
	
	// Iterate through dirs
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// Check if "." or "..", if not...
			// Check if its a directory.
			if ((strcmp(wfd.cFileName,_T("."))) && (strcmp(wfd.cFileName,_T(".."))) && 
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				
				CString csDirIn = _T("");
				
				// Set to the directory found.
				csDirIn = csDirPath + wfd.cFileName;
				//新建IStorage
				
				int iStr=strlen(wfd.cFileName);
				int i=-1;
				wchar_t *pwc= (wchar_t *)malloc((iStr+1)* sizeof( wchar_t ));
				i = mbstowcs( pwc, wfd.cFileName, iStr );
				pwc[iStr]=0;
				hr=pStg->CreateStorage(pwc,STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE,0,0,&dstorage);
				if( FAILED(hr) )
				{
					CString szFailMsg=CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_FAIL");
					CLang::GetHandle().ShowMessage((CString)wfd.cFileName+szFailMsg);
					/*throw L"Failed StgCreateStorageEx";*/  
				}
				free(pwc);
				CreateIMGFileSystemForBurn(csDirIn,(void*)dstorage);
				dstorage->Release();
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
	}

	csText = csDirPath + _T("*.*");
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// If NOT a directory...
			if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				
				CString csIn = _T("");
				CString csOut = _T("");
				
				// Set to the file found.
				csIn = csDirPath + wfd.cFileName;
				int iStr=strlen(wfd.cFileName);
				int i=-1;
				wchar_t *pwc= (wchar_t *)malloc((iStr+1)* sizeof( wchar_t ));
				i = mbstowcs( pwc, wfd.cFileName, iStr );
				pwc[iStr]=0;
				
				

				hr=pStg->CreateStream(pwc,STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE,0,0,&pStream);
				if( FAILED(hr) )
				{
					CString szFailMsg=CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_FAIL");
					CLang::GetHandle().ShowMessage((CString)wfd.cFileName+/*"fail"*/szFailMsg);
					/*throw L"Failed StgCreateStorageEx";*/  
				}
				CFile file(csIn,CFile::modeReadWrite | CFile::shareExclusive);
				
				void * buf = new char[10*1024*1024];
				UINT read= file.Read(buf,10*1024*1024);
				if (read > 0)
				{
					ULONG written;
					pStream->Write(buf,read,&written);
				}else
				{
					exit(0);
				}
				free(pwc);
				free(buf);
				pStream->Release();
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
		
	}
	//pStream->Release();
	//dstorage->Release();	
	return TRUE;
}

void CMRI_DataBackupDlg::PackDCMView(char *szPath, void *pStorage)
{
	IStorage *pSt = (IStorage*)pStorage;
	char szTmp[MAX_PATH];
	sprintf(szTmp, "%s*.*", szPath);
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(szTmp, &wfd);
	IStream * pStream;
	
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do
		{
			if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) 
				continue;
			
			CString csIn = _T("");
			CString csOut = _T("");
			
			// Set to the file found.
			csIn = szPath;
			csIn+= wfd.cFileName;
			int iStr=strlen(wfd.cFileName);
			int i=-1;
			wchar_t *pwc= (wchar_t *)malloc((iStr+1)* sizeof( wchar_t ));
			i = mbstowcs( pwc, wfd.cFileName, iStr );
			pwc[iStr]=0;
			
			HRESULT hr=pSt->CreateStream(pwc,STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE,0,0,&pStream);
			if( FAILED(hr) )
			{
				CString szFailMsg=CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_FAIL");
				CLang::GetHandle().ShowMessage((CString)wfd.cFileName+/*"fail"*/szFailMsg);
			}
			CFile file(csIn,CFile::modeReadWrite | CFile::shareExclusive);
			
			void * buf = new char[10*1024*1024];
			UINT read= file.Read(buf,10*1024*1024);
			if (read > 0)
			{
				ULONG written;
				pStream->Write(buf,read,&written);
			}else
				break;
			free(pwc);
			delete buf;
			pStream->Release();
		}while (FindNextFile(hFind, &wfd));
	} 
}


//////////////////////////////////////////////////////////////////////////
#include "D:\Program Files\Microsoft Visual Studio\VC98\Include\WINIOCTL.H"
BOOL CMRI_DataBackupDlg::CheckDiskAlready()
{
	BOOL nRet=FALSE;
	CString szCDRomString = GetCD_ROM_DISK_INFO();
	char   pszdrivename[20];   
	DWORD   driveserial;   
	DWORD   maximumcomponentlength;   
	DWORD   filesystemflags;   
	char   pszfilesystemnamebuffer[30];
	::GetVolumeInformation(     
	  szCDRomString,  //   address   of   root   directory   of   the   file   system     
	  pszdrivename,   //   address   of   name   of   the   volume     
	  20,             //   length   of   lpvolumenamebuffer     
	  &driveserial,   //   address   of   volume   serial   number     
	  &maximumcomponentlength,   //   address   of   system   maximum   filename   length     
	  &filesystemflags,                 //   address   of   file   system   flags     
	  pszfilesystemnamebuffer,         //   address   of   name   of   file   system     
	  30                   //   length   of   lpfilesystemnamebuffer     
  );  
	
	HANDLE     hCD,   hFile;   
	DWORD       dwNotUsed;  
	hFile   =   CreateFile("c:\\sector.txt",   
						  GENERIC_WRITE,  
						  0,
						  NULL, 
						  CREATE_ALWAYS,   
						  FILE_ATTRIBUTE_NORMAL,
						  NULL);   

 
//	HANDLE m_hDevice;
//    CString FileName=”F:”;
//    m_hDevice =CreateFile("\\\\.\\"+szCDRomString,                // 文件名路径
//    /*GENERIC_READ*/GENERIC_WRITE,                                            // 读写方式
//    /*FILE_SHARE_READ | FILE_SHARE_WRITE*/0,                      // 共享方式
//    NULL,                                                    // 默认的安全描述符
//    /*OPEN_EXISTING*/OPEN_ALWAYS,                                           // 创建方式
//    0,                                                       // 不需设置文件属性
//    NULL);
	if(szCDRomString.Right(1)=="\\")
	{
		szCDRomString=szCDRomString.Left(szCDRomString.GetLength()-1);
	}

	hCD = CreateFile("\\\\.\\"+szCDRomString, 
					GENERIC_READ,   
					FILE_SHARE_READ|FILE_SHARE_WRITE,   
					NULL,   
					OPEN_EXISTING,   
					FILE_ATTRIBUTE_NORMAL,
					NULL);  

	if(hCD != INVALID_HANDLE_VALUE)   
	{   
		DISK_GEOMETRY dgCDROM;   
		PREVENT_MEDIA_REMOVAL   pmrLockCDROM;   
    
	    //Lock   the   compact   disc   in   the   CD-ROM   drive   to   prevent   accidental   
	    //removal   while   reading   from   it.   
		pmrLockCDROM.PreventMediaRemoval   =   TRUE;   

		//DeviceIoControl(hCD,   IOCTL_CDROM_MEDIA_REMOVAL,   
		DeviceIoControl(hCD,   
						IOCTL_STORAGE_MEDIA_REMOVAL,   
						&pmrLockCDROM,   
						sizeof(pmrLockCDROM),
						NULL,   
						0,  
						&dwNotUsed, 
						NULL); 
		
		//Get   sector   size   of   compact   disc   
		//if   (DeviceIoControl   (hCD,   IOCTL_CDROM_GET_DRIVE_GEOMETRY,   
		if   (DeviceIoControl(hCD,   IOCTL_DISK_GET_DRIVE_GEOMETRY,NULL,0,&dgCDROM,sizeof(dgCDROM), &dwNotUsed,NULL))   
		{   
			LPBYTE   lpSector;   
			DWORD dwSize = 2 * dgCDROM.BytesPerSector;     //   2   sectors   

			//Allocate   buffer   to   hold   sectors   from   compact   disc.   Note   that   
			//the   buffer   will   be   allocated   on   a   sector   boundary   because   the   
			//allocation   granularity   is   larger   than   the   size   of   a   sector   on   a   
			//compact   disk.   
			lpSector=(unsigned char *)VirtualAlloc (NULL, dwSize,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE); 
			
		    // Move   to   16th   sector   for   something   interesting   to   read.   
			SetFilePointer(hCD,dgCDROM.BytesPerSector*16,NULL,FILE_BEGIN);   

		    // Read   sectors   from   the   compact   disc   and   write   them   to   a   file.   
			if(ReadFile(hCD,lpSector,dwSize,&dwNotUsed,NULL))   
				WriteFile(hFile,lpSector, dwSize,&dwNotUsed,NULL); 
			
			VirtualFree(lpSector,0,MEM_RELEASE); 
			nRet=TRUE;
		}
		else
		{
			nRet=FALSE;
		}
    
       //Unlock   the   disc   in   the   CD-ROM   drive.   
		pmrLockCDROM.PreventMediaRemoval   =   FALSE;   
		DeviceIoControl(hCD,
						IOCTL_STORAGE_MEDIA_REMOVAL,
						&pmrLockCDROM, 
						sizeof(pmrLockCDROM),
						NULL,
						0,
						&dwNotUsed,
						NULL);   

		CloseHandle(hCD);   
		CloseHandle(hFile);   
   }

	if(nRet==FALSE)
	{
		return FALSE;
	}

	ULARGE_INTEGER h1;
	ULARGE_INTEGER h2;
	ULARGE_INTEGER h3;
	
	BOOL bRet = GetDiskFreeSpaceEx(szCDRomString+"\\",&h1,&h2,&h3);
	/*********zyh add 2008.4.10*********/
	if(0 == bRet)
		return nRet;
	/**********************************************/
	
	/*
	char szTmp[128];
	sprintf(szTmp, "可用空间：%u, 总共空间：%u, 空闲空间:%u", h1.QuadPart / 1024 / 1024, h2.QuadPart / 1024 / 1024, h3.QuadPart / 1024 / 1024);
	AfxMessageBox(szTmp);
	*/
	
	ULONG dDisc=h2.QuadPart-h3.QuadPart;

	if(dDisc>2048 )//不是空盘
	{
		nRet |= 2;
	}
	if(dDisc+this->m_nSelStudySize>_MAX_CD_)
	{
		nRet |= 4;
	}
	
	return nRet;
}

CString CMRI_DataBackupDlg::GetCD_ROM_DISK_INFO()
{
	BOOL nRet=FALSE;
	TCHAR buf[100];
	DWORD len = GetLogicalDriveStrings(sizeof(buf)/sizeof(TCHAR),buf);
	
	std::string msg = "Logical Drives:\n";  // STL string
	for (TCHAR* s=buf; *s; s+=_tcslen(s)+1) 
	{
		LPCTSTR sDrivePath = s;
		msg += sDrivePath;
		msg += " ";
		
		// GetDriveType 获取枚举值，如DRIVE_UNKNOWN等.
		//
		UINT uDriveType = GetDriveType(sDrivePath);
		if(DRIVE_CDROM==uDriveType)
		{
			return sDrivePath;			
		}
		//	  for (int i=0; DriveTypeFlags[i].name; i++) {
		//         if (uDriveType == DriveTypeFlags[i].type) {
		//            msg += DriveTypeFlags[i].name;
		//            break;
		//         }
		//      }
		//      msg += ''''''''''''''''\n'''''''''''''''';
	}
	return "";
	
}

// 
// void CMRI_DataBackupDlg::OnDestroy() 
// {
// 	CDialog::OnDestroy();
// 	
// 	// TODO: Add your message handler code here
// 	CoUninitialize();
// }
// 
void CMRI_DataBackupDlg::OnEditchangeComboSpeed() 
{
	// TODO: Add your control notification handler code here
	int dCount=m_Combo_CDSpeed.GetCount();
	int dCur=m_Combo_CDSpeed.GetCurSel();
	if(dCur==0)
	{
		m_vCDSpeed=40;
		m_BurnByte=2*1024*1024;
		
	}
	else if(dCur==1)
	{
		m_vCDSpeed=32;
		m_BurnByte=1*1024*1024;
	}
	else if(dCur==2)
	{
		m_vCDSpeed=24;
		m_BurnByte=0.5*1024*1024;
		
	}
	DisplayRecordDiskInfo();
}

bool CMRI_DataBackupDlg::DisplayRecordDiskInfo()
{
	HRESULT hr;
    //Added by Tom, --2008.07.10
	CoInitialize(NULL);
	//IDiscMaster* pDiskMaster;
	IDiscMaster* pDiskMaster;
	hr = CoCreateInstance(CLSID_MSDiscMasterObj, NULL,CLSCTX_LOCAL_SERVER, 
							  IID_IDiscMaster, (void**)&pDiskMaster);

// 	if(!pDiskMaster)
// 	{
// 		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CANNOT_WRITE")/*"Can't Init Storage Container!"*/);
// 		return FALSE;
// 	}
	if(FAILED(hr))
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CANNOT_WRITE")/*"Can't Init Storage Container!"*/);
		return FALSE;

	}

	hr = pDiskMaster->Open();
	if(FAILED(hr))
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CANNOT_WRITE")/*"Can't Init Storage Container!"*/);
		return FALSE;

	}
	
	//	////////////////////////////////////////////////////
	//	//加入读写信息，但是好像需要放入光盘
	//	//
	IJolietDiscMaster* joilet;
	hr = pDiskMaster->SetActiveDiscMasterFormat(IID_IJolietDiscMaster,(void**)&joilet );
	if(FAILED(hr))
	{
		//CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CANNOT_WRITE")/*"Can't Init Storage Container!"*/);
		return FALSE;

	}
	IEnumDiscRecorders* recordersEnum;
	hr = pDiskMaster->EnumDiscRecorders(&recordersEnum);
	if(FAILED(hr))
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CANNOT_WRITE")/*"Can't Init Storage Container!"*/);
		return FALSE;

	}
	ULONG num;
	IDiscRecorder* recorder;
	//一般这个就是默认的刻录机
	hr = recordersEnum->Next(1,&recorder,&num);
	if(recorder==NULL)
	{
		pDiskMaster->Release();
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("DLG_MRI_DATABACKUP_IDD_DIALOG_CD_PARAM___MSG_CANNOT_WRITE")/*"Can't Find CD-RW On Your System!"*/);
		return FALSE;

	}
	//////////////////////////////////////////////////////
	CString str, temp;
	
	CComBSTR b(256);
	recorder->GetBasePnPID(&b);
	str=b;
	m_sCDName.SetWindowText(str);
	//DISPLAYNAMES dn;
	CComBSTR b1(256);
	CComBSTR b2(256);
	CComBSTR b3(256);
	recorder->GetDisplayNames(&b1,&b2,&b3);
	str = b1;
	str = b2;
	str = b3;
	////////////////////////////////////////////////////
	//设置光驱速度
	hr=recorder->OpenExclusive();
	PROPSPEC propspec; 
	propspec.ulKind = PRSPEC_LPWSTR; 
	propspec.lpwstr = L"WriteSpeed";//VolumeName 
	PROPVARIANT propvarRead;
	propvarRead.vt = VT_I4;
	propvarRead.lVal=32;
	//omQIPtr<IPropertyStorage> pPropStg; 
	//IPropertySetStorage *pPropSetStg = NULL;
	IPropertySetStorage *pPropSetStg = NULL;
	IPropertyStorage *pPropStg = NULL;
	WCHAR *pwszError = L"";
	//PROPSPEC propspec; 
	PROPVARIANT propvarWrite; 
	//	PROPVARIANT propvarRead;
	try{
		hr = StgCreateStorageEx( L"WriteRead.stg",
			STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE,
			STGFMT_STORAGE,
			// STGFMT_STORAGE => Structured Storage 
			// property sets
			// STGFMT_FILE    => NTFS file system 
			// property sets
			0, NULL, NULL,
			IID_IPropertySetStorage,
			reinterpret_cast<void**>(&pPropSetStg) );
        if( FAILED(hr) ) throw L"Failed StgCreateStorageEx";
		
		//        hr = pPropSetStg->Create( fmtid, NULL, PROPSETFLAG_DEFAULT, 
		//                    STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,
		//                    &pPropStg );
		//        if( FAILED(hr) ) throw L"Failed IPropertySetStorage::Create";
		hr=recorder->GetRecorderProperties(&pPropStg);
		
		propspec.ulKind = PRSPEC_LPWSTR; 
        propspec.lpwstr = L"WriteSpeed";
		memset(&propvarWrite,0,sizeof(propvarWrite));
		
        propvarWrite.vt = VT_I4;
        propvarWrite.bVal=0x20;
		
        hr = pPropStg->WriteMultiple( 1, &propspec, &propvarWrite, 
			PID_FIRST_USABLE );
		////////////////////////////////////////////////////
		hr=recorder->SetRecorderProperties(pPropStg);
        if( FAILED(hr) ) 
            throw L"Failed IPropertyStorage::WriteMultiple";
		
        // Write a Unicode string property to the property set
		
	}
	catch( const WCHAR *pwszError )
	{
		wprintf( L"Error:  %s (hr=%08x)\n", pwszError, hr );
	}
	
	//PropVariantClear( &propvarRead );
	if( pPropStg ) pPropStg->Release();
	if( pPropSetStg ) pPropSetStg->Release();
	recorder->Release();
	pDiskMaster->Release();
	return TRUE;
}

void CMRI_DataBackupDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(_IMAGE_EVENT_==nIDEvent)
	{
		//m_nProParam=0;
		m_nProParam++;
		if(m_nProParam>=25)
		{
			m_nProParam=25;
		}
		m_Pro_Burn.SetPos(m_nProParam);
	}
	else if(_ADD_DATA_==nIDEvent)
	{
		m_nProParam++;
		if(m_nProParam>=60)
		{
			m_nProParam=60;
		}
		m_Pro_Burn.SetPos(m_nProParam);
		
	}
	else if(_BURN_EVENT_==nIDEvent)
	{
		if(m_BurnTime==0)
			m_BurnTime=1;
		m_BurnParam++;
		
		
		m_nProParam=60+ ((int)(40.0*m_BurnParam/m_BurnTime));
		if(m_nProParam>=95)
		{
			m_nProParam=95;
		}
		m_Pro_Burn.SetPos(m_nProParam);
		
	}
	
	CDialog::OnTimer(nIDEvent);
}
