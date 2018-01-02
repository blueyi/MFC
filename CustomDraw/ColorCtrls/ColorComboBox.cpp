#include "stdafx.h"
#include "ColorComboBox.h"
#include "RGB.h"

CColorComboBox::CColorComboBox()
{
}

CColorComboBox::~CColorComboBox()
{
}


BEGIN_MESSAGE_MAP(CColorComboBox, CComboBox)
	//{{AFX_MSG_MAP(CColorComboBox)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HBRUSH CColorComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	if( nCtlColor == CTLCOLOR_LISTBOX || nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX )
        {
                if (m_bOverControl)
                {
                        pDC->SetTextColor(m_crHotFg);
                        pDC->SetBkColor(m_crHotBg);
                        hbr = *m_pHotBrush;
                }
                else
                {
                        pDC->SetTextColor(m_crFg);
                        pDC->SetBkColor(m_crBg);
                        hbr = *m_pBrush;
                }
        }
	return hbr;
}

BOOL CColorComboBox::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
        if (message != WM_CTLCOLOREDIT)
        {
                 return CComboBox::OnChildNotify(message,wParam,lParam,pLResult);
        }
        HDC hdcChild = (HDC)wParam;
        if( m_bOverControl )
        {
                SetTextColor(hdcChild, m_crHotFg);
                SetBkColor(hdcChild, m_crHotBg);
                *pLResult = (LRESULT)(m_pHotBrush->GetSafeHandle());
        }
        else
        {
                SetTextColor(hdcChild, m_crFg);
                SetBkColor(hdcChild, m_crBg);
                *pLResult = (LRESULT)(m_pBrush->GetSafeHandle());
        }
        return TRUE;
}

void CColorComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
        if (!m_bOverControl)
        {
                m_bOverControl = TRUE;
                Invalidate();
                SetTimer(m_nTimerID, m_iRolloverDelay, NULL);
        }
	CComboBox::OnMouseMove(nFlags, point);
}

void CColorComboBox::OnTimer(UINT nIDEvent) 
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
	CComboBox::OnTimer(nIDEvent);
}
