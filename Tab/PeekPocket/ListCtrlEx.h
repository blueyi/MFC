//////////////////////////////////////////////////////////////////////////
// This is just a wrapper around MFC CListCtrl without
// shell gesture recognition (dots popup)
// more on the subject:
// http://www.pocketpcdn.com/articles/print_disable_reddots.html
//////////////////////////////////////////////////////////////////////////

#pragma once


// CListCtrlEx

class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	virtual ~CListCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRecognizeGesture(NMHDR* pNMHDR, LRESULT* pResult); 
};


