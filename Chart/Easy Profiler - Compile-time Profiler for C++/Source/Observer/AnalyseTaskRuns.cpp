/********************************************************************
    File:	        AnalyseTaskRuns	
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
#include "AnalyseTaskRuns.h"
REGISTER_CLASS(factory, CAnalyseTaskRuns, WM_ANALYSIS_SINGLETASK_RUNSHISTORY)

CAnalyseTaskRuns::CAnalyseTaskRuns(void)
{
	setParams(CFeature::Task,CFeature::None);
}

CAnalyseTaskRuns::~CAnalyseTaskRuns(void)
{
}

void CAnalyseTaskRuns::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CTask* pTask=(CTask*) pTarget;
	//
	chartControl.resetSeries();
	chartControl.addSeries(pTask->getName(),
		CChartControl::Column);



	CTask::runsVectorT::iterator myIt;


	int iCount=1;

	for (myIt = pTask->getRuns().begin(); myIt != pTask->getRuns().end(); myIt++ ){
		CTask::CRun* pCurRun=*myIt;

		CString strX;
		strX.Format(_T("%d"),iCount);



		chartControl.addPoint(pTask->getName(),strX,
			pCurRun->getStop()-pCurRun->getStart());
		iCount++;

	}
}