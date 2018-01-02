#include "stdafx.h"
#include "ColorControl.h"
#include "RGB.h"

CColorControl::CColorControl()
: m_pBrush(NULL),
m_pHotBrush(NULL)
{
        m_pBrush = new CBrush(RGB_WHITE);
        m_pHotBrush = new CBrush(RGB_WHITE);
        m_bOverControl = FALSE;
        m_nTimerID     = 1;
        m_iRolloverDelay = 10;
}

CColorControl::~CColorControl()
{
        delete m_pBrush;
        delete m_pHotBrush;
}

void CColorControl::SetDisabledColors( COLORREF DisabledFGColor, COLORREF DisabledBGColor )
{
	m_crDisabledFg = DisabledFGColor;
	m_crDisabledBg = DisabledBGColor;
}

void CColorControl::SetColors(const COLORREF FGColor, const COLORREF BGColor, const COLORREF HotFGColor, const COLORREF HotBGColor)
{
	m_crFg = FGColor;
	m_crBg = BGColor;
        m_crHotFg = HotFGColor;
        m_crHotBg = HotBGColor;
        delete m_pBrush;
        delete m_pHotBrush;
        m_pBrush = m_pHotBrush = 0;
        m_pBrush = new CBrush(BGColor);
        m_pHotBrush = new CBrush(HotBGColor);
}
