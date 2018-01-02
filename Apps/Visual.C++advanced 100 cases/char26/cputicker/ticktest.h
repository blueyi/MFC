#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

class CTickTestApp : public CWinApp
{
public:
	CTickTestApp();

	//{{AFX_VIRTUAL(CCpuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCpuApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

