#ifndef _CCOLORCOMBOBOX_H_
#define _CCOLORCOMBOBOX_H_

#include "ColorControl.h"

class CColorComboBox : public CComboBox, public CColorControl
{

public:

	CColorComboBox();
	virtual ~CColorComboBox();

        //{{AFX_VIRTUAL(CColorComboBox)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	//}}AFX_VIRTUAL

protected:

        //{{AFX_MSG(CColorComboBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}

#endif
