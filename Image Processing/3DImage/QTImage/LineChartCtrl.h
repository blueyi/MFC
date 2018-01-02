#if !defined(AFX_LINECHARTCTRL_H__4C81C33B_1F16_4173_AF9A_A39CB4F1B6DC__INCLUDED_)
#define AFX_LINECHARTCTRL_H__4C81C33B_1F16_4173_AF9A_A39CB4F1B6DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineChartCtrl.h : header file
//
#include "AfxTempl.h"

/////////////////////////////////////////////////////////////////////////////
// CLineChartCtrl window
#include "GlobalHeader.h"

class CLineChartCtrl : public CStatic
{
// Construction
public:
	CLineChartCtrl();
	void GetPixelColor(int pixel,COLORREF &color);
	void DrawLine();
	
	int m_iMode; //=0 opacity mapping =1 color mapping.  =2 grad mapping
	CList<IA_PIXEL_ITEM,IA_PIXEL_ITEM&> m_itemList;
	IA_PIXEL_ITEM *m_grayHistogram;
	BOOL m_bRedrawHistogram;

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineChartCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetPixelOpacity(int pixel,float &opacity);
	void AddItem(IA_PIXEL_ITEM itemNew);
	void SetPixelRange(unsigned short min,unsigned short max);
	virtual ~CLineChartCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineChartCtrl)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void DrawHistogram(CDC *pDC);
	
	void Notify();
	void GetValue(int x,int y,unsigned short &pixel,float &value);
	void GetPos(unsigned short pixel,float value,int &x,int &y);
	

	CDC      m_memDC;
	CDC      m_bkDC;
	CBitmap  m_bitmap;
	CBitmap  m_bitmapBK;
	CBitmap  *m_pOldBitmap,*m_pOldBitmapBK;
	
	unsigned short m_pixelRange[2];
	float m_valueRange[2];
	BOOL m_bLeftBtnDown;
	int m_iCurSel;
	int m_iRadius; //ÇòµÄ°ë¾¶
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINECHARTCTRL_H__4C81C33B_1F16_4173_AF9A_A39CB4F1B6DC__INCLUDED_)
