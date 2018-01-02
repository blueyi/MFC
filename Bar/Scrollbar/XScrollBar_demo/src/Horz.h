// Horz.h : header file
//

#ifndef HORZ_H
#define HORZ_H

#include "XScrollBar.h"
#include "SampleStatic.h"
#include "Color.h"

/////////////////////////////////////////////////////////////////////////////
// CHorz dialog

class CHorz : public CDialog
{
// Construction
public:
	CHorz(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHorz)
	enum { IDD = IDD_HORIZONTAL };
	CSampleStatic	m_Sample;
	BOOL	m_bThumbColor;
	BOOL	m_bThumbGripper;
	BOOL	m_bChannelColor;
	//}}AFX_DATA
	CXScrollBar m_HorizontalScrollBar1;	// red
	CXScrollBar m_HorizontalScrollBar2;	// green
	CXScrollBar m_HorizontalScrollBar3;	// blue
	CXScrollBar m_HorizontalScrollBar4;	// saturation
	CXScrollBar m_HorizontalScrollBar5;	// luminance

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHorz)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CColor	m_color;
	int		m_nRed, m_nGreen, m_nBlue;
	int		m_nSaturation, m_nLuminance;
	float	m_dHue, m_dLuminance, m_dSaturation;

	void Init();

	// Generated message map functions
	//{{AFX_MSG(CHorz)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnThumb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //HORZ_H
