// ObjectGLPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/PGLObjectPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLObjectPropPage property page

IMPLEMENT_DYNCREATE(CPGLObjectPropPage, CPropertyPage)

CPGLObjectPropPage::CPGLObjectPropPage(CPGLObject* _pObject) : CPropertyPage(CPGLObjectPropPage::IDD)
{
	pObject=_pObject;
	//{{AFX_DATA_INIT(CPGLObjectPropPage)
	m_selected = FALSE;
	m_visible = FALSE;
	m_name = _T("");
	m_alpha = 0.0f;
	//}}AFX_DATA_INIT
}

CPGLObjectPropPage::~CPGLObjectPropPage()
{
}

void CPGLObjectPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLObjectPropPage)
	DDX_Check(pDX, IDC_PGL_CHECK_SELECTED, m_selected);
	DDX_Check(pDX, IDC_PGL_CHECK_VISIBLE, m_visible);
	DDX_Text(pDX, IDC_PGL_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_PGL_EDIT_ALPHA, m_alpha);
	DDV_MinMaxFloat(pDX, m_alpha, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLObjectPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLObjectPropPage)
	ON_BN_CLICKED(IDC_PGL_BUTTON_CHANGE_COLOR, OnButtonChangeColor)
	ON_BN_CLICKED(IDC_PGL_CHECK_SELECTED, OnCheckSelected)
	ON_BN_CLICKED(IDC_PGL_CHECK_VISIBLE, OnCheckVisible)
	ON_EN_KILLFOCUS(IDC_PGL_EDIT_NAME, OnKillfocusEditName)
	ON_EN_KILLFOCUS(IDC_PGL_EDIT_ALPHA, OnKillfocusEditAlpha)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLObjectPropPage message handlers

void CPGLObjectPropPage::OnButtonChangeColor() 
{
	// let's create the COLORREF
	CColorDialog pColDlg;

	if (pColDlg.DoModal()==IDOK)
	{
		COLORREF col=pColDlg.GetColor();
		pObject->SetRed((float)(((col<<24)>>24)/255.0));
		pObject->SetGreen((float)(((col<<16)>>24)/255.0));
		pObject->SetBlue((float)((col>>16)/255.0));
	}
}

void CPGLObjectPropPage::OnCheckSelected() 
{
	UpdateData(TRUE);
		if (m_selected)
			pObject->Select();
		else
			pObject->Deselect();
	UpdateData(FALSE);	
}

void CPGLObjectPropPage::OnCheckVisible() 
{
	UpdateData(TRUE);
		if (m_visible)
			pObject->Show();
		else
			pObject->Hide();
	UpdateData(FALSE);	
}

void CPGLObjectPropPage::OnKillfocusEditName() 
{
	UpdateData(TRUE);
		pObject->SetName(m_name);
	UpdateData(FALSE);
}

void CPGLObjectPropPage::OnKillfocusEditAlpha() 
{
	UpdateData(TRUE);
		pObject->SetAlpha(m_alpha);
	UpdateData(FALSE);
}

BOOL CPGLObjectPropPage::OnSetActive() 
{
	m_alpha=(pObject->GetColor()).GetAlpha();
	m_name=pObject->GetName();
	m_selected=pObject->IsSelected();
	m_visible=pObject->IsVisible();

	UpdateData(FALSE);	

	return CPropertyPage::OnSetActive();
}

BOOL CPGLObjectPropPage::OnKillActive() 
{
	UpdateData(TRUE);

	pObject->SetName(m_name);
	pObject->SetAlpha(m_alpha);
	if (m_visible)
		pObject->Show();
	else
		pObject->Hide();
	
	return CPropertyPage::OnKillActive();
}
