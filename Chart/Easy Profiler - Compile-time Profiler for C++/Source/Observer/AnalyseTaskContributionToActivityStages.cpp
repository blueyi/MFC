/********************************************************************
    File:	        AnalyseTaskContributionToActivityStages	
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
#include "AnalyseTaskContributionToActivityStages.h"

REGISTER_CLASS(factory, CAnalyseTaskContributionToActivityStages, WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_STACKED)

CAnalyseTaskContributionToActivityStages::CAnalyseTaskContributionToActivityStages(void)
{
	setParams(CFeature::Activity,CFeature::Task);
}

CAnalyseTaskContributionToActivityStages::~CAnalyseTaskContributionToActivityStages(void)
{
}

void CAnalyseTaskContributionToActivityStages::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CActivity* pActivity=(CActivity*)pTarget;
	CTask* pTask=(CTask*)pExtraTarget;


	chartControl.resetSeries();

	chartControl.addSeries(pActivity->getName(), CChartControl::StackedColumn);
	chartControl.addSeries(pTask->getName(), CChartControl::StackedColumn);


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


		chartControl.addPoint(pActivity->getName(),pCurPoint->getName(),
			pCurPoint->getTime()-pLastPoint->getTime()-taskContribution);

		chartControl.addPoint(pTask->getName(),pCurPoint->getName(),
			taskContribution);

		pLastPoint=pCurPoint;
		myIt++;
	}

}