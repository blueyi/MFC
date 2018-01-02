// ButtonSubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonSub.h"
#include "ButtonSubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonSubDlg dialog

CButtonSubDlg::CButtonSubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CButtonSubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CButtonSubDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CButtonSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonSubDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CButtonSubDlg, CDialog)
	//{{AFX_MSG_MAP(CButtonSubDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonSubDlg message handlers

BOOL CButtonSubDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//but.SubclassDlgItem(IDC_BUTTON1,this);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	idcount=0;
#ifdef _SAMPLE1
	pdc=new CClientDC(this);
#endif

#ifdef _SAMPLE2
	but= new CMyButton();
	but->Create("Hello",WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,CRect(10,10,100,100),this,1000+idcount);
#endif
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CButtonSubDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CButtonSubDlg::OnPaint() 
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
HCURSOR CButtonSubDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CButtonSubDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
#ifdef _SAMPLE1
	pdc->BeginPath();
	pdc->MoveTo(point);
	spoint=epoint=point;
	SetCapture();
#endif
	CDialog::OnLButtonDown(nFlags, point);
}

void CButtonSubDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
#ifdef _SAMPLE1
	pdc->EndPath();
	cRgn.DeleteObject();
	cRgn.CreateFromPath(pdc); 
	HRGN rrgn;
	rrgn=::CreateRectRgn(0,0,0,0);
	int res=CombineRgn(rrgn,cRgn.operator HRGN(),0,RGN_COPY);
	
	if(NULLREGION ==res)
		MessageBox("Null Region::Cannot create region for button");
	else if(ERROR==res)
		MessageBox("Error::Cannot create region");
	else
	{
		CBrush br;br.CreateSolidBrush(RGB(255,0,0));
		CRect rect;
		GetClientRect(rect);
		but= new CMyButton();
		but->SetRgn(CRgn::FromHandle(rrgn)); 
		but->Create("",WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_PUSHBUTTON,rect,this,1000+idcount);
		idcount++;
	}
	ReleaseCapture();
#endif
	CDialog::OnLButtonUp(nFlags, point);
}

void CButtonSubDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString mouse;
	mouse.Format("Irregular Buttons - X:%d Y:%d",point.x,point.y);
	SetWindowText(mouse);
	if(nFlags==MK_LBUTTON)
	{
#ifdef _SAMPLE1
		CClientDC dc(this);
		pdc->LineTo(point);
		dc.MoveTo(spoint);
		dc.LineTo(point);
		spoint=point;	// just a usual thing. no use here.
#endif
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CButtonSubDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(HIWORD(wParam)==BN_CLICKED)
	{
		for(int i=0;i<idcount;i++)
		{
			if(LOWORD(wParam)==1000+i)
			{
				CString smsg;smsg.Format("Button %d Clicked",i+1);
				MessageBox(smsg);
				break;
			}
		}
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CButtonSubDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	for(int i=0;i<idcount;i++)
	{
		CMyButton *bt=(CMyButton *)GetDlgItem(1000+i);
		if(bt) 
			delete bt;
	}
#ifdef _SAMPLE1
	if(pdc) 
		delete pdc;
#endif
}
