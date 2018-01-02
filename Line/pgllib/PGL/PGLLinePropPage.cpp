// LineGLPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/PGLLinePropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLLinePropPage property page

IMPLEMENT_DYNCREATE(CPGLLinePropPage, CPropertyPage)

CPGLLinePropPage::CPGLLinePropPage(CPGLLine* _pLine) : CPropertyPage(CPGLLinePropPage::IDD)
{
	m_pLine=_pLine;
	//{{AFX_DATA_INIT(CPGLLinePropPage)
	m_lineWidth = 0.0f;
	m_pointWidth = 0.0f;
	m_lineType = -1;
	m_pointType = -1;
	m_iInterpolationType = -1;
	m_iStripSize = 0;
	m_bFilled = FALSE;
	//}}AFX_DATA_INIT
}

CPGLLinePropPage::~CPGLLinePropPage()
{
}

void CPGLLinePropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLLinePropPage)
	DDX_Text(pDX, IDC_PGL_EDIT_LINE_WIDTH, m_lineWidth);
	DDV_MinMaxFloat(pDX, m_lineWidth, 1.e-002f, 100.f);
	DDX_Text(pDX, IDC_PGL_EDIT_POINT_WIDTH, m_pointWidth);
	DDV_MinMaxFloat(pDX, m_pointWidth, 0.01f, 100.f);
	DDX_Radio(pDX, IDC_PGL_RADIO_LINE_NONE, m_lineType);
	DDX_Radio(pDX, IDC_PGL_RADIO_POINT_NONE, m_pointType);
	DDX_Radio(pDX, IDC_PGL_RADIO_INTERPOLATION_STEP, m_iInterpolationType);
	DDX_Text(pDX, IDC_EDIT_STRIP_SIZE, m_iStripSize);
	DDX_Check(pDX, IDC_PGL_CHECK_FILL, m_bFilled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLLinePropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPGLLinePropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CPGLLinePropPage::OnKillActive() 
{
	UpdateData(TRUE);

	m_pLine->SetFilled(m_bFilled);
	m_pLine->SetStripSize(m_iStripSize);

	// radio buttons
	switch(m_iInterpolationType)
	{
	case 0: 
		m_pLine->SetInterpolationType(PGL_INTERPOLATION_STEP); 
		break;
	case 1: 
		m_pLine->SetInterpolationType(PGL_INTERPOLATION_LINEAR); 
		break;
	case 2:
		m_pLine->SetInterpolationType(PGL_INTERPOLATION_SEGMENT); 
		break;
	}

	switch(m_lineType)
	{
	case 0:
		m_pLine->SetLineType(PGL_LINE_NONE); 
		break;
	case 1:
		m_pLine->SetLineType(PGL_LINE_CONT); 
		break;
	case 2:
		m_pLine->SetLineType(PGL_LINE_BARBAR); 
		break;
	case 3:
		m_pLine->SetLineType(PGL_LINE_BARPOINT); 
		break;
	case 4:
		m_pLine->SetLineType(PGL_LINE_POINTPOINT); 
		break;
	}

	switch(m_pointType)
	{
	case 0:
		m_pLine->SetPointType(PGL_POINT_NONE);
		break;
	case 1:
		m_pLine->SetPointType(PGL_POINT_SIMPLE);
		break;
	case 2:
		m_pLine->SetPointType(PGL_POINT_CONTOUR);
		break;
	case 3:
		m_pLine->SetPointType(PGL_POINT_TRIANGLE);
		break;
	case 4:
		m_pLine->SetPointType(PGL_POINT_SQUARE);
		break;
	}

	m_pLine->SetPointWidth(m_pointWidth);
	m_pLine->SetLineWidth(m_lineWidth);
	
	return CPropertyPage::OnKillActive();
}

BOOL CPGLLinePropPage::OnSetActive() 
{
	ASSERT_VALID(m_pLine);

	m_bFilled = m_pLine->IsFilled();

	m_lineWidth=m_pLine->GetLineWidth();
	m_pointWidth=m_pLine->GetPointWidth();
	m_iStripSize = m_pLine->GetStripSize();


	// radio buttons
	switch(m_pLine->GetInterpolationType())
	{
	case PGL_INTERPOLATION_STEP: 
		m_iInterpolationType=0; 
		break;
	case PGL_INTERPOLATION_LINEAR: 
		m_iInterpolationType=1; 
		break;
	case PGL_INTERPOLATION_SEGMENT:
		m_iInterpolationType=2; 
		break;
	}

	switch(m_pLine->GetLineType())
	{
	case PGL_LINE_NONE:
		m_lineType=0; break;
	case PGL_LINE_CONT:
		m_lineType=1; break;
	case PGL_LINE_BARBAR:
		m_lineType=2; break;
	case PGL_LINE_BARPOINT:
		m_lineType=3; break;
	case PGL_LINE_POINTPOINT:
		m_lineType=4; break;
	}

	switch(m_pLine->GetPointType())
	{
	case PGL_POINT_NONE:
		m_pointType=0; break;
	case PGL_POINT_SIMPLE:
		m_pointType=1; break;
	case PGL_POINT_CONTOUR:
		m_pointType=2; break;
	case PGL_POINT_TRIANGLE:
		m_pointType=3; break;
	case PGL_POINT_SQUARE:
		m_pointType=4; break;
	}

	UpdateData(FALSE);
	
	return CPropertyPage::OnSetActive();
}
