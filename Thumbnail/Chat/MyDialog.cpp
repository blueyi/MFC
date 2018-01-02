// MyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "MyDialog.h"


// CMyDialog 对话框

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)
CMyDialog::CMyDialog(CString name,CWnd* pParent /*=NULL*/)
	: m_name(name),CDialog(CMyDialog::IDD, pParent)
	, m_port(6000)
{
	Iimage =-1;
	info = "" ;
	show = false;
}

CMyDialog::~CMyDialog()
{
	
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT22, m_edit);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_EDIT2, m_port);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
	DDX_Control(pDX, IDC_IMAGE, m_image);
	DDX_Control(pDX, IDC_BUTTON1, m_send);
	DDX_Control(pDX, IDC_BUTTON2, m_close);
	DDX_Control(pDX, IDC_BUTTON3, m_button3);
	DDX_Control(pDX, IDC_STATIC3, m_static1);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnOK)
//	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_WM_CTLCOLOR()
//	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_WM_CLOSE()
	ON_LBN_DBLCLK(IDC_LIST1, OnLbnDblclkList1)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, OnRecordButtonClicked)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_MYMESSAGE,OnMyMessage)
END_MESSAGE_MAP()


// CMyDialog 消息处理程序

void CMyDialog::OnOK()
{
	// TODO: 在此添加控件通知处理程序代码
		///CDialog::OnOK();
	if ( !m_edit.IsWindowEnabled())
	{
		m_edit.EnableWindow(true);
		m_edit.SetWindowText(info);
		info = "";
		m_send.SetWindowText("发送信息");
		m_edit.SetFocus();
		return ;
	}	
	CString text;
	m_edit.GetWindowText(text);
	if (text == "")
	{
		MessageBox("不要发送空信息哦，太浪费网络资源了","提示",MB_OK);
		return;
	}

	BYTE addr1;
	BYTE addr2;
	BYTE addr3;
	BYTE addr4;
	m_ip.GetAddress(addr1,addr2,addr3,addr4);
	CString ipstr;
	ipstr.Format("%d.%d.%d.%d",addr1,addr2,addr3,addr4);
	//MessageBox(str);


	CAsyncSocket * psocket = new CAsyncSocket;
	if ( psocket->Create(1601,SOCK_DGRAM,FD_READ|FD_WRITE,NULL) ==SOCKET_ERROR)
	{
		AfxMessageBox("创建套接字失败");
			delete psocket;
			//m_edit.SetWindowText("");
			m_edit.SetFocus();
			return;
	}
	int result = psocket->SendTo(text,text.GetLength(),1600,ipstr);
	if ( result == SOCKET_ERROR)
	{
		AfxMessageBox("发送消息失败");
		delete psocket;
		//m_edit.SetWindowText("");
		m_edit.SetFocus();
		return;
	}
	CTime t=CTime::GetCurrentTime();
	CString m_time = t.Format("%Y-%m-%d %H:%M");
	m_listbox.InsertString(0,"你对"+m_name+"说: "+text+"   "+m_time);
	delete psocket;
	psocket = NULL;
	m_edit.SetWindowText("");

	
}

void CMyDialog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

int CMyDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
//	m_ip.SetAddress(192,168,0,168);
	SetWindowText("与"+m_name+"聊天中");
	// TODO:  在此添加您专用的创建代码
	/*
	m_socket.SetHWnd((HWND)this);
	if(m_socket.Create(1600,SOCK_DGRAM,FD_READ|FD_WRITE,NULL)==SOCKET_ERROR)
	{
		AfxMessageBox("创建套接字失败");
	}
	*/
	
	return 0;
}

void CMyDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

HBRUSH CMyDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	 pDC->SetBkMode(TRANSPARENT);
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (nCtlColor != CTLCOLOR_LISTBOX &&  nCtlColor !=  CTLCOLOR_EDIT)
	{
		HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
		return br;
	}
	return hbr;
}

//void CMyDialog::OnBnClickedButton4()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	
//	
//}
void CMyDialog::OnReceive()
{
	/*
	char strrev[1024];
	memset(strrev,'\0',1024);
	int nresult;
	UINT port;	
	CString ipstr;

	nresult=m_socket.ReceiveFrom(strrev,sizeof(strrev),ipstr,port);
	if ( (nresult != SOCKET_ERROR) )
	{
		CString str = strrev;
		m_listbox.AddString(m_name+"对你说: "+str);
		
	}
	if ( !this->IsWindowVisible())
	{
		this->ShowWindow(SW_SHOW);
	}
	*/
}

void CMyDialog::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_socket.Close();
	m_socket.ShutDown(2);
	//UnregisterHotKey(m_hWnd,1001); 
	CDialog::OnClose();
}
BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strbmp;
	int i,flag = Iimage + 1;
	strbmp.Format("face//%d.bmp",flag);

	HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,strbmp,IMAGE_BITMAP,0,0,
		LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_image.SetBitmap(hbitmap);
	CFont font;
	font.CreateFont(
			15,                        // nHeight
			 0,                         // nWidth
			 0,                         // nEscapement
			 0,                         // nOrientation
			 FW_NORMAL,                 // nWeight
			 FALSE,                     // bItalic
			 FALSE,                     // bUnderline
			  0,                         // cStrikeOut
			  ANSI_CHARSET,              // nCharSet
			 OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			 DEFAULT_QUALITY,           // nQuality
			 DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");   // lpszFacename
	m_edit.SetFont(&font,true);



//分解ＩＰ
	char iptemp[4][4];
	for (int i=0;i<4;i++)
	{
		memset(iptemp[i],'\0',4);
	}
	CString s = ip;
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
	m_ip.SetAddress( ipint[0],ipint[1],ipint[2],ipint[3] );
	return true;
}
//双击listbox
void CMyDialog::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	for ( int i = 0; i< m_listbox.GetCount(); i++ )
	{
		if (m_listbox.GetSel(i))
		{
			if (m_edit.IsWindowEnabled())
			{
				CString str ;
				m_listbox.GetText(i,str);
				m_edit.SetWindowText(str);
				break;
			}
		}
	}
	

}

void CMyDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyDialog::OnRecordButtonClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	if (show ==true)
	{
		CRect rc;
		this->GetClientRect(&rc);
		//this->CalcWindowRect(&rc, CWnd::adjustBorder);
		m_static2.GetClientRect(&rc);
		rc.right+=20;
		rc.bottom +=50;
		this->ClientToScreen(&rc);
		//this->CenterWindow(NULL);
		this->MoveWindow(&rc,true);
		show = false;
	}
	else
	{
		CRect allrect, downrect;
		this->GetClientRect(&allrect);
		//this->CalcWindowRect(&allrect, CWnd::adjustBorder);
		m_static1.GetClientRect(&downrect);
		int a = allrect.bottom;
		allrect.bottom = allrect.bottom - (downrect.bottom- downrect.top)+15 ;
		//allrect.right +=10;
	//allrect.right = allrect.right - (downrect.right - downrect.left )+10;
		this->ClientToScreen(&allrect);
	//CenterWindow(NULL);
		this->MoveWindow(&allrect,true);
		show = true;
	}
	m_edit.SetFocus();
}

void CMyDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if( show ==false)
	{
		CRect allrect, downrect;
		this->GetClientRect(&allrect);
		//this->CalcWindowRect(&allrect, CWnd::adjustBorder);
		m_static1.GetClientRect(&downrect);
		int a = allrect.bottom;
		allrect.bottom = allrect.bottom - (downrect.bottom- downrect.top)+15 ;
		this->ClientToScreen(&allrect);
	//CenterWindow(NULL);
		this->MoveWindow(&allrect,true);
		show = true;
	}
	
	
	// TODO: 在此添加消息处理程序代码
}



void CMyDialog::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此添加消息处理程序代码
}
LRESULT CMyDialog::OnMyMessage(WPARAM wParam,LPARAM lParam)
{
	CString temp;
		m_send.GetWindowText(temp);
		if ( temp == "发送信息")
		{
			OnOK();
		}
	return 0;
}
