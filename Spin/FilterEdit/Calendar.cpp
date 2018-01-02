#include "stdafx.h"
#include "Calendar.h"

namespace FilterEdit
{
void CCalendar::ZeroTime (PSYSTEMTIME pSysTime)
{
	pSysTime->wHour = 0;
	pSysTime->wMinute = 0;
	pSysTime->wSecond = 0;
	pSysTime->wMilliseconds = 0;
}

BOOL CCalendar::PreTranslateMessage (MSG *pMsg)
{
	BOOL bRet = FALSE;

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)
		{
			SYSTEMTIME st;
			COleDateTimeSpan ts (pMsg->wParam == VK_LEFT ? -1 : 1, 0, 0, 0);

			// Bug in control - workaround...
			GetCurSel (&st);
			ZeroTime (&st);

			COleDateTime dt (st);

			dt += ts;
			SetCurSel (dt);
			bRet = TRUE;
		}
		else if (pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
		{
			SYSTEMTIME st;
			COleDateTimeSpan ts (pMsg->wParam == VK_UP ? -7 : 7, 0, 0, 0);

			// Bug in control - workaround...
			GetCurSel (&st);
			ZeroTime (&st);

			COleDateTime dt (st);

			dt += ts;
			SetCurSel (dt);
			bRet = TRUE;
		}
		else if (pMsg->wParam == ' ' || pMsg->wParam == VK_RETURN)
		{
			NMSELCHANGE sc;

			::memset (&sc, 0, sizeof(sc));
			sc.nmhdr.hwndFrom = m_hWnd;
			sc.nmhdr.idFrom = 123;
			sc.nmhdr.code = MCN_SELECT;
			GetCurSel (&sc.stSelStart);
			ZeroTime (&sc.stSelStart);
			GetParent ()->SendMessage (WM_NOTIFY, 123,
				reinterpret_cast<LPARAM>(&sc));
			bRet = TRUE;
		}
	}

	if (!bRet)
	{
		bRet = CMonthCalCtrl::PreTranslateMessage (pMsg);
	}

	return bRet;
}

BEGIN_MESSAGE_MAP(CCalendar, CMonthCalCtrl)
	//{{AFX_MSG_MAP(CCalendar)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendar message handlers
void CCalendar::OnKillFocus (CWnd *pNewWnd)
{
	HWND hWnd = pNewWnd ? pNewWnd->m_hWnd : 0;

	GetParent ()->PostMessage (WM_KILLFOCUS, reinterpret_cast<WPARAM> (hWnd), 0);
}
}
