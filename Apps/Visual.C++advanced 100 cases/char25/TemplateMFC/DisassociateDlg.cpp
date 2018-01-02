// DisassociateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFC.h"
#include "DisassociateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using JetByteTools::CIterateCATID;
using JetByteTools::CComCatInformation;
using JetByteTools::CWin32Exception;
using JetByteTools::CComGUID;

/////////////////////////////////////////////////////////////////////////////
// CDisassociateDlg dialog


CDisassociateDlg::CDisassociateDlg(
	JetByteTools::CGUIDRegistryList &list, 
	CWnd* pParent /*=NULL*/)
	:	CDialog(CDisassociateDlg::IDD, pParent),
		m_list(list),
		m_objectsList(list.Begin(), list.End()),
		m_bImplCatSelected(false),
		m_bReqCatSelected(false) ,
		m_implementsList(CIterateCATID::End(), CIterateCATID::End()),
		m_requiresList(CIterateCATID::End(), CIterateCATID::End())

{
	//{{AFX_DATA_INIT(CDisassociateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDisassociateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisassociateDlg)
	DDX_Control(pDX, IDC_REQUIRE_LIST, m_requiresList);
	DDX_Control(pDX, IDC_IMPLEMENT_LIST, m_implementsList);
	DDX_Control(pDX, IDC_OBJECTS_LIST, m_objectsList);
	DDX_Control(pDX, IDOK, m_OKButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisassociateDlg, CDialog)
	//{{AFX_MSG_MAP(CDisassociateDlg)
	ON_LBN_SELCANCEL(IDC_IMPLEMENT_LIST, OnSelcancelImplementList)
	ON_LBN_SELCHANGE(IDC_IMPLEMENT_LIST, OnSelchangeImplementList)
	ON_LBN_SELCANCEL(IDC_REQUIRE_LIST, OnSelcancelRequireList)
	ON_LBN_SELCHANGE(IDC_REQUIRE_LIST, OnSelchangeRequireList)
	ON_LBN_SELCANCEL(IDC_OBJECTS_LIST, OnSelcancelObjectsList)
	ON_LBN_SELCHANGE(IDC_OBJECTS_LIST, OnSelchangeObjectsList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisassociateDlg message handlers

void CDisassociateDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDisassociateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDisassociateDlg::OnSelcancelImplementList() 
{
	m_bImplCatSelected = false;	

	ManageStateOfOKButton();
}

void CDisassociateDlg::OnSelchangeImplementList() 
{
	m_bImplCatSelected = true;	

	ManageStateOfOKButton();
}

void CDisassociateDlg::OnSelcancelRequireList() 
{
	m_bReqCatSelected = false;	

	ManageStateOfOKButton();
}

void CDisassociateDlg::OnSelchangeRequireList() 
{
	m_bReqCatSelected = true;	

	ManageStateOfOKButton();
}

void CDisassociateDlg::ManageStateOfOKButton()
{
	// Any selected category means we can disassociate...

	m_OKButton.EnableWindow(m_bImplCatSelected || m_bReqCatSelected);
}

void CDisassociateDlg::OnSelcancelObjectsList() 
{
	m_implementsList.DeleteAll();
	m_requiresList.DeleteAll();

	m_bReqCatSelected = false;
	m_bImplCatSelected = false;

	ManageStateOfOKButton();
}

void CDisassociateDlg::OnSelchangeObjectsList() 
{
	// First cancel the previous selections...
	OnSelcancelObjectsList();	

	// Now populate the requires and implements boxes for this
	// object...

	UINT selectedItem = m_objectsList.GetCurSel();

	if (LB_ERR != selectedItem)
	{
		// Now make it so...

		CComGUID *pGuid = m_objectsList.GetItemData(selectedItem);

		if (pGuid)
		{
			try
			{
				::MessageBox(m_hWnd, _T("If your COMCAT.DLL is broken, this will fail!"), 
					_T("Warning"), MB_ICONSTOP);

				CComCatInformation catMgr;

				CIterateCATID implBegin(catMgr.IterateImplCategoriesOfClass(*pGuid));
				CIterateCATID reqBegin(catMgr.IterateReqCategoriesOfClass(*pGuid));

				CIterateCATID end(CIterateCATID::End());

				
				m_implementsList.Populate(implBegin, end);

				m_requiresList.Populate(reqBegin, end);
			}
			catch (CWin32Exception &e)
			{
				e.MessageBox(m_hWnd);
			}
		}
	}

	ManageStateOfOKButton();

}
