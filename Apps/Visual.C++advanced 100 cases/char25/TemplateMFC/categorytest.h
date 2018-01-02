#if !defined(AFX_ATEGORYTEST_H__FD3AB4E8_620A_11D2_BFEB_0020186676FB__INCLUDED_)
#define AFX_ATEGORYTEST_H__FD3AB4E8_620A_11D2_BFEB_0020186676FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ategoryTest.h : header file
//

#include "ComGuidListBox.hpp"
#include "ComCatInformation.hpp"


/////////////////////////////////////////////////////////////////////////////
// CategoryTest dialog

class CategoryTest : public CDialog
{
// Construction
public:
	CategoryTest(
		JetByteTools::CIterateCATEGORYINFO it, 
		CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CategoryTest)
	enum { IDD = IDD_CATEGORY_TEST };
	CButton	m_DisassociateButton;
	CButton	m_AssociateButton;
	CButton	m_RemoveCategoryButton;
	CButton	m_ShowObjectsButton;
	//}}AFX_DATA


protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CategoryTest)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CategoryTest)
	afx_msg void OnShowObjects();
	virtual BOOL OnInitDialog();
	afx_msg void OnRemoveCategory();
	afx_msg void OnAddCategory();
	afx_msg void OnAssociate();
	afx_msg void OnDisassociate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private :

	typedef JetByteTools::TComGUIDListBox<JetByteTools::CIterateCATEGORYINFO, JetByteTools::CComCatInfo> CatListBox;

	void GetCategories(
		CatListBox &list, 
		ULONG *pImplemented, 
		CATID **ppCatidImpl);

	CatListBox m_requiresList;
	CatListBox m_implementsList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATEGORYTEST_H__FD3AB4E8_620A_11D2_BFEB_0020186676FB__INCLUDED_)
