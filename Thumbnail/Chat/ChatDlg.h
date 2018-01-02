// ChatDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyListCtrl.h"
#include "MyDialog.h"
#include "afxcmn.h"
#include "afxtempl.h"
#include "MySocket.h"
#include "WinXPButtonST.h"
#include "InformDlg.h"
// CChatDlg 对话框
class  user
{
public:
	user( ):name(""),pdlg(NULL),ip(""),ID(-1),Iimage(-1),inicount(-1)
	{
	};
	user(const user & u)
	{
		/*
		if ( u.pdlg != NULL)
		{
			pdlg = new CMyDialog(u.pdlg->m_name);
		}
		else
		{
			
		}
		*/
		pdlg = NULL;
		name = u.name ;
		ip =  u.ip ;
		ID = u.ID ;
		Iimage = u.Iimage;
		inicount= u.inicount ;
	}
	user & operator =(const user & u)
	{
		if ( this != &u)
		{
			/*
			if ( u.pdlg != NULL)
			{
				pdlg = new CMyDialog(u.pdlg->m_name);
			}
			else
			{
				pdlg = NULL;
			}
			*/
			pdlg = NULL;
			name = u.name ;
			ip =  u.ip ;
			ID = u.ID ;
			Iimage = u.Iimage;
			inicount = u.inicount ;
			}
			return *this;
		}
	~user()
	{
		if( pdlg != NULL)
		{
			delete pdlg;
		}
	};
	CString name;
	CMyDialog *pdlg;
	CString ip;
	int ID;
	int Iimage;
	int inicount;

};
class CChatDlg : public CDialog
{
// 构造
public:
	CChatDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_listctrl;
	CImageList m_imagelist;
	CMyDialog  *pDialog;
	CMySocket m_socket;
	CInformDlg *pdlg;
	CList <user,user&> m_userlist;
	HWND m_forhwd;
	bool hidenflag;
	afx_msg void OnLbnSelchangeList1();
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
//	afx_msg void OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On140();

	void OnReceive();
	CWinXPButtonST m_menu;
	afx_msg void OnDeleteUser();
	afx_msg void OnAddUser();
	afx_msg void On150();
	afx_msg void OnSendToAll();
	afx_msg void OnAbort();
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam); 
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnMac();
	afx_msg void OnChess();
	
};
