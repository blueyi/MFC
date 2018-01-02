#include "ToolMisc.h"




// launch a thread and return its handle
HANDLE runThread( LPTHREAD_START_ROUTINE fct, void* param )
{

	DWORD ThreadID;
	return CreateThread(	NULL, 0, 
							(LPTHREAD_START_ROUTINE)fct,
							param,
							0, &ThreadID	);	
}



