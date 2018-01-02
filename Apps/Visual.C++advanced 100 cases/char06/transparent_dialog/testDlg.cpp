// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int FirstRun = 1;
void TransparentBlt( HDC hdcDest, int nXDest, int nYDest, int nWidth, 
			int nHeight, HBITMAP hBitmap, int nXSrc, int nYSrc,
			COLORREF colorTransparent, HPALETTE hPal );
static void MessageBlast(int iColumn,int iRow,LPCTSTR lpszMsg);

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
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
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

//Initialize fisrt run flag	
	FirstRun = 1;
//resize window to fit bitmap rect
	MoveWindow(200,200,535,105,TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint() 
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
		CPaintDC dc(this); // device context for painting
//Get and HDC pointer and pass it to SetupBk()
		HDC hdc;
		hdc = dc.GetSafeHdc();
		SetupBk(dc);
		CDialog::OnPaint();
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//Overridden to allow for mouse draging
void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}


//From Codeguru.. by Zafir Anjum, the transparency here is overkill, 
//SetupBk() will take care of the transparency that we are dealing with
void TransparentBlt( HDC hdcDest, int nXDest, int nYDest, int nWidth, 
			int nHeight, HBITMAP hBitmap, int nXSrc, int nYSrc,
			COLORREF colorTransparent, HPALETTE hPal )
{
	CDC dc, memDC, maskDC, tempDC;
	dc.Attach( hdcDest );
	maskDC.CreateCompatibleDC(&dc);
	CBitmap maskBitmap;
	
	//add these to store return of SelectObject() calls
	CBitmap* pOldMemBmp = NULL;
	CBitmap* pOldMaskBmp = NULL;
	HBITMAP hOldTempBmp = NULL;
	
	memDC.CreateCompatibleDC(&dc);
	tempDC.CreateCompatibleDC(&dc);
	CBitmap bmpImage;
	bmpImage.CreateCompatibleBitmap( &dc, nWidth, nHeight );
	pOldMemBmp = memDC.SelectObject( &bmpImage );
	
	// Select and realize the palette
	if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && hPal )
	{
		::SelectPalette( dc, hPal, FALSE );
		dc.RealizePalette();
		
		::SelectPalette( memDC, hPal, FALSE );
	}
	
	hOldTempBmp = (HBITMAP) ::SelectObject( tempDC.m_hDC, hBitmap );
	
	memDC.BitBlt( 0,0,nWidth, nHeight, &tempDC, nXSrc, nYSrc, SRCCOPY );
	
	// Create monochrome bitmap for the mask
	maskBitmap.CreateBitmap( nWidth, nHeight, 1, 1, NULL );
	pOldMaskBmp = maskDC.SelectObject( &maskBitmap );
	memDC.SetBkColor( colorTransparent );
	
	// Create the mask from the memory DC
	maskDC.BitBlt( 0, 0, nWidth, nHeight, &memDC, 
		0, 0, SRCCOPY );
	
	// Set the background in memDC to black. Using SRCPAINT with black 
	// and any other color results in the other color, thus making 
	// black the transparent color
	memDC.SetBkColor(RGB(0,0,0));
	memDC.SetTextColor(RGB(255,255,255));
	memDC.BitBlt(0, 0, nWidth, nHeight, &maskDC, 0, 0, SRCAND);
	
	// Set the foreground to black. See comment above.
	dc.SetBkColor(RGB(255,255,255));
	dc.SetTextColor(RGB(0,0,0));
	dc.BitBlt(nXDest, nYDest, nWidth, nHeight, &maskDC, 0, 0, SRCAND);
	
	// Combine the foreground with the background
	dc.BitBlt(nXDest, nYDest, nWidth, nHeight, &memDC, 
		0, 0, SRCPAINT);
	
	
	if (hOldTempBmp)
		::SelectObject( tempDC.m_hDC, hOldTempBmp);
	if (pOldMaskBmp)
		maskDC.SelectObject( pOldMaskBmp );
	if (pOldMemBmp)
		memDC.SelectObject( pOldMemBmp );
	
	dc.Detach();
}

//Used for debugging.....
static void MessageBlast(int iColumn,int iRow,LPCTSTR lpszMsg) 
{ 
	HDC hdcScreen; 

	// Get a raw screen DC 
	hdcScreen = GetWindowDC( GetDesktopWindow() ); 

	if (hdcScreen) 
	{ 
		TextOut( hdcScreen, iColumn, iRow, lpszMsg, lstrlen(lpszMsg)); 

		// Release the screen DC 
		ReleaseDC( GetDesktopWindow(), hdcScreen ); 
	} 
} 


//Setup the windows Region
//The windows region controls what the OS will draw in reguards to the window
//The loop below will search for the "magic color" and add it to a region
//then Xor the region and assign it to the window and viola.
void CTestDlg::SetupBk(HDC hdc)
{
	int X,Y,H,W;
	CBitmap CB; 
	CRect R;
	COLORREF C;
	GetWindowRect(&R);
	H = R.bottom - R.top;
	W = R.right - R.left;
	CB.LoadBitmap(IDB_BITMAP2);
	HBITMAP HB = (HBITMAP)CB;

	TransparentBlt( hdc , 0, 0, 535, 105, HB, 0, 0,0x00000000 , NULL );
	

//Only do this once because it takes some time.
//maybe should pre-make a seperate file to hold region data?
	if (FirstRun){
		int Set = 0;
		//begin pixel by pixel scan for transparent color
		for(X=0;X<=W;X++){
			for(Y=0;Y<=H;Y++){
				C = GetPixel(hdc,X,Y);
				//Get the color
				if(C == 0x00FFFFFF){
					if(Set == 0){
						//First, init the working region 
						//never delete Working, the OS does not store the value, only a pointer to it.
						Working.CreateRectRgn(X,Y,X+1,Y+1);
						Set = 1;
					}
					else{
						Temp.CreateRectRgn(X,Y,X+1,Y+1);
						//Add pixel to region
						Working.CombineRgn( &Working, &Temp,RGN_OR );
						Temp.DeleteObject();
					}
				}
			}
		}
		FirstRun = 0;
		Temp.CreateRectRgn(0,0,1200,1200);
		//flip to get the non-transparent region
		Working.CombineRgn( &Working, &Temp,RGN_XOR    );
		Temp.DeleteObject();
		if (Set) SetWindowRgn((HRGN)Working,TRUE);
		//redraw just incase.. trust me.. leave this here
		RedrawWindow();
	}
	
}
