// SoundGenerator.h : main header file for the SOUNDGENERATOR application
//

#if !defined(AFX_SOUNDGENERATOR_H__6EA5EEAB_8AEA_4C9D_8A04_999245AEAE3E__INCLUDED_)
#define AFX_SOUNDGENERATOR_H__6EA5EEAB_8AEA_4C9D_8A04_999245AEAE3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoundGeneratorApp:
// See SoundGenerator.cpp for the implementation of this class
//

class CSoundGeneratorApp : public CWinApp
{
public:
	CSoundGeneratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundGeneratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSoundGeneratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDGENERATOR_H__6EA5EEAB_8AEA_4C9D_8A04_999245AEAE3E__INCLUDED_)
