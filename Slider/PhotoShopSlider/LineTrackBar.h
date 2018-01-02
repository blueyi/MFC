/********************************************************************

	LineTrackBar.h - ISee图像浏览器—图像处理模块类LineTrackBar头文件

    版权所有(C) VCHelp-coPathway-ISee workgroup 2000 all member's

    这一程序是自由软件，你可以遵照自由软件基金会出版的GNU 通用许可证
	条款来修改和重新发布这一程序。或者用许可证的第二版，或者（根据你
	的选择）用任何更新的版本。

    发布这一程序的目的是希望它有用，但没有任何担保。甚至没有适合特定
	目地的隐含的担保。更详细的情况请参阅GNU通用许可证。

    你应该已经和程序一起收到一份GNU通用许可证(GPL)的副本。如果还没有，
	写信给：
    The Free Software Foundation, Inc.,  675  Mass Ave,  Cambridge,
    MA02139,  USA

	如果你在使用本软件时有什么问题或建议，用以下地址可以与我们取得联
	系：
		http://isee.126.com
		http://www.vchelp.net
	或：
		iseesoft@china.com

	作者：马翔
   e-mail:hugesoft@yeah.net

   功能实现：PhotoShop风格的滑动条

	文件版本：
		Build xxxxx
		Date  2000-11-18

********************************************************************/
#if !defined(AFX_LINETRACKBAR_H__D4A2173A_2625_4EE6_97EC_F421924361D0__INCLUDED_)
#define AFX_LINETRACKBAR_H__D4A2173A_2625_4EE6_97EC_F421924361D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineTrackBar.h : header file
//
#include <afxtempl.h>
#include "SignEdit.h"

#define RE_STRING	0
#define RE_INT		1

class CLineTrackObj:public CObject
{
public:
	CLineTrackObj() {;}

	COLORREF m_color;
	int     m_nLower;		// lower bounds
	int     m_nUpper;		// upper bounds
	int		m_nZero;

	int     m_nPos;		// current position within bounds
	int		m_nStep;
	int		m_nStype;
	BOOL	m_bFocus;
	CWnd	*pCtrl;
};

typedef CTypedPtrArray <CObArray, CLineTrackObj*> CItemArray;

/////////////////////////////////////////////////////////////////////////////
// CLineTrackBar window

class CLineTrackBar : public CWnd
{
// Construction
public:
	CLineTrackBar();

// Attributes
public:
	CDC      m_MemDC;
	CBitmap  m_Bitmap;
	CItemArray m_items;
	CLineTrackObj* pItem;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineTrackBar)
	//}}AFX_VIRTUAL

// Implementation
private:
	void SetGroupControlText();
	void SetGroupControl(int nCtrl);
	void InvalidateCtrl();
	void DrawSpike();

public:
	BOOL RegisterWndClass(HINSTANCE hInstance);
	int GetPos();
	void SetPos(int nPos);
	BOOL InitControl(int nGroupCtrl=-1,COLORREF color=RGB(0,0,0), int nLower=0, int nZero=100, int nUpper=200,int nStep=1,BOOL bFocus=FALSE,int nStype=0);
	virtual ~CLineTrackBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineTrackBar)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINETRACKBAR_H__D4A2173A_2625_4EE6_97EC_F421924361D0__INCLUDED_)
