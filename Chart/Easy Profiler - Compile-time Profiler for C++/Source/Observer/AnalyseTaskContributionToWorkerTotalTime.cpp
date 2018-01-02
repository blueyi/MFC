/********************************************************************
    File:	        AnalyseTaskContributionToWorkerTotalTime	
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
#include "AnalyseTaskContributionToWorkerTotalTime.h"
REGISTER_CLASS(factory, CAnalyseTaskContributionToWorkerTotalTime, WM_ANALYSIS_SINGLEWORKER_WITHTASK_TIMETOTAL)


CAnalyseTaskContributionToWorkerTotalTime::CAnalyseTaskContributionToWorkerTotalTime(void)
{
	setParams(CFeature::Worker,CFeature::Task);
}

CAnalyseTaskContributionToWorkerTotalTime::~CAnalyseTaskContributionToWorkerTotalTime(void)
{
}

void CAnalyseTaskContributionToWorkerTotalTime::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CWorker* pWorker=(CWorker*)pTarget;
	CTask* pTask=(CTask*)pExtraTarget;


	chartControl.resetSeries();

	chartControl.addSeries(pWorker->getName(), CChartControl::Column);
	chartControl.addSeries(pTask->getName(), CChartControl::Column);

	//
	double contributionTotal=0;
	for (CWorker::runsVectorT::iterator myIt=pWorker->getRuns().begin();
		myIt!=pWorker->getRuns().end();myIt++)
	{
		CWorker::CRun* pRun=*myIt;
		//
		contributionTotal+=pTask->measureTimeContribution(pRun->getStart(),pRun->getPause(),pWorker->getThreadID());
	}
	
	chartControl.addPoint(pWorker->getName(),_T("Total"),pWorker->getTimeTotal());

	chartControl.addPoint(pTask->getName(),_T("Total"),contributionTotal);

}