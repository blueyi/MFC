/********************************************************************
    File:	        AnalyseAllActivitiesTotal	
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
#include "AnalyseAllActivitiesTotal.h"
#include "uicontroller.h"
REGISTER_CLASS(factory, CAnalyseAllActivitiesTotal, WM_ANALYSIS_ALLACTIVITIES_TOTAL)


CAnalyseAllActivitiesTotal::CAnalyseAllActivitiesTotal(void)
{
	setParams(CFeature::None,CFeature::None);
}

CAnalyseAllActivitiesTotal::~CAnalyseAllActivitiesTotal(void)
{
}

void CAnalyseAllActivitiesTotal::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CTest* pTest=theMachine.getSelectedAnalysisComboTests();

	chartControl.resetSeries();
	chartControl.addSeries(pTest->getName(), CChartControl::Pie);
	//

	for (activityMapT::iterator myIt=pTest->getActivitiesMap().begin();
		myIt!=pTest->getActivitiesMap().end();myIt++)
	{
		CActivity* pActivity=myIt->second;

		double timeTotal=pActivity->getTimeElapse();

		chartControl.addPoint(pTest->getName(),pActivity->getName(),
			timeTotal);
	}

}