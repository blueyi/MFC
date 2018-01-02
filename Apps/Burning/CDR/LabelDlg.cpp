// LabelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDR.h"
#include "LabelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabelDlg dialog


CLabelDlg::CLabelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLabelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLabelDlg)
	m_label = _T("");
	m_hint = _T("");
	//}}AFX_DATA_INIT
}


void CLabelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLabelDlg)
	DDX_Text(pDX, IDC_EDIT1, m_label);
	DDV_MaxChars(pDX, m_label, 15);
	DDX_Text(pDX, IDC_HINT, m_hint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLabelDlg, CDialog)
	//{{AFX_MSG_MAP(CLabelDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabelDlg message handlers
