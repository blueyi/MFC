/********************************************************************
    File:	        CompareWorkerContributionToActivityTotalTime	
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
#include "CompareWorkerContributionToActivityTotalTime.h"
REGISTER_CLASS(factory2, CCompareWorkerContributionToActivityTotalTime, WM_COMPARE_SINGLEACTIVITY_WITHWORKER_TOTAL)

CCompareWorkerContributionToActivityTotalTime::CCompareWorkerContributionToActivityTotalTime(void)
{
	setParams(CFeature::Activity,CFeature::Worker);
}

CCompareWorkerContributionToActivityTotalTime::~CCompareWorkerContributionToActivityTotalTime(void)
{
}

void CCompareWorkerContributionToActivityTotalTime::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	chartControl.resetSeries();

	int i=0;
	for (std::vector<CTest*>::iterator myIt=tests.begin();myIt!=tests.end();myIt++)
	{
		i++;
		CTest* pTest=*myIt;
		//
		CActivity* pActivity=(CActivity*) pTest->getFeatureByName(targetName);
		CWorker* pWorker=(CWorker*) pTest->getFeatureByName(extraTargetName);
		//

		std::string activitySeries=pTest->getDescription()+std::string(" ")+pActivity->getName();
		std::string workerSeries=pTest->getDescription()+std::string(" ")+pWorker->getName();

		chartControl.addSeries(activitySeries, CChartControl::Column);
		chartControl.addSeries(workerSeries, CChartControl::Column);

		for (std::vector<CTest*>::iterator myIt2=tests.begin();myIt2!=tests.end();myIt2++)
		{
			CTest* pTest2=*myIt2;
			if (pTest2!=pTest)
			{
				chartControl.addPoint(activitySeries,pTest2->getDescription(),0);
				chartControl.addPoint(workerSeries,pTest2->getDescription(),0);
			}
			else{
				double workerContribution=pWorker->measureTimeContribution(pActivity->getStart(),pActivity->getStop());

				chartControl.addPoint(activitySeries,pTest->getDescription(),
					pActivity->getTimeElapse());

				chartControl.addPoint(workerSeries,pTest->getDescription(),
					workerContribution);
			}

		}
	}
}