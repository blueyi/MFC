// AdvHeader.cpp : implementation file
//

#include "stdafx.h"
#include "ListImage.h"
#include "AdvHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvHeader

CAdvHeader::CAdvHeader()
{
}

CAdvHeader::~CAdvHeader()
{
}


BEGIN_MESSAGE_MAP(CAdvHeader, CHeaderCtrl)
	//{{AFX_MSG_MAP(CAdvHeader)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvHeader message handlers

BOOL CAdvHeader::Init(CHeaderCtrl *pHeader)
{	
	ASSERT(pHeader && pHeader->GetSafeHwnd());
	if (!SubclassWindow(pHeader->GetSafeHwnd()))
	{
		OutputDebugString(_T("Unable to subclass existing header!\n"));
		return FALSE;
	}
	return TRUE;
}
