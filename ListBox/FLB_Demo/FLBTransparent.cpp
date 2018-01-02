// FLBTransparent.cpp : implementation file
//

#include "stdafx.h"
#include "demoflb.h"
#include "FLBTransparent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFLBTransparent

CFLBTransparent::CFLBTransparent()
{
}

CFLBTransparent::CFLBTransparent(DWORD dwStyleFlags, LPCTSTR lpszMruListName) :
CFontListBox(dwStyleFlags, lpszMruListName)
{
}

CFLBTransparent::~CFLBTransparent()
{
}


BEGIN_MESSAGE_MAP(CFLBTransparent, CFontListBox)
	//{{AFX_MSG_MAP(CFLBTransparent)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFLBTransparent message handlers

COLORREF CFLBTransparent::OnColorHighlightText()
{
	return RGB(255, 0, 0);
}

COLORREF CFLBTransparent::OnColorText()
{
	return ::GetSysColor(COLOR_HIGHLIGHTTEXT);
}
