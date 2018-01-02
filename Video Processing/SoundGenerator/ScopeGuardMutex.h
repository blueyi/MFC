#ifndef _SCOPEGUARDMUTEX_INCLUDED
#define _SCOPEGUARDMUTEX_INCLUDED

#include <windows.h>

/********************************************
  
  Release the mutex when the object is destroyed.  

  Guaranty that the mutex will be released...

********************************************/
class ScopeGuardMutex
{
	class Mutex *m_pMutex;

public:

	ScopeGuardMutex(Mutex *pMutex);
	~ScopeGuardMutex();
};



#endif