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
#if !defined(AFX_PGLOBJECTPROPPAGE_H__CF898C3D_8166_11D4_8267_00A024D26A1F__INCLUDED_)
#define AFX_PGLOBJECTPROPPAGE_H__CF898C3D_8166_11D4_8267_00A024D26A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectGLPropPage.h : header file
//

#include "PGLObject.h"

/////////////////////////////////////////////////////////////////////////////
// CPGLObjectPropPage dialog

/*!
	\defgroup PGLPropPageGroup Property pages.
	\ingroup PGLDialogGroup
*/

/*! \brief Graphical object property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLObjectPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLObjectPropPage)

// Construction
public:
	CPGLObjectPropPage(CPGLObject* _pObject=NULL);
	~CPGLObjectPropPage();

	void setObjectGL(CPGLObject* _pObject)
	{	pObject=_pObject;};
// Dialog Data
	//{{AFX_DATA(CPGLObjectPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_COBJECT };
	BOOL	m_selected;
	BOOL	m_visible;
	CString	m_name;
	float	m_alpha;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLObjectPropPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPGLObjectPropPage)
	afx_msg void OnButtonChangeColor();
	afx_msg void OnCheckSelected();
	afx_msg void OnCheckVisible();
	afx_msg void OnKillfocusEditName();
	afx_msg void OnKillfocusEditAlpha();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CPGLObject* pObject;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTGLPROPPAGE_H__CF898C3D_8166_11D4_8267_00A024D26A1F__INCLUDED_)
