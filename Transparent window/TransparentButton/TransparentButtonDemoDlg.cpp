// TransparentButtonDemoDlg.cpp : implementation file
//

/********************************************************************
*
*	TRANSPARENT BUTTON DEMO
*
*	This is a demo program to show the use of a bitmap-on-bitmap
*	approach when using button controls, and how these buttons can
*	be displayed with various degrees of transparency on a dynamic
*	background.  The buttons also produce anti-aliased edging for a
*	nice clean interface.
*
*	The dialog-based application is displayed as a circle to give a
*	stylistic effect to the typically mundane MFC program.
*
*	Thanks very much to many contributors at www.codeproject.com and
*	www.codeguru.com, including:
*
*	Niek Albers and Frederick Ackers for the CHoverButtonEx class
*	Paul Nettle for the WinDIB class and alphaBlend routine
*	Keith Rule for CMemDC
*
*	If this demo works, and you liked it, it was written by 
*
*						  Bob Carboni
*					www.carbonisoftware.com
*
*	If not, I don't know who put this pile of crap together...
*
********************************************************************/

#include "stdafx.h"
#include "TransparentButtonDemo.h"
#include "TransparentButtonDemoDlg.h"

#include <math.h>
#include "MemDC.h"
#include ".\transparentbuttondemodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static BOOL LoadBitmapAndPalette(CBitmap &bitmap, CPalette &pal)
{
	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	bitmap.GetObject( sizeof(ds), &ds );
	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;
	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL);			// Desktop DC
	if( nColors > 256 )	pal.CreateHalftonePalette( &dc );
	else{
		// Create the palette
		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject( &bitmap );
		::GetDIBColorTable( memDC, 0, nColors, pRGB );
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;
		for( int i=0; i < nColors; i++){
			pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}
		pal.CreatePalette( pLP );
		delete[] pLP;
		delete[] pRGB;
	}
	return TRUE;
}

static BOOL GetBitmapAndPalette(UINT nIDResource, CBitmap &bitmap, CPalette &pal)
{
	if (bitmap.m_hObject != NULL)
		bitmap.Detach();
	if (pal.m_hObject != NULL)
		pal.Detach();

	LPCTSTR lpszResourceName = (LPCTSTR)nIDResource;
	HBITMAP hBmp = (HBITMAP)::LoadImage( AfxGetInstanceHandle(), 
		lpszResourceName, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION );
	if( hBmp == NULL )return FALSE;
	bitmap.Attach( hBmp );

	return LoadBitmapAndPalette(bitmap, pal);
}

static void DrawTheBackground(CWnd *view,CDC *pDC,CPalette *mp_palette,CBitmap *mp_bitmap)
{
	if(pDC->IsPrinting())return;
	CRect rect;
	CPalette *old_palette=NULL;
	// Select and realize the palette
	if( pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE && mp_palette->m_hObject != NULL ){
		old_palette=pDC->SelectPalette( mp_palette, FALSE );
		pDC->RealizePalette();
	}
	view->GetClientRect(rect);
	pDC->DPtoLP(rect);
	CMemDC DC(pDC,rect);
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(pDC))return;
	BITMAP bm;
	mp_bitmap->GetBitmap(&bm);
	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(mp_bitmap);
	for(int i=((int)floor((double)rect.left/bm.bmWidth))*bm.bmWidth;i<=rect.right/*rect.Width()*/;i+=bm.bmWidth)
	     for(int j=((int)floor((double)rect.top/bm.bmHeight))*bm.bmHeight;j<=rect.bottom/*rect.Height()*/;j+=bm.bmHeight)
		DC->BitBlt(i, j, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);	
	pDC->SelectPalette(old_palette,FALSE);
	pDC->RealizePalette();	
}

// CTransparentButtonDemoDlg dialog



CTransparentButtonDemoDlg::CTransparentButtonDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransparentButtonDemoDlg::IDD, pParent),
	m_nWidth(300),
	m_nHeight(300)
{
	m_nBkGrndBitmapID = IDB_BKGRND;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransparentButtonDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_OpenButton);
	DDX_Control(pDX, IDC_BUTTON2, m_SaveButton);
	DDX_Control(pDX, IDC_BUTTON3, m_Btn1);
	DDX_Control(pDX, IDC_BUTTON4, m_Btn2);
	DDX_Control(pDX, IDC_BUTTON5, m_Btn3);
	DDX_Control(pDX, IDC_BUTTON6, m_Btn4);
	DDX_Control(pDX, IDOK, m_ExitBtn);
}

BEGIN_MESSAGE_MAP(CTransparentButtonDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedNextBg)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedNextBg)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedNextBg)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedNextBg)
END_MESSAGE_MAP()


// CTransparentButtonDemoDlg message handlers

BOOL CTransparentButtonDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Make the window a circle sized to background bitmap
	SetWindowPos(NULL, 0, 0, m_nWidth, m_nHeight, SWP_NOMOVE | SWP_NOOWNERZORDER);
	m_WinRgn.CreateEllipticRgn(0, 0, m_nWidth, m_nHeight);
	SetWindowRgn(m_WinRgn , TRUE );

	// Create "pill" style buttons
	HRGN rp = CreateEllipticRgn(0, 0, 75, 48);

	m_OpenButton.SetHorizontal(TRUE);
	m_OpenButton.SetRegion(rp);
	m_OpenButton.LoadRaw(IDR_OPEN, 300, 48);
	m_OpenButton.SetToolTipText("Open a File");

	m_SaveButton.SetHorizontal(TRUE);
	m_SaveButton.SetRegion(rp);
	m_SaveButton.LoadRaw(IDR_SAVE, 300, 48);
	m_SaveButton.SetToolTipText("Save the File");

	DeleteObject(rp);

	// Create round buttons
	HRGN r = CreateEllipticRgn(0, 0, 48, 48);

	m_Btn1.SetHorizontal(TRUE);
	m_Btn1.SetRegion(r);
	m_Btn1.LoadRaw(IDR_RED, 192, 48);
	m_Btn1.SetToolTipText("Press Me!");

	m_Btn2.SetHorizontal(TRUE);
	m_Btn2.SetRegion(r);
	m_Btn2.LoadRaw(IDR_PURPLE, 192, 48);
	m_Btn2.SetToolTipText("Press Me!");

	m_Btn3.SetHorizontal(TRUE);
	m_Btn3.SetRegion(r);
	m_Btn3.LoadRaw(IDR_PURPLE, 192, 48);
	m_Btn3.SetToolTipText("Press Me!");

	m_Btn4.SetHorizontal(TRUE);
	m_Btn4.SetRegion(r);
	m_Btn4.LoadRaw(IDR_RED, 192, 48);
	m_Btn4.SetToolTipText("Press Me!");

	m_ExitBtn.SetHorizontal(TRUE);
	m_ExitBtn.SetRegion(r);
	m_ExitBtn.LoadRaw(IDR_EXIT, 192, 48);
	m_ExitBtn.SetToolTipText("Later...");

	DeleteObject(r);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTransparentButtonDemoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{
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
		// Draw the background using current bitmap
		::GetBitmapAndPalette(m_nBkGrndBitmapID, m_Bitmap, m_Palette);
		::DrawTheBackground(this, &dc, &m_Palette, &m_Bitmap);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTransparentButtonDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTransparentButtonDemoDlg::OnBnClickedNextBg()
{
	if (m_nBkGrndBitmapID == IDB_BKGRND)
		m_nBkGrndBitmapID = IDB_BG2;
	else if (m_nBkGrndBitmapID == IDB_BG2)
		m_nBkGrndBitmapID = IDB_BG3;
	else if (m_nBkGrndBitmapID == IDB_BG3)
		m_nBkGrndBitmapID = IDB_BG4;
	else if (m_nBkGrndBitmapID == IDB_BG4)
		m_nBkGrndBitmapID = IDB_BG5;
	else if (m_nBkGrndBitmapID == IDB_BG5)
		m_nBkGrndBitmapID = IDB_BG6;
	else if (m_nBkGrndBitmapID == IDB_BG6)
		m_nBkGrndBitmapID = IDB_BKGRND;

	m_OpenButton.RefreshBkgrnd();
	m_SaveButton.RefreshBkgrnd();
	m_Btn1.RefreshBkgrnd();
	m_Btn2.RefreshBkgrnd();
	m_Btn3.RefreshBkgrnd();
	m_Btn4.RefreshBkgrnd();
	m_ExitBtn.RefreshBkgrnd();

	Invalidate();
	UpdateWindow();
}
