// DlgContourLine.cpp : implementation file
//

#include "stdafx.h"
#include "DlgContourLine.h"
#include "Commands.h"
#include "Viewer2D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgContourLine dialog


CDlgContourLine::CDlgContourLine(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgContourLine::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgContourLine)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pView=NULL;
	m_bLargest=FALSE;

}

void CDlgContourLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgContourLine)
	DDX_Control(pDX, IDC_STATIC_COLOR, m_ctrlContour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgContourLine, CDialog)
	//{{AFX_MSG_MAP(CDlgContourLine)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_LARGEST, OnCheckLargest)
	ON_BN_CLICKED(IDC_BUTTON_MESH, OnButtonMesh)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgContourLine message handlers

BOOL CDlgContourLine::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, TRUE);			// Set big icon
	SetIcon(hIcon, FALSE);		// Set small icon

	m_ctrlContour.m_iMode=1;
	m_ctrlContour.SetPixelRange(0,4096);
	m_ctrlContour.m_grayHistogram=NULL;
	m_ctrlContour.DrawLine();

	m_srDlg.Create(IDD_IMAGE_SR_FRAME,NULL);
	m_srDlg.ShowWindow(FALSE);
	int x=GetSystemMetrics(SM_CXSCREEN);
	int y=GetSystemMetrics(SM_CYSCREEN);
	int width=700;
	int height=500;
	m_srDlg.MoveWindow((x-width)/2,(y-height)/2,width,height);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgContourLine::SendCommand(int nCmdID,CString sPara)
{
	if(m_pView)
	{
		m_pView->SendMessage(WM_CALL_COMMAND,WPARAM(nCmdID),LPARAM(&sPara));
	}
}


BOOL CDlgContourLine::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	int iResult=*((int *)wParam);
	IA_PIXEL_ITEM item;

	if(iResult==10 || iResult==20)
	{
		item = *((IA_PIXEL_ITEM *)lParam);
	}
	CString sTmp;

	if(iResult==20) //color map
	{
		sTmp.Format("%i",item.pixel);
		GetDlgItem(IDC_EDIT_COLOR_PIXEL)->SetWindowText(sTmp);
		
		int iCount=m_ctrlContour.m_itemList.GetCount();
		m_contourList.RemoveAll();
		POSITION pos=m_ctrlContour.m_itemList.GetHeadPosition();
		while(pos)
		{
			item=m_ctrlContour.m_itemList.GetNext(pos);
			m_contourList.AddTail(item);
		}
		

	}

	if(iResult==21) //Update color map
	{
		OnBtnUpdate();
	}

	
	return TRUE; //CDialog::OnNotify(wParam, lParam, pResult);
}

void CDlgContourLine::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	CString sTmp;
	SendCommand(CMD_UPDATECONTOURIMAGE,sTmp);
}


void CDlgContourLine::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CString sTmp;
	SendCommand(CMD_CLEARCONTOUR,sTmp);
	CDialog::OnClose();
}

void CDlgContourLine::OnCheckLargest() 
{
	// TODO: Add your control notification handler code here
	if(m_bLargest)
	{
		m_bLargest=FALSE;
	}else
	{
		m_bLargest=TRUE;
	}

	OnBtnUpdate();
}

BOOL CDlgContourLine::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN){   
		switch(pMsg->wParam){   
		case   VK_ESCAPE:   
			 return   TRUE;   
			 break;
		case VK_RETURN:
			return TRUE;
			break;
		}   
	}   
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgContourLine::OnButtonMesh() 
{
	// TODO: Add your control notification handler code here
	if(m_pView==NULL)
		return;

	vtkImageData *pImage=((C2DViewer*)m_pView)->GetSeries();
	if(pImage==NULL)
		return;

	MESH_OPTIONS option;
	IA_PIXEL_ITEM item;
	int count=0;

	m_srDlg.ClearMesh();

	count=m_contourList.GetCount();
	for(int i=1;i<count-1;i++)
	{
		item=m_contourList.GetAt(m_contourList.FindIndex(i));
		option.label=item.pixel;
		option.color=item.color;
		m_srDlg.AddMesh(pImage,option);
	}

	m_srDlg.ShowWindow(TRUE);
}

void CDlgContourLine::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_ctrlContour.GetSafeHwnd())
		return;
	int iTop=50;
	GetDlgItem(IDC_STATIC_PIXEL)->MoveWindow(cx-100,iTop,50,17);
	GetDlgItem(IDC_EDIT_COLOR_PIXEL)->MoveWindow(cx-50,iTop,48,17);
	m_ctrlContour.MoveWindow(2,iTop+20,cx-4,cy-iTop-22);
}
