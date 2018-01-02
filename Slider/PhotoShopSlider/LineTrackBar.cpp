/********************************************************************

	LineTrackBar.cpp - ISee图像浏览器—图像处理模块类LineTrackBar
	实现代码文件

    版权所有(C) VCHelp-coPathway-ISee workgroup 2000 all member's

    这一程序是自由软件，你可以遵照自由软件基金会出版的GNU 通用许可证
	条款来修改和重新发布这一程序。或者用许可证的第二版，或者（根据你
	的选择）用任何更新的版本。

    发布这一程序的目的是希望它有用，但没有任何担保。甚至没有适合特定
	目地的隐含的担保。更详细的情况请参阅GNU通用许可证。

    你应该已经和程序一起收到一份GNU通用许可证(GPL)的副本。如果还没有，
	写信给：
    The Free Software Foundation, Inc.,  675  Mass Ave,  Cambridge,
    MA02139,  USA

	如果你在使用本软件时有什么问题或建议，用以下地址可以与我们取得联
	系：
		http://isee.126.com
		http://www.vchelp.net
	或：
		iseesoft@china.com

	作者：马翔
   e-mail:hugesoft@yeah.net

   功能实现：PhotoShop风格的滑动条

	文件版本：
		Build xxxxx
		Date  2000-11-18

********************************************************************/
// LineTrackBar.cpp : implementation file
//

#include "stdafx.h"
#include "LineTrackBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineTrackBar

CLineTrackBar::CLineTrackBar()
{
	CLineTrackBar::RegisterWndClass(AfxGetInstanceHandle());
	pItem = NULL;
}

CLineTrackBar::~CLineTrackBar()
{
	int nCount = m_items.GetSize();
	
	for (int i = 0; i < nCount; i++)
		delete m_items.GetAt(i);
	m_items.RemoveAll();

}


BEGIN_MESSAGE_MAP(CLineTrackBar, CWnd)
	//{{AFX_MSG_MAP(CLineTrackBar)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLineTrackBar message handlers
//	初始化控件函数
//	nGroupCtrl：协作控件ID,默认为-1
//	ncolor：控件颜色,默认为RGB(0,0,0)[黑色]
//	nLower：控件最小值（大于等于0）,默认为0
//	nZero：控件原点（大于等于nLower）,默认为100
//	nUpper：控件最大值（大于等于nZero）,默认为200
//	nStep：控件步长,默认为1
//	bFocus：设置协作控件焦点，默认为FALSE（不设置），为TRUE时
//			点中LineTrackBar时协作控件将得到焦点
//	nStype：控件返值类型，目前未使用
//
//	此控件在设置nLower,nZero,nUpper,nStep参数后会自动适应大小

BOOL CLineTrackBar::InitControl(int nGroupCtrl,COLORREF ncolor,
								int nLower, int nZero,int nUpper,
								int nStep,BOOL bFocus,int nStype)
{	
	CLineTrackObj* pItem = new CLineTrackObj;
	pItem->m_color = ncolor;
	pItem->m_nLower = nLower;
	pItem->m_nUpper = nUpper;
	pItem->m_nZero =nZero;
	pItem->m_nPos = nZero;
	pItem->m_nStep =nStep;
	pItem->m_nStype=nStype;
	pItem->m_bFocus =bFocus;

	if(pItem->m_nStep<=0)
		pItem->m_nStep=1;

	VERIFY(pItem->m_nLower>=0);
	VERIFY(pItem->m_nZero>=pItem->m_nLower);
	VERIFY(pItem->m_nUpper>=pItem->m_nZero);
	VERIFY(pItem->m_nStep<pItem->m_nUpper);

	try 
	{
		m_items.Add(pItem);
		this->SetWindowPos(this,pItem->m_nLower,0,(pItem->m_nUpper-pItem->m_nLower)*pItem->m_nStep+11,15,SWP_NOMOVE|SWP_NOZORDER|
			SWP_SHOWWINDOW|SWP_NOACTIVATE);
		InvalidateCtrl();
		SetGroupControl (nGroupCtrl);	

		switch(pItem->m_nStype )
		{
		case RE_STRING:
			SetGroupControlText();
			break;
		}

		return TRUE;
	}
	catch (CMemoryException* e)
	{
		if (pItem !=NULL) 
			delete pItem;
		e->Delete();
		return FALSE;
	}
}

void CLineTrackBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rcClient;
	GetClientRect(rcClient);

	// draw scale
	if (m_MemDC.GetSafeHdc() != NULL)
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_MemDC, 0, 0, SRCCOPY);

	// Do not call CWnd::OnPaint() for painting messages
}

void CLineTrackBar::InvalidateCtrl()
{
	CClientDC dc(this);
	CRect rcClient;
	int nRang;

	pItem = m_items.GetAt(0);
	nRang=pItem->m_nUpper*pItem->m_nStep-pItem->m_nLower*pItem->m_nStep;

	GetClientRect(rcClient);

	if (m_MemDC.GetSafeHdc() == NULL)
	{
		m_MemDC.CreateCompatibleDC(&dc);
		m_Bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
		m_MemDC.SelectObject(m_Bitmap);
		
		// draw scale
		m_MemDC.SetBkColor(RGB(255,255,255));
//		m_MemDC.SetBkMode (TRANSPARENT);
		CBrush bkBrush;
		bkBrush.CreateSysColorBrush(COLOR_ACTIVEBORDER);
		m_MemDC.FillRect(rcClient,&bkBrush);

		CPen pen(PS_SOLID, 1, pItem->m_color);
		CPen* pOldPen = m_MemDC.SelectObject(&pen);
		
		m_MemDC.MoveTo(CPoint(rcClient.left+5, rcClient.top+5));
		m_MemDC.LineTo(CPoint(rcClient.left+5+nRang+1, rcClient.top+5));
		m_MemDC.MoveTo(CPoint(rcClient.left+5, rcClient.top));
		m_MemDC.LineTo(CPoint(rcClient.left+5, rcClient.top+5));
		m_MemDC.MoveTo(CPoint(rcClient.left+5+pItem->m_nZero*pItem->m_nStep, rcClient.top));
		m_MemDC.LineTo(CPoint(rcClient.left+5+pItem->m_nZero*pItem->m_nStep, rcClient.top+5));
		m_MemDC.MoveTo(CPoint(rcClient.left+5+nRang, rcClient.top ));
		m_MemDC.LineTo(CPoint(rcClient.left+5+nRang, rcClient.top+5));

		CPoint ptPolyAr[4];
		ptPolyAr[0].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[0].y=rcClient.top+6 ;
		ptPolyAr[1].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep-5-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[1].y=rcClient.top+11;
		ptPolyAr[2].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep+5-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[2].y=rcClient.top+11;
		ptPolyAr[3].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[3].y=rcClient.top+6 ;
		m_MemDC.Polyline (ptPolyAr,4);
		m_MemDC.SelectObject(pOldPen);
	}
	InvalidateRect(rcClient, FALSE);		
}

void CLineTrackBar::DrawSpike()
{
	CRect rcClient;
	GetClientRect(rcClient);
	UINT nRang;
				
	nRang=pItem->m_nUpper*pItem->m_nStep-pItem->m_nLower*pItem->m_nStep;

	if (m_MemDC.GetSafeHdc() != NULL)
	{
		m_MemDC.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_MemDC, 4, 0, SRCCOPY);


		m_MemDC.SetBkColor(RGB(255,255,255));
//		m_MemDC.SetBkMode (TRANSPARENT);
		CBrush bkBrush;
		bkBrush.CreateSysColorBrush(COLOR_ACTIVEBORDER);
		m_MemDC.FillRect(rcClient,&bkBrush);

		CPen pen(PS_SOLID, 1, pItem->m_color);
		CPen* pOldPen = m_MemDC.SelectObject(&pen);
		
		m_MemDC.MoveTo(CPoint(rcClient.left+5, rcClient.top+5));
		m_MemDC.LineTo(CPoint(rcClient.left+5+nRang+1, rcClient.top+5));
		m_MemDC.MoveTo(CPoint(rcClient.left+5, rcClient.top));
		m_MemDC.LineTo(CPoint(rcClient.left+5, rcClient.top+5));
		m_MemDC.MoveTo(CPoint(rcClient.left+5+pItem->m_nZero*pItem->m_nStep, rcClient.top));
		m_MemDC.LineTo(CPoint(rcClient.left+5+pItem->m_nZero*pItem->m_nStep, rcClient.top+5));
		m_MemDC.MoveTo(CPoint(rcClient.left+5+nRang, rcClient.top ));
		m_MemDC.LineTo(CPoint(rcClient.left+5+nRang, rcClient.top+5));

		CPoint ptPolyAr[4];
		ptPolyAr[0].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[0].y=rcClient.top+6 ;
		ptPolyAr[1].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep-5-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[1].y=rcClient.top+11;
		ptPolyAr[2].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep+5-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[2].y=rcClient.top+11;
		ptPolyAr[3].x=rcClient.left+5+pItem->m_nPos*pItem->m_nStep-pItem->m_nLower*pItem->m_nStep;
		ptPolyAr[3].y=rcClient.top+6 ;
//		if(m_bMouseHit==TRUE)
//		{
//			m_MemDC.Polygon (ptPolyAr,3);
//		}
		m_MemDC.Polyline (ptPolyAr,4);

		m_MemDC.SelectObject(pOldPen);
	}
}

void CLineTrackBar::SetPos(int nPos)
{
	pItem->m_nPos=nPos;
	if(pItem->m_nPos <pItem->m_nLower )
		pItem->m_nPos =pItem->m_nLower;
	else if(pItem->m_nPos >pItem->m_nUpper)
		pItem->m_nPos =pItem->m_nUpper;
	DrawSpike();
	Invalidate(FALSE);
}

int CLineTrackBar::GetPos()
{
	return pItem->m_nPos;
}

BOOL CLineTrackBar::RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.lpszClassName = "LINE_TRACKBAR_CTRL"; // matches class name in client
	wc.hInstance = hInstance;
	wc.lpfnWndProc = ::DefWindowProc;
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.lpszMenuName = NULL;
	wc.hbrBackground = (HBRUSH) ::GetStockObject(LTGRAY_BRUSH);
	wc.style = CS_GLOBALCLASS; // To be modified
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	return (::RegisterClass(&wc) != 0);
}

void CLineTrackBar::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

void CLineTrackBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcClient;
	GetClientRect(rcClient);
	pItem->m_nPos =(point.x-rcClient.left-5)/pItem->m_nStep+pItem->m_nLower;
	if(pItem->m_nPos <pItem->m_nLower)
		pItem->m_nPos =pItem->m_nLower;
	else if(pItem->m_nPos >pItem->m_nUpper )
		pItem->m_nPos =pItem->m_nUpper;
	
	DrawSpike();
	Invalidate(FALSE);
	switch(pItem->m_nStype )
	{
	case RE_STRING:
		SetGroupControlText();
		break;
	}
	if(pItem->pCtrl!=NULL && pItem->m_bFocus ==TRUE)
	{
		pItem->pCtrl->SetFocus ();
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CLineTrackBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcClient;
	if(nFlags==MK_LBUTTON)
	{
		GetClientRect(rcClient);
		pItem->m_nPos =(point.x-rcClient.left-5)/pItem->m_nStep+pItem->m_nLower;

		if(pItem->m_nPos <pItem->m_nLower )
		{
			pItem->m_nPos =pItem->m_nLower;
		}
		else if(pItem->m_nPos >pItem->m_nUpper)
		{
			pItem->m_nPos =pItem->m_nUpper;
		}	

		DrawSpike();
		Invalidate(FALSE);
		switch(pItem->m_nStype )
		{
		case RE_STRING:
			SetGroupControlText();
			break;
		}

	}

	CWnd::OnMouseMove(nFlags, point);
}

void CLineTrackBar::SetGroupControl(int nCtrl)
{
	if(nCtrl!=-1)
		pItem->pCtrl = GetParent()->GetDlgItem(nCtrl);
	else
		pItem->pCtrl =NULL;
}

void CLineTrackBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}

void CLineTrackBar::SetGroupControlText()
{
	if(pItem->pCtrl !=NULL)
	{
		char szText[255];
		wsprintf(szText,"%d",pItem->m_nPos );
		pItem->pCtrl->SetWindowText(szText);
	}
}
