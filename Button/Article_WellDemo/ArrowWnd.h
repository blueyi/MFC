////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2002, SVizSoft, All rights reserved.
//
// FILE:     arrowwnd.h
//			$Revision: 1.1.1.1 $
//			$Date: 2002/11/06 22:08:49 $
//			$Author: tzhu $ of last update
//
// CREATOR:    Tao Zhu
//
// DESCRIPTION
//    Class defination for class CSVizArrowWell. 
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARROWWND_H__)
#define AFX_ARROWWND_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "wellbtn.h"

// To hold the Arrows and their names
typedef SVIZDLLEXPORT struct {
    int crArrow;
    TCHAR    *szName;
} ArrowTableEntry;

//struct ArrowTableEntry;
/////////////////////////////////////////////////////////////////////////////
// CSVizArrowWell window

class SVIZDLLEXPORT CSVizArrowWell : public CSVizWellCtrl
{
    DECLARE_DYNCREATE(CSVizArrowWell)
// Construction
public:
    CSVizArrowWell		();
    CSVizArrowWell		(CPoint p, int arrowType, CWnd* pParentWnd, DWORD);

public:
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSVizArrowWell)
    public:
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual			~CSVizArrowWell		();
    int				GetArrow		(int nIndex)   { return m_Arrows[nIndex].crArrow; }
    void			DrawCellContent	(CDC*, int, CRect, BYTE);
    CString			GetWellName		(int nIndex)   { return m_Arrows[nIndex].szName; }
//    BOOL			Create			(CPoint, int , CWnd* );
    virtual void	Initialise		();

protected:

// protected attributes
protected:
    static	ArrowTableEntry m_Arrows[];
    CImageList		m_image;
//    int             m_crInitialArrow, 
//					m_crArrow;

    // Generated message map functions
protected:
    //{{AFX_MSG(CSVizArrowWell)
    afx_msg void OnPaint();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/** @class CSVizArrowWell
 *  @brief Control for choosing different Arrow stype
 *
 * The CSVizArrowWell class provides the basic functionality to choose arrow style
 * It is derived from CSVizWellCtrl.
 * 
 * For more information on CSVizArrowWell, see CSVizWellCtrl and CArrowPicker.
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
