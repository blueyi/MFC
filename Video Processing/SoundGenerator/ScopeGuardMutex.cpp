#include "ScopeGuardMutex.h"
#include "Mutex.h"
#include "DBGAssert.h"

ScopeGuardMutex::ScopeGuardMutex(Mutex *pMutex)
{
	DBGASSERT( pMutex != NULL )
	m_pMutex = pMutex;
	pMutex->Get();
}

ScopeGuardMutex::~ScopeGuardMutex()
{		
	m_pMutex->Release();
}