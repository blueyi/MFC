#if !defined(AFX_IMAGEAREA_H__CF819F6E_D799_424C_B2D4_714E5BFBE0E6__INCLUDED_)
#define AFX_IMAGEAREA_H__CF819F6E_D799_424C_B2D4_714E5BFBE0E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageArea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageArea window

class CImageArea : public CStatic
{
// Construction
public:
	CImageArea();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageArea)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageArea();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageArea)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEAREA_H__CF819F6E_D799_424C_B2D4_714E5BFBE0E6__INCLUDED_)
