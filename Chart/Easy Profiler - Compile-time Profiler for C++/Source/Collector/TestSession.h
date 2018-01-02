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
#pragma once
#include "Task.h"
#include "Activity.h"
#include "Worker.h"

typedef PROFILER_API std::map<std::string,CTask*> taskMapT;
typedef PROFILER_API std::map<std::string,CActivity*> activityMapT;
typedef PROFILER_API std::map<std::string,CWorker*> workerMapT;

class CTestsFile;

class PROFILER_API CTest
{
public:
	CTest(std::string sessionName);
	CTest(std::string sessionName,std::string dateTime,std::string description);
	~CTest(void);
private:
	std::string sessionName;
	std::string dateTime;
	std::string description;
	bool bIsCompressionMode;
	CTestsFile* pTestsFile;
	//
	taskMapT tasksMap;
	activityMapT activitiesMap;
	workerMapT workersMap;
private://no serializable :
	LARGE_INTEGER	m_QPFrequency;		// ticks/sec resolution
	LARGE_INTEGER	m_StartCounter;		// start time
	double GetElapsedTime();
public:
	void initTest();
	
	void beginActivity(std::string blocName);
	void endActivity(std::string blocName);
	void insertCheckPoint(std::string blocName,std::string pointName);
	void beginTask(std::string subBlocName);
	void endTask(std::string subBlocName);
	void runWorker(char* workerName);
	void pauseWorker(char* workerName);

	void flush(char* regionName,char* outputDirectory,char outputType);
	static CTest* createFromXML(XMLNode& xSession);

	void setTestsFile(CTestsFile* pTestsFile);
	CTestsFile* GetTestsFile();
	bool containsActivity(CActivity* pSearchedMainBloc);
	bool containsTask(CTask* pSearchedSubBloc);
	int countTasks()
	{
		int count=0;
		taskMapT::const_iterator it=tasksMap.begin();
		for (; it != tasksMap.end(); ++it) {
			
			count++;
		}
		return count;
	}

	std::string getName();
	std::string getDateTime();
	std::string getDescription();
	activityMapT& getActivitiesMap();
	taskMapT& getTasksMap();
	workerMapT& getWorkersMap();
	CFeature* getFeatureByName(std::string featureName);
	void setDescription(std::string description);
	//
	bool getIsCompressionMode();
	void setCompressionMode();
	void NotifyEvent(TIMESTAMP timeNow)
	{
		for (taskMapT::iterator myIt=tasksMap.begin();
			myIt!=tasksMap.end();
			myIt++)
		{
			CTask* pTask=myIt->second;
			pTask->splitTempMapAndFlushCompressed(timeNow);
		}
		//
		for (workerMapT::iterator myIt=workersMap.begin();
			myIt!=workersMap.end();
			myIt++)
		{
			CWorker* pWorker=myIt->second;
			pWorker->SplitAndFlush(timeNow);
		}
	}

	//
};

/*
CRITICAL_SECTION c_s;
::InitializeCriticalSection(&c_s);
::LeaveCriticalSection(&c_s);
::DeleteCriticalSection(&c_s);
::EnterCriticalSection(&c_s);
*/