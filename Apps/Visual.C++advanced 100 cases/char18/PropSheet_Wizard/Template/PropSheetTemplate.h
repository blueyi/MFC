// $$Root$$.h : main header file for the $$Root$$ application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App:
// See $$Root$$.cpp for the implementation of this class
//

class C$$Safe_root$$App : public CWinApp
{
public:
	C$$Safe_root$$App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C$$Safe_root$$App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

$$IF(START_ON_TASKBAR)
public:
	BOOL EnableStartOnTaskBar (BOOL bEnable = TRUE)
	{
		BOOL bRes = GetProfileInt (_T ("StartUp"), _T ("StartOnTaskBarAllowed"), FALSE);
		WriteProfileInt (_T ("StartUp"), _T ("StartOnTaskBarAllowed"), bEnable);
		return (bRes);
	}
$$ENDIF	//START_ON_TASKBAR

// Implementation

	//{{AFX_MSG(C$$Safe_root$$App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

$$IF(START_ON_TASKBAR)
inline BOOL AfxEnableStartOnTaskBar (BOOL bEnable = TRUE)
{
	return (((C$$Safe_root$$App *)AfxGetApp ())->EnableStartOnTaskBar (bEnable));
}
$$ENDIF	//START_ON_TASKBAR
