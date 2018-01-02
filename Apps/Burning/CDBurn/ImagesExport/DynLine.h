#if !defined(AFX_DYNLINE_H__AFBB7EE5_76F3_41FA_B18E_5A7F4A926204__INCLUDED_)
#define AFX_DYNLINE_H__AFBB7EE5_76F3_41FA_B18E_5A7F4A926204__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DynLine.h : header file
//
#ifdef FILMING_IMP
   #define CLASS_DECL_DLNLINE  __declspec(dllexport)
#else
   #define CLASS_DECL_DLNLINE  __declspec(dllimport)
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynLine window

class /*CLASS_DECL_DLNLINE*/ CDynLine : public CStatic
{
// Construction
public:
	CDynLine();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynLine)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Stop();
	void Start();
	CBitmap m_bmp;
	virtual ~CDynLine();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDynLine)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNLINE_H__AFBB7EE5_76F3_41FA_B18E_5A7F4A926204__INCLUDED_)
