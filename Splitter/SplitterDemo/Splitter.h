// Splitter.h : SPLITTER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SPLITTER_H__78A12252_2545_47FA_86E7_B7C04C16D66D__INCLUDED_)
#define AFX_SPLITTER_H__78A12252_2545_47FA_86E7_B7C04C16D66D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CSplitterApp:
// このクラスの動作の定義に関しては Splitter.cpp ファイルを参照してください。
//

class CSplitterApp : public CWinApp
{
public:
	CSplitterApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSplitterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CSplitterApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SPLITTER_H__78A12252_2545_47FA_86E7_B7C04C16D66D__INCLUDED_)
