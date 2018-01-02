/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  de Halleux Jonathan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact: de Halleux Jonathan, pglinfo@patabelgos.org
*/
#if !defined(AFX_PGLMAPZPROPPAGE_H__DF34D287_C735_45BA_B111_D33B0EFC7A96__INCLUDED_)
#define AFX_PGLMAPZPROPPAGE_H__DF34D287_C735_45BA_B111_D33B0EFC7A96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLMapZPropPage.h : header file
//
#include "PGLMapZ.h"
/////////////////////////////////////////////////////////////////////////////
// CPGLMapZPropPage dialog
#include "PGLMapZ.h"

/*! \brief Height map property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLMapZPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLMapZPropPage)

// Construction
public:
	CPGLMapZPropPage(CPGLMapZ* pMap=NULL);
	~CPGLMapZPropPage();

// Dialog Data
	//{{AFX_DATA(CPGLMapZPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_MAP_Z };
	CString	m_sCM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLMapZPropPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPGLMapZ* m_pMap;
	// Generated message map functions
	//{{AFX_MSG(CPGLMapZPropPage)
	afx_msg void OnSelchangePglComboColormap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLMAPZPROPPAGE_H__DF34D287_C735_45BA_B111_D33B0EFC7A96__INCLUDED_)
