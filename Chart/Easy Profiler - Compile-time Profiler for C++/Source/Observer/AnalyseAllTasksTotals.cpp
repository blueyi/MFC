/********************************************************************
    File:	        AnalyseAllTasksTotals	
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
#include "AnalyseAllTasksTotals.h"
#include "uicontroller.h"
REGISTER_CLASS(factory, CAnalyseAllTasksTotals, WM_ANALYSIS_ALLTASKS_TOTAL)

CAnalyseAllTasksTotals::CAnalyseAllTasksTotals(void)
{
	setParams(CFeature::None,CFeature::None);
}

CAnalyseAllTasksTotals::~CAnalyseAllTasksTotals(void)
{
}

void CAnalyseAllTasksTotals::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CTest* pTest=theMachine.getSelectedAnalysisComboTests();

	chartControl.resetSeries();
	chartControl.addSeries(pTest->getName(), CChartControl::Pie);
	//

	for (taskMapT::iterator myIt=pTest->getTasksMap().begin();
		myIt!=pTest->getTasksMap().end();myIt++)
	{
		CTask* pTask=myIt->second;

		double timeTotal=pTask->getTimeTotal();

		chartControl.addPoint(pTest->getName(),pTask->getName(),
			timeTotal);
	}

}