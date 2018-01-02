#ifndef _CCOLOR_STATIC_H_
#define _CCOLOR_STATIC_H_

#include "ColorControl.h"

class CColorStatic : public CStatic, public CColorControl
{

public:

        CColorStatic();
	virtual ~CColorStatic();

	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

protected:

        //{{AFX_MSG(CColorStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
