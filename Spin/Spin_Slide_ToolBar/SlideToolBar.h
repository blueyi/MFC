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
#if !defined(AFX_SLIDETOOLBAR_H__992196A1_7C20_11D4_BEC3_B9FC12288B45__INCLUDED_)
#define AFX_SLIDETOOLBAR_H__992196A1_7C20_11D4_BEC3_B9FC12288B45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SlideToolBar.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CSlideToolBar window

class CSlideToolBar : public CToolBar
{
// Construction
public:
	CSlideToolBar();

// Attributes
public:
	
	// X Rotation Set 
	CSliderCtrl m_wndSlider_Rot_X;
	CEdit m_wndEdit_Rot_X;
	CSpinButtonCtrl m_wndSpin_Rot_X;

	// Y Rotation Set 
	CSliderCtrl m_wndSlider_Rot_Y;
	CEdit m_wndEdit_Rot_Y;
	CSpinButtonCtrl m_wndSpin_Rot_Y;

	// Z Rotation Set 
	CSliderCtrl m_wndSlider_Rot_Z;
	CEdit m_wndEdit_Rot_Z;
	CSpinButtonCtrl m_wndSpin_Rot_Z;

	// Font used to fill the edit controls
	CFont m_font;


	int	m_nRotation[3];
		   

// Operations
public:

	void SetPositions();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlideToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateValues();
	virtual ~CSlideToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSlideToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDETOOLBAR_H__992196A1_7C20_11D4_BEC3_B9FC12288B45__INCLUDED_)
