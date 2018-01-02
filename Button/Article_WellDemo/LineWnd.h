////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2002, SVizSoft, All rights reserved.
//
// FILE:     LineWnd.h
//			$Revision: 1.1.1.1 $
//			$Date: 2002/11/06 22:08:50 $
//			$Author: tzhu $ of last update
//
// CREATOR:    Tao Zhu
//
// DESCRIPTION
//    Class defination for class CSVizLineStyleWell.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LineWND_H__)
#define AFX_LineWND_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "wellbtn.h"
// To hold the Lines and their names
typedef SVIZDLLEXPORT struct {
    int crLine;
    TCHAR    *szName;
} LineTableEntry;

//struct LineTableEntry;
/////////////////////////////////////////////////////////////////////////////
// CSVizLineStyleWell window

class SVIZDLLEXPORT CSVizLineStyleWell : public CSVizWellCtrl
{
	DECLARE_DYNCREATE(CSVizLineStyleWell)
// Construction
public:
    CSVizLineStyleWell();
    CSVizLineStyleWell(CPoint p, int LineType, int, CWnd* pParentWnd, DWORD);
    void			Initialise			();
	virtual void	DrawCellContent     (CDC*, int, CRect, BYTE);

// Attributes
public:

// Operations
public:
//    BOOL			Create				(CPoint p, int crLine, CWnd* pParentWnd, DWORD dwWinStyle = WS_VISIBLE|WS_POPUP);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSVizLineStyleWell)
    public:
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CSVizLineStyleWell();

protected:

    LPCTSTR GetLineName(int nIndex)           { return m_Lines[nIndex].szName; }

// protected attributes
protected:
    static			LineTableEntry m_Lines[];
//    int				m_crWell ,
//					m_crInitialWell;
    CImageList		m_image;
    // Generated message map functions
protected:
    //{{AFX_MSG(CSVizLineStyleWell)
    afx_msg void OnPaint();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/** @class CSVizLineStyleWell
 *  @brief Control for choosing different LineStyle
 *
 * The CSVizLineStyleWell class provides the basic functionality to choose line (dash) style
 * It is derived from CSVizWellCtrl and typically has only one column.
 * 
 * For more information on CSVizLineStyleWell, see CSVizWellCtrl, CLinePicker.
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
