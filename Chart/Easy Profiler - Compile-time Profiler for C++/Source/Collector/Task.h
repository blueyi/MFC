/********************************************************************
    File:	        Task	
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
#include "Feature.h"

class CTest;
class PROFILER_API CTask : public CFeature
{
public:
	class CRun{
	public:
		CRun(TIMESTAMP start,DWORD dwThreadID)
		{
			this->start=start;
			this->dwThreadID=dwThreadID;
		}
		CRun(TIMESTAMP start,TIMESTAMP stop,DWORD dwThreadID)
			//Called by XML reader.;
		{
			this->start=start;
			this->stop=stop;
			this->dwThreadID=dwThreadID;
		}
			
	private:
		TIMESTAMP start;
		TIMESTAMP stop;
		DWORD dwThreadID;
	public:
		void setStart(TIMESTAMP start)
		{
			this->start=start;
		}
		void setStop(TIMESTAMP stop)
		{
			this->stop=stop;
		}
		TIMESTAMP getStart()
		{
			return start;
		}
		TIMESTAMP getStop()
		{
			return stop;
		}
		DWORD getThreadID()
		{
			return dwThreadID;
		}
	};
	typedef std::vector<CRun*> runsVectorT;
	CTask(std::string subBlocName);
	CTask(std::string subBlocName,TIMESTAMP start);
	~CTask(void);
private:
	std::string subBlocName;
	runsVectorT runVector;//The final collected vector of runs.
	//temporary map :
	typedef std::map<DWORD,CRun*> tempRunsMapT;
	tempRunsMapT tempRunsMap;

	//
public:
	runsVectorT& getRuns();
	std::string getName();
	void Start(TIMESTAMP start);
	void Stop(TIMESTAMP stop);
	void addRun(std::string start,std::string stop,std::string threadID);
	void flush(XMLNode& xSubBlocNode);

	static CTask* createFromXMLNode(XMLNode& xSubNode,CTest* pParentTest);

	double measureTimeContribution(double _start,double _stop);;
	double measureTimeContribution(double _start,double _stop,DWORD threadID);
	double getTimeTotal();
	int getRunsCount();
	//
	typedef std::map<DWORD,runsVectorT*> intermediateMapT;
	intermediateMapT intermediateMap;
	void splitTempMapAndFlushCompressed(TIMESTAMP timeNow);
	void AddToIntermediate(CRun* pRun);
};
