#if !defined(AFX_TESTWND_H__31CE8CFD_A998_4B2D_8EE4_84117DD1FF28__INCLUDED_)
#define AFX_TESTWND_H__31CE8CFD_A998_4B2D_8EE4_84117DD1FF28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestWnd window

#include "OpenGLWnd.h"

class CTestWnd : public COpenGLWnd
{
private:
	GLenum quadricNormals;
	GLenum quadricDwStyle;
	GLenum quadricOrientation;
	CGLDispList quadric;
	int sceneselect;
	BOOL TessFilling;
	CGLDispList tessPolygon;
	GLdouble TessWindRule;
	CGLDispList anothercube;
	CPoint MouseDownPoint;
	double X_Angle;
	double Y_Angle;

private:
	void BuildQuadrDispList();
	void BuildTessDispList();
	
public:
	void OnCreateGL();
	void OnDrawGL();
// Construction
public:
	CTestWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTWND_H__31CE8CFD_A998_4B2D_8EE4_84117DD1FF28__INCLUDED_)
