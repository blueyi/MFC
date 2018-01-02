// HistogramMatlab.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HistogramMatlab.h"
#include "HistogramMatlabDlg.h"

#include "gdiplus.h"
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatlabApp

BEGIN_MESSAGE_MAP(CHistogramMatlabApp, CWinApp)
	//{{AFX_MSG_MAP(CHistogramMatlabApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatlabApp construction

CHistogramMatlabApp::CHistogramMatlabApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHistogramMatlabApp object

CHistogramMatlabApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatlabApp initialization

BOOL CHistogramMatlabApp::InitInstance()
{
	AfxEnableControlContainer();
	CoInitialize(NULL);

	CRandomGenerator randn;

	InitMatlab();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	CHistogramMatlabDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CHistogramMatlabApp::ExitInstance() 
{
	DeInitMatlab();

	CoUninitialize();

	GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}

void CHistogramMatlabApp::InitMatlab()
{
	// Get the Class Identifier for Matlab Application Object,
	// which is a globally unique identifier (GUID)
	HRESULT hr;	
	
	CLSID clsid;
	::CLSIDFromProgID(OLESTR("Matlab.Application"), &clsid);
	
	
	// Create an instance of the Matlab application and obtain the pointer
	// to the application's IUnknown interface
	
	IUnknown* pUnk;
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_SERVER,IID_IUnknown,(void**) &pUnk);
	if (FAILED(hr))
		return;

	// Query IUnknown to retrieve a pointer to the application IDispatch
	// interface
	hr = pUnk ->QueryInterface(IID_IDispatch, (void**)&m_pMtlbDispApp);
	if (FAILED(hr))
		return;
}

void CHistogramMatlabApp::DeInitMatlab()
{
	// Release the interface, clean up memory	
	if (m_pMtlbDispApp)
		m_pMtlbDispApp ->Release();
}
