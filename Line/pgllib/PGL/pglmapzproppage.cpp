// PGLMapZPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/PGLMapZPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLMapZPropPage property page

IMPLEMENT_DYNCREATE(CPGLMapZPropPage, CPropertyPage)

CPGLMapZPropPage::CPGLMapZPropPage(CPGLMapZ* pMap) : CPropertyPage(CPGLMapZPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPGLMapZPropPage)
	m_sCM = _T("");
	//}}AFX_DATA_INIT

	m_pMap=pMap;
}

CPGLMapZPropPage::~CPGLMapZPropPage()
{
}

void CPGLMapZPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLMapZPropPage)
	DDX_CBString(pDX, IDC_PGL_COMBO_COLORMAP, m_sCM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLMapZPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLMapZPropPage)
	ON_CBN_SELCHANGE(IDC_PGL_COMBO_COLORMAP, OnSelchangePglComboColormap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLMapZPropPage message handlers

void CPGLMapZPropPage::OnSelchangePglComboColormap() 
{
	UpdateData(TRUE);	

	m_pMap->SetColorMap(CPGLUtility::String2ColorMap(m_sCM));
}

BOOL CPGLMapZPropPage::OnSetActive() 
{

	ASSERT_VALID(m_pMap);
	
	// setting
	m_sCM=CPGLUtility::ColorMap2String(m_pMap->GetColorMap());
	UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}
