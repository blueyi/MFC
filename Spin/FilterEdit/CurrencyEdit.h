#pragma once
#include "BaseEdit.h"

namespace FilterEdit
{
class CCurrencyEdit : public CBaseEdit
{
public:
	CCurrencyEdit ();
	virtual ~CCurrencyEdit ();
	void CreateToolTip (CWnd *pParent);
	double GetValue () const;

protected:
	void RemoveSeparators (CString &str) const;

private:
	enum e_Currency {ePrefix, eSuffix, ePrefixSpc, eSpcSuffix};
	enum e_NegCurrency {eParenCurrNumParen, eNegCurrNum, eCurrNegNum,
		eCurrNumNeg, eParenNumCurrParen, eNegNumCurr, eNumNegCurr,
		eNumCurrNeg, eNegNumSpcCurr, eNegCurrSpcNum, eNumSpcCurrNeg,
		eCurrSpcNumNeg, eCurrSpcNegNum, eNumNegSpcCurr, eParenCurrSpcNumParen,
		eParenNumSpcCurrParen};

	static bool m_bInitialised;
	static CString m_strCurrency;
	static e_Currency m_eCurrency;
	static e_NegCurrency m_eNegCurrency;
	static CString m_strDecimal;
	static int m_iFractionalDigits;
	static CString m_strSeparator;
	static CString m_strToolTip;
	static CRegEx m_RegEx;
};
}
