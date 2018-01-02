/********************************************************************
    File:	        AnalyseTaskContributionToActivityTotalTime	
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
#include "AnalyseTaskContributionToActivityTotalTime.h"
REGISTER_CLASS(factory, CAnalyseTaskContributionToActivityTotalTime, WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_TOTAL)


CAnalyseTaskContributionToActivityTotalTime::CAnalyseTaskContributionToActivityTotalTime(void)
{
	setParams(CFeature::Activity,CFeature::Task);
}

CAnalyseTaskContributionToActivityTotalTime::~CAnalyseTaskContributionToActivityTotalTime(void)
{
}

void CAnalyseTaskContributionToActivityTotalTime::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CActivity* pActivity=(CActivity*)pTarget;
	CTask* pTask=(CTask*)pExtraTarget;


	chartControl.resetSeries();

	chartControl.addSeries(pActivity->getName(), CChartControl::Column);
	chartControl.addSeries(pTask->getName(), CChartControl::Column);

	CActivity::CCheckPoint* pFirstPoint=pActivity->getPoints().front();
	CActivity::CCheckPoint* pLastPoint=pActivity->getPoints().back();

	double taskContribution=pTask->measureTimeContribution(pFirstPoint->getTime(),
		pLastPoint->getTime());


	chartControl.addPoint(pActivity->getName(),_T("Total"),
		pLastPoint->getTime()-pFirstPoint->getTime());

	chartControl.addPoint(pTask->getName(),_T("Total"),
		taskContribution);


}