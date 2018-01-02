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

// NetTrafficButton.h : Haupt-Header-Datei für die Anwendung NETTRAFFICBUTTON
//

#if !defined(AFX_NETTRAFFICBUTTON_H__90594683_8F58_4A0E_8B76_A880A8C7D109__INCLUDED_)
#define AFX_NETTRAFFICBUTTON_H__90594683_8F58_4A0E_8B76_A880A8C7D109__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		


class CNetTrafficButtonApp : public CWinApp
{
public:
	CNetTrafficButtonApp();

	//{{AFX_VIRTUAL(CNetTrafficButtonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	//{{AFX_MSG(CNetTrafficButtonApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_NETTRAFFICBUTTON_H__90594683_8F58_4A0E_8B76_A880A8C7D109__INCLUDED_)
