#if !defined(AFX_SERIESLISTCTRL_H__DAAD79F1_8304_4441_8D54_8CBF8ADC20A6__INCLUDED_)
#define AFX_SERIESLISTCTRL_H__DAAD79F1_8304_4441_8D54_8CBF8ADC20A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeriesListCtrl.h : header file
//
#include "SeriesManager.h"
/////////////////////////////////////////////////////////////////////////////
// CSeriesListCtrl window

class CSeriesListCtrl : public CListCtrl
{
// Construction
public:
	CSeriesListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesListCtrl)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	//}}AFX_VIRTUAL

// Implementation
public:
	void AddSeries();
	void SetSeriesManager(CSeriesManager *pManager);
	virtual ~CSeriesListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSeriesListCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bMeasured;
	BOOL m_bSized;
	CFont m_font;
	COLORREF m_clSelected,m_clUnselected;

	CSeriesManager *m_pManager;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESLISTCTRL_H__DAAD79F1_8304_4441_8D54_8CBF8ADC20A6__INCLUDED_)
