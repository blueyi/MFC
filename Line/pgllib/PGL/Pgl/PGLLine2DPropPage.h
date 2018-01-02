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
#if !defined(AFX_PGLLINE2DPROPPAGE_H__CF898C40_8166_11D4_8267_00A024D26A1F__INCLUDED_)
#define AFX_PGLLINE2DPROPPAGE_H__CF898C40_8166_11D4_8267_00A024D26A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLLine2D.h"

/////////////////////////////////////////////////////////////////////////////
// CPGLLine2DPropPage dialog

/*! \brief 2D line property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLLine2DPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLLine2DPropPage)

// Construction
public:
	CPGLLine2DPropPage(CPGLLine2D* _pLine2D=NULL);
	~CPGLLine2DPropPage();

	void SetPointer(CPGLLine2D* _pLine2D)
	{	ASSERT_VALID(_pLine2D); m_pLine2D=_pLine2D;};

// Dialog Data
	//{{AFX_DATA(CPGLLine2DPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_LINE2D };
	int		m_nPoints;
	BOOL	m_bShowEnd;
	BOOL	m_bShowStart;
	double	m_dLengthEnd;
	double	m_dThickEnd;
	double	m_dLengthStart;
	double	m_dThickStart;
	BOOL	m_bFill;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLLine2DPropPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPGLLine2D* m_pLine2D;
	// Generated message map functions
	//{{AFX_MSG(CPGLLine2DPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINE2DGLPAGE_H__CF898C40_8166_11D4_8267_00A024D26A1F__INCLUDED_)
