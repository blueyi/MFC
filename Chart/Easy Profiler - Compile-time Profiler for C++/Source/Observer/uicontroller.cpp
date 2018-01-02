/********************************************************************
    File:	        UIControler	
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
#include "StdAfx.h"
#include "Observer.h"

#include "uicontroller.h"

#include "MainFrm.h"
#include "ProfileTree.h"
#include "TestSelectionPane.h"
#include "ChartControl.h"

#include "AnalysisTool.h"
#include "CompareTool.h"



CUIControler::CUIControler(void)
{
	curToolCommand=0;
}

CUIControler::~CUIControler(void)
{
	//
}

CUIControler theMachine;


CTest* CUIControler::getParentSession( CActivity* pMainBlocThis )
{
	return pMainBlocThis->getParentTest();
	/*
	for (int i=0;i<filesArray.GetCount();i++)
		{
			TestsVector testsVect=filesArray[i]->getTestsVector();
			//
			TestsVector::iterator myIt;
	
	
			for (myIt = testsVect.begin(); myIt != testsVect.end(); myIt++ ){
				CTest* pSession=*myIt;
				//
				if(pSession->containsActivity(pMainBlocThis))
					return pSession;
			}
		}
		return NULL;*/
	
}

CTest* CUIControler::getParentSession( CTask* pSubBloc )
{
	return pSubBloc->getParentTest();
/*
	for (int i=0;i<filesArray.GetCount();i++)
	{
		TestsVector testsVect=filesArray[i]->getTestsVector();
		//
		TestsVector::iterator myIt;


		for (myIt = testsVect.begin(); myIt != testsVect.end(); myIt++ ){
			CTest* pSession=*myIt;
			//
			if(pSession->containsTask(pSubBloc))
				return pSession;
		}
	}
	return NULL;*/

}

CString toMFCString(std::string stl_str){

	CString str;
	str.Format(_T("%S"),stl_str.c_str());

	return str;
}
void CUIControler::openHistoryFile()
{
	TCHAR  szFilters[]=
		_T("XML (*.xml)");
	CFileDialog filedlg(TRUE,_T("xml"),_T("*.xml"),0,szFilters);

	if (filedlg.DoModal()==IDOK)
	{
		if (filedlg.GetPathName().IsEmpty())
		{
			return;
		}
	}
	else
	{
		return;
	}


	std::string filePath=CCommonUtilities::toBasicString(filedlg.GetPathName());

	testsFilesMapT::iterator myIt=testsFilesMap.find(filePath);
	if(myIt!=testsFilesMap.end())
	{
		AfxMessageBox(_T("Already opened"));
		return;
	}


	CTestsFile* pTests=openFile(filePath);
	if (pTests)
	{
		pHistoryTree->renderFile(pTests,pHistoryTree->hRoot);
		addFileToHomeCombo(filedlg.GetPathName());
	}
	//
}

void CUIControler::OnOpenTestSuite()
{
	CString m_strSelectedFolder;
	if (!theApp.GetShellManager()->BrowseForFolder(m_strSelectedFolder, AfxGetMainWnd(), m_strSelectedFolder))
		return;
	

	std::string folderPath=CCommonUtilities::toBasicString(m_strSelectedFolder);
	//
	for (foldersVectorT::iterator myIt=foldersVector.begin();
		myIt!=foldersVector.end();myIt++)
	{
		std::string thisFolderPath=*myIt;
		if (thisFolderPath==folderPath)
		{
			AfxMessageBox(_T("Already opened, choose update instead"));
			return;
		}
	}


	CStringArray files;

	CFileFind finder;
	BOOL bWorking = finder.FindFile(m_strSelectedFolder+_T("/*.xml"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		files.Add(finder.GetFilePath());
	} 

	if (files.GetCount()!=0)
	{
		HTREEITEM hSuiteItem=pHistoryTree->createSuiteTreeItem(m_strSelectedFolder);
		foldersVector.push_back(folderPath);
		addFolderToHomeCombo(m_strSelectedFolder);
		//
		for (int i=0;i<files.GetCount();i++)
		{
			std::string filePath=CCommonUtilities::toBasicString(files[i]);

			testsFilesMapT::iterator myIt=testsFilesMap.find(filePath);
			if(myIt==testsFilesMap.end())
			{
				CTestsFile* pTests=openFile(filePath);
				if (pTests)
				{
					pTests->setParentFolder(folderPath);
					pHistoryTree->renderFile(pTests,hSuiteItem);
				}
			}	
		}
	}
	else
	{
		AfxMessageBox(_T("Folder is empty"));
	}	
}





void CUIControler::onDrawMainBlocSeries( CActivity* pSelectedBloc )
{

}

void CUIControler::onDrawMainBlocDPs( CActivity* pSelectedBloc )
{
	
	
}

void CUIControler::onDrawSubBlocsContributionToAMainBloc( CActivity* pSelectedBloc )
{
	CTest* pParentSession=getParentSession(pSelectedBloc);
	if(pParentSession==NULL)
		return;

	chartControl.resetSeries();
	chartControl.addSeries(pSelectedBloc->getName(),CChartControl::Pie);
	


	double activityDuration=pSelectedBloc->getTimeElapse();
	//
	taskMapT::const_iterator it=pParentSession->getTasksMap().begin();
	for (; it != pParentSession->getTasksMap().end(); ++it) {
		CTask* pCurBloc=it->second;
		//Calculate current bloc contribution.



		double total=pCurBloc->measureTimeContribution(pSelectedBloc->getStart(),
			pSelectedBloc->getStop());


		activityDuration-=total;
		//
		chartControl.addPoint(pSelectedBloc->getName(),
			pCurBloc->getName(),
			total);

	}

	chartControl.addPoint(pSelectedBloc->getName(),
		_T("uncounted"),
		activityDuration);

}

void CUIControler::onDrawTasksRunsAsColumn( CTask* pTask )
{
	
}

void CUIControler::onDrawSubBlocContributionToAMainBloc( CActivity* pActivity,CTask* pTask )
{
	
}



void CUIControler::updateAnalysisFeatureTargetCombos() /*Triggered by updateTestsCombo */ /*or by a combo ui sel change event. */
{
	//Find the new test then populate combos with child features.
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pAnalyseTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_TEST_SELECT));
	if (pAnalyseTestsCombo == NULL)
	{
		return;
	}
	int iSel=pAnalyseTestsCombo->GetCurSel();
	if (iSel==-1)
	{
		return;
	}
	DWORD_PTR dwData=pAnalyseTestsCombo->GetItemData(iSel);

	CTest* pSession=(CTest*)dwData;

	//AfxMessageBox(CCommonUtilities::toMFCString(pSession->getName()));
	CMFCRibbonComboBox* pAllItemsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_ITEM_SELECT));
	CMFCRibbonComboBox* pTasksForActivityCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_SINGLEACTIVITY_CB_TASKSEL));
	CMFCRibbonComboBox* pWorkerForActivityCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_SINGLEACTIVITY_CB_WORKERSEL));
	CMFCRibbonComboBox* pTaskForWorkerCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_SINGLEWORKER_CB_SELTASK));
	//
	pAllItemsCombo->RemoveAllItems();
	pTasksForActivityCombo->RemoveAllItems();
	pWorkerForActivityCombo->RemoveAllItems();
	pTaskForWorkerCombo->RemoveAllItems();
	//

	activityMapT& mainBlocsMap=pSession->getActivitiesMap();
	activityMapT::const_iterator itMain=mainBlocsMap.begin();

	for (; itMain != mainBlocsMap.end(); ++itMain) {
		CActivity* pActivity=itMain->second;
		pAllItemsCombo->AddItem(CCommonUtilities::toMFCString(pActivity->getName()),(DWORD_PTR)pActivity);
	}


	taskMapT& subBlocsMap=pSession->getTasksMap();
	taskMapT::const_iterator it=subBlocsMap.begin();

	for (; it != subBlocsMap.end(); ++it) {
		CTask* pTask=it->second;
		pAllItemsCombo->AddItem(CCommonUtilities::toMFCString(pTask->getName()),(DWORD_PTR)pTask);
		pTasksForActivityCombo->AddItem(CCommonUtilities::toMFCString(pTask->getName()),(DWORD_PTR)pTask);
		pTaskForWorkerCombo->AddItem(CCommonUtilities::toMFCString(pTask->getName()),(DWORD_PTR)pTask);

	}

	for (workerMapT::iterator wIt=pSession->getWorkersMap().begin();
		wIt!=pSession->getWorkersMap().end();
		wIt++)
	{
		CWorker* pWorker=wIt->second;
		//
		pAllItemsCombo->AddItem(CCommonUtilities::toMFCString(pWorker->getName()),(DWORD_PTR)pWorker);
		pWorkerForActivityCombo->AddItem(CCommonUtilities::toMFCString(pWorker->getName()),(DWORD_PTR)pWorker);
	}
}

void CUIControler::updateCompareFeatureTargetCombos()
{
	//Find the new test then populate combos with child features.
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pAnalyseTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_COMPARE_FOCUS_SELTEST));
	if (pAnalyseTestsCombo == NULL)
	{
		return;
	}
	int iSel=pAnalyseTestsCombo->GetCurSel();
	if (iSel==-1)
	{
		return;
	}

	CString strRegionName=pAnalyseTestsCombo->GetItem(iSel);


	std::vector<CTest*> matchingTests=getMatchingTests(CCommonUtilities::toBasicString(strRegionName));
	std::vector<CTest*>::iterator testsIt;
	
	if(matchingTests.empty())
	{
		AfxMessageBox(_T("no matching test found"));
		return;
	}

	//Now First update the selection pane :
	pSelectionTestTree->updateTests(strRegionName,matchingTests);


	CTest* pSession=matchingTests.front();
	//AfxMessageBox(CCommonUtilities::toMFCString(pSession->getName()));
	
	CMFCRibbonComboBox* pAllItemsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_COMPARE_FOCUS_SELITEM));
	CMFCRibbonComboBox* pTasksForActivityCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_COMPARE_SINGLEACTIVITY_SELTASK));
	CMFCRibbonComboBox* pWorkerForActivityCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_COMPARE_SINGLEACTIVITY_SELWORKER));
	CMFCRibbonComboBox* pTaskForWorkerCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_COMPARE_SINGLEWORKER_SELTASK));
	//
	pAllItemsCombo->RemoveAllItems();
	pTasksForActivityCombo->RemoveAllItems();
	pWorkerForActivityCombo->RemoveAllItems();
	pTaskForWorkerCombo->RemoveAllItems();
	//

	activityMapT& mainBlocsMap=pSession->getActivitiesMap();
	activityMapT::const_iterator itMain=mainBlocsMap.begin();

	for (; itMain != mainBlocsMap.end(); ++itMain) {
		CActivity* pActivity=itMain->second;
		pAllItemsCombo->AddItem(CCommonUtilities::toMFCString(pActivity->getName()),(DWORD_PTR)pActivity->getType());
	}

	taskMapT& subBlocsMap=pSession->getTasksMap();
	taskMapT::const_iterator it=subBlocsMap.begin();

	for (; it != subBlocsMap.end(); ++it) {
		CTask* pTask=it->second;
		pAllItemsCombo->AddItem(CCommonUtilities::toMFCString(pTask->getName()),(DWORD_PTR)pTask->getType());
		pTasksForActivityCombo->AddItem(CCommonUtilities::toMFCString(pTask->getName()),(DWORD_PTR)pTask->getType());
		pTaskForWorkerCombo->AddItem(CCommonUtilities::toMFCString(pTask->getName()),(DWORD_PTR)pTask->getType());
	}

	for (workerMapT::iterator wIt=pSession->getWorkersMap().begin();
		wIt!=pSession->getWorkersMap().end();
		wIt++)
	{
		CWorker* pWorker=wIt->second;
		//
		pAllItemsCombo->AddItem(CCommonUtilities::toMFCString(pWorker->getName()),(DWORD_PTR)pWorker->getType());
		pWorkerForActivityCombo->AddItem(CCommonUtilities::toMFCString(pWorker->getName()),(DWORD_PTR)pWorker->getType());
	}
}



void CUIControler::addTestsCollectionToRibbonCombos( CTestsFile* pCollection )
{
	/*
	WM_COMPARE_FOCUS_SELTEST
	WM_ANALYSIS_TEST_SELECT
	*/
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pAnalyseTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_TEST_SELECT));
	CMFCRibbonComboBox* pCompareTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_COMPARE_FOCUS_SELTEST));
	


	TestsVector::iterator myIt;

	for (myIt = pCollection->getTestsVector().begin(); myIt != pCollection->getTestsVector().end(); myIt++ ){
		//
		CTest* pSession=*myIt;

		//AfxMessageBox(CCommonUtilities::toMFCString(pSession->getName()));
		CString dispName=CCommonUtilities::toMFCString(pSession->getName())+_T("[")+\
			CCommonUtilities::toMFCString(pSession->getDescription())+_T("]");

		pAnalyseTestsCombo->AddItem(CCommonUtilities::toMFCString(dispName),(DWORD_PTR)pSession);
		pCompareTestsCombo->AddItem(CCommonUtilities::toMFCString(pSession->getName()));

	}
}

CFeature* CUIControler::getAnalysisTarget()
{
	return getFeatureByComboID(WM_ANALYSIS_ITEM_SELECT);
}
CFeature* CUIControler::getAnalysisTaskForActivityTarget()
{
	return getFeatureByComboID(WM_ANALYSIS_SINGLEACTIVITY_CB_TASKSEL);
}

CFeature* CUIControler::getAnalysisWorkerForActivityTarget()
{
	return getFeatureByComboID(WM_ANALYSIS_SINGLEACTIVITY_CB_WORKERSEL);
}

CFeature* CUIControler::getAnalysisTaskForWorkerTarget()
{
	return getFeatureByComboID(WM_ANALYSIS_SINGLEWORKER_CB_SELTASK);
}

/*
CFeature::Type CBusinessMachine::getCompareTarget()
{
return getFeatureTypeByComboID(WM_COMPARE_FOCUS_SELITEM);
}

CFeature::Type CBusinessMachine::getCompareTaskForActivityTarget()
{
return getFeatureByComboID(WM_COMPARE_SINGLEACTIVITY_SELTASK);
}

CFeature::Type CBusinessMachine::getCompareWorkerForActivityTarget()
{
return getFeatureByComboID(WM_COMPARE_SINGLEACTIVITY_SELWORKER);
}

CFeature::Type CBusinessMachine::getCompareTaskForWorkerTarget()
{
return getFeatureByComboID(WM_COMPARE_SINGLEWORKER_SELTASK);
}*/

void CUIControler::routeCompareCommand( int commandID )
{
	CCompareTool* pTool=NULL;
	try
	{
		pTool=factory2.create(commandID);
	}
	catch(not_registered ex)
	{
		std::string str(ex.what());
		CString strWhat=CCommonUtilities::toMFCString(str);

		AfxMessageBox(_T("exception :")+strWhat);
		return;
	}
	//
	CFeature::Type targetType;
	CString targetName;

	if (pTool->getTargetType()!=CFeature::None)
	{
		if(!getCompareFeatureTargetInfo(WM_COMPARE_FOCUS_SELITEM,targetName,targetType))
		{
			AfxMessageBox(_T("Please select a feature item"));
			return;
		}

		if (targetType!=pTool->getTargetType())
		{
			//.
			AfxMessageBox(_T("Please select the correct feature item"));
			return;
		}
	}
	
	//
	CFeature::Type extraTargetType=CFeature::None;
	CString extraTargetName;

	if(pTool->getTargetType()==CFeature::Activity)
	{
		switch (pTool->getExtraTargetType())
		{
		case CFeature::Task:
			if (!getCompareFeatureTargetInfo(WM_COMPARE_SINGLEACTIVITY_SELTASK,extraTargetName,extraTargetType))
			{
				AfxMessageBox(_T("missing feature"));
				return;
			}
			break;
		case CFeature::Worker:
			if (!getCompareFeatureTargetInfo(WM_COMPARE_SINGLEACTIVITY_SELWORKER,extraTargetName,extraTargetType))
			{
				AfxMessageBox(_T("missing feature"));
				return;
			}
			break;
		default:
			break;

		}
	}
	if (pTool->getTargetType()==CFeature::Worker)
	{
		if (pTool->getExtraTargetType()==CFeature::Task)
		{
			if (!getCompareFeatureTargetInfo(WM_COMPARE_SINGLEWORKER_SELTASK,extraTargetName,extraTargetType))
			{
				AfxMessageBox(_T("missing item"));
				return;
			}
		}
	}

	//
	//Now trigger the compareTool :
	pTool->execute(pSelectionTestTree->getSelectedTests(),CCommonUtilities::toBasicString(targetName),
		CCommonUtilities::toBasicString(extraTargetName));
	pTool->render();
	//
	curToolCommand=commandID;

}
void CUIControler::routeAnalysisCommand( int commandID )
{
	CAnalysisTool* pTool=NULL;
	try
	{
		pTool=factory.create(commandID);
	}
	catch (not_registered ex)
	{
		std::string str(ex.what());
		CString strWhat=CCommonUtilities::toMFCString(str);

		AfxMessageBox(_T("exception :")+strWhat);
		return;
	}
	//
	CFeature* pTarget=NULL;
	if (pTool->getTargetType()!=CFeature::None)
	{
		pTarget=getAnalysisTarget();
		if(pTarget==NULL)
		{
			//.
			AfxMessageBox(_T("Please select a feature item"));
			return;
		}
		if (pTarget->getType()!=pTool->getTargetType())
		{
			//.
			AfxMessageBox(_T("Please select the correct feature item"));
			return;
		}
	}
	
	
	

	//
	CFeature* pExtraTarget=NULL;
	if (pTool->getTargetType()==CFeature::Activity &&
		pTool->getExtraTargetType()==CFeature::Task)
	{
		pExtraTarget=getAnalysisTaskForActivityTarget();
		if(pExtraTarget==NULL)
		{
			//.
			AfxMessageBox(_T("Please select missing item"));
			return;
		}
	}

	if (pTool->getTargetType()==CFeature::Activity &&
		pTool->getExtraTargetType()==CFeature::Worker)
	{
		pExtraTarget=getAnalysisWorkerForActivityTarget();
		if(pExtraTarget==NULL)
		{
			//.
			AfxMessageBox(_T("Please select missing item"));
			return;
		}
	}

	if (pTool->getTargetType()==CFeature::Worker &&
		pTool->getExtraTargetType()==CFeature::Task)
	{
		pExtraTarget=getAnalysisTaskForWorkerTarget();
		if(pExtraTarget==NULL)
		{
			AfxMessageBox(_T("Please select missing item"));
			//.
			return;
		}
	}


	pTool->execute(pTarget,pExtraTarget);
	pTool->render();

	curToolCommand = commandID;
}

CFeature* CUIControler::getFeatureByComboID( UINT comboID )
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(comboID));
	if (pCombo == NULL)
	{
		return NULL;
	}
	int iSel=pCombo->GetCurSel();
	if (iSel==-1)
	{
		return NULL;
	}
	DWORD_PTR dwData=pCombo->GetItemData(iSel);

	CFeature* pFeature=(CFeature*)dwData;
	return pFeature;
}



bool CUIControler::getCompareFeatureTargetInfo( UINT comboID,CString& featureName,CFeature::Type& featureType )
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(comboID));
	if (pCombo == NULL)
	{
		return false;
	}
	int iSel=pCombo->GetCurSel();
	if (iSel==-1)
	{
		return false;
	}
	DWORD_PTR dwData=pCombo->GetItemData(iSel);

	featureType=(CFeature::Type)dwData;
	featureName=pCombo->GetItem(iSel);
	return true;
}

CTest* CUIControler::getSelectedAnalysisComboTests()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pAnalyseTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_TEST_SELECT));
	if (pAnalyseTestsCombo == NULL)
	{
		return NULL;
	}
	int iSel=pAnalyseTestsCombo->GetCurSel();
	if (iSel==-1)
	{
		return NULL;
	}
	DWORD_PTR dwData=pAnalyseTestsCombo->GetItemData(iSel);

	CTest* pSession=(CTest*)dwData;
	return pSession;
}

void CUIControler::addFolderToHomeCombo( CString folderName )
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFilesFolder = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_FILEFOLDER));

	pFilesFolder->AddItem(folderName,0);
}

void CUIControler::addFileToHomeCombo( CString fileName )
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFilesFolder = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_FILEFOLDER));

	pFilesFolder->AddItem(fileName,1);
}

void CUIControler::updateTestHomeCombo()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFileFoldersCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_FILEFOLDER));
	CMFCRibbonComboBox* pTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_TEST));

	pTestsCombo->RemoveAllItems();

	if (pFileFoldersCombo->GetCurSel()==-1)
		return;

	if ( pFileFoldersCombo->GetItemData(pFileFoldersCombo->GetCurSel())==0 )
	{
		//It is a folder.
		return;
	}

	CString strFilePath=pFileFoldersCombo->GetItem(pFileFoldersCombo->GetCurSel());
	//
	std::string filePath=CCommonUtilities::toBasicString(strFilePath);

	testsFilesMapT::iterator testsIt=testsFilesMap.find(filePath);
	//
	if(testsIt==testsFilesMap.end())
		return;//Nothing found.

	CTestsFile* pCollection=testsIt->second;

	for (TestsVector::iterator myIt = pCollection->getTestsVector().begin(); myIt != pCollection->getTestsVector().end(); myIt++ ){
		//
		CTest* pSession=*myIt;

		//AfxMessageBox(CCommonUtilities::toMFCString(pSession->getName()));
		CString dispName=CCommonUtilities::toMFCString(pSession->getName())+_T("[")+\
			CCommonUtilities::toMFCString(pSession->getDescription())+_T("]");

		pTestsCombo->AddItem(CCommonUtilities::toMFCString(dispName),(DWORD_PTR)pSession);
	}
}



#include "SetDescriptionDlg.h"

void CUIControler::OnSetTestDescription()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_TEST));

	if (pTestsCombo->GetCurSel()==-1)
		return;

	CString strPath=pTestsCombo->GetItem(pTestsCombo->GetCurSel());
	CTest* pTest= (CTest*) pTestsCombo->GetItemData(pTestsCombo->GetCurSel());
	//
	//


	CSetDescriptionDlg m_dlg;
	if(m_dlg.DoModal()!=IDOK)
		return;

	
	std::string newDescription = CCommonUtilities::toBasicString(m_dlg.m_strDescription);

	CTestsFile* pTestsFile=pTest->GetTestsFile();
	pTestsFile->updateTestDescriptionInXML(pTest,newDescription);
	pHistoryTree->updateTestDisplayText(pTest);
	updateTestAtRibbonCombo(pTest);

	/*
	CString displayText;
		displayText.Format(_T("region name=%S\ndescription=%S"),pTest->getName().c_str(),pTest->getDescription().c_str());
		AfxMessageBox(displayText);
	
		displayText.Format(_T("parent test file is :%S"),pTest->GetTestsFile()->GetFilePath().c_str());
		AfxMessageBox(displayText);*/
	

}

void CUIControler::OnDeleteTest()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_TEST));

	if (pTestsCombo->GetCurSel()==-1)
		return;

	CString strPath=pTestsCombo->GetItem(pTestsCombo->GetCurSel());
	CTest* pTest= (CTest*) pTestsCombo->GetItemData(pTestsCombo->GetCurSel());
	//
	//

	CTestsFile* pFile=pTest->GetTestsFile();
	pHistoryTree->deleteTest(pTest);
	removeTestFromRibbonCombos(pTest);

	//Will also finally delete the mem reference.
	pFile->removeTestFromXML(pTest);
	/*
CString displayText;
	displayText.Format(_T("region name=%S\ndescription=%S"),pTest->getName().c_str(),pTest->getDescription().c_str());
	AfxMessageBox(displayText);
*/

}

void CUIControler::removeTestFromRibbonCombos( CTest* pTest )
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pAnalyseTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_TEST_SELECT));


	DWORD_PTR dwPtr=(DWORD_PTR)pTest;
	pAnalyseTestsCombo->DeleteItem(dwPtr);
}

void CUIControler::OnCloseFileFolder()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFileFoldersCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_FILEFOLDER));


	if (pFileFoldersCombo->GetCurSel()==-1)
		return;

	CString strPath=pFileFoldersCombo->GetItem(pFileFoldersCombo->GetCurSel());

	if ( pFileFoldersCombo->GetItemData(pFileFoldersCombo->GetCurSel())==1 )
	{
		std::string filePath=CCommonUtilities::toBasicString(strPath);
		CloseTestsFile(filePath);
	}
	else
	{
		std::string folderPath=CCommonUtilities::toBasicString(strPath);//Folder !
		//Loop on all files :

		std::vector<std::string> matchedFiles;
		for (testsFilesMapT::iterator myIt=testsFilesMap.begin();
			myIt!=testsFilesMap.end();
			myIt++)
		{
			CTestsFile* pFile=myIt->second;
			if(pFile->GetParentFolder()==folderPath)
				matchedFiles.push_back(pFile->GetFilePath());
		}

		for (std::vector<std::string>::iterator myIt=matchedFiles.begin();
			myIt!=matchedFiles.end();myIt++)
		{
			CloseTestsFile(*myIt);
		}
		pFileFoldersCombo->DeleteItem(pFileFoldersCombo->GetCurSel());
		
	}
}

void CUIControler::updateTestAtRibbonCombo( CTest* pTest )
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pAnalyseTestsCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_ANALYSIS_TEST_SELECT));


	DWORD_PTR dwPtr=(DWORD_PTR)pTest;
	pAnalyseTestsCombo->DeleteItem(dwPtr);


	CString dispName=CCommonUtilities::toMFCString(pTest->getName())+_T("[")+\
		CCommonUtilities::toMFCString(pTest->getDescription())+_T("]");

	pAnalyseTestsCombo->AddItem(CCommonUtilities::toMFCString(dispName),(DWORD_PTR)pTest);

}

void CUIControler::CloseTestsFile( std::string filePath )
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFileFoldersCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_FILEFOLDER));

	//Find the file in the vector :
	testsFilesMapT::iterator myIt=testsFilesMap.find(filePath);
	if (myIt!=testsFilesMap.end())
	{
		CTestsFile* pFile=myIt->second;
		//
		//Remove al tests from all references :
		for (TestsVector::iterator testsIt=pFile->getTestsVector().begin();
			testsIt!=pFile->getTestsVector().end();testsIt++)
		{
			CTest* pTest=*testsIt;
			//
			pHistoryTree->deleteTest(pTest);
			removeTestFromRibbonCombos(pTest);
		}
		//Now delete the file from the Combo :
		CString strDisplay;strDisplay.Format(_T("%S"),filePath.c_str());
		pFileFoldersCombo->DeleteItem( strDisplay );
		//
		testsFilesMap.erase(myIt);
		CTestsFile::releaseFile(pFile);
	}
}

void CUIControler::OnUpdateFileFolder()
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFileFoldersCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox,pMainFrame->GetRibbonBar()->FindByID(WM_SELECT_FILEFOLDER));


	if (pFileFoldersCombo->GetCurSel()==-1)
		return;

	CString strPath=pFileFoldersCombo->GetItem(pFileFoldersCombo->GetCurSel());

	if ( pFileFoldersCombo->GetItemData(pFileFoldersCombo->GetCurSel())==0 )
	{
		AfxMessageBox(_T("Updating Folder :\n")+strPath);
		//It is a folder.
		std::string folderPath=CCommonUtilities::toBasicString(strPath);

		HTREEITEM hSuiteItem=pHistoryTree->findSuiteTreeItem(folderPath);

		CFileFind finder;
		BOOL bWorking = finder.FindFile(strPath+_T("/*.xml"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			std::string filePath=CCommonUtilities::toBasicString(finder.GetFilePath());
			//
			testsFilesMapT::iterator myIt=testsFilesMap.find(filePath);
			if(myIt==testsFilesMap.end())
			{
				CTestsFile* pTests=openFile(filePath);
				if (pTests)
				{
					pTests->setParentFolder(folderPath);
					pHistoryTree->renderFile(pTests,hSuiteItem);
				}
			}
		} 
		return;
	}
	else
	{
		AfxMessageBox(_T("Updating File :\n")+strPath);
		std::string filePath=CCommonUtilities::toBasicString(strPath);
		//Close the file then reopen it :
		CloseTestsFile(filePath);
		
		//Reopen it :

		CTestsFile* pTests=openFile(filePath);
		if (pTests)
		{
			pHistoryTree->renderFile(pTests,pHistoryTree->hRoot);
			addFileToHomeCombo(strPath);
		}

	}
}
