#ifndef _PLAYER_INCLUDED
#define _PLAYER_INCLUDED

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <vector>
#include "IPlayer.h"


#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")

class Player : public IPlayer
{
private :
	SOUNDFORMAT m_format;						// Format for a sound buffer, 
											//	as describe in IPlayer.h

	LPDIRECTSOUNDBUFFER	m_lpDSBuffer;		// DirectSound buffer
	LPDIRECTSOUND m_lpDS;					// DirectSound object
	HWND m_hWnd;							// Window handler

	HANDLE* m_pReadEvent;
	HANDLE m_hNotifyEndThread;
	LPDIRECTSOUNDNOTIFY m_lpdsNotify;
	DSBPOSITIONNOTIFY* m_pDSNotify;

	int m_nbReadEvent;

	IPlayer::SoundEventListener* objectListener;
		

public :
	Player();
	~Player();
		
	virtual void Init();
	void SetHWnd(HWND p_hWnd);

	virtual void Play(long p_flag);
	virtual void Stop();	
	virtual bool CreateSoundBuffer(SOUNDFORMAT format, long bufferLength, long event);
	virtual void Write(long start, BYTE* data, long size);
	virtual bool CreateEventReadNotification(std::vector<DWORD>&p_event);	
	virtual void SetSoundEventListener(IPlayer::SoundEventListener* p_listener);
	virtual void RemoveSoundEventListener();

private :	
	class Mutex* m_mutex;

	void CallEvent(int eventNumber);
	void WaitNotif();

	static void WaitForNotify(Player* p_player) ;

};

#endif	