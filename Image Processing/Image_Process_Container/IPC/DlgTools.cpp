// DlgTools.cpp : implementation file
//

#include "stdafx.h"
#include "IPC.h"
#include "DlgTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTools dialog


CDlgTools::CDlgTools(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTools::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTools)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTools::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTools)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTools, CDialog)
	//{{AFX_MSG_MAP(CDlgTools)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTools message handlers
