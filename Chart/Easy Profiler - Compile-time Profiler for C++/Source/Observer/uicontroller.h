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
#pragma once
class CProfileTree;
class CTestSelectionTree;

class CAnalysisTool;
class CCompareTool;

/*
class CTestStorageBase{
public:
	CTestStorageBase(StorageType myType){
		this->myType=myType;
	};
	~CTestStorageBase(){};
	enum StorageType{
		SingleTest=1,
		FolderTests,
	}myType;
};
class CSingleTest : public CTestStorageBase{
public:
	CSingleTest(CString filePath):CTestStorageBase(SingleTest){
		this->filePath=filePath;
	};
private:
	CString filePath;
	CTestsFile* pFragmentedTests;
};*/

class CUIControler
{
public:
	enum TDisplay{
		NONE=0,
		ACTIVITY_POINTS_SPLINE,
		ACTIVITY_POINTS_COLUMN,
		TASK_RUNS_COLUMN,
	};
	CUIControler(void);
	~CUIControler(void);
public:
	void openHistoryFile();
	void OnOpenTestSuite();
private:

	typedef	std::map<std::string,CTestsFile*> testsFilesMapT;
	typedef	std::vector<std::string> foldersVectorT;

	testsFilesMapT testsFilesMap;
	foldersVectorT foldersVector;

public:
	CTest* getParentSession(CActivity* pMainBloc);
	CTest* getParentSession(CTask* pSubBloc);
public:
	CTestsFile* openFile(std::string fileName){
		CTestsFile* pCollection=CTestsFile::createFromXML(fileName);
		testsFilesMap[fileName]=pCollection;
		addTestsCollectionToRibbonCombos(pCollection);
		return pCollection;
	}

	void addTestsCollectionToRibbonCombos(CTestsFile* pCollection);
	void removeTestFromRibbonCombos(CTest* pTest);
	void updateTestAtRibbonCombo(CTest* pTest);
	void addFolderToHomeCombo(CString folderName);
	void addFileToHomeCombo(CString fileName);
	//
	void updateTestHomeCombo();
	//
	void OnUpdateFileFolder();
	void OnSetTestDescription();
	void OnCloseFileFolder();
	void OnDeleteTest();

	CProfileTree* pHistoryTree;
	CTestSelectionTree* pSelectionTestTree;

	void onDrawMainBlocSeries(CActivity* pSelectedBloc);
	void onDrawMainBlocDPs(CActivity* pSelectedBloc);
	void onDrawSubBlocsContributionToAMainBloc(CActivity* pSelectedBloc);
	void onDrawSubBlocContributionToAMainBloc(CActivity* pActivity,CTask* pTask);
	void onDrawTasksRunsAsColumn(CTask* pTask);

	//////////////////////////////////////////////////////////////////////////
	CFeature* getFeatureByComboID(UINT comboID);

	CFeature* getAnalysisTarget();
	CFeature* getAnalysisTaskForActivityTarget();
	CFeature* getAnalysisWorkerForActivityTarget();
	CFeature* getAnalysisTaskForWorkerTarget();
	void routeAnalysisCommand(int commandID);
	//

	/*
	CFeature::Type getCompareTarget();
		CFeature::Type getCompareTaskForActivityTarget();
		CFeature::Type getCompareWorkerForActivityTarget();
		CFeature::Type getCompareTaskForWorkerTarget();*/
	

	bool getCompareFeatureTargetInfo(UINT comboID,CString& featureName,CFeature::Type& featureType);
	void routeCompareCommand(int commandID);

	//////////////////////////////////////////////////////////////////////////
	void updateAnalysisFeatureTargetCombos();
		//Triggered by updateTestsCombo
		//or by a combo ui sel change event.;
	void updateCompareFeatureTargetCombos();
 

	//
	std::vector<CTest*> getMatchingTests(std::string regionName)
	{
		std::vector<CTest*> matchingTests;

		for (testsFilesMapT::iterator testsIt=testsFilesMap.begin();
			testsIt!=testsFilesMap.end();testsIt++)
		{
			CTestsFile* pTestsFile=testsIt->second;
			TestsVector testsVect=pTestsFile->getTestsVector();
			//
			TestsVector::iterator myIt;


			for (myIt = testsVect.begin(); myIt != testsVect.end(); myIt++ ){
				CTest* pSession=*myIt;
				//

				if(pSession->getName()==regionName)
					matchingTests.push_back(pSession);
			}
		}
		return matchingTests;
	}

	//
	UINT curToolCommand;
	int activeTool;
	CAnalysisTool* pCurAnalysisTool;
	CCompareTool* pCurCompareTool;

public:
	UINT getCurToolCommandID()
	{
		return curToolCommand;
	}

	CTest* getSelectedAnalysisComboTests();
	//
	void CloseTestsFile(std::string filePath);
};
extern CUIControler theMachine;