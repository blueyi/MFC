#include "StdAfx.h"
#include "CurrencyEdit.h"

#include <memory>
#include <sstream>

namespace FilterEdit
{
bool CCurrencyEdit::m_bInitialised = false;
CString CCurrencyEdit::m_strCurrency;
CCurrencyEdit::e_Currency CCurrencyEdit::m_eCurrency = ePrefix;
CCurrencyEdit::e_NegCurrency CCurrencyEdit::m_eNegCurrency = eNegCurrNum;
CString CCurrencyEdit::m_strDecimal;
int CCurrencyEdit::m_iFractionalDigits = 2;
CString CCurrencyEdit::m_strSeparator;
CString CCurrencyEdit::m_strToolTip;
CRegEx CCurrencyEdit::m_RegEx;

CCurrencyEdit::CCurrencyEdit () :
	CBaseEdit (&m_RegEx)
{
	if (!m_bInitialised)
	{
		// Max len for LOCALE_SCURRENCY is 6.  This is the longest entry out of the
		// used LOCALE_ attributes.
		unsigned int iBuffSize = 6;
		TCHAR szBuffer[6 + 1];

		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_SCURRENCY, szBuffer,
			iBuffSize);
		m_strCurrency = szBuffer;
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_ICURRENCY, szBuffer,
			iBuffSize);
		m_eCurrency = static_cast<e_Currency> (_tstoi (szBuffer));
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_INEGCURR, szBuffer,
			iBuffSize);
		m_eNegCurrency = static_cast<e_NegCurrency> (_tstoi (szBuffer));
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, szBuffer,
			iBuffSize);
		m_strDecimal = szBuffer;
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_IDIGITS, szBuffer,
			iBuffSize);
		m_iFractionalDigits = _tstoi (szBuffer);
		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, szBuffer,
			iBuffSize);
		m_strSeparator = szBuffer;
		iBuffSize = ::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_SMONGROUPING, szBuffer,
			0);

		std::auto_ptr<TCHAR> Grouping (new TCHAR[iBuffSize]);

		::GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_SMONGROUPING, Grouping.get (),
			iBuffSize);
//		_tcscpy (Grouping.get (), _T("3;4;5;0")); // Test...

		TCHAR *pszGrouping = Grouping.get ();
		int iCurr = 0;
		int iNext = _tstoi (pszGrouping);
		CString strDigit = _T("[0-9]");
		CString strRegEx;

		if (iNext == 0)
		{
			strRegEx = strDigit + '+';
		}
		else
		{
			CString strLHS;
			CString strRHS;
			CString strTrailer;
			CString strSeparator = m_strSeparator;

			EscapeString (strSeparator);

			do
			{
				strLHS.Format (_T("%s{1,%d}"), strDigit, iNext);
				strRHS.Format (_T("%s{%d}"), strDigit, iNext);
				iCurr = iNext;

				while (*pszGrouping != ';') pszGrouping++;

				pszGrouping++;
				iNext = _tstoi (pszGrouping);

				if (iNext == 0)
				{
					strRHS = '(' + strSeparator + strRHS + _T(")*");
					strRegEx += strLHS + strRHS + strTrailer;
				}
				else
				{
					strRegEx += strLHS;
					strRegEx += strTrailer;
					strRegEx += '|';
					strTrailer = strSeparator + strRHS + strTrailer;
				}
			} while (iNext != 0);
		}

		CString strDecimal = m_strDecimal;
		CString strFract;

		EscapeString (strDecimal);
		strFract.Format (_T("%s[0-9]{%d}"), strDecimal, m_iFractionalDigits);
		strRegEx = '(' + strRegEx + ')' + strFract;

		CString strCurrency = m_strCurrency;
		CString strNegRegEx = strRegEx;

		EscapeString (strCurrency);

		switch (m_eCurrency)
		{
			case ePrefix:
				strRegEx = strCurrency + strRegEx;
				break;
			case eSuffix:
				strRegEx += strCurrency;
				break;
			case ePrefixSpc:
				strRegEx = strCurrency + ' ' + strRegEx;
				break;
			case eSpcSuffix:
				strRegEx += ' ' + strCurrency;
				break;
			default:
				// Should never get here
				assert (0);
				break;
		}

		switch (m_eNegCurrency)
		{
			case eParenCurrNumParen:
				strNegRegEx = _T("\\(") + strCurrency + strNegRegEx +
					_T("\\)");
				break;
			case eNegCurrNum:
				strNegRegEx = '-' + strCurrency + strNegRegEx;
				break;
			case eCurrNegNum:
				strNegRegEx = strCurrency + '-' + strNegRegEx;
				break;
			case eCurrNumNeg:
				strNegRegEx = strCurrency + strNegRegEx + '-';
				break;
			case eParenNumCurrParen:
				strNegRegEx = _T("\\(") + strNegRegEx + strCurrency +
					_T("\\)");
				break;
			case eNegNumCurr:
				strNegRegEx = '-' + strNegRegEx + strCurrency;
				break;
			case eNumNegCurr:
				strNegRegEx += '-' + strCurrency;
				break;
			case eNumCurrNeg:
				strNegRegEx += strCurrency + '-';
				break;
			case eNegNumSpcCurr:
				strNegRegEx = '-' + strNegRegEx + ' ' + strCurrency;
				break;
			case eNegCurrSpcNum:
				strNegRegEx =  '-' + strCurrency + ' ' + strNegRegEx;
				break;
			case eNumSpcCurrNeg:
				strNegRegEx += ' ' + strCurrency + '-';
				break;
			case eCurrSpcNumNeg:
				strNegRegEx = strCurrency + ' ' + strNegRegEx + '-';
				break;
			case eCurrSpcNegNum:
				strNegRegEx = strCurrency + _T(" -") + strNegRegEx;
				break;
			case eNumNegSpcCurr:
				strNegRegEx += _T("- ") + strCurrency;
				break;
			case eParenCurrSpcNumParen:
				strNegRegEx = _T("\\(") + strCurrency + ' ' + strNegRegEx +
					_T("\\)");
				break;
			case eParenNumSpcCurrParen:
				strNegRegEx = _T("\\(") + strNegRegEx + ' ' + strCurrency +
					_T("\\)");
				break;
			default:
				// Should never get here
				assert (0);
				break;
		}

		strRegEx += '|' + strNegRegEx;

		m_RegEx.assign (strRegEx);
		iBuffSize = ::GetCurrencyFormat (LOCALE_USER_DEFAULT, NULL,
			_T("123456789"), NULL, NULL, 0);

		std::auto_ptr<TCHAR> Currency (new TCHAR[iBuffSize]);

		::GetCurrencyFormat (LOCALE_USER_DEFAULT, NULL, _T("123456789"), NULL,
			Currency.get (), iBuffSize);
		iBuffSize = ::GetCurrencyFormat (LOCALE_USER_DEFAULT, NULL,
			_T("-123456789"), NULL, NULL, 0);

		std::auto_ptr<TCHAR> NegCurrency (new TCHAR[iBuffSize]);

		::GetCurrencyFormat (LOCALE_USER_DEFAULT, NULL, _T("-123456789"), NULL,
			NegCurrency.get (), iBuffSize);
		m_strToolTip = Currency.get ();
		m_strToolTip += _T(" or ");
		m_strToolTip += NegCurrency.get ();
		m_bInitialised = true;
	}
}

CCurrencyEdit::~CCurrencyEdit ()
{
}

void CCurrencyEdit::CreateToolTip (CWnd *pParent)
{
	CBaseEdit::CreateToolTip (pParent, m_strToolTip);
}

double CCurrencyEdit::GetValue () const
{
	CString strCurrency;
	std::basic_stringstream<TCHAR> ss;
	double dValue = 0;

	GetWindowText (strCurrency);
	RemoveSeparators (strCurrency);
	ss << static_cast<const TCHAR *> (strCurrency);
	ss >> dValue;
	return dValue;
}

void CCurrencyEdit::RemoveSeparators (CString &str) const
{
	CString strValue;
	bool bNeg = str.Find ('-') >= 0;
	const TCHAR *pszStr = str;

	if (!bNeg) bNeg = str.Find ('(') >= 0;

	while (*pszStr)
	{
		if (*pszStr >= '0' && *pszStr <= '9')
		{
			strValue += *pszStr;
		}

		pszStr++;
	}

	strValue.Insert (strValue.GetLength () - m_iFractionalDigits, '.');

	if (bNeg) strValue = '-' + strValue;

	str = strValue;
}
}
