// RenameUtilityDlg.cpp : implementation file
//
#include "stdafx.h"
#include "RenameUtility.h"
#include "RenameUtilityDlg.h"
#include "renameutilitydlg.h"
#include "DirDialog.h"
#include "..\inc\renameutilitydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
volatile int CRenameUtilityDlg::	m_nPercent = 0;
CString CRenameUtilityDlg::			m_strStatus = _T("");
BOOL CRenameUtilityDlg::			m_bCancelled = FALSE;
BOOL CRenameUtilityDlg::			m_bResult = 25;
double CRenameUtilityDlg::			m_bTotalFileCount = 0;

/*---------------------------------------------------------------------------------------------
Name				:	run(LPVOID pParam)
Purpose				:	<Purpose>
Parameters			:
						LPVOID  pParam - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
UINT run(LPVOID pParam)
{
	CRenameOption	*objRenameData = (CRenameOption *) pParam;
	CBulkRename		objBulkRename;
	BOOL			bResult;
	int				nFileCount = 0;
	switch(objRenameData->enOperationType)
	{
		case CRenameOption :: OperationType :: nChangeCase: //
			{
				bResult = objBulkRename.FileChangeCase(objRenameData->m_strPath,
													   objRenameData->CaseType,
													   objRenameData->bRenameSubFolder,
													   CRenameUtilityDlg :: CancelProc);
			}
			break;

		case CRenameOption :: OperationType :: nReplace:	//
			{
				bResult = objBulkRename.RenameFile(*objRenameData, CRenameUtilityDlg :: CancelProc);
			}
			break;

		case CRenameOption :: OperationType :: nSuff_Pref:	//
			{
				bResult = objBulkRename.RenameFile(*objRenameData, CRenameUtilityDlg :: CancelProc);
			}
			break;
	}

	//bResult = objBulkRename.FileChangeCase(objRenameData->m_strPath,objRenameData->CaseType,objRenameData->bRenameSubFolder,CRenameUtilityDlg::CancelProc);
	CRenameUtilityDlg :: m_bResult = bResult;
	nFileCount = CBulkRename :: nFileCurrCount;
	:: PostMessage(objRenameData->hWnd, WM_USER_THREAD_FINISHED, (WPARAM) bResult, 0);
	objBulkRename.ErrorReport();
	delete objRenameData;
	objRenameData = NULL;
	return(0);
}

/*---------------------------------------------------------------------------------------------
Name				:	FileCountThread(LPVOID pParam)
Purpose				:	<Purpose>
Parameters			:
						LPVOID  pParam - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
UINT FileCountThread(LPVOID pParam)
{
	int					nFileCount = 0;
	CRenameOption		*objRenameData = (CRenameOption *) pParam;
	CRenameUtilityDlg	objRenameUtilityDlg;
	CBulkRename			objBulkRename;
	objBulkRename.GetFileCountinFolder(objRenameData->m_strPath, nFileCount);
	CRenameUtilityDlg :: m_bTotalFileCount = nFileCount;
	delete objRenameData;
	objRenameData = NULL;
	return(0);
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum
	{
		IDD = IDD_ABOUTBOX
	};
protected:
	virtual void	DoDataExchange(CDataExchange *pDX); // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog :: DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
// CRenameUtilityDlg dialog

/*---------------------------------------------------------------------------------------------
Name				:	CRenameUtilityDlg(CWnd *pParent = 0)
Purpose				:	<Purpose>
Parameters			:
						CWnd * pParent - 
Return				:	Void.
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
CRenameUtilityDlg::CRenameUtilityDlg(CWnd *pParent /*=NULL*/ ) : CDialog(CRenameUtilityDlg::IDD, pParent), m_strDirectory(_T("")), bCheckFolderRename(FALSE), nNameState(0), c_strFindWhat(_T("")), c_strReplaceWith(_T("")), c_strAddSuffix(_T("")), cv_Suffix(0), cv_incext(0)
{
	poProgress = NULL;
	poProgressText = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

/*---------------------------------------------------------------------------------------------
Name				:	DoDataExchange(CDataExchange *pDX)
Purpose				:	<Purpose>
Parameters			:
						CDataExchange * pDX - 
Return				:	Void.
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog :: DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROOTFOLDER, m_strDirectory);
	DDX_Check(pDX, IDC_CHECK_FOLDER, bCheckFolderRename);
	DDX_Radio(pDX, IDC_RAD_LOWERCASE, nNameState);

	//DDX_Control(pDX, IDC_PROG_RENAME, RenameProgressBar);
	DDX_Control(pDX, IDC_STATIC_PROGRESSBAR, m_CEProgress);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_cSprogresstext);
	DDX_Text(pDX, IDC_EDIT_FIND, c_strFindWhat);
	DDV_MaxChars(pDX, c_strFindWhat, 25);
	DDX_Text(pDX, IDC_EDIT_REPLACE, c_strReplaceWith);
	DDV_MaxChars(pDX, c_strReplaceWith, 25);
	DDX_Text(pDX, IDC_EDIT_ADDSUFFIX, c_strAddSuffix);
	DDV_MaxChars(pDX, c_strAddSuffix, 15);
	DDX_Radio(pDX, IDC_RAD_SUFFIX, cv_Suffix);
	DDX_Radio(pDX, IDC_RAD_INCEXT, cv_incext);
}

BEGIN_MESSAGE_MAP(CRenameUtilityDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUT_ROOTFOLDER_DIR, OnBnClickedButRootfolderDir)
	ON_BN_CLICKED(IDC_BUT_UPPERCASE, OnBnClickedButUppercase)
	ON_WM_TIMER()
	ON_MESSAGE(WM_USER_THREAD_FINISHED, OnThreadFinished)
	ON_BN_CLICKED(IDC_CHECK_FOLDER, OnBnClickedCheckFolder)
	ON_BN_CLICKED(IDC_BUT_REPLACE_RENAME, OnBnClickedButReplaceRename)
	ON_BN_CLICKED(IDC_BUT_SUFFIX, OnBnClickedButSuffix)
	ON_BN_CLICKED(IDC_RAD_RMV_TXT, OnBnClickedRadRmvTxt)
	ON_BN_CLICKED(IDC_RAD_EXCL_EXT, OnBnClickedRadExclExt)
	ON_BN_CLICKED(IDC_RAD_INCEXT, OnBnClickedRadIncext)
END_MESSAGE_MAP()
// CRenameUtilityDlg message handlers

/*---------------------------------------------------------------------------------------------
Name				:	OnInitDialog(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CRenameUtilityDlg::OnInitDialog()
{
	CDialog :: OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu	*pSysMenu = GetSystemMenu(FALSE);
	if(pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if(!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon

	// Create the CPPToolTip object
	m_tooltip.Create(this);

	//add tool tips
	AddToolTips();

	// TODO: Add extra initialization here
	return(TRUE);				// return TRUE  unless you set the focus to a control
}

void CRenameUtilityDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg	dlgAbout;

		dlgAbout.DoModal();
	}
	else
	{
		CDialog :: OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,

//  this is automatically done for you by the framework.
void CRenameUtilityDlg::OnPaint()
{
	if(IsIconic())
	{
		CPaintDC	dc(this);	// device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM> (dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int		cxIcon = GetSystemMetrics(SM_CXICON);
		int		cyIcon = GetSystemMetrics(SM_CYICON);
		CRect	rect;
		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog :: OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags

//  the minimized window.
HCURSOR CRenameUtilityDlg::OnQueryDragIcon()
{
	return (static_cast<HCURSOR>(m_hIcon));
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedButRootfolderDir(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedButRootfolderDir()
{
	CDirDialog	dlgDir;

	dlgDir.m_strTitle = _T("Select directory for Renaming Files");
	UpdateData(TRUE);
	dlgDir.m_strSelDir = m_strDirectory;
	dlgDir.m_strWindowTitle = _T("Select directory ");
	if(dlgDir.DoBrowse(this) == IDOK)
	{
		m_strDirectory = dlgDir.m_strPath;

		// Append backslash if necessary
		if((m_strDirectory.GetLength() > 0) && (m_strDirectory[m_strDirectory.GetLength() - 1] != TCHAR('\\')))
		{
			m_strDirectory += TCHAR('\\');
		}

		UpdateData(FALSE);

		CRenameOption	*pRenameData = new CRenameOption;
		pRenameData->m_strPath = m_strDirectory;
		pRenameData->hWnd = this->m_hWnd;

		//Create the worker thread
		CWinThread	*pThread = AfxBeginThread(FileCountThread, (void *) pRenameData, THREAD_PRIORITY_NORMAL);

		//Fail if the thread failed to create itself
		if(!pThread)
		{
			ASSERT(FALSE);
		}
	}
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedButUppercase(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedButUppercase()
{
	UpdateData(TRUE);

	int n_TimerID;

	//RenameProgressBar.SetPos(0);
	//RenameProgressBar.SetRange32(0, 100);
	poProgress = &m_CEProgress;
	poProgressText = &m_cSprogresstext;
	CBulkRename :: nFileCurrCount = 0;
	m_poSkinProgress = new CSkinProgress(poProgress,
										 m_bTotalFileCount,
										 NULL,
										 //#ifdef dCSP_SLIDERBAR_METHOD
										 FALSE,
										 //#endif // dCSP_SLIDERBAR_METHOD
										 poProgressText,
										 m_strStatus,
										 cSPT_AUTOSIZE);

	//m_poSkinProgress->SetSize(200,TRUE);
	n_TimerID = SetTimer(5, 30, NULL);
	if(!m_strDirectory.IsEmpty())
	{
		BOOL	bResult = FALSE;
		if(nNameState == 0)
		{
			bResult = RecChangeCase(m_strDirectory, CRenameOption :: enCaseType :: nLowerCase, bCheckFolderRename);
		}
		else if(nNameState == 1)
		{
			bResult = RecChangeCase(m_strDirectory, CRenameOption :: enCaseType :: nUpperCase, bCheckFolderRename);
		}
		else if(nNameState == 2)
		{
			bResult = RecChangeCase(m_strDirectory, CRenameOption :: enCaseType :: nTitelCase, bCheckFolderRename);
		}
	}
	else
	{
		AfxMessageBox(_T("Please select a folder to rename "));
	}
}

/*---------------------------------------------------------------------------------------------
Name				:	RecChangeCase(CString strPath, CRenameOption::enCaseType nCaseType, BOOL bIncDir = 0)
Purpose				:	<Purpose>
Parameters			:
						CString  strPath - 
						CRenameOption::enCaseType nCaseType - 
						BOOL  bIncDir - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CRenameUtilityDlg::RecChangeCase(CString strPath, CRenameOption::enCaseType nCaseType, BOOL bIncDir)
{
	UpdateData(TRUE);

	CRenameOption	*pRenameData = new CRenameOption;
	pRenameData->m_strPath = strPath;
	pRenameData->CaseType = nCaseType;
	pRenameData->bRenameSubFolder = bIncDir;
	pRenameData->hWnd = this->m_hWnd;
	pRenameData->enOperationType = CRenameOption :: OperationType :: nChangeCase;
	DisableUI();

	//Create the worker thread
	CWinThread	*pThread = AfxBeginThread(run, (void *) pRenameData, THREAD_PRIORITY_NORMAL);

	//Fail if the thread failed to create itself
	if(!pThread)
	{
		ASSERT(FALSE);
		return(FALSE);
	}

	return(TRUE);
}

/*---------------------------------------------------------------------------------------------
Name				:	CancelProc(LPCTSTR strStatus, int nPercent)
Purpose				:	<Purpose>
Parameters			:
						LPCTSTR  strStatus - 
						int  nPercent - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CALLBACK CRenameUtilityDlg::CancelProc(LPCTSTR strStatus, int nPercent)
{
	m_nPercent = nPercent;
	m_strStatus = strStatus;

	return(m_bCancelled);
}

/*---------------------------------------------------------------------------------------------
Name				:	OnTimer(UINT nIDEvent)
Purpose				:	<Purpose>
Parameters			:
						UINT  nIDEvent - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString strMessage;

	//strMessage.Format(_T("Importing File : %s : Percent :  %i "),m_strStatus,m_nPercent);
	strMessage = m_strStatus;
	if(m_nPercent == 100)
	{
		strMessage = _T("Import file Complete");
	}

	//GetDlgItem(IDC_STATIC_PROGRESS)->SetWindowText(strMessage);
	//RenameProgressBar.SetPos(m_nPercent);
	if(m_poSkinProgress)
	{
		m_poSkinProgress->SetPos(m_nPercent);
		m_poSkinProgress->SetText(strMessage, TRUE);
	}

	CDialog :: OnTimer(nIDEvent);
}

/*---------------------------------------------------------------------------------------------
Name				:	OnThreadFinished(WPARAM wParam, LPARAM lParam)
Purpose				:	<Purpose>
Parameters			:
						WPARAM  wParam - 
						LPARAM  lParam - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
LONG CRenameUtilityDlg::OnThreadFinished(WPARAM wParam, LPARAM lParam)
{
	BOOL	Result = (int) wParam;
	EnableUI();

	//RenameProgressBar.SetPos(m_nPercent);
	if(CBulkRename :: nErrorCount == 0)
	{
		GetDlgItem(IDC_STATIC_PROGRESS)->SetWindowText(_T("All files renamed Successfuly "));
		KillTimer(5);
		m_poSkinProgress->SetPos(m_bTotalFileCount);

		int nResult = AfxMessageBox(_T("All files renamed Successfuly "));
		if(nResult == IDOK)
		{
			//RenameProgressBar.SetPos(0);
			m_poSkinProgress->SetPos(0);
		}
	}
	else
	{
		GetDlgItem(IDC_STATIC_PROGRESS)->SetWindowText(_T("Error Ocurred while Renaming some of the file "));
		KillTimer(5);

		int nResult = AfxMessageBox(_T("Error Ocurred while Renaming some of the file "));
		if(nResult == IDOK)
		{
			//RenameProgressBar.SetPos(0);
			m_poSkinProgress->SetPos(0);
		}
	}

	// If Error Count is more than 0 then show the Error Log
	if(CBulkRename :: nErrorCount > 0)
	{
		ShellExecute(NULL, "open", "ErrorLog.htm", NULL, NULL, SW_SHOWNORMAL);
	}

	delete m_poSkinProgress;
	m_poSkinProgress = NULL;
	UpdateData(FALSE);

	return(0);
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedCheckFolder(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedCheckFolder()
{
	UpdateData();
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedButReplaceRename(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedButReplaceRename()
{
	CBulkRename :: nFileCurrCount = 0;

	//RenameFile
	UpdateData(TRUE);
	if(!(m_strDirectory.IsEmpty() || c_strFindWhat.IsEmpty()))
	{
		int n_TimerID;
		n_TimerID = SetTimer(5, 10, NULL);

		//RenameProgressBar.SetPos(0);
		//RenameProgressBar.SetRange32(0, 100);
		poProgress = &m_CEProgress;
		poProgressText = &m_cSprogresstext;

		m_poSkinProgress = new CSkinProgress(poProgress,
											 m_bTotalFileCount,
											 NULL,
											 //#ifdef dCSP_SLIDERBAR_METHOD
											 FALSE,
											 //#endif // dCSP_SLIDERBAR_METHOD
											 poProgressText,
											 m_strStatus,
											 cSPT_AUTOSIZE);

		//m_poSkinProgress->SetSize(200,TRUE);
		CRenameOption	*pRenameData = new CRenameOption;
		pRenameData->m_strPath = m_strDirectory;
		pRenameData->hWnd = this->m_hWnd;
		pRenameData->m_strFindWhat = c_strFindWhat;
		pRenameData->m_strReplaceWith = c_strReplaceWith;
		pRenameData->enOperationType = CRenameOption :: OperationType :: nReplace;
		if(cv_incext == 0)
		{
			pRenameData->enRenameOptions = CRenameOption :: RenameOptions :: nIncludeExt;
		}
		else if(cv_incext == 1)
		{
			pRenameData->enRenameOptions = CRenameOption :: RenameOptions :: nExcludeExt;
		}
		else if(cv_incext == 2)
		{
			pRenameData->enRenameOptions = CRenameOption :: RenameOptions :: nRemoveText;
		}

		DisableUI();

		//Create the worker thread
		CWinThread	*pThread = AfxBeginThread(run, (void *) pRenameData, THREAD_PRIORITY_NORMAL);

		//Fail if the thread failed to create itself
		if(!pThread)
		{
			ASSERT(FALSE);
		}
	}
	else
	{
		if(m_strDirectory.IsEmpty())
		{
			AfxMessageBox(_T("Please select a folder to rename "));
			GetDlgItem(IDC_EDIT_ROOTFOLDER)->SetFocus();
			return;
		}
		else if(c_strFindWhat.IsEmpty())
		{
			AfxMessageBox(_T("Please enter the text that need to be changes  "));
			GetDlgItem(IDC_EDIT_FIND)->SetFocus();
			return;
		}
		else if(c_strReplaceWith.IsEmpty())
		{
			AfxMessageBox(_T("Please enter the New text   "));
			GetDlgItem(IDC_EDIT_REPLACE)->SetFocus();
			return;
		}
	}
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedButSuffix(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedButSuffix()
{
	CBulkRename :: nFileCurrCount = 0;

	//RenameFile
	UpdateData(TRUE);
	if(!(m_strDirectory.IsEmpty() || c_strAddSuffix.IsEmpty()))
	{
		int n_TimerID;
		n_TimerID = SetTimer(5, 10, NULL);

		//RenameProgressBar.SetPos(0);
		//RenameProgressBar.SetRange32(0, 100);
		poProgress = &m_CEProgress;
		poProgressText = &m_cSprogresstext;

		m_poSkinProgress = new CSkinProgress(poProgress,
											 m_bTotalFileCount,
											 NULL,
											 //#ifdef dCSP_SLIDERBAR_METHOD
											 FALSE,
											 //#endif // dCSP_SLIDERBAR_METHOD
											 poProgressText,
											 m_strStatus,
											 cSPT_AUTOSIZE);

		//m_poSkinProgress->SetSize(200,TRUE);
		//cv_Suffix;
		CRenameOption	*pRenameData = new CRenameOption;
		pRenameData->m_strPath = m_strDirectory;
		pRenameData->hWnd = this->m_hWnd;
		pRenameData->m_strSuff_Pref = c_strAddSuffix;
		pRenameData->enOperationType = CRenameOption :: OperationType :: nSuff_Pref;
		if(cv_Suffix == 0)
		{
			pRenameData->enRenameOptions = CRenameOption :: RenameOptions :: nSuffix;
		}
		else if(cv_Suffix == 1)
		{
			pRenameData->enRenameOptions = CRenameOption :: RenameOptions :: nPrefix;
		}

		DisableUI();

		//Create the worker thread
		CWinThread	*pThread = AfxBeginThread(run, (void *) pRenameData, THREAD_PRIORITY_NORMAL);

		//Fail if the thread failed to create itself
		if(!pThread)
		{
			ASSERT(FALSE);
		}
	}
	else
	{
		if(m_strDirectory.IsEmpty())
		{
			AfxMessageBox(_T("Please select a folder to rename "));
			GetDlgItem(IDC_EDIT_ROOTFOLDER)->SetFocus();
			return;
		}
		else if(c_strAddSuffix.IsEmpty())
		{
			AfxMessageBox(_T("Please add some suffix or Prefix"));
			GetDlgItem(IDC_EDIT_ADDSUFFIX)->SetFocus();
			return;
		}
	}
}

/*---------------------------------------------------------------------------------------------
Name				:	PreTranslateMessage(MSG *pMsg)
Purpose				:	<Purpose>
Parameters			:
						MSG * pMsg - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CRenameUtilityDlg::PreTranslateMessage(MSG *pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_tooltip.RelayEvent(pMsg);
	return(CDialog :: PreTranslateMessage(pMsg));
}

/*---------------------------------------------------------------------------------------------
Name				:	AddToolTips(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	Void.
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::AddToolTips()
{
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_ROOTFOLDER),
					  _T("Enter the Parent folder in which all <BR>the files will be Renamed. <BR><font color=red size=12pt style=b> Note:</font> please select the folder by clicking on ... only"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUT_ROOTFOLDER_DIR), _T("Choose the Parent Folder."));
	m_tooltip.AddTool(GetDlgItem(IDC_CHECK_FOLDER),
					  _T("If Selected all the SubFolder Will also <BR>be Renamed along with Files."));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_LOWERCASE), _T("Converts all letters in the name(s)<BR>to lower-case"));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_UPPERCASE), _T("Converts all letters in the name(s) <BR>into capitals."));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_TITELCASE),
					  _T("Converts all the words in the selected <BR>items to initial caps. A word is <BR>generally defined as a string of letters proceeded by <BR>a space or a bracket. So <B>\"joe public.txt\"</B> <BR>would become <B>\"Joe Public.txt\"</B> <BR>but <B>\"joe-public.txt\"</B> would become <B>\"Joe-public.txt\"</B>."));
	m_tooltip.AddTool(GetDlgItem(IDC_BUT_UPPERCASE),
					  _T("Change case of all the files inside the <BR>Selected Parent Folder."));
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_FIND), _T("Specify the text you wish to find"));
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_REPLACE), _T("Specify the text you wish to replace <BR>it with."));
	m_tooltip.AddTool(GetDlgItem(IDC_EDIT_ADDSUFFIX), _T("Enter the text to be <BR>Added as Prefix or Suffix."));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_SUFFIX), _T("Add a fixed text string to the <BR>start of the filename."));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_PREFIX), _T("Add a fixed text string to the end <BR>of a filename."));
	m_tooltip.AddTool(GetDlgItem(IDC_BUT_SUFFIX), _T("Add a fixed prefix or suffix to the <BR>filename."));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_INCEXT), _T("If Selected Extention will <BR>also be included in file names."));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_EXCL_EXT), _T("If Selected Extention will <BR>not be considered"));
	m_tooltip.AddTool(GetDlgItem(IDC_BUT_REPLACE_RENAME),
					  _T("Allow you to replace occurrences of ,<BR>one text string with another "));
	m_tooltip.AddTool(GetDlgItem(IDC_RAD_RMV_TXT),
					  _T("Rename all the files by  <BR>Removing the specified text from all <BR>file names"));

	m_tooltip.SetNotify();
	m_tooltip.SetColorBk(RGB(255, 255, 255), RGB(240, 247, 255), RGB(192, 192, 208));
	m_tooltip.SetEffectBk(CPPDrawManager :: EFFECT_SOFTBUMP);
	m_tooltip.EnableEscapeSequences(0);
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedRadRmvTxt(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedRadRmvTxt()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_REPLACE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_REMOVETXT)->SetWindowText(_T("Remove Text"));
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedRadExclExt(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedRadExclExt()
{
	GetDlgItem(IDC_EDIT_REPLACE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_REMOVETXT)->SetWindowText(_T("Find What"));
}

/*---------------------------------------------------------------------------------------------
Name				:	OnBnClickedRadIncext(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CRenameUtilityDlg::OnBnClickedRadIncext()
{
	GetDlgItem(IDC_EDIT_REPLACE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_REMOVETXT)->SetWindowText(_T("Find What"));
}

void CRenameUtilityDlg::DisableUI()
{
	GetDlgItem(IDC_BUT_ROOTFOLDER_DIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_UPPERCASE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_REPLACE_RENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_SUFFIX)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
}

void CRenameUtilityDlg::EnableUI()
{
	GetDlgItem(IDC_BUT_ROOTFOLDER_DIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_UPPERCASE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_REPLACE_RENAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_SUFFIX)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
}
