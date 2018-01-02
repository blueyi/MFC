// ToolBarShrink.h: interface for the CToolBarPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARSHRINK_H__11521262_3856_41ED_A399_D1AC38093863__INCLUDED_)
#define AFX_TOOLBARSHRINK_H__11521262_3856_41ED_A399_D1AC38093863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ToolbarEx.h"

class CToolBarShrink : public CToolBarEx  
{
public:
	CToolBarShrink();
	~CToolBarShrink();

	void Create();
	void Update(double dShrinkRatio);
	void SetMainFrame( CFrameWnd* pFrame)	{	m_pFrame = pFrame;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarEx)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CToolBarShrink)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(CToolBarShrink)
protected:
	double m_dShrinkRatio;
	CSliderCtrl* m_pShrinkSlider;
	CFrameWnd* m_pFrame;
};

#endif // !defined(AFX_TOOLBARPLAYER_H__11521262_3856_41ED_A399_D1AC38093863__INCLUDED_)
