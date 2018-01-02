// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Observer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "Observer.h"
#include "MainFrm.h"

#include "ChartControl.h"

#include "./TipOfTheDay/custsite.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CObserverApp

BEGIN_MESSAGE_MAP(CObserverApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CObserverApp::OnAppAbout)
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CObserverApp::OnFileOpen)
	// Standard print setup command
	//ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
/*
	ON_COMMAND( ID_HELP_FINDER, OnHelpFinder )
	ON_COMMAND( ID_HELP, OnHelp ) */

END_MESSAGE_MAP()


// CObserverApp construction

CObserverApp::CObserverApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CObserverApp object

CObserverApp theApp;


// CObserverApp initialization

BOOL CObserverApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(0);  // Load standard INI file options

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	
	LoadExtDll_CFormView();
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
			if (!ProcessShellCommand(cmdInfo))
					return FALSE;
		
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();


	CCustomOccManager *pMgr = new CCustomOccManager;

	// Create an IDispatch class for extending the Dynamic HTML Object Model 
	m_pDispOM = new CImpIDispatch;

	// Set our control containment up but using our control container 
	// management class instead of MFC's default
	AfxEnableControlContainer(pMgr);

	



	int showTips=GetInt(_T("showTips"),1);
	if(showTips==1)
	{
		CTipOfTheDayDlg TipDialog;
		TipDialog.DoModal();
	}



	//EnableHtmlHelp();

	return TRUE;
}





CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_LICENCE, &CAboutDlg::OnBnClickedLicence)
	ON_BN_CLICKED(IDC_WEBSITE, &CAboutDlg::OnBnClickedWebsite)
END_MESSAGE_MAP()

// App command to run the dialog
#include "ChartControl.h"
void CObserverApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CObserverApp customization load/save methods

void CObserverApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CObserverApp::LoadCustomState()
{
}

void CObserverApp::SaveCustomState()
{
}


CObserverApp::~CObserverApp()
{
	if ( m_pDispOM != NULL)
	{
		delete m_pDispOM;
	}
}

void CObserverApp::OnFileOpen()
{
	//
}


// CObserverApp message handlers




void CAboutDlg::OnBnClickedLicence()
{
	// TODO: Add your control notification handler code here
	::ShellExecute (NULL, NULL, _T("http://www.apache.org/licenses/LICENSE-2.0"), NULL, NULL, NULL);
}

void CAboutDlg::OnBnClickedWebsite()
{
	// TODO: Add your control notification handler code here
	::ShellExecute (NULL, NULL, _T("http://www.potatosoftware.com"), NULL, NULL, NULL);
}
