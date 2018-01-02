#include "stdafx.h"
#include "ticktest.h"
#include "cputicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CTickTestApp, CWinApp)
	//{{AFX_MSG_MAP(CTickTestApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

CTickTestApp::CTickTestApp()
{
}

CTickTestApp theApp;

BOOL CTickTestApp::InitInstance()
{
  CCPUTicker tick1;
  CCPUTicker tick2;

  //make sure High res timing is available
  if (!tick1.IsAvailable())
  {
    AfxMessageBox(_T("High resolution timing is not available on this CPU"));
    return FALSE;
  }

  //Warn that program may look like it has hung while running
  if (AfxMessageBox(_T("This program will appear to hang for up to 20 seconds while determining CPU speed\nThis is normal behaviour, Continue?"), MB_YESNO) == IDYES)
  {
    //perform the test
    tick1.Measure();
    Sleep(1000);
    tick2.Measure();

    //Display the results
    CString sMsg;
    sMsg.Format(_T("Sleep(1000) really sleeped for %f seconds"), tick2.GetTickCountAsSeconds() - tick1.GetTickCountAsSeconds());
    AfxMessageBox(sMsg);
  }

	return FALSE;
}
