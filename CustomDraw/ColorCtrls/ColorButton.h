#ifndef _CCOLORBUTTON_H_
#define _CCOLORBUTTON_H_

#include "ColorControl.h"

class CColorButton : public CButton, public CColorControl
{

public:

	CColorButton();
	virtual ~CColorButton();

protected:

	//{{AFX_VIRTUAL(CColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CColorButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

#endif
