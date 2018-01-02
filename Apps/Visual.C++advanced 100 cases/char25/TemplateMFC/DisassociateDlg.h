#if !defined(AFX_DISASSOCIATEDLG_H__29BBB0B8_68A9_11D2_BFFA_0020186676FB__INCLUDED_)
#define AFX_DISASSOCIATEDLG_H__29BBB0B8_68A9_11D2_BFFA_0020186676FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DisassociateDlg.h : header file
//

#include "ComGuidListBox.hpp"
#include "ComCatInformation.hpp"
#include "GUIDRegistryList.hpp"

/////////////////////////////////////////////////////////////////////////////
// CDisassociateDlg dialog

class CDisassociateDlg : public CDialog
{
// Construction
public:
	CDisassociateDlg(
		JetByteTools::CGUIDRegistryList &list, 
		CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDisassociateDlg)
	enum { IDD = IDD_DISASSOCIATE_DIALOG };
	CButton	m_OKButton;
	//}}AFX_DATA

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisassociateDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CDisassociateDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelcancelImplementList();
	afx_msg void OnSelchangeImplementList();
	afx_msg void OnSelcancelRequireList();
	afx_msg void OnSelchangeRequireList();
	afx_msg void OnSelcancelObjectsList();
	afx_msg void OnSelchangeObjectsList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private :

	void ManageStateOfOKButton();

	bool m_bImplCatSelected;
	bool m_bReqCatSelected;

	typedef JetByteTools::TComGUIDListBox<JetByteTools::CIterateCATID, JetByteTools::CComCatInfo> CatListBox;
	typedef JetByteTools::TComGUIDListBox<JetByteTools::CGUIDRegistryList::iterator, JetByteTools::CComGUID>	RegGUIDListBox;
	
	JetByteTools::CGUIDRegistryList &m_list; 
	
	RegGUIDListBox m_objectsList;
	CatListBox	m_requiresList;
	CatListBox	m_implementsList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISASSOCIATEDLG_H__29BBB0B8_68A9_11D2_BFFA_0020186676FB__INCLUDED_)
