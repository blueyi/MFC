/********************************************************************
    File:	        CompareActivityTimelines	
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
#include "CompareActivityTimelines.h"

REGISTER_CLASS(factory2, CCompareActivityTimelines, WM_COMPARE_SINGLEACTIVITY_TIMELINE)


CCompareActivityTimelines::CCompareActivityTimelines(void)
{
	setParams(CFeature::Activity,CFeature::None);
}

CCompareActivityTimelines::~CCompareActivityTimelines(void)
{
	//
}

void CCompareActivityTimelines::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{

	std::vector<CTest*>::iterator myIt;

	chartControl.resetSeries();


	for (myIt=tests.begin();myIt!=tests.end();myIt++)
	{
		CTest* pTest=*myIt;
		chartControl.addSeries(pTest->getDescription(),CChartControl::Spline);
		//

		CActivity* pActivity=(CActivity*) pTest->getFeatureByName(targetName);
		//
		CActivity::PointsVector pointVector=pActivity->getPoints();

		CActivity::PointsVector::iterator myIt;


		for (myIt = pointVector.begin(); myIt != pointVector.end(); myIt++ ){
			CActivity::CCheckPoint* pPoint=*myIt;
			//
			chartControl.addPoint(pTest->getDescription(),pPoint->getName(),
				pPoint->getTime());
		}
	}
	//
}
