/************************************************************************/
/* Instrumentation routines interface definition
Notes :
1.Add this file to your includes and link to the supplied lib module. Finally
deploy Profiler.dll next to your project executable.
2.Please make sure to read the commentary text explaining each instrumentation routine.
3.To use these routine, you are advised to use the supplied helper-macros instead :
this will help you easily get rid of the instrumentation code, once you want to get
the final compilation. If you un-define the EasyProfiler symbol, the macros will
compile to nothing, hereby removing any effect on your compilation result.

Part of Easy Profiler deliverables.
Potato software. http://www.potatosoftware.com*/
/************************************************************************/


#ifdef PROFILER_EXPORTS
#define PROFILER_API __declspec(dllexport)
#else
#define PROFILER_API __declspec(dllimport)
#endif



PROFILER_API void startRegion(char* regionName,char collectionType);
//************************************
// FullName:  startActivity
// Description:  
//    marks the entry point to your profiling region.
// reg
//	  put the character 'v' to indicate a verbose data collection, and 'h'
//************************************
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

#ifndef EasyProfiler
#define EasyProfiler
#endif

#ifdef EasyProfiler
#define _startRegion(regionName,collectionType) startRegion(regionName,collectionType);
#define _startActivity(activityName) startActivity(activityName);
#define _insertCheckPoint(checkPointName,activityName) insertCheckPoint(checkPointName,activityName);
#define _stopActivity(activityName) stopActivity(activityName);
#define _startTask(taskName) startTask(taskName);
#define _stopTask(taskName) stopTask(taskName);
#define _startWorker(workerName) startWorker(workerName);
#define _stopWorker(workerName) stopWorker(workerName);
#define _flushRegion(regionName,outputDirectory,outputType) flushRegion(regionName,outputDirectory,outputType);
#else
#define _startRegion(regionName,collectionType) 
#define _startActivity(activityName) 
#define _insertCheckPoint(checkPointName,activityName) 
#define _stopActivity(activityName) 
#define _startTask(taskName) 
#define _stopTask(taskName) 
#define _startWorker(workerName) 
#define _stopWorker(workerName) 
#define _flushRegion(regionName,outputDirectory,outputType)
#endif
