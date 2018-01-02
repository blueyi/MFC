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
#include "StdAfx.h"
#include "Worker.h"
#include "TestSession.h"

CWorker::CWorker(std::string workerName,DWORD dwThreadID)
:CFeature(Worker)
{
	this->workerName=workerName;
	this->dwThreadID=dwThreadID;
	pCurrentRun=NULL;
	pIntermediateRun=NULL;
}

CWorker::~CWorker(void)
{
}

std::string CWorker::getName()
{
	return workerName;
}

CWorker::runsVectorT& CWorker::getRuns()
{
	return runVector;
}

void CWorker::Start( TIMESTAMP start )
{
	if (pCurrentRun!=NULL)
		delete pCurrentRun;//Corrupted instrumentation.
	pCurrentRun=new CRun(start);
	//
}
void CWorker::SplitAndFlush( TIMESTAMP timeNow )
{
	if (pCurrentRun)
	{
		//Add it to intermediate vector.
		//
		pCurrentRun->setPause(timeNow);
		addToIntermediateRun(pCurrentRun);
		pCurrentRun->setStart(timeNow);
	}
	if (pIntermediateRun)
	{
		runVector.push_back(pIntermediateRun);
		pIntermediateRun=NULL;
	}
}
void CWorker::addToIntermediateRun( CRun* pRun )
{
	//merge or create a new intermediate :
	if (pIntermediateRun==NULL)
	{
		pIntermediateRun=new CRun(pRun->getStart(),pRun->getPause());
	}
	else
	{
		pIntermediateRun->setPause(pIntermediateRun->getPause()+pRun->getPause()-pRun->getStart());
	}
}
void CWorker::Stop( TIMESTAMP stop )
{
	if(pCurrentRun==NULL)
		return;//bad instrumentation.
	pCurrentRun->setPause(stop);
	//
	if (!pParentTest->getIsCompressionMode())
	{
		//Just push it directly to vector :
		runVector.push_back(pCurrentRun);
		pCurrentRun=NULL;
	}
	else
	{
		addToIntermediateRun(pCurrentRun);
		delete pCurrentRun;
		pCurrentRun=NULL;
	}
}

DWORD CWorker::getThreadID()
{
	return dwThreadID;
}

void CWorker::flushToXML( XMLNode& xWorkerNode )
{
	std::vector<CRun*>::iterator myIt;
	for (myIt = runVector.begin(); myIt != runVector.end(); myIt++ ){
		CRun* pRun=*myIt;

		XMLNode runNode=xWorkerNode.addChild("run");
		//adding attributes.
		runNode.addAttribute("start",CUtilities::GetFormattedTime(pRun->getStart()).c_str());
		runNode.addAttribute("stop",CUtilities::GetFormattedTime(pRun->getPause()).c_str());
	}
}

CWorker* CWorker::createFromXMLNode( XMLNode& xWorkerNode,CTest* pParentTest )
{
	std::string name=xWorkerNode.getAttribute("name");
	std::string strThreadID=xWorkerNode.getAttribute("threadID");

	CWorker* pWorker=new CWorker(name,CUtilities::GetDWORDByString(strThreadID));
	pWorker->setParentTest(pParentTest);
	

	int nRuns=xWorkerNode.nChildNode("run");
	int it=0;

	for (int i=0;i<nRuns;i++)
	{
		XMLNode xRun=xWorkerNode.getChildNode("run",&it);

		std::string start=xRun.getAttribute("start");
		std::string stop=xRun.getAttribute("stop");

		pWorker->addRun(start,stop);
	}

	return pWorker;
}

double CWorker::getTimeTotal()
{
	runsVectorT::iterator myIt;
	double total=0;
	for (myIt = runVector.begin(); myIt != runVector.end(); myIt++ ){
		CRun* pCurRun=*myIt;

		total+=pCurRun->getPause()-pCurRun->getStart();
	}
	return total;
}

int CWorker::getRunsCount()
{
	int count=0;
	for (runsVectorT::iterator myIt = runVector.begin(); myIt != runVector.end(); myIt++ )
		count++;
	return count;
}

double CWorker::measureTimeContribution( double _start,double _stop )
{
	//
	double total=0;
	for (runsVectorT::iterator myIt=runVector.begin();
		myIt!=runVector.end();
		myIt++)
	{
		CRun* pRun=*myIt;
		//

		double __start=max(_start,pRun->getStart());
		double __stop=min(_stop,pRun->getPause());

		if (__start < __stop)
		{
			total+=(__stop-__start);
		}
	}
	return total;
}


