#include "StdAfx.h"
#include "DateTimeEdit.h"

namespace FilterEdit
{
bool CDateTimeEdit::m_bInitialised = false;
CRegEx CDateTimeEdit::m_DateRegEx;
CRegEx CDateTimeEdit::m_TimeHHMMRegEx;
CRegEx CDateTimeEdit::m_TimeHHMMSSRegEx;
CRegEx CDateTimeEdit::m_DateTimeHHMMRegEx;
CRegEx CDateTimeEdit::m_DateTimeHHMMSSRegEx;
DWORD CDateTimeEdit::m_dwCenturyPrefix = 0;
DWORD CDateTimeEdit::m_dwTwoDigitYearMax = 0;
TCHAR CDateTimeEdit::m_chFieldOrder = 0;
int CDateTimeEdit::m_iDayIndexStart = -1;
int CDateTimeEdit::m_iDayIndexEnd = -1;
int CDateTimeEdit::m_iMonthIndexStart = -1;
int CDateTimeEdit::m_iMonthIndexEnd = -1;
int CDateTimeEdit::m_iYearIndexStart = -1;
int CDateTimeEdit::m_iYearIndexEnd = -1;
int CDateTimeEdit::m_iDateLength = -1;
TCHAR CDateTimeEdit::m_cDateSeparator = 0;
TCHAR CDateTimeEdit::m_cTimeSeparator = 0;
CString CDateTimeEdit::m_strDateToolTip;
CString CDateTimeEdit::m_strTimeHHMMToolTip;
CString CDateTimeEdit::m_strTimeHHMMSSToolTip;
CString CDateTimeEdit::m_strDateTimeHHMMToolTip;
CString CDateTimeEdit::m_strDateTimeHHMMSSToolTip;

static const int WM_CREATE_CAL_BUTTON = (WM_USER + 1);

void AFXAPI DDX_DateTimeEdit(CDataExchange *pDX, int nIDC, COleDateTime &Date)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	CDateTimeEdit *pWnd = static_cast<CDateTimeEdit *>
		(CWnd::FromHandle(hWndCtrl));

	if (pDX->m_bSaveAndValidate)
	{
		Date = pWnd->GetDateTime();
	}
	else
	{
		pWnd->SetDateTime(Date);
	}
}

void AFXAPI DDX_DateTimeEdit(CDataExchange *pDX, int nIDC, CString &Date)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	CDateTimeEdit *pWnd = static_cast<CDateTimeEdit *>
		(CWnd::FromHandle(hWndCtrl));

	if (pDX->m_bSaveAndValidate)
	{
		if (pWnd->IsInputValid(false))
		{
			pWnd->GetWindowText(Date);
		}
		else
		{
			Date.Empty();
		}
	}
	else
	{
		pWnd->SetWindowText(Date);
	}
}

// TODO:
// - Calculate calendar type automatically?  (Currently CAL_GREGORIAN)
CDateTimeEdit::CDateTimeEdit (const e_Mode eMode/* = eDate*/) :
	CBaseEdit (eMode == eTimeHHMM ? &m_TimeHHMMRegEx :
	eMode == eTimeHHMMSS ? &m_TimeHHMMSSRegEx :
	eMode == eDateTimeHHMM ? &m_DateTimeHHMMRegEx :
	eMode == eDateTimeHHMMSS ? &m_DateTimeHHMMSSRegEx :
	&m_DateRegEx),
	m_eMode (eMode),
	m_dwMargins (0),
	m_bFromSpin (false),
	m_pCalendarDlg (0),
	m_iHourIndexStart (-1),
	m_iHourIndexEnd (-1),
	m_iMinuteIndexStart (-1),
	m_iMinuteIndexEnd (-1),
	m_iSecondIndexStart (-1),
	m_iSecondIndexEnd (-1)
{
	m_Min.SetStatus(COleDateTime::null);
	m_Max.SetStatus(COleDateTime::null);

	if (!m_bInitialised)
	{
		TCHAR szData[4] = _T("");
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_SDATE, szData, 4);
		m_cDateSeparator = *szData;

#if _MSC_VER < 1310
		SYSTEMTIME st;

		::GetLocalTime (&st);
		m_dwCenturyPrefix = st.wYear + 24;
#else
		::GetCalendarInfo (LOCALE_USER_DEFAULT, CAL_GREGORIAN,
			CAL_RETURN_NUMBER | CAL_ITWODIGITYEARMAX, 0, 0,
			&m_dwCenturyPrefix);
#endif
		m_dwTwoDigitYearMax = m_dwCenturyPrefix % 1000;
		m_dwCenturyPrefix -= m_dwTwoDigitYearMax;
		m_dwCenturyPrefix /= 100;
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_IDATE, szData, 2);

		switch (*szData)
		{
			case '0':
				m_chFieldOrder = 'm';
				m_iMonthIndexStart = 0;
				m_iMonthIndexEnd = 2;
				m_iDayIndexStart = m_iMonthIndexEnd + 1;
				m_iDayIndexEnd = m_iDayIndexStart + 2;
				m_iYearIndexStart = m_iDayIndexEnd + 1;
				m_iYearIndexEnd = m_iYearIndexStart + 4;
				break;
			case '1':
				m_chFieldOrder = 'd';
				m_iDayIndexStart = 0;
				m_iDayIndexEnd = 2;
				m_iMonthIndexStart = m_iDayIndexEnd + 1;
				m_iMonthIndexEnd = m_iMonthIndexStart + 2;
				m_iYearIndexStart = m_iMonthIndexEnd + 1;
				m_iYearIndexEnd = m_iYearIndexStart + 4;
				break;
			case '2':
				m_chFieldOrder = 'y';
				m_iYearIndexStart = 0;
				m_iYearIndexEnd = 4;
				m_iMonthIndexStart = m_iYearIndexEnd + 1;
				m_iMonthIndexEnd = m_iMonthIndexStart + 2;
				m_iDayIndexStart = m_iMonthIndexEnd + 1;
				m_iDayIndexEnd = m_iDayIndexStart + 2;
				break;
			default:
				assert (0);
				break;
		}

		m_iDateLength = 10;
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_STIME, szData, 4);
		m_cTimeSeparator = *szData;

		const CString strDay (_T("(0[1-9]|[12]\\d|3[01])"));
		const CString strMonth (_T("(0[1-9]|1[0-2])"));
		const CString strYear (_T("\\d{4}"));
		const CString strYearTooltip (_T("YYYY"));
		const CString strMonthTooltip (_T("MM"));
		const CString strDayTooltip (_T("DD"));
		CString strEscTimeSeparator (m_cTimeSeparator);
		CString strEscDateSeparator (m_cDateSeparator);
		CString strDate;
		CString strTimeHHMM;
		CString strTimeHHMMSS;
		CString strFormat;

		EscapeString (strEscTimeSeparator);
		strTimeHHMM = _T("([01][0-9]|2[0-3])") + strEscTimeSeparator +
			_T("[0-5][0-9]");
		strTimeHHMMSS = _T("([01][0-9]|2[0-3])(") + strEscTimeSeparator +
			_T("[0-5][0-9]){2}");
		EscapeString (strEscDateSeparator);

		if (m_chFieldOrder == 'y')
		{
			strDate = strYear + strEscDateSeparator + strMonth +
				strEscDateSeparator + strDay;
			strFormat = strYearTooltip;
			strFormat += m_cDateSeparator;
			strFormat += strMonthTooltip;
			strFormat += m_cDateSeparator;
			strFormat += strDayTooltip;
		}
		else
		{
			if (m_chFieldOrder == 'd')
			{
				strDate = strDay + strEscDateSeparator + strMonth +
					strEscDateSeparator + strYear;
				strFormat += strDayTooltip;
				strFormat += m_cDateSeparator;
				strFormat += strMonthTooltip;
			}
			else
			{
				strDate = strMonth + strEscDateSeparator + strDay +
					strEscDateSeparator + strYear;
				strFormat += strMonthTooltip;
				strFormat += m_cDateSeparator;
				strFormat += strDayTooltip;
			}

			strFormat += m_cDateSeparator;
			strFormat += strYearTooltip;
		}

		m_DateRegEx.assign (strDate);
		m_TimeHHMMRegEx.assign (strTimeHHMM);
		m_TimeHHMMSSRegEx.assign (strTimeHHMMSS);
		m_DateTimeHHMMRegEx.assign (strDate + ' ' + strTimeHHMM);
		m_DateTimeHHMMSSRegEx.assign (strDate + ' ' + strTimeHHMMSS);
		m_strDateToolTip.Format (_T("Please enter a date in format %s"),
			strFormat);
		m_strTimeHHMMToolTip.Format (_T("Please enter a time in format HH:MM"),
			strFormat);
		m_strTimeHHMMSSToolTip.Format (_T("Please enter a time in format ")
			_T("HH:MM:SS"), strFormat);
		m_strDateTimeHHMMToolTip.Format (_T("Please enter a date and time in ")
			_T("format %s HH:MM"), strFormat);
		m_strDateTimeHHMMSSToolTip.Format (_T("Please enter a date and time ")
			_T("in format %s HH:MM:SS"), strFormat);
	}

	SetTimeIndexes ();
}

CDateTimeEdit::~CDateTimeEdit ()
{
}

void CDateTimeEdit::SetMode (const e_Mode eMode)
{
	// This always works now, regardless of the regex
	SetWindowText (_T(""));
	m_eMode = eMode;

	switch(m_eMode)
	{
	case eDate:
		SetRegEx (&m_DateRegEx);
		break;
	case eTimeHHMM:
		SetRegEx (&m_TimeHHMMRegEx);
		break;
	case eTimeHHMMSS:
		SetRegEx (&m_TimeHHMMSSRegEx);
		break;
	case eDateTimeHHMM:
		SetRegEx (&m_DateTimeHHMMRegEx);
		break;
	case eDateTimeHHMMSS:
		SetRegEx (&m_DateTimeHHMMSSRegEx);
		break;
	default:
		assert (0);
		break;
	}

	SetToolTipText ();
	SetTimeIndexes ();

	if (m_eMode == eTimeHHMM || m_eMode == eTimeHHMMSS)
	{
		m_ButtonCalendar.ShowWindow (FALSE);
		SetMargins (LOWORD (m_dwMargins), HIWORD (m_dwMargins));
	}
	else
	{
		CRect ClientRect;

		GetClientRect (ClientRect);
		SetMargins (LOWORD(m_dwMargins), HIWORD (m_dwMargins) +
			ClientRect.bottom - ClientRect.top);
		m_ButtonCalendar.ShowWindow (TRUE);
	}
}

CDateTimeEdit::e_Mode CDateTimeEdit::GetMode () const
{
	return m_eMode;
}

void CDateTimeEdit::SetDateTime (const COleDateTime &dt)
{
	if (dt.GetStatus () == COleDateTime::valid)
	{
		switch (m_eMode)
		{
		case eDate:
			SetDate (dt.GetYear (), dt.GetMonth (), dt.GetDay ());
			break;
		case eTimeHHMM:
		case eTimeHHMMSS:
			SetTime (dt.GetHour (), dt.GetMinute (), dt.GetSecond ());
			break;
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
			SetDateTime (dt.GetYear (), dt.GetMonth (), dt.GetDay (),
				dt.GetHour (), dt.GetMinute (), dt.GetSecond ());
			break;
		default:
			assert (0);
			break;
		}
	}
	else
	{
		// This always works now, regardless of the regex
		SetWindowText (_T(""));
	}
}

COleDateTime CDateTimeEdit::GetDateTime ()
{
	COleDateTime dt;

	if (GetWindowTextLength () == 0)
	{
		dt.SetStatus (COleDateTime::null);
	}
	else
	{
		bool bSuccess = IsInputValid (false);

		if (bSuccess)
		{
			switch (m_eMode)
			{
			case eDate:
				dt.SetDate (GetYear (), GetMonth (), GetDay ());
				break;
			case eTimeHHMM:
			case eTimeHHMMSS:
				dt.SetTime (GetHour (), GetMinute (), GetSecond ());
				break;
			case eDateTimeHHMM:
			case eDateTimeHHMMSS:
				dt.SetDateTime (GetYear (), GetMonth (), GetDay (), GetHour (),
					GetMinute (), GetSecond ());
				break;
			default:
				assert (0);
				break;
			}
		}
		else
		{
			dt.SetStatus (COleDateTime::invalid);
		}
	}

	return dt;
}

bool CDateTimeEdit::SetDateTime (const int iYear, const int iMonth,
	const int iDay, const int iHour, const int iMinute, const int iSecond)
{
	bool bSuccess = true;

	switch (m_eMode)
	{
	case eDate:
		bSuccess = SetDate (iYear, iMonth, iDay);
		break;
	case eTimeHHMM:
	case eTimeHHMMSS:
		bSuccess = SetTime (iHour, iMinute, iSecond);
		break;
	case eDateTimeHHMM:
	case eDateTimeHHMMSS:
	{
		CString strText;

		switch (m_chFieldOrder)
		{
			case 'd':
				strText.Format (_T("%02d%c%02d%c%04d %02d%c%02d%c%02d"),
					iDay, m_cDateSeparator, iMonth, m_cDateSeparator,
					iYear, iHour, m_cTimeSeparator, iMinute, m_cTimeSeparator,
					iSecond);
				bSuccess = !GetProcessChars () ||
					IsDayMonthYearValid (strText);
				break;
			case 'm':
				strText.Format (_T("%02d%c%02d%c%04d %02d%c%02d%c%02d"),
					iMonth, m_cDateSeparator, iDay, m_cDateSeparator, iYear,
					iHour, m_cTimeSeparator, iMinute, m_cTimeSeparator,
					iSecond);
				bSuccess = !GetProcessChars () ||
					IsMonthDayYearValid (strText);
				break;
			case 'y':
				strText.Format (_T("%04d%c%02d%c%02d %02d%c%02d%c%02d"),
					iYear, m_cDateSeparator, iMonth, m_cDateSeparator, iDay,
					iHour, m_cTimeSeparator, iMinute, m_cTimeSeparator,
					iSecond);
				bSuccess = !GetProcessChars () ||
					IsYearMonthDayValid (strText);
				break;
			default:
				assert (0);
				break;
		}

		if (bSuccess)
		{
			SetWindowText (m_eMode == eDateTimeHHMMSS ?
				strText : strText.Left(strText.GetLength () - 3));
		}

		break;
	}
	default:
		assert (0);
		break;
	}

	return bSuccess;
}

bool CDateTimeEdit::GetDateTime (int &iYear, int &iMonth, int &iDay,
	int &iHour, int &iMinute, int &iSecond)
{
	bool bSuccess = IsInputValid (false) && GetWindowTextLength ();

	if (bSuccess)
	{
		switch (m_eMode)
		{
		case eDate:
			iDay = GetDay ();
			iMonth = GetMonth ();
			iYear = GetYear ();
			iHour = -1;
			iMinute = -1;
			iSecond = -1;
			break;
		case eTimeHHMM:
		case eTimeHHMMSS:
			iDay = -1;
			iMonth = -1;
			iYear = -1;
			iHour = GetHour ();
			iMinute = GetMinute ();
			iSecond = m_eMode == eTimeHHMMSS ? GetSecond () : -1;
			break;
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
			iDay = GetDay ();
			iMonth = GetMonth ();
			iYear = GetYear ();
			iHour = GetHour ();
			iMinute = GetMinute ();
			iSecond = m_eMode == eDateTimeHHMMSS ? GetSecond () : -1;
			break;
		default:
			assert (0);
			break;
		}
	}

	return bSuccess;
}

bool CDateTimeEdit::SetDate (const int iYear, const int iMonth, const int iDay)
{
	bool bSuccess = m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS;

	if (bSuccess)
	{
		CString strDate;

		switch (m_chFieldOrder)
		{
			case 'd':
				strDate.Format (_T("%02d%c%02d%c%04d"), iDay,
					m_cDateSeparator, iMonth, m_cDateSeparator, iYear);
				bSuccess = !GetProcessChars () ||
					IsDayMonthYearValid (strDate);
				break;
			case 'm':
				strDate.Format (_T("%02d%c%02d%c%04d"), iMonth,
					m_cDateSeparator, iDay, m_cDateSeparator, iYear);
				bSuccess = !GetProcessChars () ||
					IsMonthDayYearValid (strDate);
				break;
			case 'y':
				strDate.Format (_T("%04d%c%02d%c%02d"), iYear,
					m_cDateSeparator, iMonth, m_cDateSeparator, iDay);
				bSuccess = !GetProcessChars () ||
					IsYearMonthDayValid (strDate);
				break;
			default:
				assert (0);
				break;
		}

		if (bSuccess)
		{
			if (m_eMode == eDateTimeHHMM)
			{
				SetWindowText (strDate + _T(" 00:00"));
			}
			else if (m_eMode == eDateTimeHHMMSS)
			{
				SetWindowText (strDate + _T(" 00:00:00"));
			}
			else
			{
				SetWindowText (strDate);
			}
		}
	}

	return bSuccess;
}

bool CDateTimeEdit::GetDate (int &iYear, int &iMonth, int &iDay)
{
	const bool bSuccess = m_eMode != eTimeHHMM &&
		m_eMode != eTimeHHMMSS && IsInputValid (false);

	if (bSuccess)
	{
		iDay = GetDay ();
		iMonth = GetMonth ();
		iYear = GetYear ();
	}

	return bSuccess;
}

bool CDateTimeEdit::SetTimeStamp (const SQL_TIMESTAMP_STRUCT *ts_)
{
	bool bSuccess = true;

	switch (m_eMode)
	{
	case eDate:
		bSuccess = SetDate (ts_->year, ts_->month, ts_->day);
		break;
	case eTimeHHMM:
	case eTimeHHMMSS:
		bSuccess = SetTime (ts_->hour, ts_->minute, ts_->second);
		break;
	case eDateTimeHHMM:
	case eDateTimeHHMMSS:
	{
		bSuccess = SetDateTime (ts_->year, ts_->month, ts_->day,
			ts_->hour, ts_->minute, ts_->second);
		break;
	}
	default:
		assert (0);
		break;
	}

	return bSuccess;
}

bool CDateTimeEdit::GetTimeStamp (SQL_TIMESTAMP_STRUCT *pTS)
{
	const bool bSuccess = IsInputValid (false);

	if (bSuccess)
	{
		int iDay = -1;
		int iMonth = -1;
		int iYear = -1;
		int iHour = -1;
		int iMinute = -1;
		int iSecond = -1;

		switch (m_eMode)
		{
		case eDate:
			GetDate (iYear, iMonth, iDay);
			break;
		case eTimeHHMM:
		case eTimeHHMMSS:
			GetTime (iHour, iMinute, iSecond);
			break;
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
			GetDate (iYear, iMonth, iDay);
			GetTime (iHour, iMinute, iSecond);
			break;
		default:
			assert (0);
			break;
		}

		if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
		{
			pTS->day = static_cast<SQLUSMALLINT>(iDay);
			pTS->month = static_cast<SQLUSMALLINT>(iMonth);
			pTS->year = static_cast<SQLSMALLINT>(iYear);
		}

		if (m_eMode != eDate)
		{
			pTS->hour = static_cast<SQLUSMALLINT>(iHour);
			pTS->minute = static_cast<SQLUSMALLINT>(iMinute);
			pTS->second = static_cast<SQLUSMALLINT>(iSecond);
		}
	}

	return bSuccess;
}

bool CDateTimeEdit::SetGregorian (const boost::gregorian::date &date_)
{
	bool bSuccess = true;

	if (date_.is_not_a_date ())
	{
		// This always works now, regardless of the regex
		SetWindowText (_T(""));
	}
	else
	{
		switch (m_eMode)
		{
		case eDate:
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
			bSuccess = SetDate (date_.year (), date_.month (), date_.day ());
			break;
		case eTimeHHMM:
		case eTimeHHMMSS:
			// Nothing to do
			assert (0);
			break;
		default:
			assert (0);
			break;
		}
	}

	return bSuccess;
}

boost::gregorian::date CDateTimeEdit::GetGregorian ()
{
	const bool bSuccess = IsInputValid (false);
	boost::gregorian::date date_;

	if (bSuccess && GetWindowTextLength ())
	{
		int iDay = -1;
		int iMonth = -1;
		int iYear = -1;

		switch (m_eMode)
		{
		case eDate:
		{
			GetDate (iYear, iMonth, iDay);
			date_ = boost::gregorian::date (LOWORD(iYear), LOWORD(iMonth),
				LOWORD(iDay));
			break;
		}
		case eTimeHHMM:
		case eTimeHHMMSS:
			// Nothing to do
			assert (0);
			break;
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
			// Can only store the date
			GetDate (iYear, iMonth, iDay);
			date_ = boost::gregorian::date (LOWORD(iYear), LOWORD(iMonth),
				LOWORD(iDay));
			break;
		default:
			assert (0);
			break;
		}
	}
	else
	{
		date_ = boost::gregorian::date (boost::date_time::not_a_date_time);
	}

	return date_;
}

bool CDateTimeEdit::SetPosixTime (const boost::posix_time::ptime &time_)
{
	bool bSuccess = true;

	if (time_.is_not_a_date_time ())
	{
		// This always works now, regardless of the regex
		SetWindowText (_T(""));
	}
	else
	{
		switch (m_eMode)
		{
		case eDate:
			bSuccess = SetGregorian (time_.date());
			break;
		case eTimeHHMM:
		case eTimeHHMMSS:
		{
			boost::posix_time::time_duration td = time_.time_of_day();

			bSuccess = SetTime (td.hours(), td.minutes(), td.seconds());
			break;
		}
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
		{
			boost::gregorian::date date_ = time_.date();
			boost::posix_time::time_duration td = time_.time_of_day();

			bSuccess = SetDateTime (date_.year (), date_.month (),
				date_.day (), td.hours (), td.minutes (), td.seconds ());
			break;
		}
		default:
			assert (0);
			break;
		}
	}

	return bSuccess;
}

boost::posix_time::ptime CDateTimeEdit::GetPosixTime ()
{
	const bool bSuccess = IsInputValid (false);
	boost::posix_time::ptime time_;

	if (bSuccess && GetWindowTextLength ())
	{
		switch (m_eMode)
		{
		case eDate:
		{
			boost::gregorian::date date_ = GetGregorian ();

			time_ = boost::posix_time::ptime (date_);
			break;
		}
		case eTimeHHMM:
		case eTimeHHMMSS:
		{
			boost::posix_time::ptime::time_duration_type td_ (GetHour (),
				GetMinute (), GetSecond ());

			time_ = boost::posix_time::ptime (boost::gregorian::date (), td_);
			break;
		}
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
		{
			boost::gregorian::date date_ = GetGregorian ();
			boost::posix_time::ptime::time_duration_type td_ (GetHour (),
				GetMinute (), GetSecond ());

			time_ = boost::posix_time::ptime (date_, td_);
			break;
		}
		default:
			assert (0);
			break;
		}
	}
	else
	{
		time_ = boost::posix_time::ptime (boost::date_time::not_a_date_time);
	}

	return time_;
}

int CDateTimeEdit::GetDay ()
{
	int iDay = -1;

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS && IsInputValid (false))
	{
		CString strDate;

		GetWindowText (strDate);
		iDay = GetDay (strDate);
	}

	return iDay;
}

int CDateTimeEdit::GetMonth ()
{
	int iMonth = -1;

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS && IsInputValid (false))
	{
		CString strDate;

		GetWindowText (strDate);
		iMonth = GetMonth (strDate);
	}

	return iMonth;
}

int CDateTimeEdit::GetYear ()
{
	int iYear = -1;

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS && IsInputValid (false))
	{
		CString strDate;

		GetWindowText (strDate);
		iYear = GetYear (strDate);
	}

	return iYear;
}

bool CDateTimeEdit::SetTime (const int iHour, const int iMinute, const int iSecond)
{
	bool bSuccess = m_eMode != eDate && iHour >= 0 && iHour <= 23 &&
		iMinute >= 0 && iMinute <= 59 && iSecond >= 0 && iSecond <= 59;

	if (m_eMode == eDateTimeHHMM || m_eMode == eDateTimeHHMMSS)
	{
		// Date must be followed by a space:
		bSuccess = !GetProcessChars () ||
			GetWindowTextLength () > m_iDateLength;
	}

	if (bSuccess)
	{
		CString strTime;

		strTime.Format (_T("%02d%c%02d%c%02d"), iHour,
			m_cTimeSeparator, iMinute, m_cTimeSeparator, iSecond);
		SetSel (m_iHourIndexStart, m_iSecondIndexEnd);
		ReplaceSel (m_eMode == eDateTimeHHMMSS ? strTime :
			strTime.Left (strTime.GetLength () - 3));
	}

	return bSuccess;
}

bool CDateTimeEdit::GetTime (int &iHour, int &iMinute, int &iSecond)
{
	bool bSuccess = m_eMode != eDate && IsInputValid (false);

	if (bSuccess)
	{
		iHour = GetHour ();
		iMinute = GetMinute ();
		iSecond = GetSecond ();
	}

	return bSuccess;
}

int CDateTimeEdit::GetHour ()
{
	int iHour = -1;

	if (m_eMode != eDate && IsInputValid (false))
	{
		CString strText;

		GetWindowText (strText);
		strText = strText.Mid (m_iHourIndexStart, 2);
		iHour = _tstoi (strText);
	}

	return iHour;
}

int CDateTimeEdit::GetMinute ()
{
	int iMinute = -1;

	if (m_eMode != eDate && IsInputValid (false))
	{
		CString strText;

		GetWindowText (strText);
		strText = strText.Mid (m_iMinuteIndexStart, 2);
		iMinute = _tstoi (strText);
	}

	return iMinute;
}

int CDateTimeEdit::GetSecond ()
{
	int iSecond = -1;

	if (m_eMode != eDate && IsInputValid (false))
	{
		CString strText;

		GetWindowText (strText);
		strText = strText.Mid (m_iSecondIndexStart, 2);
		iSecond = _tstoi (strText);
	}

	return iSecond;
}

void CDateTimeEdit::CreateToolTip (CWnd *pParent)
{
	switch (m_eMode)
	{
	case eDate:
		CBaseEdit::CreateToolTip (pParent, m_strDateToolTip);
		break;
	case eTimeHHMM:
		CBaseEdit::CreateToolTip (pParent, m_strTimeHHMMToolTip);
		break;
	case eTimeHHMMSS:
		CBaseEdit::CreateToolTip (pParent, m_strTimeHHMMSSToolTip);
		break;
	case eDateTimeHHMM:
		CBaseEdit::CreateToolTip (pParent, m_strDateTimeHHMMToolTip);
		break;
	case eDateTimeHHMMSS:
		CBaseEdit::CreateToolTip (pParent, m_strDateTimeHHMMSSToolTip);
		break;
	default:
		assert (0);
		break;
	}
}

// TODO: Review function
void CDateTimeEdit::Increment (const int iInc)
{
	const int iLen = GetWindowTextLength ();
	int iSelStart = 0;
	int iSelEnd = 0;

	// Note GetSel over-ridden
	GetSel (iSelStart, iSelEnd);

	int iStart = 0;
	int iEnd = 0;
	e_Part ePart = LocatePart (iSelStart, iStart, iEnd);

	if (iLen < iEnd)
	{
		MoveRight ();
	}
	else
	{
		CString strText;
		int i = 0;
		CString strPart;
		bool bProcess = true;

		GetWindowText (strText);
		i = _tstoi (strText.Mid (iStart, iEnd - iStart));
		i += iInc > 0 ? 1 : -1;

		if (ePart > eYear)
		{
			if (i < 0)
			{
				switch (ePart)
				{
				case eHour:
					i = 23;
					break;
				case eMinute:
				case eSecond:
					i = 59;
					break;
				default:
					assert (0);
					break;
				}
			}
			else
			{
				switch (ePart)
				{
				case eHour:
					if (i > 23) i = 0;
					break;
				case eMinute:
				case eSecond:
					if (i > 59) i = 0;
					break;
				default:
					assert (0);
					break;
				}
			}

			strPart.Format (_T("%02d"), i);
		}
		else
		{
			if (i < 1)
			{
				switch (ePart)
				{
				case eDay:
					i = MaxDay (GetMonth (strText), GetYear (strText));
					break;
				case eMonth:
					// December has 31 days, so no need to check day.
					i = 12;
					break;
				case eYear:
					// Handled in else below.
					break;
				default:
					assert (0);
					break;
				}
			}
			else
			{
				switch (ePart)
				{
				case eDay:
					// Handled below
					break;
				case eMonth:
				{
					const int iDay = GetDay (strText);

					// Select a valid month, wrapping around if necessary.
					while (!ValidateDayMonth (iDay, i))
					{
						i += iInc;

						if (i == 0) i = 12;
						else if (i == 13) i = 1;
					}

					// Check for leap year.
					if (!ValidateLeapYear (iDay, i, GetYear (strText)))
					{
						i += iInc;
					}

					break;
				}
				case eYear:
					// Check for leap year.
					if (GetDay (strText) == 29 && GetMonth (strText) == 2)
					{
						while (!ValidateLeapYear (29, 2, i))
						{
							i += iInc;

							// Check for under/overflow.
							if (i < 1753) i = 9996;
							else if (i > 9999) i = 1756;
						}
					}
					else
					{
						if (i < 1753)
						{
							i = 9999;
						}
						else if (i > 9999)
						{
							i = 1753;
						}
					}

					break;
				}
			}

			if (ePart == eYear)
			{
				strPart.Format (_T("%04d"), i);
			}
			else
			{
				strPart.Format (_T("%02d"), i);
			}

			strText.Delete (iStart, iEnd - iStart);
			strText.Insert (iStart, strPart);
			bProcess = IsDateValid (strText);

			if (!bProcess && ePart != eYear)
			{
				strPart = _T("01");
			}
		}

		// Needed when up arrow pressed with nothing selected.
		SetSel (iStart, iEnd);
		ReplaceSel (strPart, TRUE);
	}

	SetSel (iStart, iEnd);
	m_bFromSpin = true;
}

void CDateTimeEdit::GetSel (int &nStartChar, int &nEndChar) const
{
	CEdit::GetSel (nStartChar, nEndChar);

	if (nEndChar < nStartChar)
	{
		std::swap (nStartChar, nEndChar);
	}
}

const CButton *CDateTimeEdit::GetCalendarButton () const
{
	return &m_ButtonCalendar;
}

void CDateTimeEdit::SetMin(const COleDateTime &Min)
{
	m_Min = Min;
}

void CDateTimeEdit::SetMax(const COleDateTime &Max)
{
	m_Max = Max;
}

bool CDateTimeEdit::SyntaxCheck (const CString &strText)
{
	bool bSuccess = true;
	CString strTemp (strText);
	bool bChanged = (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS) ?
		ExpandYear (strTemp) : false;

	if (m_eMode != eDate)
	{
		bChanged |= FormatTime (strTemp);
	}

	if (bChanged)
	{
		const bool bProcessChars = GetProcessChars ();

		SetProcessChars (false);
		SetWindowText (strTemp);
		SetProcessChars (bProcessChars);
	}

	bSuccess = CBaseEdit::SyntaxCheck (strTemp);

	if (!bSuccess)
	{
		SetToolTipText ();
	}

	return bSuccess;
}

bool CDateTimeEdit::SemanticCheck (const CString &strText,
	CString *pstrErrorMsg/* = 0*/)
{
	bool bOK = true;

	if (!(m_eMode == eTimeHHMM || m_eMode == eTimeHHMMSS))
	{
		bOK = IsDateValid (strText, pstrErrorMsg);

		// Further checking if Date is COMPLETE.
		if (bOK && (m_eMode == eDate && strText.GetLength () == 10 ||
			m_eMode == eDateTimeHHMM && strText.GetLength () == 16 ||
			m_eMode == eDateTimeHHMM && strText.GetLength () == 19))
		{
			if (m_Min.GetStatus () != COleDateTime::null)
			{
				COleDateTime Date;

				Date.ParseDateTime(strText);
				bOK = Date >= m_Min;

				if (!bOK)
				{
					CString strError = "Minimum Date allowed is ";

					switch (m_eMode)
					{
					case eDate:
						strError += m_Min.Format(VAR_DATEVALUEONLY);
						break;
					case eDateTimeHHMM:
						strError += m_Min.Format().Left(16);
						break;
					case eDateTimeHHMMSS:
						strError += m_Min.Format();
						break;
					}

					if (pstrErrorMsg)
					{
						*pstrErrorMsg = strError;
					}
					else if (GetToolTipCreated())
					{
						CBaseEdit::SetToolTipText (strError);
					}
				}
			}

			if (bOK && m_Max.GetStatus () != COleDateTime::null)
			{
				COleDateTime Date;

				Date.ParseDateTime(strText);
				bOK = Date <= m_Max;

				if (!bOK)
				{
					CString strError = "Maximum Date allowed is ";

					switch (m_eMode)
					{
					case eDate:
						strError += m_Max.Format(VAR_DATEVALUEONLY);
						break;
					case eDateTimeHHMM:
						strError += m_Max.Format().Left(16);
						break;
					case eDateTimeHHMMSS:
						strError += m_Max.Format();
						break;
					}

					if (pstrErrorMsg)
					{
						*pstrErrorMsg = strError;
					}
					else if (GetToolTipCreated())
					{
						CBaseEdit::SetToolTipText (strError);
					}
				}
			}
		}
	}

	return bOK;
}

void CDateTimeEdit::FormatDateTime ()
{
	CString strText;
	bool bFormatted = false;

	GetWindowText (strText);

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
	{
		bFormatted = FormatDate (strText);
	}

	if (m_eMode != eDate)
	{
		bFormatted |= FormatTime (strText);
	}

	if (bFormatted)
	{
		const bool bProcessChars = GetProcessChars ();

		SetProcessChars (false);
		SetWindowText (strText);
		SetProcessChars (bProcessChars);
	}
}

bool CDateTimeEdit::FormatDate (CString &strDate)
{
	bool bFormatted = false;

	bFormatted = FormatDay (strDate);
	bFormatted |= FormatMonth (strDate);
	bFormatted |= FormatYear (strDate);
	return bFormatted;
}

bool CDateTimeEdit::FormatDay (CString &strText)
{
	bool bFormatted = false;

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
	{
		if (strText.GetLength () >= m_iDayIndexEnd)
		{
			const TCHAR ch = strText[m_iDayIndexEnd - 1];

			if (ch < '0' || ch > '9')
			{
				if (strText[m_iDayIndexStart] == '0')
				{
					strText.SetAt (m_iDayIndexStart, '1');
				}

				strText.Insert (m_iDayIndexStart, '0');
				bFormatted = true;
			}
		}

		if (m_chFieldOrder != 'y')
		{
			if (strText.GetLength () == m_iDayIndexEnd)
			{
				strText += m_cDateSeparator;
				bFormatted = true;
			}
			else if (strText.GetLength () >= m_iDayIndexEnd &&
				strText[m_iDayIndexEnd] != m_cDateSeparator)
			{
				strText.Insert (m_iDayIndexEnd, m_cDateSeparator);
				bFormatted = true;
			}
		}
	}

	return bFormatted;
}

bool CDateTimeEdit::FormatMonth (CString &strText)
{
	bool bFormatted = false;

	if (strText.GetLength () >= m_iMonthIndexEnd)
	{
		const TCHAR ch = strText[m_iMonthIndexEnd - 1];

		if (ch < '0' || ch > '9')
		{
			if (strText[m_iMonthIndexStart] == '0')
			{
				strText.SetAt (m_iMonthIndexStart, '1');
			}

			strText.Insert (m_iMonthIndexStart, '0');
			bFormatted = true;
		}

		if (m_chFieldOrder != 'y')
		{
			if (strText.GetLength () == m_iMonthIndexEnd)
			{
				strText += m_cDateSeparator;
				bFormatted = true;
			}
			else if (strText[m_iMonthIndexEnd] != m_cDateSeparator)
			{
				strText.Insert (m_iMonthIndexEnd, m_cDateSeparator);
				bFormatted = true;
			}
		}
	}

	return bFormatted;
}

bool CDateTimeEdit::FormatYear (CString &strText)
{
	bool bFormatted = false;

	if (strText.GetLength () >= m_iYearIndexEnd)
	{
		TCHAR ch = strText[m_iYearIndexStart + 1];

		if (ch < '0' || ch > '9')
		{
			strText.Insert (m_iYearIndexStart, '0');
			bFormatted = true;
		}

		// Allow previous if to run to create two digits.
		ch = strText[m_iYearIndexStart + 2];

		if (ch < '0' || ch > '9')
		{
			const DWORD dwYear = _tstoi (strText.Left (2));
			DWORD dwCenturyPrefix = m_dwCenturyPrefix;
			CString strPrefix;

			if (dwYear > m_dwTwoDigitYearMax)
			{
				dwCenturyPrefix--;
			}

			strPrefix.Format (_T("%d"), dwCenturyPrefix);
			strText.Insert (m_iYearIndexStart, strPrefix);
			bFormatted = true;
		}

		ch = strText[m_iYearIndexStart + 3];

		if (ch < '0' || ch > '9')
		{
			strText.Insert (m_iYearIndexStart, static_cast<TCHAR>
				(m_dwCenturyPrefix / 10) + '0');

			if (_tstoi (strText.Mid (m_iYearIndexStart, 4)) < 1752)
			{
				strText.Delete (m_iYearIndexStart, 4);
				strText.Insert (m_iYearIndexStart, _T("1753"));
			}

			bFormatted = true;
		}
	}

	if ((m_eMode == eDateTimeHHMM || m_eMode == eDateTimeHHMMSS) &&
		strText.GetLength () == m_iDateLength)
	{
		strText += ' ';
		bFormatted = true;
	}

	return bFormatted;
}

bool CDateTimeEdit::FormatTime (CString &strText)
{
	bool bFormatted = false;
	int iFirstIndex = strText.Find (m_cTimeSeparator);
	int iSecondIndex = -1;

	if (iFirstIndex > 0)
	{
		if (iFirstIndex < m_iHourIndexEnd)
		{
			strText.Insert (m_iHourIndexStart, '0');
			iFirstIndex++;
			bFormatted = true;
		}

		iSecondIndex = strText.Find (m_cTimeSeparator, iFirstIndex + 1);

		if (iSecondIndex > 0)
		{
			if (iSecondIndex < m_iMinuteIndexEnd)
			{
				strText.Insert (m_iMinuteIndexStart, '0');
				bFormatted = true;
			}
		}
	}

	if ((m_eMode == eDateTimeHHMM || m_eMode == eDateTimeHHMMSS) &&
		strText.GetLength () == m_iDateLength)
	{
		strText += ' ';
		bFormatted = true;
	}
	else if (strText.GetLength () == m_iHourIndexEnd ||
		(m_eMode == eTimeHHMMSS && strText.GetLength () == m_iMinuteIndexEnd))
	{
		strText += m_cTimeSeparator;
		bFormatted = true;
	}

	return bFormatted;
}

bool CDateTimeEdit::IsDateValid (const CString &strText,
	CString *pstrErrorMsg/* = 0*/)
{
	bool bValid = true;

	switch (m_chFieldOrder)
	{
		case 'd':
			bValid = IsDayMonthYearValid (strText, pstrErrorMsg);
			break;
		case 'm':
			bValid = IsMonthDayYearValid (strText, pstrErrorMsg);
			break;
		case 'y':
			bValid = IsYearMonthDayValid (strText, pstrErrorMsg);
			break;
		default:
			assert (0);
			bValid = false;
			break;
	}

	return bValid;
}

bool CDateTimeEdit::IsDayMonthYearValid (const CString &strDate,
	CString *pstrErrorMsg/* = 0*/)
{
	bool bValid = true;
	const int iLen = strDate.GetLength ();
	int iDay = 0;
	int iMonth = 0;
	int iYear = 0;

	if (iLen >= 1)
	{
		if (iLen >= 2)
		{
			iDay = _tstoi (strDate.Left (2));
		}
		else
		{
			iDay = _tstoi (strDate);
		}

		// Day only test
		bValid = iLen == 1 || (iDay >= 1 && iDay <= 31);

		if (!bValid)
		{
			if (pstrErrorMsg)
				*pstrErrorMsg = _T("Day must be 1-31");
		}
		else if (iLen > m_iMonthIndexStart)
		{
			if (iLen >= m_iMonthIndexEnd)
			{
				iMonth = _tstoi (strDate.Mid (m_iMonthIndexStart, 2));
			}
			else
			{
				iMonth = _tstoi (strDate.Mid (m_iMonthIndexStart));
			}

			// Month only test
			bValid = iLen == m_iMonthIndexEnd - 1 || (iMonth >= 1 && iMonth <= 12);

			if (bValid)
			{
				// Day and Month test
				bValid = ValidateDayMonth (iDay, iMonth);

				if (bValid)
				{
					if (iLen >= m_iYearIndexEnd)
					{
						iYear = _tstoi (strDate.Mid (m_iYearIndexStart, 4));
						bValid = ValidateLeapYear (iDay, iMonth, iYear);

						if (bValid)
						{
							bValid = iYear > 1752;

							if (!bValid && pstrErrorMsg)
								*pstrErrorMsg = _T("Years < 1753 not supported.");
						}
						else if (pstrErrorMsg)
							*pstrErrorMsg = _T("Invalid Leap Year");
					}
				}
				else
				{
					if (pstrErrorMsg)
						*pstrErrorMsg = _T("Invalid Day/Month Combination");
				}
			}
			else
			{
				if (pstrErrorMsg)
					*pstrErrorMsg = _T("Month must be 1-12");
			}
		}
	}

	return bValid;
}

bool CDateTimeEdit::IsMonthDayYearValid (const CString &strDate,
	CString *pstrErrorMsg/* = 0*/)
{
	bool bValid = true;
	const int iLen = strDate.GetLength ();
	int iDay = 0;
	int iMonth = 0;
	int iYear = 0;

	if (iLen >= 1)
	{
		if (iLen >= 2)
		{
			iMonth = _tstoi (strDate.Left (2));
		}
		else
		{
			iMonth = _tstoi (strDate);
		}

		// Month only test
		bValid = iLen == 1 || (iMonth >= 1 && iMonth <= 12);

		if (!bValid)
		{
			if (pstrErrorMsg)
				*pstrErrorMsg = _T("Month must be 1-12");
		}
		else if (iLen > m_iDayIndexStart)
		{
			if (iLen >= m_iDayIndexEnd)
			{
				iDay = _tstoi (strDate.Mid (m_iDayIndexStart, 2));
			}
			else
			{
				iDay = _tstoi (strDate.Mid (m_iDayIndexStart));
			}

			// Day only test
			bValid = iLen == m_iDayIndexEnd - 1 || (iDay >= 1 && iDay <= 31);

			if (bValid)
			{
				// Day and Month test
				bValid = ValidateDayMonth (iDay, iMonth);

				if (bValid)
				{
					if (iLen >= m_iYearIndexEnd)
					{
						iYear = _tstoi (strDate.Mid (m_iYearIndexStart, 4));
						bValid = ValidateLeapYear (iDay, iMonth, iYear);

						if (bValid)
						{
							bValid = iYear > 1752;

							if (!bValid && pstrErrorMsg)
								*pstrErrorMsg = _T("Years < 1753 not supported.");
						}
						else if (pstrErrorMsg)
							*pstrErrorMsg = _T("Invalid Leap Year");
					}
				}
				else
				{
					if (pstrErrorMsg)
						*pstrErrorMsg = _T("Invalid Day/Month Combination");
				}
			}
			else
			{
				if (pstrErrorMsg)
					*pstrErrorMsg = _T("Day must be 1-31");
			}
		}
	}

	return bValid;
}

bool CDateTimeEdit::IsYearMonthDayValid (const CString &strDate,
	CString *pstrErrorMsg/* = 0*/)
{
	bool bValid = true;
	const int iLen = strDate.GetLength ();
	int iDay = 0;
	int iMonth = 0;
	int iYear = 0;

	if (iLen >= 4)
	{
		iYear = _tstoi (strDate.Left (4));

		if (iLen > m_iMonthIndexStart)
		{
			if (iLen >= m_iMonthIndexEnd)
			{
				iMonth = _tstoi (strDate.Mid (m_iMonthIndexStart, 2));
			}
			else
			{
				iMonth = _tstoi (strDate.Mid (m_iMonthIndexStart));
			}

			// Month only test
			bValid = iLen == m_iMonthIndexEnd - 1 || (iMonth >= 1 && iMonth <= 12);

			if (!bValid)
			{
				if (pstrErrorMsg)
					*pstrErrorMsg = _T("Month must be 1-12");
			}
			else if (iLen > m_iDayIndexStart)
			{
				if (iLen < m_iDayIndexEnd)
				{
					iDay = _tstoi (strDate.Right (1));
				}
				else
				{
					iDay = _tstoi (strDate.Mid (m_iDayIndexStart, 2));
				}

				// Day only test
				bValid = iLen == m_iDayIndexEnd - 1 || (iDay >= 1 && iDay <= 31);

				if (bValid)
				{
					// Day and Month test
					bValid = ValidateDayMonth (iDay, iMonth);

					if (bValid)
					{
						bValid = ValidateLeapYear (iDay, iMonth, iYear);

						if (bValid)
						{
							bValid = iYear > 1752;

							if (!bValid && pstrErrorMsg)
								*pstrErrorMsg = _T("Years < 1753 not supported.");
						}
						else if (pstrErrorMsg)
							*pstrErrorMsg = _T("Invalid Leap Year");
					}
					else
					{
						if (pstrErrorMsg)
							*pstrErrorMsg = _T("Invalid Day/Month Combination");
					}
				}
				else
				{
					if (pstrErrorMsg)
						*pstrErrorMsg = _T("Day must be 1-31");
				}
			}
		}
	}

	return bValid;
}

// TODO: Review function.
void CDateTimeEdit::MoveLeft ()
{
	int iSelStart = 0;
	int iSelEnd = 0;

	// Note GetSel over-ridden
	GetSel (iSelStart, iSelEnd);
	FormatDateTime ();

	int iStart = 0;
	int iEnd = 0;
	// Calc which part we're in now.
	e_Part ePart = LocatePart (iSelStart, iStart, iEnd);

	if (iSelStart != iSelEnd || iEnd > GetWindowTextLength ())
	{
		const int iOffset = 1;
		const int iSpace = (m_eMode == eDateTimeHHMM ||
			m_eMode == eDateTimeHHMMSS) && ePart == eHour ? 1 : 0;

		iSelStart = iStart - iOffset - iSpace;
		SetSel (iSelStart, iSelStart);
		// Calc where we're going next.
		ePart = LocatePart (iSelStart, iStart, iEnd);
	}

	SetSel (iStart, iEnd);
}

// TODO: Review function
void CDateTimeEdit::MoveRight ()
{
	CString strText;
	bool bFormatted = false;
	bool bSelectEnd = false;

	GetWindowText (strText);

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
	{
		TCHAR ch = strText.GetLength () ? strText[strText.GetLength () - 1] : 0;

		bFormatted = FormatDate (strText);
		bSelectEnd = strText.Right (1) != ch;

		if (ExpandYear (strText))
		{
			bFormatted |= FormatDate (strText);
		}
	}

	if (m_eMode != eDate)
	{
		TCHAR ch = strText.GetLength () ? strText[strText.GetLength () - 1] : 0;

		bFormatted |= FormatTime (strText);
		bSelectEnd |= strText.Right (1) != ch;
	}

	const int iLen = strText.GetLength ();
	int iSelStart = 0;
	int iSelEnd = 0;

	if (bFormatted && bSelectEnd)
	{
		iSelStart = iLen;
	}
	else
	{
		// Note GetSel over-ridden
		GetSel (iSelStart, iSelEnd);
	}

	int iStart = 0;
	int iEnd = 0;
	e_Part ePart = LocatePart (iSelStart, iStart, iEnd);

	if (m_eMode == eTimeHHMM || m_eMode == eTimeHHMMSS)
	{
		if (iLen == iStart)
		{
			COleDateTime dt = COleDateTime::GetCurrentTime ();
			CString strPart;

			switch (ePart)
			{
			case eHour:
				strPart.Format (_T("%02d"), dt.GetHour ());
				break;
			case eMinute:
				strPart.Format (_T("%02d"), dt.GetMinute ());
				break;
			case eSecond:
				strPart.Format (_T("%02d"), dt.GetSecond ());
				break;
			default:
				assert (0);
				break;
			}

			strText += strPart;
		}
		else
		{
			int iCurrStart = 0;
			int iCurrEnd = 0;

			// Note GetSel over-ridden
			GetSel (iCurrStart, iCurrEnd);

			if (iCurrStart != iCurrEnd)
			{
				const int iOffset = 1;
				const int iSelStart = iEnd + iOffset;

				SetSel (iSelStart, iSelStart);
				ePart = LocatePart (iSelStart, iStart, iEnd);
			}

			SetSel (iStart, iEnd);
		}
	}
	else
	{
		if (iLen == iStart)
		{
			COleDateTime dt = COleDateTime::GetCurrentTime ();
			CString strPart;

			switch (ePart)
			{
			case eDay:
				strPart.Format (_T("%02d"), dt.GetDay ());
				break;
			case eMonth:
				strPart.Format (_T("%02d"), dt.GetMonth ());
				break;
			case eYear:
				strPart.Format (_T("%04d"), dt.GetYear ());
				break;
			case eHour:
				strPart.Format (_T("%02d"), dt.GetHour ());
				break;
			case eMinute:
				strPart.Format (_T("%02d"), dt.GetMinute ());
				break;
			case eSecond:
				strPart.Format (_T("%02d"), dt.GetSecond ());
				break;
			default:
				assert (0);
				break;
			}

			strText += strPart;
		}
		else
		{
			if (iStart != iEnd)
			{
				const int iSelStart = iEnd + 1;

				SetSel (iSelStart, iSelStart);
				ePart = LocatePart (iSelStart, iStart, iEnd);
			}

			if (iLen >= iEnd)
			{
				SetSel (iStart, iEnd);
			}
			else
			{
				SetSel (iEnd, iEnd);
			}
		}
	}

	bool bProcess = true;

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
	{
		bProcess = IsDateValid (strText);

		if (!bProcess && ePart < eHour)
		{
			CString strPart;
			int i = 0;

			do
			{
				strPart = (strText.Mid (iStart, iEnd - iStart));
				i = _tstoi (strPart);

				switch (ePart)
				{
				case eDay:
				case eMonth:
					--i;
					strPart.Format(_T("%02d"), i);
					break;
				case eYear:
					--i;
					strPart.Format(_T("%04d"), i);
					break;
				default:
					assert (0);
					break;
				}

				strText.Delete (iStart, iEnd - iStart);
				strText.Insert (iStart, strPart);
				bProcess = IsDateValid (strText);
			} while (!bProcess);
		}
	}

	if (bProcess)
	{
		const bool bProcessChars = GetProcessChars ();

		SetProcessChars (false);
		SetWindowText (strText);
		SetProcessChars (bProcessChars);

		if (bSelectEnd)
			SetSel (strText.GetLength (), strText.GetLength ());
		else
			SetSel (iStart, iEnd);
	}
}

void CDateTimeEdit::SetToolTipText ()
{
	if (GetToolTipCreated())
	{
		switch(m_eMode)
		{
		case eDate:
			CBaseEdit::SetToolTipText (m_strDateToolTip);
			break;
		case eTimeHHMM:
			CBaseEdit::SetToolTipText (m_strTimeHHMMToolTip);
			break;
		case eTimeHHMMSS:
			CBaseEdit::SetToolTipText (m_strTimeHHMMSSToolTip);
			break;
		case eDateTimeHHMM:
			CBaseEdit::SetToolTipText (m_strDateTimeHHMMToolTip);
			break;
		case eDateTimeHHMMSS:
			CBaseEdit::SetToolTipText (m_strDateTimeHHMMSSToolTip);
			break;
		default:
			assert (0);
			break;
		}
	}
}

void CDateTimeEdit::SetTimeIndexes ()
{
	switch (m_eMode)
	{
	case eDate:
		m_iHourIndexStart = -1;
		m_iHourIndexEnd = -1;
		m_iMinuteIndexStart = -1;
		m_iMinuteIndexEnd = -1;
		m_iSecondIndexStart = -1;
		m_iSecondIndexEnd = -1;
		break;
	case eTimeHHMM:
	case eTimeHHMMSS:
		m_iHourIndexStart = 0;
		m_iHourIndexEnd = 2;
		m_iMinuteIndexStart = m_iHourIndexEnd + 1;
		m_iMinuteIndexEnd = m_iMinuteIndexStart + 2;
		m_iSecondIndexStart = m_eMode == eTimeHHMMSS ?
			m_iMinuteIndexEnd + 1 : -1;
		m_iSecondIndexEnd = m_eMode == eTimeHHMMSS ?
			m_iSecondIndexStart + 2 : -1;
		break;
	case eDateTimeHHMM:
	case eDateTimeHHMMSS:
		m_iHourIndexStart = m_iDateLength + 1;
		m_iHourIndexEnd = m_iHourIndexStart + 2;
		m_iMinuteIndexStart = m_iHourIndexEnd + 1;
		m_iMinuteIndexEnd = m_iMinuteIndexStart + 2;
		m_iSecondIndexStart = m_eMode == eDateTimeHHMMSS ?
			m_iMinuteIndexEnd + 1 : -1;
		m_iSecondIndexEnd = m_eMode == eDateTimeHHMMSS ?
			m_iSecondIndexStart + 2 : -1;
		break;
	default:
		assert (0);
		break;
	}
}

bool CDateTimeEdit::ValidateDayMonth (const int iDay, const int iMonth)
{
	const int iMaxDay = MaxDay (iMonth, -1);

	return iDay <= iMaxDay;
}

bool CDateTimeEdit::ValidateLeapYear (const int iDay, const int iMonth,
	const int iYear)
{
	bool bValid = true;

	// Day, Month and Year validation
	if (iDay == 29 && iMonth == 2)
	{
		if (iYear > 1752)
		{
			// Leap year calculation taken from K&R "The C Programming Language"
			bValid = iYear % 4 == 0 && iYear % 100 != 0 || iYear % 400 == 0;
		}
		else
		{
			bValid = false;
		}
	}

	return bValid;
}

bool CDateTimeEdit::ExpandYear (CString &strDate)
{
	bool bExpanded = false;
	CString strText (strDate);

	// Take care of case where format is DDMMYYYY or MMDDYYYY
	// and only two digits have been entered when tabbing out
	// of the control.
	if (m_chFieldOrder != 'y' && strText.GetLength () == m_iDateLength - 2)
	{
		const DWORD dwYear = _tstoi (strText.Mid (m_iYearIndexStart, 2));
		DWORD dwCenturyPrefix = m_dwCenturyPrefix;
		CString strPrefix;

		if (dwYear > m_dwTwoDigitYearMax)
		{
			dwCenturyPrefix--;
		}

		strPrefix.Format (_T("%02d"), dwCenturyPrefix);
		strText.Insert (m_iYearIndexStart, strPrefix);

		// In case a leap year check is needed...
		if (m_chFieldOrder == 'd' && IsDayMonthYearValid (strText) ||
			m_chFieldOrder == 'm' && IsMonthDayYearValid (strText))
		{
			strDate = strText;
			bExpanded = true;
		}
	}

	return bExpanded;
}

CDateTimeEdit::e_Part CDateTimeEdit::LocatePart (const int iSelStart, int &iStart, int &iEnd) const
{
	e_Part ePart = eDay;

	switch (m_eMode)
	{
	case eDate:
	{
		ePart = LocateDate (iSelStart, iStart, iEnd);
		break;
	}
	case eTimeHHMM:
	case eTimeHHMMSS:
	{
		ePart = LocateTime (iSelStart, iStart, iEnd);
		break;
	}
	case eDateTimeHHMM:
	case eDateTimeHHMMSS:
	{
		if (iSelStart <= m_iDateLength)
		{
			ePart = LocateDate (iSelStart, iStart, iEnd);
		}
		else
		{
			ePart = LocateTime (iSelStart, iStart, iEnd);
		}

		break;
	}
	default:
		assert (0);
		break;
	}

	return ePart;
}

CDateTimeEdit::e_Part CDateTimeEdit::LocateDate (const int iSelStart,
	int &iStart, int &iEnd) const
{
	e_Part ePart = eDay;

	if (iSelStart >= m_iDayIndexStart && iSelStart <= m_iDayIndexEnd)
	{
		iStart = m_iDayIndexStart;
		iEnd = m_iDayIndexEnd;
	}
	else if (iSelStart >= m_iMonthIndexStart && iSelStart <= m_iMonthIndexEnd)
	{
		ePart = eMonth;
		iStart = m_iMonthIndexStart;
		iEnd = m_iMonthIndexEnd;
	}
	else if (iSelStart >= m_iYearIndexStart && iSelStart <= m_iYearIndexEnd)
	{
		ePart = eYear;
		iStart = m_iYearIndexStart;
		iEnd = m_iYearIndexEnd;
	}

	return ePart;
}

CDateTimeEdit::e_Part CDateTimeEdit::LocateTime (const int iSelStart, int &iStart, int &iEnd) const
{
	e_Part ePart = eHour;

	if (iSelStart >= m_iHourIndexStart && iSelStart <= m_iHourIndexEnd)
	{
		iStart = m_iHourIndexStart;
		iEnd = m_iHourIndexEnd;
	}
	else if (iSelStart >= m_iMinuteIndexStart && iSelStart <= m_iMinuteIndexEnd)
	{
		ePart = eMinute;
		iStart = m_iMinuteIndexStart;
		iEnd = m_iMinuteIndexEnd;
	}
	else if (iSelStart >= m_iSecondIndexStart && iSelStart <= m_iSecondIndexEnd)
	{
		ePart = eSecond;
		iStart = m_iSecondIndexStart;
		iEnd = m_iSecondIndexEnd;
	}

	return ePart;
}

int CDateTimeEdit::GetDay (const CString &strDate) const
{
	int iDay = -1;

	if (strDate.GetLength () >= m_iDayIndexEnd)
	{
		iDay = _tstoi (strDate.Mid (m_iDayIndexStart, 2));
	}

	return iDay;
}

int CDateTimeEdit::GetMonth (const CString &strDate) const
{
	int iMonth = -1;

	if (strDate.GetLength () >= m_iMonthIndexEnd)
	{
		iMonth = _tstoi (strDate.Mid (m_iMonthIndexStart, 2));
	}

	return iMonth;
}

int CDateTimeEdit::GetYear (const CString &strDate) const
{
	int iYear = -1;

	if (strDate.GetLength () >= m_iYearIndexEnd)
	{
		iYear = _tstoi (strDate.Mid (m_iYearIndexStart, 4));
	}

	return iYear;
}

int CDateTimeEdit::MaxDay (const int iMonth, const int iYear)
{
	int iDay = 31;

	if (iMonth > -1)
	{
		if (iMonth == 2)
		{
			iDay = 29;
		}
		else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11)
		{
			iDay = 30;
		}
		
		if (iYear > -1 && iMonth == 2)
		{
			if (!ValidateLeapYear (29, 2, iYear))
			{
				iDay = 28;
			}
		}
	}

	return iDay;
}

BEGIN_MESSAGE_MAP(CDateTimeEdit, CBaseEdit)
	//{{AFX_MSG_MAP(CDateTimeEdit)
	ON_MESSAGE(WM_CREATE_CAL_BUTTON, OnCreateCalButton)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT_EX(EN_KILLFOCUS, OnKillFocusEx)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(123, OnCalendar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDateTimeEdit::PreSubclassWindow ()
{
	// Delay button creation, or all hell breaks loose.
	PostMessage (WM_CREATE_CAL_BUTTON);
}

LRESULT CDateTimeEdit::WindowProc (UINT message, WPARAM wParam, LPARAM lParam)
{
	const LRESULT lRes = m_bFromSpin && message == EM_SETSEL ? 0 :
		CBaseEdit::WindowProc (message, wParam, lParam);

	switch (message)
	{
	case WM_ENABLE:
		if (::IsWindow(m_ButtonCalendar.m_hWnd))
		{
			m_ButtonCalendar.EnableWindow (static_cast<BOOL>(wParam));
		}

		break;
	case EM_SETSEL:
		m_bFromSpin = false;

		if (::IsWindow(m_ButtonCalendar.m_hWnd))
		{
			m_ButtonCalendar.Invalidate ();
		}

		break;
	case EM_SETREADONLY:
		if (::IsWindow(m_ButtonCalendar.m_hWnd))
		{
			m_ButtonCalendar.EnableWindow (!wParam);
		}

		break;
	default:
		break;
	}

	return lRes;
}

LRESULT CDateTimeEdit::OnCreateCalButton (WPARAM, LPARAM)
{
	CRect ClientRect;
	CRect ButtonRect;
	DWORD dwStyle = BS_BITMAP | BS_DEFPUSHBUTTON | WS_CHILD | WS_TABSTOP;

	m_dwMargins = GetMargins ();
	GetClientRect (ClientRect);

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
	{
		SetMargins (LOWORD(m_dwMargins), ClientRect.bottom - ClientRect.top);
		dwStyle |= WS_VISIBLE;
	}

	if (!IsWindowEnabled () || (GetStyle () & ES_READONLY))
	{
		dwStyle |= WS_DISABLED;
	}

	ButtonRect.SetRect (ClientRect.right - (ClientRect.bottom - ClientRect.top),
		0, ClientRect.right, ClientRect.bottom);

	if (!m_ButtonCalendar.m_hWnd)
	{
		static char szBitmap[] = {-128, 0, 0, 0, -128, 0, 0, 0, -128, 0, 0, 0,
			-128, 0, 0, 0, -128, 0, 0, 0, -128, 0, 0, 0, -128, 0, 0, 0,
			-128, 0, 0, 0, -128, 0, 0, 0, -128, 0, 0, 0, -128, 0, 0, 0,
			-128, 0, 0, 0, -128, 0, 0, 0, -128, 0, 0, 0, -128, -128, -128, 0,
			-128, 0, 0, 0, -128, 0, 0, 0, -64, -64, -64, 0, -64, -64, -64, 0,
			-64, -64, -64, 0, -64, -64, -64, 0, -64, -64, -64, 0,
			-128, 0, 0, 0, -128, 0, 0, 0, -128, -128, -128, 0, -128, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, -1, -1, 0, -128, -128, -128, 0, -1, -1, -1, 0,
			-128, -128, -128, 0, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0,
			0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, 0,
			-128, -128, -128, 0, -1, -1, -1, 0, -128, -128, -128, 0,
			-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			-1, -1, -1, 0, -128, -128, -128, 0, -128, -128, -128, 0,
			-128, -128, -128, 0, -128, -128, -128, 0, -128, -128, -128, 0,
			-128, -128, -128, 0, -1, -1, -1, 0, -1, -1, -1, 0,
			-1, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		m_ButtonCalendar.Create (_T(""), dwStyle, ButtonRect, this, 123);
		m_CalendarBitmap.CreateBitmap(13,12, 1, 32, szBitmap);
		m_ButtonCalendar.SetBitmap (m_CalendarBitmap);
	}

	return 1;
}

// Here's how I dumped the bitmap:
/*
	BOOL bRet = m_CalendarBitmap.LoadBitmap(MAKEINTRESOURCE(IDB_CALENDAR));
	char bits[624] = "";
	char *ptr = bits;
	DWORD bytes = m_CalendarBitmap.GetBitmapBits(sizeof(bits), &bits);

	m_CalendarBitmap.Dump(afxDump);

	FILE *fp = fopen("c:\\ben.txt", "w");
	CString str;

	for (int h = 0; h < 12; h++)
	{
		for (int w = 0; w < 13; ++w)
		{
			for (int b = 0; b < 4; ++b)
			{
				str.Format("%d, ", (int) *ptr++);
				fputs(str, fp);
			}

			fputs("\r\n", fp);
		}
	}

	fclose(fp);
*/

void CDateTimeEdit::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(::GetKeyState (VK_CONTROL) & 0x80) &&
		!(::GetKeyState (VK_SHIFT) & 0x80) && (nChar == VK_LEFT ||
		nChar == VK_RIGHT))
	{
		ResetValid ();

		switch (nChar)
		{
		case VK_LEFT:
			MoveLeft ();
			break;
		case VK_RIGHT:
			MoveRight ();
			break;
		default:
			assert (0);
			break;
		}
	}
	else if ((::GetKeyState (VK_CONTROL) & 0x80) && nChar == VK_DOWN)
	{
		OnCalendar ();
	}
	else
	{
		CBaseEdit::OnKeyDown (nChar, nRepCnt, nFlags);
	}

	m_ButtonCalendar.Invalidate ();
}

// TODO: Review function.
void CDateTimeEdit::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	bool bFinished = false;
	const int iCurrLen = GetWindowTextLength ();
	int iSelStart = -1;
	int iSelEnd = -1;

	// Note GetSel over-ridden
	GetSel (iSelStart, iSelEnd);

	if (nChar != VK_BACK && (iSelStart != iSelEnd &&
		iSelEnd != iCurrLen))
	{
		int iStart = -1;
		int iEnd = -1;
		bool bOK = true;

		e_Part ePart = LocatePart (iSelStart, iStart, iEnd);

		if (iSelStart == iStart && iSelEnd == iEnd)
		{
			switch (ePart)
			{
			case eDay:
				bOK = nChar >= '0' && nChar <= '3';

				if (!bOK)
					DisplayToolTip (true, _T("Day must start with 0-3"));
				break;
			case eMonth:
				bOK = nChar >= '0' && nChar <= '1';

				if (!bOK)
					DisplayToolTip (true, _T("Month must start with 0 or 1"));
				break;
			case eYear:
				bOK = nChar >= '0' && nChar <= '9';
				break;
			case eHour:
				bOK = nChar >= '0' && nChar <= '2';

				if (!bOK)
					DisplayToolTip (true, _T("Hour must start with 0-2"));
				break;
			case eMinute:
				bOK = nChar >= '0' && nChar <= '5';

				if (!bOK)
					DisplayToolTip (true, _T("Minute must start with 0-5"));
				break;
			case eSecond:
				bOK = nChar >= '0' && nChar <= '5';

				if (!bOK)
					DisplayToolTip (true, _T("Second must start with 0-5"));
				break;
			}

			if (bOK)
			{
				const bool bProcessChars = GetProcessChars ();

				SetProcessChars (false);
				CBaseEdit::OnChar (nChar, nRepCnt, nFlags);
				SetProcessChars (bProcessChars);
			}

			bFinished = true;
		}
	}
	else if (iSelStart >= m_iYearIndexStart && iSelStart <= m_iYearIndexEnd &&
		iSelStart < iCurrLen)
	{
		if (nChar >= '0' && nChar <= '9')
		{
			CString strText;
			const TCHAR *pszText = 0;
			int iCount = 0;

			ValidateChar (nChar, false);
			strText = GetProposedText ();
			pszText = static_cast<const TCHAR *>(strText) + m_iYearIndexStart;

			while (*pszText >= '0' && *pszText <= '9')
			{
				++iCount;
				++pszText;
			}

			if (iCount <= 4)
			{
				const bool bProcessChars = GetProcessChars ();

				if (iCount == 4)
				{
					if (_tstoi (strText.Mid (m_iYearIndexStart, 4)) < 1752)
					{
						strText.Delete (m_iYearIndexStart, 4);
						strText.Insert (m_iYearIndexStart, _T("1753"));
					}
				}

				SetProcessChars (false);
				SetWindowText (strText);
				SetProcessChars (bProcessChars);
				SetSel (iSelStart + 1, iSelStart + 1);
				bFinished = true;
			}
		}
	}
	else if (nChar == ' ' && iCurrLen == 0)
	{
		const COleDateTime dt (COleDateTime::GetCurrentTime ());
		CString strToday;

		switch(m_eMode)
		{
		case eDate:
			strToday = dt.Format (VAR_DATEVALUEONLY);
			break;
		case eTimeHHMM:
		case eTimeHHMMSS:
			strToday = dt.Format (VAR_TIMEVALUEONLY);

			if (strToday.IsEmpty ())
			{
				strToday = CString (_T("00")) + m_cTimeSeparator +
					CString (_T("00")) + m_cTimeSeparator +
					CString (_T("00"));
			}

			if (m_eMode == eTimeHHMM)
			{
				strToday = strToday.Left(strToday.GetLength () - 3);
			}

			break;
		case eDateTimeHHMM:
		case eDateTimeHHMMSS:
			strToday = dt.Format ();

			if (strToday.GetLength () == m_iDateLength)
			{
				strToday += CString (_T("00")) + m_cTimeSeparator +
					CString (_T("00")) + m_cTimeSeparator +
					CString (_T("00"));
			}

			if (m_eMode == eDateTimeHHMM)
			{
				strToday = strToday.Left(strToday.GetLength () - 3);
			}

			break;
		default:
			assert (0);
			break;
		}

		const int iLen = strToday.GetLength ();
		const bool bProcessChars = GetProcessChars ();

		SetProcessChars (false);
		SetWindowText (strToday);
		SetProcessChars (bProcessChars);
		SetSel (iLen, iLen);
		bFinished = true;
	}

	if (!bFinished)
	{
		CString strText;
		bool bFormatted = false;

		// Use this function to generate the 'proposed text'.
		// Don't check return value, because we will re-format first.
		ValidateChar (nChar);
		strText = GetProposedText ();

		if (nChar != VK_BACK)
		{
			if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
			{
				/// Pre-process
				bFormatted = FormatDate (strText);
			}
		}

		// Syntax check
		if (Match (strText))
		{
			CString strErrorMsg;

			if (SemanticCheck (strText, &strErrorMsg))
			{
				if (nChar != VK_BACK)
				{
					if (m_eMode != eDate)
					{
						bFormatted |= FormatTime (strText);
					}
				}

				if (bFormatted)
				{
					const int iLen = strText.GetLength ();
					const bool bProcessChars = GetProcessChars ();

					SetProcessChars (false);
					SetWindowText (strText);
					SetProcessChars (bProcessChars);
					SetSel (iLen, iLen);
				}
				else
				{
					CBaseEdit::OnChar (nChar, nRepCnt, nFlags);
				}
			}
			else
			{
				DisplayToolTip (true, strErrorMsg);
			}
		}
	}

	m_ButtonCalendar.Invalidate ();
}

void CDateTimeEdit::OnLButtonDown (UINT nFlags, CPoint point)
{
	FormatDateTime ();
	CBaseEdit::OnLButtonDown (nFlags, point);
	m_ButtonCalendar.Invalidate ();
}

// TODO: Review function.
void CDateTimeEdit::OnLButtonUp (UINT nFlags, CPoint point)
{
	int iSelStart = 0;
	int iSelEnd = 0;

	CBaseEdit::OnLButtonUp (nFlags, point);
	// Note GetSel over-ridden
	GetSel (iSelStart, iSelEnd);

	int iStart = 0;
	int iEnd = 0;
	const int iLen = GetWindowTextLength ();

	LocatePart (iSelStart, iStart, iEnd);

	if (iSelStart <= iLen && iSelEnd < iLen)
	{
		SetSel (iStart, iEnd);
	}

	m_ButtonCalendar.Invalidate ();
}

void CDateTimeEdit::OnLButtonDblClk (UINT nFlags, CPoint point)
{
	CBaseEdit::OnLButtonDblClk (nFlags, point);
	m_ButtonCalendar.Invalidate ();
}

void CDateTimeEdit::OnMouseMove (UINT nFlags, CPoint point)
{
	CBaseEdit::OnMouseMove (nFlags, point);
	m_ButtonCalendar.Invalidate ();
}

// Separate function, otherwise SetSel() doesn't work...
void CDateTimeEdit::OnKillFocus (CWnd *pNewWnd)
{
	CString strText;

	GetWindowText (strText);

	const int iLen = strText.GetLength ();

	if (m_eMode != eTimeHHMM && m_eMode != eTimeHHMMSS)
	{
		ExpandYear (strText);

		if (m_eMode == eDateTimeHHMM)
		{
			if (iLen == m_iDateLength)
			{
				strText += _T(" 00:00");
			}
			else if (iLen == m_iDateLength + 1)
			{
				strText += _T("00:00");
			}
		}
		else if (m_eMode == eDateTimeHHMMSS)
		{
			if (iLen == m_iDateLength)
			{
				strText += _T(" 00:00:00");
			}
			else if (iLen == m_iDateLength + 1)
			{
				strText += _T("00:00:00");
			}
		}
	}

	if (m_eMode != eDate)
	{
		if (iLen == m_iSecondIndexStart)
		{
			strText += _T("00");
		}
	}

	SetSel (0, -1);
	ReplaceSel (strText, TRUE);
	CBaseEdit::OnKillFocus (pNewWnd);
}

BOOL CDateTimeEdit::OnKillFocusEx ()
{
	// Don't pass on kill focus if we are moving to the calendar...
	// (i.e. return FALSE if we want msg to propogate)
	return GetFocus() == &m_ButtonCalendar;
}

void CDateTimeEdit::OnCalendar ()
{
	const int iDay = GetDay ();
	const int iMonth = GetMonth ();
	const int iYear = GetYear ();

	// m_pCalendarDlg deleted/zeroed by CCalendarDlg
	m_pCalendarDlg = new CCalendarDlg (this, this);
	// Modeless dialog is now created dynamically in constructor.
	// (IDD_CALENDAR no longer exists)
//	m_pCalendarDlg->Create (IDD_CALENDAR, this);
	m_pCalendarDlg->SetDate (iDay, iMonth, iYear);
	m_pCalendarDlg->ShowWindow (TRUE);
}
}
