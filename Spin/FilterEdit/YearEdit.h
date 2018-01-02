#pragma once
#include "BaseEdit.h"

namespace FilterEdit
{
class CYearEdit : public CBaseEdit
{
public:
	CYearEdit ();
	virtual ~CYearEdit ();
	int GetValue () const;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnKillFocus(CWnd* pNewWnd);

private:
	static bool m_bInitialised;
	static CRegEx m_RegEx;
};
}
