// Line2DGLPage.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/PGLLine2DPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLLine2DPropPage property page

IMPLEMENT_DYNCREATE(CPGLLine2DPropPage, CPropertyPage)

CPGLLine2DPropPage::CPGLLine2DPropPage(CPGLLine2D* _pLine2D) : CPropertyPage(CPGLLine2DPropPage::IDD)
{
	m_pLine2D=_pLine2D;
	//{{AFX_DATA_INIT(CPGLLine2DPropPage)
	m_nPoints = 0;
	m_bShowEnd = FALSE;
	m_bShowStart = FALSE;
	m_dLengthEnd = 0.0;
	m_dThickEnd = 0.0;
	m_dLengthStart = 0.0;
	m_dThickStart = 0.0;
	m_bFill = FALSE;
	//}}AFX_DATA_INIT
}

CPGLLine2DPropPage::~CPGLLine2DPropPage()
{
}

void CPGLLine2DPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLLine2DPropPage)
	DDX_Text(pDX, IDC_PGL_EDIT_NPOINTS, m_nPoints);
	DDX_Check(pDX, IDC_PGL_CHECK_END_ARROW_SHOW, m_bShowEnd);
	DDX_Check(pDX, IDC_PGL_CHECK_START_ARROW_SHOW, m_bShowStart);
	DDX_Text(pDX, IDC_PGL_EDIT_END_ARROW_LENGTH, m_dLengthEnd);
	DDX_Text(pDX, IDC_PGL_EDIT_END_ARROW_THICK, m_dThickEnd);
	DDX_Text(pDX, IDC_PGL_EDIT_START_ARROW_LENGTH, m_dLengthStart);
	DDX_Text(pDX, IDC_PGL_EDIT_START_ARROW_THICK, m_dThickStart);
	DDX_Check(pDX, IDC_PGL_CHECK_FILL, m_bFill);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLLine2DPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLLine2DPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLLine2DPropPage message handlers

BOOL CPGLLine2DPropPage::OnKillActive() 
{
	UpdateData(TRUE);
	ASSERT_VALID(m_pLine2D);

	m_pLine2D->ShowStartArrow(m_bShowStart);
	m_pLine2D->ShowEndArrow(m_bShowEnd);

	m_pLine2D->SetStartArrowLength(m_dLengthStart);
	m_pLine2D->SetEndArrowLength(m_dLengthEnd);

	m_pLine2D->SetStartArrowThick(m_dThickStart);
	m_pLine2D->SetEndArrowThick(m_dThickEnd);

	m_pLine2D->SetFilled(m_bFill);

	return CPropertyPage::OnKillActive();
}

BOOL CPGLLine2DPropPage::OnSetActive() 
{

	ASSERT_VALID(m_pLine2D);
	m_nPoints=m_pLine2D->GetNPoints();

	m_bShowStart=m_pLine2D->IsStartArrow();
	m_bShowEnd=m_pLine2D->IsEndArrow();

	m_dLengthStart=m_pLine2D->GetStartArrowLength();
	m_dLengthEnd=m_pLine2D->GetEndArrowLength();
	m_dThickStart=m_pLine2D->GetStartArrowThick();
	m_dThickEnd=m_pLine2D->GetEndArrowThick();

	m_bFill = m_pLine2D->IsFilled();

	UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}
