// MyFade.cpp : implementation file
//

#include "stdafx.h"
#include "MyFade.h"

#pragma warning(disable: 4201)

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#pragma warning(default: 4201)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WC_FADEWND	_T("FadeWnd")
/////////////////////////////////////////////////////////////////////////////
// CMyFade

CMyFade::CMyFade(CWnd*		pParent)
{
		// register the window
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, WC_FADEWND, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = 0;
		wndcls.cbWndExtra		= 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;	// no application icon
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = NULL;	// no background
        wndcls.lpszMenuName     = NULL;	// no manu application
        wndcls.lpszClassName    = WC_FADEWND;

        if (!AfxRegisterClass(&wndcls))
            AfxThrowResourceException();
    }

	m_hBitmap		= NULL;
	m_hNewBitmap	= NULL;
	m_pWndLock		= NULL;
	
}

CMyFade::~CMyFade()
{
	if (m_hBitmap)		{	DeleteObject(m_hBitmap);	m_hBitmap    = NULL;	}
	if (m_hNewBitmap)	{	DeleteObject(m_hNewBitmap);	m_hNewBitmap = NULL;	}

	if (m_pWndLock)
	{
		m_pWndLock->SetFocus();
	}
}


BEGIN_MESSAGE_MAP(CMyFade, CWnd)
	//{{AFX_MSG_MAP(CMyFade)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFade message handlers

void CMyFade::FadeScreen(CWnd *pParent)
{
	if(pParent)
	{
		CMyFade *pFade=new CMyFade(pParent);
		if(pFade)
		{
			pFade->Create(pParent, CRect(0, 0, 0, 0));
		}
	}
}

void CMyFade::OnDraw(CDC* pDC)
{
	CRect rc;
	GetWindowRect(rc);
	HDC hbmDC=CreateCompatibleDC(pDC->GetSafeHdc());
	HBITMAP hOldbmp=(HBITMAP)::SelectObject(hbmDC, m_hNewBitmap);
	// 将屏幕位图再输入到屏幕上去
	BitBlt(pDC->GetSafeHdc(), 0, 0, rc.Width(), rc.Height(),
		hbmDC, 0, 0, SRCCOPY);
	SelectObject(hbmDC, hOldbmp);
	DeleteObject(hbmDC);
}

void CMyFade::OnPaint() 
{
	CPaintDC dc(this);
	//OnDraw(&dc);
}

HBITMAP CMyFade::CopyScreenToBitmap(LPRECT lpRect)
{
	HDC	hScrDC, hMemDC;			// screen DC and memory DC     
	int	nX, nY, nX2, nY2;		// coordinates of rectangle to grab     
	int	nWidth, nHeight;		// DIB width and height     
	int	xScrn,  yScrn;			// screen resolution      

	HGDIOBJ	hOldBitmap, hBitmap;
	if (IsRectEmpty(lpRect))       
		return NULL;      
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);     
	hMemDC = CreateCompatibleDC(hScrDC);
	xScrn = GetDeviceCaps(hScrDC, HORZRES);     
	yScrn = GetDeviceCaps(hScrDC, VERTRES); 

	nX  = lpRect->left;     
	nY  = lpRect->top;     
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	if (nX  < 0)		nX = 0;     
	if (nY  < 0)		nY = 0;     
	if (nX2 > xScrn)	nX2 = xScrn;     
	if (nY2 > yScrn)	nY2 = yScrn;      

	nWidth	= nX2 - nX;     
	nHeight	= nY2 - nY;      

	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight); 
	hOldBitmap = SelectObject(hMemDC, hBitmap);  
    // 将屏幕输入到内存DC里面去，再通过SelectObject到位图句柄里面
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);     
	// 将刚刚得到到的屏幕位图置换出句柄
	hBitmap=SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hScrDC);     
	DeleteDC(hMemDC); 
	return (HBITMAP)hBitmap;
}


BOOL CMyFade::Create(CWnd *pParent, CRect rc)
{
	if (!pParent  ||  !IsWindow(pParent->GetSafeHwnd()))
	{
		MessageBox("error1");
		return false;
	}

	CClientDC dcParent(pParent);
	if (dcParent.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		MessageBox("error2");
		return FALSE;
	}
	
	GetDesktopWindow()->GetWindowRect(rc);
	CString	szText;

	GetDesktopWindow()->GetWindowText(szText);

	if (!CWnd::CreateEx(
			0,
			WC_FADEWND,
			szText,
			WS_POPUP | WS_CHILD | WS_VISIBLE,
			rc,
			pParent,
			NULL,
			NULL))
	{
		MessageBox("error3");
		return FALSE;
	}
	/*
	if(pParent!=GetDesktopWindow())
	{
		m_pWndLock=pParent;
		m_pWndLock->EnableWindow(false);
		HRGN hRgn=CreateRectRgn(0, 0, 0, 0);
		int regiontype=m_pWndLock->GetWindowRgn(hRgn);
		if(regiontype!=ERROR)
		{
			MessageBox("error4");
			SetWindowRgn(hRgn, false);
		}
		DeleteObject(hRgn);
	}
	*/
	m_hBitmap	= CopyScreenToBitmap(rc);
	
	SetTimer(1, 2000, NULL);
	
}

//////////////////////////////////////////////////////////////////////////
// 核心函数，将屏幕变暗
HBITMAP CMyFade::FadeBitmap(HBITMAP hBmp, double dfTrans)
{
	HBITMAP hRetBmp = NULL;
	if (hBmp)
	{
		HDC hBufferDC = CreateCompatibleDC(NULL);
		HGDIOBJ hPrevBufObject = SelectObject(hBufferDC, hBmp);

		HDC hDirectDC = CreateCompatibleDC(NULL);	// DC for working		
		if (hDirectDC)
		{
			BITMAP bm;
			GetObject(hBmp, sizeof(bm), &bm);
			BITMAPINFO bmInfo; 
			ZeroMemory(&bmInfo,sizeof(bmInfo));
			bmInfo.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
			bmInfo.bmiHeader.biWidth	= bm.bmWidth;
			bmInfo.bmiHeader.biHeight	= bm.bmHeight;
			bmInfo.bmiHeader.biPlanes	=  1;
			bmInfo.bmiHeader.biBitCount	= 32;		
			UINT* ptPixels;		
			HBITMAP hDirectBitmap = CreateDIBSection(hDirectDC,
				(BITMAPINFO*)&bmInfo,
				DIB_RGB_COLORS,(void**)&ptPixels, NULL, 0);
			if (hDirectBitmap)
			{
				// 将hDirectBitmap放入hDirectDC中处理
				HGDIOBJ hPrevBufDirObject = SelectObject(hDirectDC, hDirectBitmap);
				// 当前将原hBmp即屏幕的所有像素写入到hDirectDC
				// 即需要对像素灰度处理的DC中
				BitBlt(hDirectDC,0,0,bm.bmWidth,bm.bmHeight,hBufferDC,0,0,SRCCOPY);					
				
				int iAlpha = (int)(255.0 * dfTrans / 100.0);
				
				int nSize = bm.bmWidth * bm.bmHeight;
				for (int i=0; i<nSize; i++)
				{			
					// 0.212671 * R + 0.715160 * G + 0.072169 * B
					int iSrcR = (ptPixels[i]) & 0x00ff0000 >> 16;
					int iSrcG = ptPixels[i] & 0x0000ff00 >> 8;
					int iSrcB = ptPixels[i] & 0x000000ff;
					int iGrey = (iSrcR * 54 + iSrcG * 182 + iSrcB * 19) >> 8;
					
					COLORREF Col =iGrey ; //RGB(iGrey, iGrey, iGrey) ; 
					ptPixels[i] = RGB(
						(GetBValue( Col ) * iAlpha + iSrcB * (255 - iAlpha)) >> 8,
						(GetGValue( Col ) * iAlpha + iSrcG * (255 - iAlpha)) >> 8,
						(GetRValue( Col ) * iAlpha + iSrcR * (255 - iAlpha)) >> 8 );
				}
				SelectObject(hDirectDC,hPrevBufDirObject);		
				hRetBmp = hDirectBitmap;
			}
			DeleteDC(hDirectDC);
		}
		SelectObject(hBufferDC, hPrevBufObject);
		DeleteDC(hBufferDC);
	}
	return hRetBmp;
}

static i=0;

void CMyFade::OnTimer(UINT nIDEvent) 
{
	CWnd::OnTimer(nIDEvent);
	CClientDC dc(this);
	
	i+=2;
	if(i>100)
	{
		KillTimer(1);
		return;
	}
	DWORD dwStartCount = timeGetTime();
	if(m_hNewBitmap)
	{
		DeleteObject(m_hNewBitmap);
		m_hNewBitmap = NULL;
	}
	m_hNewBitmap = FadeBitmap(m_hBitmap,(double)i);
	OnDraw(&dc);
	DWORD dwEndCount = timeGetTime();	// tick counter in milliseconds

}
