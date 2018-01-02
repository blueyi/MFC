// BulkRename.h : main header file for the BulkRename DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CBulkRenameApp
// See BulkRename.cpp for the implementation of this class
//

class CBulkRenameApp : public CWinApp
{
public:
	CBulkRenameApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
