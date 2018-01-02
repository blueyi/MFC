
#include "stdafx.h"
#include "Chat.h"
#include "UserInfoDlg.h"


// CUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialog)
CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
	, m_name(_T(""))
{
	m_curentimage  =  -1;
}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipctrl);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_comboxex);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CUserInfoDlg 消息处理程序

BOOL CUserInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_name+"的基本资料"); 
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
	int i,ipint[4];
	for ( i=0; i < 4; i++ )
	{
		ipint[i] = atoi(iptemp[i]);
	}
	m_ipctrl.SetAddress( ipint[0],ipint[1],ipint[2],ipint[3] );

	// TODO:  在此添加额外的初始化
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
	
	
	m_comboxex.SetImageList(&m_imagelist);
	COMBOBOXEXITEM     cbi;
	int      nItem;
	for(  int i = 0 ;i < 15 ; i++)
	{
		cbi.mask = CBEIF_IMAGE | CBEIF_INDENT | CBEIF_OVERLAY |
				   CBEIF_SELECTEDIMAGE ;//| CBEIF_TEXT;
		cbi.iItem = i;
		cbi.pszText = "";//(LPTSTR)(LPCTSTR)str;
		//cbi.cchTextMax = str.GetLength();
		cbi.iImage = i;
		cbi.iSelectedImage = i;
		cbi.iOverlay = I_IMAGECALLBACK;//1;//2;
		cbi.iIndent = I_INDENTCALLBACK;//(i & 0x03);   //Set indentation according
                            //to item position
		nItem = m_comboxex.InsertItem(&cbi);
	}
	if (m_curentimage < 0)
	{
		m_comboxex.SetCurSel(0);
	}
	else
		m_comboxex.SetCurSel(m_curentimage);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

void CUserInfoDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CUserInfoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE ipint[4];
	m_ipctrl.GetAddress(ipint[0],ipint[1],ipint[2],ipint[3]);
	CString tempip;
	tempip.Format("%d.%d.%d.%d",ipint[0],ipint[1],ipint[2],ipint[3]);
	ip = tempip;

	m_curentimage  = m_comboxex.GetCurSel(); 
	OnOK();
}

void CUserInfoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void CUserInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	//分解ＩＰ
	
	// TODO: 在此添加消息处理程序代码
}

HBRUSH CUserInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
