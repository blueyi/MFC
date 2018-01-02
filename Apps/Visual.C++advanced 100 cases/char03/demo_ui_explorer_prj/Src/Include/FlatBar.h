////////////////////////////////////////////////////////////////
// CFlatToolBar 1997 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// This code compiles with Visual C++ 5.0 on Windows 95
//

#if !defined(FLATBAR_H_INCLUDED)
#define FLATBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Old commctrl.h compatibility *** Kirk Stowell
#if !defined (TB_SETEXTENDEDSTYLE)
#define TB_SETEXTENDEDSTYLE (WM_USER+84)
#endif

#if !defined (TB_SETHOTIMAGELIST)
#define TB_SETHOTIMAGELIST (WM_USER+52) 
#endif

#if !defined (TB_SETIMAGELIST)
#define TB_SETIMAGELIST (WM_USER+48)
#endif

#if !defined (TBSTYLE_TRANSPARENT)
#define TBSTYLE_TRANSPARENT 0x8000
#endif

#if !defined (TBSTYLE_AUTOSIZE)
#define TBSTYLE_AUTOSIZE 0x0010
#endif

#if !defined (TBSTYLE_EX_DRAWDDARROWS)
#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#endif

#if !defined (TBSTYLE_FLAT)
#define TBSTYLE_FLAT 0x0800
#endif

//////////////////
// "Flat" style tool bar. Use instead of CToolBar in your CMainFrame
// or other window to create a tool bar with the flat look.
//
// CFlatToolBar fixes the display bug described in the article. It also has
// overridden load functions that modify the style to TBSTYLE_FLAT. If you
// don't create your toolbar by loading it from a resource, you should call
// ModifyStyle(0, TBSTYLE_FLAT) yourself.
//

class CLASS_EXPORT CFlatToolBar : public CToolBar {

	DECLARE_DYNAMIC(CFlatToolBar)

////////////////////////////////////////////////////////////////
// FixTB code from August 98 article:
////////////////////////////////////////////////////////////////

public:
	CFlatToolBar();
	virtual ~CFlatToolBar();

	static int iVerComCtl32; // version of commctl32.dll (eg 471)

	// There is a bug in comctl32.dll, version 4.71+ that causes it to
	// draw vertical separators in addition to horizontal ones, when the
	// toolbar is vertical. Set this to FALSE to eliminate them--but then
	// you lose your dropdown arrows.
	//
	BOOL m_bShowDropdownArrowWhenVertical;

	CSize CalcLayout(DWORD nMode, int nLength = -1);
	CSize CalcSize(TBBUTTON* pData, int nCount);
	int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);
	void SizeToolBar(TBBUTTON* pData, int nCount, int nLength,
		BOOL bVert = FALSE);

	// MFC has versions of these are hidden--why?
	//
	void GetButton(int nIndex, TBBUTTON* pButton) const;
	void SetButton(int nIndex, TBBUTTON* pButton);

////////////////////////////////////////////////////////////////
// End FixTb code.
////////////////////////////////////////////////////////////////

public:
	BOOL LoadToolBar(LPCTSTR lpszResourceName);
	BOOL LoadToolBar(UINT nIDResource)
		{ return LoadToolBar(MAKEINTRESOURCE(nIDResource)); }

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatToolBar)
	public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	virtual CSize GetButtonSize(TBBUTTON* pData, int iButton);
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CFlatToolBar)
	afx_msg void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
	afx_msg void OnWindowPosChanged(LPWINDOWPOS lpWndPos);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////
// The following class was copied from BARTOOL.CPP in the MFC source.
// All I changed was SetCheck--PD.
//
class CFlatOrCoolBarCmdUI : public CCmdUI // class private to this file !
{
public: // re-implementations only
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};

#endif