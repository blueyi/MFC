// SpinnerTBView.h : interface of the CSpinnerTBView class
//
/////////////////////////////////////////////////////////////////////////////

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

#if !defined(AFX_SpinnerTBVIEW_H__D8FEDCEF_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
#define AFX_SpinnerTBVIEW_H__D8FEDCEF_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpinnerTBDoc.h"

class CSpinnerTBView : public CView
{
protected: // create from serialization only
	CSpinnerTBView();
	
	
	DECLARE_DYNCREATE(CSpinnerTBView)

// Attributes
public:
	CSpinnerTBDoc* GetDocument();
	
// Operations
public:
	
	// This is used to report in the status pane
	CString m_strRGB;

	// Palette used for gradient fill
	CPalette m_palette; 

	// Gradient filling method
    void DoGradientFill (CDC* pDC, LPRECT pRect);
    
	// Text drawing method
	void DoDrawText (CDC* pDC, LPRECT pRect);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinnerTBView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpinnerTBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpinnerTBView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnColorsRed();
	afx_msg void OnColorsGreen();
	afx_msg void OnColorsBlue();
	afx_msg void OnColorsSpinners();
	afx_msg void OnUpdateRed();
	afx_msg void OnUpdateGreen();
	afx_msg void OnUpdateBlue();
	afx_msg void OnUpdateGradient();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SpinnerTBView.cpp
inline CSpinnerTBDoc* CSpinnerTBView::GetDocument()
   { return (CSpinnerTBDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SpinnerTBVIEW_H__D8FEDCEF_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
