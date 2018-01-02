#if !defined(AFX_PGLMAPVECTORPROPPAGE_H__74858A02_426C_4A5D_8BD0_FD1DE5E8C168__INCLUDED_)
#define AFX_PGLMAPVECTORPROPPAGE_H__74858A02_426C_4A5D_8BD0_FD1DE5E8C168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLMapVectorPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGLMapVectorPropPage dialog

/*! \brief Vector field property page.

\ingroup PGLPropPageGroup
*/
class CPGLMapVectorPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPGLMapVectorPropPage)

// Construction
public:
	CPGLMapVectorPropPage(CPGLMapVector* pMapVector = NULL);
	~CPGLMapVectorPropPage();

	void SetMapVector(CPGLMapVector* pMapVector)
	{	m_pMapVector = pMapVector;};
// Dialog Data
	//{{AFX_DATA(CPGLMapVectorPropPage)
	enum { IDD = IDD_PGL_PROPPAGE_MAP_VECTORFIELD };
	double	m_dLineWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPGLMapVectorPropPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPGLMapVector* m_pMapVector;
	// Generated message map functions
	//{{AFX_MSG(CPGLMapVectorPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLMAPVECTORPROPPAGE_H__74858A02_426C_4A5D_8BD0_FD1DE5E8C168__INCLUDED_)
