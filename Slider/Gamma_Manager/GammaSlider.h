/***=========================================================================
====                                                                     ====
====                          D C U t i l i t y                          ====
====                                                                     ====
=============================================================================
====                                                                     ====
====    File name           :  GammaSlider.h                             ====
====    Project name        :  GammaManager                              ====
====    Project number      :  ---                                       ====
====    Creation date       :  24/10/2002                                ====
====    Author(s)           :  Dany Cantin                               ====
====                                                                     ====
====                  Copyright © DCUtility  2002                        ====
====                                                                     ====
=============================================================================
===========================================================================*/


#ifndef GammaSlider_H
#define GammaSlider_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGammaSlider window

class CGammaSlider : public CSliderCtrl
{
	// Construction
public:
	CGammaSlider();
	
	// Attributes
private:
    WORD	m_RampSaved[255*3];
	
	// Operations
public:
    void    RestoreGamma();

private:
	void	SetGamma(float Gamma);
	int		GetGammaPos();
    void    Restore();
    void    LoadSettings();
    void    SaveSettings();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGammaSlider)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CGammaSlider();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CGammaSlider)
	afx_msg void HScroll(UINT nSBCode, UINT nPos);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#endif // GammaSlider_H
