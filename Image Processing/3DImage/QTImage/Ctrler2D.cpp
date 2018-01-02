// Ctrler2D.cpp : implementation file
//

#include "stdafx.h"
#include "QTImage.h"
#include "Ctrler2D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C2DCtrler dialog


C2DCtrler::C2DCtrler(CWnd* pParent /*=NULL*/)
	: CDialog(C2DCtrler::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DCtrler)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void C2DCtrler::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DCtrler)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DCtrler, CDialog)
	//{{AFX_MSG_MAP(C2DCtrler)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DCtrler message handlers
