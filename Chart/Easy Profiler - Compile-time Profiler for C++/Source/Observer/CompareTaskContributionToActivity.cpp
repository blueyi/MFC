/********************************************************************
    File:	        CompareTaskContributionToActivity	
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
#include "CompareTaskContributionToActivity.h"
REGISTER_CLASS(factory2, CCompareTaskContributionToActivity, WM_COMPARE_SINGLEACTIVITY_WITHTASK_STACKED)


CCompareTaskContributionToActivity::CCompareTaskContributionToActivity(void)
{
	setParams(CFeature::Activity,CFeature::Task);
}

CCompareTaskContributionToActivity::~CCompareTaskContributionToActivity(void)
{
}

void CCompareTaskContributionToActivity::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	std::vector<CTest*>::iterator myIt;
	chartControl.resetSeries();

	int i=0;
	for (myIt=tests.begin();myIt!=tests.end();myIt++)
	{
		i++;
		CTest* pTest=*myIt;
		//
		CActivity* pActivity=(CActivity*) pTest->getFeatureByName(targetName);
		CTask* pTask=(CTask*) pTest->getFeatureByName(extraTargetName);
		//

		std::string activitySeries=pTest->getDescription()+std::string(" ")+pActivity->getName();
		std::string taskSeries=pTest->getDescription()+std::string(" ")+pTask->getName();

		chartControl.addSeries(activitySeries, CChartControl::StackedColumn);
		chartControl.addSeries(taskSeries, CChartControl::StackedColumn);

		
		CString strProperty;
		strProperty.Format(_T("StackedGroupName=%d"),i);
		//
		chartControl.setCustomProperty(activitySeries,strProperty);
		chartControl.setCustomProperty(taskSeries,strProperty);


		//
		CActivity::PointsVector pointVector=pActivity->getPoints();

		CActivity::PointsVector::iterator myIt;



		myIt=pointVector.begin();
		if (myIt==pointVector.end())
			return;

		CActivity::CCheckPoint* pLastPoint=*myIt;

		myIt++;

		while (myIt != pointVector.end())
		{
			CActivity::CCheckPoint* pCurPoint=*myIt;

			double taskContribution=pTask->measureTimeContribution(pLastPoint->getTime(),
				pCurPoint->getTime());


			chartControl.addPoint(activitySeries,pCurPoint->getName(),
				pCurPoint->getTime()-pLastPoint->getTime()-taskContribution);

			chartControl.addPoint(taskSeries,pCurPoint->getName(),
				taskContribution);

			pLastPoint=pCurPoint;
			myIt++;
		}
	}
}