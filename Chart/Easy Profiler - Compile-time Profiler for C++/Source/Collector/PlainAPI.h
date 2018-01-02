/********************************************************************
    File:	        PlainAPI	
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
#include "Profiler.h"


PROFILER_API void startRegion(char* regionName,char collectionType);
//
PROFILER_API void startActivity(char* activityName);
PROFILER_API void insertCheckPoint(char* checkPointName,char* activityName);
PROFILER_API void stopActivity(char* activityName);
PROFILER_API void startTask(char* taskName);
PROFILER_API void stopTask(char* taskName);
PROFILER_API void startWorker(char* workerName);
PROFILER_API void stopWorker(char* workerName);
//
PROFILER_API void flushRegion(char* regionName,char* outputDirectory,char outputType);
	//if outputType=s then output is a separate file



#include "TestsCollection.h"




