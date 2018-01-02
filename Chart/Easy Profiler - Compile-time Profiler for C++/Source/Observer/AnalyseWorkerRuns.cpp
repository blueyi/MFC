/********************************************************************
    File:	        AnalyseWorkerRuns	
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
#include "AnalyseWorkerRuns.h"
REGISTER_CLASS(factory, CAnalyseWorkerRuns, WM_ANALYSIS_SINGLEWORKER_RUNPAUSE)

CAnalyseWorkerRuns::CAnalyseWorkerRuns(void)
{
	setParams(CFeature::Worker,CFeature::None);
}

CAnalyseWorkerRuns::~CAnalyseWorkerRuns(void)
{
}

void CAnalyseWorkerRuns::execute( CFeature* pTarget,CFeature* pExtraTarget/*=NULL*/ )
{
	CWorker* pWorker=(CWorker*) pTarget;
	//
	chartControl.resetSeries();
	chartControl.addSeries(pWorker->getName(),
		CChartControl::Column);



	CWorker::runsVectorT::iterator myIt;


	int iCount=1;

	for (myIt = pWorker->getRuns().begin(); myIt != pWorker->getRuns().end(); myIt++ ){
		CWorker::CRun* pCurRun=*myIt;

		CString strX;
		strX.Format(_T("%d"),iCount);



		chartControl.addPoint(pWorker->getName(),strX,
			pCurRun->getPause()-pCurRun->getStart());
		iCount++;

	}
}