/********************************************************************
    File:	        CompareAllTasksTotalTimes	
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
#include "CompareAllTasksTotalTimes.h"
REGISTER_CLASS(factory2, CCompareAllTasksTotalTimes, WM_COMPARE_ALLTASKS_TOTAL)

CCompareAllTasksTotalTimes::CCompareAllTasksTotalTimes(void)
{
	setParams(CFeature::None,CFeature::None);
}

CCompareAllTasksTotalTimes::~CCompareAllTasksTotalTimes(void)
{
}

void CCompareAllTasksTotalTimes::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	chartControl.resetSeries();

	int i=0;
	for (std::vector<CTest*>::iterator testsIt=tests.begin();testsIt!=tests.end();testsIt++)
	{
		i++;
		CTest* pTest=*testsIt;
		
		//
		setupBlueColor(pTest->countTasks());

		for (taskMapT::iterator myIt=pTest->getTasksMap().begin();
			myIt!=pTest->getTasksMap().end();myIt++)
		{
			CTask* pTask=myIt->second;

			std::string taskSeriesName=pTask->getName()+std::string(" ")+pTest->getDescription();

			chartControl.addSeries(taskSeriesName,CChartControl::StackedColumn);
			chartControl.setSeriesColor(taskSeriesName,GetNextBlue());

			CString strProperty;
			strProperty.Format(_T("StackedGroupName=%d"),i);
			//
			chartControl.setCustomProperty(taskSeriesName,strProperty);


			chartControl.addPoint(taskSeriesName,pTest->getDescription()/*_T("Total")*/,pTask->getTimeTotal());
		}		
	}
}