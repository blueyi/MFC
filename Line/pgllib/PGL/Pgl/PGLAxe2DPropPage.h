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
#if !defined(AFX_PGLAXE2DPROPPAGE_H__649AE70A_8577_45BD_9674_0718C5612B22__INCLUDED_)
#define AFX_PGLAXE2DPROPPAGE_H__649AE70A_8577_45BD_9674_0718C5612B22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLAxe2DPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGLAxe2DPropPage dialog

/*! \brief 2D axis property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLAxe2DPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLAxe2DPropPage)

// Construction
public:
	CPGLAxe2DPropPage(CPGLAxe2D* _pAxe2D = NULL);
	~CPGLAxe2DPropPage();

	void SetPointer(CPGLAxe2D* _pAxe2D)
	{	ASSERT_VALID(_pAxe2D); m_pAxe2D=_pAxe2D;};

// Dialog Data
	//{{AFX_DATA(CPGLAxe2DPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_AXE2D };
	BOOL	m_bHorGrid;
	BOOL	m_bVertGrid;
	BOOL	m_bXAuto;
	double	m_dXStep;
	BOOL	m_bYAuto;
	double	m_dYStep;
	BOOL	m_bBotLbl;
	CString	m_sBotLbl;
	CString	m_sLeftLbl;
	CString	m_sTopLbl;
	BOOL	m_bLeftLbl;
	BOOL	m_bRightLbl;
	BOOL	m_bTopLbl;
	CString	m_sRightLbl;
	BOOL	m_bNumberBottom;
	BOOL	m_bNumberLeft;
	BOOL	m_bNumberRight;
	BOOL	m_bNumberTop;
	int		m_slNumberBottom;
	int		m_slNumberLeft;
	int		m_slNumberRight;
	int		m_slNumberTop;
	CTime	m_tTimeOriginH;
	CTime	m_tTimeStep;
	CTime	m_tTimeOrigin;
	UINT	m_iDays;
	CString	m_sTimeFormat;
	BOOL	m_bTimeLabel;
	BOOL	m_bLogX;
	BOOL	m_bLogY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLAxe2DPropPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	CPGLAxe2D* m_pAxe2D;
	// Generated message map functions
	//{{AFX_MSG(CPGLAxe2DPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLAXE2DPROPPAGE_H__649AE70A_8577_45BD_9674_0718C5612B22__INCLUDED_)
