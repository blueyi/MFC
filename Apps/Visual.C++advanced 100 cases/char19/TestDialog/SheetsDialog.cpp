/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/20/98 8:58:48 AM
  Comments: ...
 ************************************/

#include "stdafx.h"
#include "TestDialog.h"
#include "SheetsDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SCtrlID CSheetsDialog::m_ctrlID;

// Function name	: CSheetsDialog::CSheetsDialog
// Description	    : 
// Return type		: 
CSheetsDialog::CSheetsDialog()
{
}

// Function name	: CSheetsDialog::~CSheetsDialog
// Description	    : 
// Return type		: 
CSheetsDialog::~CSheetsDialog()
{

}

// Function name	: CSheetsDialog::GetFirstView
// Description	    : Get first
// Return type		: CWnd* 
CWnd* CSheetsDialog::GetFirstView()
{
	return GetNextViewValid(CSheetsWnd::GetFirstView());
}

// Function name	: CSheetsDialog::GetNextView
// Description	    : Get next...
// Return type		: CWnd* 
CWnd* CSheetsDialog::GetNextView()
{
	return GetNextViewValid(CSheetsWnd::GetNextView());;
}

// Function name	: CSheetsDialog::GetNextViewValid
// Description	    : Valid view
// Return type		: CWnd* 
// Argument         : CWnd * pWnd
CWnd* CSheetsDialog::GetNextViewValid(CWnd * pWnd)
{
	while (pWnd && (m_ctrlID.Is(pWnd->GetDlgCtrlID())))
		pWnd = CSheetsWnd::GetNextView();
	return pWnd;
}
