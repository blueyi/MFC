#if !defined(AFX_MYDIALOG_H__E10DB6E0_03C5_11D4_893F_0000B4B587FF__INCLUDED_)
#define AFX_MYDIALOG_H__E10DB6E0_03C5_11D4_893F_0000B4B587FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialog.h : header file
// download by http://www.codefans.net

/////////////////////////////////////////////////////////////////////////////
// CMyDialog dialog

#include "Dib.h"
//背景风格
#define BACK_STYLE_NORMAL 0					//普通，没有特殊背景
#define BACK_STYLE_BITMAP 1					//以位图作为背景
#define BACK_STYLE_COLORED 2				//以指定颜色作为背景
//位图显示风格
#define BMP_STYLE_ORIGIN 0					//按位图原大小显示
#define BMP_STYLE_STRETCH 1					//让位图拉伸显示
#define BMP_STYLE_TILE 2					//位图平铺

class CMyDialog : public CDialog
{
// Construction
public:
	//重载的构造函数，pBmpName默认为NULL，这样就和普通的CDialog一样的构造
	CMyDialog(const UINT IDD,CWnd* pParent = NULL,LPCTSTR pBmpName = NULL);
	virtual ~CMyDialog();					//析构函数
	virtual void Initialize();				//初始化函数
	virtual void Empty();					//清空函数
	virtual BOOL LoadBmp(LPCTSTR pBmpName);	//调入Bitmap
	//以下几个函数分别设置和获得背景显示风格、背景颜色和位图显示风格
	int GetBackStyle() { return m_nBackStyle; }
	CBrush * GetBackBrush() { return m_pBackBrush; }
	int GetBmpStyle() { return m_nBmpStyle; }
	void SetBackStyle(int nBackStyle);
	void SetBackBrush(COLORREF color);
	void SetBmpStyle(int nBmpStyle);
protected:
	CDib * m_pDib;							//背景图的CDib类指针
	CBrush * m_pBackBrush;					//背景颜色画笔
	int m_nBackStyle;						//背景显示风格
	int m_nBmpStyle;						//位图显示风格
// Dialog Data
	//{{AFX_DATA(CMyDialog)
	//将MyDialog的ID注释掉，使用子类的ID
	//enum { IDD = _UNKNOWN_RESOURCE_ID_ };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
//protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDialog)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOG_H__E10DB6E0_03C5_11D4_893F_0000B4B587FF__INCLUDED_)
