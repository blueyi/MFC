// ProfileTree.cpp : implementation file
//

#include "stdafx.h"
#include "ProfileTree.h"

#include "BusinessMachine.h"
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

void CProfileTree::renderFile( CTestsCollection* pFile )
{
	TestsVector::iterator myIt;

	for (myIt = pFile->getTestsVector().begin(); myIt != pFile->getTestsVector().end(); myIt++ ){
		//
		CTestSession* pSession=*myIt;

		addSession(pSession);

	}
	ExpandAll();
}

void CProfileTree::addSession( CTestSession* pSession )
{
	HTREEITEM hItem=InsertItem(getFromSTL(pSession->getName()), 0, 0,hRoot);

	setItemUserData(hItem,"session",(DWORD_PTR) pSession);


	//INSERTING MAINBLOCS :
	HTREEITEM hMainBlocs=InsertItem(_T("Activities"),1,1,hItem);



	MainBlocsMap& mainBlocsMap=pSession->GetObservationMap();
	MainBlocsMap::const_iterator itMain=mainBlocsMap.begin();

	for (; itMain != mainBlocsMap.end(); ++itMain) {
		CActivity* pMainBloc=itMain->second;


		renderActivity(pMainBloc,hMainBlocs);
	}



	//INSERTING SUBBLOCS 
	SubBlocksMap& subBlocsMap=pSession->GetSubBlocsMap();



	HTREEITEM hSubBlocs=InsertItem(_T("Tasks"),3,3,hItem);
	setItemUserData(hSubBlocs,"Tasks",(DWORD_PTR) 0);


	SubBlocksMap::const_iterator it=subBlocsMap.begin();

	for (; it != subBlocsMap.end(); ++it) {
		CTask* pSubBloc=it->second;
		renderTask(pSubBloc,hSubBlocs);
	}


	//INSERTING THREADS : 
	HTREEITEM hThreads=InsertItem(_T("Workers"),2,2,hItem);
	
	HTREEITEM hThread1=InsertItem(_T("Image Fetcher"),1,1,hThreads);
	InsertItem(_T("Handle=0x223"),2,2,hThread1);
	InsertItem(_T("Total 14s: jobCounts: 12"),2,2,hThread1);

	HTREEITEM hThread2=InsertItem(_T("Renderer"),1,1,hThreads);
	InsertItem(_T("Handle=0x211"),2,2,hThread2);
	InsertItem(_T("Total 14s: jobCounts: 12"),2,2,hThread2);

}



void CProfileTree::renderActivity( CActivity* pActivity,HTREEITEM hItemActivity )
{
	CString strDuration;
	strDuration.Format(_T("Duration = %f"),pActivity->getTimeElapse());

	CString display=getFromSTL(pActivity->getName())+_T(" ")+toYellow(strDuration);


	HTREEITEM hMainBlocItem=InsertItem(display, 1, 1,hItemActivity);
	setItemUserData(hMainBlocItem,"mainBloc",(DWORD_PTR) pActivity);


	CString strnPoints;
	strnPoints.Format(_T("count = %d"),pActivity->getPointsCount());
	display=_T("Checkpoints ")+toYellow(strnPoints);
	HTREEITEM hMainBlocsPoints=InsertItem(display,4,4,hMainBlocItem);
	setItemUserData(hMainBlocsPoints,"mainBloc_series",(DWORD_PTR) pActivity);
	//
	
	CActivity::PointsVector::iterator myIt;


	for (myIt = pActivity->getPoints().begin(); myIt != pActivity->getPoints().end(); myIt++ )
	{
		CActivity::CSPoint* pPoint=*myIt;
		InsertItem(getFromSTL(pPoint->getName())+_T(" time=1.s"),6,6,hMainBlocsPoints);
	}
}

void CProfileTree::renderTask( CTask* pTask,HTREEITEM hItemTask )
{
	HTREEITEM hSubBlocItem=InsertItem(getFromSTL(pTask->getName()), 3, 3,hItemTask);

	setItemUserData(hSubBlocItem,"subBloc",(DWORD_PTR) pTask);
	//
	InsertItem(_T("Total = 3.6s count=12"),14,14,hSubBlocItem);
	HTREEITEM hRunsItem=InsertItem(_T("runHistory"),8,8,hSubBlocItem);
	//

	CTask::runsVectorT::iterator myIt;
	for (myIt = pTask->getRuns().begin(); myIt != pTask->getRuns().end(); myIt++ )
	{
		CTask::CRun* pRun=*myIt;
		//
		InsertItem(_T("start = 3.6s end=12 duration=3.7"),9,9,hRunsItem);

	}

}

void CProfileTree::renderThreads( HTREEITEM hItemThread )
{
	//
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

	hRoot=InsertItem(_T("All files ")+toYellow(_T("total=12")), 5, 5);
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