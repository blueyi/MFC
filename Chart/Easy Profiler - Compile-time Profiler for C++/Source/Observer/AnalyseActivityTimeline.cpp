/********************************************************************
    File:	        AnalyseActivityTimeline	
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
#include "AnalyseActivityTimeline.h"

REGISTER_CLASS(factory, CAnalyseActivityTimeline, WM_ANALYSIS_SINGLEACTIVITY_TIMELINE)

CAnalyseActivityTimeline::CAnalyseActivityTimeline(void)
{
	setParams(CFeature::Activity,CFeature::None);
}

CAnalyseActivityTimeline::~CAnalyseActivityTimeline(void)
{
	//
	//
}

void CAnalyseActivityTimeline::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CActivity* pActivity=(CActivity*)pTarget;

	chartControl.resetSeries();
	chartControl.addSeries(pActivity->getName(),CChartControl::Spline);

	//

	CActivity::PointsVector pointVector=pActivity->getPoints();

	CActivity::PointsVector::iterator myIt;


	for (myIt = pointVector.begin(); myIt != pointVector.end(); myIt++ ){
		CActivity::CCheckPoint* pPoint=*myIt;
		//
		chartControl.addPoint(pActivity->getName(),pPoint->getName(),
			pPoint->getTime());
	}
}