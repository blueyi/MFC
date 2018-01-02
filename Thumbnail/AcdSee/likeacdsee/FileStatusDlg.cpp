// FileStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BigSee.h"
#include "FileStatusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileStatusDlg dialog


CFileStatusDlg::CFileStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileStatusDlg)
	m_strfilepath = _T("");
	m_strfilesize = _T("");
	//}}AFX_DATA_INIT
}


void CFileStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileStatusDlg)
	DDX_Text(pDX, IDC_STATIC_FILEPATH, m_strfilepath);
	DDX_Text(pDX, IDC_STATIC_FILESIZE, m_strfilesize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CFileStatusDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileStatusDlg message handlers

BOOL CFileStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(_T("File Attribute Dialog"));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
