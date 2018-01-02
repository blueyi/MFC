/////////////////////////////////////////////////////////////////////////////
// CHardwareInfoDlg.cpp : implementation file
//
// Hardware information checking.
// All rights reserved.
//
// Written by Naveen Kohli (naveen@a3ds.com)
// Version 1.0
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc. to
//    naveen@a3ds.com
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "HardwareInfo.h"
#include "HardwareInfoDlg.h"

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
// CHardwareInfoDlg dialog

CHardwareInfoDlg::CHardwareInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHardwareInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHardwareInfoDlg)
	m_stMaxAddress = _T("");
	m_stNumProcessors = _T("");
	m_stOemId = _T("");
	m_stMinAdress = _T("");
	m_stPageSize = _T("");
	m_stProcessorLevel = _T("");
	m_stMask = _T("");
	m_stProRevision = _T("");
	m_stProcessorType = _T("");
	m_stArchitecture = _T("");
	m_stMouse = _T("");
	m_stButtonsSwapped = _T("");
	m_stMouseSpeed = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHardwareInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHardwareInfoDlg)
	DDX_Control(pDX, IDC_SPEED_STATIC, m_SpeedStatic);
	DDX_Control(pDX, IDC_SWAPPED_STATIC, m_SwappedStatic);
	DDX_Control(pDX, IDC_MOUSE_STATIC, m_MouseStatic);
	DDX_Control(pDX, IDC_PROARCH_STATIC, m_ArchStatic);
	DDX_Control(pDX, IDC_PROTYPE_STATIC, m_ProcessorTypeStatic);
	DDX_Control(pDX, IDC_PROREV_STATIC, m_ProRevStatic);
	DDX_Control(pDX, IDC_PROMASK_STATIC, m_MaskStatic);
	DDX_Control(pDX, IDC_PROLEVEL_STATIC, m_ProLevelStatic);
	DDX_Control(pDX, IDC_PAGESIZE_STATIC, m_PageSzStatic);
	DDX_Control(pDX, IDC_OEMID_STATIC, m_OemIdStatic);
	DDX_Control(pDX, IDC_NUMPRO_STATIC, m_NumProcStatic);
	DDX_Control(pDX, IDC_MINADRS_STATIC, m_MinAdStatic);
	DDX_Control(pDX, IDC_MAXADRS_STATIC, m_MaxAdStatic);
	DDX_Text(pDX, IDC_MAXADRS_STATIC, m_stMaxAddress);
	DDX_Text(pDX, IDC_NUMPRO_STATIC, m_stNumProcessors);
	DDX_Text(pDX, IDC_OEMID_STATIC, m_stOemId);
	DDX_Text(pDX, IDC_MINADRS_STATIC, m_stMinAdress);
	DDX_Text(pDX, IDC_PAGESIZE_STATIC, m_stPageSize);
	DDX_Text(pDX, IDC_PROLEVEL_STATIC, m_stProcessorLevel);
	DDX_Text(pDX, IDC_PROMASK_STATIC, m_stMask);
	DDX_Text(pDX, IDC_PROREV_STATIC, m_stProRevision);
	DDX_Text(pDX, IDC_PROTYPE_STATIC, m_stProcessorType);
	DDX_Text(pDX, IDC_PROARCH_STATIC, m_stArchitecture);
	DDX_Text(pDX, IDC_MOUSE_STATIC, m_stMouse);
	DDX_Text(pDX, IDC_SWAPPED_STATIC, m_stButtonsSwapped);
	DDX_Text(pDX, IDC_SPEED_STATIC, m_stMouseSpeed);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHardwareInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CHardwareInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHardwareInfoDlg message handlers

BOOL CHardwareInfoDlg::OnInitDialog()
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
	
	// Get processor information.

	if (!GetProcessorInfo ()) {
		AfxMessageBox (_T ("Error getting system hardware information"), MB_ICONSTOP);
	}

	// Get mouse information.

	if (!GetMouseInfo ()) {
		AfxMessageBox (_T ("Error getting mouse information"), MB_ICONSTOP);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHardwareInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHardwareInfoDlg::OnPaint() 
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
HCURSOR CHardwareInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

bool CHardwareInfoDlg::GetProcessorInfo()
{
	SYSTEM_INFO sysInfo;
	char str [MAX_PATH];

	// Get the hardware information

	GetSystemInfo (&sysInfo);

	// Lets check the processor type first

	if (sysInfo.dwProcessorType  == PROCESSOR_INTEL_386) {
		m_stProcessorType = _T ("Intel 386");
	}
	else if (sysInfo.dwProcessorType  == PROCESSOR_INTEL_486) {
		m_stProcessorType = _T ("Intel 486");
	}
	else if (sysInfo.dwProcessorType  == PROCESSOR_INTEL_PENTIUM) {
		m_stProcessorType = _T ("Intel Pentium");
	}
	else if (sysInfo.dwProcessorType  == PROCESSOR_MIPS_R4000) {
		// only for NT
		m_stProcessorType = _T ("MIPS");
	}
	else if (sysInfo.dwProcessorType  == PROCESSOR_ALPHA_21064) {
		// only for NT
		m_stProcessorType = _T ("Alpha");
	}
	else {
		m_stProcessorType = _T ("Unknown");
	}

	// check number of processors

	itoa (sysInfo.dwNumberOfProcessors , str, 10);

	m_stNumProcessors = CString (str);

	// Check the architecture type and processor level

	// Windows 95 doesn't use processor level

	if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
		m_stArchitecture = _T ("Pentium");
		switch (sysInfo.wProcessorLevel) {
			case 3:
				m_stProcessorLevel = _T ("Intel 80386");
				break;
			case 4:
				m_stProcessorLevel = _T ("Intel 80486");
				break;
			case 5:
				m_stProcessorLevel = _T ("Pentium");
				// Check if the MMX instruction set is availbale or not.

				if (IsProcessorFeaturePresent (PF_MMX_INSTRUCTIONS_AVAILABLE)) {
					m_stProcessorLevel += _T (" MMX");
				}
				break;
			case 6:
				m_stProcessorLevel = _T ("Pentium (II/Pro)");
				break;
		}
	}
	else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MIPS) {
		m_stArchitecture = _T ("MIPS");
		if (sysInfo.wProcessorLevel == 0004) {
			m_stProcessorLevel = _T ("MIPS R4000");
		}
		else {
			m_stProcessorLevel = _T ("Unknown");
		}
	}
	else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA) {
		m_stArchitecture = _T ("Alpha");

		itoa (sysInfo.wProcessorLevel , str, 10);

		m_stProcessorLevel = m_stArchitecture + CString (str);
	}
	else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_PPC) {
		m_stArchitecture = _T ("PPC");

		switch (sysInfo.wProcessorLevel) {
			case 1:
				m_stProcessorLevel = _T ("PPC 601");
				break;
			case 3:
				m_stProcessorLevel = _T ("PPC 603");
				break;
			case 4:
				m_stProcessorLevel = _T ("PPC 604");
				break;
			case 6:
				m_stProcessorLevel = _T ("PPC 603+");
				break;
			case 9:
				m_stProcessorLevel = _T ("PPC 604+");
				break;
			case 20:
				m_stProcessorLevel = _T ("PPC 620");
				break;
		}
	}
	else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN) {
		m_stArchitecture = _T ("Unknown");
	}


	// Check page size

	itoa (sysInfo.dwPageSize , str, 10);
	m_stPageSize = CString (str);

	// Application address

	TCHAR buffer [64];

	sprintf( buffer, "%p", sysInfo.lpMaximumApplicationAddress);

	m_stMaxAddress = _T ("0x") + CString (buffer);
	
	sprintf( buffer, "%p", sysInfo.lpMinimumApplicationAddress);

	m_stMinAdress = _T ("0x") + CString (buffer);

	// Get active processor mask
	// It represent how many processors are active (?? I am not sure)

	itoa (sysInfo.dwActiveProcessorMask , str, 10);
	m_stMask = CString (str);

	UpdateData (FALSE);

	return (true);
}

bool CHardwareInfoDlg::GetMouseInfo()
{
	int mouseInfo[3];	// We need an array (size 3) of int for mouse information
	TCHAR str [32];
	BOOL stat;

	// Check if mouse is present or not.

	stat = GetSystemMetrics (SM_MOUSEPRESENT);

	if (!stat) {
		m_stMouse = _T ("Not installed");
	}
	else {
		m_stMouse = _T ("Installed");

		// Check if buttons are swapped

		stat = GetSystemMetrics (SM_SWAPBUTTON);

		m_stButtonsSwapped = (stat) ? _T ("Swapped") : _T ("Not swapped");
		
	}

	// Get mouse speed

	SystemParametersInfo (SPI_GETMOUSE, NULL, mouseInfo, NULL);
	
	// mouseInfo [0] & mouseInfo [1], give twp threshold values for mouse
	// mpuseInfo [2] gives the mouse speed.

	sprintf (str, "%d", mouseInfo[2]);

	m_stMouseSpeed = CString (str);

	UpdateData (FALSE);

	return (true);
}
