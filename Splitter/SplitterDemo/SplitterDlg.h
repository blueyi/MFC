// SplitterDlg.h : ヘッダー ファイル
//

#if !defined(AFX_SPLITTERDLG_H__4EEC3C5F_57EC_4FDD_B7DE_7161B9445A7B__INCLUDED_)
#define AFX_SPLITTERDLG_H__4EEC3C5F_57EC_4FDD_B7DE_7161B9445A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControlSplitter.h"
/////////////////////////////////////////////////////////////////////////////
// CSplitterDlg ダイアログ

class CSplitterDlg : public CDialog
{
// 構築
public:
	CSplitterDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSplitterDlg)
	enum { IDD = IDD_SPLITTER_DIALOG };
	CControlSplitter	m_splitter3;
	CControlSplitter	m_splitter2;
	CControlSplitter	m_splitter;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSplitterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSplitterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SPLITTERDLG_H__4EEC3C5F_57EC_4FDD_B7DE_7161B9445A7B__INCLUDED_)
