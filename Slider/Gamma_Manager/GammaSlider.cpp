/***=========================================================================
====                                                                     ====
====                          D C U t i l i t y                          ====
====                                                                     ====
=============================================================================
====                                                                     ====
====    File name           :  GammaSlider.cpp                           ====
====    Project name        :  GammaManager                              ====
====    Project number      :  ---                                       ====
====    Creation date       :  24/10/2002                                ====
====    Author(s)           :  Dany Cantin                               ====
====                                                                     ====
====                  Copyright © DCUtility  2002                        ====
====                                                                     ====
====    History
====    v1.1 - Add function LoadSettings and SaveSettings
====    v1.0 - Initial release
=============================================================================
===========================================================================*/


#include "stdafx.h"
#include "GammaSlider.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_POS     0
#define MAX_POS     40
#define POS_FACTOR  10.0

#define REG_SECTION "GammaSlider"
#define REG_ENTRY   "Settings"

/*===========================================================================

@mfunc CGammaSlider - Constructor

===========================================================================*/
CGammaSlider::CGammaSlider()
{
}



/*===========================================================================

@mfunc ~CGammaSlider - Destructor

===========================================================================*/
CGammaSlider::~CGammaSlider()
{
    Restore();
}



/*===========================================================================

@mfunc OnDestroy - See MFC

===========================================================================*/
void CGammaSlider::OnDestroy() 
{
    SaveSettings();

	CSliderCtrl::OnDestroy();
}



BEGIN_MESSAGE_MAP(CGammaSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CGammaSlider)
	ON_WM_HSCROLL_REFLECT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/*===========================================================================

@mfunc PreSubclassWindow - See MFC

===========================================================================*/
void CGammaSlider::PreSubclassWindow() 
{
	if (!GetDeviceGammaRamp(::GetDC(NULL), m_RampSaved))
	{
		TRACE("WARNING: Cannot initialize DeviceGammaRamp.\n");
		EnableWindow(FALSE);
	}
	else 
	{		
		SetRange(MIN_POS, MAX_POS);
		SetTicFreq(5);
        LoadSettings();
    }
	
	CSliderCtrl::PreSubclassWindow();
}



/*===========================================================================

@mfunc  GetGammaPos - Get current gamma average (Originaly for RGB input)

===========================================================================*/
int CGammaSlider::GetGammaPos() 
{ 
	float rgb[3]  = {1.0, 1.0, 1.0}; 
	
	for (int i = 0; i < 3; i++) {
        
		float Csum	    = 0.0; 
		int   Ccount	= 0; 
		int   min		= 256 * i; 
		int   max		= min + 256; 

		for (int j = min; j < max; j++) {
            
			if (j != 0 && m_RampSaved[j] != 0 && m_RampSaved[j] != 65536) 
			{ 
				double B = (j % 256) / 256.0; 
				double A = m_RampSaved[j] / 65536.0; 
				float  C = (float)(log(A) / log(B));
                
				Csum += C; 
				Ccount++; 
			} 
		} 

		rgb[i] = Csum / Ccount; 
	} 
	
	return (int)(MAX_POS-(rgb[0] * POS_FACTOR));
}



/*===========================================================================

@mfunc HScroll	- Refelction

@parm  nSBCode	- Reflection code

@parm  nPos		- Poition value

===========================================================================*/
void CGammaSlider::HScroll(UINT nSBCode, UINT nPos) 
{
	if (nSBCode == SB_THUMBTRACK || nSBCode == TB_LINEDOWN ||
		nSBCode == TB_LINEUP || nSBCode == TB_TOP)
	{
		SetGamma((float)((MAX_POS-nPos) / POS_FACTOR));
	}
}



/*===========================================================================

@mfunc SetGamma - Set current gamma average (Originaly for RGB input)

@parm  Gamma - Gamma value 

===========================================================================*/
void CGammaSlider::SetGamma(float Gamma)
{
	WORD ramp[256*3];

	for(int i = 0; i < 256; i++) {
		ramp[i] = ramp[i+256] = ramp[i+512] = 
		(WORD)min(65535, max(0, pow((i+1) / 256.0, Gamma) * 65535 + 0.5));
	}

    SetDeviceGammaRamp(::GetDC(NULL), ramp);
}



/*===========================================================================

@mfunc LoadSettings - Load current state

===========================================================================*/
void CGammaSlider::LoadSettings()
{
    int nPos = AfxGetApp()->GetProfileInt(REG_SECTION, REG_ENTRY, GetGammaPos());

    SetPos(nPos); 
	SetGamma((float)((MAX_POS-((nPos == MAX_POS) ? MAX_POS-3 : nPos)) / POS_FACTOR));
}



/*===========================================================================

@mfunc SaveSettings - Save current state

===========================================================================*/
void CGammaSlider::SaveSettings()
{
    AfxGetApp()->WriteProfileInt(REG_SECTION, REG_ENTRY, GetPos()); 
}



/*===========================================================================

@mfunc RestoreGamma - Restore saved gamma

===========================================================================*/
void CGammaSlider::RestoreGamma()
{
    SetPos(GetGammaPos());
    Restore();
}



/*===========================================================================

@mfunc Restore - Restore saved gamma

===========================================================================*/
void CGammaSlider::Restore()
{
	if (!SetDeviceGammaRamp(::GetDC(NULL), m_RampSaved))
		TRACE("WARNING: Cannot restore DeviceGammaRamp.\n");
}

