/********************************************************************
    File:	        CompareTaskContributionToWorkerTotalTime	
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
#include "CompareTaskContributionToWorkerTotalTime.h"
REGISTER_CLASS(factory2, CCompareTaskContributionToWorkerTotalTime, WM_COMPARE_SINGLEWORKER_WITHTASK_TOTAL)

CCompareTaskContributionToWorkerTotalTime::CCompareTaskContributionToWorkerTotalTime(void)
{
	setParams(CFeature::Worker,CFeature::Task);
}

CCompareTaskContributionToWorkerTotalTime::~CCompareTaskContributionToWorkerTotalTime(void)
{
}

void CCompareTaskContributionToWorkerTotalTime::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	chartControl.resetSeries();

	int i=0;
	for (std::vector<CTest*>::iterator myIt=tests.begin();myIt!=tests.end();myIt++)
	{
		i++;
		CTest* pTest=*myIt;
		//
		CWorker* pWorker=(CWorker*) pTest->getFeatureByName(targetName);
		CTask* pTask=(CTask*) pTest->getFeatureByName(extraTargetName);
		//

		std::string workerSeries=pTest->getDescription()+std::string(" ")+pWorker->getName();
		std::string taskSeries=pTest->getDescription()+std::string(" ")+pTask->getName();

		chartControl.addSeries(workerSeries, CChartControl::Column);
		chartControl.addSeries(taskSeries, CChartControl::Column);

		for (std::vector<CTest*>::iterator myIt2=tests.begin();myIt2!=tests.end();myIt2++)
		{
			CTest* pTest2=*myIt2;
			if (pTest2!=pTest)
			{
				chartControl.addPoint(workerSeries,pTest2->getDescription(),0);
				chartControl.addPoint(taskSeries,pTest2->getDescription(),0);
			}
			else{
				TIMESTAMP firstStart=0,lastPause=0;
				if (!pWorker->getRuns().empty())
				{
					firstStart=pWorker->getRuns().front()->getStart();
					lastPause=pWorker->getRuns().back()->getPause();
				}
				
				double taskContribution=pTask->measureTimeContribution(firstStart,lastPause);

				chartControl.addPoint(workerSeries,pTest->getDescription(),
					pWorker->getTimeTotal());

				chartControl.addPoint(taskSeries,pTest->getDescription(),
					taskContribution);
			}

		}
	}
}