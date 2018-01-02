/********************************************************************
    File:	        AnalyseActivityStages	
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
#include "AnalyseActivityStages.h"
REGISTER_CLASS(factory, CAnalyseActivityStages, WM_ANALYSIS_SINGLEACTIVITY_STAGES)


CAnalyseActivityStages::CAnalyseActivityStages(void)
{
	setParams(CFeature::Activity,CFeature::None);
}

CAnalyseActivityStages::~CAnalyseActivityStages(void)
{
}

void CAnalyseActivityStages::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CActivity* pActivity=(CActivity*)pTarget;
	chartControl.resetSeries();
	chartControl.addSeries(pActivity->getName(),CChartControl::Column);

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


		chartControl.addPoint(pActivity->getName(),pCurPoint->getName(),
			pCurPoint->getTime()-pLastPoint->getTime());

		pLastPoint=pCurPoint;
		myIt++;
	}
}