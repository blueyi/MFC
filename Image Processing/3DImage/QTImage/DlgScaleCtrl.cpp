// DlgScaleCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "qtimage.h"
#include "DlgScaleCtrl.h"
#include "vvPluginApi.h"
#include "globalHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScaleCtrl dialog


CDlgScaleCtrl::CDlgScaleCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScaleCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgScaleCtrl)
	//}}AFX_DATA_INIT
	m_min=(float)0.1;
	m_max=(float)0.2;

	m_iLastPos=0;
}


void CDlgScaleCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScaleCtrl)
	DDX_Control(pDX, IDC_EDIT_VALUE, m_value);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_caption);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScaleCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgScaleCtrl)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_WM_SIZE()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScaleCtrl message handlers

BOOL CDlgScaleCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgScaleCtrl::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int i=m_slider.GetPos();
	if(i==m_iLastPos)
	{
		return;
	}
	m_iLastPos=i;

	m_fCurSlice=i*m_step+m_min;
	if(m_fCurSlice>m_max)
		m_fCurSlice=m_max;

	CString sTmp;
	sTmp.Format("%f",m_fCurSlice);
	while((sTmp.Find(".",0)>=0 && sTmp.Right(1)=="0")||sTmp.Right(1)==".")
	{
		sTmp=sTmp.Left(sTmp.GetLength()-1);
	}
	if(sTmp=="")
		sTmp="0";

	m_value.SetWindowText(sTmp);

	
	
}

void CDlgScaleCtrl::SetGUIProperty(int property, const char *value)
{
	

	CString sTmp;
	sTmp.Format("%s",value);
	int iFind;

	switch(property)
	{
	case VVP_GUI_TYPE:
		if(sTmp!=VVP_GUI_SCALE&&sTmp!=VVP_GUI_CHECKBOX)
		{
			MessageBox("SetGUIProperty error");
			return;
		}
		m_ctrlType=sTmp;
		break;
	case VVP_GUI_LABEL:
		m_sSliderTxt=sTmp;
		break;
	case VVP_GUI_DEFAULT:
		m_fCurSlice=(float)atof(value);
		
		break;
	case VVP_GUI_HELP:
		m_sHelp=sTmp;
		break;
	case VVP_GUI_HINTS:
		sTmp.TrimLeft();
		sTmp.TrimRight();
		iFind=sTmp.Find(" ",0);
		if(iFind>0)
		{
			m_min=(float)atof(sTmp.Left(iFind));
			sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);
			sTmp.TrimLeft();
			sTmp.TrimRight();
		}else
		{
			MessageBox("CDlgScaleCtrl::SetGUIProperty error");
			return;
		}
		iFind=sTmp.Find(" ",0);
		if(iFind>0)
		{
			m_max=(float)atof(sTmp.Left(iFind));
			sTmp=sTmp.Right(sTmp.GetLength()-iFind-1);
			sTmp.TrimLeft();
			sTmp.TrimRight();
		}else
		{
			MessageBox("CDlgScaleCtrl::SetGUIProperty error");
			return;
		}
		m_step=(float)atof(sTmp);
		m_iMin=0;
		m_iMax=(int)((m_max-m_min)/m_step);
		break;
	default:
		MessageBox("CDlgScaleCtrl::error");
	}
}

char *CDlgScaleCtrl::GetGUIProperty(int property)
{
	CString sTmp;
	if(property==VVP_GUI_VALUE)
	{
		m_value.GetWindowText(sTmp);
		sprintf(m_sValue,"%s",sTmp);
	}else
	{
		AfxMessageBox("GetGUIProperty error");
	}
	return m_sValue;
}

BOOL CDlgScaleCtrl::PreTranslateMessage(MSG* pMsg) 
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

void CDlgScaleCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	int iEditWidth=50;
	int iHeight=20;
	// TODO: Add your message handler code here
	if(m_slider.GetSafeHwnd())
	{
		CRect rs;
		GetClientRect(rs);
		
		m_caption.MoveWindow(5,2,rs.Width()-iEditWidth-12,iHeight);
		m_value.MoveWindow(rs.Width()-iEditWidth-5,2,iEditWidth-1,iHeight);

		m_slider.MoveWindow(5,iHeight+7,rs.Width()-10,cy-iHeight-9);
	}
}

void CDlgScaleCtrl::RefreshCtrl()
{
	CString sTmp;
	int i;
	CString sMin,sMax;
	sMin.Format("%f",m_min);
	while((sMin.Find(".",0)>=0 && sMin.Right(1)=="0")||sMin.Right(1)==".")
	{
		sMin=sMin.Left(sMin.GetLength()-1);
	}
	if(sMin=="")
		sMin="0";
	sMax.Format("%f",m_max);
	while((sMax.Find(".",0)>=0 && sMax.Right(1)=="0")||sMax.Right(1)==".")
	{
		sMax=sMax.Left(sMax.GetLength()-1);
	}

	sTmp.Format("%s(%s,%s)",m_sSliderTxt,sMin,sMax);
	m_caption.SetWindowText(sTmp);

	m_slider.SetRange(m_iMin,m_iMax);
	i=(int)((m_fCurSlice-m_min)/m_step);
	if(i<m_iMin)
		i=m_iMin;
	if(i>m_iMax)
		i=m_iMax;
	m_slider.SetPos(i);
	m_slider.SetPageSize(1);
}

void CDlgScaleCtrl::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWnd *pParent=GetParent();
	pParent->SendMessage(WM_INTIME_SEGMENTED);

	*pResult = 0;
}
