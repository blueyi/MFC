// TDS_chartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TDS_chart.h"
#include "TDS_chartDlg.h"
#include <comdef.h>

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
// CTDS_chartDlg dialog

CTDS_chartDlg::CTDS_chartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTDS_chartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTDS_chartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lCharttype=0;
	m_Timer=0;
}

void CTDS_chartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTDS_chartDlg)
	DDX_Control(pDX, IDC_MSCHART1, m_ChartControl);
	DDX_Control(pDX, IDC_SPIN1, m_SpinControl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTDS_chartDlg, CDialog)
	//{{AFX_MSG_MAP(CTDS_chartDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDREFRESH, OnRefresh)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AUTOREFRESH, OnAutorefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTDS_chartDlg message handlers

//--------------------------------------------------------
// Author -Alex .C. Punnen
// email - alexcpn@hotmail.com
// Date  - 24/May/2003
//--------------------------------------------------------

BOOL CTDS_chartDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here

	int nBound;
	//---------------------------------------------
	// Called to populate the m_filedetails list
	//---------------------------------------------
	
	nBound=	PopulateChartData();
	
	//---------------------------------------------
	//	Adding Data to Chart
	//---------------------------------------------

	AddOrUpdateChartData(nBound);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTDS_chartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTDS_chartDlg::OnPaint() 
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
HCURSOR CTDS_chartDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//--------------------------------------------------------
// Author -Alex .C. Punnen
// email - alexcpn@hotmail.com
// Date  - 24/May/2003
//--------------------------------------------------------
void CTDS_chartDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_ChartControl.SetChartType(lCharttype);
	m_ChartControl.Refresh(); 

	lCharttype++;
	
	if(lCharttype>9)
		lCharttype=0;
	
	*pResult = 0;
}

void CTDS_chartDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnGetMinMaxInfo(lpMMI);
}



//--------------------------------------------------------
// Author -Alex .C. Punnen
// email - alexcpn@hotmail.com
// Date  - 24/May/2003
//--------------------------------------------------------
int CTDS_chartDlg::PopulateChartData()
{
	//Forgive me for the bit elaborate list stucture
	// my application needed it to fill from a database query
	//however i am taKing out the complete recordset and database part
	
	m_filedetails.clear();  
	
	CString csTemp;
	
	int nBound=0;
	for(int i=1;i<11;i++)
	{
		
		FILEDETAILS filedetailsstruct;
			
		//below is the rowlabel,it SHOULD NOT be a string 
		//that can be converted to a valid number
	
		csTemp.Format("John_%d",i);
		filedetailsstruct.login=csTemp ;
		
		csTemp.Format("%d",i*4);
		filedetailsstruct.n9000 =csTemp;
		
		csTemp.Format("%d",i*6);
		filedetailsstruct.n9002 =csTemp;
		
		csTemp.Format("%d",i*8);
		filedetailsstruct.n9004=csTemp;
		
		csTemp.Format("%d",i*10);
		filedetailsstruct.nCancel=csTemp;
				
		m_filedetails.insert(m_filedetails.end(),filedetailsstruct);
		nBound++;
		
	}

		
	return nBound;

}
//--------------------------------------------------------
// Author -Alex .C. Punnen
// email - alexcpn@hotmail.com
// Date  - 24/May/2003
//--------------------------------------------------------

int CTDS_chartDlg::AddOrUpdateChartData(int noOfRows)
{
	COleSafeArray saRet;

	SAFEARRAYBOUND sab[2];

	sab[0].cElements =noOfRows;// give this exact
	sab[1].cElements = 5; //number of columns + 1 (because the first column is where we put 
						// the row labels - ie in 1.1, 2.1, 3.1, 4,1 etc

	sab[0].lLbound = sab[1].lLbound = 1;

	// Use the chart as the backdrop of the legend.
	m_ChartControl.SetShowLegend(TRUE);

	// Create the safe-array...

	saRet.Create(VT_BSTR, 2, sab);

	long index[2] = {0,0}; //a 2D graph needs a 2D array as index array
	BSTR bstr;
	index[0]=1;

	FILEDETAILS filedetailsstruct;
	CString cstemp;

	for(i=m_filedetails.begin();i!=m_filedetails.end();i++)
	{

			filedetailsstruct =(FILEDETAILS)*i;
			
			index[1]=1;
			bstr = filedetailsstruct.login.AllocSysString(); // Row label
			saRet.PutElement(index, bstr);

			index[1]=2;
	
			bstr = filedetailsstruct.n9000.AllocSysString(); // Data for column 1
			 ::SysFreeString(bstr);
			saRet.PutElement(index, bstr);
			
			index[1]=3;
			bstr = filedetailsstruct.n9002.AllocSysString(); // Data for column 2
			 ::SysFreeString(bstr);
			saRet.PutElement(index, bstr);

			index[1]=4;
			bstr = filedetailsstruct.n9004.AllocSysString(); // Data for column 3
			 ::SysFreeString(bstr);
			saRet.PutElement(index, bstr);

			index[1]=5;
			bstr = filedetailsstruct.nCancel.AllocSysString();// Data for column 4
			 ::SysFreeString(bstr);
			saRet.PutElement(index, bstr);

			index[0]++;
	
	}	
		
    m_ChartControl.SetChartData(saRet.Detach()); 
	
	m_ChartControl.SetColumnLabelCount(4); 
	m_ChartControl.SetColumn(1); 
	m_ChartControl.SetColumnLabel("Monday") ;
	m_ChartControl.SetColumn(2); 
	m_ChartControl.SetColumnLabel("Wednesday") ;
	m_ChartControl.SetColumn(3); 
	m_ChartControl.SetColumnLabel("Friday") ;
	m_ChartControl.SetColumn(4); 
	m_ChartControl.SetColumnLabel("Saturday") ;
return 1;

}

//--------------------------------------------------------
// Author -Alex .C. Punnen
// email - alexcpn@hotmail.com
// Date  - 24/May/2003
//--------------------------------------------------------
void CTDS_chartDlg::OnRefresh() 
{
	//---------------------------------------------
	// Called to populate the m_filedetails list
	//---------------------------------------------
	
	int nBound=	PopulateChartData();
	
	//---------------------------------------------
	//	Adding Data to Chart
	//---------------------------------------------

	AddOrUpdateChartData(nBound);

	m_ChartControl.UpdateData(0); 


	
}

CTDS_chartDlg::~CTDS_chartDlg()
{
	//m_oDB.Close();  
}

void CTDS_chartDlg::OnTimer(UINT nIDEvent) 
{
	OnRefresh();
	CDialog::OnTimer(nIDEvent);
}

void CTDS_chartDlg::OnAutorefresh() 
{
	CButton *AutoRefreshCheck =(CButton *)GetDlgItem(IDC_AUTOREFRESH);
	
	if(AutoRefreshCheck->GetCheck()) 
	{
		if(!m_Timer)
		m_Timer=  SetTimer(1,2000,0);		
	}
	else
	{
		if(m_Timer)
			KillTimer(m_Timer);
	}
}
//--------------------------------------------------------
// Author -Alex .C. Punnen
// email - alexcpn@hotmail.com
// Date  - 24/May/2003
//--------------------------------------------------------
void CTDS_chartDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(m_ChartControl.m_hWnd !=0) 
	{
	
		CButton *OK =(CButton *)GetDlgItem(IDOK);
		CButton *CANCEL =(CButton *)GetDlgItem(IDCANCEL);
		CButton *REFRESH =(CButton *)GetDlgItem(IDREFRESH);
		CButton *AUTOREFRESHCHECK =(CButton *)GetDlgItem(IDC_AUTOREFRESH);

		CSpinButtonCtrl *SpinButton=(CSpinButtonCtrl *)GetDlgItem(IDC_SPIN1);
		CStatic *Static=(CStatic *)GetDlgItem(IDC_STATIC);
		
		//RECT rect;
		//OK->GetClientRect(&rect); 
		
		OK->MoveWindow(cx-100,cy-40,77,23);
		CANCEL->MoveWindow(cx-180,cy-40,77,23);
		REFRESH->MoveWindow(cx-260,cy-40,77,23);
		AUTOREFRESHCHECK->MoveWindow(cx-350,cy-40,87,23);
		SpinButton->MoveWindow(cx-380,cy-40,25,23);
		
		Static->MoveWindow(15,13,cx-33,cy-59);
		m_ChartControl.MoveWindow(20,20,cx-40,cy-70);
	}
}
