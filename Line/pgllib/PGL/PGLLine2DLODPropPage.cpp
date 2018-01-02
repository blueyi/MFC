// PGLLine2DLODPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLLine2DLODPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLLine2DLODPropPage property page

IMPLEMENT_DYNCREATE(CPGLLine2DLODPropPage, CPropertyPage)

CPGLLine2DLODPropPage::CPGLLine2DLODPropPage(CPGLLine2DLOD* _pLine2DLOD) : CPropertyPage(CPGLLine2DLODPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPGLLine2DLODPropPage)
	m_iNbPApprox = 0;
	m_iNbPOrig = 0;
	m_dTol = 0.0;
	m_dPreview = FALSE;
	//}}AFX_DATA_INIT

	m_pLine2DLOD=_pLine2DLOD;
}

CPGLLine2DLODPropPage::~CPGLLine2DLODPropPage()
{
}

void CPGLLine2DLODPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLLine2DLODPropPage)
	DDX_Text(pDX, IDC_PGL_EDIT_NBPAPPROX, m_iNbPApprox);
	DDX_Text(pDX, IDC_PGL_EDIT_NBPORIG, m_iNbPOrig);
	DDX_Text(pDX, IDC_PGL_EDIT_TOL, m_dTol);
	DDX_Check(pDX, IDC_PGL_CHECK_PREVIEW, m_dPreview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLLine2DLODPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLLine2DLODPropPage)
	ON_EN_CHANGE(IDC_PGL_EDIT_TOL, OnChangePglEditTol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLLine2DLODPropPage message handlers

BOOL CPGLLine2DLODPropPage::OnKillActive() 
{
	UpdateData(TRUE);

	CPGLLine2DLOD::LODLine& pHull=m_pLine2DLOD->GetHull();

	// Setting tolerance
	pHull.SetTol(m_dTol);

	// Simplify
	pHull.Simplify();	
	
	return CPropertyPage::OnKillActive();
}

void CPGLLine2DLODPropPage::OnChangePglEditTol() 
{
	UpdateData(TRUE);
	if (m_dPreview)
	{

		CPGLLine2DLOD::LODLine& pHull=m_pLine2DLOD->GetHull();

		// Setting tolerance
		pHull.SetTol(m_dTol);
	
		pHull.Simplify();
		Refresh();
	}

	UpdateData(FALSE);
}

void CPGLLine2DLODPropPage::Refresh()
{
	m_iNbPOrig=m_pLine2DLOD->GetHull().GetPoints().size();
	m_iNbPApprox=m_pLine2DLOD->GetHull().GetKeys().size();
	m_dTol=m_pLine2DLOD->GetHull().GetTol();
}

BOOL CPGLLine2DLODPropPage::OnSetActive() 
{
	ASSERT(m_pLine2DLOD);
	m_dPreview=TRUE;

	Refresh();
	UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}
