#if !defined(AFX_UPPANEVIEW_H__CC1D234A_62A8_4F25_B0EF_17732A46BB41__INCLUDED_) 
#define AFX_UPPANEVIEW_H__CC1D234A_62A8_4F25_B0EF_17732A46BB41__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
// UpPaneView.h : header file 
// 
#include <afxcview.h> 
#include "CurveDrawingDoc.h" 
///////////////////////////////////////////////////////////////////////////// 
// CUpPaneView view 

class CUpPaneView : public CListView 
{ 
protected: 
	CUpPaneView();           // protected constructor used by dynamic creation 
	DECLARE_DYNCREATE(CUpPaneView) 

	// Attributes 
public: 

	// Operations 
public: 
	void AddList(); 

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CUpPaneView) 
public: 
	virtual void OnInitialUpdate(); 
protected: 
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view 
	//}}AFX_VIRTUAL 

	// Implementation 
protected: 
	virtual ~CUpPaneView(); 
#ifdef _DEBUG 
	virtual void AssertValid() const; 
	virtual void Dump(CDumpContext& dc) const; 
#endif 

	// Generated message map functions 
protected: 
	//{{AFX_MSG(CUpPaneView) 
	// NOTE - the ClassWizard will add and remove member functions here. 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

///////////////////////////////////////////////////////////////////////////// 

//{{AFX_INSERT_LOCATION}} 
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 

#endif // !defined(AFX_UPPANEVIEW_H__CC1D234A_62A8_4F25_B0EF_17732A46BB41__INCLUDED_) 