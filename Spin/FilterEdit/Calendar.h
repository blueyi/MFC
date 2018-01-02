#ifndef CALENDAR_H
#define CALENDAR_H

#include <afxdtctl.h>

namespace FilterEdit
{
class CCalendar : public CMonthCalCtrl
{
protected:
	void ZeroTime (PSYSTEMTIME pSysTime);
	void SendDate ();
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMonthCal)
	protected:
	virtual BOOL PreTranslateMessage (MSG *pMsg);
	//}}AFX_VIRTUAL	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CCalendar)
	afx_msg void OnKillFocus (CWnd *pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
}

#endif
