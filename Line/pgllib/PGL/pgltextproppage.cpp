// PGLTextPropPage.cpp : implementation file
//

#include "StdAfx.h"
#include "PGL/PGL.h"
#include "PGL/PGLTextPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLTextPropPage property page

IMPLEMENT_DYNCREATE(CPGLTextPropPage, CPropertyPage)

CPGLTextPropPage::CPGLTextPropPage(CPGLText* _pText) : CPropertyPage(CPGLTextPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPGLTextPropPage)
	m_sText = _T("");
	m_fAngle = 0.0f;
	m_rAlign = -1;
	//}}AFX_DATA_INIT
	m_pText=_pText;
}

CPGLTextPropPage::~CPGLTextPropPage()
{
}

void CPGLTextPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLTextPropPage)
	DDX_Text(pDX, IDC_PGL_EDIT_STRIN_TEXT, m_sText);
	DDX_Text(pDX, IDC_PGL_EDIT_ANGLE, m_fAngle);
	DDX_Radio(pDX, IDC_PGL_RADIO_LEFT, m_rAlign);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLTextPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLTextPropPage)
	ON_BN_CLICKED(IDC_PGL_BUTTON_CHOOSE_FONT, OnPglButtonChooseFont)
	ON_EN_KILLFOCUS(IDC_PGL_EDIT_STRIN_TEXT, OnKillfocusPglEditStrinText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLTextPropPage message handlers

void CPGLTextPropPage::OnPglButtonChooseFont() 
{
	LOGFONT lf=m_pText->GetFont().GetLOGFONT();
	CFontDialog fontDlg(&lf);

	if (fontDlg.DoModal() == IDOK)
	{
	   fontDlg.GetCurrentFont(&lf);
	   TRACE("Face name of the selected font = %s\n", lf.lfFaceName);

		m_pText->GetFont().SetLOGFONT(lf);
	}

}

void CPGLTextPropPage::OnKillfocusPglEditStrinText() 
{
	UpdateData(TRUE);

	m_pText->SetString(m_sText);
}

BOOL CPGLTextPropPage::OnKillActive() 
{
	UpdateData(TRUE);

	m_pText->SetString(m_sText);
	m_pText->SetAngle(m_fAngle);

	switch (m_rAlign)
	{
	case 0:
		m_pText->SetAlign(PGL_TEXT_ALIGN_LEFT);
		break;
	case 1:
		m_pText->SetAlign(PGL_TEXT_ALIGN_CENTER);
		break;
	case 2:
		m_pText->SetAlign(PGL_TEXT_ALIGN_RIGHT);
		break;
	}
	
	return CPropertyPage::OnKillActive();
}

void CPGLTextPropPage::Refresh()
{
	ASSERT_VALID(m_pText);
	m_sText=m_pText->GetString();
	m_fAngle=m_pText->GetAngle();
	switch (m_pText->GetAlign())
	{
	case PGL_TEXT_ALIGN_LEFT:
		m_rAlign=0;
		break;
	case PGL_TEXT_ALIGN_CENTER:
		m_rAlign=1;
		break;
	case PGL_TEXT_ALIGN_RIGHT:
		m_rAlign=2;
		break;
	}
	
	UpdateData(FALSE);
}

BOOL CPGLTextPropPage::OnSetActive() 
{
	Refresh();
	
	return CPropertyPage::OnSetActive();
}
