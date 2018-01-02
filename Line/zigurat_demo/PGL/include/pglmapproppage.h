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
#if !defined(AFX_PGLMAPPROPPAGE_H__8E1EAF89_5673_4ED9_8541_391ECCB82287__INCLUDED_)
#define AFX_PGLMAPPROPPAGE_H__8E1EAF89_5673_4ED9_8541_391ECCB82287__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLMapPropPage.h : header file
//

#include "PGLMap.h"

/////////////////////////////////////////////////////////////////////////////
// CPGLMapPropPage dialog

/*! \brief 2D Map property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLMapPropPage : public CPropertyPage
{
// Construction
public:
	CPGLMapPropPage(CPGLMap* pMap=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPGLMapPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_MAP };
	double	m_dDx;
	double	m_dDy;
	int		m_iNx;
	int		m_iNxNy;
	int		m_iNy;
	double	m_dLeft;
	double	m_dTop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGLMapPropPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void SetMap(CPGLMap* pMap)
	{	m_pMap=pMap;};
protected:
	CPGLMap* m_pMap;

	// Generated message map functions
	//{{AFX_MSG(CPGLMapPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLMAPPROPPAGE_H__8E1EAF89_5673_4ED9_8541_391ECCB82287__INCLUDED_)
