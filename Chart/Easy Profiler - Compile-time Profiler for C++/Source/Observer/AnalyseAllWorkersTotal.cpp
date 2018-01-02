/********************************************************************
    File:	        AnalyseAllWorkersTotal	
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
#include "AnalyseAllWorkersTotal.h"
#include "uicontroller.h"
REGISTER_CLASS(factory, CAnalyseAllWorkersTotal, WM_ANALYSIS_ALLWORKERS_TOTAL)

CAnalyseAllWorkersTotal::CAnalyseAllWorkersTotal(void)
{
	setParams(CFeature::None,CFeature::None);
}

CAnalyseAllWorkersTotal::~CAnalyseAllWorkersTotal(void)
{
}

void CAnalyseAllWorkersTotal::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CTest* pTest=theMachine.getSelectedAnalysisComboTests();

	chartControl.resetSeries();
	chartControl.addSeries(pTest->getName(), CChartControl::Pie);
	//

	for (workerMapT::iterator myIt=pTest->getWorkersMap().begin();
		myIt!=pTest->getWorkersMap().end();myIt++)
	{
		CWorker* pWorker=myIt->second;

		double timeTotal=pWorker->getTimeTotal();

		chartControl.addPoint(pTest->getName(),pWorker->getName(),
			timeTotal);
	}
}