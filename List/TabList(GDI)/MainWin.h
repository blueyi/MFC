#if !defined _MAINWIN_H_
#define _MAINWIN_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

class CWorkWin : public CWnd
{
public:
	CWorkWin();

public:

public:

	//{{AFX_VIRTUAL(CWorkWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	void SetPageInfo();
	void AddRecord(MYDATA *pData);
	virtual ~CWorkWin();

protected:
	//{{AFX_MSG(CWorkWin)
	afx_msg void OnPaint();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnAddRecord();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMyMark();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	RECORD   *Head;
	RECORD   *Tail;
	RECORD   *pCur;
	RECORD   *pFirst;
	FILETYPE  fHead;
	CString   fName;
	int       pCount;
	int       lSel;
	int       cPage;
	int       aPage;
	int       iIndex;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif 
