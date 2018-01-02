#if !defined(AFX_BKBITMAP_H__3442F2A4_54D9_4E37_8953_4E755914D102__INCLUDED_)
#define AFX_BKBITMAP_H__3442F2A4_54D9_4E37_8953_4E755914D102__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BkBitmap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBkBitmap window

class CBkBitmap : public CStatic
{
// Construction
public:
	CBkBitmap();

// Attributes
public:

protected:
	BOOL		m_bBkModified;
// Operations
public:
	HBITMAP SetBitmap( HBITMAP hBitmap );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBkBitmap)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBkBitmap();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBkBitmap)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BKBITMAP_H__3442F2A4_54D9_4E37_8953_4E755914D102__INCLUDED_)
