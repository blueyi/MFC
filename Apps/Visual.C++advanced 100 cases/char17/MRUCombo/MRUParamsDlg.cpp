// MRUParamsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MRUComboTest.h"
#include "MRUParamsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRUParamsDlg dialog


CMRUParamsDlg::CMRUParamsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMRUParamsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMRUParamsDlg)
	m_nMRUSize = 0;
	m_cstrRegKey = _T("");
	m_cstrRegValue = _T("");
	//}}AFX_DATA_INIT
}


void CMRUParamsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMRUParamsDlg)
	DDX_Control(pDX, IDC_SPIN1, m_spinner);
	DDX_Text(pDX, IDC_MRU_SIZE, m_nMRUSize);
	DDV_MinMaxInt(pDX, m_nMRUSize, 1, 16);
	DDX_Text(pDX, IDC_REG_KEY, m_cstrRegKey);
	DDX_Text(pDX, IDC_REG_VALUE, m_cstrRegValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMRUParamsDlg, CDialog)
	//{{AFX_MSG_MAP(CMRUParamsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMRUParamsDlg message handlers

BOOL CMRUParamsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_spinner.SetRange ( 1, 16 );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
