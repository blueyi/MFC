#if !defined(AFX_SPLITTERWNDEX_H__E27F199D_D5BB_4444_8E49_615EF2AF2675__INCLUDED_) 
#define AFX_SPLITTERWNDEX_H__E27F199D_D5BB_4444_8E49_615EF2AF2675__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
// SplitterWndEx.h : header file 
// 

///////////////////////////////////////////////////////////////////////////// 
// CSplitterWndEx window 

class CSplitterWndEx : public CSplitterWnd 
{ 
	// Construction 
public: 
	CSplitterWndEx(); 

	// Attributes 
public: 

	// Operations 
public: 

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CSplitterWndEx) 
	//}}AFX_VIRTUAL 

	// Implementation 
public: 
	virtual ~CSplitterWndEx(); 

	// Generated message map functions 
protected: 
	//{{AFX_MSG(CSplitterWndEx) 
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

///////////////////////////////////////////////////////////////////////////// 

//{{AFX_INSERT_LOCATION}} 
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 

#endif // !defined(AFX_SPLITTERWNDEX_H__E27F199D_D5BB_4444_8E49_615EF2AF2675__INCLUDED_) 