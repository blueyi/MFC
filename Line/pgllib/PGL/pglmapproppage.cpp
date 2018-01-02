// PGLMapPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/PGLMapPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLMapPropPage dialog


CPGLMapPropPage::CPGLMapPropPage(CPGLMap* pMap)
	: CPropertyPage(CPGLMapPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPGLMapPropPage)
	m_dDx = 0.0;
	m_dDy = 0.0;
	m_iNx = 0;
	m_iNxNy = 0;
	m_iNy = 0;
	m_dLeft = 0.0;
	m_dTop = 0.0;
	//}}AFX_DATA_INIT

	m_pMap=pMap;
}


void CPGLMapPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLMapPropPage)
	DDX_Text(pDX, IDC_PGL_EDIT_DX, m_dDx);
	DDX_Text(pDX, IDC_PGL_EDIT_DY, m_dDy);
	DDX_Text(pDX, IDC_PGL_EDIT_NX, m_iNx);
	DDX_Text(pDX, IDC_PGL_EDIT_NXTIMSNY, m_iNxNy);
	DDX_Text(pDX, IDC_PGL_EDIT_NY, m_iNy);
	DDX_Text(pDX, IDC_PGL_EDIT_LEFT, m_dLeft);
	DDX_Text(pDX, IDC_PGL_EDIT_TOP, m_dTop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLMapPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLMapPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLMapPropPage message handlers

BOOL CPGLMapPropPage::OnKillActive() 
{

	UpdateData(TRUE);
	// retreiving info	
	ASSERT_VALID(m_pMap);

	m_pMap->SetDx(m_dDx);
	m_pMap->SetDy(m_dDy);
	m_pMap->SetX0(m_dLeft);
	m_pMap->SetY0(m_dTop);
	
	return CPropertyPage::OnKillActive();
}

BOOL CPGLMapPropPage::OnSetActive() 
{
	ASSERT_VALID(m_pMap);
	m_iNx=m_pMap->GetNx();
	m_iNy=m_pMap->GetNy();
	m_iNxNy=m_iNx*m_iNy;

	m_dDx=m_pMap->GetDx();
	m_dDy=m_pMap->GetDy();
	m_dLeft=m_pMap->GetX0();		
	m_dTop=m_pMap->GetY0();		

	UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}
