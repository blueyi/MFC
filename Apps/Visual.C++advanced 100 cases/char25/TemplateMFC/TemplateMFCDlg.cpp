// TemplateMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFC.h"
#include "TemplateMFCDlg.h"
#include "ComGUID.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using JetByteTools::CComGUID;


ListItemProcessor::ListItemProcessor(
   JetByteTools::CGUIDRegistryList &regList,
   JetByteTools::TComGUIDListBox<JetByteTools::CGUIDRegistryList::iterator, JetByteTools::CComGUID> &listBox,
	bool bAddItem)
	:  m_bAddItem(bAddItem),
		m_regList(regList),
      m_listBox(listBox)
{
}

void ListItemProcessor::ProcessSelectedItem(
   const int /* nIndex */,                      
   const CString &description,              
   void *pData,                           
   JetByteTools::CJBListBox::PostProcessAction_e &action)
{
   // This should be type safe anyway, pData should come in as a CComGUID
   // This means more template work...

   CComGUID *pGuid = (CComGUID*)pData;

	if (m_bAddItem)
	{
		// We're called to add an item to the list...
		if (!m_regList.HasItem(*pGuid))
      {
			m_regList.Add(*pGuid);
			m_listBox.AddItem(description, new CComGUID(*pGuid));

			action = JetByteTools::CJBListBox::Unselect;
      }
      else
      {
         ::MessageBox(NULL, _T("Item already present in list"), _T("Error"), MB_ICONSTOP);
      }
	}
	else
	{
		// Remove item from list box and registry list

		m_regList.Remove(*pGuid);
		
	   action = JetByteTools::CJBListBox::Delete;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTemplateMFCDlg dialog

CTemplateMFCDlg::CTemplateMFCDlg(
	JetByteTools::CGUIDRegistryList &list, 
	JetByteTools::CIterateGUID &catStart,
	const JetByteTools::CIterateGUID &catEnd,
	CWnd* pParent /*=NULL*/)
	:	CDialog(CTemplateMFCDlg::IDD, pParent),
		m_list(list),
		m_RegistryList(list.Begin(), list.End()),
		m_CategoryContentsList(catStart, catEnd),
		m_removeProcessor(m_list, m_RegistryList, false),
		m_addProcessor(m_list, m_RegistryList, true)
{
	//{{AFX_DATA_INIT(CTemplateMFCDlg)
	//}}AFX_DATA_INIT
}

void CTemplateMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplateMFCDlg)
	DDX_Control(pDX, IDC_CAT_LIST, m_CategoryContentsList);
	DDX_Control(pDX, IDC_REGISTRY_LIST, m_RegistryList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTemplateMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CTemplateMFCDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateMFCDlg message handlers

BOOL CTemplateMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Clicking the remove button OR double clicking an item in the registry
	// list causes it to be removed...

	m_RegistryList.AssociateButton(
      IDC_REMOVE, &m_removeProcessor);
	
	m_RegistryList.SetDefaultProcessor(&m_removeProcessor);

	// Clicking the add button OR double clicking the item in the category
	// list causes the object to be added to the registry list

	m_CategoryContentsList.AssociateButton(
      IDC_ADD, &m_addProcessor);
	
	m_CategoryContentsList.SetDefaultProcessor(&m_addProcessor);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

//put these in item processors and do it properly for both clicks in the list and button clicks

/*
void CTemplateMFCDlg::OnAdd() 
{
	// add item that's selected in category list to registry list and list box
	
	int nIndex = m_CategoryContentsList.GetCurSel();

	if (LB_ERR != nIndex)
	{		
		CString description;
	
		m_CategoryContentsList.GetText(nIndex, description);

		CComGUID *pGuid = m_CategoryContentsList.GetItemData(nIndex);
	
		if (!m_list.HasItem(*pGuid))
      {
			m_list.Add(*pGuid);
			m_RegistryList.AddItem(description, new CComGUID(*pGuid));
      }
      else
      {
         MessageBox( _T("Item already present in list"), _T("Error"), MB_ICONSTOP);
      }
	}
}
*/
/*void CTemplateMFCDlg::OnRemove() 
{
	// Remove item from list box and registry list

	int nIndex = m_RegistryList.GetCurSel();

	if (LB_ERR != nIndex)
	{		
		CComGUID *pGuid = m_RegistryList.GetItemData(nIndex);

		m_list.Remove(*pGuid);
		
		m_RegistryList.DeleteItem(nIndex);
	}
}
*/
