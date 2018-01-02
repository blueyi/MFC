/********************************************************************
    File:	        TestSession	
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
#include "TestSession.h"


CTest::CTest( std::string sessionName )
{
	//
	SYSTEMTIME st;
	GetSystemTime(&st);

	char* pTimeBuffer=new char[255];
	sprintf_s(pTimeBuffer,255,"%.2d%.2d%.2d%.2d%.2d%.2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	std::string timeDate(pTimeBuffer);
	delete pTimeBuffer;

	char* pDescBuffer=new char[255];
	sprintf_s(pDescBuffer,255,"testDate :%.2d/%.2d/%.2d %.2d:%.2d:%.2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	std::string description(pDescBuffer);
	delete pDescBuffer;

	//CTest(sessionName,timeDate);

	this->sessionName=sessionName;
	this->dateTime=timeDate;
	this->description=description;
	this->bIsCompressionMode=false;	
}


CTest::CTest(std::string sessionName,std::string dateTime,std::string description)
{
	this->sessionName=sessionName;
	this->dateTime=dateTime;
	this->description=description;
	this->bIsCompressionMode=false;
}
double CTest::GetElapsedTime()
{
	LARGE_INTEGER	curCounter;
	ZeroMemory(&curCounter, sizeof(curCounter));
	QueryPerformanceCounter (&curCounter);
	//
	__int64			m_ElapsedTime=(curCounter.QuadPart  - m_StartCounter.QuadPart );

	return (static_cast<double>(m_ElapsedTime) / static_cast<double>(m_QPFrequency.QuadPart));
}

void CTest::initTest()
{
	ZeroMemory(&m_QPFrequency, sizeof(m_QPFrequency));
	ZeroMemory(&m_StartCounter,sizeof(m_StartCounter));
	QueryPerformanceFrequency(&m_QPFrequency);
	QueryPerformanceCounter (&m_StartCounter);
}

void CTest::flush( char* regionName,char* outputDirectory,char outputType )
{
	if (bIsCompressionMode)
	{
		NotifyEvent(GetElapsedTime());
	}
	std::string xmlFilePath;

	if(outputType=='s')
		xmlFilePath=std::string(outputDirectory)+"/"+std::string(regionName)+" "+dateTime+".xml";
	else
		xmlFilePath=std::string(outputDirectory)+"/"+std::string(regionName)+".xml";

	XMLNode xMainNode;

	if(outputType=='s'){
		//
		XMLNode global=XMLNode::createXMLTopNode("xml",TRUE);
		global.addAttribute("version","1.0");
		xMainNode=global.addChild("profilingData");
	}
	else
		xMainNode=XMLNode::openFileHelper(xmlFilePath.c_str(),"profilingData");
		

	XMLNode xSessionNode=xMainNode.addChild("test");
	xSessionNode.addAttribute("regionName",sessionName.c_str());
	xSessionNode.addAttribute("dateTime",dateTime.c_str());
	xSessionNode.addAttribute("description",description.c_str());
	xSessionNode.addAttribute("highPerformance",bIsCompressionMode ? "true" : "false");

	//Flush sub-blocs :
	std::map<std::string,CTask*>::const_iterator _it=tasksMap.begin();
	for (; _it != tasksMap.end(); ++_it) {
		CTask* pSubBloc=_it->second;
		std::string subBlocName=_it->first;
		//
		XMLNode xSubBloc=xSessionNode.addChild("task");

		xSubBloc.addAttribute("name",subBlocName.c_str());
		pSubBloc->flush(xSubBloc);
	}

	//Flushing main-blocs :
	std::map<std::string,CActivity*>::const_iterator it=activitiesMap.begin();
	for (; it != activitiesMap.end(); ++it) {
		CActivity* pBloc=it->second;
		std::string blocName=it->first;
		//
		XMLNode xMainBloc=xSessionNode.addChild("activity");

		xMainBloc.addAttribute("name",blocName.c_str());
		pBloc->flush(xMainBloc);
	}

	//Flush workers :
	for (workerMapT::iterator workersIt=workersMap.begin();workersIt!=workersMap.end();workersIt++)
	{
		CWorker* pWorker=workersIt->second;
		XMLNode xWorkerNode=xSessionNode.addChild("worker");

		xWorkerNode.addAttribute("name",pWorker->getName().c_str());
		xWorkerNode.addAttribute("threadID",CUtilities::GetFormattedDWORD(pWorker->getThreadID()).c_str());

		pWorker->flushToXML(xWorkerNode);
	}

	xMainNode.writeToFile(xmlFilePath.c_str());
}

void CTest::beginActivity( std::string blocName )
{
	CActivity* pNewBloc=new CActivity(blocName,GetElapsedTime());
	pNewBloc->setParentTest(this);
	activitiesMap[blocName]=pNewBloc;
	//
	if (bIsCompressionMode)
	{
		NotifyEvent(GetElapsedTime());
	}
}

void CTest::endActivity( std::string blocName )
{
	activitiesMap[blocName]->endMainBloc(GetElapsedTime());
	if (bIsCompressionMode)
	{
		NotifyEvent(GetElapsedTime());
	}
}

void CTest::insertCheckPoint( std::string blocName,std::string pointName )
{
	activitiesMap[blocName]->insertPoint(pointName,GetElapsedTime());
	if (bIsCompressionMode)
	{
		NotifyEvent(GetElapsedTime());
	}
}

void CTest::beginTask( std::string subBlocName )
{
	if (tasksMap.find(subBlocName)==tasksMap.end())
	{
		CTask* pSubBloc=new CTask(subBlocName,GetElapsedTime());
		pSubBloc->setParentTest(this);
		tasksMap[subBlocName]=pSubBloc;
	}
	else
		tasksMap[subBlocName]->Start(GetElapsedTime());
}

void CTest::endTask( std::string subBlocName )
{
	/*
	double d=GetElapsedTime();
	::MessageBoxA(NULL,CUtilities::GetFormattedTime(d).c_str(),NULL,MB_OK);*/

	tasksMap[subBlocName]->Stop(GetElapsedTime());
}

CTest* CTest::createFromXML( XMLNode& xSession )
{
	std::string sessionName=xSession.getAttribute("regionName");
	std::string dateTime=xSession.getAttribute("dateTime");
	std::string description=xSession.getAttribute("description");
	CTest* pSession=new CTest(sessionName,dateTime,description);

	//
	int nSubBlocs=xSession.nChildNode("task");
	int it=0;

	for (int i=0;i<nSubBlocs;i++)
	{
		XMLNode xSubBloc=xSession.getChildNode("task",&it);

		CTask* pSubBloc=CTask::createFromXMLNode(xSubBloc,pSession);
		pSubBloc->setParentTest(pSession);
		pSession->tasksMap[pSubBloc->getName()]=pSubBloc;
		//
	}


	int nMainBlocs=xSession.nChildNode("activity");
	int _it=0;

	for (int i=0;i<nMainBlocs;i++)
	{
		XMLNode xMainBloc=xSession.getChildNode("activity",&_it);

		CActivity* pMainBloc=CActivity::createFromXML(xMainBloc,pSession);
		pMainBloc->setParentTest(pSession);
		pSession->activitiesMap[pMainBloc->getName()]=pMainBloc;
		//
	}

	int nWorkers=xSession.nChildNode("worker");
	int __it=0;

	for (int i=0;i<nWorkers;i++)
	{
		XMLNode xWorkerNode=xSession.getChildNode("worker",&__it);

		CWorker* pWorker=CWorker::createFromXMLNode(xWorkerNode,pSession);
		pWorker->setParentTest(pSession);
		pSession->workersMap[pWorker->getName()]=pWorker;
		//
	}

	return pSession;
}

std::string CTest::getName()
{
	return sessionName;
}

activityMapT& CTest::getActivitiesMap()
{
	return activitiesMap;
}

taskMapT& CTest::getTasksMap()
{
	return tasksMap;
}

bool CTest::containsActivity( CActivity* pSearchedMainBloc )
{
	activityMapT::const_iterator it=activitiesMap.begin();
	for (; it != activitiesMap.end(); ++it) {
		if(pSearchedMainBloc==it->second)
			return true;
	}
	return false;
}

bool CTest::containsTask( CTask* pSearchedSubBloc )
{
	taskMapT::const_iterator it=tasksMap.begin();
	for (; it != tasksMap.end(); ++it) {
		if(pSearchedSubBloc==it->second)
			return true;
	}
	return false;
}

CFeature* CTest::getFeatureByName( std::string featureName )
{
	activityMapT::const_iterator it=activitiesMap.find(featureName);
	if (it!=activitiesMap.end())
	{
		CActivity* pActivity=it->second;
		return pActivity;
	}

	taskMapT::const_iterator it2=tasksMap.find(featureName);
	if (it2!=tasksMap.end())
	{
		CTask* pTask=it2->second;
		return pTask;
	}

	workerMapT::const_iterator it3=workersMap.find(featureName);
	if (it3!=workersMap.end())
	{
		CWorker* pWorker=it3->second;
		return pWorker;
	}

	return NULL;
}

std::string CTest::getDateTime()
{
	return dateTime;
}

std::string CTest::getDescription()
{
	return description;
}

CTest::~CTest( void )
{
	//
}

void CTest::runWorker( char* workerName )
{
	if (workersMap.find(workerName)==workersMap.end())
	{
		DWORD dwThreadID=GetCurrentThreadId();
		//Create a new worker reference.
		CWorker* pWorker=new CWorker(workerName,dwThreadID);
		pWorker->setParentTest(this);
		//add first run :
		pWorker->Start(GetElapsedTime());
		//add it to map :
		workersMap[workerName]=pWorker;
	}
	else
		workersMap[workerName]->Start(GetElapsedTime());//creating a new run
}

void CTest::pauseWorker( char* workerName )
{
	if (workersMap.find(workerName)==workersMap.end())
	{
		DWORD dwThreadID=GetCurrentThreadId();
		//Create a new worker reference.
		CWorker* pWorker=new CWorker(workerName,dwThreadID);
		pWorker->setParentTest(this);
		//add it to map :
		workersMap[workerName]=pWorker;
	}
	else
		workersMap[workerName]->Stop(GetElapsedTime());//creating a new run
}

workerMapT& CTest::getWorkersMap()
{
	return workersMap;
}

bool CTest::getIsCompressionMode()
{
	return bIsCompressionMode;
}

void CTest::setCompressionMode()
{
	bIsCompressionMode=true;
}

void CTest::setTestsFile( CTestsFile* pTestsFile )
{
	this->pTestsFile=pTestsFile;
}

CTestsFile* CTest::GetTestsFile()
{
	return pTestsFile;
}

void CTest::setDescription( std::string description )
{
	this->description=description;
}