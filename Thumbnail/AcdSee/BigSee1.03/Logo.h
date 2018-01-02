#if !defined(AFX_LOGO_H__DC102E81_D246_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_LOGO_H__DC102E81_D246_11D6_AFCA_001088A02FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Logo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogo window

class CLogo : public CWnd
{
// Construction
public:
	CLogo();

// Attributes
public:
	CBitmap m_bitmap;
    BITMAP  m_bmpStruct;
// Operations
public:
	void CreateLogo(CWnd*pWnd,UINT nBitmapID,UINT nChildID);
	void MoveLogo(int nWidth,int nHeight);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogo)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLogo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogo)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGO_H__DC102E81_D246_11D6_AFCA_001088A02FAC__INCLUDED_)
