// MacDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "MacDlg.h"
#define destPORT 137  //nbtstat name port
#define myPORT 4321
BYTE bs[50]={0x0,0x00,0x0,0x10,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x43,0x4b,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x0,0x0,0x21,0x0,0x1};
unsigned char B1[4],B2[4];
HANDLE wait_handle;

CString strOldIP="";
bool bExit=false;
int i;


// CMacDlg 对话框
CMacDlg *pdlg;


UINT ScanThread(LPVOID param)
{
	do
	{
		if(bExit)
		{
			//AfxMessageBox("退出线程!");
			pdlg->GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
			pdlg->GetDlgItem(IDC_IPADDRESS1)->EnableWindow(true);
			pdlg->GetDlgItem(IDC_IPADDRESS2)->EnableWindow(true);
			pdlg->GetDlgItem(IDC_EDIT1)->EnableWindow(true);
			
			bExit=false;
			return 1;
		}
		
		pdlg->m_strIP.Format("%d.%d.%d.%d",B1[0],B1[1],B1[2],B1[3]);
		pdlg->SetWindowText("正在扫描"+pdlg->m_strIP);

		if ( pdlg->m_UDPSocket.SendTo((void*)bs,50,destPORT,pdlg->m_strIP,0) == SOCKET_ERROR)
		{
			AfxMessageBox("发送消息错误");
		}

		
        int nWait=pdlg->m_spin.GetPos();
		WaitForSingleObject( wait_handle,nWait );
		ResetEvent(wait_handle);
		

		//=============================================
		if(B1[2]<=B2[2])
		{
		  
		   if(B1[3]<B2[3])B1[3]++;
		   else if(B1[2]<B2[2]&&B1[3]<255)B1[3]++;
		   else if(B1[2]<B2[2]&&B1[3]==255)
		   {
			   B1[3]=0;
			   B1[2]++;
		   }
		}
		else break;
		if(B1[3]>=B2[3]&&B1[2]>=B2[2])break;

	}while(B1[2]<=255&&B1[3]<=255);
	
	pdlg->OnEndScan();
	
	return 0;
}
IMPLEMENT_DYNAMIC(CMacDlg, CDialog)
CMacDlg::CMacDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMacDlg::IDD, pParent)
{
	pdlg = this;
	if(!m_UDPSocket.Create(myPORT,SOCK_DGRAM))
	{
		AfxMessageBox("Failed Create Socket");
	}
}

CMacDlg::~CMacDlg()
{
}

void CMacDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_begin);
	DDX_Control(pDX, IDC_BUTTON2, m_end);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipctrl1);
	DDX_Control(pDX, IDC_IPADDRESS2, m_ipctrl2);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Control(pDX, IDC_PROGRESS1, m_proctrl);
	DDX_Control(pDX, IDC_SPIN1, m_spin);
}


BEGIN_MESSAGE_MAP(CMacDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnBegin)
	ON_BN_CLICKED(IDC_BUTTON2, OnEndScan)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, OnIpnFieldchangedIpaddress1)
END_MESSAGE_MAP()


// CMacDlg 消息处理程序

HBRUSH CMacDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	 pDC->SetBkMode(TRANSPARENT);
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (nCtlColor != CTLCOLOR_LISTBOX &&  nCtlColor !=  CTLCOLOR_EDIT)
	{
		HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
		return br;
	}
	return hbr;
}

BOOL CMacDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ipctrl1.SetAddress(192,168,0,1);
	m_ipctrl2.SetAddress(192,168,0,255);
	m_proctrl.SetRange(0,100);
	m_proctrl.SetStep(5);
	m_spin.SetBuddy(GetDlgItem(IDC_EDIT1));
	m_spin.SetRange(100,1000);
	m_spin.SetPos( 100 );
	wait_handle=CreateEvent(NULL,true,false,"receive data");
	
	m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT  );
	m_listctrl.InsertColumn(0,"MAC地址",LVCFMT_LEFT,120);
	m_listctrl.InsertColumn(0,"主机",LVCFMT_LEFT,80);
	m_listctrl.InsertColumn(0,"工作组",LVCFMT_LEFT,80);
	m_listctrl.InsertColumn(0,"IP地址",LVCFMT_LEFT,100);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

void CMacDlg::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_proctrl.StepIt();

	CDialog::OnTimer(nIDEvent);
}
//begin scan
void CMacDlg::OnBegin()
{
	// TODO: 在此添加控件通知处理程序代码
	bExit=false;
	m_listctrl.DeleteAllItems();
	m_ipctrl1.GetAddress(B1[0],B1[1],B1[2],B1[3]);
	m_ipctrl2.GetAddress(B2[0],B2[1],B2[2],B2[3]);

	if(B2[2]<B1[2]){AfxMessageBox("终止地址应大于起始地址！"); return ;}
	else if(B2[2]==B1[2]&&B2[3]<B1[3]){AfxMessageBox("终止地址应大于起始地址！"); return ;}
	if(B2[0]!=B1[0]||B2[1]!=B1[1]){AfxMessageBox("不支持A类或B类网！"); return ;}
	
	SetTimer(1,100,0);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(false);
	GetDlgItem(IDC_IPADDRESS2)->EnableWindow(false);
	GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	AfxBeginThread(ScanThread,this->GetSafeHwnd(),THREAD_PRIORITY_NORMAL,0,0,NULL);

}

void CMacDlg::OnEndScan()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	bExit=true;
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(true);
	GetDlgItem(IDC_IPADDRESS2)->EnableWindow(true);
	GetDlgItem(IDC_EDIT1)->EnableWindow(true);
	m_proctrl.SetPos(0);
	SetWindowText("Mac扫描器");
	
	
}

void CMacDlg::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

		unsigned char AddrB[4];
	m_ipctrl1.GetAddress(AddrB[0],AddrB[1],AddrB[2],AddrB[3]);
	m_ipctrl2.SetAddress(AddrB[0],AddrB[1],AddrB[2],255);	

	*pResult = 0;
}

void CMacDlg::OnReceive(void)
{
	BYTE Buf[500];
	
	memset(Buf,'\0',sizeof(Buf));

	CString str,strIP,strHost,strHex,strMac,Host,Group,User;
	UINT dport;
	m_UDPSocket.ReceiveFrom(Buf,500,strIP,dport,0);

	if(strIP==(char)NULL||strIP==strOldIP)return;
	strOldIP=strIP;

	int index=m_listctrl.InsertItem(0,strIP);

	strHost="";
	strHex="";
	User="?";
	Host="\\";
	
	int tem=0,num=0;
	bool bAdd=true;

	//if(m_strIP==strIP)
	for(i=57;i<500;i++) //57-72
	{
		if(Buf[i]==0xcc)break; 
		if(Buf[i]==0x20)bAdd=false;
		if(bAdd)
		{
			str.Format("%c",Buf[i]);
			if(Buf[i]>=' ')strHost+=str;

			str.Format("%02x.",Buf[i]);
			strHex+=str;
		}

		if((++tem)%18==0)
		{
            bAdd=true; 
			//m_ListBox.AddString(strHost);//
			strHost.TrimRight((char)NULL);
			if(strHost=="")
			{
   				if ( strMac.GetLength()> 17 )
				strMac.Delete(17,strMac.GetLength()-17);
				m_listctrl.SetItem(index,3,LVIF_TEXT,strMac, 0, 0, 0,0);
				break;
			}


			if(num==0&&strHost!="")
			{
				m_listctrl.SetItem(index,2,LVIF_TEXT,strHost, 0, 0, 0,0);
				Host=strHost;
				num++;
			}
			else
			{
				if(Host!=strHost&&num==1&&strHost!="")
				{
					m_listctrl.SetItem(index,1,LVIF_TEXT,strHost, 0, 0, 0,0);
					Group=strHost;
					//AfxMessageBox(strHost);
				    num++;
				}
				else 
				{
					if(strHost!=Host&&strHost!=Group&&num==2&&strHost!="")
					{
						User=strHost;
						if(User!="__MSBROWSE__")
						{
							//m_listctrl.SetItem(index,3,LVIF_TEXT,User, 0, 0, 0,0);
							num++;
						}
						//num++;
					}
				}

			}
			
			strMac=strHex;
			strHost="";
			strHex="";
			
		}
		
	}
	SetEvent(wait_handle);
}
