// DestEquipCom_Intervention.h: interface for the CComSocket_SysDiagnosis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESTEQUIPCOM_INTERVENTION_H__B7B9B21D_3796_4722_953C_ECFAFF492299__INCLUDED_)
#define AFX_DESTEQUIPCOM_INTERVENTION_H__B7B9B21D_3796_4722_953C_ECFAFF492299__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ------------------------------------------------------------------------------------------
#include "CommonDefine.h"
#include "Com.h"
#include "SockCom\\TcpComForWindows.h"

// ------------------------------------------------------------------------------------------
// 作为介入监控终端的服务器
class CComSocket_SysDiagnosis : public CCom
{
public:
	CComSocket_SysDiagnosis();
	virtual ~CComSocket_SysDiagnosis();

private:
	short m_nNumOfPort;
	CTcpComForWindows* m_pTcpComForWindows;
	UINT m_nBroadcastMsgId;
	
public:
	void Init( HWND hWnd, UINT nMessageID );

	void AcceptRequest( unsigned short nTypeOfAcceptRequest );
};

#endif // !defined(AFX_DESTEQUIPCOM_INTERVENTION_H__B7B9B21D_3796_4722_953C_ECFAFF492299__INCLUDED_)
