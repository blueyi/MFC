// CategoryNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFC.h"
#include "CategoryNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategoryNameDlg dialog


CCategoryNameDlg::CCategoryNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCategoryNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCategoryNameDlg)
	m_categoryName = _T("");
	//}}AFX_DATA_INIT
}


void CCategoryNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCategoryNameDlg)
	DDX_Text(pDX, IDC_EDIT1, m_categoryName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCategoryNameDlg, CDialog)
	//{{AFX_MSG_MAP(CCategoryNameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCategoryNameDlg message handlers

CString CCategoryNameDlg::GetName()
{
	return m_categoryName;
}
