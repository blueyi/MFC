#if !defined(AFX_ADVHEADER_H__31A9FFC4_8106_47A3_AF25_8221ACD7404A__INCLUDED_)
#define AFX_ADVHEADER_H__31A9FFC4_8106_47A3_AF25_8221ACD7404A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvHeader.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdvHeader window

class CAdvHeader : public CHeaderCtrl
{
// Construction
public:
	CAdvHeader();

// Attributes
public:
	BOOL Init(CHeaderCtrl *pHeader);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvHeader)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAdvHeader();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAdvHeader)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVHEADER_H__31A9FFC4_8106_47A3_AF25_8221ACD7404A__INCLUDED_)
