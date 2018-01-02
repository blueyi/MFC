#pragma once
#include "BaseEdit.h"
#include "CalendarDlg.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sqltypes.h>

namespace FilterEdit
{
void AFXAPI DDX_DateTimeEdit(CDataExchange *pDX, int nIDC, COleDateTime &Date);
void AFXAPI DDX_DateTimeEdit(CDataExchange *pDX, int nIDC, CString &Date);

class CDateTimeEdit : public CBaseEdit
{
public:
	enum e_Mode {eDate, eTimeHHMM, eTimeHHMMSS, eDateTimeHHMM, eDateTimeHHMMSS};

	CCalendarDlg *m_pCalendarDlg;

	CDateTimeEdit (const e_Mode eMode = eDate);
	virtual ~CDateTimeEdit ();

	void SetMode (const e_Mode eMode);
	e_Mode GetMode () const;
	void SetDateTime (const COleDateTime &dt);
	// A lot of Get functions can't be const due to IsInputValid()
	// setting flags etc.
	COleDateTime GetDateTime ();
	bool SetDateTime (const int iYear, const int iMonth, const int iDay,
		const int iHour, const int iMinute, const int iSecond);
	bool GetDateTime (int &iYear, int &iMonth, int &iDay,
		int &iHour, int &iMinute, int &iSecond);
	bool SetDate (const int iYear, const int iMonth, const int iDay);
	bool GetDate (int &iYear, int &iMonth, int &iDay);
	bool SetTimeStamp (const SQL_TIMESTAMP_STRUCT *ts_);
	bool GetTimeStamp (SQL_TIMESTAMP_STRUCT *ts_);
	bool SetGregorian (const boost::gregorian::date &date_);
	boost::gregorian::date GetGregorian ();
	bool SetPosixTime (const boost::posix_time::ptime &time_);
	boost::posix_time::ptime GetPosixTime ();
	int GetDay ();
	int GetMonth ();
	int GetYear ();
	bool SetTime (const int iHour, const int iMinute, const int iSecond);
	bool GetTime (int &iHour, int &iMinute, int &iSecond);
	int GetHour ();
	int GetMinute ();
	int GetSecond ();
	void CreateToolTip (CWnd *pParent);
	virtual void Increment (const int iInc);

	void GetSel (int &nStartChar, int &nEndChar) const;
	const CButton *GetCalendarButton () const;

	void SetMin(const COleDateTime &Min);
	void SetMax(const COleDateTime &Max);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimeEdit)
protected:
	virtual void PreSubclassWindow ();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDateTimeEdit)
	afx_msg LRESULT OnCreateCalButton (WPARAM, LPARAM);
	afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar (UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk (UINT nFlags, CPoint point);
	afx_msg void OnMouseMove (UINT nFlags, CPoint point);
	afx_msg void OnKillFocus (CWnd *pNewWnd);
	afx_msg BOOL OnKillFocusEx();
	afx_msg void OnCalendar ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual bool SyntaxCheck (const CString &strText);
	virtual bool SemanticCheck (const CString &strText,
		CString *pstrErrorMsg = 0);
	void FormatDateTime ();
	bool FormatDate (CString &strText);
	bool FormatDay (CString &strText);
	bool FormatMonth (CString &strText);
	bool FormatYear (CString &strText);
	bool FormatTime (CString &strText);
	bool IsDateValid (const CString &strText, CString *pstrErrorMsg = 0);
	bool IsDayMonthYearValid (const CString &strText,
		CString *pstrErrorMsg = 0);
	bool IsMonthDayYearValid (const CString &strText,
		CString *pstrErrorMsg = 0);
	bool IsYearMonthDayValid (const CString &strText,
		CString *pstrErrorMsg = 0);
	void MoveLeft ();
	void MoveRight ();

	void SetToolTipText();

private:
	enum e_Part {eDay, eMonth, eYear, eHour, eMinute, eSecond};

	e_Mode m_eMode;
	DWORD m_dwMargins;
	CButton m_ButtonCalendar;
	CBitmap m_CalendarBitmap;
	bool m_bFromSpin;
	COleDateTime m_Min;
	COleDateTime m_Max;

	static bool m_bInitialised;
	static CRegEx m_TimeHHMMRegEx;
	static CRegEx m_TimeHHMMSSRegEx;
	static CRegEx m_DateRegEx;
	static CRegEx m_DateTimeHHMMRegEx;
	static CRegEx m_DateTimeHHMMSSRegEx;
	static DWORD m_dwCenturyPrefix;
	static DWORD m_dwTwoDigitYearMax;
	static TCHAR m_chFieldOrder;
	static int m_iDayIndexStart;
	static int m_iDayIndexEnd;
	static int m_iMonthIndexStart;
	static int m_iMonthIndexEnd;
	static int m_iYearIndexStart;
	static int m_iYearIndexEnd;
	static int m_iDateLength;
	int m_iHourIndexStart;
	int m_iHourIndexEnd;
	int m_iMinuteIndexStart;
	int m_iMinuteIndexEnd;
	int m_iSecondIndexStart;
	int m_iSecondIndexEnd;
	static TCHAR m_cDateSeparator;
	static TCHAR m_cTimeSeparator;
	static CString m_strDateToolTip;
	static CString m_strTimeHHMMToolTip;
	static CString m_strTimeHHMMSSToolTip;
	static CString m_strDateTimeHHMMToolTip;
	static CString m_strDateTimeHHMMSSToolTip;

	void SetTimeIndexes ();
	bool ValidateDayMonth (const int iDay, const int iMonth);
	bool ValidateLeapYear (const int iDay, const int iMonth,
		const int iYear);
	bool ExpandYear (CString &strYear);
	e_Part LocatePart (const int iSelStart, int &iStart, int &iEnd) const;
	e_Part LocateDate (const int iSelStart, int &iStart, int &iEnd) const;
	e_Part LocateTime (const int iSelStart, int &iStart, int &iEnd) const;
	int GetDay (const CString &strDate) const;
	int GetMonth (const CString &strDate) const;
	int GetYear (const CString &strDate) const;
	int MaxDay (const int iMonth, const int iYear);
};
}
