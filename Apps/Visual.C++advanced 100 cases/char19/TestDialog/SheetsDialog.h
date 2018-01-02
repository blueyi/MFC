/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/20/98 9:25:26 AM
  Comments: SheetsDialog.h: interface for the CSheetsDialog class.
 ************************************/

#if !defined(AFX_SHEETSDIALOG_H__CCAACD81_1F93_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_SHEETSDIALOG_H__CCAACD81_1F93_11D2_864F_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SheetsWnd.h"
#include <afxtempl.h>

struct SCtrlID {
	CMap<UINT,UINT,BOOL,BOOL> m_mapCtrlIDs;
	SCtrlID()
	{
		m_mapCtrlIDs[IDOK] = TRUE;
		m_mapCtrlIDs[IDCANCEL] = TRUE;
		m_mapCtrlIDs[IDC_STATIC] = TRUE;
	};
	BOOL Is(UINT id)
	{
		BOOL bValue = TRUE;
		return m_mapCtrlIDs.Lookup(id, bValue);
	}
};

class CSheetsDialog : public CSheetsWnd  
{
public:
	CSheetsDialog();
	virtual ~CSheetsDialog();
	virtual CWnd* GetNextView();
	virtual CWnd* GetFirstView();

private:
	CWnd* GetNextViewValid(CWnd* pWnd);
	static SCtrlID m_ctrlID;
	
};

#endif // !defined(AFX_SHEETSDIALOG_H__CCAACD81_1F93_11D2_864F_0040055C08D9__INCLUDED_)
