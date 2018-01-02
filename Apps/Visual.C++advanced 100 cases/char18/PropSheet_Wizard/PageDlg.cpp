// PageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Propsheet Wizard.h"
#include "PageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageDlg dialog


CPageDlg::CPageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageDlg)
	m_caption = _T("");
	m_class = _T("");
	//}}AFX_DATA_INIT
	m_bClassChanged = FALSE;
}


void CPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageDlg)
	DDX_Control(pDX, IDC_EDIT_CLASS, m_ctrlClass);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_caption);
	DDX_Text(pDX, IDC_EDIT_CLASS, m_class);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageDlg, CDialog)
	//{{AFX_MSG_MAP(CPageDlg)
	ON_EN_CHANGE(IDC_EDIT_CAPTION, OnChangeEditCaption)
	ON_EN_CHANGE(IDC_EDIT_CLASS, OnChangeEditClass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageDlg message handlers

void CPageDlg::OnChangeEditCaption() 
{
	if (!m_bClassChanged)
	{
		UpdateData ();
		m_class = _T ("C") + ToSafeName (m_caption);
		UpdateData (FALSE);
	}
	UpdateOk ();
}

void CPageDlg::OnChangeEditClass() 
{
	if (CWnd::GetFocus () == &m_ctrlClass)
		m_bClassChanged = TRUE;
	UpdateOk ();
}

void CPageDlg::OnOK() 
{
	if (m_caption.IsEmpty () || m_class.IsEmpty ())
		return;
	for (int i = 0;i < m_class.GetLength ();i++)
		if (!isalnum (m_class[i]) && m_class[i] != '_')
			return;
	
	CDialog::OnOK();
}

void CPageDlg::UpdateOk ()
{
	UpdateData ();
	BOOL bValidClass = TRUE;
	for (int i = 0;i < m_class.GetLength ();i++)
		if (!isalnum (m_class[i]) && m_class[i] != '_')
		{
			bValidClass = FALSE;
			break;
		}
	m_ok.EnableWindow (!m_caption.IsEmpty () && !m_class.IsEmpty () && bValidClass);
}

BOOL CPageDlg::PreTranslateMessage(MSG* pMsg)
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CPageDlg::OnInitDialog()
{
	m_bClassChanged = (m_class != _T ("C") + ToSafeName (m_caption)) && m_class.GetLength () != 0;

	CDialog::OnInitDialog();

	// Create the ToolTip control.
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);

	// TODO: Use one of the following forms to add controls:
	m_tooltip.AddTool (GetDlgItem (IDC_EDIT_CAPTION), IDS_PAGEDLG_EDIT_CAPTION_TIP);
	m_tooltip.AddTool (GetDlgItem (IDC_EDIT_CLASS), IDS_PAGEDLG_EDIT_CLASS_TIP);

	UpdateOk ();

	return TRUE;
}

CString CPageDlg::ToSafeName (LPCTSTR lpszName)
{
	CString res = _T ("");
	BOOL bSpace = TRUE;
	for (int i = 0;lpszName[i];i++)
	{
		if (isalnum (lpszName[i]) || lpszName[i] == '_')
		{
			if (bSpace)
			{
				res += (CString)/*toupper*/(lpszName[i]);
				bSpace = FALSE;
			}
			else
				res += lpszName[i];
		}
		else
			if (isspace (lpszName[i]))
				bSpace = TRUE;
	}
	return (res);
}
