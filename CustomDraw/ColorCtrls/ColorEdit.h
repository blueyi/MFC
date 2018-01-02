#ifndef _CCOLOR_EDIT_H_
#define _CCOLOR_EDIT_H_

#include "ColorControl.h"

class CColorEdit : public CEdit, public CColorControl
{

public:

        CColorEdit();
	virtual ~CColorEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

        //{{AFX_VIRTUAL(CColorEdit)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	//}}AFX_VIRTUAL

protected:

        //{{AFX_MSG(CColorEdit)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}

#endif
