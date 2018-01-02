// CWBButtonDemo.h : CWBBUTTONDEMO アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_CWBBUTTONDEMO_H__518122C5_358F_11D4_8F4F_00402656D980__INCLUDED_)
#define AFX_CWBBUTTONDEMO_H__518122C5_358F_11D4_8F4F_00402656D980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CCWBButtonDemoApp:
// このクラスの動作の定義に関しては CWBButtonDemo.cpp ファイルを参照してください。
//

class CCWBButtonDemoApp : public CWinApp
{
public:
	CCWBButtonDemoApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCWBButtonDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CCWBButtonDemoApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CWBBUTTONDEMO_H__518122C5_358F_11D4_8F4F_00402656D980__INCLUDED_)
