// Spin.cpp : implementation file
//

#include "stdafx.h"
#include "Spin.h"

#include "BaseEdit.h"

namespace FilterEdit
{
// CSpin
IMPLEMENT_DYNAMIC (CSpin, CSpinButtonCtrl)
CSpin::CSpin ()
{
}

CSpin::~CSpin ()
{
}

BEGIN_MESSAGE_MAP (CSpin, CSpinButtonCtrl)
	ON_NOTIFY_REFLECT(UDN_DELTAPOS, OnDeltapos)
END_MESSAGE_MAP ()

// CSpin message handlers
void CSpin::OnDeltapos (NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN> (pNMHDR);
	CBaseEdit *pEdit = reinterpret_cast<CBaseEdit *> (GetBuddy ());

	if (!(pEdit->GetStyle () & ES_READONLY))
	{
		// Delta sign has to be reversed...  Also its value is inconsistent.
		pEdit->Increment (pNMUpDown->iDelta >= 0 ? -1 : 1);
	}

	*pResult = 0;
}
}
