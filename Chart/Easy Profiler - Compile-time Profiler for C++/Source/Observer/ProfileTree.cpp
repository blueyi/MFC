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
// ProfileTree.cpp : implementation file
//

#include "stdafx.h"
#include "ProfileTree.h"

#include "uicontroller.h"
// CProfileTree

IMPLEMENT_DYNAMIC(CProfileTree, CXHtmlTree)

CProfileTree::CProfileTree()
{
	theMachine.pHistoryTree=this;
}

CProfileTree::~CProfileTree()
{
}


BEGIN_MESSAGE_MAP(CProfileTree, CXHtmlTree)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()

CString toYellow(CString str)
{
	return _T("<font bgcolor=\"yellow\">")+str+_T("</font>");
}

// CProfileTree message handlers



void CProfileTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CXHtmlTree::OnLButtonDown(nFlags, point);

	HTREEITEM hItem = GetSelectedItem();

	DWORD_PTR ptrAdvise=GetItemData(hItem);

	for (int i=0;i<adviseArray.GetCount();i++)
	{
		CAdvise* pCurAdvise=adviseArray[i];
		//
		if (((DWORD_PTR)pCurAdvise)==ptrAdvise)
		{
			onItemClicked(pCurAdvise->getDataTypeResolver(),pCurAdvise->getUserData());
			return;
		}
	}

}

int CProfileTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXHtmlTree::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	
	return 0;
}

CString getFromSTL(std::string stl_str){

	CString str;
	str.Format(_T("%S"),stl_str.c_str());

	return str;
}

void CProfileTree::renderFile( CTestsFile* pFile,HTREEITEM hParent )
{
	TestsVector::iterator myIt;

	for (myIt = pFile->getTestsVector().begin(); myIt != pFile->getTestsVector().end(); myIt++ ){
		//
		CTest* pSession=*myIt;

		addTest(pSession,hParent);

	}
	Expand(hRoot,TVE_EXPAND);
}

void CProfileTree::addTest( CTest* pSession,HTREEITEM hParent )
{
	CString dispName=CCommonUtilities::toMFCString(pSession->getName())+_T("[")+\
		CCommonUtilities::toMFCString(pSession->getDescription())+_T("]");

	HTREEITEM hTestItem=InsertItem(dispName, 0, 0,hParent);
	setItemUserData(hTestItem,"session",(DWORD_PTR) pSession);


	activityMapT& mainBlocsMap=pSession->getActivitiesMap();
	activityMapT::const_iterator itMain=mainBlocsMap.begin();

	for (; itMain != mainBlocsMap.end(); ++itMain) {
		CActivity* pMainBloc=itMain->second;
		renderActivity(pMainBloc,hTestItem);
	}



	//INSERTING SUBBLOCS 
	taskMapT& subBlocsMap=pSession->getTasksMap();
	taskMapT::const_iterator it=subBlocsMap.begin();

	for (; it != subBlocsMap.end(); ++it) {
		CTask* pSubBloc=it->second;
		renderTask(pSubBloc,hTestItem);
	}


	//INSERTING THREADS : 
	for (workerMapT::iterator wIt=pSession->getWorkersMap().begin();
		wIt!=pSession->getWorkersMap().end();wIt++)
	{
		CWorker* pWorker=wIt->second;
		renderWorker(pWorker,hTestItem);
	}


	Expand(hTestItem,TVE_EXPAND);
}



void CProfileTree::renderActivity( CActivity* pActivity,HTREEITEM hItemActivity )
{
	CString strDuration;
	strDuration.Format(_T("Duration = %f"),pActivity->getTimeElapse());

	CString display=getFromSTL(pActivity->getName())+_T(" ")+toYellow(strDuration);


	HTREEITEM hMainBlocItem=InsertItem(display, 10, 10,hItemActivity);
	setItemUserData(hMainBlocItem,"mainBloc",(DWORD_PTR) pActivity);


	CString strnPoints;
	strnPoints.Format(_T("count = %d"),pActivity->getPointsCount());
	display=_T("Checkpoints ")+toYellow(strnPoints);
	HTREEITEM hMainBlocsPoints=InsertItem(display,14,14,hMainBlocItem);
	setItemUserData(hMainBlocsPoints,"mainBloc_series",(DWORD_PTR) pActivity);
	//
	
	CActivity::PointsVector::iterator myIt;


	for (myIt = pActivity->getPoints().begin(); myIt != pActivity->getPoints().end(); myIt++ )
	{
		CActivity::CCheckPoint* pPoint=*myIt;

		CString strPointTime;
		strPointTime.Format(_T(" time=%fs"),pPoint->getTime());
		CString displayPoint=getFromSTL(pPoint->getName())+strPointTime;

		InsertItem(displayPoint,6,6,hMainBlocsPoints);
	}

	Expand(hMainBlocItem,TVE_EXPAND);
}
void CProfileTree::renderWorker( CWorker* pWorker,HTREEITEM hTestItem )
{
	HTREEITEM hThreadItem=InsertItem(getFromSTL(pWorker->getName()),9,9,hTestItem);


	double avg=(pWorker->getTimeTotal())/((double)pWorker->getRunsCount());
	CString dispPP;
	dispPP.Format(_T("Handle=0x%x AvgWork: %fs jobCounts: %d"),pWorker->getThreadID(),avg,pWorker->getRunsCount());
	HTREEITEM hRunsItem=InsertItem(dispPP,14,14,hThreadItem);
	
	CWorker::runsVectorT::iterator myIt;
	for (myIt = pWorker->getRuns().begin(); myIt != pWorker->getRuns().end(); myIt++ )
	{
		CWorker::CRun* pRun=*myIt;
		//
		CString displayRun;
		displayRun.Format(_T("start = %fs end=%fs duration=%fs"),pRun->getStart(),pRun->getPause(),pRun->getPause()-pRun->getStart());
		InsertItem(displayRun,8,8,hRunsItem);
	}
	Expand(hThreadItem,TVE_EXPAND);
}
void CProfileTree::renderTask( CTask* pTask,HTREEITEM hItemTask )
{
	HTREEITEM hSubBlocItem=InsertItem(getFromSTL(pTask->getName()), 11, 11,hItemTask);

	setItemUserData(hSubBlocItem,"subBloc",(DWORD_PTR) pTask);
	//
	double avg=(pTask->getTimeTotal())/((double)pTask->getRunsCount());
	CString displayTaskPPties;
	displayTaskPPties.Format(_T("runHistory Avg = %fs count=%d"),avg,pTask->getRunsCount());

	HTREEITEM hRunsItem=InsertItem(displayTaskPPties,14,14,hSubBlocItem);
	//

	CTask::runsVectorT::iterator myIt;
	for (myIt = pTask->getRuns().begin(); myIt != pTask->getRuns().end(); myIt++ )
	{
		CTask::CRun* pRun=*myIt;
		//
		CString displayRun;
		displayRun.Format(_T("start = %fs end=%fs duration=%fs threadID=0x%x"),pRun->getStart(),pRun->getStop(),pRun->getStop()-pRun->getStart(),pRun->getThreadID());
		InsertItem(displayRun,8,8,hRunsItem);

	}
	Expand(hSubBlocItem,TVE_EXPAND);
}



void CProfileTree::initTree()
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




	Initialize(FALSE, FALSE)
		.SetSmartCheckBox(TRUE)
		.SetHtml(true)
		.SetStripHtml(FALSE)
		.SetImages(TRUE)
		.SetReadOnly(false)
		.SetDragOps(XHTMLTREE_DO_DEFAULT);
		//.SetDropCursors(IDC_NODROP, IDC_DROPCOPY, IDC_DROPMOVE);
	//.SetSeparatorColor(RGB(0,0,255))
	//



	CString str=_T("All files [");
	str+=_T("<font bgcolor=\"yellow\">");
	str+=_T("12");
	str+=_T("</font>");
	str+=_T("]");

	hRoot=InsertItem(_T("All files ")/*+toYellow(_T("total=12"))*/, 5, 5);
	SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);
}

CProfileTree::CAdvise* CProfileTree::resolveItemAdvise( HTREEITEM hItem )
{
	DWORD_PTR ptrAdvise=GetItemData(hItem);

	for (int i=0;i<adviseArray.GetCount();i++)
	{
		CAdvise* pCurAdvise=adviseArray[i];
		//
		if (((DWORD_PTR)pCurAdvise)==ptrAdvise)
		{
			return (CAdvise*)ptrAdvise;
		}
	}
	return NULL;
}
void CProfileTree::onItemClicked( std::string dataTypeResolver,DWORD_PTR pUserData )
{
	//MessageBoxA(NULL,dataTypeResolver.c_str(),"onItemClicked",MB_OK);
	if(dataTypeResolver=="mainBloc")
		theMachine.onDrawMainBlocSeries((CActivity*)pUserData);
	if (dataTypeResolver=="subBloc")
	{
		theMachine.onDrawTasksRunsAsColumn((CTask*)pUserData);
	}
	if(dataTypeResolver=="mainBloc_series")
		theMachine.onDrawMainBlocDPs((CActivity*)pUserData);
}
void CProfileTree::onItemDropped( HTREEITEM hDropSource,HTREEITEM hDropTarget )
{
	/*
	AfxMessageBox(_T(""));
	CString display;
	display.Format(_T("onItemDropped :\n %s \n %s"),
	GetItemText(hDropSource),
	GetItemText(hDropTarget));
	AfxMessageBox(display);*/
	CAdvise* pSourceAdvise=resolveItemAdvise(hDropSource);
	CAdvise* pTargetAdvise=resolveItemAdvise(hDropTarget);
	if(pSourceAdvise==NULL || pTargetAdvise==NULL)
		return;
	if(pSourceAdvise->getDataTypeResolver()=="Tasks" &&
		pTargetAdvise->getDataTypeResolver()=="mainBloc")
	{
		theMachine.onDrawSubBlocsContributionToAMainBloc((CActivity*)pTargetAdvise->getUserData());
	}
	if(pSourceAdvise->getDataTypeResolver()=="subBloc" &&
		pTargetAdvise->getDataTypeResolver()=="mainBloc")
	{
		theMachine.onDrawSubBlocContributionToAMainBloc((CActivity*)pTargetAdvise->getUserData(),(CTask*)pSourceAdvise->getUserData());
	}
	
}

void CProfileTree::deleteTest( CTest* pTest )
{
	for (int i=0;i<adviseArray.GetCount();i++)
	{
		CAdvise* pAdvise=adviseArray[i];
		if (pAdvise->getDataTypeResolver()=="session" && 
			pAdvise->getUserData()==(DWORD_PTR)pTest)
		{
			DeleteItem(pAdvise->GetHTREE());
			adviseArray.RemoveAt(i);
			return;
		}
	}
}

void CProfileTree::updateTestDisplayText( CTest* pTest )
{
	for (int i=0;i<adviseArray.GetCount();i++)
	{
		CAdvise* pAdvise=adviseArray[i];
		if (pAdvise->getDataTypeResolver()=="session" && 
			pAdvise->getUserData()==(DWORD_PTR)pTest)
		{
			
			CString dispName=CCommonUtilities::toMFCString(pTest->getName())+_T("[")+\
				CCommonUtilities::toMFCString(pTest->getDescription())+_T("]");

			SetItemText(pAdvise->GetHTREE(),dispName);
			return;
		}
	}
}