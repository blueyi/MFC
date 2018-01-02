#pragma once
#include "afxcmn.h"
#include "MySocket.h"
#include "afxwin.h"
#include "WinXPButtonST.h"
// CMyDialog 对话框
#define WM_MYMESSAGE WM_USER+100

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(CString name,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDialog();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOK();
	afx_msg void OnBnClickedButton3();
	CRichEditCtrl m_edit;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton2();
private:
	
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CIPAddressCtrl m_ip;
	CString ip;
	CMySocket m_socket;
	int m_port;
//	afx_msg void OnBnClickedButton4();
	void OnReceive();
	CListBox m_listbox;
	afx_msg void OnClose();
	CStatic m_image;
	CString m_name;
	CString info;
	CWinXPButtonST m_send;
	CWinXPButtonST m_close;
	int Iimage;
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CWinXPButtonST m_button3;
	CStatic m_static1;
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CStatic m_static2;
	bool show;
	afx_msg void OnDestroy();
	afx_msg LRESULT OnMyMessage(WPARAM wParam,LPARAM lParam);
};
