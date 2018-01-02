// EffectDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "svizres.h"
#include "EffectDlg.h"
#include "Fillpatterndlg.h"
#include "fillpicturedlg.h"
#include "fillgradientdlg.h"
#include "ColourPopupwnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectDlg dialog


/** Constructor
 * @param pParent Pointer to parent CWnd. It might be NULL
 */

CEffectDlg::CEffectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEffectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEffectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pGradientDlg=NULL;
	m_pPatternDlg=NULL;
	m_pPictureDlg=NULL;
	m_nColor = 1; //1 based
	m_nStyle = 0; //0 based
	m_hatchStyle = HatchStyleHorizontal;
	m_BrushType = BrushTypeSolidColor;
	m_nStyle = 0;
	m_linearFillMode = LinearGradientModeHorizontal;
	m_wrapMode = WrapModeTile;
	m_fileName ="";

	m_effectpage = 0x07; //default show all

}


void CEffectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEffectDlg)
	DDX_Control(pDX, IDC_SVIZ_FILLTAB, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEffectDlg, CDialog)
	//{{AFX_MSG_MAP(CEffectDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectDlg message handlers

BOOL CEffectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//create 3 tabs.

	if (m_effectpage & GRADIENTFILL){
		m_pGradientDlg = new CFillGradientDlg;
		if (m_BrushType == BrushTypeLinearGradient ||m_BrushType == BrushTypePathGradient)
			m_pGradientDlg->m_nStyle = m_nStyle;
		m_pGradientDlg->Create(IDD_SVIZ_FILL_GRADIENT, &m_Tab);
		m_Tab.AddTab(m_pGradientDlg,_T("Gradient"),0);
	}

	if (m_effectpage & PATTERNFILL){
		m_pPatternDlg = new CFillPatternDlg;
		m_pPatternDlg->Create(IDD_SVIZ_FILL_PATTERN, &m_Tab);
		m_Tab.AddTab(m_pPatternDlg,_T("Pattern"),1);
	}
	
	if (m_effectpage &PICTUREFILL){
		m_pPictureDlg = new CFillPictureDlg;
		m_pPictureDlg->Create(IDD_SVIZ_FILL_PICTURE, &m_Tab);
		m_Tab.AddTab( m_pPictureDlg,_T("Picture"),2);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEffectDlg::OnDestroy() 
{
	if (m_pGradientDlg)
		delete m_pGradientDlg;
	if (m_pPatternDlg)
		delete m_pPatternDlg;
	if (m_pPictureDlg)
		delete m_pPictureDlg;

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

/*
void CEffectDlg::OnOK() 
{
    ((CColourPopupWnd*)GetParent())->m_StartColor =m_StartColor;
	((CColourPopupWnd*)GetParent())->m_EndColor =m_EndColor;
	((CColourPopupWnd*)GetParent())->m_BrushType =m_BrushType;
	((CColourPopupWnd*)GetParent())->m_linearFillMode =m_linearFillMode;
	((CColourPopupWnd*)GetParent())->m_fileName =m_fileName;
	((CColourPopupWnd*)GetParent())->m_hatchStyle =m_hatchStyle;

	CDialog::OnOK();
}
*/
