/********************************************************************
    File:	        AnalyseAllTasksContributionToActivityStages	
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
#include "AnalyseAllTasksContributionToActivityStages.h"
#include "uicontroller.h"
REGISTER_CLASS(factory, CAnalyseAllTasksContributionToActivityStages, WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_STACKED)


CAnalyseAllTasksContributionToActivityStages::CAnalyseAllTasksContributionToActivityStages(void)
{
	setParams(CFeature::Activity,CFeature::None);
}

CAnalyseAllTasksContributionToActivityStages::~CAnalyseAllTasksContributionToActivityStages(void)
{
}

void CAnalyseAllTasksContributionToActivityStages::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	
	CActivity* pActivity=(CActivity*)pTarget;
	chartControl.resetSeries();

	chartControl.addSeries(pActivity->getName(), CChartControl::StackedColumn);

	CTest* pTest=theMachine.getParentSession(pActivity);

	taskMapT::iterator tasksIt;

	for (tasksIt=pTest->getTasksMap().begin();tasksIt!=pTest->getTasksMap().end();tasksIt++)
	{
		CTask* pTask=tasksIt->second;
		chartControl.addSeries(pTask->getName(), CChartControl::StackedColumn);
	}


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

		double allTasksContribution=0;

		for (taskMapT::iterator taskIt2=pTest->getTasksMap().begin();taskIt2!=pTest->getTasksMap().end();taskIt2++)
		{
			CTask* pTask=taskIt2->second;
			double taskContribution=pTask->measureTimeContribution(pLastPoint->getTime(),
				pCurPoint->getTime());

			chartControl.addPoint(pTask->getName(),pCurPoint->getName(),
				taskContribution);
			
			allTasksContribution+=taskContribution;
		}

		chartControl.addPoint(pActivity->getName(),pCurPoint->getName(),
			pCurPoint->getTime()-pLastPoint->getTime()-allTasksContribution);


		pLastPoint=pCurPoint;
		myIt++;
	}




}