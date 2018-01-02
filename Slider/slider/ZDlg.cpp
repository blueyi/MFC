// ZDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Step.h"
#include "ZDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDlg dialog

ZDlg::ZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ZDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ZDlg)
	//}}AFX_DATA_INIT
}

void ZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZDlg)
	DDX_Control(pDX, STA_INFO, sta_Info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZDlg, CDialog)
	//{{AFX_MSG_MAP(ZDlg)
	ON_BN_CLICKED(IDOK, On_IDOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void ZDlg::On_IDOK() 
{
}

BOOL ZDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rcMe;
	GetClientRect(&rcMe);
	rcMe.DeflateRect(20,20);
	
	CRect rc;

	BOOL Create(CWnd*pMum,CRect rcBd,BOOL bHorz,int iID);
	//Height or Width of the slider is 27 pixels always
	rcMe.DeflateRect(27,27);

	//create vert 2 sliders
	rc=rcMe;	
	rc.right=rc.left;
	rc.left=rc.right-27;
	slider_Left.Create(this,rc,FALSE,SLIDER_LEFT);
	rc=rcMe;	
	rc.left=rc.right;
	rc.right=rc.left+27;
	slider_Right.Create(this,rc,FALSE,SLIDER_RIGHT);

	//create horz 2 sliders
	rc=rcMe;	
	rc.bottom=rc.top;
	rc.top=rc.bottom-27;
	slider_Top.Create(this,rc,TRUE,SLIDER_TOP);
	rc=rcMe;	
	rc.top=rc.bottom;
	rc.bottom=rc.top+27;
	slider_Bottom.Create(this,rc,TRUE,SLIDER_BOTTOM);

	//set range and tick
	slider_Left.SetRange(-50,50,10);
	slider_Right.SetRange(0,100,10);
	slider_Top.SetRange(-100,100,20);
	slider_Bottom.SetRange(100,300,20);

	return 1;
}


BOOL ZDlg::OnCommand(WPARAM w, LPARAM lParam) 
{
	CString csBar;
	SliderBoth*pSlider=0;

	switch(w)
	{
	case SLIDER_LEFT:
		csBar="left";
		pSlider=&slider_Left;
		break;
	case SLIDER_RIGHT:
		csBar="right";
		pSlider=&slider_Right;
		break;
	case SLIDER_TOP:
		csBar="top";
		pSlider=&slider_Top;
		break;
	case SLIDER_BOTTOM:
		csBar="bottom";
		pSlider=&slider_Bottom;
		break;
	}

	if(pSlider)
	{
		int iPos0,iPos1;
		pSlider->GetPosition(iPos0,iPos1);
		int iMin,iMax,iTick;
		pSlider->GetRange(iMin,iMax,iTick);

		CString cs;
		cs.Format("pos: %d, %d\n\nmin=%d, max=%d, tick=%d",
					iPos0,iPos1,iMin,iMax,iTick);
		sta_Info.SetWindowText("Message from "+csBar+" slider\n\nvalues are:\n"+cs);
	}

	return CDialog::OnCommand(w, lParam);
}
