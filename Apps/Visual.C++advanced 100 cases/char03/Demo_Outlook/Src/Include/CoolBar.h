////////////////////////////////////////////////////////////////
// CCoolBar 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 5.0 on Windows 95

#if !defined(COOLBAR_H_INCLUDED)
#define COOLBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////
// CCoolBar encapsulates IE 4.0 common coolbar for MFC.
//
class CLASS_EXPORT CCoolBar : public CControlBar {
protected:
	DECLARE_DYNAMIC(CCoolBar)

public:
	CCoolBar();
	virtual ~CCoolBar();

	BOOL Create(CWnd* pParentWnd, DWORD dwStyle,
		DWORD dwAfxBarStyle = CBRS_ALIGN_TOP,
		UINT nID = AFX_IDW_TOOLBAR);

	// Message wrappers
	BOOL GetBarInfo(LPREBARINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_GETBARINFO, 0, (LPARAM)lp); }
	BOOL SetBarInfo(LPREBARINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_SETBARINFO, 0, (LPARAM)lp); }
	BOOL GetBandInfo(int iBand, LPREBARBANDINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_GETBANDINFO, iBand, (LPARAM)lp); }
	BOOL SetBandInfo(int iBand, LPREBARBANDINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_SETBANDINFO, iBand, (LPARAM)lp); }
	BOOL InsertBand(int iWhere, LPREBARBANDINFO lp)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_INSERTBAND, (WPARAM)iWhere, (LPARAM)lp); }
	BOOL DeleteBand(int nWhich)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(RB_INSERTBAND, (WPARAM)nWhich); }
	int GetBandCount()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(RB_GETBANDCOUNT); }
	int GetRowCount()
		{ ASSERT(::IsWindow(m_hWnd));
	     return (int)SendMessage(RB_GETROWCOUNT); }
	int GetRowHeight(int nWhich)
		{ ASSERT(::IsWindow(m_hWnd));
	     return (int)SendMessage(RB_GETROWHEIGHT, (WPARAM)nWhich); }

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCoolBar)
	protected:
	// new virtual functions you must/can override
	virtual BOOL OnCreateBands() = 0; // return -1 if failed
	virtual void OnHeightChange(const CRect& rcNew);
	// CControlBar Overrides
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    //}}AFX_VIRTUAL

    // Generated message map functions
protected:
    //{{AFX_MSG(CCoolBar)
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPaint();
	afx_msg void OnHeigtChange(NMHDR* pNMHDR, LRESULT* pRes);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////
// Programmer-friendly REBARBANDINFO initializes itself
//
class CLASS_EXPORT CRebarBandInfo : public REBARBANDINFO {
public:
	CRebarBandInfo() {
		memset(this, 0, sizeof(REBARBANDINFO));
		cbSize = sizeof(REBARBANDINFO);

		// *** Kirk Stowell
		fMask   = RBBIM_STYLE|RBBIM_CHILD|RBBIM_CHILDSIZE|RBBIM_BACKGROUND|RBBIM_COLORS;
		fStyle  = RBBS_FIXEDBMP;
		clrFore = GetSysColor(COLOR_BTNTEXT);
		clrBack	= GetSysColor(COLOR_BTNFACE);
	}
};

#endif