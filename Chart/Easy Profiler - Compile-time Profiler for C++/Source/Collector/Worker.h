/********************************************************************
    File:	        Worker	
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
#include "feature.h"

class CTest;
class PROFILER_API CWorker : public CFeature
{
public:
	CWorker(std::string workerName,DWORD dwThreadID);
	~CWorker(void);
	class CRun
	{
	public:
		CRun(TIMESTAMP runTime)
		{
			this->runTime=runTime;
		}
		CRun(TIMESTAMP runTime,TIMESTAMP stopTime)
		{
			this->runTime=runTime;
			this->stopTime=stopTime;
		}
		~CRun(){};
		void setStart(TIMESTAMP start)
		{
			this->runTime=start;
		}
		void setPause(TIMESTAMP stopTime)
		{
			this->stopTime=stopTime;
		}
		TIMESTAMP getStart()
		{
			return runTime;
		}
		TIMESTAMP getPause()
		{
			return stopTime;
		}
	private:
		TIMESTAMP runTime;
		TIMESTAMP stopTime;
	};
	typedef std::vector<CRun*> runsVectorT;
private:
	std::string workerName;
	runsVectorT runVector;
	DWORD dwThreadID;
	//
	CRun* pCurrentRun;
	CRun* pIntermediateRun;
public:
	std::string getName();
	runsVectorT& getRuns();
	DWORD getThreadID();
	void Start(TIMESTAMP start);
	void Stop(TIMESTAMP stop);
	void SplitAndFlush(TIMESTAMP timeNow);
	void addToIntermediateRun(CRun* pRun);
	//
	void flushToXML(XMLNode& xWorkerNode);
	static CWorker* createFromXMLNode(XMLNode& xWorkerNode,CTest* pParentTest);
	void addRun(std::string start,std::string stop){
		runVector.push_back(new CRun(atof(start.c_str()),atof(stop.c_str())));
	}
	//
	double getTimeTotal();
	int getRunsCount();
	double measureTimeContribution( double _start,double _stop );
	//
	//
	CTest* pParentTest;//
	CTest* getParentTest()
	{
		return pParentTest;
	}
	void setParentTest(CTest* pParentTest)
	{
		this->pParentTest=pParentTest;
	}
	//Tasks contribution.
	typedef std::map<std::string,TIMESTAMP> tasksTimesMapT;
	tasksTimesMapT tasksTimesMap;
	//
	void addTaskRun(std::string taskName,TIMESTAMP duration)
	{
		tasksTimesMapT::iterator myIt=tasksTimesMap.find(taskName);
		if (myIt!=tasksTimesMap.end())
		{
			myIt->second+=duration;
		}
		else
		{
			tasksTimesMap[taskName]=duration;
		}
	}
};
