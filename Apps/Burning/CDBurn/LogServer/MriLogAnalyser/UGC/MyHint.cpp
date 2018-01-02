#include "stdafx.h"
#include "MyHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/********************************************
*********************************************/
CMyHint::CMyHint()
{
	//alloc memory
}

/********************************************
*********************************************/
CMyHint::~CMyHint()
{
	//perform clean-up
}


/********************************************
*********************************************/
BEGIN_MESSAGE_MAP(CMyHint, CWnd)
	//{{AFX_MSG_MAP(CMyHint)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************
*********************************************/
void CMyHint::OnPaint() 
{
//	if ( m_nX == m_nPrevX && m_nY == m_nPrevY )
//		return;

	CDC* dc =GetDC();
/*
	if(m_hFont != NULL)
		dc->SelectObject(m_hFont);
*/	
	//////////// Added by XZHL	
	CFont font;
	VERIFY( font.CreateFont(
		15,								// nHeight
		0,								// nWidth, 0
		0,								// nEscapement
		0,								// nOrientation
		FW_THIN,						// FW_HEAVY,FW_BOLD,FW_NORMAL,nWeight
		FALSE,							// bItalic
		FALSE,							// bUnderline
		0,								// cStrikeOut
		ANSI_CHARSET,					// nCharSet
		OUT_DEFAULT_PRECIS,				// nOutPrecision
		CLIP_DEFAULT_PRECIS,			// nClipPrecision
		PROOF_QUALITY,					// DEFAULT_QUALITY,nQuality
		DEFAULT_PITCH | FF_SWISS,		// nPitchAndFamily
		"Arial") );						// lpszFacename, Arial, Arial Bold, ¿¬Ìå_GB2312
	m_hFont = &font;
	if(m_hFont != NULL)
		dc->SelectObject(m_hFont);
////////////	
	RECT rect;
	GetClientRect(&rect);

	dc->SetTextColor(m_textColor);
	dc->SetBkColor(m_backColor);


	dc->SetBkMode(OPAQUE);
	dc->DrawText( m_text, &rect, DT_LEFT );//DT_CENTER|DT_VCENTER);//|DT_SINGLELINE);

	ReleaseDC(dc);
	ValidateRect(NULL);
}

BOOL CMyHint::Create(CWnd* pParentWnd, HBRUSH hbrBackground)
{
	ASSERT_VALID(pParentWnd);
    ASSERT(::IsWindow(pParentWnd->GetSafeHwnd()));

	m_ctrl = (CMap1*) pParentWnd;

///	m_pParentWnd=pParentWnd;

	// creation of window
    // 
	if(hbrBackground==NULL)
	{
		hbrBackground=(HBRUSH) (COLOR_INFOBK+1);
	}

	WNDCLASS wndClass;
	wndClass.style=CS_SAVEBITS|CS_DBLCLKS; 
    wndClass.lpfnWndProc=AfxWndProc; 
    wndClass.cbClsExtra=0; 
    wndClass.cbWndExtra=0; 
    wndClass.hInstance=AfxGetInstanceHandle(); 
    wndClass.hIcon=::LoadCursor(NULL,IDC_ARROW); 
    wndClass.hCursor=0; 
    wndClass.hbrBackground=hbrBackground; 
    wndClass.lpszMenuName=NULL; 
	wndClass.lpszClassName=_T("HintWnd");
	
	if(!AfxRegisterClass(&wndClass))
	{
		return FALSE;
	}

	CRect rect(0,0,0,0);
    if(!CWnd::CreateEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST, wndClass.lpszClassName, _T(""), 
		WS_BORDER|WS_POPUP, rect, NULL, 0, NULL))
	{
        return FALSE;
	}

	//init the variables
	m_text=_T("");					//display text
	m_textColor = RGB(0,0,0);		//text color
	m_backColor = RGB(255,255,224);	//background color
	m_windowAlign	= UG_ALIGNLEFT;	//UG_ALIGNLEFT,UG_ALIGNRIGHT,UG_ALIGNCENTER
									//UG_ALIGNTOP,UG_ALIGNBOTTOM,UG_ALIGNVCENTER
	m_textAlign		= UG_ALIGNLEFT;	//UG_ALIGNLEFT,UG_ALIGNRIGHT,UG_ALIGNCENTER
	m_hFont	= NULL;					//font handle
	
	//get the font height
	CDC * dc =GetDC();
	CSize s = dc->GetTextExtent(_T("X"),1);
	m_fontHeight = s.cy;
	m_nFixedFontHeight = s.cy;
	ReleaseDC(dc);

    return TRUE;
}


/********************************************
*********************************************/
int CMyHint::SetFont(CFont * font){

	m_hFont	= font;
	
	//get the font height
	CDC * dc =GetDC();
	if(m_hFont != NULL)
		dc->SelectObject(m_hFont);
	CSize s = dc->GetTextExtent(_T("Xy"),2);
	m_fontHeight = s.cy + 3;
	ReleaseDC(dc);
	return UG_SUCCESS;
}
/********************************************
align = UG_ALIGNLEFT or UG_ALIGNRIGHT or UG_ALIGNCENTER
		+ UG_ALIGNTOP or UG_ALIGNBOTTOM or UG_ALIGNVCENTER
*********************************************/
int	CMyHint::SetWindowAlign(int align){
	m_windowAlign = align;
	return UG_SUCCESS;
}
/********************************************
align = UG_ALIGNLEFT or UG_ALIGNRIGHT or UG_ALIGNCENTER
*********************************************/
int CMyHint::SetTextAlign(int align){
	m_textAlign = align;
	return UG_SUCCESS;
}
/********************************************
*********************************************/
int CMyHint::SetTextColor(COLORREF color){
	m_textColor	= color;
	return UG_SUCCESS;
}
/********************************************
*********************************************/
int CMyHint::SetBackColor(COLORREF color){
	m_backColor	= color;
	return UG_SUCCESS;
}
/********************************************
*********************************************/
int CMyHint::SetText(LPCTSTR string,int update){
	m_text = string;
	if(update)
		Invalidate();
	return UG_SUCCESS;
}
/********************************************
*********************************************/
int CMyHint::MoveHintWindow(int x,int y,int width)
{
	m_nPrevX = m_nX = x;
	m_nPrevY = m_nY = y;

	RECT rect;

	//get the width of the string and reset the
	//specified width if needed
	CDC * dc =GetDC();
	// TD first select font...
	if(m_hFont != NULL)
		dc->SelectObject(m_hFont);
/*	CSize s = dc->GetTextExtent(m_text,m_text.GetLength());
	if((s.cx+4) > width)
		width = s.cx+4;
*/	
	// Added by XZHL
	CString sTmpStr = GetMaxLenString( m_text );
	CSize s = dc->GetTextExtent( sTmpStr, sTmpStr.GetLength() );
	if((s.cx+4) > width)
		width = s.cx+4;
	
	ReleaseDC(dc);
	
	//set up the horizontal pos
	if(m_windowAlign&UG_ALIGNCENTER){		//center
		rect.left = x-(width/2);
		rect.right = x+width;
	}
	else if(m_windowAlign&UG_ALIGNRIGHT){	//right
		rect.left = x-width;
		rect.right = x;
	}
	else{									//left
		rect.left = x;
		rect.right = x+width;
	}

	//set up the vertical pos
	int nYOffset = 0;
	if(m_windowAlign&UG_ALIGNVCENTER){		//center
		rect.top	= y-(m_fontHeight/2) - nYOffset;
		rect.bottom = rect.top+m_fontHeight - nYOffset;
	}
	else if(m_windowAlign&UG_ALIGNBOTTOM){  //bottom
		rect.top	= y-m_fontHeight - nYOffset;
		rect.bottom = y - nYOffset;
	}
	else{									//top
		rect.top = y + nYOffset;
		rect.bottom = y+m_fontHeight + nYOffset;
	}

	//make sure the position is within the parent
	RECT parentRect;
	int dif;
	m_ctrl->GetClientRect(&parentRect);


	if(rect.left < 0){
		dif = 0 - rect.left;
		rect.left+=dif;
		rect.right +=dif;
	}
	if(rect.top <0){
		dif = 0 - rect.top;
		rect.top +=dif;
		rect.bottom +=dif;
	}
	if(rect.right > parentRect.right){
		dif = rect.right - parentRect.right;
		rect.right -=dif;
		rect.left -=dif;
	}
	if(rect.bottom > parentRect.bottom){
		dif = rect.bottom - parentRect.bottom;
		rect.top -= dif;
		rect.bottom -= dif;
	}


	m_ctrl->ClientToScreen(&rect);

	Hide();
	MoveWindow(&rect,TRUE);
	Show();

	SendMessage(WM_PAINT,0,0);

	return UG_SUCCESS;
}
/********************************************
*********************************************/
int CMyHint::Hide(){
	ShowWindow(SW_HIDE);
	return UG_SUCCESS;
}
/********************************************
*********************************************/
int CMyHint::Show(){
	if(IsWindowVisible() == FALSE)
		ShowWindow(SW_SHOWNA);			
//	SetFocus();
	return UG_SUCCESS;
}

// Added by XZHL
void CMyHint::SetLineNum(int nNum)
{
	m_fontHeight = m_nFixedFontHeight * nNum;	
}

// Added by XZHL
CString CMyHint::GetMaxLenString(LPCTSTR string)
{
	CString ss = string, ss1 = "", ss2 = "";
	int nPos0 = 0, nPos = 0;
	int nWidth0 = 0, nWidth = 0;

	for(int i=0 ;; i++)
	{
		if ( i==0 )
			nPos = ss.Find( "\n", 0 );
		else
			nPos = ss.Find( "\n", nPos + 2 );

		if ( nPos == -1 )
		{
			nWidth = ss.Mid( nPos0, ss.GetLength() - nPos0 ).GetLength();
			ss1 = ss.Mid( nPos0, ss.GetLength() - nPos0 );
		}
		else if ( nPos >= 0 )
		{
			nWidth = ss.Mid( nPos0, nPos - nPos0 ).GetLength();
			ss1 = ss.Mid( nPos0, nPos - nPos0 );
		}

		if ( nWidth > nWidth0 )
		{
			nWidth0 = nWidth;
			ss2 = ss1;
		};
		nPos0 = nPos;

		if ( nPos == -1 )
			break;
	}

	return ss2;
};

void CMyHint::OnLButtonDown(UINT nFlags, CPoint point) 
{
	Hide();

	CWnd::OnLButtonDown( nFlags, point ); 
};
void CMyHint::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
/*
	if(nChar == VK_LEFT)
		AfxMessageBox( "VK_LEFT" );
	else if(nChar == VK_RIGHT)
		AfxMessageBox( "VK_RIGHT" );
*/
	if(nChar == VK_ESCAPE)
		Hide();
};
void CMyHint::OnMouseMove(UINT nFlags, CPoint point)
{
	m_nPrevX = m_nX;
	m_nPrevY = m_nY;
	m_nX = point.x;
	m_nY = point.y;
};
