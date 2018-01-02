// FillPatternDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "svizres.h"
#include "FillPatternDlg.h"
#include "effectdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFillPatternDlg dialog
IMPLEMENT_DYNAMIC (CFillPatternDlg, CPropertyPage);


CFillPatternDlg::CFillPatternDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CFillPatternDlg::IDD)
{
	//{{AFX_DATA_INIT(CFillPatternDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_backColorCtrl.m_strEffectText="";
	m_foreColorCtrl.m_strEffectText="";
	m_backColorCtrl.m_strNoText="";
	m_foreColorCtrl.m_strNoText="";
	m_hatchbtn.m_pParent = this;
}


void CFillPatternDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFillPatternDlg)
	DDX_Control(pDX, IDC_SVIZ_HATCHWELLBTN, m_hatchbtn);
	DDX_Control(pDX, IDC_SVIZ_SAMPLE, m_sample);
	DDX_Control(pDX, IDC_SVIZ_SECOND_COLOR, m_backColorCtrl);
	DDX_Control(pDX, IDC_SVIZ_FIRST_COLOR, m_foreColorCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFillPatternDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CFillPatternDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
    ON_REGISTERED_MESSAGE(WELL_SELENDOK,     OnSelEndOK)
///	ON_REGISTERED_MESSAGE(WELL_SELENDOK,     OnSelHatchEndOK)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFillPatternDlg message handlers
LONG CFillPatternDlg::OnSelEndOK(UINT lParam, LONG wParam)
{
	DrawSample();

	UINT dlgID = wParam;

	if (dlgID == IDC_SVIZ_HATCHWELLBTN){
 		GetDlgItem(IDC_STATICNAME)->SetWindowText(m_hatchbtn.GetWellName(m_hatchbtn.m_crWell));
	}
	else{
		Color c1,c2;
		c1.SetFromCOLORREF(m_foreColorCtrl.GetColour());
		c2.SetFromCOLORREF(m_backColorCtrl.GetColour());

		m_hatchbtn.m_foreColor = c1;
		m_hatchbtn.m_backColor = c2;
		m_hatchbtn.Invalidate();
		m_hatchbtn.UpdateWindow();
	}

	SetValue();

    return TRUE;
}

LONG CFillPatternDlg::OnSelHatchEndOK(UINT lParam, LONG /*wParam*/)
{
	DrawSample();
	SetValue();
	 return TRUE;
}


void CFillPatternDlg::DrawSample()
{

	//send message to m_sample to let it redraw;
	m_sample.Invalidate();
	m_sample.UpdateWindow();

}

BOOL CFillPatternDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CEffectDlg *pDlg = (CEffectDlg *)(GetParent()->GetParent());

	m_foreColorCtrl.SetColour(pDlg->m_StartColor.ToCOLORREF());
	m_backColorCtrl.SetColour(pDlg->m_EndColor.ToCOLORREF());
	m_hatchbtn.m_crWell = (int)pDlg->m_hatchStyle;

	m_hatchbtn.m_backColor = pDlg->m_EndColor;
	m_hatchbtn.m_foreColor = pDlg->m_StartColor;


	DrawSample();	
	m_hatchbtn.SetWindowSize();
	m_hatchbtn.CreateToolTips();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


int CFillPatternDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//
//	m_hatchbtn.SetWindowSize();
	
	return 0;
}
void CFillPatternDlg::SetValue()
{
	CEffectDlg *pDlg = (CEffectDlg *)(GetParent()->GetParent());

	pDlg->m_BrushType = BrushTypeHatchFill;

	//Color is already set by the CSampleButton::DrawItem();
}

