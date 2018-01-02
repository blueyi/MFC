

#include "stdafx.h"
#include "Chat.h"
#include "ChessDlg.h"
#include "SetNetDlg.h"
#include "SocketThread.h"

#define DEEP  3
// CChessDlg 对话框
/*
CChessDlg * ppdlg;
UINT ListenThread(LPVOID lpParam)
{
	ppdlg->SetWindowText("正在监听网络连接");
	
	ppdlg->m_socket.Listen(1) ;
	

}
*/
IMPLEMENT_DYNAMIC(CChessDlg, CDialog)
CChessDlg::CChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChessDlg::IDD, pParent)
{
	for (int i = 0 ;i < 20 ; i++ )
		for (int j=0;j<20;j++ )
			Fivearray[i][j] = 0;
	is_myturn = false;
	set_netflag = false;
	is_connect = false;
	m_and_p_flag = false;
	
}

CChessDlg::~CChessDlg()
{
	m_socket.Close();
	m_socket.ShutDown(2);

	m_con_socket.Close();
	m_con_socket.ShutDown(2);
	StepList.RemoveAll();
	for (int i = 0 ;i < 20 ; i++ )
		for (int j=0;j<20;j++ )
			Fivearray[i][j] = 0;
}

void CChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC2, m_smain);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Control(pDX, IDC_BUTTON4, bt1);
	DDX_Control(pDX, IDC_BUTTON3, bt2);
	DDX_Control(pDX, IDC_BUTTON5, bt3);
	DDX_Control(pDX, IDC_BUTTON2, bt4);
	DDX_Control(pDX, IDC_BUTTON6, bt5);
	DDX_Control(pDX, IDC_BUTTON7, bt7);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
}


BEGIN_MESSAGE_MAP(CChessDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()

	ON_BN_CLICKED(IDC_BUTTON2, OnRegret)
	ON_BN_CLICKED(IDC_BUTTON3, OnNet)
	ON_MESSAGE(WAS_ACCEPT,OnMyMessage)
	ON_BN_CLICKED(IDC_BUTTON5, OnSendMessage)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, OnMachineAndPeson)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChessDlg 消息处理程序

BOOL CChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//ShowWindow(SW_MAXIMIZE);
	CRect rc ;
	m_smain.GetClientRect(&rc);
	

	int x = rc.right  ;
	int y = rc.bottom  ;
	
	 step_x = (x)/20 ;
	 step_y = (y)/20;

	if ( m_and_p_flag == true )
	{
		bt2.EnableWindow(false);
		m_combox.SetCurSel(0);
		is_myturn = true;
		SetWindowText("五子棋（人机对战）");
		//Fivearray[10][10] = 3 ;
		SetTimer(1,500,0);
		return true;
	}
	bt1.EnableWindow(false);
	m_con_socket.SetHwnd((HWND)this);
	m_socket.SetHwnd((HWND)this);
	 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

HBRUSH CChessDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	pDC->SetBkMode(TRANSPARENT);
	if (nCtlColor !=  CTLCOLOR_EDIT &&  nCtlColor !=  CTLCOLOR_LISTBOX) 
		hbr = ::CreateSolidBrush(RGB(128,128,200));
	return hbr;
}

void CChessDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	DrawGrid();
	DrawAllChess();
	
}
void CChessDlg::DrawGrid()
{
	CDC *pdc = m_smain.GetDC();
	CRect rc ;
	m_smain.GetClientRect(&rc);
	int x = rc.right  ;
 	int y = rc.bottom  ;
    int i;
	
	int xx = rc.left ;
	int yy = rc.top+6 ;
	//画竖线
	for (int i = 0 ; i < 21; i++ )
	{
		pdc->MoveTo(xx,yy);
		pdc->LineTo(xx,y);
		xx += step_x ;
	}
	
	xx = rc.left ;
    yy = rc.top +6;
	//画横线
	for ( i = 0 ; i < 20 ; i++ )
	{
		pdc->MoveTo(xx,yy);
		pdc->LineTo(x,yy);
		yy += step_y ;
	}
	
	
}
//鼠标左键事件
void CChessDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值　
	
	CDialog::OnNcLButtonDblClk(nHitTest, point);
}

void CChessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( m_and_p_flag == true  )
	{
		if ( is_myturn == true)
		{
			is_myturn = false;
			DrawChess(point);
			if ( IsSuccess()|| is_myturn == true)
				return ;
			//初级
			if ( m_combox.GetCurSel() == 0 )
			{
				Step st;
				if (SearchValue(Fivearray,st,true) != 100000)
				    SearchMaxValue(st,Fivearray);
				st.side = 3;
				Fivearray[st.x][st.y] = 3;
				StepList.AddTail(st);
				DrawChess(st.x,st.y,false);
				m_currentstep.x = st.x;
				m_currentstep.y = st.y;
				//Invalidate();
			}
			//高级
			else
			{
				
				Step st;
				int score = SearchMaxValue(st,Fivearray);
				if ( score >=  1000 || score <= 20 )
				{
					st.side = 3;
					Fivearray[st.x][st.y] = 3;
					StepList.AddTail(st);
					DrawChess(st.x,st.y,false);
					m_currentstep.x = st.x;
					m_currentstep.y = st.y;
					//Invalidate();
				}
				else
				{
				


				GameStatus temp;
				for (int i = 0 ; i < 20 ; i++)
				for (int jj = 0 ; jj< 20 ;jj++)
					temp.fivearray[i][jj] = Fivearray[i][jj];
				temp.deep = 0;
				temp.is_machine = true ;
				temp.score = 0;

				Step st1;
				Step st2;
				//机器方下得分
				int score1 = DeepSearch(temp,st1,true,0);
				//换人方下得分
				int score2 = DeepSearch(temp,st2,false,0);
				
				if ( score1 > score2 )
				{
					st1.side = 3;
					Fivearray[st1.x][st1.y] = 3;
					StepList.AddTail(st1);
					DrawChess(st1.x,st1.y ,false);
					m_currentstep.x = st1.x;
					m_currentstep.y = st1.y;
					//Invalidate();
				}
				
				if ( score1 < score2 )
				{
					st2.side = 3;
					Fivearray[st2.x][st2.y] = 3;
					StepList.AddTail(st2);
					DrawChess(st2.x,st2.y,false );
					m_currentstep.x = st2.x;
					m_currentstep.y = st2.y;
					//Invalidate();

				}

				if ( score1 == score2 )
				{
					if ( st1.deep <= st2.deep )
					{
						st1.side = 3;
						Fivearray[st1.x][st1.y] = 3;
						StepList.AddTail(st1);
						DrawChess(st1.x,st1.y,false);
						m_currentstep.x = st1.x;
						m_currentstep.y = st1.y;
						//Invalidate();
					}
					else
					{
						st2.side = 3;
						Fivearray[st2.x][st2.y] = 3;
						StepList.AddTail(st2);
						DrawChess(st2.x,st2.y,false );
						m_currentstep.x = st2.x;
						m_currentstep.y = st2.y;
						//Invalidate();
					}
				}



				}
			}
			if (! IsSuccess())
			{
				is_myturn = true;
			}
		}
			
		return;
	}
	if (set_netflag == false)
	{
		MessageBox("你还未设置网络，如要网络对战，请点网络对战按钮","友情提示",MB_OK);
		return ;
	}
	if ( is_connect == false)
	{
		MessageBox("没有网络连接","友情提示",MB_OK);
		return;
	}
	if ( is_myturn == false)
	{
		MessageBox("别急别急，对方还没下呢","友情提示",MB_OK);
		return;
		
	}
	DrawChess(point);
	

	CDialog::OnLButtonDown(nFlags, point);
}
//画棋子
void CChessDlg::DrawChess (CPoint point)
{
	
	int x = point.x -12;
	int y = point.y-18  ;
	int linex  = y / step_y;
	int liney = x / step_x ;
	if (  (y - linex * step_y) >  (step_y/2) )
	{
		linex++;
	}
	if (  (x - liney * step_x) >  (step_x/2) )
	{
		liney++;
	}
	CDC * pdc = m_smain.GetDC();
	if ( linex <= 0 || linex >= 20 || liney <= 0 || liney >= 20||Fivearray[linex][liney] != 0 )
	{
		is_myturn = true;
		return ;
	}

	is_myturn = false;
	Fivearray[linex][liney] = 1;
	Step tstep;
	tstep.side = 1;
	tstep.x = linex;
	tstep.y = liney;
	StepList.AddTail(tstep);
	pdc->SelectStockObject(BLACK_BRUSH);
	//pdc->SelectStockObject(WHITE_PEN);
	pdc->Ellipse(liney*step_x-10,linex*step_y-10+6,liney * step_x +10,linex * step_y +10+6);
	//pdc->Rectangle(liney*step_x-10,linex*step_y-10+6,liney * step_x +10,linex * step_y +10+6);
	if ( m_and_p_flag != true )
	{
		CString ms;
		ms.Format("*****%d*****%d*****",linex,liney);
		m_con_socket.Send(ms,ms.GetLength(),0);
		IsSuccess();
	}
	
	
}
void CChessDlg::DrawChess (int linex ,int liney,bool is_current= false)
{
	CDC * pdc = m_smain.GetDC();
	if (Fivearray[linex][liney] == 0)
		return;
	if ( Fivearray[linex][liney] == 1 )
	{
		pdc->SelectStockObject(BLACK_BRUSH);
	}
	else 
	{
		pdc->SelectStockObject(WHITE_BRUSH);
	}
	if ( is_current == true)
	{
		CBrush br(RGB(211,198,244));
		pdc->SelectObject(br);
		pdc->Ellipse(liney*step_x-10,linex*step_y-10+6,liney * step_x +10,linex * step_y +10+6);
	}
	else
	pdc->Ellipse(liney*step_x-10,linex*step_y-10+6,liney * step_x +10,linex * step_y +10+6);
	if ( m_and_p_flag != true )
	{
		IsSuccess();
	}
	
	

}
void CChessDlg::DrawAllChess()
{
	for (int i = 0 ; i <20 ; i++ )
		for (int j= 0; j<20 ; j++ )
		{
			if (Fivearray[i][j] != 0)
			{
				if ( m_currentstep.x == i && m_currentstep.y == j)
				{
					DrawChess(i,j,true);
				}
				else
					DrawChess(i,j);
			}

		}
}

//悔棋

void CChessDlg::OnRegret()
{
	// TODO: 在此添加控件通知处理程序代码
	if (StepList.GetCount() == 0 )
	{
		MessageBox("你一个子都没下，悔什么悔啊，别乱搞","提示",MB_OK);
		return;	
	}
	if ( m_and_p_flag == true  )
	 {
		 if ( StepList.GetCount() > 0)
		 {
			 Step tem = StepList.GetTail();
			 StepList.RemoveTail();
			 Fivearray[tem.x][tem.y] = 0 ;
			if ( StepList.GetCount() > 0)
			{
				 tem = StepList.GetTail();				
				if ( tem.side == 1 )
				{
					StepList.RemoveTail();
					Fivearray[tem.x][tem.y] = 0;
				}
			}
		 }
		Invalidate();
		if (  StepList.GetCount() > 0 )
		{
			Step tem = StepList.GetTail();
			m_currentstep = tem;
		}
		is_myturn = true ;
		return ;
		
		
	 }
	Step temp = StepList.GetTail();
	CString str = "regretregret";
	m_con_socket.Send(str,str.GetLength(),0);
	




		
}
//网络对战
void CChessDlg::OnNet()
{
	// TODO: 在此添加控件通知处理程序代码
	
	 
	CSetNetDlg dlg;
	if ( dlg.DoModal() ==IDOK)
	{
		if ( set_netflag == true )
	 {
		
		CString str = "------bybyebyebye";
		m_con_socket.Send(str,str.GetLength(),0);
		
		
		
	 }
		m_socket.Close();
		m_socket.ShutDown(2);
		m_con_socket.Close();
		m_con_socket.ShutDown(2);
		StepList.RemoveAll();
		for (int i = 0 ;i < 20 ; i++ )
			for (int j=0;j<20;j++ )
			Fivearray[i][j] = 0;
		Invalidate();
		is_connect = false;
		set_netflag = true ;
		int port = dlg.m_port;
		//服务器
		if ( dlg.checked_server  == true )
		{
			is_server = true;
			is_myturn = true;

			if (m_socket.Create(port,SOCK_STREAM,NULL) == SOCKET_ERROR )
			{
				AfxMessageBox("创建端口失败");
				return ;
			}
			
			
			SetWindowText("网络对战(正在等待连接)");
			m_socket.Listen(1) ;
			WSAAsyncSelect(m_socket,this->m_hWnd,WAS_ACCEPT,FD_ACCEPT|FD_READ);
		}

		else
		{
			is_server = false;
			is_myturn = false;
			
			m_con_socket.Create(5001,SOCK_STREAM);
			CString ip;
			ip = dlg.ip ;
			if ( m_con_socket.Connect(ip,port) == TRUE )
			{
				this->SetWindowText("连接"+ip+"成功");
				is_connect = true;
			}
			else
			{
				this->SetWindowText("连接"+ip+"失败");
				MessageBox("连接远端服务器失败，请检查网络","友情提示",MB_OK);
		
			}
		}
	}
	
	
}
void CChessDlg::OnReceive()
{
	char buf[1024];
	memset(buf,'\0',1024);
	m_con_socket.Receive(buf,sizeof(buf),0);

	if (	strstr(buf,"*****")	)
	{
		is_myturn = true;
		char *position1 = buf + 5 ;
		char *position2 = strstr(position1,"*****");
		char *position3 = position2 + 5 ;
		char *position4 = strstr(position3,"*****");
		*position4 = '\0';
		*position2 = '\0';
		int i = atoi(position1);
		int j = atoi(position3);
		Fivearray[i][j] = 2 ;
		Step tstep;
		tstep.side = 2;
		tstep.x = i;
		tstep.y = j;
		StepList.AddTail(tstep);
		DrawChess(i,j);

		return;
	}
	
	CString str = buf;
	if ( str == "overoveryouoverover")
	{
		MessageBox("你输了，结束战斗！","提示",MB_OK);
		StepList.RemoveAll();
		is_myturn = false;
		for (int i = 0 ;i < 20 ; i++ )
		for (int j=0;j<20;j++ )
			Fivearray[i][j] = 0;
		Invalidate();
		if ( MessageBox("继续玩吗？","友情提示",MB_YESNO) ==IDNO)
		{
			SetWindowText("五子棋");
			set_netflag = false;
			is_connect = false;
			CString str = "------bybyebyebye";
			m_con_socket.Send(str,str.GetLength(),0);

		}
		else
		{
			if (is_server == true)
			{
				is_myturn = true;
			}
		}
		
		return ;
	}
	if ( str =="regretregret" )
	{
		if ( MessageBox("    对方要求悔棋，你同意否？","悔棋",MB_YESNO) == IDYES )
		{
			is_myturn = false ;
			CString str_agree;
			str_agree = "agreeregrete";
			m_con_socket.Send(str_agree,str_agree.GetLength(),0);
			if ( StepList.GetCount() == 0)
			{
				return ;
			}
			Step st = StepList.GetTail();
			Fivearray[st.x][st.y] = 0;
			StepList.RemoveTail();
			if (StepList.GetCount() != 0)
			{
				st = StepList.GetTail();
				if ( st.side == 2 )
				{
					Fivearray[st.x][st.y] = 0;
					StepList.RemoveTail();
				}
			}
		}
		else
		{
			CString str_no = "++++++nonononon++++++";
			m_con_socket.Send(str_no,str_no.GetLength(),0);

		}
		Invalidate();
		return ;
	}
	if ( str == "agreeregrete")
	{
		
		is_myturn = true;
		Step st = StepList.GetTail();
		Fivearray[st.x][st.y] = 0;
		StepList.RemoveTail();
		if ( StepList.GetCount()  != 0 )
		{
			st = StepList.GetTail();
			if ( st.side == 1 )
			{
				Fivearray[st.x][st.y] = 0;
				StepList.RemoveTail();
			}
		}
		Invalidate();
		MessageBox("对方已同意悔棋","悔棋提示",MB_OK);
		return ;

	}
	if ( str == "++++++nonononon++++++")
	{
		MessageBox("对方未同意你悔棋情求","悔棋提示",MB_OK);
		return;
	}
	if ( str == "------bybyebyebye")
	{
		MessageBox("对方已经逃跑了","提示",MB_OK);
		is_myturn = false;
		set_netflag = false;
		is_connect = false;
		SetWindowText("五子棋");

		return;
	}
	m_listbox.AddString (str);
}
LRESULT CChessDlg::OnMyMessage(WPARAM wParam,LPARAM lParam)
{
	
	switch( lParam)
	{
		case FD_ACCEPT:
			if (m_socket.Accept(m_con_socket) )
			{
				CString ip;
				UINT port;
				m_con_socket.GetPeerName(ip,port);
				SetWindowText("网络对战(远端主机"+ip+"已连接)");
				is_connect = true;
			}
			break;
		case FD_READ:
			OnReceive();
			
			
	}
	
	
	return 0;
}



void CChessDlg::OnSendMessage()
{
	// TODO: 在此添加控件通知处理程序代码
	CString mssage ;
	m_edit.GetWindowText(mssage);
	m_con_socket.Send(mssage,mssage.GetLength(),0);
	m_edit.SetWindowText("");
}
bool  CChessDlg::IsSuccess()
{
	if ( m_and_p_flag == true )
	{
		if ( StepList.GetCount() == 0 )
		return false;
		Step temp = StepList.GetTail();
		int i = temp.x ;
		int j = temp.y ;
		int side = temp.side ;
		if ( LeftRight(i,j,side) == 5 || UpDown(i,j,side) == 5 
		 ||LupToRdown(i,j,side) == 5 || RuptoLdown(i,j,side)==5)
		{
			if ( side == 3 )
			{
				MessageBox("电脑胜利，结束战斗！","提示",MB_OK);
			}
			else
			{
				MessageBox("你胜利了，结束战斗！","提示",MB_OK);
			}
			/*
			StepList.RemoveAll();
			for (int i = 0 ;i < 20 ; i++ )
			for (int j=0;j<20;j++ )
				Fivearray[i][j] = 0;
				*/
			is_myturn = false;
			Invalidate();
			return true;
		}
		return false ;

	}
	if ( StepList.GetCount() == 0 )
		return false;
	Step temp = StepList.GetTail();
	int i = temp.x ;
	int j = temp.y ;
	int side = temp.side ;
	if ( side == 2 )
		return  false;
	if ( LeftRight(i,j,side) == 5 || UpDown(i,j,side) == 5 
		 ||LupToRdown(i,j,side) == 5 || RuptoLdown(i,j,side)==5)
	{
		MessageBox("胜利，结束战斗！","提示",MB_OK);
		StepList.RemoveAll();
		for (int i = 0 ;i < 20 ; i++ )
		for (int j=0;j<20;j++ )
			Fivearray[i][j] = 0;
		is_myturn = false;
		CString sendstr;
		sendstr = "overoveryouoverover";
		m_con_socket.Send(sendstr,sendstr.GetLength(),0);

		Invalidate();
		if ( MessageBox("继续玩吗？","友情提示",MB_YESNO) ==IDNO)
		{
			SetWindowText("五子棋");
			set_netflag = false;
			is_connect = false;
			CString str = "------bybyebyebye";
			m_con_socket.Send(str,str.GetLength(),0);

		}
		else
		{
			if (is_server == true)
			{
				is_myturn = true;
			}
		}

		return true;
	}
	return false;

}
int CChessDlg::LeftRight(int i, int j,int side)
{
	
	int tempi,count;
	tempi = i;
	count = 1;
	//toleft
	while ( --tempi > 0 && Fivearray[tempi][j] == side)
	{
		count ++;
	}
	tempi = i;
	while ( ++ tempi <20 && Fivearray[tempi][j] == side )
	{
		count ++;
	}
	return count;
}
int CChessDlg::UpDown(int i, int j,int side)
{
	int tempj,count;
	tempj = j;
	count = 1;

	while ( --tempj > 0 && Fivearray[i][tempj] == side)
	{
		count ++;
	}
	tempj = j;
	while ( ++ tempj <20 &&Fivearray[i][tempj] == side )
	{
		count ++;
	}
	return count;
}
int CChessDlg::LupToRdown(int i, int j,int side)
{
	int tempi,tempj,count;
	tempi = i,tempj = j;
	count = 1;

	while ( --tempi > 0 && -- tempj >0 && Fivearray[tempi][tempj] == side)
	{
		count ++;
	}
	tempi = i,tempj = j;
	while ( ++ tempi<20 && ++ tempj < 20 &&Fivearray[tempi][tempj] == side )
	{
		count ++;
	}
	return count;
}
int CChessDlg::RuptoLdown(int i, int j,int side)
{
	int tempi,tempj,count;
	tempi = i,tempj = j;
	count = 1;
	
	while ( --tempi > 0 && ++tempj <20 && Fivearray[tempi][tempj] == side)
	{
		count ++;
	}
	tempi = i,tempj = j;
	while ( ++ tempi<20 && -- tempj > 0 && Fivearray[tempi][tempj] == side )
	{
		count ++;
	}
	return count;
}

void CChessDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CChessDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CChessDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialog::OnClose();
	 m_socket.Close();
	 m_socket.ShutDown(2);
	 CString str = "------bybyebyebye";
	 m_con_socket.Send(str,str.GetLength(),0);
	 StepList.RemoveAll();
	 for (int i = 0 ;i < 20 ; i++ )
		for (int j=0;j<20;j++ )
			Fivearray[i][j] = 0;
	 m_con_socket.Close();
	 m_con_socket.ShutDown(2);

	CDialog::OnCancel();
}
void CChessDlg::SocketClose()
{
	MessageBox("远端主机已关闭连接","提示",MB_OK);
	SetWindowText("五子棋");

}
void  CChessDlg::GetCurrentScore( GameStatus &board_situation)
{
	int i = board_situation.st.x ;
	int j = board_situation.st.y;
	board_situation.score = 0;
	//状态
	//返回8 成5：five
	//返回7 活4：alivefour
	//返回6 活3：alivethree
	//返回5 活2：alivetwo
	//返回4 死4：deadfour
	//返回3 死3：deadthree
	//返回2 死2：deadtwo
	//返回0,

	//搜索出左到右的状态
	int lr =LeftToRight_Status(i , j ,board_situation.fivearray);
	if  ( lr == 8 ) 
	{
		if ( board_situation.is_machine )
			board_situation.score = 100000;
		else
			board_situation.score = -100000;
		return ;
	}
	//从上到下
	int ud = UpToDown_Status(i,j ,board_situation.fivearray );
	if  ( ud == 8 ) 
	{
		if ( board_situation.is_machine )
			board_situation.score = 100000;
		else
			board_situation.score = -100000;
		return ;
	}
	
	//从左上到右下
	int lutrd = LeftUpToRightDown_Status(i,j ,board_situation.fivearray );
	if  ( lutrd == 8 ) 
	{
		if ( board_situation.is_machine )
			board_situation.score = 100000;
		else
			board_situation.score = -100000;
		return ;
	}

	//从左下到右上
	int ldtru =LeftDownToRightUp_Status(i,j ,board_situation.fivearray );
	if  ( ldtru == 8 ) 
	{
		if ( board_situation.is_machine )
			board_situation.score = 100000;
		else
			board_situation.score = -100000;
		return ;
	}
	
	//是否活4
	if ( lr == 7 || ud == 7 || lutrd == 7 || ldtru == 7 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 10000;
		else
			board_situation.score = -10000;
		return ;
	}
	//双死4
	if ( 
		 ( lr == 4 && (ud == 4 || lutrd == 4 || ldtru == 4))
		 || (ud == 4 && (lutrd == 4|| ldtru == 4))
		 || (lutrd == 4 && ldtru == 4)
		)
	{
		if ( board_situation.is_machine )
			board_situation.score = 10000;
		else
			board_situation.score = -10000;
		return ;
	}
	//死4活3
	if ( 
		  ( lr == 4 && (ud == 6 || lutrd == 6 || ldtru == 6))
		  || ( ud == 4 && (lr == 6 || lutrd == 6 || ldtru == 6))
		  || ( lutrd == 4 && (lr == 6 ||  ud== 6 || ldtru == 6))
		  ||  ( ldtru== 4 && (lr == 6 ||  ud== 6 || lutrd == 6))
		  )
	{
		if ( board_situation.is_machine )
			board_situation.score = 10000;
		else
			board_situation.score = -10000;
		return ;
	}
	//双活3
	if ( 
		 ( lr == 6 && (ud == 6 || lutrd == 6 || ldtru == 6))
		 || (ud == 6 && (lutrd == 6|| ldtru == 6))
		 || (lutrd == 6 && ldtru == 6)
		)
	{
		if ( board_situation.is_machine )
			board_situation.score = 5000;
		else
			board_situation.score = -5000;
		return ;
	}
	//活3双活2
	if ( ( lr == 6 || ud == 6 || lutrd == 6 || ldtru == 6 ) &&
		(	( lr == 5 && (ud == 5 || lutrd == 5 || ldtru == 5))
		 || (ud == 5 && (lutrd == 5|| ldtru == 5))
		 || (lutrd == 5 && ldtru == 5) )
		 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 5000;
		else
			board_situation.score = -5000;
		return ;
	}
	//活3死3
	if ( 
		  ( lr == 3 && (ud == 6 || lutrd == 6 || ldtru == 6))
		  || ( ud == 3 && (lr == 6 || lutrd == 6 || ldtru == 6))
		  || ( lutrd == 3 && (lr == 6 ||  ud== 6 || ldtru == 6))
		  ||  ( ldtru== 3 && (lr == 6 ||  ud== 6 || lutrd == 6))
		  )
	{
		if ( board_situation.is_machine )
			board_situation.score = 1000;
		else
			board_situation.score = -1000;
		return ;
	}
	
	//死4
	if ( lr == 4 || ud == 4 || lutrd == 4 || ldtru == 4 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 500;
		else
			board_situation.score = -500;
		return ;
	}
	//单活3
	if ( lr == 6 || ud == 6 || lutrd == 6 || ldtru == 6 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 200;
		else
			board_situation.score = -200;
		return ;
	}
	//双活2
	if ( 
		 ( lr == 5 && (ud == 5 || lutrd == 5 || ldtru == 5))
		 || (ud == 5 && (lutrd == 5|| ldtru == 5))
		 || (lutrd == 5 && ldtru == 5)
		)
	{
		if ( board_situation.is_machine )
			board_situation.score = 100;
		else
			board_situation.score = -100;
		return ;
	}
	//双死3
	if ( 
		 ( lr == 3 && (ud == 3 || lutrd == 3 || ldtru == 3))
		 || (ud == 3 && (lutrd == 3|| ldtru == 3))
		 || (lutrd == 3 && ldtru == 3)
		)
	{
		if ( board_situation.is_machine )
			board_situation.score = 50;
		else
			board_situation.score = -50;
		return ;
	}
	//单活2
	if ( lr == 5 || ud == 5 || lutrd == 5 || ldtru == 5 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 10;
		else
			board_situation.score = -10;
		return ;
	}
	//单死3
	if ( lr == 3 || ud == 3 || lutrd == 3 || ldtru == 3 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 5;
		else
			board_situation.score = -5;
		return ;
	}
	//单死2
	if ( lr == 2 || ud == 2 || lutrd == 2 || ldtru == 2 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 2;
		else
			board_situation.score = -2;
		return ;
	}
	//死1
	if ( lr == 1 || ud == 1 || lutrd == 1 || ldtru == 1 )
	{
		if ( board_situation.is_machine )
			board_situation.score = 1;
		else
			board_situation.score = -1;
		return ;
	}



	return  ;
}


int CChessDlg::LeftToRight_Status(int i, int j ,int array[][20])
{
	int tempj,count;
	tempj = j;
	count = 1;
	bool aliveone  = false;
	bool alivetwo = false;
	bool beyond = false;
	int side = array[i][j];
	//toleft
	while ( --tempj > 0 && array[i][tempj] == side)
	{
		count ++;
	}
	 if ( tempj > 0 && array[i][tempj] == 0)
	 {
		 aliveone = true;
	 }
	 else if ( tempj > 0 && array[i][tempj] == 1 )
	 {
		beyond = true;
	 }
	tempj = j;
	while ( ++ tempj <20 && array[i][tempj] == side )
	{
		count ++;
	}
	
	 if ( tempj < 20  && array[i][tempj] == 0)
	 {
		 alivetwo = true;
	 }
	 else if ( tempj > 0 && array[i][tempj] == 1 )
	 {
		beyond = true;
	 }
	if ( count >= 5)
	{
		return 8 ;
	}
	 if (count == 1 && aliveone == true && alivetwo == true )
	{
		return 0;
	}
	if ( count == 1 && beyond == true )
	{
		return 1 ;
	}
	 if ( count > 1 && aliveone == true && alivetwo == true )
	 {
		 return count + 3;
	 }
	 if ( count > 1 && (aliveone == true || alivetwo == true ))
	 {
		 return count ;
	 }
	
	 return 0;
	
	
}

int CChessDlg::UpToDown_Status(int i, int j ,int array[][20])
{
	int tempi,count;
	tempi = i;
	count = 1;
	bool aliveone  = false;
	bool alivetwo = false;
	bool beyond = false;
	int side = array[i][j];

	while ( --tempi > 0 && array[tempi][j] == side)
	{
		count ++;
	}

	if ( tempi > 0 && array[tempi][j] == 0  )
	{
		 aliveone = true;
	}
	else if (tempi > 0 && array[tempi][j] == 1 )
	{
		beyond = true;
	}

	tempi = i;
	while ( ++ tempi < 20 && array[tempi][j] == side )
	{
		count ++;
	}

	if ( tempi <  20 && array[tempi][j] == 0 )
	{
		 alivetwo = true;
	}
	else if ( tempi < 20 && array[tempi][j] == 1)
	{
		beyond = true ;
	}
	if ( count >= 5)
	{
		return 8 ;
	}

	if (count == 1 && aliveone == true && alivetwo == true )
	{
		return 0;
	}
	if ( count == 1 && beyond == true )
	{
		return 1 ;
	}
	 if ( count > 1 && aliveone == true && alivetwo == true )
	 {
		 return count + 3;
	 }
	 if ( count > 1 && (aliveone == true || alivetwo == true ))
	 {
		 return count ;
	 }

	return 0;
}
int CChessDlg::LeftUpToRightDown_Status(int i, int j ,int array[][20])
{
	int tempi,tempj,count;
	tempi = i,tempj = j;
	count = 1;
	bool aliveone  = false;
	bool alivetwo = false;
	bool beyond = false;
	int side = array[i][j];

	while ( --tempi > 0 && -- tempj >0 && array[tempi][tempj] == side)
	{
		count ++;
	}
	if ( tempi > 0 && tempj >0 && array[tempi][tempj] == 0 )
	{
		aliveone = true;
	}
	else if ( tempi > 0 && tempj > 0 && array[tempi][tempj] == 1)
	{
		beyond = true;
	}
	tempi = i,tempj = j;
	while ( ++ tempi<20 && ++ tempj < 20 && array[tempi][tempj] == side )
	{
		count ++;
	}
	if ( tempi < 20 && tempj <20 && array[tempi][tempj] == 0)
	{
		alivetwo = true;
	}
	else if ( tempi < 20 && tempj < 20 && array[tempi][tempj] == 1 )
	{
		beyond = true;
	}
	if ( count >= 5)
	{
		return 8 ;
	}
	if (count == 1 && aliveone == true && alivetwo == true )
	{
		return 0;
	}
	if ( count == 1 && beyond == true )
	{
		return 1 ;
	}
	 if ( count > 1 && aliveone == true && alivetwo == true )
	 {
		 return count + 3;
	 }
	 if ( count > 1 && (aliveone == true || alivetwo == true ))
	 {
		 return count ;
	 }

	return 0;
}
int CChessDlg::LeftDownToRightUp_Status(int i, int j ,int array[][20])
{
	int tempi,tempj,count;
	tempi = i,tempj = j;
	count = 1;
	bool aliveone  = false;
	bool alivetwo = false;
	bool beyond = false;
	int side = array[i][j];
	
	while ( ++tempi < 20 && --tempj > 0 && array[tempi][tempj] == side)
	{
		count ++;
	}
	if ( tempi < 20 && tempj > 0 && array[tempi][tempj] == 0)
	{
		aliveone = true;
	}
	else if ( tempi < 20 && tempj > 0 && array[tempi][tempj] == 1)
	{
		beyond = true ;
	}
	tempi = i,tempj = j;
	while ( -- tempi > 0 && ++ tempj < 20 && array[tempi][tempj] == side )
	{
		count ++;
	}
	if ( tempi > 0 && tempj < 20 && array[tempi][tempj] == 0 )
	{
		alivetwo = true;
	}
	else if ( tempi > 0 && tempj < 20 && array[tempi][tempj] == 1)
	{
		beyond = true;
	}
	if ( count >= 5)
	{
		return 8 ;
	}
	if (count == 1 && aliveone == true && alivetwo == true )
	{
		return 0;
	}
	if ( count == 1 && beyond == true )
	{
		return 1 ;
	}
	 if ( count > 1 && aliveone == true && alivetwo == true )
	 {
		 return count + 3;
	 }
	 if ( count > 1 && (aliveone == true || alivetwo == true ))
	 {
		 return count ;
	 }
	return 0;
}
//人机对战
void CChessDlg::OnMachineAndPeson()
{
	if ( MessageBox("        要重新开始吗？","友情提示",MB_YESNO) == IDYES)
	{
		m_and_p_flag = true ;
		is_myturn = true;
		StepList.RemoveAll();
			for (int i = 0 ;i < 20 ; i++ )
			for (int j=0;j<20;j++ )
				Fivearray[i][j] = 0;
			Invalidate();

	}
	
}
int   CChessDlg::MachineSearchGoodPlace(Step &st)
{
    int i;
	CList<GameStatus,GameStatus&>GameStatusList;
	GameStatus temp;
	temp.is_machine = true;
	temp.deep = 0;
	for (int i = 0 ; i < 20 ; i++)
		for (int jj = 0 ; jj< 20 ;jj++)
		temp.fivearray[i][jj] = Fivearray[i][jj];
	

	for ( i = 1 ; i < 20 ; i++)
		for(int j =1; j < 20 ; j++)
		{
			if ( Fivearray[i][j] == 0)
			{
				temp.fivearray[i][j] = 3;
				temp.st.side = 3;
				temp.st.x = i ;
				temp.st.y = j;
				GetCurrentScore(temp);
				if ( temp.score > 0 )
				{
					if ( GameStatusList.GetCount() > 0 )
					{
						POSITION ps  = GameStatusList.GetHeadPosition();
						GameStatus temp1 = GameStatusList.GetAt(ps);
						while (ps != NULL && temp.score > temp1.score )
						{
							temp1 = GameStatusList.GetNext(ps);
							
						}
						if ( ps == NULL)
						{
							ps = GameStatusList.GetTailPosition();
							temp1 = GameStatusList.GetAt(ps);
							if (temp1.score > temp.score )
							{
								GameStatusList.InsertBefore(ps,temp);
							}
							else
								GameStatusList.AddTail(temp);
						}
						else
						{
							GameStatusList.InsertBefore(ps,temp);
						}
					}
					else
					{
						GameStatusList.AddTail(temp);
					}
					
				}	
				temp.fivearray[i][j] = 0;

			}
			

		}
		/*
		POSITION ps  = GameStatusList.GetTailPosition();
		if ( ps == NULL )
			return 0;
		//初级
		if ( m_combox.GetCurSel() == 0 )
		{
			temp = GameStatusList.GetPrev(ps); 
			st = temp.st ;
			GameStatusList.RemoveAll(); 
			return temp.score;
		}
		//中级
		else
		{
			int maxscore = 0;
			for (int i = 0;i < 3; i++ )
			{
				GameStatus ts =  GameStatusList.GetAt(ps);
				int sc = DeepSearch(ts);
				return sc;
			}
			
		}
		 
		
		 
		
		 /*
		StepList.AddTail( st );
		Fivearray[st.x][st.y] = 3 ; 
		DrawChess(temp.st.x,temp.st.y); 
		/*
		int ss = temp.score ;
		while ( ps != NULL )
		{
			temp = GameStatusList.GetPrev(ps);
			 ss = temp.score ;
		}
		*/
		
	return 0 ;
	
}
int  CChessDlg::MachineSearchBadPlace(Step &stt)
{
    int i;
	CList<GameStatus,GameStatus&>GameStatusList;
	GameStatus temp;
	temp.deep = 0;
	temp.is_machine = false;
	for (int i = 0 ; i < 20 ; i++)
		for (int jj = 0 ; jj < 20 ;jj++)
		temp.fivearray[i][jj] = Fivearray[i][jj];
	

	for ( i = 1 ; i < 20 ; i++)
		for(int j =1; j < 20 ; j++)
		{
			if ( Fivearray[i][j] == 0)
			{
				temp.fivearray[i][j] = 1;
				temp.st.side = 1;
				temp.st.x = i ;
				temp.st.y = j;
				temp.score = 0 ;
				GetCurrentScore(temp);
				if ( temp.score < 0 )
				{
					if ( GameStatusList.GetCount() > 0 )
					{
						POSITION ps  = GameStatusList.GetHeadPosition();
						GameStatus temp1 = GameStatusList.GetAt(ps);
						while (ps != NULL && temp.score < temp1.score )
						{
							temp1 = GameStatusList.GetNext(ps);
							
						}
						if ( ps == NULL)
						{
							ps = GameStatusList.GetTailPosition();
							temp1 = GameStatusList.GetAt(ps);
							if (temp1.score < temp.score )
							{
								GameStatusList.InsertBefore(ps,temp);
							}
							else
								GameStatusList.AddTail(temp);
						}
						else
						{
							GameStatusList.InsertBefore(ps,temp);
						}
					}
					else
					{
						GameStatusList.AddTail(temp);
					}
					
				}	
				
				temp.fivearray[i][j] = 0;

			}
			

		}

		/*
		POSITION ps  = GameStatusList.GetTailPosition();
		//初级
		if ( m_combox.GetCurSel() == 0 )
		{
			temp = GameStatusList.GetPrev(ps);
			 stt = temp.st ;
			 GameStatusList.RemoveAll();
			 return -temp.score;
		}
		/*
		StepList.AddTail( st );
		Fivearray[st.x][st.y] = 3 ; 
		DrawChess(temp.st.x,temp.st.y); 
		
		int ss = temp.score ;
		while ( ps != NULL )
		{
			temp = GameStatusList.GetPrev(ps);
			 ss = temp.score ;
		}
		*/
		return 0 ;
		
}

int  CChessDlg::SearchMaxValue(Step &st ,int array[][20])
{
	int max_score = 0;
	int score = 0;
    int i;

	GameStatus temp;
	temp.is_machine = true;
	temp.deep = 0;
	for (int i = 0 ; i < 20 ; i++)
		for (int jj = 0 ; jj< 20 ;jj++)
		temp.fivearray[i][jj] = array[i][jj];
	

	for ( i = 1 ; i < 20 ; i++)
		for(int j =1; j < 20 ; j++)
		{
			if ( array[i][j] == 0)
			{
				temp.st.x = i ;
				temp.st.y = j;
				score = 0;
				int score1 = 0,score2 = 0;
				

				
				temp.fivearray[i][j] = 3;
				temp.st.side = 3;
				temp.is_machine = true; 
				temp.score = 0;
				GetCurrentScore(temp);
				score1  = temp.score ;
				
				temp.fivearray[i][j] = 1;
				temp.st.side = 1 ;
				temp.is_machine = false ;
				temp.score = 0;
				 GetCurrentScore(temp);
				score2 = -temp.score ;

				
				
				//机器
				if ( score1 >= 10000 )
				{
					 
					temp.fivearray[i][j] = 3;
					temp.st.side = 3;
					temp.is_machine = true; 
					temp.score = 0;
					Step tempst1; 
					int tempscore = SearchValue(temp.fivearray,tempst1,false);
					if ( score1 < tempscore)//如果当前盘面还有比现在分数大的，则防守
					{
						st.x = tempst1.x;
						st.y = tempst1.y ;
						return tempscore;
					}
					else
					{
						st.x = i;
						st.y = j;
						return score1;
					}
				}
				if ( score2 >= 100000 )
				{
					temp.fivearray[i][j] = 1;
					temp.st.side = 1 ;
					temp.is_machine = false ;
					temp.score = 0;
					Step tempst1; 
					int tempscore = SearchValue(temp.fivearray,tempst1,true);
					if ( score2 <= tempscore)//
					{
						st.x = tempst1.x;
						st.y = tempst1.y ;
						return tempscore;
					}
					else
					{
						st.x = i;
						st.y = j;
						return score1;
					}
					
				}

				

				score = score1 + score2 ;

				 if  ( score > max_score )
				 {
					 max_score = score ;
					 st.x = i;
					 st.y = j;
				 }
			

				temp.fivearray[i][j] = 0;

			}
			

		}
		return max_score ;
}
//返回分数
int CChessDlg::DeepSearch(GameStatus  ts,Step &st,bool machine,int value)
{
    int i;
	ts.deep++;
	st.deep ++ ;
	int score =0 ;
	if  ( ts.deep  == 3 )
	{
		
		score = SearchValue ( ts.fivearray,st,machine);
		return score;
	}

	

	int min_score = 0;
	 score = 0;
	
	//选出几局分较高的
	CList<GameStatus,GameStatus&>GameStatusList;
	for ( int i = 1 ; i < 20 ; i++)
		for(int j =1; j < 20 ; j++)
		{
			if ( ts.fivearray[i][j] == 0)
			{
				

				ts.st.x = i ;
				ts.st.y = j;
				score = 0;
				if ( machine )
				{
					ts.fivearray[i][j] = 3;
					ts.st.side = 3;
					ts.is_machine = true ;
					ts.score = 0;
					GetCurrentScore( ts );
					if ( score == 100000)
					{
						st.x = i;
						st.y = j;
						return score;
					}
					score = ts.score ;
				}
				else
				{
					ts.fivearray[i][j] = 1;
					ts.st.side = 1 ;
					ts.is_machine = false ;
					ts.score = 0;
					GetCurrentScore(ts);
					score =  - ts.score ;
					ts.score = score;
					if ( score == 100000)
					{
						st.x = i;
						st.y = j;
						return score;
					}
				}
				ts.score = score ;
				if ( score == 0)
				{
					ts.fivearray[i][j] = 0;
					continue;	
				}
					
				if ( GameStatusList.GetCount() == 0)
				{
					min_score = ts.score ;					
					GameStatusList.AddTail(ts);
				}
				else
				{
					if  ( score <= min_score )
					{
						 min_score = score ;
						GameStatusList.AddTail(ts);
					}
					else
					{
						POSITION ps = GameStatusList.GetTailPosition();
						while ( ps != NULL )
						{
							GameStatus temp = GameStatusList.GetPrev(ps);
							if  ( temp.score >= score )
							{
							
								GameStatusList.InsertAfter(ps,ts);
								break;
							}
						
						}
						if ( ps == NULL )
						{
							GameStatusList.AddHead( ts );
						}
					}
					
				}
				ts.fivearray[i][j] = 0;

			}
			

		}//for
		POSITION ps = GameStatusList.GetHeadPosition();
		Step tempstep = st;
		int  tempscore = 0 ;
		int max = 0;
		for ( i = 0 ;i < 3; i ++ )
		{
			GameStatus temp =  GameStatusList.GetNext(ps);
				value = temp.score  ;
				tempscore = DeepSearch(temp,tempstep,! machine,temp.score );

				if ( tempscore > max )
				{
					max = tempscore;
					st = temp.st;
					st.deep = tempstep.deep ;
				}
			
			if ( ps == NULL )
				break;

		}

		return max ;

	
}

int CChessDlg::SearchValue(int array[][20],Step & st,bool machine)
{
	int max_score = 0;
	int score = 0;
    int i;

	GameStatus temp;
	temp.is_machine = machine;
	temp.deep = 0;
	for (int i = 0 ; i < 20 ; i++)
		for (int jj = 0 ; jj< 20 ;jj++)
		temp.fivearray[i][jj] = array[i][jj];
	

	for ( i = 1 ; i < 20 ; i++)
		for(int j =1; j < 20 ; j++)
		{
			if ( array[i][j] == 0)
			{
				temp.st.x = i ;
				temp.st.y = j;
				score = 0;
				
				if ( machine)
				{
					temp.fivearray[i][j] = 3;
					temp.st.side = 3;
					temp.is_machine = true; 
					temp.score = 0;
					GetCurrentScore(temp);
					score  = temp.score ;
				}
				else
				{
					temp.fivearray[i][j] = 1;
					temp.st.side = 1 ;
					temp.is_machine = false ;
					temp.score = 0;
					GetCurrentScore(temp);
					score = score - temp.score ;
				}
				if ( score == 100000 )
				{
					st.x = i;
					st.y = j;
					return  score;
				}
				 if  ( score > max_score )
				 {
					 max_score = score ;
					 st.x = i;
					 st.y = j;
				 }
				temp.fivearray[i][j] = 0;

			}
			

		}
		return max_score ;
}
void CChessDlg::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DrawChess(oldstep.x,oldstep.y,false);
	oldstep = m_currentstep;
	flag = !flag;
	DrawChess(m_currentstep.x,m_currentstep.y,flag);
	CDialog::OnTimer(nIDEvent);
}
