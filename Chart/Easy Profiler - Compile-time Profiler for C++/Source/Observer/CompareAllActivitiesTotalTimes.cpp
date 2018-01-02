/********************************************************************
    File:	        CompareAllActivitiesTotalTimes	
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
#include "CompareAllActivitiesTotalTimes.h"
REGISTER_CLASS(factory2, CCompareAllActivitiesTotalTimes, WM_COMPARE_SALLACTIVITIES_TOTAL)

CCompareAllActivitiesTotalTimes::CCompareAllActivitiesTotalTimes(void)
{
	setParams(CFeature::None,CFeature::None);
}

CCompareAllActivitiesTotalTimes::~CCompareAllActivitiesTotalTimes(void)
{
}

void CCompareAllActivitiesTotalTimes::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	chartControl.resetSeries();

	int i=0;
	for (std::vector<CTest*>::iterator testsIt=tests.begin();testsIt!=tests.end();testsIt++)
	{
		i++;
		CTest* pTest=*testsIt;

		//

		for (activityMapT::iterator myIt=pTest->getActivitiesMap().begin();
			myIt!=pTest->getActivitiesMap().end();myIt++)
		{
			CActivity* pActivity=myIt->second;

			std::string activitySeriesName=pActivity->getName()+std::string(" ")+pTest->getDescription();

			chartControl.addSeries(activitySeriesName,CChartControl::StackedColumn);

			CString strProperty;
			strProperty.Format(_T("StackedGroupName=%d"),i);
			//
			chartControl.setCustomProperty(activitySeriesName,strProperty);


			chartControl.addPoint(activitySeriesName,_T("Total"),pActivity->getTimeElapse());
		}		
	}
}