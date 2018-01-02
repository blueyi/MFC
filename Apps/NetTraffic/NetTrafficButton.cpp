/*******************************************

	MFTrafficButton

	Version:	1.0
	Date:		31.10.2001
	Author:		Michael Fatzi
	Mail:		Michael_Fatzi@hotmail.com
	Copyright 1996-1997, Keith Rule

	You may freely use or modify this code provided this
	Copyright is included in all derived versions.
	
	History: 10.2001 Startup

	Handy little button control to display current 
	nettraffic as graph in a button.

********************************************/


#include "stdafx.h"
#include "NetTrafficButton.h"
#include "NetTrafficButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetTrafficButtonApp

BEGIN_MESSAGE_MAP(CNetTrafficButtonApp, CWinApp)
	//{{AFX_MSG_MAP(CNetTrafficButtonApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetTrafficButtonApp Construction

CNetTrafficButtonApp::CNetTrafficButtonApp()
{
}


CNetTrafficButtonApp theApp;


BOOL CNetTrafficButtonApp::InitInstance()
{

#ifdef _AFXDLL
	Enable3dControls();			
#else
	Enable3dControlsStatic();	
#endif

	this->SetDialogBkColor(RGB(170,175,195),RGB(0,0,0));

	CNetTrafficButtonDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}

	return FALSE;
}
