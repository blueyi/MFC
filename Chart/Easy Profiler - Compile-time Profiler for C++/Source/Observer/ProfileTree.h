/********************************************************************
    File:	        ProfileTree	
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
#pragma once

#include "xHTML/XHtmlTree.h"
#include "resource.h"
class CUIControler;

// CProfileTree

class CProfileTree : public CXHtmlTree
{
	DECLARE_DYNAMIC(CProfileTree)

public:
	CProfileTree();
	virtual ~CProfileTree();
public:
	class CAdvise{
	private:
		DWORD_PTR pUserData;
		std::string dataTypeResolver;
		HTREEITEM hItem;
	public:
		CAdvise(std::string dataTypeResolver,HTREEITEM hItem,DWORD_PTR pUserData){
			this->dataTypeResolver=dataTypeResolver;
			this->pUserData=pUserData;
			this->hItem=hItem;
		}
		DWORD_PTR getUserData(){
			return pUserData;
		}
		std::string getDataTypeResolver(){
			return dataTypeResolver;
		}
		HTREEITEM GetHTREE()
		{
			return hItem;
		}
	};
	CArray<CAdvise*> adviseArray;
	CAdvise* resolveItemAdvise(HTREEITEM hItem);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
protected:
	DECLARE_MESSAGE_MAP()


	virtual void onItemClicked(std::string dataTypeResolver,DWORD_PTR pUserData);
private:
	
	CImageList m_Images;
	void setItemUserData(HTREEITEM hItem,std::string dataTypeResolver,DWORD_PTR pUserData){
		CAdvise* pNewAdvise=new CAdvise(dataTypeResolver,hItem,pUserData);
		SetItemData(hItem,(DWORD_PTR)pNewAdvise);
		adviseArray.Add(pNewAdvise);
	}
public:
	HTREEITEM hRoot;
	void initTree();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void renderFile(CTestsFile* pFile,HTREEITEM hParent);
	HTREEITEM createSuiteTreeItem(CString dirName)
	{
		HTREEITEM hSuiteItem=InsertItem(dirName, 5, 5,hRoot);

		std::string strResolver=std::string("folder ")+CCommonUtilities::toBasicString(dirName);
		setItemUserData(hSuiteItem,strResolver,0);
		return hSuiteItem;
	}
	HTREEITEM findSuiteTreeItem(std::string folderName)
	{
		for (int i=0;i<adviseArray.GetCount();i++)
		{
			CAdvise* pAdvise=adviseArray[i];
			//
			if(pAdvise->getDataTypeResolver()==(std::string("folder ")+folderName))
			{
				return pAdvise->GetHTREE();
			}
		}
	}

	void addTest(CTest* pSession,HTREEITEM hParent);

	void renderActivity(CActivity* pActivity,HTREEITEM hItemActivity);
	void renderTask(CTask* pTask,HTREEITEM hItemTask);
	void renderWorker(CWorker* pWorker,HTREEITEM hTestItem);



	virtual void onItemDropped(HTREEITEM hDropSource,HTREEITEM hDropTarget);

	void deleteTest(CTest* pTest);
	void updateTestDisplayText(CTest* pTest);
	void deleteFile()
	{
		//
	}
	void deletFolder()
	{
		//
	}
};


