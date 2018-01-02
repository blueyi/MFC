/********************************************************************
    File:	        AnalyseAllTasksContributionToActivityTotalTime	
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
#include "AnalyseAllTasksContributionToActivityTotalTime.h"
#include "uicontroller.h"
REGISTER_CLASS(factory, CAnalyseAllTasksContributionToActivityTotalTime, WM_ANALYSIS_SINGLEACTIVITY_WITHALLTASKS_TOTAL)

CAnalyseAllTasksContributionToActivityTotalTime::CAnalyseAllTasksContributionToActivityTotalTime(void)
{
	setParams(CFeature::Activity,CFeature::None);
}

CAnalyseAllTasksContributionToActivityTotalTime::~CAnalyseAllTasksContributionToActivityTotalTime(void)
{
}

void CAnalyseAllTasksContributionToActivityTotalTime::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CActivity* pActivity=(CActivity*)pTarget;
	chartControl.resetSeries();

	chartControl.addSeries(pActivity->getName(), CChartControl::Column);

	CTest* pTest=theMachine.getParentSession(pActivity);


	for (taskMapT::iterator tasksIt=pTest->getTasksMap().begin();tasksIt!=pTest->getTasksMap().end();tasksIt++)
	{
		CTask* pTask=tasksIt->second;
		chartControl.addSeries(pTask->getName(), CChartControl::Column);
	}


	CActivity::CCheckPoint* pFirstPoint=pActivity->getPoints().front();
	CActivity::CCheckPoint* pLastPoint=pActivity->getPoints().back();

	chartControl.addPoint(pActivity->getName(),_T("Total"),
		pLastPoint->getTime()-pFirstPoint->getTime());



	for (taskMapT::iterator tasksIt=pTest->getTasksMap().begin();tasksIt!=pTest->getTasksMap().end();tasksIt++)
	{
		CTask* pTask=tasksIt->second;
		
		double taskContribution=pTask->measureTimeContribution(pFirstPoint->getTime(),
			pLastPoint->getTime());
		chartControl.addPoint(pTask->getName(),_T("Total"),
			taskContribution);
	}

	
}