// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonSub.h"
#include "MyButton.h"
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers




void CMyButton::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

#ifdef _SAMPLE1

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	SetWindowRgn(rgn,TRUE);			// Construct your buttons region. This wont reflect in your view. But you can sense it by clicking the region area.

	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);	// Get dc for the button
	
	switch(lpDrawItemStruct->itemAction) 
	{
		case ODA_SELECT:
		{
			GetParent()->Invalidate();
		}							// no break; for this case
		case ODA_DRAWENTIRE:
		{
			if(lpDrawItemStruct->itemState & ODS_SELECTED)	
			{
				pDC->FillRgn(CRgn::FromHandle(trgn), CBrush::FromHandle((HBRUSH)GetStockObject(GRAY_BRUSH)));
			}
			// Draw button down state
			else
			{
				pDC->FillRgn(CRgn::FromHandle(trgn), CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
				HRGN r= ::CreateRectRgn(0,0,0,0);
				CombineRgn(r,trgn,0,RGN_COPY);
				OffsetRgn(r,2,2);
				pDC->FillRgn(CRgn::FromHandle(r), CBrush::FromHandle((HBRUSH)GetStockObject(GRAY_BRUSH)));
			}
			break;
		}
		case ODA_FOCUS: 
		{
				pDC->FillRgn(CRgn::FromHandle(trgn),CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH))); 
		}
		break;
	}
	// Draw button caption.
}

#endif



void CMyButton::SetRgn(CRgn *region)
{
	rgn=::CreateRectRgn(0,0,0,0); 
	CombineRgn(rgn,region->operator HRGN(),NULL,RGN_COPY);
	trgn=::CreateRectRgn(0,0,0,0);
	CombineRgn(trgn,region->operator HRGN(),NULL,RGN_COPY);
}

#ifdef _SAMPLE2

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
   UINT uStyle = DFCS_BUTTONPUSH;

   // This code only works with buttons.
   ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

   // If drawing selected, add the pushed style to DrawFrameControl.
   if (lpDrawItemStruct->itemState & ODS_SELECTED)
      uStyle |= DFCS_PUSHED;

   // Draw the button frame.
   ::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
      DFC_BUTTON, uStyle);

   // Get the button's text.
   CString strText;
   GetWindowText(strText);

   // Draw the button text using the text color red.
   COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255,0,0));
   ::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
      &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
   ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}

#endif
