/*##################################################################

  Author:	Masoud Samimi
  Website:	www.geocities.com/samimi73
  Email:	marcello43@hotmail.com

  Program:	Spinners Toolbar
  History:	05.01.1999 (dd.mm.yy)
  
  Purpose: Please visit my website, it is expalined there.
  

Important Notice:

	This Method and the Application is Copyright(c) Masoud Samimi 1999,2000.
	You can freely use it as long as you credit me for it.

	No guarantee/warantee, expressed or implied is given on this app and I will not be responsible 
	for any damage to you, your property or any other person from using it.
	USE IT ON YOUR OWN RISK.

	Thankyou and have FUNNE =-)

	Masoud Samimi.

##################################################################*/
// SlideToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "SpinnerTB.h"
#include "SlideToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlideToolBar

CSlideToolBar::CSlideToolBar()
{
	
	m_nRotation[0] = 10;
	m_nRotation[1] = 100;
	m_nRotation[2] = -100;

	
}

CSlideToolBar::~CSlideToolBar()
{
}


BEGIN_MESSAGE_MAP(CSlideToolBar, CToolBar)
	//{{AFX_MSG_MAP(CSlideToolBar)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlideToolBar message handlers

int CSlideToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//##################################################//
    // Load the dummy buttons toolbar.
	//
    if (!LoadToolBar (IDR_SLIDER_BAR))
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

	//################# Rot X Slider/Edit set #################

	SetButtonInfo (0, ID_EDIT_ROTX, TBBS_SEPARATOR , cxChar * 8);
	GetItemRect (0, &rect);
    rect.bottom = rect.top + (cyChar + 6);
	
	if(!m_wndEdit_Rot_X.CreateEx(WS_EX_CLIENTEDGE, // Make a 3D-border
      _T("EDIT"), NULL,
      //WS_TABSTOP |
	  ES_READONLY | ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD,
      rect, this, ID_EDIT_ROTX))

	return -1;


	m_wndEdit_Rot_X.SetFont (&m_font);

	SetButtonInfo (1, ID_SLIDE_ROTX, TBBS_SEPARATOR, cxChar * 12);
	GetItemRect (1, &rect);
    rect.bottom = rect.top + (cyChar + 2);

	
	if (!m_wndSlider_Rot_X.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |// dwStyle
						TBS_HORZ |
						//TBS_AUTOTICKS |
						TBS_NOTICKS |
						TBS_BOTH,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SLIDE_ROTX))		// UINT  nID
	
	return -1;

	
	
	// Not required to be visible, so we hide it by not using//
	// the WS_VISIBLE style bit //

	if (!m_wndSpin_Rot_X.Create(WS_CHILD | // dwStyle
						UDS_SETBUDDYINT,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SPIN_ROTX))		// UINT  nID
	
	return -1;

	//################# Rot Y Slider/Edit set #################

	SetButtonInfo (2, ID_EDIT_ROTY, TBBS_SEPARATOR , cxChar * 8);
	GetItemRect (2, &rect);
    rect.bottom = rect.top + (cyChar + 6);
	
	if(!m_wndEdit_Rot_Y.CreateEx(WS_EX_CLIENTEDGE, // Make a 3D-border
      _T("EDIT"), NULL,
      //WS_TABSTOP |
	  ES_READONLY | ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD,
      rect, this, ID_EDIT_ROTY))

	return -1;


	m_wndEdit_Rot_Y.SetFont (&m_font);

	SetButtonInfo (3, ID_SLIDE_ROTY, TBBS_SEPARATOR, cxChar * 12);
	GetItemRect (3, &rect);
    rect.bottom = rect.top + (cyChar + 2);

	
	if (!m_wndSlider_Rot_Y.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |// dwStyle
						TBS_HORZ |
						//TBS_AUTOTICKS |
						TBS_NOTICKS |
						TBS_BOTH,
						rect,					// rect
						this,		// CWnd* pParentWndntWnd
						ID_SLIDE_ROTY))		// UINT  nID
	
	return -1;

	
	
	// Not required to be visible, so we hide it by not using//
	// the WS_VISIBLE style bit //

	if (!m_wndSpin_Rot_Y.Create(WS_CHILD | // dwStyle
						UDS_SETBUDDYINT,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SPIN_ROTY))		// UINT  nID
	
	return -1;

	//################# Rot Z Slider/Edit set #################

	SetButtonInfo (4, ID_EDIT_ROTZ, TBBS_SEPARATOR , cxChar * 8);
	GetItemRect (4, &rect);
    rect.bottom = rect.top + (cyChar + 6);
	
	if(!m_wndEdit_Rot_Z.CreateEx(WS_EX_CLIENTEDGE, // Make a 3D-border
      _T("EDIT"), NULL,
      //WS_TABSTOP |
	  ES_READONLY | ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_VISIBLE | WS_CHILD,
      rect, this, ID_EDIT_ROTZ))

	return -1;


	m_wndEdit_Rot_Z.SetFont (&m_font);

	SetButtonInfo (5, ID_SLIDE_ROTZ, TBBS_SEPARATOR, cxChar * 12);
	GetItemRect (5, &rect);
    rect.bottom = rect.top + (cyChar + 2);

	
	if (!m_wndSlider_Rot_Z.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |// dwStyle
						TBS_HORZ |
						//TBS_AUTOTICKS |
						TBS_NOTICKS |
						TBS_BOTH,
						rect,					// rect
						this,		// CWnd* pParentWndntWnd
						ID_SLIDE_ROTZ))		// UINT  nID
	
	return -1;

	
	
	// Not required to be visible, so we hide it by not using//
	// the WS_VISIBLE style bit //

	if (!m_wndSpin_Rot_Z.Create(WS_CHILD | // dwStyle
						UDS_SETBUDDYINT,
						rect,					// rect
						this,		// CWnd* pParentWnd
						ID_SPIN_ROTZ))		// UINT  nID
	
	return -1;

	SetPositions();

	return 0;

}


void CSlideToolBar::SetPositions()
{
	
	m_wndSlider_Rot_X.SetRange(-100, 100);
	m_wndSlider_Rot_Y.SetRange(-100, 100);
	m_wndSlider_Rot_Z.SetRange(-100, 100);

	m_wndSpin_Rot_X.SetRange(-100, 100);
	m_wndSpin_Rot_Y.SetRange(-100, 100);
	m_wndSpin_Rot_Z.SetRange(-100, 100);

	m_wndSpin_Rot_X.SetBuddy(&m_wndEdit_Rot_X);
	m_wndSpin_Rot_Y.SetBuddy(&m_wndEdit_Rot_Y);
	m_wndSpin_Rot_Z.SetBuddy(&m_wndEdit_Rot_Z);

	m_wndSlider_Rot_X.SetPos(m_nRotation[0]);
	m_wndSlider_Rot_Y.SetPos(m_nRotation[1]);
	m_wndSlider_Rot_Z.SetPos(m_nRotation[2]);

	m_wndSpin_Rot_X.SetPos(m_nRotation[0]);
	m_wndSpin_Rot_Y.SetPos(m_nRotation[1]);
	m_wndSpin_Rot_Z.SetPos(m_nRotation[2]);


	
}

void CSlideToolBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CSliderCtrl* m_wndSlider_Rot_X = (CSliderCtrl*) pScrollBar;
	CSliderCtrl* m_wndSlider_Rot_Y = (CSliderCtrl*) pScrollBar;
	CSliderCtrl* m_wndSlider_Rot_Z = (CSliderCtrl*) pScrollBar;

	UpdateValues();

	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_SLIDER); 
	::SetCursor(hCursor);
	

	CToolBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSlideToolBar::UpdateValues()
{
	m_wndSpin_Rot_X.SetPos(m_wndSlider_Rot_X.GetPos());
	m_wndSpin_Rot_Y.SetPos(m_wndSlider_Rot_Y.GetPos());
	m_wndSpin_Rot_Z.SetPos(m_wndSlider_Rot_Z.GetPos());

	m_nRotation[0] = m_wndSpin_Rot_X.GetPos();
	m_nRotation[1] = m_wndSpin_Rot_Y.GetPos();
	m_nRotation[2] = m_wndSpin_Rot_Z.GetPos();

}
