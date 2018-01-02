#if !defined(AFX_PGLLINE2DLODPROPPAGE_H__AFE1E0E5_7EBF_4091_B3CA_123048AFB7A3__INCLUDED_)
#define AFX_PGLLINE2DLODPROPPAGE_H__AFE1E0E5_7EBF_4091_B3CA_123048AFB7A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLLine2DLODPropPage.h : header file
//

#include "PGLLine2DLOD.h"

/////////////////////////////////////////////////////////////////////////////
// CPGLLine2DLODPropPage dialog

/*! \brief 2D line with level of detail property page.

\ingroup PGLPropPageGroup
*/
class PGL_EXT_CLASS CPGLLine2DLODPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLLine2DLODPropPage)


// Construction
public:
	CPGLLine2DLODPropPage(CPGLLine2DLOD* _pLine2DLOD = NULL);
	~CPGLLine2DLODPropPage();

	void SetPointer(CPGLLine2DLOD* _pLine2DLOD)
	{	m_pLine2DLOD=_pLine2DLOD;};
// Dialog Data
	//{{AFX_DATA(CPGLLine2DLODPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_LINE2DLOD };
	int		m_iNbPApprox;
	int		m_iNbPOrig;
	double	m_dTol;
	BOOL	m_dPreview;
	//}}AFX_DATA

protected:
	CPGLLine2DLOD* m_pLine2DLOD;
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLLine2DLODPropPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	// Generated message map functions
	//{{AFX_MSG(CPGLLine2DLODPropPage)
	afx_msg void OnChangePglEditTol();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLLINE2DLODPROPPAGE_H__AFE1E0E5_7EBF_4091_B3CA_123048AFB7A3__INCLUDED_)
