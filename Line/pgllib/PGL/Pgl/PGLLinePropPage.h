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
#if !defined(AFX_PGLLINEPROPPAGE_H__CF898C3E_8166_11D4_8267_00A024D26A1F__INCLUDED_)
#define AFX_PGLLINEPROPPAGE_H__CF898C3E_8166_11D4_8267_00A024D26A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineGLPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGLLinePropPage dialog
#include "PGLLine.h"

/*! \brief Line property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLLinePropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLLinePropPage)

// Construction
public:
	CPGLLinePropPage(CPGLLine* _pLine=NULL);
	~CPGLLinePropPage();

	void SetLineGL(CPGLLine* _pLine)
	{	ASSERT_VALID(_pLine); m_pLine=_pLine;};


// Dialog Data
	//{{AFX_DATA(CPGLLinePropPage)
	enum { IDD = IDD_PGL_PROPPAGE_LINE };
	float	m_lineWidth;
	float	m_pointWidth;
	int		m_lineType;
	int		m_pointType;
	int		m_iInterpolationType;
	UINT	m_iStripSize;
	BOOL	m_bFilled;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLLinePropPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPGLLine* m_pLine;
	// Generated message map functions
	//{{AFX_MSG(CPGLLinePropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLLINEPROPPAGE_H__CF898C3E_8166_11D4_8267_00A024D26A1F__INCLUDED_)
