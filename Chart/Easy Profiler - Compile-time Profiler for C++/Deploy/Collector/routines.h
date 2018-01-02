/************************************************************************/
/* Instrumentation routines interface definition file
Notes :
1.Add this file to your includes and link to the supplied lib module. Finally
deploy Profiler.dll next to your project executable.
2.Please make sure to read the commentary text explaining each instrumentation routine.
3.To use these routinse, you are advised to use the supplied helper-macros instead :
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



//************************************
// Name:  startRegion
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * regionName    : input a name of your choice
// Parameter: char collectionType  : input either 'v' or 'h'
// Description: surround your target code by startRegion and flushRegion. both accept a region name of your choice
//				as a first parameter. Input the 'h' value in the second parameter if you deal with fine portions of code
//				that are called thousands/million times during the lifetime of your region (a typical case would be
//				to profile a chess engine that performs millions of postion calculations and evaluations per second.
//************************************
PROFILER_API void startRegion(char* regionName,char collectionType);	
//************************************
// Name:  startActivity
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * activityName
// Description: surround the target sub portion with startActivity and stopActivities. It is preferable not
//				to have your activities overlap in time. It is mandatory that your activities are executed only once.
//************************************
PROFILER_API void startActivity(char* activityName);
//************************************
// lName:  insertCheckPoint
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * checkPointName
// Parameter: char * activityName
// Description: this routine is used to insert a point event within a particular activity indicated by the
//				second parameter. Make sure that your checkpoint is inserted between calls to startActivity and stopActivity.
//				For a particular activity name, a particular checkpoint name, there should be one call to insertCheckpoint.
//************************************
PROFILER_API void insertCheckPoint(char* checkPointName,char* activityName);
//************************************
// Name:  stopActivity
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * activityName
// Description : marks the exit point from your activity.
//************************************
PROFILER_API void stopActivity(char* activityName);
//************************************
// Name:  startTask
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * taskName
// Description: used to mark the entry point to a sub block of code that is supposed to be called concurrently and within loops,etc
//				Just insert a chosen name. The name should be unique within the scope of the target region.
//************************************
PROFILER_API void startTask(char* taskName);
//************************************
// Name:  stopTask
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * taskName
// Description: marks the exit point from the task indicated by the taskName parameter.
//************************************
PROFILER_API void stopTask(char* taskName);
//************************************
// Name:  startWorker
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * workerName
// Description: startWorker and stopWorker are used to model the execution/pausing of a particular thread.
//				It is necessary that all calls mae to startWorker/stopWorker with the same name, actualy emanate from the same
//				thread
//************************************
PROFILER_API void startWorker(char* workerName);
//************************************
// Name:  stopWorker
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * workerName
// Description: used to mark that the worker is not executing a job. 
//************************************
PROFILER_API void stopWorker(char* workerName);
//************************************
// Name:  flushRegion
// Returns:   PROFILER_API void
// Qualifier:
// Parameter: char * regionName
// Parameter: char * outputDirectory :   input the directory where data should go eg. "C:/tests/"
// Parameter: char outputType : input 's' or 'd'. In the first case, a new file with the name [regionName]_[DateTime].xml will
//								be created in the above indicated directory. In the latter,  the collector will look for
//								an existing file named : [regionName].xml and situated in the indicated directory. There data
//								will be appended to existing values.
//************************************
PROFILER_API void flushRegion(char* regionName,char* outputDirectory,char outputType);

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
