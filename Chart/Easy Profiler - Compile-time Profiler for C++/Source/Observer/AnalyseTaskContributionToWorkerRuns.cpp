/********************************************************************
    File:	        AnalyseTaskContributionToWorkerRuns	
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
#include "AnalyseTaskContributionToWorkerRuns.h"
REGISTER_CLASS(factory, CAnalyseTaskContributionToWorkerRuns, WM_ANALYSIS_SINGLEWORKER_WITHTASK_MULTIPLESTACKED)

CAnalyseTaskContributionToWorkerRuns::CAnalyseTaskContributionToWorkerRuns(void)
{
	setParams(CFeature::Worker,CFeature::Task);
}

CAnalyseTaskContributionToWorkerRuns::~CAnalyseTaskContributionToWorkerRuns(void)
{
}

void CAnalyseTaskContributionToWorkerRuns::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CWorker* pWorker=(CWorker*)pTarget;
	CTask* pTask=(CTask*)pExtraTarget;


	chartControl.resetSeries();

	chartControl.addSeries(pWorker->getName(), CChartControl::StackedColumn);
	chartControl.addSeries(pTask->getName(), CChartControl::StackedColumn);


	CWorker::runsVectorT::iterator myIt=pWorker->getRuns().begin();

	int i=0;
	while (myIt != pWorker->getRuns().end())
	{
		i++;
		CWorker::CRun* pRun=*myIt;

		double taskContribution=pTask->measureTimeContribution(pRun->getStart(),pRun->getPause(),pWorker->getThreadID());
			
		CString strPointName;
		strPointName.Format(_T("%d"),i);
		//
		chartControl.addPoint(pWorker->getName(),strPointName,
			pRun->getPause()-pRun->getStart()-taskContribution);

		chartControl.addPoint(pTask->getName(),strPointName,
			taskContribution);

		myIt++;
	}
}