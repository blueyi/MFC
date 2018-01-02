#if !defined(AFX_SERIESLIST_H__8DDD09DB_0C35_420E_98F9_6D46A2968402__INCLUDED_)
#define AFX_SERIESLIST_H__8DDD09DB_0C35_420E_98F9_6D46A2968402__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeriesList.h : header file
//
#include "SeriesListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CSeriesList dialog

class CSeriesList : public CDialog
{
// Construction
public:
	CSeriesList(CWnd* pParent = NULL);   // standard constructor

	void AddSeries();
	void SetSeriesManager(CSeriesManager *pManager);

	CSeriesManager *m_pManager;

// Dialog Data
	//{{AFX_DATA(CSeriesList)
	enum { IDD = IDD_IMAGE_LIST };
	CSeriesListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeriesList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnClickListImage(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESLIST_H__8DDD09DB_0C35_420E_98F9_6D46A2968402__INCLUDED_)
