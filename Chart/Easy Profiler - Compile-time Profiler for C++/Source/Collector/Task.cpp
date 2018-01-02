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
#include "StdAfx.h"
#include "Task.h"

#include <algorithm>
#include "TestSession.h"

bool UDgreater ( CTask::CRun* elem1, CTask::CRun* elem2 )
{
	return elem1->getStart() > elem2->getStart();
}
double CTask::measureTimeContribution( double _start,double _stop )
{
	//
	runsVectorT sortVector=runVector;
	sort( sortVector.begin( ), sortVector.end( ), UDgreater );

	double total=0;
	
	double last=0;
	for (runsVectorT::iterator myIt=sortVector.begin();
		myIt!=sortVector.end();
		myIt++)
	{
		CRun* pRun=*myIt;
		//
		double _start=max(last,pRun->getStart());
		if (pRun->getStop() > last)
		{
			total+=(pRun->getStop()-_start);
			last=pRun->getStop();
		}
	}
	return total;
}

double CTask::measureTimeContribution( double _start,double _stop,DWORD threadID )
{
	double total=0;
	for (runsVectorT::iterator myIt=runVector.begin();
		myIt!=runVector.end();
		myIt++)
	{

		CRun* pCurRun=*myIt;

		if (pCurRun->getThreadID()==threadID)
		{
			double start,stop;

			start= max(pCurRun->getStart(),_start);
			stop=min(pCurRun->getStop(),_stop);
			if(start < _stop
				&&
				stop > _start)
			{
				total+=(stop-start);
			}
		}
	}
	return total;
}
CTask::CTask( std::string subBlocName )
:CFeature(Task)
{
	this->subBlocName=subBlocName;
}

CTask::CTask( std::string subBlocName,TIMESTAMP start )
:CFeature(Task)
{
	this->subBlocName=subBlocName;
	this->Start(start);
}

CTask::~CTask( void )
{

}

CTask::runsVectorT& CTask::getRuns()
{
	return runVector;
}

double CTask::getTimeTotal()
{
	CTask::runsVectorT::iterator myIt;

	double total=0;


	for (myIt = runVector.begin(); myIt != runVector.end(); myIt++ ){
		CRun* pCurRun=*myIt;

		total+=pCurRun->getStop()-pCurRun->getStart();
	}

	return total;

}

int CTask::getRunsCount()
{
	int count=0;
	for (runsVectorT::iterator myIt = runVector.begin(); myIt != runVector.end(); myIt++ )
		count++;
	return count;
}

CTask* CTask::createFromXMLNode( XMLNode& xSubNode,CTest* pParentTest )
{
	//
	std::string subBlocName=xSubNode.getAttribute("name");
	CTask* pSubBloc=new CTask(subBlocName);
	pSubBloc->setParentTest(pParentTest);

	int nRuns=xSubNode.nChildNode("run");
	int it=0;

	for (int i=0;i<nRuns;i++)
	{
		XMLNode xRun=xSubNode.getChildNode("run",&it);

		std::string start=xRun.getAttribute("start");
		std::string stop=xRun.getAttribute("stop");
		std::string threadID=xRun.getAttribute("threadID");

		pSubBloc->addRun(start,stop,threadID);
	}

	return pSubBloc;
}

void CTask::flush( XMLNode& xSubBlocNode )
{
	std::vector<CRun*>::iterator myIt;
	for (myIt = runVector.begin(); myIt != runVector.end(); myIt++ ){
		CRun* pRun=*myIt;

		XMLNode runNode=xSubBlocNode.addChild("run");
		//adding attributes.
		runNode.addAttribute("start",CUtilities::GetFormattedTime(pRun->getStart()).c_str());
		runNode.addAttribute("stop",CUtilities::GetFormattedTime(pRun->getStop()).c_str());
		runNode.addAttribute("threadID",CUtilities::GetFormattedDWORD(pRun->getThreadID()).c_str());
	}
}

void CTask::addRun( std::string start,std::string stop,std::string threadID )
{
	runVector.push_back(new CRun(atof(start.c_str()),atof(stop.c_str()),CUtilities::GetDWORDByString(threadID)));
}
void CTask::Stop( TIMESTAMP stop )
{
	//Get the current threadID in order to locate the start value
	DWORD dwThreadID=GetCurrentThreadId();
	//
	tempRunsMapT::iterator myIt=tempRunsMap.find(dwThreadID);
	if(myIt==tempRunsMap.end())
		return;//Nothing to do.
	CRun* pRun=myIt->second;
	//update it
	pRun->setStop(stop);
	//remove from temp map.
	tempRunsMap.erase(myIt);

	if (getParentTest()->getIsCompressionMode())
	{
		//add it to intermediate map
		AddToIntermediate(pRun);
	}
	else
	{
		//pump it directly to final storage :
		runVector.push_back(pRun);
	}
	
}
void CTask::Start( TIMESTAMP start )
{
	//Get the current thread ID.
	DWORD dwThreadID=GetCurrentThreadId();
	//Find and correct the corresponding run in the temp map or
	//just create a new one and add it to the temp map.
	tempRunsMapT::iterator myIt=tempRunsMap.find(dwThreadID);
	if(myIt!=tempRunsMap.end())
	{
		CRun* pRun=myIt->second;
		pRun->setStart(start);
		return;
	}
	//
	CRun* pNewRun=new CRun(start,dwThreadID);
	tempRunsMap[dwThreadID]=pNewRun;
}


std::string CTask::getName()
{
	return subBlocName;
}



void CTask::splitTempMapAndFlushCompressed( TIMESTAMP timeNow )
{
	for (tempRunsMapT::iterator myIt=tempRunsMap.begin();
		myIt!=tempRunsMap.end();
		myIt++)
	{
		CRun* pRun=myIt->second;
		//
		CRun* pSplit=new CRun(pRun->getStart(),timeNow,pRun->getThreadID());
		AddToIntermediate(pSplit);
		pRun->setStart(timeNow);
	}
	//
	for (intermediateMapT::iterator myIt=intermediateMap.begin();
		myIt!=intermediateMap.end();myIt++)
	{
		runsVectorT* pVector=myIt->second;
		for (runsVectorT::iterator it=pVector->begin();
			it!=pVector->end();
			it++)
		{
			CRun* pRun=*it;
			runVector.push_back(pRun);
		}
		pVector->clear();
		//delete pVector;  System craches here.
	}
}

void CTask::AddToIntermediate( CRun* pRun )
{
	//localize the last run, and if it has not expired
	//then append the new run to it.
	//otherwise just create a new one.
	intermediateMapT::iterator myIt=intermediateMap.find(pRun->getThreadID());
	if (myIt==intermediateMap.end())
	{
		runsVectorT* pVect=new runsVectorT;
		pVect->push_back(pRun);
		intermediateMap[pRun->getThreadID()]=pVect;
		return;
	}
	runsVectorT* pVector=myIt->second;
	if(pVector->empty())
	{
		pVector->push_back(pRun);
		return;
	}
	CRun* pLastRun=pVector->back();
	//Join :
	pLastRun->setStop(pLastRun->getStop()+pRun->getStop()-pRun->getStart());
}
