// Player.cpp : Implementation of Player class
//

#include "MATException.h"
#include "Player.h"
#include "DirectSoundErr.h"
#include "Mutex.h"
#include "ScopeGuardMutex.h"
#include "DbgAssert.h"
#include "ToolMisc.h"
#include <vector>



Player::Player()
	{
	// Reset the sound buffer
	m_lpDSBuffer = NULL;
	m_lpDS = NULL;
	m_hWnd = NULL;
	m_nbReadEvent = 0;
	m_pReadEvent = NULL;
	m_lpdsNotify = NULL;
	m_pDSNotify = NULL;
	m_hNotifyEndThread = NULL;

	m_mutex = new Mutex();
	}

Player::~Player()
{

	if (m_hNotifyEndThread) 
	{
		// set the first handle to terminate the waitNotif thread
		SetEvent(m_pReadEvent[m_nbReadEvent]);
		WaitForSingleObject(m_hNotifyEndThread, INFINITE);
		CloseHandle(m_hNotifyEndThread);
		
		// delete all remaining handles<
		for(int i =0; i <=m_nbReadEvent; ++i)
		{
			CloseHandle(m_pReadEvent[i]);			
		}

		delete[] m_pReadEvent;
	}


	//Free up the buffer
	if (m_lpdsNotify)
		m_lpdsNotify->Release();

	
	if(m_lpDSBuffer)		
		m_lpDSBuffer->Release();
		
	if (m_lpDS)
		m_lpDS->Release();

	if (m_pDSNotify)
		delete[] m_pDSNotify;


	delete m_mutex;

	
}

/*****
* Player::Init() : This function is the first one to be called after the Player instance.
*					It creates the DirectSound object which will be use after by the player.
*
*/
void Player::Init()
	{
	// Create DirectSound Object
	HRESULT hres = DirectSoundCreate(NULL, &m_lpDS, NULL);

	if (FAILED(hres))
		{
		EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::CreateDS DirectSoundCreate"));
		}

	// Set Cooperative Level
	hres = m_lpDS->SetCooperativeLevel(m_hWnd, DSSCL_EXCLUSIVE|DSSCL_PRIORITY);
	
	if (FAILED(hres))
		{
		EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::CreateDS SetCooperativeLevel"));
		}
	}


/*****
* Player::SetHWnd :	This function must be called before calling Init() 
*					Use to set the Window handling used in the Init function.
*
*/
void Player::SetHWnd(HWND p_hWnd)
	{
	m_hWnd = p_hWnd;
	}

/*****
*	Player::CreateSoundBuffer : This function creates the directSoundBuffer which will
*								eventually be read. We have to set the buffer desc 
*								(DSBUFFERDESC) and then, call CreateSoundBuffer.
*
*	@format :		The format of the data that will be read.
*	@bufferLength : The size of the buffer you will read.
*	@flags	:		specifying the capabilities to include when creating a 
*					new DirectSoundBuffer object
*
*/
bool Player::CreateSoundBuffer(SOUNDFORMAT format, long bufferLength, long flags)
	{
	WAVEFORMATEX wfx;
	DSBUFFERDESC dsbdesc;

	// Set up wave format structure.
	memset( &wfx, 0, sizeof(WAVEFORMATEX) );
	format.toWFX(wfx);	

	// Set up DSBUFFERDESC structure.
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));  // Zero it out. 
	dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags             = flags | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_STICKYFOCUS;
	dsbdesc.dwBufferBytes       = bufferLength; 
	dsbdesc.lpwfxFormat         = (LPWAVEFORMATEX)&wfx;

	// Once the buffer description complete, we have to create the buffer. 
	HRESULT hres = m_lpDS->CreateSoundBuffer(&dsbdesc, &m_lpDSBuffer, NULL);

	if (FAILED(hres))
		{
		EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::Create CreateSoundBuffer"));	
		}	

	return true;
	}


/*****
*	Player::Write : This function is used to fill in the LPDIRECTSOUND buffer with new data
*
*	@start	: Position where to start to put data in the DirectSoundBuffer
*	@data	: data itself.
*	@size	: length of the data buffer.
*
*/
void Player::Write(long start, BYTE* data, long size) 
	{
	// Lock data in buffer for writing
	LPVOID ptrData1;
	DWORD  ptrData1Size;
	LPVOID ptrData2;
	DWORD  ptrData2Size;
	HRESULT hres;
	
	hres = m_lpDSBuffer->Lock(start, size, &ptrData1, &ptrData1Size, &ptrData2, &ptrData2Size, DSBLOCK_ENTIREBUFFER );	
	
	
	if (FAILED(hres))
		{		
		EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::Write Lock"));
		}
	
	// Fill in the LPDIRECTSOUND buffer with new data
	CopyMemory(ptrData1, data, size);
	
	
	// Unlock data in buffer
	hres = m_lpDSBuffer->Unlock(ptrData1, ptrData1Size, ptrData2, ptrData2Size);
		
	if (FAILED(hres))
		{
		EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::Write Unlock"));
		}
	
	}


/*****
*	Player::Play : This function play the LPDIRECTSOUNDBUFFER. The buffer must be valid and
*					the buffer must have something in it to be played.
*
*	@flag	:	looping mode (0 = no, 1= yes)
*			
*
*/
void Player::Play(long p_flag)
	{
	DWORD status;

	if( p_flag == 1 )
	{
		p_flag = DSBPLAY_LOOPING;
		
	}
	else
	{
		p_flag = 0;
	}

	HRESULT hres = m_lpDSBuffer->GetStatus(&status);
	if (FAILED(hres))
		{		
		EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::Play GetStatus"));
		}

	if((status & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
		{
		hres = m_lpDSBuffer->Play(0, 0, p_flag);
	
		if (FAILED(hres))		// Play the sound
			{
			EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::Play Play"));
			}
		}
	}


/*****
*	Player::Stop : This function just stop playing the buffer.
*
*/
void Player::Stop()
	{
	DWORD status;

	if( m_lpDSBuffer == NULL )
	{
		return;		// object not created
	}

	HRESULT hres = m_lpDSBuffer->GetStatus(&status);
	if (FAILED(hres))
		{		
		EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::Stop GetStatus"));
		}

	if((status & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
		{
		hres = m_lpDSBuffer->Stop();		

		if (FAILED(hres))		// Play the sound
			{
			EXCEP(DirectSoundErr::GetErrDesc(hres), _T("Player::Stop Stop"));
			}
		}
	}

void Player::SetSoundEventListener(IPlayer::SoundEventListener* p_listener)
	{
	objectListener= p_listener;
	}

	
void Player::RemoveSoundEventListener()
	{
	ScopeGuardMutex g(m_mutex);

	objectListener= NULL;
	}

bool Player::CreateEventReadNotification(std::vector<DWORD>&vect_offset)
	{
	m_nbReadEvent = vect_offset.size();

	DBGASSERT( m_lpDSBuffer != NULL )
	DBGASSERT( m_pReadEvent == NULL )
	DBGASSERT( m_lpdsNotify == NULL )		// no event should have been created before
	DBGASSERT( m_pDSNotify == NULL )	
	
	DBGASSERT( m_nbReadEvent+2 <= MAXIMUM_WAIT_OBJECTS )	// must don't create more than MAXIMUM_WAIT_OBJECTS events
	
	m_pReadEvent = new HANDLE[m_nbReadEvent + 1];
	m_pDSNotify = new DSBPOSITIONNOTIFY[m_nbReadEvent + 1];	
	

	for( int t=0; t < m_nbReadEvent; t++ )
	{
		m_pReadEvent[t] = CreateEvent(NULL, 0, 0, NULL);

		m_pDSNotify[t].hEventNotify = m_pReadEvent[t];
		m_pDSNotify[t].dwOffset = vect_offset[t];
			
	}

	// end event
	m_pReadEvent[m_nbReadEvent] = CreateEvent(NULL, 0, 0, NULL);

	bool Success = true;



	HRESULT res = m_lpDSBuffer->QueryInterface(IID_IDirectSoundNotify,(void**)&m_lpdsNotify);
	if(FAILED(res))
		{		
		EXCEP(DirectSoundErr::GetErrDesc(res), _T("Player::CreateWriteNotification QueryInterface"))
		
		
		Success = false;
		}

	if( Success == true )
		{	
		res = m_lpdsNotify->SetNotificationPositions(m_nbReadEvent, m_pDSNotify);
		
		if( FAILED(res))
			{
			EXCEP(DirectSoundErr::GetErrDesc(res), _T("Player::CreateWriteNotification SetNotificationPositions"))
		
			
			Success = false;
			}

		}
	

	if( Success == false )	
		return 0;

	
	
	
	m_hNotifyEndThread = runThread((LPTHREAD_START_ROUTINE) WaitForNotify, this);		
	
	return true;
	}

/******************************************************

  WaitNotif

  Wait for a read notif.

******************************************************/
void Player::WaitNotif()
{	
	DBGASSERT( m_pReadEvent != NULL );	
	
	DWORD WaitRet;
	bool Continue = true;	

	do
	{
	
		WaitRet = WaitForMultipleObjects(	m_nbReadEvent+1,
											m_pReadEvent,
											0,
											INFINITE	);		
		
		DWORD EventNumber = WaitRet - WAIT_OBJECT_0;
		
		if( WaitRet == WAIT_FAILED )
			{			
			
			Continue = false;
			}
		else if( EventNumber < m_nbReadEvent )
			{
		
			CallEvent(EventNumber);

			}
		else if( EventNumber == m_nbReadEvent)
			{
			
			Continue = false;
			}
	
	}while( Continue );	
	
}

void Player::WaitForNotify(Player* p_player)
	{
	p_player->WaitNotif();
	}

void Player::CallEvent(int eventNumber)
	{
	ScopeGuardMutex g(m_mutex);

	if (objectListener)
		objectListener->OnSoundPlayerNotify(eventNumber);

	}




