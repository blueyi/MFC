/********************************************************************
    File:	        CompareWorkerRuns	
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
#include "CompareWorkerRuns.h"
REGISTER_CLASS(factory2, CCompareWorkerRuns, WM_COMPARE_SINGLEWORKER_RUNHISTO)

CCompareWorkerRuns::CCompareWorkerRuns(void)
{
	setParams(CFeature::Worker,CFeature::None);
}

CCompareWorkerRuns::~CCompareWorkerRuns(void)
{
}

void CCompareWorkerRuns::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	chartControl.resetSeries();

	for (std::vector<CTest*>::iterator testsIt=tests.begin();testsIt!=tests.end();testsIt++)
	{
		CTest* pTest=*testsIt;
		chartControl.addSeries(pTest->getDescription(),CChartControl::Column);
		//

		CWorker* pWorker=(CWorker*) pTest->getFeatureByName(targetName);

		//
		int i=1;

		for (CWorker::runsVectorT::iterator myIt=pWorker->getRuns().begin();
			myIt!=pWorker->getRuns().end();myIt++)
		{
			CString str;
			str.Format(_T("%d"),i);
			i++;


			CWorker::CRun* pRun=*myIt;

			chartControl.addPoint(pTest->getDescription(),str,
				pRun->getPause()-pRun->getStart());
		}
	}
}