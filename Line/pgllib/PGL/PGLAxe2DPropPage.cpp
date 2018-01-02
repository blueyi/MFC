// PGLAxe2DPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLAxe2DPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLAxe2DPropPage property page

IMPLEMENT_DYNCREATE(CPGLAxe2DPropPage, CPropertyPage)

CPGLAxe2DPropPage::CPGLAxe2DPropPage(CPGLAxe2D* _pAxe2D) 
: CPropertyPage(CPGLAxe2DPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPGLAxe2DPropPage)
	m_bHorGrid = FALSE;
	m_bVertGrid = FALSE;
	m_bXAuto = FALSE;
	m_dXStep = 0.0;
	m_bYAuto = FALSE;
	m_dYStep = 0.0;
	m_bBotLbl = FALSE;
	m_sBotLbl = _T("");
	m_sLeftLbl = _T("");
	m_sTopLbl = _T("");
	m_bLeftLbl = FALSE;
	m_bRightLbl = FALSE;
	m_bTopLbl = FALSE;
	m_sRightLbl = _T("");
	m_bNumberBottom = FALSE;
	m_bNumberLeft = FALSE;
	m_bNumberRight = FALSE;
	m_bNumberTop = FALSE;
	m_slNumberBottom = 0;
	m_slNumberLeft = 0;
	m_slNumberRight = 0;
	m_slNumberTop = 0;
	m_tTimeOriginH = 0;
	m_tTimeStep = 0;
	m_tTimeOrigin = 0;
	m_iDays = 0;
	m_sTimeFormat = _T("");
	m_bTimeLabel = FALSE;
	m_bLogX = FALSE;
	m_bLogY = FALSE;
	//}}AFX_DATA_INIT

	m_pAxe2D=_pAxe2D;
}

CPGLAxe2DPropPage::~CPGLAxe2DPropPage()
{
}

void CPGLAxe2DPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLAxe2DPropPage)
	DDX_Check(pDX, IDC_PGL_HORGRID_CHECK, m_bHorGrid);
	DDX_Check(pDX, IDC_PGL_VERTGRID_CHECK, m_bVertGrid);
	DDX_Check(pDX, IDC_PGL_XNUMBER_CHECK, m_bXAuto);
	DDX_Text(pDX, IDC_PGL_XNUMBER_EDIT, m_dXStep);
	DDX_Check(pDX, IDC_PGL_YNUMBER_CHECK, m_bYAuto);
	DDX_Text(pDX, IDC_PGL_YNUMBER_EDIT, m_dYStep);
	DDX_Check(pDX, IDC_PGL_BOTTOM_LABEL_CHECK, m_bBotLbl);
	DDX_Text(pDX, IDC_PGL_EDIT_BOTTOM_LABEL, m_sBotLbl);
	DDX_Text(pDX, IDC_PGL_EDIT_LEFT_LABEL, m_sLeftLbl);
	DDX_Text(pDX, IDC_PGL_EDIT_TOP_LABEL, m_sTopLbl);
	DDX_Check(pDX, IDC_PGL_LEFT_LABEL_CHECK, m_bLeftLbl);
	DDX_Check(pDX, IDC_PGL_RIGHT_LABEL_CHECK, m_bRightLbl);
	DDX_Check(pDX, IDC_PGL_TOP_LABEL_CHECK, m_bTopLbl);
	DDX_Text(pDX, IDC_PGL_EDIT_RIGHT_LABEL, m_sRightLbl);
	DDX_Check(pDX, IDC_PGL_CHECK_NUMBER_BOTTOM, m_bNumberBottom);
	DDX_Check(pDX, IDC_PGL_CHECK_NUMBER_LEFT, m_bNumberLeft);
	DDX_Check(pDX, IDC_PGL_CHECK_NUMBER_RIGHT, m_bNumberRight);
	DDX_Check(pDX, IDC_PGL_CHECK_NUMBER_TOP, m_bNumberTop);
	DDX_Slider(pDX, IDC_PGL_SLIDER_NUMBER_BOTTOM, m_slNumberBottom);
	DDX_Slider(pDX, IDC_PGL_SLIDER_NUMBER_LEFT, m_slNumberLeft);
	DDX_Slider(pDX, IDC_PGL_SLIDER_NUMBER_RIGHT, m_slNumberRight);
	DDX_Slider(pDX, IDC_PGL_SLIDER_NUMBER_TOP, m_slNumberTop);
	DDX_DateTimeCtrl(pDX, IDC_PGL_DATETIMEPICKER_TIMEORIGIN_HOUR, m_tTimeOriginH);
	DDX_DateTimeCtrl(pDX, IDC_PGL_DATETIMEPICKER_TIMESTEP_HOURS, m_tTimeStep);
	DDX_DateTimeCtrl(pDX, IDC_PGL_DATETIMEPICKER_TIMEORIGIN, m_tTimeOrigin);
	DDX_Text(pDX, IDC_PGL_EDIT_TIMESTEP_DAYS, m_iDays);
	DDX_Text(pDX, IDC_PGL_EDIT_TIMEFORMAT, m_sTimeFormat);
	DDX_Check(pDX, IDC_PGL_CHECK_TIME_LABEL, m_bTimeLabel);
	DDX_Check(pDX, IDC_PGL_CHECK_LOGX, m_bLogX);
	DDX_Check(pDX, IDC_PGL_CHECK_LOGY, m_bLogY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLAxe2DPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLAxe2DPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLAxe2DPropPage message handlers
BOOL CPGLAxe2DPropPage::OnSetActive() 
{
	ASSERT_VALID(m_pAxe2D);

	Refresh();

	return CPropertyPage::OnSetActive();
}

BOOL CPGLAxe2DPropPage::OnKillActive() 
{
	UpdateData(TRUE);

	// labels
	m_pAxe2D->SetLeftLabel(m_sLeftLbl);
	m_pAxe2D->SetRightLabel(m_sRightLbl);
	m_pAxe2D->SetBottomLabel(m_sBotLbl);
	m_pAxe2D->SetTopLabel(m_sTopLbl);

	m_pAxe2D->GetLeftLabel()->Show(m_bLeftLbl);
	m_pAxe2D->GetRightLabel()->Show(m_bRightLbl);
	m_pAxe2D->GetTopLabel()->Show(m_bTopLbl);
	m_pAxe2D->GetBottomLabel()->Show(m_bBotLbl);

	// grids
	m_pAxe2D->SetShowGrid(1,m_bHorGrid);
	m_pAxe2D->SetShowGrid(0,m_bVertGrid);

	// steps
	m_pAxe2D->SetAutoSteps(0,m_bXAuto);
	m_pAxe2D->SetAutoSteps(1,m_bYAuto);
	m_pAxe2D->SetGridStep(0,m_dXStep);	
	m_pAxe2D->SetGridStep(1,m_dYStep);	

	m_pAxe2D->SetLogAxis(0,m_bLogX);
	m_pAxe2D->SetLogAxis(1,m_bLogY);
	
	// numbering
	m_pAxe2D->GetBottomNumber()->Show(m_bNumberBottom);
	m_pAxe2D->GetTopNumber()->Show(m_bNumberTop);
	m_pAxe2D->GetLeftNumber()->Show(m_bNumberLeft);
	m_pAxe2D->GetRightNumber()->Show(m_bNumberRight);

	m_pAxe2D->SetBottomNumberPos(m_slNumberBottom/100.0);
	m_pAxe2D->SetTopNumberPos(m_slNumberTop/100.0);
	m_pAxe2D->SetLeftNumberPos(m_slNumberLeft/100.0);
	m_pAxe2D->SetRightNumberPos(m_slNumberRight/100.0);

	// time label
	m_pAxe2D->SetTimeLabel(m_bTimeLabel);
	CTime orig( m_tTimeOrigin.GetYear(), m_tTimeOrigin.GetMonth(), m_tTimeOrigin.GetDay(), 
		m_tTimeOriginH.GetHour(), m_tTimeOriginH.GetMinute(), m_tTimeOrigin.GetSecond());
	CTimeSpan step(m_iDays, m_tTimeStep.GetHour(), m_tTimeStep.GetMinute(),m_tTimeStep.GetSecond());
	m_pAxe2D->SetTimeLabelFormat(orig, step, m_sTimeFormat); 


	return CPropertyPage::OnKillActive();
}


void CPGLAxe2DPropPage::Refresh()
{
	// labels
	m_sLeftLbl = m_pAxe2D->GetLeftLabel()->GetString();
	m_sRightLbl = m_pAxe2D->GetRightLabel()->GetString();
	m_sTopLbl = m_pAxe2D->GetTopLabel()->GetString();
	m_sBotLbl = m_pAxe2D->GetBottomLabel()->GetString();

	m_bLeftLbl = m_pAxe2D->GetLeftLabel()->IsVisible();
	m_bRightLbl = m_pAxe2D->GetRightLabel()->IsVisible();
	m_bTopLbl = m_pAxe2D->GetTopLabel()->IsVisible();
	m_bBotLbl = m_pAxe2D->GetBottomLabel()->IsVisible();

	// grids
	m_bHorGrid=m_pAxe2D->IsShowGrid(1);
	m_bVertGrid=m_pAxe2D->IsShowGrid(0);

	// steps
	// auto
	m_bXAuto=m_pAxe2D->IsAutoSteps(0);
	m_bYAuto=m_pAxe2D->IsAutoSteps(1);
	m_dXStep=m_pAxe2D->GetGridStep(0);
	m_dYStep=m_pAxe2D->GetGridStep(1);

	// log
	m_bLogX = m_pAxe2D->IsLogAxis(0);
	m_bLogY = m_pAxe2D->IsLogAxis(1);

	// numbering
	m_bNumberBottom = m_pAxe2D->GetBottomNumber()->IsVisible();
	m_bNumberTop = m_pAxe2D->GetTopNumber()->IsVisible();
	m_bNumberLeft = m_pAxe2D->GetLeftNumber()->IsVisible();
	m_bNumberRight = m_pAxe2D->GetRightNumber()->IsVisible();

	m_slNumberBottom = (int)floor(m_pAxe2D->GetBottomNumberPos()*100);
	m_slNumberLeft = (int)floor(m_pAxe2D->GetLeftNumberPos()*100);
	m_slNumberTop = (int)floor(m_pAxe2D->GetTopNumberPos()*100);
	m_slNumberRight = (int)floor(m_pAxe2D->GetRightNumberPos()*100);

	// time label
	m_bTimeLabel = m_pAxe2D->IsTimeLabel();
	m_iDays = m_pAxe2D->GetTimeLabelStep().GetDays();
	m_tTimeStep = CTime( 2000, 1, 1, 
		m_pAxe2D->GetTimeLabelStep().GetHours(),
		m_pAxe2D->GetTimeLabelStep().GetMinutes(),
		m_pAxe2D->GetTimeLabelStep().GetSeconds() );
	m_tTimeOrigin = CTime( m_pAxe2D->GetTimeLabelOrig());
	m_tTimeOriginH = CTime( m_pAxe2D->GetTimeLabelOrig());

	m_sTimeFormat = m_pAxe2D->GetTimeLabelString();

	UpdateData(FALSE);
}
