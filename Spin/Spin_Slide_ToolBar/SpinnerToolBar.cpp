// SpinToolBar.cpp : implementation file
//


/*##################################################################

  Author:	Masoud Samimi
  Website:	www.geocities.com/samimi73
  Email:	marcello43@hotmail.com

  Program:	Spinner Toolbars
  History:	22.07.2000 (dd.mm.yy)
  
  Purpose: Please visit my website, it is expalined there.
  

Important Notice:

	This Idea and the Application is Copyright(c) Masoud Samimi 1999,2000.
	You can freely use it as long as you credit me for it.

	No guarantee/warantee, expressed or implied is given on this app and I will not be responsible 
	for any damage to you, your property or any other person from using it.
	USE IT ON YOUR OWN RISK.

	Thankyou and have FUNNE =-)

	Masoud Samimi.

##################################################################*/

#include "stdafx.h"
#include "SpinnerTB.h"
#include "SpinnerToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpinToolBar

CSpinToolBar::CSpinToolBar()
{

	m_nRed		= 255;
	m_nGreen	= 255;
	m_nBlue		= 0;

	m_nGradValue = 255;
		
}

CSpinToolBar::~CSpinToolBar()
{
}


BEGIN_MESSAGE_MAP(CSpinToolBar, CToolBar)
	//{{AFX_MSG_MAP(CSpinToolBar)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpinToolBar message handlers

int CSpinToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;


	//##################################################//
    // Load the dummy buttons toolbar.
	//
    if (!LoadToolBar (IDR_SPINNER_BAR))
        return -1;



	//##################################################//
	// Spinner Toolbar button modifying method 

	
	// DC to select font into
	CClientDC dc(this);
	
	
	// CFont object used to set the desired control fonts

	m_font.CreatePointFont (100, _T ("MS Sans Serif"));
    CFont* pOldFont = dc.SelectObject (&m_font);


	// TEXTMETRIC is Useful to measure and place the controls
	// in the desired positions

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	int cxChar = tm.tmAveCharWidth;
	int cyChar = tm.tmHeight + tm.tmExternalLeading;

	dc.SelectObject (pOldFont);


    CRect rect;

	//################# Red set of spinners #################

	// Edit Red //

    SetButtonInfo (0, ID_EDIT_R, TBBS_SEPARATOR , cxChar * 8);
	GetItemRect (0, &rect);
    rect.bottom = rect.top + (cyChar + 6);
	
	if(!m_wndEdit_r.CreateEx(WS_EX_CLIENTEDGE, // Make a 3D-border
      _T("EDIT"), NULL,
     WS_TABSTOP | ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD,
      rect, this, ID_EDIT_R))

	return -1;
	
	// Spinner Red //

	m_wndEdit_r.SetFont (&m_font);

	SetButtonInfo (1, ID_SPIN_R, TBBS_SEPARATOR, cxChar * 3);
	GetItemRect (1, &rect);
    rect.bottom = rect.top + (cyChar + 6);

	
	if (!m_wndSpin_r.Create(WS_CHILD | WS_VISIBLE | // dwStyle
						UDS_ALIGNRIGHT | UDS_SETBUDDYINT | UDS_ARROWKEYS,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SPIN_R))		// UINT  nID
	
	
	return -1;
	
	m_wndSpin_r.SetFont (&m_font);


	//################# Green set of spinners #################

	// Edit Green //

	SetButtonInfo (2, ID_EDIT_G, TBBS_SEPARATOR , cxChar * 8);
	GetItemRect (2, &rect);
    rect.bottom = rect.top + (cyChar + 6);
	
	if(!m_wndEdit_g.CreateEx(WS_EX_CLIENTEDGE, // Make a 3D-border
      _T("EDIT"), NULL,
     WS_TABSTOP |  ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD,
      rect, this, ID_EDIT_G))

	return -1;

	m_wndEdit_g.SetFont (&m_font);

	
	// Spinner Green //

	SetButtonInfo (3, ID_SPIN_G, TBBS_SEPARATOR, cxChar * 3);
	GetItemRect (3, &rect);
    rect.bottom = rect.top + (cyChar + 6);

	
	if (!m_wndSpin_g.Create(WS_CHILD | WS_VISIBLE | // dwStyle
						UDS_ALIGNRIGHT | UDS_SETBUDDYINT | UDS_ARROWKEYS,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SPIN_G))		// UINT  nID
	
	
	return -1;
	
	m_wndSpin_g.SetFont (&m_font);



	//################# Blue set of spinners #################

	// Edit Blue //

	SetButtonInfo (4, ID_EDIT_B, TBBS_SEPARATOR , cxChar * 8);
	GetItemRect (4, &rect);
    rect.bottom = rect.top + (cyChar + 6);

	if(!m_wndEdit_b.CreateEx(WS_EX_CLIENTEDGE, // Make a 3D-border
      _T("EDIT"), NULL,
      WS_TABSTOP | ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD,
      rect, this, ID_EDIT_B))

	return -1;


	m_wndEdit_b.SetFont (&m_font);

	
	// Spinner Blue //

	SetButtonInfo (5, ID_SPIN_B, TBBS_SEPARATOR, cxChar * 3);
	GetItemRect (5, &rect);
    rect.bottom = rect.top + (cyChar + 6);

	
	if (!m_wndSpin_b.Create(WS_CHILD | WS_VISIBLE | // dwStyle
						UDS_ALIGNRIGHT | UDS_SETBUDDYINT | UDS_ARROWKEYS,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SPIN_B))		// UINT  nID
	
	return -1;

	m_wndSpin_b.SetFont (&m_font);


	//################# Slider/Edit set #################

	SetButtonInfo (6, ID_EDIT_SLD, TBBS_SEPARATOR , cxChar * 8);
	GetItemRect (6, &rect);
    rect.bottom = rect.top + (cyChar + 6);
	
	if(!m_wndEdit_sld.CreateEx(WS_EX_CLIENTEDGE, // Make a 3D-border
      _T("EDIT"), NULL,
      //WS_TABSTOP |
	  ES_READONLY | ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD,
      rect, this, ID_EDIT_SLD))

	return -1;


	m_wndEdit_sld.SetFont (&m_font);

	SetButtonInfo (7, ID_SLIDER, TBBS_SEPARATOR, cxChar * 12);
	GetItemRect (7, &rect);
    rect.bottom = rect.top + (cyChar + 2);

	
	if (!m_wndSlider.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |// dwStyle
						TBS_HORZ | TBS_AUTOTICKS |
						//TBS_NOTICKS |
						TBS_BOTTOM,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SLIDER))		// UINT  nID
	
	return -1;

	
	
	// Not required to be visible, so we hide it by not using//
	// the WS_VISIBLE style bit //

	if (!m_wndSpin_sld.Create(WS_CHILD | // dwStyle
						UDS_SETBUDDYINT,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SPIN_SLD))		// UINT  nID
	
	return -1;


	// Set the edit box default numbers

	SetPositions();


	return 0;

}


void CSpinToolBar::SetPositions()
{
	

	// Set Red Spinner and Edit box value is OK

	m_wndSpin_r.SetRange(0, 255);
	m_wndSpin_r.SetBuddy(&m_wndEdit_r);
	m_wndSpin_r.SetPos(m_nRed);

	
	// Set Green Spinner and Edit box value is OK

	m_wndSpin_g.SetRange(0, 255);
	m_wndSpin_g.SetBuddy(&m_wndEdit_g);
	m_wndSpin_g.SetPos(m_nGreen);
	
	
	// Set Blue Spinner and Edit box value is OK

	m_wndSpin_b.SetRange(0, 255);
	m_wndSpin_b.SetBuddy(&m_wndEdit_b);
	m_wndSpin_b.SetPos(m_nBlue);

	
	// Set Slider, Invisible Spinner and Edit box value is OK
	
	m_wndSlider.SetRange(0, 255);
	m_wndSpin_sld.SetRange(0, 255);
	
	m_wndSpin_sld.SetBuddy(&m_wndEdit_sld);
	
	m_wndSlider.SetPos(m_nGradValue);
	m_wndSpin_sld.SetPos(m_wndSlider.GetPos());


}

void CSpinToolBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
		
	CSliderCtrl* m_wndSlider = (CSliderCtrl*) pScrollBar;
	m_wndSpin_sld.SetPos(m_wndSlider->GetPos());

	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_SLIDER); 
	::SetCursor(hCursor);
	
	CToolBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSpinToolBar::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
	CSpinButtonCtrl* m_wndSpin_r = (CSpinButtonCtrl*) pScrollBar;
	CSpinButtonCtrl* m_wndSpin_g = (CSpinButtonCtrl*) pScrollBar;
	CSpinButtonCtrl* m_wndSpin_b = (CSpinButtonCtrl*) pScrollBar;

	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_SPINNER); 
	::SetCursor(hCursor);	

	CToolBar::OnVScroll(nSBCode, nPos, pScrollBar);
}
