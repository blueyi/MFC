#if !defined _WORK_H_
#define _WORK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       

/////////////////////////////////////////////////////////////////////////////

class CWorkApp : public CWinApp
{
public:
	CWorkApp();

	//{{AFX_VIRTUAL(CWorkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

public:
	//{{AFX_MSG(CWorkApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif 