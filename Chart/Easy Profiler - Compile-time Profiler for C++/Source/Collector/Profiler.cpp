// Profiler.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Profiler.h"



#include "TestSession.h"




CTest* pCurrentTest=NULL;


PROFILER_API void startRegion(char* regionName,char collectionType)
{
	pCurrentTest=new CTest(regionName);
	pCurrentTest->initTest();
	//
	if (collectionType=='p')
	{
		pCurrentTest->setCompressionMode();
	}
}
//
PROFILER_API void startActivity(char* activityName)
{
	pCurrentTest->beginActivity(activityName);
}
PROFILER_API void insertCheckPoint(char* checkPointName,char* activityName)
{
	pCurrentTest->insertCheckPoint(activityName,checkPointName);
}
PROFILER_API void stopActivity(char* activityName)
{
	pCurrentTest->endActivity(activityName);
}
PROFILER_API void startTask(char* taskName)
{
	pCurrentTest->beginTask(taskName);
}
PROFILER_API void stopTask(char* taskName)
{
	pCurrentTest->endTask(taskName);
}
PROFILER_API void startWorker(char* workerName)
{
	pCurrentTest->runWorker(workerName);
}
PROFILER_API void stopWorker(char* workerName)
{
	pCurrentTest->pauseWorker(workerName);
}
//
PROFILER_API void flushRegion(char* regionName,char* outputDirectory,char outputType)
{
	pCurrentTest->flush(regionName,outputDirectory,outputType);
}