#pragma once

namespace FilterEdit
{
// CSpin
class CSpin : public CSpinButtonCtrl
{
	DECLARE_DYNAMIC (CSpin)

public:
	CSpin ();
	virtual ~CSpin ();

protected:
	DECLARE_MESSAGE_MAP ()
public:
	afx_msg void OnDeltapos (NMHDR *pNMHDR, LRESULT *pResult);
};
}
