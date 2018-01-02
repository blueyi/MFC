/********************************************************************

	SignEdit.h - ISee图像浏览器—图像处理模块类SignEdit头文件

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

   功能实现：可不输入内容的整数编辑框

	文件版本：
		Build xxxxx
		Date  2000-11-18

********************************************************************/
#if !defined(AFX_SIGNEDIT_H__E42C869B_8178_452E_BA85_51850C709A49__INCLUDED_)
#define AFX_SIGNEDIT_H__E42C869B_8178_452E_BA85_51850C709A49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SignEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSignEdit window

class CSignEdit : public CEdit
{
// Construction
public:
	CSignEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSignEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSignEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGNEDIT_H__E42C869B_8178_452E_BA85_51850C709A49__INCLUDED_)
