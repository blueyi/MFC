#if !defined(AFX_MYVIEW_H__B9A0B20A_78EA_4CE4_A0C9_EDABB34EB902__INCLUDED_) 
#define AFX_MYVIEW_H__B9A0B20A_78EA_4CE4_A0C9_EDABB34EB902__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
// MyView.h : header file 
// 
#include "clPlot.h" 
///////////////////////////////////////////////////////////////////////////// 
// CMyView view 

class CMyView : public CView 
{ 
public: 
	CMyView();           // protected constructor used by dynamic creation 
	virtual ~CMyView(); 
	DECLARE_DYNCREATE(CMyView) 

	// Attributes 
public: 
	CRect rc; 
	clPlot m_plot; 

	// Operations 
public: 

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CMyView) 
protected: 
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view 
	//}}AFX_VIRTUAL 

	// Implementation 
protected: 

#ifdef _DEBUG 
	virtual void AssertValid() const; 
	virtual void Dump(CDumpContext& dc) const; 
#endif 

	// Generated message map functions 
protected: 
	//{{AFX_MSG(CMyView) 
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

///////////////////////////////////////////////////////////////////////////// 

//{{AFX_INSERT_LOCATION}} 
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 

#endif // !defined(AFX_MYVIEW_H__B9A0B20A_78EA_4CE4_A0C9_EDABB34EB902__INCLUDED_) 