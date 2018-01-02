// SliderClrDemoView.h : interface of the CSliderClrDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLIDERCLRDEMOVIEW_H__B1E7DAAB_488C_4D24_B142_B244BA1B189E__INCLUDED_)
#define AFX_SLIDERCLRDEMOVIEW_H__B1E7DAAB_488C_4D24_B142_B244BA1B189E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SliderCtrlEx.h"	// Slider with colored ranges

class CSliderClrDemoView : public CFormView
{
protected: // create from serialization only
	CSliderClrDemoView();
	DECLARE_DYNCREATE(CSliderClrDemoView)

public:
	//{{AFX_DATA(CSliderClrDemoView)
	enum { IDD = IDD_SLIDERCLRDEMO_FORM };
	CEdit	m_Edit3;
	CSliderCtrlEx	m_Slider3;
	CEdit	m_Edit2;
	CEdit	m_Edit1;
	CSliderCtrlEx	m_Slider2;
	CSliderCtrlEx	m_Slider1;
	//}}AFX_DATA

// Attributes
public:
	CSliderClrDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderClrDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	int colorScheme;
	void ItemUpdate(LPARAM data1, int sValue, BOOL IsDragging);
	static void sItemUpdate(CSliderClrDemoView *obj, LPARAM data1, int sValue, BOOL IsDragging);
	virtual ~CSliderClrDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int ticfreq;
	//{{AFX_MSG(CSliderClrDemoView)
	afx_msg void OnChgtics();
	afx_msg void OnChgclrs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SliderClrDemoView.cpp
inline CSliderClrDemoDoc* CSliderClrDemoView::GetDocument()
   { return (CSliderClrDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDERCLRDEMOVIEW_H__B1E7DAAB_488C_4D24_B142_B244BA1B189E__INCLUDED_)
