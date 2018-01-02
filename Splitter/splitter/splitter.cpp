// splitter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "splitter.h"
#include "MyDocument.h"
#include "MyView1.h"
#include "MyView2.h"
#include "MyFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterApp

BEGIN_MESSAGE_MAP(CSplitterApp, CWinApp)
	//{{AFX_MSG_MAP(CSplitterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterApp construction

CSplitterApp::CSplitterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSplitterApp object

CSplitterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSplitterApp initialization

BOOL CSplitterApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


 	CMultiDocTemplate* pDocTemplate1;
	pDocTemplate1 = new CMultiDocTemplate(
		IDR_MAINFRAME2,
		RUNTIME_CLASS(CMyDocument),
		RUNTIME_CLASS(CMyFrame),       
		RUNTIME_CLASS(CMyView1));
  
  AddDocTemplate(pDocTemplate1);

 	CMultiDocTemplate* pDocTemplate2;
	pDocTemplate2 = new CMultiDocTemplate(
		IDR_MAINFRAME2,
		RUNTIME_CLASS(CMyDocument),
		RUNTIME_CLASS(CMyFrame),       
		RUNTIME_CLASS(CMyView2));
  AddDocTemplate(pDocTemplate2);

	CMDIFrameWnd* pMainFrame = new CMDIFrameWnd;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

  // Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	pDocTemplate1->OpenDocumentFile(NULL);
	pDocTemplate2->OpenDocumentFile(NULL);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}
