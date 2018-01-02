// LineChartControlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LineChartControlDemo.h"
#include "LineChartControlDemoDlg.h"
#include ".\linechartcontroldemodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GET_RANDOM( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CLineChartControlDemoDlg dialog



CLineChartControlDemoDlg::CLineChartControlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineChartControlDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iBtnExitFromRight = 10;
	m_iBtnExitFromBottom =10;
}

void CLineChartControlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLOT, m_plot);
	DDX_Control(pDX, IDOK, m_btnExit);
}

BEGIN_MESSAGE_MAP(CLineChartControlDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_DISP_LINE1, OnBnClickedDispLine1)
	ON_BN_CLICKED(IDC_DISP_LINE2, OnBnClickedDispLine2)
END_MESSAGE_MAP()


// CLineChartControlDemoDlg message handlers

BOOL CLineChartControlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	((CButton*)GetDlgItem(IDC_DISP_LINE1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_DISP_LINE2))->SetCheck(TRUE);

	//remember initial position
	GetWindowRect(&m_rectOldWindow);
	m_btnExit.GetClientRect(&m_rectBtnExit);
	m_plot.GetWindowRect(&m_rectOldPlotWindow);
	TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());
	ScreenToClient(&m_rectOldPlotWindow);
	TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());

	m_plot.AddLine(PS_SOLID,RGB(255,0,0));
	m_plot.AddLine(PS_SOLID,RGB(0,255,0));

	m_plot.GetAxisY().m_color=RGB(0,255,0);
	m_plot.GetAxisY().m_dMinValue=5000;
	m_plot.GetAxisY().m_dMaxValue=6000;
	m_plot.CalcLayout();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLineChartControlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLineChartControlDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLineChartControlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLineChartControlDemoDlg::OnTimer(UINT nIDEvent)
{
	BOOL bAxisYChanged = FALSE;
	//In fact, x values are not used when draw lines
	//If you want to use x values in any way, 
	//you may calculate point x in the way that point y is calculated.
	//see also: DrawLines(CDC* pDC);
	double x=time(0);
	double y0=(double)GET_RANDOM(4000,6899);
	double y1=(double)GET_RANDOM(6000,8899);
	if(y0<m_plot.GetAxisY().m_dMinValue)
	{
		m_plot.GetAxisY().m_dMinValue=y0*0.95;
		bAxisYChanged = TRUE;
	}else if(y0>m_plot.GetAxisY().m_dMaxValue)
	{
		m_plot.GetAxisY().m_dMaxValue=y0*1.05;
		bAxisYChanged = TRUE;
	}
	if(y1<m_plot.GetAxisY().m_dMinValue)
	{
		m_plot.GetAxisY().m_dMinValue=y1*0.95;
		bAxisYChanged = TRUE;
	}else if(y1>m_plot.GetAxisY().m_dMaxValue)
	{
		m_plot.GetAxisY().m_dMaxValue=y1*1.05;
		bAxisYChanged = TRUE;
	}

	if(bAxisYChanged)
	{
		m_plot.CalcLayout();
	}

	m_plot.GetLine(0).AddPoint(x,y0);
	m_plot.GetLine(1).AddPoint(x,y1);
		

	//CDialog::OnTimer(nIDEvent);
}

void CLineChartControlDemoDlg::OnBnClickedStart()
{
	SetTimer(1,150,NULL);
	m_plot.SetRate(150);//
	m_plot.Start();

	GetDlgItem(IDC_START)->EnableWindow(FALSE);

}

void CLineChartControlDemoDlg::OnBnClickedStop()
{
	KillTimer(1);
	m_plot.Stop();
	for(int i=0;i<m_plot.GetLineCount();i++)
	{
		m_plot.GetLine(i).RemoveAllPoints();
	}
	GetDlgItem(IDC_START)->EnableWindow();
	m_plot.Invalidate();
}

/*
 Set new control postition as needed.
 */
void CLineChartControlDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);

		
	if(m_btnExit.GetSafeHwnd())
	{
		m_btnExit.MoveWindow(rect.right-m_iBtnExitFromRight-m_rectBtnExit.Width(),
		rect.bottom-m_iBtnExitFromBottom-m_rectBtnExit.Height(),
		m_rectBtnExit.Width(),m_rectBtnExit.Height());
	}
	if(m_plot.GetSafeHwnd())
	{
		TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());

		m_plot.MoveWindow(m_rectOldPlotWindow.left,
			m_rectOldPlotWindow.top,
			rect.right-m_iBtnExitFromRight-5-m_rectOldPlotWindow.left,
			rect.bottom-m_iBtnExitFromBottom-m_rectBtnExit.Height()-7-m_rectOldPlotWindow.top);
	}

	
}
/*
 Check window size while resizeing, if small than origianl size, then restore to original size.
 */
void CLineChartControlDemoDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	if(pRect->right - pRect->left <=m_rectOldWindow.Width())
     	pRect->right = pRect->left + m_rectOldWindow.Width();
	
     if(pRect->bottom - pRect->top <=m_rectOldWindow.Height())
     	pRect->bottom = pRect->top + m_rectOldWindow.Height();

	CDialog::OnSizing(fwSide, pRect);
}

void CLineChartControlDemoDlg::OnBnClickedDispLine1()
{
	m_plot.GetLine(0).m_bDraw = ((CButton*)GetDlgItem(IDC_DISP_LINE1))->GetCheck(); 
}

void CLineChartControlDemoDlg::OnBnClickedDispLine2()
{
	m_plot.GetLine(1).m_bDraw = ((CButton*)GetDlgItem(IDC_DISP_LINE2))->GetCheck(); 
}
