// PGLRegionPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "pgl/pgl.h"
#include "pgl/PGLRegionPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLRegionPropPage property page

IMPLEMENT_DYNCREATE(CPGLRegionPropPage, CPropertyPage)

CPGLRegionPropPage::CPGLRegionPropPage(CPGLRegion* pRegion) : CPropertyPage(CPGLRegionPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPGLRegionPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pRegion = pRegion;
}

CPGLRegionPropPage::~CPGLRegionPropPage()
{
}

void CPGLRegionPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLRegionPropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLRegionPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLRegionPropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLRegionPropPage message handlers

BOOL CPGLRegionPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}

BOOL CPGLRegionPropPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}
