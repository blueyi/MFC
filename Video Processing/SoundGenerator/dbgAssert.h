#ifndef _DBGASSERT_INCLUDED
#define _DBGASSERT_INCLUDED

#ifdef _DEBUG

	#include <assert.h>
	#define DBGASSERT(condition) assert(condition);	

#else
	#define DBGASSERT(condition)

#endif




#endif