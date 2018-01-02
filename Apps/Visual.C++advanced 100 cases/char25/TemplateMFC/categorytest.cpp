// ategoryTest.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFC.h"
#include "TemplateMFCDlg.h"
#include "CategoryTest.h"
#include "AssociateObjectDlg.h"
#include "DisassociateDlg.h"

#include "CategoryNameDlg.h"

#include "ComCatInformation.hpp"
#include "ComCatRegister.hpp"

#include "Utils.hpp"
#include "OleString.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using JetByteTools::CGUIDRegistryList;
using JetByteTools::CRegistryKey;
using JetByteTools::CIterateGUID;
using JetByteTools::CIterateCATEGORYINFO;
using JetByteTools::CComCatInfo;
using JetByteTools::CComCatInformation;
using JetByteTools::CComCatRegister;
using JetByteTools::CWin32Exception;


/////////////////////////////////////////////////////////////////////////////
// CategoryTest dialog


CategoryTest::CategoryTest(
	JetByteTools::CIterateCATEGORYINFO it, 
	CWnd* pParent /*=NULL*/)
	:	CDialog(CategoryTest::IDD, pParent),
		m_requiresList(it, CIterateCATEGORYINFO::End()),
		m_implementsList(it, CIterateCATEGORYINFO::End())
{
	//{{AFX_DATA_INIT(CategoryTest)
	//}}AFX_DATA_INIT
}


void CategoryTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CategoryTest)
	DDX_Control(pDX, IDC_DISASSOCIATE, m_DisassociateButton);
	DDX_Control(pDX, IDC_ASSOCIATE, m_AssociateButton);
	DDX_Control(pDX, IDC_REMOVE_CATEGORY, m_RemoveCategoryButton);
	DDX_Control(pDX, IDC_SHOW_OBJECTS, m_ShowObjectsButton);
	DDX_Control(pDX, IDC_REQUIRE_LIST, m_requiresList);
	DDX_Control(pDX, IDC_IMPLEMENT_LIST, m_implementsList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CategoryTest, CDialog)
	//{{AFX_MSG_MAP(CategoryTest)
	ON_BN_CLICKED(IDC_SHOW_OBJECTS, OnShowObjects)
	ON_BN_CLICKED(IDC_REMOVE_CATEGORY, OnRemoveCategory)
	ON_BN_CLICKED(IDC_ADD_CATEGORY, OnAddCategory)
	ON_BN_CLICKED(IDC_ASSOCIATE, OnAssociate)
	ON_BN_CLICKED(IDC_DISASSOCIATE, OnDisassociate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CategoryTest message handlers

void CategoryTest::OnShowObjects() 
{
	// See what we want implemented...

	ULONG cImplemented = 0;
	CATID *pCatidImpl = 0;

	GetCategories(m_implementsList, &cImplemented, &pCatidImpl);

	// And what the object requires...

	ULONG cRequired = 0;
	CATID *pCatidReq = 0;

	GetCategories(m_requiresList, &cRequired, &pCatidReq);

	// Access the category manager...

	try
	{
	   CComCatInformation catMgr;

		// Grab an iterator onto objetcts that meet our requirements...

		CIterateGUID catBegin = catMgr.IterateClassesOfCategories(
			cImplemented,
			pCatidImpl, 
			cRequired, 
			pCatidReq);

		// Open the key
		CRegistryKey key = CRegistryKey(HKEY_LOCAL_MACHINE).CreateOrOpenKey(_T("SOFTWARE\\JetByte\\RegList"));

		// Point the list at it
		CGUIDRegistryList list(key);

		// Todo: It would be nice, if we could list all of the objects on the system
		// if we don't select any implemented categories...

		CTemplateMFCDlg dlg(
			list,
			catBegin,
			CIterateGUID::End(),
			this);

		dlg.DoModal();
	}
	catch (CWin32Exception &e)
	{
		e.MessageBox(m_hWnd);
	}


	delete [] pCatidImpl;
	delete [] pCatidReq;
}

BOOL CategoryTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Associate all of the buttons with the implements list, they will remain 
	// grayed out until at least one item is highlighted in the list...

	m_implementsList.AssociateButton(
      m_AssociateButton);

	m_implementsList.AssociateButton(
      m_ShowObjectsButton);

	// This button should only highlight on a single selection

	m_implementsList.AssociateButton(
      m_RemoveCategoryButton, JetByteTools::CJBListBox::SingleSelection);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CategoryTest::GetCategories(
	CatListBox &list, 
	ULONG *pImplemented, 
	CATID **ppCatidImpl)
{
	ASSERT(pImplemented);
	ASSERT(ppCatidImpl);

	// Get all of the items that are selected, allocate an array for them
	// pull out the things and copy them into the array...
	int numSelected = list.GetSelectionCount();

	if (numSelected != LB_ERR && numSelected != 0)
	{
		int *pSelectedItems = new int[numSelected];

		int selected = list.GetSelectedItems(numSelected, pSelectedItems);

		ASSERT(selected == numSelected);

		CATID *pCatidArray = new CATID[numSelected];

		for (int i = 0; i < numSelected; i++)
		{
			CComCatInfo *pCatInfo = list.GetItemData(pSelectedItems[i]);

			ASSERT(pCatInfo);
			
			pCatidArray[i] = pCatInfo->GetCATID();
		}

		delete [] pSelectedItems;

		*pImplemented = (ULONG)numSelected;
		*ppCatidImpl = pCatidArray;
	}
}

void CategoryTest::OnRemoveCategory() 
{
	if (IDYES == MessageBox(
		_T("Removing a Componet Category that you didn't create could cause problems for any application which uses the category. Are you sure you want to continue?"), 
		_T("Remove Component Category"), 
		MB_ICONSTOP | MB_YESNO | MB_DEFBUTTON2))
	{
		// Remove from lists
		// Remove from category manager...

		int selectedItem;

		if (LB_ERR != m_implementsList.GetSelItems(1, &selectedItem))
		{
			CComCatInfo *pCatInfo = m_implementsList.GetItemData(selectedItem);

			ASSERT(pCatInfo);

			GUID catid = pCatInfo->GetCATID();

			CString description = pCatInfo->GetDescription();

			// Don't need pCatInfo now and it's soon to become invalid...
			pCatInfo = 0;

			if (IDYES == MessageBox(
				_T("Are you sure you want to delete: ") + description,
				_T("Are you sure?"), 
				MB_ICONSTOP | MB_YESNO | MB_DEFBUTTON2))
			{
				// Remove from list it's not selected in...
				m_requiresList.DeleteItem(m_requiresList.FindString(-1, description));

				// Remove from list it's selected in...
				m_implementsList.DeleteItem(selectedItem);

				// Now delete the category from the component category manager...

				try
				{
					CComCatRegister catMgr;
				
					catMgr.UnRegisterCategories(&catid);

					MessageBox(
						_T("Category: ") +  description + _T(" - successfully deleted"),
						_T("Category Deleted"), 
						MB_ICONINFORMATION);
				}
				catch (CWin32Exception &e)
				{
					e.MessageBox(m_hWnd);
				}
			}
			else
			{
				MessageBox(
					_T("Category: ") +  description + _T(" - NOT deleted"),
					_T("Category Not Deleted"), 
					MB_ICONINFORMATION);
			}
		}
	}
}

void CategoryTest::OnAddCategory() 
{
	// Generate a GUID

	CLSID catid;

	HRESULT hr = CoCreateGuid(&catid);

	if (SUCCEEDED(hr))
	{
		// Prompt for a name

		CCategoryNameDlg dlg(this);

		if (IDOK == dlg.DoModal() && dlg.GetName() != "")
		{
			CString catDesc = dlg.GetName();

			if (IDYES == MessageBox(
				_T("Are you sure you want to add the category: ") + catDesc, 
				_T("Add Category"), 
				MB_ICONQUESTION | MB_YESNO))
			{
				// Create a CATEGORYINFO structure...

				CATEGORYINFO catInfo;

				catInfo.catid = catid;
				catInfo.lcid = GetUserDefaultLCID(); 
				wcsncpy(catInfo.szDescription, JetByteTools::_O(catDesc), 127);

				// Access the Component Category Manager...

				try
				{
					CComCatRegister catMgr;

					// Make it so...

					catMgr.RegisterCategories(&catInfo);

					// Add to the lists...

					m_requiresList.AddItem(catDesc, new CComCatInfo(catInfo));
					m_implementsList.AddItem(catDesc, new CComCatInfo(catInfo));

					MessageBox(
						_T("Category: ") + catDesc + _T(" - successfully added"),
						_T("Category Added"),
						MB_ICONINFORMATION);
				}
				catch (CWin32Exception &e)
				{
					e.MessageBox(m_hWnd);
				}
			}
		}
	}		
	else
	{
		MessageBox(
			JetByteTools::GetLastErrorMessage(hr), 
			_T("Failed to generate a GUID"), 
			MB_ICONSTOP);
	}
}

void CategoryTest::OnAssociate() 
{
	// See what we want implemented...
	ULONG cImplemented = 0;
	CATID *pCatidImpl = 0;

	GetCategories(m_implementsList, &cImplemented, &pCatidImpl);

	// And what the object requires...

	ULONG cRequired = 0;
	CATID *pCatidReq = 0;

	GetCategories(m_requiresList, &cRequired, &pCatidReq);

	// Open the key
	CRegistryKey key = CRegistryKey(HKEY_CLASSES_ROOT).OpenKey(_T("CLSID"));

	// Point the list at it - this was never intended for this kind of use...
	CGUIDRegistryList list(key);

	CAssociateObjectDlg dlg(
		list,
		cImplemented, 
		pCatidImpl, 
		cRequired, 
		pCatidReq, 
		this);
	
	dlg.DoModal();
}

using JetByteTools::CIterateCATID;
using JetByteTools::CComCatInformation;
using JetByteTools::CWin32Exception;
using JetByteTools::CComGUID;

void CategoryTest::OnDisassociate() 
{
	// Open the key
	CRegistryKey key = CRegistryKey(HKEY_CLASSES_ROOT).OpenKey(_T("CLSID"));

	// Point the list at it - this was never intended for this kind of use...
	CGUIDRegistryList list(key);
	
	CDisassociateDlg dlg(list, this);
	
	dlg.DoModal();
}
