#pragma once
#include <afxtempl.h>

// CIbTabCtrl

class CIbTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CIbTabCtrl)

private: 
	CArray<CWnd*,CWnd*> m_oPages;
	void setPage(CWnd* pWnd);
	int  m_iPrevPage;
public:
	CIbTabCtrl();
	virtual ~CIbTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void addNewPage(CString strPage, CWnd * pPage);
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	void setDefaultPage(int iIndex);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void removePage(int iIndex);
};


