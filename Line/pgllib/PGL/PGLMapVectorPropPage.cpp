// PGLMapVectorPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "pgl/PGL.h"
#include "pgl/PGLMapVectorPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLMapVectorPropPage property page

IMPLEMENT_DYNCREATE(CPGLMapVectorPropPage, CPropertyPage)

CPGLMapVectorPropPage::CPGLMapVectorPropPage(CPGLMapVector* pMapVector) : CPropertyPage(CPGLMapVectorPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPGLMapVectorPropPage)
	m_dLineWidth = 0.0;
	//}}AFX_DATA_INIT
	m_pMapVector = pMapVector;
}

CPGLMapVectorPropPage::~CPGLMapVectorPropPage()
{
}

void CPGLMapVectorPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLMapVectorPropPage)
	DDX_Text(pDX, IDC_PGL_EDIT_LINEWIDTH, m_dLineWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLMapVectorPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLMapVectorPropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLMapVectorPropPage message handlers

BOOL CPGLMapVectorPropPage::OnSetActive() 
{
	ASSERT_VALID(m_pMapVector);
	
	m_dLineWidth = m_pMapVector->GetLineWidth();

	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}

BOOL CPGLMapVectorPropPage::OnKillActive() 
{
	ASSERT_VALID(m_pMapVector);

	UpdateData(TRUE);
	
	m_pMapVector->SetLineWidth(m_dLineWidth);

	return CPropertyPage::OnKillActive();
}
