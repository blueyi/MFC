
#ifndef __XPANETEXT__
#define __XPANETEXT__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XStatusBar.h"

class XPaneText
{
protected:
	int	index;

public:
	XPaneText(LPCSTR text, int ix = 0)
	{
		ASSERT(XStatusBar::aktBar);

		index = ix;
		XStatusBar::aktBar->SavePane(ix);
		XStatusBar::aktBar->SetMode(ix, XSB_TEXT | XStatusBar::aktBar->GetMode(ix) & XSB_ALIGN);

		COLORREF fg = XStatusBar::aktBar->GetFgColor(ix);
		COLORREF bk = XStatusBar::aktBar->GetBkColor(ix);
		XStatusBar::aktBar->SetFgColor(ix, fg, fg);		// Gleiche Fg- und Bk-Farbe für
		XStatusBar::aktBar->SetBkColor(ix, bk, bk);		// On- und Off-Modus

		XStatusBar::aktBar->SetText(ix, text, text);	// Gleicher Text in beiden Modi
	}

	~XPaneText()
	{
		ASSERT(XStatusBar::aktBar);

		XStatusBar::aktBar->RestorePane(index);
	}
};

#endif // __XPANETEXT__
