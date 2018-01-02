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
#if !defined(AFX_PGLTEXTPROPPAGE_H__EACBD19F_C8E6_4CBC_97C8_1D75881D068A__INCLUDED_)
#define AFX_PGLTEXTPROPPAGE_H__EACBD19F_C8E6_4CBC_97C8_1D75881D068A__INCLUDED_

#include "PGLText.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLTextPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGLTextPropPage dialog

/*! \brief Text property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLTextPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLTextPropPage)

// Construction
public:
	CPGLTextPropPage(CPGLText* _pText=NULL);
	~CPGLTextPropPage();

// Dialog Data
	//{{AFX_DATA(CPGLTextPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_TEXT };
	CString	m_sText;
	float	m_fAngle;
	int		m_rAlign;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLTextPropPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	CPGLText* m_pText;
	// Generated message map functions
	//{{AFX_MSG(CPGLTextPropPage)
	afx_msg void OnPglButtonChooseFont();
	afx_msg void OnKillfocusPglEditStrinText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLTEXTPROPPAGE_H__EACBD19F_C8E6_4CBC_97C8_1D75881D068A__INCLUDED_)
