// ViewManager.cpp: implementation of the CViewManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MDIWindList.h"
#include "ViewManager.h"

#include "WindowListDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CViewManager theViewManager;
CWindowTabCtrl theWindowTab;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewManager::CViewManager()
{
	bClosing = false;
}

CViewManager::~CViewManager()
{
	arViews.RemoveAll();
	arViewTitles.RemoveAll();
}

void CViewManager::AddView(const char * csName, CView * pView)
{
	if (bClosing) return;

	CString cs(csName);

	arViews.Add(pView);
	arViewTitles.Add(cs);

	if (theWindowTab.GetSafeHwnd())
	{
		TC_ITEM ti;
		ti.mask = TCIF_TEXT|TCIF_PARAM;
		ti.pszText = cs.LockBuffer();
		ti.lParam = (long) pView;
		theWindowTab.InsertItem(theWindowTab.GetItemCount(), &ti);
		cs.UnlockBuffer();
		theWindowTab.ResizeTabs();
	}
}

void CViewManager::RemoveView(CView * pView)
{
	if (bClosing || arViews.GetSize() <= 0) return;

	int t;

	if (theWindowTab.GetSafeHwnd())
	{
		for (t = 0; t < theWindowTab.GetItemCount(); t++)
		{
			TC_ITEM ti;
			ti.mask = TCIF_PARAM;
			theWindowTab.GetItem(t, &ti);
			if (ti.lParam == (long) pView)
			{
				theWindowTab.DeleteItem(t);
				break;
			}
		}
	}


	for (t = 0; t < arViews.GetSize(); t++)
	{
		if ((CView *)(arViews.GetAt(t)) == pView)
		{
			arViewTitles.RemoveAt(t);
			arViews.RemoveAt(t);
			return;
		}
	}
}

void CViewManager::RemoveAll()
{
	arViews.RemoveAll();
	arViewTitles.RemoveAll();
}

void CViewManager::DoWindowList()
{
	CWindowListDlg dlg;
	dlg.DoModal();
}

void CViewManager::SetViewName(const char * cs, CView * pView)
{
	if (bClosing || arViews.GetSize() <= 0) return;

	int t;
	CString csName(cs);

	if (theWindowTab.GetSafeHwnd())
	{
		for (t = 0; t < theWindowTab.GetItemCount(); t++)
		{
			TC_ITEM ti;
			ti.mask = TCIF_PARAM;
			theWindowTab.GetItem(t, &ti);
			if (ti.lParam == (long) pView)
			{
				ti.mask = TCIF_PARAM|TCIF_TEXT;
				ti.pszText = csName.LockBuffer();
				theWindowTab.SetItem(t, &ti);
				csName.UnlockBuffer();
				theWindowTab.Invalidate();
				break;
			}
		}
	}

	for (t = 0; t < arViews.GetSize(); t++)
	{
		if ((CView *)(arViews.GetAt(t)) == pView)
		{
			arViewTitles.SetAt(t, csName);
			return;
		}
	}
}

int CViewManager::GetWindowNum()
{
	return arViews.GetSize();
}

void CViewManager::OnActivateView(const BOOL bActivate, CView * pView)
{
	if (bActivate)
	{
		if (theWindowTab.GetSafeHwnd())
		{
			for (int t = 0; t < theWindowTab.GetItemCount(); t++)
			{
				TC_ITEM ti;
				ti.mask = TCIF_PARAM;
				theWindowTab.GetItem(t, &ti);
				if (ti.lParam == (long) pView)
				{
					theWindowTab.SetCurSel(t);
					theWindowTab.Invalidate();
					break;
				}
			}
		}
	}
}
