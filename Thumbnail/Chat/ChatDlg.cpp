// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
#include "UserInfoDlg.h"
#include "SendToAllDlg.h"
#include  "WinXPButtonST.h"
#include "MacDlg.h"
#include "ChessDlg.h"
#include "ChoiceKindDlg.h"
#include "afxwin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#define WM_MYMESSAGE WM_USER+30


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
/*
UINT ReceiveThread(LPVOID lpParam)
{
	HWND handle= (HWND)lpParam;
	CChatDlg *dlg = (CChatDlg *)handle;
	return 0;

}
*/
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CWinXPButtonST m_bu;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_bu);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChatDlg 对话框



CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	pdlg = NULL;
	hidenflag = true;
	//m_hIcon = AfxGetApp()->LoadIcon(IDB_BITMAP3);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listctrl);
	DDX_Control(pDX, IDC_BUTTON1, m_menu);
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	ON_WM_CTLCOLOR()

	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnNMDblclkList2)
//	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_HOTKEY,OnHotKey) 
//	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnNMRclickList2)
ON_COMMAND(ID_140, On140)
ON_COMMAND(ID_149, OnDeleteUser)
ON_COMMAND(ID_147, OnAddUser)
ON_COMMAND(ID_150, On150)
ON_COMMAND(ID_148, OnSendToAll)
ON_COMMAND(ID_167, OnAbort)
ON_COMMAND(ID_169, OnMac)
ON_COMMAND(ID_172, OnChess)
END_MESSAGE_MAP()


// CChatDlg 消息处理程序

BOOL CChatDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();
	RegisterHotKey(m_hWnd,1001,MOD_CONTROL,'Q'); 
	RegisterHotKey(m_hWnd,1002,MOD_CONTROL,'q'); 
	//RegisterHotKey(m_hWnd,1003,MOD_CONTROL,'q');
	RegisterHotKey(m_hWnd,1003,MOD_CONTROL,13); 
	
	SetWindowText("梦聊");

	
	

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO：在此添加额外的初始化代码

	m_menu.SetRounded(true,true);

//对richedit的初始化
	AfxInitRichEdit( );

	//创建imagelist
	m_imagelist.Create(32,32,ILC_COLOR32|ILC_MASK,15,2);
	CBitmap bm[15];
	bm[0].LoadBitmap(IDB_BITMAP1);	
	bm[1].LoadBitmap(IDB_BITMAP2);
	bm[2].LoadBitmap(IDB_BITMAP3);
	bm[3].LoadBitmap(IDB_BITMAP4);	
	bm[4].LoadBitmap(IDB_BITMAP5);
	bm[5].LoadBitmap(IDB_BITMAP6);
	bm[6].LoadBitmap(IDB_BITMAP7);	
	bm[7].LoadBitmap(IDB_BITMAP8);
	bm[8].LoadBitmap(IDB_BITMAP9);
	bm[9].LoadBitmap(IDB_BITMAP10);	
	bm[10].LoadBitmap(IDB_BITMAP11);
	bm[11].LoadBitmap(IDB_BITMAP12);
	bm[12].LoadBitmap(IDB_BITMAP13);	
	bm[13].LoadBitmap(IDB_BITMAP14);
	bm[14].LoadBitmap(IDB_BITMAP15);
	m_imagelist.Add(&bm[0], RGB(0, 0, 0));
	m_imagelist.Add(&bm[1], RGB(0, 0, 0));
	m_imagelist.Add(&bm[2], RGB(0, 0, 0));
	m_imagelist.Add(&bm[3], RGB(0, 0, 0));
	m_imagelist.Add(&bm[4], RGB(0, 0, 0));
	m_imagelist.Add(&bm[5], RGB(0, 0, 0));
	m_imagelist.Add(&bm[6], RGB(0, 0, 0));

	m_imagelist.Add(&bm[7], RGB(0, 0, 0));
	m_imagelist.Add(&bm[8], RGB(0, 0, 0));
	m_imagelist.Add(&bm[9], RGB(0, 0, 0));
	m_imagelist.Add(&bm[10], RGB(0, 0, 0));
	m_imagelist.Add(&bm[11], RGB(0, 0, 0));
	m_imagelist.Add(&bm[12], RGB(0, 0, 0));

	m_imagelist.Add(&bm[13], RGB(0, 0, 0));
	m_imagelist.Add(&bm[14], RGB(0, 0, 0));

	m_listctrl.SetImageList(&m_imagelist, LVSIL_NORMAL);


	//初始化接收消息的socket
	m_socket.SetHWnd((HWND)this);
	if(m_socket.Create(1600,SOCK_DGRAM,FD_READ|FD_WRITE,NULL)==SOCKET_ERROR)
	{
		AfxMessageBox("创建套接字失败");
	}


//读取配置文件，读用户信息到userlist中
	CString filename;
	filename = "user\\user.ini";
	CFileFind filefind;
	if ( filefind.FindFile(filename,0) )
	{
		int  usercount;
		usercount = GetPrivateProfileInt(_T("usercount"), _T("count"),0, filename);

		if ( usercount != 0 )
		{
			for (int i = 0 ; i < usercount; i++)
			{
				CString sectionname;
				sectionname.Format("section%d",i+1);
				CString name,ip;
				int imageid;
				GetPrivateProfileString(sectionname, _T("name"),
					_T("QQ"), name.GetBuffer(MAX_PATH),
					MAX_PATH, filename);
				name.ReleaseBuffer ();

				GetPrivateProfileString(sectionname, _T("ip"),
					_T("192.168.0.0"), ip.GetBuffer(MAX_PATH),
					MAX_PATH, filename);
				ip.ReleaseBuffer ();

				imageid = GetPrivateProfileInt (sectionname, _T("imageid"),
							1, filename);
				user muser;
				muser.name = name;
				muser.ID = i;
				muser.ip = ip ;
				muser.Iimage = imageid;
				muser.inicount = i + 1;
				m_userlist.AddTail(muser);

				CString strname = name + "(不在线)";
				m_listctrl.InsertItem(i,strname,imageid);
				m_listctrl.SetItemData(i,muser.ID);
				CString onlineinfo = "onlineonline" ;
				m_socket.SendTo(onlineinfo,onlineinfo.GetLength(),1600,muser.ip ,0);

			}
		}
		
		

	}


	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}

HBRUSH CChatDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	
	HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
	return br;

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return hbr;
}


//双击列表中的图标处理事件
void CChatDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//找到别点击的图标在列表控件中的位置
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	int nItem = m_listctrl.GetNextSelectedItem(pos);
	//CString name=m_listctrl.GetItemText(nItem,0);
	if (nItem == -1)
	{
		return;
	}
	int  id  = m_listctrl.GetItemData(nItem);
	//找到该姓名在结构中的位置
   POSITION pos1;
	user *muser;
	pos1 = m_userlist.GetHeadPosition();
	while ( pos1 != NULL )
	{
		muser = &m_userlist.GetNext (pos1);
		if ( muser->ID ==  id)
		{
			break;
		}
	}

	if ( muser->ID == -1)
	{
		MessageBox("没有找到");
		return;
	}

	if (muser->pdlg == NULL)
	{
		muser->pdlg = new CMyDialog(muser->name,this);
		muser->pdlg->ip = muser->ip;
		muser->pdlg->Iimage = muser->Iimage ;
		muser->pdlg->Create(IDD_DIALOG1,this);
		muser->pdlg->ShowWindow(SW_SHOW);
	}
	if (!muser->pdlg->IsWindowVisible())
	{
		muser->pdlg->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}

//void CChatDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}

void CChatDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	 
	 
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU2));
		CPoint point;

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();
		::GetCursorPos(&point);
		pPopup->TrackPopupMenu( TPM_RIGHTALIGN  , point.x, point.y,
			pWndPopupOwner);
	
	
	
}

void CChatDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//重写配置文件
	/*
	if(MessageBox("确定退出QQ吗?", "提示", MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}*/
//保存用户信息到ini文件中
	CString filename;
		filename = "user\\user.ini";
		CFileFind filefind;
		if ( filefind.FindFile(filename,0) )//找到文件
		{
			CFile::Remove(filename);
		}
		CFile file;
		file.Open(filename,CFile::modeCreate | CFile::modeWrite,NULL);
		file.Close();
		if ( filefind.FindFile(filename,0) )

		{
			int  usercount =m_userlist.GetCount();
			CString tempcount;
			tempcount.Format("%d",usercount);
			
			WritePrivateProfileString(_T("usercount"),_T("count"),tempcount,filename);
			POSITION pos = m_userlist.GetHeadPosition();
			CString sectionname;
			int count = 0;
			while ( pos != NULL )
			{
				user muser = m_userlist.GetAt(pos);
				sectionname.Format("section%d",count+1);
				WritePrivateProfileString(sectionname, _T("name"),
									      muser.name  , filename);
				WritePrivateProfileString(sectionname, _T("ip"),
									muser.ip  , filename);
				CString strid;
				strid.Format("%d",muser.Iimage);
				WritePrivateProfileString(sectionname, _T("imageid"),
						                  strid  , filename);

				CString buf = "downlinedownline" ;
				m_socket.SendTo(buf,buf.GetLength(),1600,muser.ip );
				count++;
				m_userlist.GetNext (pos);

			}
		
		}
		//释放资源
	m_userlist.RemoveAll();
	m_socket.Close();
	UnregisterHotKey(m_hWnd, 1001); 
	UnregisterHotKey(m_hWnd, 1002); 
	UnregisterHotKey(m_hWnd, 1003); 
	CDialog::OnCancel();

	
}

//void CChatDlg::OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}



//右键菜单更改用户信息
void CChatDlg::On140()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	int i,nItem = m_listctrl.GetNextSelectedItem(pos);
	CString name=m_listctrl.GetItemText(nItem,0);

	POSITION pos1;
	user *muser;
	pos1 = m_userlist.GetHeadPosition();
	while ( pos1 != NULL )
	{
		muser = &m_userlist.GetNext (pos1);
		if ( muser->ID ==  nItem)
		{
			break;
		}
	}

	if ( muser->ID == -1)
	{
		MessageBox("没有找到");
		return;
	}

	
	
	
	CUserInfoDlg dlg;
	dlg.m_name  = muser->name;
	dlg.ip = muser->ip;
	dlg.m_curentimage = muser->Iimage ;
	
	if (dlg.DoModal() == IDOK )
	{
		muser->name = dlg.m_name;
		muser->ip = dlg.ip ;
		if (muser->pdlg == NULL)
		{
			muser->pdlg = new CMyDialog(name,this);
			muser->pdlg->ip = muser->ip;
			muser->pdlg->Create(IDD_DIALOG1,this);
		}
		muser->pdlg->ip = dlg.ip ;
		muser->pdlg->m_name = dlg.m_name;
		muser->Iimage = dlg.m_curentimage  ;
		muser->pdlg->Iimage = muser->Iimage ;
		CString strbmp;
		int flag = muser->Iimage + 1;
		strbmp.Format("face//%d.bmp",flag);

		HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,strbmp,IMAGE_BITMAP,0,0,
											LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
		muser->pdlg->m_image.SetBitmap(hbitmap);

		muser->pdlg->SetWindowText("与"+dlg.m_name+"聊天中");

	//分解ＩＰ
		char iptemp[4][4];
		for (int i=0;i<4;i++)
		{
			memset(iptemp[i],'\0',4);
		}
		CString s = dlg.ip;
		char *temp = s.GetBuffer();
		char *p1=strstr(temp,".");
		*p1='\0';
		strcpy(iptemp[0],temp);
		temp = p1 + 1;

		p1=strstr(temp,".");
		*p1='\0';
		strcpy(iptemp[1],temp);
		temp = p1 + 1;

		p1=strstr(temp,".");
		*p1='\0';
		strcpy(iptemp[2],temp);
		temp = p1 + 1;

		strcpy(iptemp[3],temp);
		int ipint[4];
		for ( i=0; i < 4; i++ )
		{
			ipint[i] = atoi(iptemp[i]);
		}
		muser->pdlg->m_ip.SetAddress( ipint[0],ipint[1],ipint[2],ipint[3] );

		
		LV_ITEM item;
		item.mask = LVIF_IMAGE|LVIF_TEXT;
		item.iItem = nItem;
		item.iSubItem = 0;
		item.pszText = muser->name.GetBuffer(muser->name.GetLength());
		item.cchTextMax = muser->name.GetLength();
		item.iImage = muser->Iimage ;
		m_listctrl.SetItem(&item);
	}//ifok
		
		

}
//收到socket信息
void CChatDlg::OnReceive()
{
	
	char strrev[1024];
	memset(strrev,'\0',1024);
	int nresult;
	UINT port;	
	CString ipstr;

	nresult=m_socket.ReceiveFrom(strrev,sizeof(strrev),ipstr,port);


	if ( (nresult != SOCKET_ERROR) )
	{
		
		
		POSITION pos1;
		user *pmuser;
		pos1 = m_userlist.GetHeadPosition();
		while ( pos1 != NULL )
		{
			pmuser = &m_userlist.GetNext (pos1);
			if( pmuser->ip == ipstr)
			{
				break;
			}
		}

		if ( pmuser->ID == -1)
		{
			return;
		}
		//是上线信息
		CString onlineflag = strrev;
		if (onlineflag == "1234567890mmm")
		{
			for (int i = 0 ;i < m_listctrl.GetItemCount() ; i++ )
			{
				int id_data = m_listctrl.GetItemData(i);
				if ( pmuser->ID == id_data)
				{
					CString str = pmuser->name +"(在线)";
					m_listctrl.SetItemText(i,0,str);
					return;
				}
			}
		}
		if ( onlineflag ==  "onlineonline")
		{
			CString temp ;
			temp ="你的好友" +pmuser->name + "上线了哦";
			//dlg.DoModal();
			if (pdlg == NULL)
			{
				pdlg = new CInformDlg(this);
				pdlg->Create (IDD_DIALOG4,this);
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}
			
			if ( !pdlg->IsWindowVisible() )
			{
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}

			for (int i = 0 ;i < m_listctrl.GetItemCount() ; i++ )
			{
				int id_data = m_listctrl.GetItemData(i);
				if ( pmuser->ID == id_data)
				{
					CString str = pmuser->name +"(在线)";
					m_listctrl.SetItemText(i,0,str);
					//return;
				}
			}
			
			CString send = "1234567890mmm";
			m_socket.SendTo(send,send.GetLength(),1600,pmuser->ip ,0);
			return;
		}
		if (onlineflag == "downlinedownline")
		{
			CString temp ;
			temp = "你的好友"+pmuser->name + "已经下线了";
			if (pdlg == NULL)
			{
				pdlg = new CInformDlg(this);
				pdlg->Create (IDD_DIALOG4,this);
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}
			
			if ( !pdlg->IsWindowVisible() )
			{
				pdlg->SetWindowText(temp);
				CPoint point(700,500);
				pdlg->ClientToScreen(&point);
				pdlg->CenterWindow(this);
				pdlg->ShowWindow(SW_SHOW);
			}
			
			for (int i = 0 ;i < m_listctrl.GetItemCount() ; i++ )
			{
				int id_data = m_listctrl.GetItemData(i);
				if ( pmuser->ID == id_data)
				{
					CString str = pmuser->name +"(不在线)";
					m_listctrl.SetItemText(i,0,str);
					return;
				}
			}

			return;
		}

		if (pmuser->pdlg == NULL)
		{
			pmuser->pdlg = new CMyDialog(pmuser->name,this);
			pmuser->pdlg->ip = pmuser->ip;
			pmuser->pdlg->Create(IDD_DIALOG1,this);
			pmuser->pdlg->ShowWindow(SW_SHOW);
		}
		if (!pmuser->pdlg->IsWindowVisible())
		{
			pmuser->pdlg->ShowWindow(SW_SHOW);
		}
		CString temp;
		pmuser->pdlg->m_send.GetWindowText(temp);
		if ( temp != "回信息")
		{
			pmuser->pdlg->m_edit.GetWindowText(pmuser->pdlg->info);
		}
		CString str = strrev;
		CTime t=CTime::GetCurrentTime();
		CString m_time = t.Format("%Y-%m-%d %H:%M");
		pmuser->pdlg->m_listbox.InsertString(0,pmuser->name+"对你说: "+str+"  "+m_time );
		pmuser->pdlg->m_edit.SetWindowText(str);
		pmuser->pdlg->m_edit.EnableWindow(false);
		pmuser->pdlg->m_send.SetWindowText("回信息");
		pmuser->pdlg->SetForegroundWindow();
		
	}
	
	
}
//删除好友
void CChatDlg::OnDeleteUser()
{
	// TODO: 在此添加命令处理程序代码

	POSITION pos = m_listctrl.GetFirstSelectedItemPosition();
	int nItem = m_listctrl.GetNextSelectedItem(pos);
	if (nItem < 0)
	{
		return;
	}
	int id=(int)m_listctrl.GetItemData(nItem);
	m_listctrl.DeleteItem(nItem);
	POSITION pos1;
	user *muser;
	pos1 = m_userlist.GetHeadPosition();
	//muser = &m_userlist.GetAt(pos1);
	while ( pos1 != NULL )
	{
		muser = &m_userlist.GetNext (pos1);
		if ( muser->ID ==  id)
		{
			if(pos1  == NULL )
			{
				pos1 = m_userlist.GetTailPosition();
			}
			else
			{
				 m_userlist.GetPrev(pos1);
			}
			 m_userlist.RemoveAt(pos1) ; 
			break;
		}
		
	}

	if ( muser->ID == -1)
	{
		MessageBox("没有找到");
		return;
	}

}
//添加好友
void CChatDlg::OnAddUser()
{
	// TODO: 在此添加命令处理程序代码
	CUserInfoDlg dlg;
	dlg.m_name = "昵称";
	dlg.ip = "192.168.0.0";
	if (dlg.DoModal() == IDOK )
	{
		user muser ;
		int id = m_listctrl.GetItemCount();
		m_listctrl.InsertItem(id,dlg.m_name,dlg.m_curentimage );
		m_listctrl.SetItemData(id,id);
		muser.ID =id;
		muser.name = dlg.m_name ;
		muser.ip = dlg.ip ;
		muser.Iimage = dlg.m_curentimage ;
		m_userlist.AddTail(muser);
	
	}
}
//增加用户
void CChatDlg::On150()
{
	OnAddUser();
}
//消息群发
void CChatDlg::OnSendToAll()
{
	// TODO: 在此添加命令处理程序代码
	CSendToAllDlg dlg;
	CString strsend;
	if (dlg.DoModal() == IDOK )
	{
		strsend = dlg.m_str;
	
		POSITION pos = m_userlist.GetHeadPosition();
		CAsyncSocket * psocket = new CAsyncSocket;
		if ( psocket->Create(1601,SOCK_DGRAM,FD_READ|FD_WRITE,NULL) ==SOCKET_ERROR)
		{
			AfxMessageBox("创建套接字失败");
			delete psocket;
			return;
		}
	
		while ( pos != NULL )
		{
			 user tempuser = m_userlist.GetAt(pos);
			int result = psocket->SendTo(strsend,strsend.GetLength(),1600,tempuser.ip);
		
			if ( result == SOCKET_ERROR)
			{
				CString temp ;
				temp = "发送给" + tempuser.name + "消息失败";
				MessageBox(temp,"发送失败提示",MB_OK);
			//delete psocket;
			//return;
			}
		
			m_userlist.GetNext(pos);
		
		}
		psocket->Close();
		delete psocket;
	}
}
//捕获热键
LRESULT CChatDlg::OnHotKey(WPARAM wParam,LPARAM lParam) 
{
	if (wParam == 1001||wParam == 1002)
	{
		if (hidenflag == true )
		{
			m_forhwd =::GetForegroundWindow();
			::ShowWindow(m_forhwd,SW_HIDE);
			ShowWindow(SW_HIDE);
			hidenflag = false ;
		}
		else
		{
			this->ShowWindow(SW_SHOW);
			::ShowWindow(m_forhwd,SW_SHOW);
			hidenflag = true;
			
		}

	}
	if (wParam == 1003)
	{
		HWND m_hhwd =::GetForegroundWindow();
		
		::SendMessage(m_hhwd,WM_MYMESSAGE,0,0);
		
	}
	return 0;
}

void CChatDlg::OnAbort()
{
	// TODO: 在此添加命令处理程序代码
	
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
  pDC->SetBkMode(TRANSPARENT);
	HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
	return br;
	//return hbr;
}



//重载onok
void CChatDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}
//重载oncancel
void CChatDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}
//扫描Ｍａｃ地址
void CChatDlg::OnMac()
{
	// TODO: 在此添加命令处理程序代码
	CMacDlg dlg;
	dlg.DoModal();

}

void CChatDlg::OnChess()
{
	// TODO: 在此添加命令处理程序代码
	CChoiceKindDlg kdlg;
	if ( kdlg.DoModal() == IDOK )
	{
			CChessDlg dlg;
		if ( kdlg.machine == true )
		{
			dlg.m_and_p_flag  = true;
			
		}
		dlg.DoModal();
	}
	

	

}
