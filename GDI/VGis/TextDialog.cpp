// TextDialog.cpp : implementation file
//

#include "stdafx.h"
#include "vgis.h"
#include "TextDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDialog dialog


CTextDialog::CTextDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTextDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextDialog, CDialog)
	//{{AFX_MSG_MAP(CTextDialog)
	ON_EN_CHANGE(IDC_TEXT, OnChangeText)
	ON_BN_CLICKED(IDC_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDialog message handlers

void CTextDialog::OnOK() 
{
	// TODO: Add extra validation here
	if (m_pWnd)
		m_pWnd->PostMessage(WM_TEXT_CHANGE,(WPARAM)&m_Text,2);
	CDialog::OnOK();
}

void CTextDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (m_pWnd)
		m_pWnd->PostMessage(WM_TEXT_CHANGE,(WPARAM)&m_Text,0);
	CDialog::OnCancel();
}

void CTextDialog::OnChangeText() 
{
	this->GetData();
	if (m_pWnd)
		 m_pWnd->PostMessage(WM_TEXT_CHANGE,(WPARAM)&m_Text,1);
}


int CTextDialog::DoModal(CWnd *pWnd,float blc,CLabel &label) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pWnd=pWnd;
	m_blc=blc;
	m_Text.SetPara(label); 
	m_lf=label.m_lf;
	return CDialog::DoModal();
}

void CTextDialog::Create(CWnd *pWnd,float blc,CLabel &label)
{
	m_pWnd=pWnd;
	m_lf=label.m_lf;

	if (!this->m_hWnd)
		CDialog::Create(IDD_TEXT_DIALOG,pWnd);

	m_blc=blc;
	CString str;
	str.Format("当前%.4f",blc);
	this->SetDlgItemText(IDC_BLC,str);
	this->ShowWindow(SW_SHOW);
}

void CTextDialog::OnFont() 
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg;
	CFont font;
	if (dlg.DoModal()==IDOK)
	{
		m_lf=*dlg.m_cf.lpLogFont;
		this->GetData();
	}
}

void CTextDialog::GetData()
{
	CString str1,str2;
	this->GetDlgItemText(IDC_MIX,str1);
	this->GetDlgItemText(IDC_MAX,str2);
	this->GetDlgItemText(IDC_TEXT,m_str);
	m_Text.SetPara(0,0,(float)atof(str2),(float)atof(str1),m_lf,m_str);
}

BOOL CTextDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();


	this->SetDlgItemText(IDC_TEXT,m_Text.m_Text);
	m_lf=m_Text.m_lf;

	CString str;
	str.Format("当前%.4f",m_blc);
	this->SetDlgItemText(IDC_BLC,str);

	if (m_Text.m_MinDisp==0)
		this->SetDlgItemInt(IDC_MIX,0);
	else
	{
		str.Format("%.4f",m_Text.m_MinDisp);
		this->SetDlgItemText(IDC_MIX,str);
	}

	if (m_Text.m_MaxDisp==0)
		this->SetDlgItemInt(IDC_MAX,0);
	else
	{
		str.Format("%.4f",m_Text.m_MaxDisp);
		this->SetDlgItemText(IDC_MAX,str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
