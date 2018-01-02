/////////////////////////////////////////////////////////////////////////////
// Dialog.cpp : implementation of the CSizeDlg class
//

#include "stdafx.h"

#include "ArrayCtrl.h"
#include "MainFrm.h"
#include "Dialog.h"

#define	VAR2CTRL	FALSE
#define	CTRL2VAR	TRUE


BEGIN_MESSAGE_MAP(CSizeDlg, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO2, OnDimClicked)
	ON_EN_UPDATE(IDC_FIXVAL, OnFixedChanged)
	//{{AFX_MSG_MAP(CSizeDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CSizeDlg::OnInitDialog()
{
	int			dimtype;
	CMainFrame*	pMain = (CMainFrame*)AfxGetMainWnd();

	m_witem = pMain->m_pActCtrl->GetItemWidth();
	m_hitem = pMain->m_pActCtrl->GetItemHeight();
	m_fixval = pMain->m_pActCtrl->GetDimension(&dimtype);
	if( m_fixval == 0 )
	{
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		m_dimcheck = 0;
	}
	else
	{
		m_dimcheck = (dimtype==ACDT_COLUMNS? IDC_RADIO1: IDC_RADIO2);
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, m_dimcheck);
	}
	UpdateData(VAR2CTRL);
	return CDialog::OnInitDialog();
}

CSizeDlg::CSizeDlg() : CDialog(CSizeDlg::IDD)
{
	//{{AFX_DATA_INIT(CSizeDlg)
	m_witem = 0;
	m_hitem = 0;
	m_fixval = 0;
	m_dimcheck = 0;
	//}}AFX_DATA_INIT
}

void CSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSizeDlg)
	DDX_Text(pDX, IDC_WSIZE, m_witem);
	DDV_MinMaxInt(pDX, m_witem, 8, 512);
	DDX_Text(pDX, IDC_HSIZE, m_hitem);
	DDV_MinMaxInt(pDX, m_hitem, 8, 512);
	DDX_Text(pDX, IDC_FIXVAL, m_fixval);
	DDV_MinMaxInt(pDX, m_fixval, 0, 1024);
	//}}AFX_DATA_MAP
}

void CSizeDlg::OnDimClicked(UINT nCmdID)
{
	switch( nCmdID )
	{
	case IDC_RADIO1:
		m_dimcheck = IDC_RADIO1;
		break;
	case IDC_RADIO2:
		m_dimcheck = IDC_RADIO2;
		break;
	default:
		return;
	}
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, m_dimcheck);   
}

void CSizeDlg::OnFixedChanged()
{
	UINT		newval;

	newval = GetDlgItemInt(IDC_FIXVAL, NULL, FALSE);
	if( newval == 0 )
	{
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		m_dimcheck = 0;
		return;
	}
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
	if( m_dimcheck == 0 ) m_dimcheck = IDC_RADIO1;
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, m_dimcheck);
}

void CSizeDlg::OnOK()
{
	UpdateData(CTRL2VAR);
	CDialog::OnOK();
}


