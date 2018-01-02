// TemplateMFCDlg.h : header file
//

#if !defined(AFX_TEMPLATEMFCDLG_H__129DF4F8_5FA5_11D2_BFE7_0020186676FB__INCLUDED_)
#define AFX_TEMPLATEMFCDLG_H__129DF4F8_5FA5_11D2_BFE7_0020186676FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ComGuidListBox.hpp"
#include "GUIDRegistryList.hpp"
#include "IterateGUID.hpp"

class ListItemProcessor : public JetByteTools::CJBListBox::ItemProcessor
{
   public :

      ListItemProcessor(
         JetByteTools::CGUIDRegistryList &regList,
         JetByteTools::TComGUIDListBox<JetByteTools::CGUIDRegistryList::iterator, JetByteTools::CComGUID> &listBox,
			bool bAddItem);

      virtual void ProcessSelectedItem(
         const int nIndex,                      
         const CString &,              
         void *pData,                           
         JetByteTools::CJBListBox::PostProcessAction_e &);

   private :

		const bool m_bAddItem;

      JetByteTools::CGUIDRegistryList &m_regList;
      JetByteTools::TComGUIDListBox<JetByteTools::CGUIDRegistryList::iterator, JetByteTools::CComGUID> &m_listBox;
};


/////////////////////////////////////////////////////////////////////////////
// CTemplateMFCDlg dialog

class CTemplateMFCDlg : public CDialog
{
// Construction
public:
	CTemplateMFCDlg(
	JetByteTools::CGUIDRegistryList &list, 
	JetByteTools::CIterateGUID &catStart,
	const JetByteTools::CIterateGUID &catEnd,
	CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTemplateMFCDlg)
	enum { IDD = IDD_TEMPLATEMFC_DIALOG };
//	CButton	m_RemoveButton;
//	CButton	m_AddButton;
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTemplateMFCDlg)
	virtual BOOL OnInitDialog();
//	afx_msg void OnAdd();
//	afx_msg void OnRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	JetByteTools::TComGUIDListBox<JetByteTools::CGUIDRegistryList::iterator, JetByteTools::CComGUID>	m_RegistryList;
	JetByteTools::TComGUIDListBox<JetByteTools::CIterateGUID, JetByteTools::CComGUID> m_CategoryContentsList;
	JetByteTools::CGUIDRegistryList &m_list;

	ListItemProcessor m_removeProcessor;
	ListItemProcessor m_addProcessor;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLATEMFCDLG_H__129DF4F8_5FA5_11D2_BFE7_0020186676FB__INCLUDED_)
