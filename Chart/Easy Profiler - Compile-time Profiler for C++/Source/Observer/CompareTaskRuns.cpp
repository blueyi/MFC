/********************************************************************
    File:	        CompareTaskRuns	
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
#include "CompareTaskRuns.h"
REGISTER_CLASS(factory2, CCompareTaskRuns, WM_COMPARE_SINGLETASK_RUNHISTO)

CCompareTaskRuns::CCompareTaskRuns(void)
{
	setParams(CFeature::Task,CFeature::None);
}

CCompareTaskRuns::~CCompareTaskRuns(void)
{
}

void CCompareTaskRuns::execute( std::vector<CTest*> tests,std::string targetName,std::string extraTargetName )
{
	chartControl.resetSeries();

	for (std::vector<CTest*>::iterator testsIt=tests.begin();testsIt!=tests.end();testsIt++)
	{
		CTest* pTest=*testsIt;
		chartControl.addSeries(pTest->getDescription(),CChartControl::Column);
		//

		CTask* pTask=(CTask*) pTest->getFeatureByName(targetName);

		//
		int i=1;

		for (CTask::runsVectorT::iterator myIt=pTask->getRuns().begin();
			myIt!=pTask->getRuns().end();myIt++)
		{
			CString str;
			str.Format(_T("%d"),i);
			i++;


			CTask::CRun* pRun=*myIt;

			chartControl.addPoint(pTest->getDescription(),str,
				pRun->getStop()-pRun->getStart());
		}
	}
}