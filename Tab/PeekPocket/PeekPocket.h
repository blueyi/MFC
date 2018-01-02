// PeekPocket.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

#include "WifiPeek.h"

class CPeekPocketApp : public CWinApp
{
public:
	CPeekPocketApp();
	
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPeekPocketApp theApp;

typedef CList<int, int > IntList;

struct DisplayInfo : BSSIDInfo
{
	DWORD ID;
	bool bActive;
	DATE dFirstSeen;
	DATE dLastSeen;
	int iBestSig;
	int iWorstSig;
	IntList ilSigHistory;

	DisplayInfo()
	{
	}

	DisplayInfo(const DisplayInfo &s)  // copy ctor
	{
		int i, count;
		POSITION pos;

		ID=s.ID;
		bActive=s.bActive;
		dFirstSeen=s.dFirstSeen;
		dLastSeen=s.dLastSeen;
		iBestSig=s.iBestSig;
		iWorstSig=s.iWorstSig;

		RSSI=s.RSSI;
		Channel=s.Channel;
		Infastructure=s.Infastructure;
		Auth=s.Auth;
		memcpy(BSSID, s.BSSID, 6);
		wcscpy(SSID, s.SSID);

		ilSigHistory.RemoveAll();
		count=s.ilSigHistory.GetCount();
		pos=s.ilSigHistory.GetHeadPosition();
		for(i=0; i<count; i++)
		{
			ilSigHistory.AddTail(s.ilSigHistory.GetNext(pos));
		}
	}
	DisplayInfo& operator=(const DisplayInfo &s)  // assignment operator
	{
		int i, count;
		POSITION pos;

		ID=s.ID;
		bActive=s.bActive;
		dFirstSeen=s.dFirstSeen;
		dLastSeen=s.dLastSeen;
		iBestSig=s.iBestSig;
		iWorstSig=s.iWorstSig;

		RSSI=s.RSSI;
		Channel=s.Channel;
		Infastructure=s.Infastructure;
		Auth=s.Auth;
		memcpy(BSSID, s.BSSID, 6);
		wcscpy(SSID, s.SSID);

		ilSigHistory.RemoveAll();
		count=s.ilSigHistory.GetCount();
		pos=s.ilSigHistory.GetHeadPosition();
		for(i=0; i<count; i++)
		{
			ilSigHistory.AddTail(s.ilSigHistory.GetNext(pos));
		}
		return *this;
	}
};

typedef CMap<BYTE *, BYTE *, DisplayInfo, DisplayInfo &> DisplayInfoMap;

//////////////////////////////////////////////////////////////////////////
//MAC Address hashing - used by map container
template<>
AFX_INLINE UINT AFXAPI HashKey<BYTE *> (BYTE *pKey)
{
	int i;
	UINT nHash;

	nHash = 0;
	for(i=0; i<6; i++)
	{
		nHash = (nHash<<5) + nHash + pKey[i];
	}
	return nHash;
}

//////////////////////////////////////////////////////////////////////////
template<>
AFX_INLINE BOOL AFXAPI CompareElements<BYTE *>(BYTE * const * pElement1, BYTE * const * pElement2)
{
	ENSURE(pElement1 != NULL && pElement2 != NULL);
	//this is a dummy function, when it gets called, hashes already were checked and this just does fine
	return TRUE;
}

