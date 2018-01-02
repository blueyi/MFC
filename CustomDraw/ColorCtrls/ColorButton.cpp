#include "stdafx.h"
#include "ColorButton.h"

CColorButton::CColorButton()
{
}


CColorButton::~CColorButton()
{
}

BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

        CDC* pDC   = CDC::FromHandle(lpDIS->hDC);
        CRect rect = lpDIS->rcItem;
        UINT state = lpDIS->itemState;

        CString strText;
        GetWindowText(strText);

        if (state & ODS_SELECTED)
                pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
                pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect( CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));

        if( state & ODS_DISABLED )
        {
                pDC->FillSolidRect(rect, m_crDisabledBg);
        }
        else if (m_bOverControl)
        {
                pDC->FillSolidRect(rect, m_crHotBg);
        }
        else
        {
                pDC->FillSolidRect(rect, m_crBg);
        }

        // Draw the text
        if (!strText.IsEmpty())
        {
                
                COLORREF prevColor;
                
                CSize Extent = pDC->GetTextExtent(strText);
                CPoint pt( rect.CenterPoint().x - Extent.cx/2, 
                rect.CenterPoint().y - Extent.cy/2 );

                if (state & ODS_SELECTED)
                        pt.Offset(1,1);

                int nMode = pDC->SetBkMode(TRANSPARENT);

                if (state & ODS_DISABLED)
                {
                        prevColor = pDC->SetTextColor(m_crDisabledFg);
                        pDC->DrawState(pt, Extent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
                }
                else if (m_bOverControl)
                {
                        prevColor = pDC->SetTextColor(m_crHotFg);
                        pDC->TextOut(pt.x, pt.y, strText);
                }
                else
                {
                        prevColor = pDC->SetTextColor(m_crFg);
                        pDC->TextOut(pt.x, pt.y, strText);
                }

                pDC->SetBkMode(nMode);
                pDC->SetTextColor(prevColor);
        }
}

void CColorButton::PreSubclassWindow() 
{
    CButton::PreSubclassWindow();
    ModifyStyle(0, BS_OWNERDRAW);
}

void CColorButton::OnMouseMove(UINT nFlags, CPoint point) 
{
        if (!m_bOverControl)
        {
                m_bOverControl = TRUE;
                Invalidate();
                SetTimer(m_nTimerID, m_iRolloverDelay, NULL);
        }
        CButton::OnMouseMove(nFlags, point);
}

void CColorButton::OnTimer(UINT nIDEvent) 
{
        CPoint p(GetMessagePos());
        ScreenToClient(&p);
        CRect rect;
        GetClientRect(rect);
        if (!rect.PtInRect(p))
        {
                m_bOverControl = FALSE;
                KillTimer(m_nTimerID);
                Invalidate();
        }
        CButton::OnTimer(nIDEvent);
}
