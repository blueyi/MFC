#include "CustomSlider.h"

// CCustomSlider

IMPLEMENT_DYNAMIC(CCustomSlider, CWnd)

BEGIN_MESSAGE_MAP(CCustomSlider, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
CCustomSlider::CCustomSlider()
{
	m_dwRangeMin=0;
	m_dwRangeMax=100;
	m_dwPos=50;
	m_hBmpThumbActive=m_hBmpThumbInactive=m_hBmpChannel=NULL;
	m_bActive=false;
	m_bIsHorz=true;
	m_bIsReverse=false;
	m_bInitialized=false;
	m_crBkg=GetSysColor(COLOR_WINDOW);
	RegisterWindowClass();
}

//////////////////////////////////////////////////////////////////////////
CCustomSlider::~CCustomSlider()
{
	//free resources
	if(m_hBmpChannel != NULL)
	{
		DeleteObject(m_hBmpChannel);
	}
	if(m_hBmpThumbActive != NULL)
	{
		DeleteObject(m_hBmpThumbActive);
	}
	if(m_hBmpThumbInactive != NULL)
	{
		DeleteObject(m_hBmpThumbInactive);
	}

	m_DrawDC.SelectObject(m_hOldDCBmp);
	DeleteObject(m_hOldDCBmp);
}

//////////////////////////////////////////////////////////////////////////
bool CCustomSlider::RegisterWindowClass()
{
WNDCLASS wndcls;
HINSTANCE hInst;

	hInst = AfxGetInstanceHandle();

	if(!(::GetClassInfo(hInst, _T("CustomSliderClass"), &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = NULL;
		wndcls.hbrBackground    = (HBRUSH)::GetStockObject(NULL_BRUSH);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = _T("CustomSliderClass");

		if(FALSE == AfxRegisterClass(&wndcls))
		{
#ifdef _DEBUG
			OutputDebugString(_T("Failed to register class for CustomSlider"));
#endif
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::SetBitmaps(HBITMAP hBmpChannel, HBITMAP hBmpThumbInactive, HBITMAP hBmpThumbActive /* = NULL */)
{
BITMAP bmpData;

	//old present and new specified
	if(m_hBmpChannel != NULL && hBmpChannel != NULL)
	{
		//dump old
		DeleteObject(m_hBmpChannel);
		m_hBmpChannel=NULL;
		m_dwChH=m_dwChW=0;
	}

	if(hBmpChannel != NULL)
	{
		m_hBmpChannel=hBmpChannel;
		//get dimensions
		if(::GetObject(hBmpChannel, sizeof(bmpData), &bmpData) != 0)
		{
			m_dwChW=(DWORD)bmpData.bmWidth;
			m_dwChH=(DWORD)bmpData.bmHeight;
		}		
	}

	//old present and new specified
	if(m_hBmpThumbInactive != NULL && hBmpThumbInactive != NULL)
	{
		//dump old
		DeleteObject(m_hBmpThumbInactive);
		m_hBmpThumbInactive=NULL;
		m_dwTH=m_dwTW=0;
	}

	if(hBmpThumbInactive != NULL)
	{
		m_hBmpThumbInactive=hBmpThumbInactive;
		//get dimensions
		if(::GetObject(hBmpThumbInactive, sizeof(bmpData), &bmpData) != 0)
		{
			m_dwTW=(DWORD)bmpData.bmWidth;
			m_dwTH=(DWORD)bmpData.bmHeight;
		}		
	}


	//old present and new specified
	if(m_hBmpThumbActive != NULL && hBmpThumbActive != NULL)
	{
		//dump old
		DeleteObject(m_hBmpThumbActive);
		m_hBmpThumbActive=NULL;
	}

	//if specified, use other bitmap for active state
	if(hBmpThumbActive != NULL)
	{
		m_hBmpThumbActive=hBmpThumbActive;
	}
	else
	{
		//otherwise use inactive bitmap for active state	
		m_hBmpThumbActive=m_hBmpThumbInactive;
	}

}

//////////////////////////////////////////////////////////////////////////
// CCustomSlider message handlers
BOOL CCustomSlider::OnEraseBkgnd(CDC* pDC)
{
CRect rect;
CBrush brBkg;

	GetClientRect(rect);

	brBkg.CreateSolidBrush(m_crBkg);
	HGDIOBJ hOldBrush = m_DrawDC.SelectObject(&brBkg);
	m_DrawDC.SetBrushOrg(0, 0);
	m_DrawDC.PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	m_DrawDC.SelectObject(hOldBrush);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::DisplayTransparentBMP(CDC *pDestDC, HBITMAP hBmp, DWORD dwW, DWORD dwH, int nX, int nY)
{
CDC dcMem;
HBITMAP hBmpOld;

	if(TRUE == dcMem.CreateCompatibleDC(pDestDC))
	{
		hBmpOld=(HBITMAP)dcMem.SelectObject(hBmp);
		if(hBmpOld != NULL)
		{
			::TransparentBlt(pDestDC->GetSafeHdc(), nX, nY, dwW, dwH, dcMem.GetSafeHdc(), 0, 0, dwW, dwH, (UINT)RGB(0, 0, 0) );
			dcMem.SelectObject(hBmpOld);
		}
	}//compatible DC ok
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::OnPaint()
{
PAINTSTRUCT ps;
CDC *pDC;
HBITMAP hCurrentThumb;
CRect rc;
DWORD dwIX, dwIY;
LONG lStyle;

	GetClientRect(&rc);

	//one-time initialization performed here instead of OnCreate
	if(m_bInitialized == false)
	{
		m_bInitialized=true;
		//check if horizontal
		lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);
		if(lStyle & TBS_VERT)
		{
			m_bIsHorz=false;
		}
		else
		{
			m_bIsHorz=true;
		}
		//at this stage we do have a HWND and a DC
		CDC *pDC;

		pDC=GetDC();
		if(pDC != NULL)
		{
			GetClientRect(&rc);
			m_DrawDC.CreateCompatibleDC(pDC);
			m_DrawBitmap.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
			m_hOldDCBmp=m_DrawDC.SelectObject(m_DrawBitmap.GetSafeHandle());
			ReleaseDC(pDC);
		}
	}

	pDC=BeginPaint(&ps);

	if(m_hBmpChannel != NULL)
	{
		//display channel
		//all drawing goes to mem DC for flicker-free drawing
		DisplayTransparentBMP(&m_DrawDC, (HBITMAP)m_hBmpChannel, m_dwChW, m_dwChH, 0, 0);

		//display thumb
		if(m_bActive == true)
		{
			hCurrentThumb=(HBITMAP)m_hBmpThumbActive;
			//no active bitmap set, use inactive
			if(hCurrentThumb == NULL)
			{
				hCurrentThumb=(HBITMAP)m_hBmpThumbInactive;
			}
		}
		else
		{
			hCurrentThumb=(HBITMAP)m_hBmpThumbInactive;
		}

		if(hCurrentThumb != NULL)
		{
			//calculate thumb x,y coordinates
			if(m_bIsHorz == true)
			{
				dwIX=PosToX(m_dwPos)-m_dwTW/2;
				dwIY = (rc.Height()-m_dwTH)/2;
			}
			else
			{
				dwIX=(rc.Width()-m_dwTW)/2;
				dwIY=PosToY(m_dwPos)-m_dwTH/2;
			}

			//display thumb
			//all drawing goes to mem DC for flicker-free drawing
			DisplayTransparentBMP(&m_DrawDC, hCurrentThumb, m_dwTW, m_dwTH, dwIX, dwIY);
		}
	}

	//finally blit mem DC to screen
	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &m_DrawDC, 0, 0, SRCCOPY);
	EndPaint(&ps);
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
DWORD dwNewPos;
CWnd *pParent;

	m_bActive=true;
	SetCapture();
	if(m_bIsHorz == true)
	{
		dwNewPos=XToPos(point.x);
	}
	else
	{
		dwNewPos=YToPos(point.y);
	}

	m_dwPos=dwNewPos;

	pParent=GetParent();
	if(pParent != NULL)
	{
		if(m_bIsHorz == true)
		{
			pParent->SendMessage(WM_HSCROLL, MAKEWPARAM(TB_THUMBPOSITION, m_dwPos), (LPARAM)GetSafeHwnd());
		}
		else
		{
			pParent->SendMessage(WM_VSCROLL, MAKEWPARAM(TB_THUMBPOSITION, m_dwPos), (LPARAM)GetSafeHwnd());
		}
	}
	Invalidate();
	Default();
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::OnLButtonUp(UINT nFlags, CPoint point)
{
CWnd *pParent;

	m_bActive=false;
	ReleaseCapture();
	Invalidate();

	pParent=GetParent();
	if(pParent != NULL)
	{
		if(m_bIsHorz == true)
		{
			pParent->SendMessage(WM_HSCROLL, MAKEWPARAM(TB_THUMBPOSITION, m_dwPos), (LPARAM)GetSafeHwnd());
		}
		else
		{
			pParent->SendMessage(WM_VSCROLL, MAKEWPARAM(TB_THUMBPOSITION, m_dwPos), (LPARAM)GetSafeHwnd());
		}
	}
	Default();
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::OnMouseMove(UINT nFlags, CPoint point)
{
CRect rc;
DWORD dwNewPos;
CWnd *pParent;

	if(m_bActive == true)
	{
		GetClientRect(&rc);
		if(rc.PtInRect(point))
		{
			if(m_bIsHorz == true)
			{
				dwNewPos=XToPos(point.x);
			}
			else
			{
				dwNewPos=YToPos(point.y);
			}
			m_dwPos=dwNewPos;

			//if pos updated, notify parent
			pParent=GetParent();
			if(pParent != NULL)
			{
				if(m_bIsHorz == true)
				{
					pParent->SendMessage(WM_HSCROLL, MAKEWPARAM(TB_THUMBTRACK, m_dwPos), (LPARAM)GetSafeHwnd());
				}
				else
				{
					pParent->SendMessage(WM_VSCROLL, MAKEWPARAM(TB_THUMBTRACK, m_dwPos), (LPARAM)GetSafeHwnd());
				}
			}
		}
		else
		{
			m_bActive=false;
			ReleaseCapture();
			//finished dragging, send POS msg
			pParent=GetParent();
			if(pParent != NULL)
			{
				if(m_bIsHorz == true)
				{
					pParent->SendMessage(WM_HSCROLL, MAKEWPARAM(TB_THUMBPOSITION, m_dwPos), (LPARAM)GetSafeHwnd());
				}
				else
				{
					pParent->SendMessage(WM_VSCROLL, MAKEWPARAM(TB_THUMBPOSITION, m_dwPos), (LPARAM)GetSafeHwnd());
				}
			}
		}
		Invalidate();
	}
	Default();
}

//////////////////////////////////////////////////////////////////////////
inline DWORD CCustomSlider::PosToX(DWORD dwPos)
{
CRect rc;
DWORD dwX;

	GetClientRect(&rc);

	if(m_bIsReverse)
	{
		//left: RangeMax, right: RangeMin
		dwX = (rc.Width() - m_dwTW/2) - ( (rc.Width() - m_dwTW) * (m_dwPos - m_dwRangeMin) ) / (m_dwRangeMax - m_dwRangeMin);
	}
	else
	{
		//left: RangeMin, right: RangeMax
		dwX = (m_dwTW/2) + ( (rc.Width() - m_dwTW) * (m_dwPos - m_dwRangeMin) ) / (m_dwRangeMax - m_dwRangeMin);
	}

	return dwX;
}

//////////////////////////////////////////////////////////////////////////
inline DWORD CCustomSlider::PosToY(DWORD dwPos)
{
CRect rc;
DWORD dwY;

	GetClientRect(&rc);

	if(m_bIsReverse)
	{
		//bottom: RangeMax, top: RangeMin
		dwY = (m_dwTH/2) + ( (rc.Height() - m_dwTH) * (m_dwPos - m_dwRangeMin) ) / (m_dwRangeMax - m_dwRangeMin);
	}
	else
	{
		//bottom: RangeMin, top: RangeMax
		dwY = (rc.Height() - m_dwTH/2) - ( (rc.Height() - m_dwTH) * (m_dwPos - m_dwRangeMin) ) / (m_dwRangeMax - m_dwRangeMin);
	}

	return dwY;
}

//////////////////////////////////////////////////////////////////////////
inline DWORD CCustomSlider::XToPos(DWORD dwX)
{
DWORD dwPos;
CRect rc;

	GetClientRect(&rc);

	if(dwX < m_dwTW/2)
	{
		if(m_bIsReverse)
		{
			dwPos = m_dwRangeMax;
		}
		else
		{
			dwPos = m_dwRangeMin;
		}
	}
	else
	if(dwX > rc.Width() - m_dwTW/2)
	{
		if(m_bIsReverse)
		{
			dwPos = m_dwRangeMin;
		}
		else
		{
			dwPos = m_dwRangeMax;
		}
	}
	else
	{
		if(m_bIsReverse)
		{
			//left: RangeMax, right: RangeMin
			dwPos = m_dwRangeMax - ( (m_dwRangeMax - m_dwRangeMin) * (dwX - m_dwTW/2) ) / (rc.Width() - m_dwTW ); 
		}
		else
		{
			//left: RangeMin, right: RangeMax
			dwPos = m_dwRangeMin + ( (m_dwRangeMax - m_dwRangeMin) * (dwX - m_dwTW/2) ) / (rc.Width() - m_dwTW ); 
		}
	}

	//final range checks
	if(dwPos < m_dwRangeMin)
	{
		dwPos = m_dwRangeMin;
	}
	else
	if(dwPos > m_dwRangeMax)
	{
		dwPos = m_dwRangeMax;
	}

	return dwPos;
}

//////////////////////////////////////////////////////////////////////////
inline DWORD CCustomSlider::YToPos(DWORD dwY)
{
DWORD dwPos;
CRect rc;

	GetClientRect(&rc);

	if(dwY < m_dwTH/2)
	{
		if(m_bIsReverse)
		{
			dwPos = m_dwRangeMin;
		}
		else
		{
			dwPos = m_dwRangeMax;
		}
	}
	else
	if(dwY > rc.Height() - m_dwTH/2)
	{
		if(m_bIsReverse)
		{
			dwPos = m_dwRangeMax;
		}
		else
		{
			dwPos = m_dwRangeMin;
		}
	}
	else
	{
		if(m_bIsReverse)
		{
			//top: RangeMin, bottom: RangeMax
			dwPos = m_dwRangeMin + ( (m_dwRangeMax - m_dwRangeMin) * (dwY - m_dwTH/2) ) / (rc.Height() - m_dwTH ); 
		}
		else
		{
			//top: RangeMax, bottom: RangeMin
			dwPos = m_dwRangeMax - ( (m_dwRangeMax - m_dwRangeMin) * (dwY - m_dwTH/2) ) / (rc.Height() - m_dwTH ); 
		}
	}

	//final range checks
	if(dwPos < m_dwRangeMin)
	{
		dwPos = m_dwRangeMin;
	}
	else
	if(dwPos > m_dwRangeMax)
	{
		dwPos = m_dwRangeMax;
	}
	return dwPos;
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::GetRange(DWORD& dwMin, DWORD& dwMax)
{
	dwMin=m_dwRangeMin;
	dwMax=m_dwRangeMax;
}

//////////////////////////////////////////////////////////////////////////
DWORD CCustomSlider::GetRangeMin()
{
	return m_dwRangeMin;
}

//////////////////////////////////////////////////////////////////////////
DWORD CCustomSlider::GetRangeMax()
{
	return m_dwRangeMax;
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::SetPos(DWORD dwPos)
{
	//update position with bounds checking
	if(dwPos > m_dwRangeMax)
	{
		m_dwPos=m_dwRangeMax;
	}
	else
	if(dwPos < m_dwRangeMin)
	{
		m_dwPos=m_dwRangeMin;
	}
	else
	{
		m_dwPos=dwPos;
	}
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
DWORD CCustomSlider::GetPos()
{
	return m_dwPos;
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::SetRange(DWORD dwMin, DWORD dwMax)
{
	m_dwRangeMin=dwMin;
	m_dwRangeMax=dwMax;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::SetRangeMin(DWORD dwMin)
{
	m_dwRangeMin=dwMin;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::SetRangeMax(DWORD dwMax)
{
	m_dwRangeMax=dwMax;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::SetReverse(bool bRev)
{
	m_bIsReverse=bRev;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
bool CCustomSlider::GetReverse()
{
	return m_bIsReverse;
}

//////////////////////////////////////////////////////////////////////////
void CCustomSlider::SetBkgColor(COLORREF crBkg)
{
	m_crBkg=crBkg;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
COLORREF CCustomSlider::GetBkgColor()
{
	return m_crBkg;
}