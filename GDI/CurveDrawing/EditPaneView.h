#if !defined(AFX_EDITPANEVIEW_H__A504806D_596B_476E_A0A6_F2EF80BD39D3__INCLUDED_) 
#define AFX_EDITPANEVIEW_H__A504806D_596B_476E_A0A6_F2EF80BD39D3__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
// EditPaneView.h : header file 
// 

///////////////////////////////////////////////////////////////////////////// 
// CEditPaneView view 

class CEditPaneView : public CEditView 
{ 
protected: 
	CEditPaneView();           // protected constructor used by dynamic creation 
	DECLARE_DYNCREATE(CEditPaneView) 

	// Attributes 
public: 

	// Operations 
public: 

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CEditPaneView) 
public: 
	virtual void OnInitialUpdate(); 
protected: 
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view 
	//}}AFX_VIRTUAL 

	// Implementation 
protected: 
	virtual ~CEditPaneView(); 
#ifdef _DEBUG 
	virtual void AssertValid() const; 
	virtual void Dump(CDumpContext& dc) const; 
#endif 

	// Generated message map functions 
protected: 
	//{{AFX_MSG(CEditPaneView) 
	// NOTE - the ClassWizard will add and remove member functions here. 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

///////////////////////////////////////////////////////////////////////////// 

//{{AFX_INSERT_LOCATION}} 
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 

#endif // !defined(AFX_EDITPANEVIEW_H__A504806D_596B_476E_A0A6_F2EF80BD39D3__INCLUDED_) 