#if !defined(AFX_DLGIMAGECONTAINER_H__C1239D2A_20EC_4A11_AE65_F39EC8C9F081__INCLUDED_)
#define AFX_DLGIMAGECONTAINER_H__C1239D2A_20EC_4A11_AE65_F39EC8C9F081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImageContainer.h : header file
//

#include "ximage.h"
#include "RectangleROI.h"
#include "EdgeDetect.h"
#include "EdgeInteraction.h"

#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDlgImageContainer dialog

class CDlgImageContainer : public CDialog
{
// Construction
public:
	void				SetCxImage(CxImage * pCxImage);
	CxImage*			GetCxImage()			{return m_pCxImage;}

	vector<CPoint>&		GetEdge()				{return m_vecEdge;}

	CRectangleROI*		GetRectangleROI()		{return &m_RectangleROI;}
	CEdgeDetect*		GetEdgeDetect()			{return &m_EdgeDetect;}
	CEdgeInteraction*	GetEdgeInteraction()	{return &m_EdgeInteraction;}

	CDlgImageContainer(CWnd* pParent = NULL);   // standard constructor
	~CDlgImageContainer();

// Dialog Data
	//{{AFX_DATA(CDlgImageContainer)
	enum { IDD = IDD_DLG_IMAGECONTAINER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImageContainer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CxImage*			m_pCxImage;

	vector<CPoint>		m_vecEdge;

	CRectangleROI		m_RectangleROI;
	CEdgeDetect			m_EdgeDetect;
	CEdgeInteraction	m_EdgeInteraction;

	// Generated message map functions
	//{{AFX_MSG(CDlgImageContainer)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMAGECONTAINER_H__C1239D2A_20EC_4A11_AE65_F39EC8C9F081__INCLUDED_)
