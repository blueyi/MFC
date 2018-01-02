// AssociateObjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFC.h"
#include "AssociateObjectDlg.h"
#include "ComCatInformation.hpp"
#include "ComCatRegister.hpp"
#include "ComGUID.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using JetByteTools::CComCatInformation;
using JetByteTools::CComCatRegister;
using JetByteTools::CWin32Exception;
using JetByteTools::CComGUID;

/////////////////////////////////////////////////////////////////////////////
// CAssociateObjectDlg dialog


CAssociateObjectDlg::CAssociateObjectDlg(
	JetByteTools::CGUIDRegistryList &list, 
	ULONG cImplemented, 
	CATID *pCatidImpl,
	ULONG cRequired,
	CATID *pCatidReq,
	CWnd* pParent /*=NULL*/)
	:	CDialog(CAssociateObjectDlg::IDD, pParent),
		m_list(list),
		m_objectsList(list.Begin(), list.End()),
		m_cImplemented(cImplemented),
		m_pCatidImpl(pCatidImpl),
		m_cRequired(cRequired),
		m_pCatidReq(pCatidReq)
{
	//{{AFX_DATA_INIT(CAssociateObjectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAssociateObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssociateObjectDlg)
	DDX_Control(pDX, IDOK, m_OKButton);
	DDX_Control(pDX, IDC_OBJECTS_LIST, m_objectsList);
	DDX_Control(pDX, IDC_REQUIRE_LIST, m_requireList);
	DDX_Control(pDX, IDC_IMPLEMENT_LIST, m_implementList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssociateObjectDlg, CDialog)
	//{{AFX_MSG_MAP(CAssociateObjectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssociateObjectDlg message handlers

BOOL CAssociateObjectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Associate the OK button with the list of objects, it will remain 
	// grayed out until an item is highlighted in the list...

	m_objectsList.AssociateButton(
      m_OKButton);

	FillBox(m_implementList, m_cImplemented, m_pCatidImpl);

	FillBox(m_requireList, m_cRequired, m_pCatidReq);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAssociateObjectDlg::FillBox(
	CListBox &box, 
	ULONG cCatids, 
	const CATID *pCatids)
{
	try
	{
		CComCatInformation catMgr;

		for (UINT i = 0; i < cCatids; i++)
		{
			LPCTSTR lpCatDesc = catMgr.GetCategoryDesc(pCatids[i]);

			box.AddString(lpCatDesc);

			free((void*)lpCatDesc);
		}
	}
	catch (CWin32Exception &e)
	{
		e.MessageBox(m_hWnd);
	}
}

void CAssociateObjectDlg::OnOK() 
{
	// Need to get the GUID and description of the selected object...

	UINT selectedItem = m_objectsList.GetCurSel();

	if (LB_ERR != selectedItem)
	{
		// Now make it so...

		CComGUID *pGuid = m_objectsList.GetItemData(selectedItem);

		if (pGuid)
		{
			try
			{
				CComCatRegister catMgr;

				if (m_cImplemented != 0)
				{
					catMgr.RegisterClassImplCategories(*pGuid, (GUID*)m_pCatidImpl, m_cImplemented);
				}

				if (m_cRequired != 0)
				{
					catMgr.RegisterClassReqCategories(*pGuid, (GUID*)m_pCatidReq, m_cRequired);
				}

				MessageBox(
					_T("Object: ") + CString(pGuid->GetDescription()) + _T(" - successfully associated with categories"),
					_T("Done"),
					MB_ICONINFORMATION);
			}
			catch(CWin32Exception &e)
			{
				e.MessageBox(m_hWnd);
			}
		}
	}

	CDialog::OnOK();
}
