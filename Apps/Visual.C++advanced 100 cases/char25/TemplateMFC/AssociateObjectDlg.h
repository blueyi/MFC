#if !defined(AFX_ASSOCIATEOBJECTDLG_H__92CBAF94_667A_11D2_BFF4_0020186676FB__INCLUDED_)
#define AFX_ASSOCIATEOBJECTDLG_H__92CBAF94_667A_11D2_BFF4_0020186676FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AssociateObjectDlg.h : header file
//

#ifndef __comcat_h__
#include <comcat.h>
#endif

#include "ComGuidListBox.hpp"
#include "GUIDRegistryList.hpp"

/////////////////////////////////////////////////////////////////////////////
// CAssociateObjectDlg dialog

class CAssociateObjectDlg : public CDialog
{
// Construction
public:
	CAssociateObjectDlg(
		JetByteTools::CGUIDRegistryList &list, 
		ULONG cImplemented, 
		CATID *pCatidImpl,
		ULONG cRequired,
		CATID *pCatidReq,
		CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAssociateObjectDlg)
	enum { IDD = IDD_ASSOCIATE_DIALOG };
	CButton	m_OKButton;
	CListBox	m_requireList;
	CListBox	m_implementList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssociateObjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAssociateObjectDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private :

	void FillBox(
		CListBox &box, 
		ULONG cCatids, 
		const CATID *pCatids);


	JetByteTools::CGUIDRegistryList &m_list; 
	JetByteTools::TComGUIDListBox<JetByteTools::CGUIDRegistryList::iterator, JetByteTools::CComGUID>	m_objectsList;
	
	const ULONG m_cImplemented;
	const CATID * const m_pCatidImpl;
	const ULONG m_cRequired;
	const CATID * const m_pCatidReq;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSOCIATEOBJECTDLG_H__92CBAF94_667A_11D2_BFF4_0020186676FB__INCLUDED_)
