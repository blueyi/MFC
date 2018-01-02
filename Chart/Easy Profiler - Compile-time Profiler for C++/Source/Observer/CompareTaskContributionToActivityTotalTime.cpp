/********************************************************************
    File:	        CompareTaskContributionToActivityTotalTime	
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
#include "CompareTaskContributionToActivityTotalTime.h"
REGISTER_CLASS(factory2, CCompareTaskContributionToActivityTotalTime, WM_COMPARE_SINGLEACTIVITY_WITHTASK_TOTAL)

CCompareTaskContributionToActivityTotalTime::CCompareTaskContributionToActivityTotalTime(void)
{
	setParams(CFeature::Activity,CFeature::Task);
}

CCompareTaskContributionToActivityTotalTime::~CCompareTaskContributionToActivityTotalTime(void)
{
}

void CCompareTaskContributionToActivityTotalTime::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	chartControl.resetSeries();

	int i=0;
	for (std::vector<CTest*>::iterator myIt=tests.begin();myIt!=tests.end();myIt++)
	{
		i++;
		CTest* pTest=*myIt;
		//
		CActivity* pActivity=(CActivity*) pTest->getFeatureByName(targetName);
		CTask* pTask=(CTask*) pTest->getFeatureByName(extraTargetName);
		//

		std::string activitySeries=pTest->getDescription()+std::string(" ")+pActivity->getName();
		std::string taskSeries=pTest->getDescription()+std::string(" ")+pTask->getName();

		chartControl.addSeries(activitySeries, CChartControl::Column);
		chartControl.addSeries(taskSeries, CChartControl::Column);

		for (std::vector<CTest*>::iterator myIt2=tests.begin();myIt2!=tests.end();myIt2++)
		{
			CTest* pTest2=*myIt2;
			if (pTest2!=pTest)
			{
				chartControl.addPoint(activitySeries,pTest2->getDescription(),0);
				chartControl.addPoint(taskSeries,pTest2->getDescription(),0);
			}
			else{
				double taskContribution=pTask->measureTimeContribution(pActivity->getStart(),pActivity->getStop());

				chartControl.addPoint(activitySeries,pTest->getDescription(),
					pActivity->getTimeElapse());

				chartControl.addPoint(taskSeries,pTest->getDescription(),
					taskContribution);
			}

		}
	}

	
}