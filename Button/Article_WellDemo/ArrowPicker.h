#if !defined(__SVIZ_ARROWPICK_H__)
#define __SVIZ_ARROWPICK_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ArrowWnd.h"
//#include "svizcomp.h"
/////////////////////////////////////////////////////////////////////////////
// CArrowPicker window
void AFXAPI DDX_ArrowPicker(CDataExchange *pDX, int nIDC, int &arrowType);
/////////////////////////////////////////////////////////////////////////////
// CArrowPicker window

class SVIZDLLEXPORT CArrowPicker : public CButton
{
// Construction
public:
    CArrowPicker();
    DECLARE_DYNCREATE(CArrowPicker);

// Attributes
public:
    int			GetArrow			();
    void		SetArrow			(int arrowType); 

    void		SetTrackSelection	(BOOL bTracking = TRUE)  { m_bTrackSelection = bTracking; }
    BOOL		GetTrackSelection	()                       { return m_bTrackSelection; }

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CArrowPicker)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CArrowPicker();

protected:
    void SetWindowSize();

// protected attributes
protected:
    BOOL		m_bActive,                // Is the dropdown active?
				m_bTrackSelection;        // track colour changes?
    int			m_Arrow;
    CRect		m_ArrowRect;
    CImageList   m_image;

    // Generated message map functions
protected:
    //{{AFX_MSG(CArrowPicker)
    afx_msg BOOL OnClicked();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);

    DECLARE_MESSAGE_MAP()
};


/** @class CArrowPicker
 *  @brief Control for choosing different arrow type working with CArrowWnd
 *
 * The CArrowPicker class provides the basic functionality to choose arrow style.
 * It is derived from CButton.
 * 
 * For more information on CArrowPicker, see CArrowWnd.
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
