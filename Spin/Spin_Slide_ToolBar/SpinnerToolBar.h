#if !defined(AFX_SPINTOOLBAR_H__E6990A61_6552_11D4_BEC3_AB6028BDFA45__INCLUDED_)
#define AFX_SPINTOOLBAR_H__E6990A61_6552_11D4_BEC3_AB6028BDFA45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpinToolBar.h : header file
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

/////////////////////////////////////////////////////////////////////////////
// CSpinToolBar window

class CSpinToolBar : public CToolBar
{
// Construction
public:
	CSpinToolBar();
	
// Attributes
public:
	
	// Edit boxes used as buddy to the spinners
	CEdit m_wndEdit_r;	// Red
	CEdit m_wndEdit_g;	// Green
	CEdit m_wndEdit_b;	// Blue

	// Spinners used as RGB increase/decrease controls
	CSpinButtonCtrl m_wndSpin_r;
	CSpinButtonCtrl m_wndSpin_g;
	CSpinButtonCtrl m_wndSpin_b;

	// Set of Slider/Spinner & Edit box for the gradient control
	CSliderCtrl m_wndSlider;
	CEdit m_wndEdit_sld;
	CSpinButtonCtrl m_wndSpin_sld;

	// Font used to fill the edit controls
	CFont m_font;

	// RGB values control components
	UINT m_nRed,
		 m_nGreen,
		 m_nBlue;

	// Value for the gradient components (RGB)
	UINT m_nGradValue;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	
	virtual ~CSpinToolBar();

protected:

	void SetPositions(void);


	// Generated message map functions
protected:
	//{{AFX_MSG(CSpinToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPINTOOLBAR_H__E6990A61_6552_11D4_BEC3_AB6028BDFA45__INCLUDED_)
