//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_RTFORM_H__D83979B6_F56A_11D3_85D3_0008C777FFEE__INCLUDED_)
#define AFX_RTFORM_H__D83979B6_F56A_11D3_85D3_0008C777FFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RTForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRTForm form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "RTSlider.h"

class CRTForm : public CFormView
{
protected:
	CRTForm();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRTForm)

// Form Data
public:
	//{{AFX_DATA(CRTForm)
	enum { IDD = IDD_RTFORM };
	CRTSlider	m_SliderPage;
	CMSFlexGrid	m_RTGrid;
	//}}AFX_DATA

// Attributes
public:
	CRect	m_sRect;

// Operations
public:
	CWnd* GetRTDemoView();
	void  MoveWindows();
	void  InitialSlider(int nMin, int nMax, int nPage, int nPos, BOOL nFlag = TRUE);
	void  RedrawGrid();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTForm)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRTForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRTForm)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTFORM_H__D83979B6_F56A_11D3_85D3_0008C777FFEE__INCLUDED_)
