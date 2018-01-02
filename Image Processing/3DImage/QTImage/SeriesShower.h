#if !defined(AFX_SERIESSHOWER_H__4FE3C6FF_3903_47CA_B1DA_67EB60ABED1E__INCLUDED_)
#define AFX_SERIESSHOWER_H__4FE3C6FF_3903_47CA_B1DA_67EB60ABED1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeriesShower.h : header file
//
#include "vtkImageData.h"
/////////////////////////////////////////////////////////////////////////////
// CSeriesShower window

class CSeriesShower : public CStatic
{
// Construction
public:
	CSeriesShower();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesShower)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Update(vtkImageData *pImage,int index);
	virtual ~CSeriesShower();

	// Generated message map functions
protected:
	CDC      m_memDC;
	CBitmap  m_bitmap;
	CBitmap  *m_pOldBitmap;

	//{{AFX_MSG(CSeriesShower)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESSHOWER_H__4FE3C6FF_3903_47CA_B1DA_67EB60ABED1E__INCLUDED_)
