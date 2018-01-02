/********************************************************************
    File:	        TestSelectionPane	
    Creation Date:	2009/11/01
	
	Author: 	    Ahmed Charfeddine
					info@potatosoftware.com

	License:        Copyright [2009] [Potato software]

					Licensed under the Apache License, Version 2.0 (the "License");
					you may not use this file except in compliance with the License.
					You may obtain a copy of the License at

							http://www.apache.org/licenses/LICENSE-2.0

					Unless required by applicable law or agreed to in writing, software
					distributed under the License is distributed on an "AS IS" BASIS,
					WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
					See the License for the specific language governing permissions and
					limitations under the License.
    
	Note :	  		
*********************************************************************/
// TestSelectionPane.cpp : implementation file
//

#include "stdafx.h"
#include "Observer.h"
#include "TestSelectionPane.h"

#include "uicontroller.h"

// CTestSelectionTree

IMPLEMENT_DYNAMIC(CTestSelectionTree, CXHtmlTree)

CTestSelectionTree::CTestSelectionTree()
{
	theMachine.pSelectionTestTree=this;
}

CTestSelectionTree::~CTestSelectionTree()
{
}

BEGIN_MESSAGE_MAP(CTestSelectionTree, CXHtmlTree)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CTestSelectionTree message handlers

void CTestSelectionTree::initTree()
{
	CBitmap bmp;
	if (!bmp.LoadBitmap (IDB_TREESMALL))
	{
		ASSERT (FALSE);
		return ;
	}
	m_Images.Create (16, 16, ILC_MASK|ILC_COLOR24, 0, 0);
	m_Images.Add (&bmp, RGB(255,255,255));

	SetImageList (&m_Images, TVSIL_NORMAL);


	Initialize(TRUE, FALSE)
		.SetSmartCheckBox(TRUE)
		.SetHtml(true)
		.SetStripHtml(FALSE)
		.SetImages(TRUE)
		.SetReadOnly(false)
		.SetDragOps(XHTMLTREE_DO_DEFAULT);
	//.SetDropCursors(IDC_NODROP, IDC_DROPCOPY, IDC_DROPMOVE);
	//.SetSeparatorColor(RGB(0,0,255))
	//


	
}

int CTestSelectionTree::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if (CXHtmlTree::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here


	return 0;
}

void CTestSelectionTree::updateTests( CString regionName,std::vector<CTest*> testsVector )
{
	DeleteAllItems();

	CString str=_T("Available tests for :")+regionName;

	hRoot=InsertItem(str, 5, 5);
	SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

	std::vector<CTest*>::iterator myIt;
	for (myIt=testsVector.begin();myIt!=testsVector.end();myIt++)
	{
		CTest* pTest=*myIt;

		HTREEITEM hItem=InsertItem(CCommonUtilities::toMFCString(pTest->getDescription()), 0, 0,hRoot);
		SetItemData(hItem,(DWORD_PTR)pTest);
	}
}

std::vector<CTest*> CTestSelectionTree::getSelectedTests()
{
	std::vector<CTest*> selectedTestsVect;

	HTREEITEM hCurrent = GetChildItem(hRoot);
	while (hCurrent != NULL) 
	{
		
		bool bChecked=GetCheck(hCurrent);

		if(bChecked)
		{
/*
			AfxMessageBox(_T("Item checked =")+GetItemText(hCurrent));
*/
			CTest* pTest=(CTest*) GetItemData(hCurrent);
			selectedTestsVect.push_back(pTest);
		}
		

		// Try to get the next item
		hCurrent = GetNextItem(hCurrent, TVGN_NEXT);
		//
	}
	return selectedTestsVect;
}