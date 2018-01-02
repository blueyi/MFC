// RTDemoView.h : interface of the CRTDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTDemoVIEW_H__12551283_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_)
#define AFX_RTDemoVIEW_H__12551283_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RealTime.h"
#include "RTSlider.h"
#include "random.h"
#include "mscomm1.h"

class CRTDemoView : public CView
{
	// just want to save time using temporary variables
	int    i, m, n;
	double m_dY, m_dValue;

protected: // create from serialization only
	CRTDemoView();
	DECLARE_DYNCREATE(CRTDemoView)

// Attributes
public:
	CRTDemoDoc* GetDocument();
	CRealTime  m_Graph;

	RndGen Rn;
	DWORD  m_nStartTime;
	int	   m_nTimeSpan;
	DWORD  MaxSeconds;
	DWORD  mSec;
	double CyclesPerSec;
	DWORD  CurrentTime;
	BOOL   m_bCanSize;

	CRTSlider m_SliderTick;
	CRect	  m_SRect;
	int		  m_sSize;
	int		  m_sTicks;
	BOOL	  m_bFlag;
	BOOL	  CanTicks;
	DWORD	  m_nTicks;

	BOOL	  m_bRealTime;
	BOOL	  m_bTimerOn;

// Operations
public:
	void DrawFrame(CRect& rect, COLORREF cr, const char* Title);
	void Redraw();
	void SetData(int i);
	void RefreshGraph();

	RECT& GetGraphRect();
	CWnd* GetRTForm();
	void  ResetSlider(int Ticks);
	void  GetYValues(int Index);
	void  TicksRanges();

	void  RTKillTimer();
	void  RTRestoreTimer();
	void  RemoveALine(int Index);
	BOOL  InsertALine(int index, COLORREF color, double low, double high, 
					  const char* name, const char* desc, const char* unit, 
					  double min, double max, int style, int width);
	void  SaveAModifiedLine();
	void  GetColorAndName(int index, COLORREF& cr, CString& name);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRTDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_sString;
	DWORD   MillSeconds;
	int		SpeedLevel;
	CMSComm m_mscomm;

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CRTDemoView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSpeedTimerspeed();
	afx_msg void OnUpdateSpeedTimerspeed(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnComm();
    DECLARE_EVENTSINK_MAP()      
};

#ifndef _DEBUG  // debug version in RTDemoView.cpp
inline CRTDemoDoc* CRTDemoView::GetDocument()
   { return (CRTDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTDemoVIEW_H__12551283_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_)
