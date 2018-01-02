#if !defined(AFX_PGLPROPERTYSHEET_H__36F21C8A_F088_4A01_8E8E_67B888695318__INCLUDED_)
#define AFX_PGLPROPERTYSHEET_H__36F21C8A_F088_4A01_8E8E_67B888695318__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PGLPropertySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPGLPropertySheet

class CPGLPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPGLPropertySheet)

// Construction
public:
	CPGLPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPGLPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	void SetGraph(CPGLGraph* _pGraph)
	{	m_pGraph=_pGraph;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGLPropertySheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	void FillTree();
	virtual ~CPGLPropertySheet();

	// Generated message map functions
protected:
	CPGLGraph* m_pGraph;
	CTreeCtrl m_tree;
	//{{AFX_MSG(CPGLPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGLPROPERTYSHEET_H__36F21C8A_F088_4A01_8E8E_67B888695318__INCLUDED_)
