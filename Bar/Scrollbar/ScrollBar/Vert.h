// Vert.h : header file
//

#ifndef VERT_H
#define VERT_H

#include "XScrollBar.h"
#include "SampleStatic.h"
#include "Color.h"

/////////////////////////////////////////////////////////////////////////////
// CVert dialog

class CVert : public CDialog
{
// Construction
public:
	CVert(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVert)
	enum { IDD = IDD_VERTICAL };
	CSampleStatic	m_Sample;
	BOOL	m_bThumbColor;
	BOOL	m_bThumbGripper;
	BOOL	m_bChannelColor;
	//}}AFX_DATA
	CXScrollBar m_VerticalScrollBar1;	// red
	CXScrollBar m_VerticalScrollBar2;	// green
	CXScrollBar m_VerticalScrollBar3;	// blue
	CXScrollBar m_VerticalScrollBar4;	// saturation
	CXScrollBar m_VerticalScrollBar5;	// luminance

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVert)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CColor	m_color;
	int		m_nRed, m_nGreen, m_nBlue;
	int		m_nSaturation, m_nLuminance;
	float	m_dHue, m_dLuminance, m_dSaturation;

	// Generated message map functions
	//{{AFX_MSG(CVert)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnThumb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //VERT_H
