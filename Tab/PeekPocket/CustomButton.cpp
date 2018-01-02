
#include "CustomButton.h"

IMPLEMENT_DYNAMIC(CCustomButton, CButton)
/////////////////////////////////////////////////////////////////////////////
// CCustomButton

CCustomButton::CCustomButton()
{
	m_crTxtIdle=::GetSysColor(COLOR_BTNTEXT);
	m_crBkgIdle=::GetSysColor(COLOR_BTNFACE);
	m_crTxtPressed=m_crTxtIdle;
	m_crBkgPressed=m_crBkgIdle;
	m_crFrame=m_crTxtIdle;
	m_crHGStart=RGB(0, 0, 0);
	m_crHGEnd=RGB(255, 255, 255);

	m_bPressed=false;

	m_bFlat=true;
	m_bTransparent=false;
	m_bHGradient=false;
	m_bIsGroup=false;

	m_hBmpActive=m_hBmpInactive=NULL;
	m_dwBmpW=m_dwBmpH=0;
	m_hCustomFont=NULL;
	m_ctType=btCustomButton;
	RegisterCustomClass();
}

//////////////////////////////////////////////////////////////
CCustomButton::~CCustomButton()
{
	if(m_hBmpActive != NULL)
	{
		DeleteObject(m_hBmpActive);
	}
	if(m_hBmpInactive != NULL)
	{
		DeleteObject(m_hBmpInactive);
	}
	m_DrawDC.SelectObject(m_hOldDCBmp);
	DeleteObject(m_hOldDCBmp);
	if(m_hCustomFont != NULL)
	{
		DeleteObject(m_hCustomFont);
	}
}

//////////////////////////////////////////////////////////////////////////
bool CCustomButton::RegisterCustomClass()
{
WNDCLASS wndcls;
HINSTANCE hInst;

	hInst = AfxGetInstanceHandle();

	if(!(::GetClassInfo(hInst, _T("CustomButtonClass"), &wndcls)))
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
		wndcls.lpszClassName    = _T("CustomButtonClass");

		if(FALSE == AfxRegisterClass(&wndcls))
		{
#ifdef _DEBUG
			OutputDebugString(_T("Failed to register class for Custom_button"));
#endif
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CCustomButton, CButton)
	//{{AFX_MSG_MAP(CCustomButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_MESSAGE(BM_SETCHECK, OnBMSetCheck)
		ON_MESSAGE(BM_GETCHECK, OnBMGetCheck)
		//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
LRESULT CCustomButton::OnBMSetCheck(WPARAM wParam, LPARAM lParam)
{
	//if radio
	if(m_ctType == btCustomRadio || m_ctType == btCustomCheckBox)
	{
		if(wParam == BST_CHECKED)
		{
			m_bPressed=true;
			SetWindowText(m_strActiveCaption);
		}
		else
		{
			m_bPressed=false;
			SetWindowText(m_strCaption);
		}
		Invalidate();
	}
	//processed
	return 0;
}

//////////////////////////////////////////////////////////////////////////
LRESULT CCustomButton::OnBMGetCheck(WPARAM wParam, LPARAM lParam)
{
	if(m_bPressed == true)
	{
		return BST_CHECKED;
	}
	else
	{
		return BST_UNCHECKED;
	}
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::PreSubclassWindow()
{
LONG lStyle;

	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	if((lStyle & BS_GROUPBOX) == BS_GROUPBOX)
	{
		m_bIsGroup=true;
		m_ctType=btCustomGroup;
	}
	else
	{
		m_bIsGroup=false;
		if(((lStyle & BS_GROUPBOX) == BS_CHECKBOX) || ((lStyle & BS_GROUPBOX) == BS_AUTOCHECKBOX))
		{
			m_ctType=btCustomCheckBox;
		}
		else
		if((lStyle & BS_GROUPBOX) == BS_RADIOBUTTON || ((lStyle & BS_GROUPBOX) == BS_AUTORADIOBUTTON))
		{
			m_ctType=btCustomRadio;
		}
		else
		{
			m_ctType=btCustomButton;
			if(lStyle & BS_FLAT)
			{
				m_bFlat=true;
			}
			else
			{
				m_bFlat=false;
			}
		}
	}

	GetWindowText(m_strCaption);
	m_strActiveCaption=m_strCaption;

	ModifyStyle(BS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);

	//at this stage we do have a HWND and a DC
	CDC *pDC;
	CRect rc;

	GetClientRect(&rc);
	pDC=GetDC();
	if(pDC != NULL)
	{
		m_DrawDC.CreateCompatibleDC(pDC);
		m_DrawBitmap.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
		m_hOldDCBmp=m_DrawDC.SelectObject(m_DrawBitmap.GetSafeHandle());
		ReleaseDC(pDC);
	}
#ifdef _DEBUG
	else
	{
		OutputDebugString(_T("Custom_button failed to get DC."));
	}
#endif


	CButton::PreSubclassWindow();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point)
{
LONG lStyle;

	//if not disabled
	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	if( !(lStyle & WS_DISABLED))
	{
		//depending on type...
		switch(m_ctType)
		{
			case btCustomButton:
			{
				//if regular button, state changes to not pressed
				if( !(lStyle & BS_PUSHLIKE))
				{
					m_bPressed=false;
					SetWindowText(m_strCaption);
					Invalidate();
				}
				else
				{
					//nothing to do
				}
				break;
			}//case Custom button
			case btCustomRadio:
			{
				break;
			}//Custom radio
			case btCustomCheckBox:
			{
				break;
			}
		}
	}
	CButton::OnLButtonUp(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point)
{
LONG lStyle;

	//if not disabled
	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	if( !(lStyle & WS_DISABLED))
	{
		//depending on type...
		switch(m_ctType)
		{
			case btCustomButton:
			{
				//if regular button, state changes to pressed
				if( !(lStyle & BS_PUSHLIKE))
				{
					m_bPressed=true;
					SetWindowText(m_strActiveCaption);
					//			SetCheck(BST_CHECKED);
				}
				else
				{
					//toggle state
					m_bPressed= !m_bPressed;
					//			SetCheck(m_bPressed == true ? BST_CHECKED : BST_UNCHECKED);
					SetWindowText(m_bPressed == true ? m_strActiveCaption : m_strCaption);
				}
				Invalidate();
				break;
			}//Custom button
			case btCustomRadio:
			{
				//if not checked, check button
				if(m_bPressed == false)
				{
					m_bPressed=true;
					SetWindowText(m_strActiveCaption);
					SetCheck(BST_CHECKED);

					//uncheck all radios in the group
					CWnd *pParentWnd;
					pParentWnd=GetParent();
					if(pParentWnd != NULL)
					{
						CWnd *pStart, *pSibling;

						pStart=pSibling=pParentWnd->GetNextDlgGroupItem(this, TRUE);
						do
						{
							if(pSibling == NULL) 
							{
								break;
							}
							if(this != pSibling)
//							&&	((GetWindowLongW( sibling, GWL_STYLE) & 0x0f) == BS_AUTORADIOBUTTON))
							{
								pSibling->SendMessage(BM_SETCHECK, BST_UNCHECKED, 0);
							}
							pSibling=pParentWnd->GetNextDlgGroupItem(pSibling, FALSE);
						}while(pSibling != pStart);
					}//if parent != NULL
				}
				break;
			}
			case btCustomCheckBox:
			{
				//toggle state
				m_bPressed= !m_bPressed;
				SetWindowText(m_bPressed == true ? m_strActiveCaption : m_strCaption);
				SetCheck(m_bPressed == true ? BST_CHECKED : BST_UNCHECKED);
				break;
			}
		}
	}
	//disable shell animation
	//call default handler instead of OnLButtonDown, which would call SHRecognizeGesture
	Default();
}

/////////////////////////////////////////////////////////////////////////////
void CCustomButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
CDC* pDC;
CRect itemRect;
LONG lStyle;
HGDIOBJ hOldFont;

	pDC=CDC::FromHandle(lpDIS->hDC);

	itemRect=lpDIS->rcItem;

	if(m_hCustomFont != NULL)
	{
		hOldFont=m_DrawDC.SelectObject((HGDIOBJ)m_hCustomFont);
	}

	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	switch(m_ctType)
	{
		case btCustomButton:
		{
			DrawPB(&m_DrawDC, &itemRect);
			break;
		}
		case btCustomRadio:
		case btCustomCheckBox:
		{
			DrawRBCB(&m_DrawDC, &itemRect);
			break;
		}
		case btCustomGroup:
		{
			DrawGB(&m_DrawDC, &itemRect);
			break;
		}
	}

	if(m_hCustomFont != NULL)
	{
		m_DrawDC.SelectObject(hOldFont);
	}

	//finally blit mem DC to screen
	pDC->BitBlt(0, 0, itemRect.Width(), itemRect.Height(), &m_DrawDC, 0, 0, SRCCOPY);
}

//////////////////////////////////////////////////////////////////////////
//gradient background drawing
void CCustomButton::DrawGradient(CDC *pDC)
{
CRect rc;
double dHRStep, dHGStep, dHBStep, dR, dG, dB;
int i, w, h;

	GetClientRect(&rc);

	w=rc.Width();
	h=rc.Height();

	//horizontal step values for R, G, B colors
	if(m_bPressed == false)
	{
		dR=GetRValue(m_crHGEnd);
		dG=GetGValue(m_crHGEnd);
		dB=GetBValue(m_crHGEnd);
	}
	else
	{
		dR=GetRValue(m_crHGStart);
		dG=GetGValue(m_crHGStart);
		dB=GetBValue(m_crHGStart);
	}

	dHRStep=dR;
	dHGStep=dG;
	dHBStep=dB;

	if(m_bPressed == false)
	{
		dHRStep-=GetRValue(m_crHGStart);
		dHGStep-=GetGValue(m_crHGStart);
		dHBStep-=GetBValue(m_crHGStart);
	}
	else
	{
		dHRStep-=GetRValue(m_crHGEnd);
		dHGStep-=GetGValue(m_crHGEnd);
		dHBStep-=GetBValue(m_crHGEnd);
	}

	dHRStep/=h;
	dHGStep/=h;
	dHBStep/=h;

	//color start values
	if(m_bPressed == false)
	{
		dR=GetRValue(m_crHGStart);
		dG=GetGValue(m_crHGStart);
		dB=GetBValue(m_crHGStart);
	}
	else
	{
		dR=GetRValue(m_crHGEnd);
		dG=GetGValue(m_crHGEnd);
		dB=GetBValue(m_crHGEnd);
	}

	//draw horz lines
	for(i=2; i<h-2; i++)
	{
		CPen ptmp(PS_SOLID, 1, RGB(dR, dG, dB));

		HGDIOBJ hOldPen=pDC->SelectObject(ptmp);

		pDC->MoveTo(2, i);
		pDC->LineTo(w-2, i);

		pDC->SelectObject(hOldPen);

		//next color
		dR+=dHRStep;
		dG+=dHGStep;
		dB+=dHBStep;
	}

}

//////////////////////////////////////////////////////////////////////////
//draw group box
void CCustomButton::DrawGB(CDC* pDC, CRect* pRect)
{
CPen framepen;
CBrush framebrush, titlebrush;
HGDIOBJ hOldPen, hOldBrush;
CString str;
LONG lStyle;
UINT nFormat;
bool bIsTxtBottom;
CSize sTextSize;
CRect rcFrame, rcText;

	//get style
	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	//is text bottom?
	if((m_cfFlags & bfMask) == bfTextBottom)
	{
		bIsTxtBottom=true;
	}
	else
	{
		bIsTxtBottom=false;
	}

	//get text dimensions
	GetWindowText(str);
	sTextSize=pDC->GetTextExtent(str);
	if(str == _T(""))
	{
		//if no title, get current text height with another call
//		CSize sTmp;
//		sTmp=pDC->GetTextExtent(_T("A"));
//		sTextSize.cy=sTmp.cy;
		sTextSize.cy=0;
	}

	//create frame pen
	framepen.CreatePen(PS_SOLID, 1, m_crFrame);

	framebrush.CreateSolidBrush(m_crBkgIdle);

	//create title brush
	titlebrush.CreateSolidBrush(m_crFrame);

	//draw frame box
	hOldPen=pDC->SelectObject(framepen);	
	hOldBrush=pDC->SelectObject(framebrush);

	rcFrame=*pRect;
	rcText=rcFrame;

	if(bIsTxtBottom == true)
	{
		rcText.top = rcFrame.bottom - sTextSize.cy;
		rcFrame.bottom -= sTextSize.cy/2;
	}
	else
	{
		rcText.bottom = rcFrame.top + sTextSize.cy;
		rcFrame.top += sTextSize.cy/2;
	}

	pDC->Rectangle(rcFrame);

	pDC->SelectObject(hOldPen);
	pDC->SelectObject(hOldBrush);

	//draw title rectangle, only if there is caption text
	if(str != _T(""))
	{
		pDC->FillRect(rcText, &titlebrush);
	}

	//prepare text
	GetClientRect(&rcText);
	if(str != _T(""))
	{
		rcText.left += 5;
		rcText.right -= 5;

		switch(lStyle & BS_CENTER)
		{
			case BS_CENTER:
			{
				nFormat=DT_CENTER;
				break;
			}
			case BS_RIGHT:
			{
				nFormat=DT_RIGHT;
				break;
			}
			default:
				nFormat=DT_LEFT;
		}

		if(bIsTxtBottom == true)
		{
			nFormat |= DT_BOTTOM;
		}
		else
		{
			nFormat |= DT_TOP;
		}

		pDC->SetTextColor(m_crTxtIdle);
/*
		if(m_bTransparent == true)
		{
			pDC->SetBkMode(TRANSPARENT);
		}
		else
		{
			pDC->SetBkMode(OPAQUE);
			pDC->SetBkColor(m_crFrame);
		}
*/
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(str, &rcText, nFormat | DT_SINGLELINE);
	}
}

//////////////////////////////////////////////////////////////////////////
//draw radio/checkbox
void CCustomButton::DrawRBCB(CDC* pDC, CRect* pRect)
{
COLORREF crColor;
HANDLE hCurrentBmp;
CString strTitle;
CRect rcText, rcBtn, rcImg;
LONG lStyle, lRight;
int tx, ty, ix, iy;
UINT nDTFormat;

	//draw radio background
	//paint with active/inactive color depending on state
	if(m_bPressed == true)
	{
		crColor=m_crBkgPressed;
	}
	else
	{
		crColor=m_crBkgIdle;
	}

	CBrush NewBrush(crColor); 
	pDC->SetBrushOrg(0,0);
	HGDIOBJ hOldBrush = pDC->SelectObject(&NewBrush);   

	//no border, rect filled with color
	pDC->PatBlt(pRect->left, pRect->top, pRect->Width(), pRect->Height(), PATCOPY);
	pDC->SelectObject(hOldBrush);

	//prepare to draw text/image
	GetClientRect(rcBtn);

	//get style
	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	//setup colors
/*
	if(m_bTransparent == true)
	{
		pDC->SetBkMode(TRANSPARENT);
	}
	else
	{
		pDC->SetBkMode(OPAQUE);
	}
*/

	pDC->SetBkMode(TRANSPARENT);
	if(m_bPressed == true)
	{
		pDC->SetTextColor(m_crTxtPressed);
		pDC->SetBkColor(m_crBkgPressed);
	}
	else
	{
		pDC->SetTextColor(m_crTxtIdle);
		pDC->SetBkColor(m_crBkgIdle);
	}

	//get current bitmap handle
	if(m_bPressed == true)
	{
		hCurrentBmp=m_hBmpActive;
	}
	else
	{
		hCurrentBmp=m_hBmpInactive;
	}

	//create image rect
	if(hCurrentBmp == NULL)
	{
		//no bitmap, will draw default
		m_dwBmpW=m_dwBmpH=16;
	}
	rcImg.SetRect(0, 0, m_dwBmpW, m_dwBmpH);

	//create text rect
	GetWindowText(strTitle);
	GetClientRect(rcText);

	rcText.right-=(m_dwBmpW+4);
	lRight=rcText.right;

	if(strTitle != _T(""))
	{
		//calculate text height
		nDTFormat = GetDTFlag(lStyle);
		pDC->DrawText(strTitle, &rcText, nDTFormat | DT_EXPANDTABS | DT_CALCRECT | DT_WORDBREAK);
	}

	rcText.right=lRight;

	//image on left, text on right:
	if((m_cfFlags & bfMask) == bfNone || m_cfFlags & bfTextRight)
	{
		//text & image positions
		ix=0;
		iy=(rcBtn.Height()-m_dwBmpH)/2;
		if(lStyle & BS_RIGHT)
		{
			tx=ix+m_dwBmpW+2;
		}
		else
		{
			tx=ix+m_dwBmpW+4;
		}
		ty=((rcBtn.Height()-rcText.Height())/2 )-1;
	}//BS_RIGHT
	else
	//text on left, image on right:
	if(m_cfFlags & bfTextLeft)
	{
		//text & image positions
		tx=0;
		ty=((rcBtn.Height()-rcText.Height())/2)-1;
		//text image y position
		iy=(rcBtn.Height()-m_dwBmpH)/2;
		ix=rcBtn.Width()-m_dwBmpW;
	}

	//draw image
	if(hCurrentBmp != NULL)		//if some image loaded
	{
		DisplayTransparentBMP(pDC, (HBITMAP)hCurrentBmp, m_dwBmpW, m_dwBmpH, ix, iy);
	}
	else
	{
		//draw default
		DrawFrameControl(pDC->GetSafeHdc(), CRect(ix, iy, ix+m_dwBmpW, iy+m_dwBmpH), DFC_BUTTON, ( m_ctType == btCustomCheckBox ? DFCS_BUTTONCHECK : DFCS_BUTTONRADIO) | (m_bPressed==true ? DFCS_CHECKED : 0) );	
	}
	//draw text
	if(strTitle != _T(""))
	{
		rcText.OffsetRect(tx, ty);
		nDTFormat = GetDTFlag(lStyle);
		pDC->DrawText(strTitle, rcText, nDTFormat | DT_EXPANDTABS | DT_WORDBREAK);
	}
}

//////////////////////////////////////////////////////////////////////////
//draw push button
void CCustomButton::DrawPB(CDC* pDC, CRect* pRect)
{
COLORREF crColor;
CString strTitle;
CRect rcText, rcBtn, rcImg;
HANDLE hCurrentBmp;
LONG lStyle;
int tx, ty, ix, iy, xsp, ysp;
bool bOffs, bTextFits, bHasText, bHasImage;
UINT nDTFormat;

	//draw button background
	//paint with active/inactive color depending on state
	if(m_bPressed == true)
	{
		crColor=m_crBkgPressed;
	}
	else
	{
		crColor=m_crBkgIdle;
	}

	CBrush NewBrush(crColor); 
	pDC->SetBrushOrg(0,0);
	HGDIOBJ hOldBrush = pDC->SelectObject(&NewBrush);   

//	if(m_bFlat == true)
	{
		//no border, rect filled with color
		pDC->PatBlt(pRect->left, pRect->top, pRect->Width(), pRect->Height(), PATCOPY);
	}
/*
	else
	{
		//leave out border
		pDC->PatBlt(pRect->left+2, pRect->top+2, pRect->Width()-2, pRect->Height()-2, PATCOPY);
	}
*/
	pDC->SelectObject(hOldBrush);

	//draw gradient if required
	if(m_bHGradient == true)
	{
		DrawGradient(&m_DrawDC);
	}

	//prepare to draw text/image
	GetClientRect(rcBtn);

	//get style
	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	//get current bitmap handle
	if(m_bPressed == true)
	{
		hCurrentBmp=m_hBmpActive;
	}
	else
	{
		hCurrentBmp=m_hBmpInactive;
	}

	//create image rect
	rcImg.SetRect(0, 0, m_dwBmpW, m_dwBmpH);

	if(hCurrentBmp == NULL)
	{
		bHasImage=false;
	}
	else
	{
		bHasImage=true;
	}

	//create text rect
	GetWindowText(strTitle);
	if(strTitle != _T(""))
	{
		bHasText=true;
		//setup DC
/*
		if(m_bTransparent == true)
		{
			pDC->SetBkMode(TRANSPARENT);
		}
		else
		{
			pDC->SetBkMode(OPAQUE);
		}
*/
		pDC->SetBkMode(TRANSPARENT);
		if(m_bPressed == true)
		{
			pDC->SetTextColor(m_crTxtPressed);
			pDC->SetBkColor(m_crBkgPressed);
		}
		else
		{
			pDC->SetTextColor(m_crTxtIdle);
			pDC->SetBkColor(m_crBkgIdle);
		}

		//calculate text width/height
		GetClientRect(rcText);

		//if has image, text must fit into smaller rect
		if(bHasImage == true)
		{
			switch(m_cfFlags & bfMask)
			{
				case bfTextBottom:
				case bfTextTop:
				{
					//text must fit into lower rect
					rcText.bottom-=m_dwBmpH;
					break;
				}
				default:
				{
					//text must fit into narrower rect
					rcText.right-=m_dwBmpW;
				}
			}//switch text alignment flags
		}//if has image

		nDTFormat = GetDTFlag(lStyle);
		pDC->DrawText(strTitle, &rcText, nDTFormat | DT_EXPANDTABS | DT_CALCRECT);
	}
	else
	{
		bHasText=false;
		rcText.SetRectEmpty();
	}
	
	//need to offset text/image for pressed button?
	if(m_bFlat == false && m_bPressed == true)
	{
		bOffs=true;	
	}
	else
	{
		bOffs=false;
	}

	//if text and image would be too long, omit text
	bTextFits=true;
/*
	if(m_cfFlags == CustomControlData::cfTextTop || m_cfFlags == CustomControlData::cfTextBottom)
	{
		if(rcBtn.Height() > rcImg.Height() + rcText.Height())
		{
			bTextFits=true;
		}
	}
	else
	{
		if(rcBtn.Width() > rcImg.Width() + rcText.Width())
		{
			bTextFits=true;
		}
	}
*/

	//calculate text and image x,y positions
	if(bTextFits == true)
	{
		//image on left, text on right:
		if((m_cfFlags & bfMask) == bfNone || m_cfFlags & bfTextRight)
		{
			//x spacing
			xsp=(rcBtn.Width()-rcImg.Width()-rcText.Width());
			if(bHasImage == true && bHasText == true)
			{
				xsp/=3;
			}
			else
			{
				//no text or no image
				xsp/=2;
			}
			ix=xsp;
			//text & image y position
			iy=(rcBtn.Height()-m_dwBmpH)/2;
			ty=(rcBtn.Height()-rcText.Height())/2;

			if(bHasImage == true)
			{
				tx=xsp+ix+m_dwBmpW;
			}
			else
			{
				tx=xsp;
			}
		}//BS_RIGHT
		else
		//text on left, image on right:
		if(m_cfFlags & bfTextLeft)
		{
			//x spacing
			xsp=(rcBtn.Width()-rcImg.Width()-rcText.Width());
			if(bHasImage == true && bHasText == true)
			{
				xsp/=3;
			}
			else
			{
				xsp/=2;
			}
			tx=xsp;
			//text image y position
			iy=(rcBtn.Height()-m_dwBmpH)/2;
			ty=(rcBtn.Height()-rcText.Height())/2;

			if(bHasText == true)
			{
				ix=xsp+tx+rcText.Width();
			}
			else
			{
				ix=xsp;
			}
		}
		else
		//text on top, image on bottom:
		if(m_cfFlags & bfTextTop)
		{
			//y spacing
			ysp=(rcBtn.Height()-rcImg.Height()-rcText.Height());
			if(bHasImage == true && bHasText == true)
			{
				ysp/=3;
			}
			else
			{
				ysp/=2;
			}
			ty=ysp;
			tx=(rcBtn.Width()-rcText.Width())/2;
			ix=(rcBtn.Width()-rcImg.Width())/2;
			
			if(bHasText == true)
			{
				iy=ysp+ty+rcText.Height();
			}
			else
			{
				iy=ysp;
			}
		}
		else
		//image on top, text on bottom:i
		if(m_cfFlags & bfTextBottom)
		{
			//y spacing
			ysp=(rcBtn.Height()-rcImg.Height()-rcText.Height());
			if(bHasImage == true && bHasText == true)
			{
				ysp/=3;
			}
			else
			{
				ysp/=2;
			}
			iy=ysp;
			tx=(rcBtn.Width()-rcText.Width())/2;
			ix=(rcBtn.Width()-rcImg.Width())/2;

			if(bHasImage == true)
			{
				ty=ysp+iy+m_dwBmpH;
			}
			else
			{
				ty=ysp;
			}
		}//BS_BOTTOM

		//offset pushed button
		if(bOffs == true)
		{
			//offset
			tx+=1;
			ty+=1;
			ix+=1;
			iy+=1;
		}
	}//if text fits
	else
	{
#ifdef _DEBUG
		OutputDebugString(_T("Button text does not fit in: \"") + strTitle + _T("\"\n"));
#endif
		if(rcBtn.Width() > rcImg.Width())
		{
			ix=(rcBtn.Width()-rcImg.Width())/2;
		}
		else
		{
			ix=0;
		}
		if(rcBtn.Height() > rcImg.Height())
		{
			iy=(rcBtn.Height()-rcImg.Height())/2;
		}
		else
		{
			iy=0;
		}

		//offset pressed non-flat button
		if(bOffs == true)
		{
			ix++;
			iy++;
		}
	}

	//at this point tx, ty, ix, iy values are set up for text and image x,y positions

	//draw image
	if(lStyle & BS_BITMAP)
	{
		DisplayTransparentBMP(pDC, (HBITMAP)hCurrentBmp, m_dwBmpW, m_dwBmpH, ix, iy);
	}
	//draw text
	if(bTextFits == true && strTitle != _T(""))
	{
		rcText.OffsetRect(tx, ty);
		nDTFormat = GetDTFlag(lStyle);
		pDC->DrawText(strTitle, rcText, nDTFormat | DT_EXPANDTABS);
	}

	//draw border
	DrawPBBorder(pDC, pRect);

	//done!
}

///////////////////////////////////////////////////////////////
//draw push button border
void CCustomButton::DrawPBBorder(CDC* pDC, CRect* pRect)
{
	if(m_bFlat == true)
	{
		//no border for flat buttons
		return;
	}

	if(m_bHGradient == true)
	{
		if(m_bPressed == true)
		{
			COLORREF crAvg, crDarker, crLighter;

			crAvg=RGB_AVERAGE(m_crHGStart, m_crHGEnd);
			crLighter=OffsetColor(crAvg, -0.1);
			crDarker=OffsetColor(crAvg, 0.2);

			CPen penLighter(PS_SOLID, 0, crLighter);
			CPen penLight(PS_SOLID, 0, crAvg);
			CPen penDark(PS_SOLID, 0, crAvg);
			CPen penDarker(PS_SOLID, 0, crDarker);

			//top-left border
			//darker line
			CPen* pOldPen = pDC->SelectObject(&penDarker);
			pDC->MoveTo(pRect->left, pRect->top+3);
			pDC->LineTo(pRect->left, pRect->bottom-3);
			pDC->MoveTo(pRect->left+3, pRect->top);
			pDC->LineTo(pRect->right-4, pRect->top);

			//dark
			pDC->SelectObject(penDark);
			pDC->MoveTo(pRect->left+1, pRect->bottom-3);
			pDC->LineTo(pRect->left+1, pRect->top+2);
			pDC->MoveTo(pRect->left+3, pRect->top+1);
			pDC->LineTo(pRect->right-2, pRect->top+1);

			//bottom-right border
			//lighter line
			pDC->SelectObject(penLighter);
			pDC->MoveTo(pRect->left+3, pRect->bottom-1);
			pDC->LineTo(pRect->right-3, pRect->bottom-1);
			pDC->MoveTo(pRect->right-1, pRect->bottom-4);
			pDC->LineTo(pRect->right-1, pRect->top+2);			

			pDC->SetPixel(pRect->left, pRect->top+3, crDarker);
			pDC->SetPixel(pRect->left+1, pRect->top+2, crDarker);
			pDC->SetPixel(pRect->left+2, pRect->top+1, crDarker);

			pDC->SetPixel(pRect->right-3, pRect->bottom-1, crLighter);
			pDC->SetPixel(pRect->right-2, pRect->bottom-2, crLighter);
			pDC->SetPixel(pRect->right-1, pRect->bottom-3, crLighter);

			//light line
			pDC->SelectObject(penLight);
			pDC->MoveTo(pRect->left+2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->MoveTo(pRect->right-2, pRect->bottom-3);
			pDC->LineTo(pRect->right-2, pRect->top+1);
			//
			pDC->SelectObject(pOldPen);
		}
		else
			//draw not pressed button border
		{
			COLORREF crAvg, crDarker, crLighter;

			crAvg=RGB_AVERAGE(m_crHGStart, m_crHGEnd);
			crLighter=OffsetColor(crAvg, -0.1);
			crDarker=OffsetColor(crAvg, 0.2);

			CPen penLighter(PS_SOLID, 0, crLighter);
			CPen penLight(PS_SOLID, 0, crAvg);
			CPen penDark(PS_SOLID, 0, crAvg);
			CPen penDarker(PS_SOLID, 0, crDarker);

			//top-left border
			//lighter line
			CPen* pOldPen = pDC->SelectObject(&penLighter);
			pDC->MoveTo(pRect->left, pRect->top+4);
			pDC->LineTo(pRect->left, pRect->bottom-3);
			pDC->MoveTo(pRect->left+4, pRect->top);
			pDC->LineTo(pRect->right-4, pRect->top);

			//light
			pDC->SelectObject(penLight);
			pDC->MoveTo(pRect->left+1, pRect->bottom-3);
			pDC->LineTo(pRect->left+1, pRect->top+2);
			pDC->MoveTo(pRect->left+3, pRect->top+1);
			pDC->LineTo(pRect->right-2, pRect->top+1);

			//bottom-right border
			//darker line
			pDC->SelectObject(penDarker);
			pDC->MoveTo(pRect->left+3, pRect->bottom-1);
			pDC->LineTo(pRect->right-3, pRect->bottom-1);
			pDC->MoveTo(pRect->right-1, pRect->bottom-4);
			pDC->LineTo(pRect->right-1, pRect->top+2);			

			pDC->SetPixel(pRect->right-3, pRect->bottom-1, crDarker);
			pDC->SetPixel(pRect->right-2, pRect->bottom-2, crDarker);
			pDC->SetPixel(pRect->right-1, pRect->bottom-3, crDarker);

			pDC->SetPixel(pRect->left+2, pRect->top+2, crLighter);

			//dark line
			pDC->SelectObject(penDark);
			pDC->MoveTo(pRect->left+2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->MoveTo(pRect->right-2, pRect->bottom-3);
			pDC->LineTo(pRect->right-2, pRect->top+1);
			//
			pDC->SelectObject(pOldPen);
		}//if not pressed
	}//if hgradient
	else
	{
		//draw pressed non-gradient button
		if(m_bPressed == true)
		{
			CPen penLighter(PS_SOLID, 0, OffsetColor(m_crBkgPressed, -0.3));
			CPen penLight(PS_SOLID, 0, OffsetColor(m_crBkgPressed, -0.2));
			CPen penDark(PS_SOLID, 0, OffsetColor(m_crBkgPressed, 0.2));
			CPen penDarker(PS_SOLID, 0, OffsetColor(m_crBkgPressed, 0.3));
			//top-left border
			//darker line
			CPen* pOldPen = pDC->SelectObject(&penDarker);

			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->left, pRect->top);
			pDC->LineTo(pRect->right, pRect->top);
			//dark
			pDC->SelectObject(penDark);
			pDC->MoveTo(pRect->left+1, pRect->bottom-1);
			pDC->LineTo(pRect->left+1, pRect->top+1);
			pDC->LineTo(pRect->right, pRect->top+1);
			//bottom-right border
			//lighter line
			pDC->SelectObject(penLighter);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->top-1);			
			//light line
			pDC->SelectObject(penLight);
			pDC->MoveTo(pRect->left+1, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->top);
			//
			pDC->SelectObject(pOldPen);
		}
		else
		//draw not pressed button
		{
			CPen penLighter(PS_SOLID, 0, OffsetColor(m_crBkgIdle, -0.3));
			CPen penLight(PS_SOLID, 0, OffsetColor(m_crBkgIdle, -0.2));
			CPen penDark(PS_SOLID, 0, OffsetColor(m_crBkgIdle, 0.2));
			CPen penDarker(PS_SOLID, 0, OffsetColor(m_crBkgIdle, 0.3));
			//top-left border
			//lighter line
			CPen* pOldPen = pDC->SelectObject(&penLighter);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->left, pRect->top);
			pDC->LineTo(pRect->right, pRect->top);
			//light
			pDC->SelectObject(penLight);
			pDC->MoveTo(pRect->left+1, pRect->bottom-1);
			pDC->LineTo(pRect->left+1, pRect->top+1);
			pDC->LineTo(pRect->right, pRect->top+1);
			//bottom-right border
			//darker line
			pDC->SelectObject(penDarker);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->top-1);			
			//dark line
			pDC->SelectObject(penDark);
			pDC->MoveTo(pRect->left+1, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->top);
			//
			pDC->SelectObject(pOldPen);
		}//if not pressed
	}//if not gradient
}

//////////////////////////////////////////////////////////////////////////
//initialization
/*
LRESULT CCustomButton::OnSetControlData(WPARAM wParam, LPARAM lParam)
{
CustomControlData *pccdControlData;
LONG lStyle;
DWProp dwp;
StrProp strp;
CRect rc;
DWORD dwTemp;

	if(lParam == NULL)
	{
		return 0;
	}
	GetClientRect(&rc);
	pccdControlData=(CustomControlData *)lParam;

	//store type
	m_ctType=pccdControlData->ctType;
	m_cfFlags=pccdControlData->cfFlags;

	//init font, if specified
	dwTemp=pccdControlData->dwFontID;
	if(dwTemp != 0)
	{
		m_hCustomFont=g_SkinManager.GetFontHandle(dwTemp);
	}

	if(pccdControlData->ctType == CustomControlData::ctCustomGroup)
	{
		m_bIsGroup=true;
		//groupbox specific params
		if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpFrameColor, dwp))
		{
			m_crFrame=dwp.dwValue;
		}
	}
	else
	{
		m_bIsGroup=false;
	}

	//is flat button?
	lStyle=GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	if(lStyle & BS_FLAT)
	{
		m_bFlat=true;
	}
	else
	{
		m_bFlat=false;
	}

	//gradient colors?
	if(m_cfFlags & bfHGradient)
	{
		m_bHGradient=true;
	}

	//init captions
	if(TRUE == pccdControlData->spmStrProps.Lookup(cspCaption, strp))
	{
		m_strCaption=m_strActiveCaption=strp.strValue;
		if(TRUE == pccdControlData->spmStrProps.Lookup(cspActiveCaption, strp))
		{
			m_strActiveCaption=strp.strValue;
		}	
	}
	
	//init text colors
	if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpBkgIdleColor, dwp))
	{
		m_crBkgIdle=dwp.dwValue;
	}

	if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpBkgActiveColor, dwp))
	{
		m_crBkgPressed=dwp.dwValue;
	}

	if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpTxtIdleColor, dwp))
	{
		m_crTxtIdle=dwp.dwValue;
	}

	if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpTxtActiveColor, dwp))
	{
		m_crTxtPressed=dwp.dwValue;
	}

	//init gradient colors
	if(m_bHGradient == true)
	{
		if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpHGradientStart, dwp))
		{
			m_crHGStart=dwp.dwValue;
		}
		if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpHGradientEnd, dwp))
		{
			m_crHGEnd=dwp.dwValue;
		}
	}

	//icon dimensions, if specified
	if(lStyle & BS_ICON)
	{
		if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpImgW, dwp))
		{
			m_dwBmpW=dwp.dwValue;
		}
		if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpImgH, dwp))
		{
			m_dwBmpH=dwp.dwValue;
		}
	}
	
	//load bitmaps/icons from file or resource	
	//if has BS_ICON style, load icon from resource
	if(lStyle & BS_ICON)
	{
		if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpBkgResource, dwp))
		{
			m_hBmpInactive=g_SkinManager.LoadIconResource(dwp.dwValue, m_dwBmpW, m_dwBmpH);
			//load same resource for "active"
			m_hBmpActive=g_SkinManager.LoadIconResource(dwp.dwValue, m_dwBmpW, m_dwBmpH);
			if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpBkgActiveResource, dwp))
			{
				//free previously loaded "active"
				g_SkinManager.FreeResource(m_hBmpActive);
				//and reload
				m_hBmpActive=g_SkinManager.LoadIconResource(dwp.dwValue, m_dwBmpW, m_dwBmpH);
			}
		}
	}//icon
	else
	//if has BS_BITMAP style, load bitmap from resource, or if resource zero, load from file
	if(lStyle & BS_BITMAP)
	{
		//is the bitmap a resource?
		if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpBkgResource, dwp))
		{
			//load from resource
			m_hBmpInactive=g_SkinManager.LoadBMPResource(dwp.dwValue);
			//load same for "active"
			m_hBmpActive=g_SkinManager.LoadBMPResource(dwp.dwValue);
			if(TRUE == pccdControlData->dpmDWProps.Lookup(cdpBkgActiveResource, dwp))
			{
				//free previously loaded "active"
				g_SkinManager.FreeResource(m_hBmpActive);
				//and reload
				m_hBmpActive=g_SkinManager.LoadBMPResource(dwp.dwValue);
			}
		}
		else
		{
			//no, its a file!
			//load from file
			if(TRUE == pccdControlData->spmStrProps.Lookup(cspBkgFile, strp))
			{
				m_hBmpInactive=g_SkinManager.LoadBitmapFile(g_SkinManager.GetSkinPath() + strp.strValue);
				//load same for "active"
				m_hBmpActive=g_SkinManager.LoadBitmapFile(g_SkinManager.GetSkinPath() + strp.strValue);
				if(TRUE == pccdControlData->spmStrProps.Lookup(cspBkgActiveFile, strp))
				{
					//free previously loaded "active"
					g_SkinManager.FreeResource(m_hBmpActive);
					//and reload
					m_hBmpActive=g_SkinManager.LoadBitmapFile(g_SkinManager.GetSkinPath() + strp.strValue);
				}
			}
		}
		//get BMP dimensions
		g_SkinManager.GetBitmapDimensions(m_hBmpActive, &m_dwBmpW, &m_dwBmpH);
	}//bitmap

	//at this stage we do have a HWND and a DC
	CDC *pDC;

	pDC=GetDC();
	if(pDC != NULL)
	{
		m_DrawDC.CreateCompatibleDC(pDC);
		m_DrawBitmap.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
		m_hOldDCBmp=m_DrawDC.SelectObject(m_DrawBitmap.GetSafeHandle());
		ReleaseDC(pDC);
	}
#ifdef _DEBUG
	else
	{
		OutputDebugString(_T("Custom_button failed to get DC."));
	}
#endif
	return 0;
}
*/

//////////////////////////////////////////////////////////////////////////
//Get DrawText flags parameter from button BS_XXX styles
DWORD CCustomButton::GetDTFlag(DWORD dwStyle)
{
DWORD dtStyle;

	dtStyle=0;

	if(!(dwStyle & BS_MULTILINE))
	{
		dtStyle |= DT_SINGLELINE;
	}
	else
	{
		dtStyle |= DT_WORDBREAK;
	}

	switch(dwStyle & BS_CENTER)
	{
		case BS_LEFT:
		{
			/* DT_LEFT is 0 */
			break;
		}
		case BS_RIGHT:
		{
			dtStyle |= DT_RIGHT;
			break;
		}
		case BS_CENTER:
		{
			dtStyle |= DT_CENTER;
			break;
		}
		default:
		dtStyle |= DT_CENTER;
	}

	switch(dwStyle & BS_VCENTER)
	{
		case BS_TOP:
		{
			/* DT_TOP is 0 */
			break;
		}
		case BS_BOTTOM:
		{
			dtStyle |= DT_BOTTOM;
			break;
		}
		/*
		case BS_VCENTER:
			//fall through:
		default:
			dtStyle |= DT_VCENTER;
		*/
	}
	return dtStyle;
}

//////////////////////////////////////////////////////////////////////////
//modify a color (lighten or darken)
//if dOffs is positive, it will darken the color, if negative, will lighten it
COLORREF CCustomButton::OffsetColor(COLORREF crColorIn, double dOffs)
{
COLORREF crColor;
BYTE bR, bG, bB, bR2, bG2, bB2;

	crColor=crColorIn;

	if(dOffs > 0.0 && dOffs <= 1.0)
	{
		bR = GetRValue(crColor);
		bG = GetGValue(crColor);
		bB = GetBValue(crColor);

		//red would underflow?
		if( bR < (BYTE)(dOffs * bR) )
		{
			bR2=0;
		}
		else
		{
			bR2 = (BYTE)(bR-(dOffs * bR));
		}

		//green would underflow?
		if( bG < (BYTE)(dOffs * bG) )
		{
			bG2=0;
		}
		else
		{
			bG2 = (BYTE)(bG-(dOffs * bG));
		}

		//blue would underflow?
		if( bB < (BYTE)(dOffs * bB) )
		{
			bB2=0;
		}
		else
		{
			bB2 = (BYTE)(bB-(dOffs * bB));
		}
		crColor = RGB(bR2, bG2, bB2);
	}
	else
		if(dOffs < 0.0 && dOffs >= -1.0)
		{
			bR = GetRValue(crColor);
			bG = GetGValue(crColor);
			bB = GetBValue(crColor);

			//red would overflow?
			if( (WORD)((1 - dOffs) * bR) < 0xff )
			{
				//no
				bR2 = (BYTE)(bR+(-dOffs * bR));
			}
			else
			{
				bR2=0xff;
			}
			//green would overflow?
			if( (WORD)((1 - dOffs) * bG) < 0xff )
			{
				//no
				bG2 = (BYTE)(bG+(-dOffs * bG));
			}
			else
			{
				bG2=0xff;
			}
			//blue would overflow?
			if( (WORD)((1 - dOffs) * bB) < 0xff )
			{
				//no
				bB2 = (BYTE)(bB+(-dOffs * bB));
			}
			else
			{
				bB2=0xff;
			}
			crColor = RGB(bR2, bG2, bB2);
		}
		return crColor;
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::DisplayTransparentBMP(CDC *pDestDC, HBITMAP hBmp, DWORD dwW, DWORD dwH, int nX, int nY)
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
void CCustomButton::SetCaption(CString strCaption, CString strActiveCaption)
{
	m_strCaption=strCaption;
	if(strActiveCaption != _T(""))
	{
		m_strActiveCaption=strActiveCaption;
	}
	else
	{
		m_strActiveCaption=m_strCaption;
	}
	if(m_bPressed == true)
	{
		SetWindowText(m_strActiveCaption);
	}
	else
	{
		SetWindowText(m_strCaption);
	}
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetFlags(DWORD dwFlags)
{
	m_cfFlags=dwFlags;
	if(m_cfFlags & bfHGradient)
	{
		m_bHGradient=true;
	}
	else
	{
		m_bHGradient=false;
	}
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetBitmaps(HBITMAP hBmpInactive, HBITMAP hBmpActive /* = NULL */)
{
BITMAP bmpData;

	//old present and new specified
	if(m_hBmpInactive != NULL && hBmpInactive != NULL)
	{
		//dump old
		DeleteObject(m_hBmpInactive);
		m_hBmpInactive=NULL;
		m_dwBmpH=m_dwBmpW=0;
	}

	if(hBmpInactive != NULL)
	{
		m_hBmpInactive=hBmpInactive;
		//get dimensions
		if(::GetObject(hBmpInactive, sizeof(bmpData), &bmpData) != 0)
		{
			m_dwBmpW=(DWORD)bmpData.bmWidth;
			m_dwBmpH=(DWORD)bmpData.bmHeight;
		}		
	}

	//old present and new specified
	if(m_hBmpActive != NULL && hBmpActive != NULL)
	{
		//dump old
		DeleteObject(m_hBmpActive);
		m_hBmpActive=NULL;
	}

	//if specified, use other bitmap for active state
	if(hBmpActive != NULL)
	{
		m_hBmpActive=hBmpActive;
	}
	else
	{
		//otherwise use inactive bitmap for active state	
		m_hBmpActive=m_hBmpInactive;
	}
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetBkgIdleColor(COLORREF crBkgIdle)
{
	m_crBkgIdle=crBkgIdle;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetBkgActiveColor(COLORREF crBkgActive)
{
	m_crBkgPressed=crBkgActive;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetFrgIdleColor(COLORREF crFrgIdle)
{
	m_crTxtIdle=crFrgIdle;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetFrgActiveColor(COLORREF crFrgActive)
{
	m_crTxtPressed=crFrgActive;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetGradientColors(COLORREF crStart, COLORREF crEnd)
{
	m_crHGStart=crStart;
	m_crHGEnd=crEnd;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetFrameColor(COLORREF crFrame)
{
	m_crFrame=crFrame;
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
void CCustomButton::SetFont(HFONT hFont)
{
	//purge old font
	if(m_hCustomFont != NULL)
	{
		DeleteObject(m_hCustomFont);
	}
	m_hCustomFont=hFont;
}
