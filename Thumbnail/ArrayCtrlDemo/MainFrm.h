/////////////////////////////////////////////////////////////////////////////
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D24AE5EA_D8A7_4C21_9423_B067F1208627__INCLUDED_)
#define AFX_MAINFRM_H__D24AE5EA_D8A7_4C21_9423_B067F1208627__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjInfo.h"

#define	TXT_SIZE		MAX_PATH
#define	TAB_ITEMS		10


/////////////////////////////////////////////////////////////////////////////
// CMainFrame class

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual	~CMainFrame();

	void		ResizeChildren	();
	void		ViewImage		(LPCTSTR lpszImageName);
	void		ViewColor		(CClrInfo* pClrInfo);
	void		SetActiveCtrl	(CArrayCtrl* pCtrl) {m_pActCtrl = pCtrl;}

	void		SplashToControl	(LPCTSTR lpszImageName);
	void		BuildFileList	(LPCTSTR lpszPath);
	CObjInfo*	BuildThumb		(LPCTSTR lpszPath, LPCTSTR lpszFile, DWORD dwFormat);
	void		RebuildThumb	(int nWidth, int nHeight);

	void		RenderInvalid	(CDC* pDC);
	void		RenderIcon		(CDC* pDC, HICON hIcon, int nWidth, int nHeight);
	void		RenderText		(CDC* pDC, LPCTSTR lpszText, int nWidth, int nHeight);
	void		RenderImage		(CDC* pDC, CBitmap* pBitmap, int nWidth, int nHeight);
	void		BuildControl	(int nId);
	void		ReflectChange	(CRect* pRect);
	void		ReflectChange	(int nOper, COLORREF crColor);
	void		ReflectChange	(int nW, int nH);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CStatusBar		m_wndStatusBar;				// status bar (unused)
	CToolBar		m_wndToolBar;				// toolbar (unused)
	CString			m_pShowClass;				// image show windows class name
	CBrush*			m_pBrush;					// main frame background brush
	CBitmap*		m_pNullImage;				// null image mark place
	CFont*			m_pFont;					// font for text drawing
	COLORREF		m_crBackGnd;				// background color
	HCURSOR			m_HandCur;					// cursor
	CMenu			m_CtrlMenu;					// control menu
	CMenu			m_ItemMenu;					// item menu
	CBitmap*		m_pSplashImage;				// image splashed on control 3

	CTabCtrl*		m_pTabCtrl;					// Tab control for color table

	CArrayCtrl*		m_pActCtrl;					// active array control
	CArrayCtrl*		m_pACtrl1;					// array control 1 (fixed, directory objects viewer)
	CArrayCtrl*		m_pACtrl2;					// array control 2 (right resizeable, directory objects viewer)
	CArrayCtrl*		m_pACtrl3;					// array control 3 (bottom resizeable, image viewer)

	int				m_nTabSel;					// tab control selected item
	CArrayCtrl*		m_pACtrlVect[TAB_ITEMS];	// array control 4 (right and bottom resizeable, color table viewer)

public:
	int				m_fResizing;				// resizing indicator

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSetFocus(CWnd *pOldWnd);
	afx_msg void	OnDestroy();
	afx_msg LRESULT	OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnExitSizeMove(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg void	OnNotifyDrawItem(UINT nCtrlId, NMHDR * pNotifyStruct, LRESULT* result);
	afx_msg void	OnNotifyLButtonDown(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void	OnNotifyRButtonDown(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void	OnNotifyLButtonDblClk(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg	void	OnNotifyGetText(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg	void	OnNotifyDelete(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void	OnSplashLButtonDown(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg	void	OnNotifyDrawColor(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg	void	OnNotifyGetInfo(UINT nCtrlId, NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg	void	OnTabSelItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg	void	OnSplashDrawItem(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void	OnItemCopy();
	afx_msg void	OnItemRemove();
	afx_msg void	OnItemSplash();
	afx_msg void	OnMainBkColor();
	afx_msg void	OnCtrlBkColor();
	afx_msg void	OnCtrlGlColor();
	afx_msg void	OnCtrlToggle();
	afx_msg void	OnCtrlDir();
	afx_msg void	OnChangeSize();
	afx_msg void	OnDeleteItems();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D24AE5EA_D8A7_4C21_9423_B067F1208627__INCLUDED_)
