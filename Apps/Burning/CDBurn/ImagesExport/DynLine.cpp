// DynLine.cpp : implementation file
//

#include "stdafx.h"
#include "DynLine.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LONG	g_lDisplay = 0;
HANDLE	g_hEnd;

UINT	DispThread(LPVOID lpParam)
{
	CDynLine* pWnd = (CDynLine*)lpParam;
	CClientDC dcClient(pWnd);
	CDC		dcMem;
	dcMem.CreateCompatibleDC(&dcClient);
	BITMAP	bits;
	pWnd->m_bmp.GetBitmap(&bits);
	CBitmap *pBmp = (CBitmap*)dcMem.SelectObject( pWnd->m_bmp );

	CSize	size(0,0);

	while(g_lDisplay)
	{
		if( size.cx<bits.bmWidth )
			size.cx +=2;
		else
			size.cx = 0;
		dcClient.BitBlt( 0,0,size.cx,bits.bmHeight,&dcMem,(bits.bmWidth-size.cx),0,SRCCOPY);
		dcClient.BitBlt( size.cx,0,(bits.bmWidth-size.cx),bits.bmHeight,&dcMem,0,0,SRCCOPY);

		Sleep( 50 );
		pWnd->Invalidate();
	}
//	SetEvent( g_hEnd );

	return 1;
}
/////////////////////////////////////////////////////////////////////////////
// CDynLine

CDynLine::CDynLine()
{
	m_bmp.LoadBitmap( IDB_WAITING_BMP );

}

CDynLine::~CDynLine()
{
	if( g_lDisplay )
		Stop();
}


BEGIN_MESSAGE_MAP(CDynLine, CStatic)
	//{{AFX_MSG_MAP(CDynLine)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynLine message handlers

int CDynLine::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	Start();
	return 0;
}

void CDynLine::Start()
{
	InterlockedIncrement(&g_lDisplay);
	AfxBeginThread(DispThread,this);
//	g_hEnd = CreateEvent( NULL,TRUE,FALSE,NULL); 	
}

void CDynLine::Stop()
{
	InterlockedDecrement(&g_lDisplay);
//	WaitForSingleObject( g_hEnd,INFINITE);
}
