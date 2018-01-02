// XPBtn_ScrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XPBtn_Scroll.h"
#include "XPBtn_ScrollDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPBtn_ScrollDlg dialog

CXPBtn_ScrollDlg::CXPBtn_ScrollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXPBtn_ScrollDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXPBtn_ScrollDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nWinVersion =WIN_UNKNOWN;
}

void CXPBtn_ScrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXPBtn_ScrollDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXPBtn_ScrollDlg, CDialog)
	//{{AFX_MSG_MAP(CXPBtn_ScrollDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXPBtn_ScrollDlg message handlers

BOOL CXPBtn_ScrollDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    // 得到当前Windows版本
	GetWinVersion();

	CString XPScrollHSPath("");  // 1.2版水平方向银色滚动条控件路径 
	CString XPScrollVSPath("");  // 1.2版垂直方向银色滚动条控件路径 
	CString XPBtnSPath("");      // 1.2版银色按钮控件路径
	CString XPButtonPath("");    // 2.0版银色按钮控件路径

    try
    {
      // 尝试打开控件文件
      CFile XPScrollHS(_T("XPScroll_Horizontal_Silver.ocx"), CFile::shareDenyNone);
	  CFile XPScrollVS(_T("XPScroll_Vertical_Silver.ocx"), CFile::shareDenyNone);
	  CFile XPBtnS(_T("XPButton_Silver.ocx"), CFile::shareDenyNone);
	  CFile XPButton(_T("XPButton.ocx"), CFile::shareDenyNone);
      
	  // 得到控件文件路径
	  XPScrollHSPath=XPScrollHS.GetFilePath();
	  XPScrollVSPath=XPScrollVS.GetFilePath(); 
	  XPBtnSPath=XPBtnS.GetFilePath(); 
	  XPButtonPath=XPButton.GetFilePath();

      // 关闭文件句柄
	  XPScrollHS.Close();
	  XPScrollVS.Close();  
	  XPBtnS.Close(); 
	  XPButton.Close();
    }
    catch (CFileException* pEx)
    {
      // 文件操作异常处理
      pEx->ReportError();
      pEx->Delete();
    }

	// 保存注册结果用的变量
	HINSTANCE hXPScrollHS,hXPScrollVS;
    HINSTANCE hXPBtnS,hXPButton;

	// Windows9X/ME/XP下，regsvr32.exe一般位于C:\WINDOWS\System32\目录下
	if(m_nWinVersion==WIN_95||m_nWinVersion==WIN_98||m_nWinVersion==WIN_ME||m_nWinVersion==WIN_XP)
	{
	   hXPScrollHS=ShellExecute(NULL,"open", "regsvr32.exe",XPScrollHSPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
       hXPScrollVS=ShellExecute(NULL,"open", "regsvr32.exe",XPScrollVSPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
       hXPBtnS=ShellExecute(NULL,"open", "regsvr32.exe",XPBtnSPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
       hXPButton=ShellExecute(NULL,"open", "regsvr32.exe",XPButtonPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
	}
	// WindowsNT/2000下，regsvr32.exe一般位于C:\WINNT\System32\目录下
	else if(m_nWinVersion==WIN_NT351||m_nWinVersion==WIN_NT40||m_nWinVersion==WIN_2000)
	{
	   hXPScrollHS=ShellExecute(NULL,"open", "regsvr32.exe",XPScrollHSPath,"C:\\WINNT\\System32\\",SW_HIDE);
       hXPScrollVS=ShellExecute(NULL,"open", "regsvr32.exe",XPScrollVSPath,"C:\\WINNT\\System32\\",SW_HIDE);
       hXPBtnS=ShellExecute(NULL,"open", "regsvr32.exe",XPBtnSPath,"C:\\WINNT\\System32\\",SW_HIDE);
       hXPButton=ShellExecute(NULL,"open", "regsvr32.exe",XPButtonPath,"C:\\WINNT\\System32\\",SW_HIDE);
	}
	//  如果不是以上Windows版本m_nWinVersion==WIN_UNKNOWN，则退出程序
	else
	{
	   AfxMessageBox(_T("未知操作系统！"),MB_OK|MB_ICONINFORMATION);
       ::PostMessage(NULL,WM_QUIT,0,0);
	}
	int RegResult1,RegResult2,RegResult3,RegResult4;
	RegResult1=int(hXPScrollHS);
	RegResult2=int(hXPScrollVS);
	RegResult3=int(hXPBtnS);
	RegResult4=int(hXPButton);

	if((RegResult1>32)&&(RegResult2>32)&&(RegResult3>32)&&(RegResult4>32))
	{
	   // 注册控件成功弹出提示
	   AfxMessageBox("恭喜恭喜，控件注册成功!",MB_OK|MB_ICONINFORMATION);
	   Sleep(1000);
	}
	else  
	{
	   // 注册控件失败弹出提示
	   AfxMessageBox("控件注册失败!",MB_OK|MB_ICONINFORMATION);
	}  	 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXPBtn_ScrollDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXPBtn_ScrollDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



BEGIN_EVENTSINK_MAP(CXPBtn_ScrollDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CXPBtn_ScrollDlg)
	ON_EVENT(CXPBtn_ScrollDlg, IDC_OK, -600 /* Click */, OnClickOk, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CXPBtn_ScrollDlg::OnClickOk() 
{

	CString XPScrollHSPath("");
	CString XPScrollVSPath("");
	CString XPBtnSPath("");
	CString XPButtonPath("");

    try
    {
      // 得到控件文件路径
      CFile XPScrollHS(_T("XPScroll_Horizontal_Silver.ocx"), CFile::shareDenyNone);
	  CFile XPScrollVS(_T("XPScroll_Vertical_Silver.ocx"), CFile::shareDenyNone);
	  CFile XPBtnS(_T("XPButton_Silver.ocx"), CFile::shareDenyNone);
	  CFile XPButton(_T("XPButton.ocx"), CFile::shareDenyNone);
      
	  XPScrollHSPath=XPScrollHS.GetFilePath();
	  XPScrollVSPath=XPScrollVS.GetFilePath(); 
	  XPBtnSPath=XPBtnS.GetFilePath(); 
	  XPButtonPath=XPButton.GetFilePath();

      // close the file handle
	  XPScrollHS.Close();
	  XPScrollVS.Close();  
	  XPBtnS.Close(); 
	  XPButton.Close();
    }
    catch (CFileException* pEx)
    {
      // if an error occurs, just make a message box
      pEx->ReportError();
      pEx->Delete();
    }

	HINSTANCE hXPScrollHS,hXPScrollVS;
    HINSTANCE hXPBtnS,hXPButton;

	if(m_nWinVersion==WIN_95||m_nWinVersion==WIN_98||m_nWinVersion==WIN_ME||m_nWinVersion==WIN_XP)
	{
	   hXPScrollHS=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPScrollHSPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
       hXPScrollVS=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPScrollVSPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
       hXPBtnS=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPBtnSPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
       hXPButton=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPButtonPath,"C:\\WINDOWS\\System32\\",SW_HIDE);
	}
	else if(m_nWinVersion==WIN_NT351||m_nWinVersion==WIN_NT40||m_nWinVersion==WIN_2000)
	{
	   hXPScrollHS=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPScrollHSPath,"C:\\WINNT\\System32\\",SW_HIDE);
       hXPScrollVS=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPScrollVSPath,"C:\\WINNT\\System32\\",SW_HIDE);
       hXPBtnS=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPBtnSPath,"C:\\WINNT\\System32\\",SW_HIDE);
       hXPButton=ShellExecute(NULL,"open", "regsvr32.exe",_T("-u -s")+XPButtonPath,"C:\\WINNT\\System32\\",SW_HIDE);
	}
	//  如果不是以上Windows版本m_nWinVersion==WIN_UNKNOWN，则退出程序
	else
	{
	   AfxMessageBox(_T("未知操作系统！"),MB_OK|MB_ICONINFORMATION);
       ::PostMessage(NULL,WM_QUIT,0,0);
	}

	CDialog::OnOK();	
}


void CXPBtn_ScrollDlg::GetWinVersion()
{
	// 得到当前Windows版本
	DWORD dwMajorVersion,dwMinorVersion,dwPlatformId;
	OSVERSIONINFOEX WinVersion;
	ZeroMemory(&WinVersion, sizeof(OSVERSIONINFOEX));
	WinVersion.dwOSVersionInfoSize =sizeof(OSVERSIONINFOEX);	
	BOOL flag=GetVersionEx((OSVERSIONINFO *) &WinVersion);
	if(flag)
	{
	   dwMajorVersion=WinVersion.dwMajorVersion;
       dwMinorVersion=WinVersion.dwMinorVersion;
	   dwPlatformId=WinVersion.dwPlatformId;
	   if(dwMajorVersion==3)
	   {
		    m_nWinVersion=WIN_NT351;
	   }
	   else if(dwMajorVersion==4 && dwMinorVersion==0 && dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
	   {
		    m_nWinVersion=WIN_95;
	   }
	   else if(dwMajorVersion==4 && dwMinorVersion==0 && dwPlatformId==VER_PLATFORM_WIN32_NT)
	   {
		    m_nWinVersion=WIN_NT40;
	   }
	   else if(dwMajorVersion==4 && dwMinorVersion==10)
	   {
		    m_nWinVersion=WIN_98;
	   }
	   else if(dwMajorVersion==4 && dwMinorVersion==90)
	   {
		    m_nWinVersion=WIN_ME;
	   }
	   else if(dwMajorVersion==5 && dwMinorVersion==0)
	   {
		    m_nWinVersion=WIN_2000;
	   }
	   else if(dwMajorVersion==5 && dwMinorVersion==1)
	   {
		    m_nWinVersion=WIN_XP;
	   }
	   else
	   {
		    m_nWinVersion=WIN_UNKNOWN;
	   }	      
	}

}
