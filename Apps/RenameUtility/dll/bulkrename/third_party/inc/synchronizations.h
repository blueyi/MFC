/*************************************************************************************
 *************************************************************************************
 **																					**
 ** File name:		synchronizations.h.												**
 **																					**
 ** Description:	Header file of synchronization classes.							**
 **																					**
 ** Last update:	February 2002.													**
 **																					**
 ** Updated by:		Desyatnikov Stas.													**
 **																					**
 ** Copyright (C) 2002. All rights reserved.										**
 **																					**
 *************************************************************************************
 *************************************************************************************/

#ifndef __SYNCHRONIZATIONS_H__
#define __SYNCHRONIZATIONS_H__

#ifdef WIN32
	#include <Windows.h>
	#include <Winbase.h>
#elif OS_VXWORKS
	#include <vxWorks.h>
	#include <semLib.h> 
#endif

class CLock
{
public:
	virtual int Remove() { return 1; }
	virtual int Acquire() { return 1; }
	virtual int Release() { return 1; }
	virtual int TryAcquire() { return 1; }
	//Overridables for RW locks
	virtual int AcquireRead() { return 1; }
	virtual int AcquireWrite() { return 1; }
	virtual int TryAcquireRead() { return 1; }
	virtual int TryAcquireWrite() { return 1; }
};

class CNULLLock : public CLock
{
};

class CSectionLock : public CLock
{
#ifdef WIN32
	CRITICAL_SECTION	m_cs;
#elif OS_VXWORKS
	SEM_ID				m_cs;
#endif


public:
	CSectionLock()
	{
#ifdef WIN32
		InitializeCriticalSection( &m_cs );
#elif OS_VXWORKS
		//Recursive semaphore, init to full - available state
		m_cs = semMCreate( SEM_Q_PRIORITY ); 
#endif
	}
	
	~CSectionLock()
	{
		Remove();
	}

	virtual int Remove() 
	{
		Release();
#ifdef WIN32
		DeleteCriticalSection( &m_cs );
#elif OS_VXWORKS
		return semDelete( m_cs ) != ERROR;
#endif
		return 1;
	}
	
	virtual int Acquire() 
	{
#ifdef WIN32
		EnterCriticalSection( &m_cs );
#elif OS_VXWORKS
		return semTake( m_cs, WAIT_FOREVER ) != ERROR;
#endif
		//printf("Locked by thread:%d\n", GetCurrentThreadId());
		return 1;
	}

	virtual int Release() 
	{
#ifdef WIN32
		LeaveCriticalSection( &m_cs );
#elif OS_VXWORKS
		return semGive( m_cs ) != ERROR;
#endif
		return 1;
	}

	virtual int TryAcquire() 
	{
#ifdef WIN32
		//Somehow doesnt work on NT4
		//return TryEnterCriticalSection( &m_cs );
		EnterCriticalSection( &m_cs );
		return 1;
#elif OS_VXWORKS
		return semTake( m_cs, 1 ) != ERROR;
#endif
	}
};


//Guard must be a stack object, so the LockRef does not need protection
class CGuard
{
	CLock*	m_pLock;
	uint	m_uiLockRef;
public:
	CGuard( CLock* pLock )
	{
		m_pLock = pLock;
		m_uiLockRef = 0;
	}
	
	int Lock()
	{
		int iRet = m_pLock->Acquire();
		m_uiLockRef += ( iRet != 0 );

		return m_uiLockRef;
	}

	int Unlock()
	{
		if ( m_pLock && m_uiLockRef )
			m_uiLockRef -= ( m_pLock->Release() != 0 );
		
		return m_uiLockRef;
	}
	~CGuard()
	{
		Unlock();
	}
};

#endif //__SYNCHRONIZATIONS_H__
