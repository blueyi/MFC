// ViewManager.h: interface for the CViewManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWMANAGER_H__C67D43A7_F890_11D1_83BA_0000B43382FE__INCLUDED_)
#define AFX_VIEWMANAGER_H__C67D43A7_F890_11D1_83BA_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxcoll.h>

#include "WindowTabCtrl.h"

class CViewManager;
extern CViewManager theViewManager;
extern CWindowTabCtrl theWindowTab;

class CViewManager  
{
public:
	void OnActivateView(const BOOL bActivate, CView * pView);
	int GetWindowNum();
	void SetViewName(const char * cs, CView * pView);
	void DoWindowList();
	void RemoveAll();
	void RemoveView(CView * pView);
	void AddView(const char * csName, CView * pView);
	CViewManager();
	virtual ~CViewManager();

	CPtrArray		arViews;
	CStringArray	arViewTitles;

	bool			bClosing;
};

#endif // !defined(AFX_VIEWMANAGER_H__C67D43A7_F890_11D1_83BA_0000B43382FE__INCLUDED_)
