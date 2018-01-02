////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2002, SVizSoft, All rights reserved.
//
// FILE:     HatchWellBtn.h
//			$Revision: 1.1.1.1 $
//			$Date: 2002/11/06 22:08:50 $
//			$Author: tzhu $ of last update
//
// CREATOR:    Tao Zhu
//
// DESCRIPTION
//    Class defination for class CSVizHatchWell. 
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HATCHWELLWND_H__EBF4CD97_65C2_4F2E_8599_9F1D8A99B2F9__INCLUDED_)
#define AFX_HATCHWELLWND_H__EBF4CD97_65C2_4F2E_8599_9F1D8A99B2F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wellbtn.h"

/////////////////////////////////////////////////////////////////////////////
// CSVizHatchWell window

class SVIZDLLEXPORT CSVizHatchWell : public CSVizWellCtrl
{
    DECLARE_DYNCREATE(CSVizHatchWell)
// Construction
public:
	CSVizHatchWell();

// Operations
public:
	virtual ~CSVizHatchWell();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVizHatchWell)
	//}}AFX_VIRTUAL
public:
    virtual CString GetWellName		(int nIndex)           { return m_hatchName[nIndex]; }

public:
    virtual void	Initialise		();
	virtual void	DrawCellContent (CDC* pDC, int nIndex, CRect rect, BYTE state);

// protected attributes
protected:
    static CString m_hatchName[];
// Implementation

	// Generated message map functions
protected:
	//{{AFX_MSG(CSVizHatchWell)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/** @class CSVizHatchWell
 *  @brief Class for picking different style of Hatch (see GDI+ HatchStyle)
 *
 * CSVizHatchWell send message to the parent windows that owns it.
 * See the message defined in the head file of CSVizWellCtrl.
 *
 * For more information on CSVizHatchWell, see CSVizWellCtrl.
 */
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HATCHWELLWND_H__EBF4CD97_65C2_4F2E_8599_9F1D8A99B2F9__INCLUDED_)
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
