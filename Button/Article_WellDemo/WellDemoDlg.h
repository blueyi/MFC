// WellDemoDlg.h : header file
//

#if !defined(AFX_WELLDEMODLG_H__58DF2F1E_5A98_4FF0_AEEF_2E430217C707__INCLUDED_)
#define AFX_WELLDEMODLG_H__58DF2F1E_5A98_4FF0_AEEF_2E430217C707__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArrowPicker.h"
#include "linePicker.h"
#include "colourpicker.h"
/////////////////////////////////////////////////////////////////////////////
// CWellDemoDlg dialog

class CWellDemoDlg : public CDialog
{
// Construction
public:
	CWellDemoDlg(CWnd* pParent = NULL);	// standard constructor
	static ArrowType GetArrowType(int );
	static int GetArrowIndex(ArrowType);

// Dialog Data
	//{{AFX_DATA(CWellDemoDlg)
	enum { IDD = IDD_WELLDEMO_DIALOG };
	CLinePicker		m_linePicker;
	CArrowPicker	m_arrowEndPicker;
	CArrowPicker	m_arrowStartPicker;
	CColourPicker	m_FillPicker;
	CColourPicker	m_LinePicker;
	int	m_Fill;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	ArrowType				m_arrowStart;
	ArrowType				m_arrowEnd;
	COLORREF				m_LineColor;
	COLORREF				m_FillColor;
	bool					m_isArrow;
	DashStyle				m_dashStyle;
	DashCap					m_dashCap;   // 0 :flat, 2: round, 3: triangle, don't know what is 1.
	BrushType               m_brushType;
	PenType					m_penType;
	Color  				    m_brushColor, //when hatch pattern used, this is foreColor
	                        m_gradientColor,
							m_penColor,
							m_penEndColor;
	int						m_penWidth;
	LinearGradientMode      m_linearGradientMode; //for linear gradient only;
	HatchStyle              m_hatchStyle;
	int                     m_startArrowSize,  // relative Arrow Size:  m_startArrowSize/10 * m_penWidth is the real size
	                        m_endArrowSize;
	int						m_startArrow,
							m_endArrow;
	CString					m_fillImage;
	WrapMode                m_wrapMode;
	int						m_FillMode; //0, - center path gradient.

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWellDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWellDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELLDEMODLG_H__58DF2F1E_5A98_4FF0_AEEF_2E430217C707__INCLUDED_)
