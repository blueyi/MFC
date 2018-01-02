#if !defined(__LinePICK_H__)
#define __LinePICK_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "LineWnd.h"

void AFXAPI DDX_LinePicker(CDataExchange *pDX, int nIDC, DashStyle &LineType);

/////////////////////////////////////////////////////////////////////////////
// CLinePicker window

class SVIZDLLEXPORT CLinePicker : public CButton
{
// Construction
public:
    CLinePicker();
    DECLARE_DYNCREATE(CLinePicker);

// Attributes
public:
    int      GetLine();
    void     SetLine(int LineType); 

    void     SetTrackSelection(BOOL bTracking = TRUE)  { m_bTrackSelection = bTracking; }
    BOOL     GetTrackSelection()                       { return m_bTrackSelection; }

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CLinePicker)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
	void SetMaximumLines(int n);
    virtual ~CLinePicker();

protected:
    void SetWindowSize();

// protected attributes
protected:
    BOOL     m_bActive,                // Is the dropdown active?
             m_bTrackSelection;        // track colour changes?
    int      m_Line;
	int		 m_nNumLines;			//maximum line number
    CRect    m_ArrowRect;

    // Generated message map functions
protected:
    //{{AFX_MSG(CLinePicker)
    afx_msg BOOL OnClicked();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);

    DECLARE_MESSAGE_MAP()
};

/** @class CLinePicker
 *  @brief Control for choosing different line type working with CLineWnd
 *
 * The CLinePicker class provides the basic functionality to choose line style.
 * It is derived from CButton.
 * 
 * For more information on CLinePicker, see CLineWnd.
 */

#endif 
///////////////////////////////////////////////////////////////////////
// This file is a part of the SViz MFC Extention Class.
// 2001-2002 SVizSoft Software, All Rights Reserved.
//
// SVIZSOFT GRANTS TO YOU THE LIMITED RIGHT TO USE THIS SOFTWARE ON 
// A SINGLE COMPUTER. 
// THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE THE PROPERTY
// OF SVIZSOFT AND ARE NOT TO BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER
// WITHOUT THE EXPRESSED WRITTEN CONSENT OF SVIZ SOFTWARE.
// 
// You can contact us.
// admin@svizsoft.com
///////////////////////////////////////////////////////////////////////
