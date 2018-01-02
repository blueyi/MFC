#if !defined _MAINFRM_H_
#define _MAINFRM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainWin.h"

class CWorkFrm : public CFrameWnd
{
	
public:
	CWorkFrm();
protected: 
	DECLARE_DYNAMIC(CWorkFrm)

public:
	CToolBar    mToolBar;

public:

	//{{AFX_VIRTUAL(CWorkFrm)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

public:
	virtual ~CWorkFrm();

protected:  
	CStatusBar  mStatusBar;
	CWorkWin    mView;

protected:
	//{{AFX_MSG(CWorkFrm)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif 