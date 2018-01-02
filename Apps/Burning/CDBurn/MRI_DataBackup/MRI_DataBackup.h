// MRI_DataBackup.h : main header file for the MRI_DATABACKUP application
//

#if !defined(AFX_MRI_DATABACKUP_H__3F498328_734C_4F69_83A5_A0140695217C__INCLUDED_)
#define AFX_MRI_DATABACKUP_H__3F498328_734C_4F69_83A5_A0140695217C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMRI_DataBackupApp:
// See MRI_DataBackup.cpp for the implementation of this class
//

class CMRI_DataBackupApp : public CWinApp
{
public:
	CMRI_DataBackupApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRI_DataBackupApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMRI_DataBackupApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRI_DATABACKUP_H__3F498328_734C_4F69_83A5_A0140695217C__INCLUDED_)
