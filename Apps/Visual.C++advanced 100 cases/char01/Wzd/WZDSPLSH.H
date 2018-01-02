#if !defined WZDSPLASH_H
#define WZDSPLASH_H

// WzdSplsh.h : header file
//
#include "WzdBtmap.h"
/////////////////////////////////////////////////////////////////////////////
// CWzdSplash window

class CWzdSplash : public CWnd
{
// Construction
public:
	CWzdSplash();

// Attributes
public:

// Operations
public:
	void Create( UINT nBitmapID );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWzdSplash)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWzdSplash();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWzdSplash)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWzdBitmap m_bitmap;
};

/////////////////////////////////////////////////////////////////////////////

#endif
