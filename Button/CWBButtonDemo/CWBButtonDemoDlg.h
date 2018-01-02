// CWBButtonDemoDlg.h : ヘッダー ファイル
//

#if !defined(AFX_CWBBUTTONDEMODLG_H__518122C7_358F_11D4_8F4F_00402656D980__INCLUDED_)
#define AFX_CWBBUTTONDEMODLG_H__518122C7_358F_11D4_8F4F_00402656D980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WBButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCWBButtonDemoDlg ダイアログ

class CCWBButtonDemoDlg : public CDialog
{
// 構築
public:
	CCWBButtonDemoDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CCWBButtonDemoDlg)
	enum { IDD = IDD_CWBBUTTONDEMO_DIALOG };
	CWBButton	m_btn6;
	CWBButton	m_btn5;
	CWBButton	m_btn4;
	CWBButton	m_btn3;
	CWBButton	m_btn2;
    CWBButton	m_btn;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCWBButtonDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCWBButtonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CWBBUTTONDEMODLG_H__518122C7_358F_11D4_8F4F_00402656D980__INCLUDED_)
