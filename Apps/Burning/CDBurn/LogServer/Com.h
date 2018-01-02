// DestEquipCom.h: interface for the CCom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESTEQUIPCOM_H__4153F062_2AD7_4A0B_91B5_BE760F2055C2__INCLUDED_)
#define AFX_DESTEQUIPCOM_H__4153F062_2AD7_4A0B_91B5_BE760F2055C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
class CCom  
{
public:
	CCom();
	virtual ~CCom();

public:
	// for Send message to calling window
	void SendMessageToCallingWindow( HWND hCallingWnd, DWORD nByteOfPacket, void* pPacket );

	//
	CString m_sConfigFileName;

};

#endif // !defined(AFX_DESTEQUIPCOM_H__4153F062_2AD7_4A0B_91B5_BE760F2055C2__INCLUDED_)
