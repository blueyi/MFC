#if !defined(AFX_MYSTATIC_H__B10E7BAF_1C1E_11D4_893F_0000B4B587FF__INCLUDED_)
#define AFX_MYSTATIC_H__B10E7BAF_1C1E_11D4_893F_0000B4B587FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();						//构造函数
	COLORREF m_foreColor,m_backColor;	//前、背景颜色
	BOOL m_bTrans;						//是否透明
	CFont * m_pFont;					//显示字体
// Attributes
public:
	//以下几个函数分别设置和获取显示的前景色、背景色、字体、透明设置
	void SetForeColor(COLORREF foreColor);
	COLORREF GetForeColor();
	void SetBackColor(COLORREF backColor);
	COLORREF GetBackColor();
	void SetTransMode(BOOL bTrans);
	BOOL IsTrans();
	CFont * GetFontPtr();
	void SetFont(int nWeight,BOOL bItalic,BOOL bUnderlined,TCHAR * pFontName);
	void SetStyle(COLORREF foreColor,COLORREF backColor,BOOL bTrans);
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__B10E7BAF_1C1E_11D4_893F_0000B4B587FF__INCLUDED_)
