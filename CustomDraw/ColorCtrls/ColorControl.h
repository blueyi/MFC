#ifndef _COLORCONTROL_H_
#define _COLORCONTROL_H_

class CColorControl  
{

public:

        CColorControl();
	virtual ~CColorControl();

	void SetColors(const COLORREF FGColor, const COLORREF BGColor, const COLORREF HotFGColor, const COLORREF HotBGColor);
	void SetDisabledColors( const COLORREF DisabledFGColor, const COLORREF DisabledBGColor );
	void SetBgColor(COLORREF cr) { m_crBg = cr; }
	void SetFgColor(COLORREF cr) { m_crFg = cr; }
	void SetHotBgColor(COLORREF cr) { m_crHotBg = cr; }
	void SetHotFgColor(COLORREF cr) { m_crHotFg = cr; }
	void SetDisabledFgColor(COLORREF cr) { m_crDisabledFg = cr; }
	void SetDisabledBgColor(COLORREF cr) { m_crDisabledBg = cr; }
	void SetRolloverDelay( UINT mSeconds ) { m_iRolloverDelay = mSeconds; }

protected:

        COLORREF m_crFg, m_crBg, m_crDisabledFg, m_crDisabledBg, m_crHotFg, m_crHotBg;
	UINT m_nTimerID, m_iRolloverDelay;
        BOOL m_bOverControl;
        CBrush* m_pBrush;
        CBrush* m_pHotBrush;

};

#endif
