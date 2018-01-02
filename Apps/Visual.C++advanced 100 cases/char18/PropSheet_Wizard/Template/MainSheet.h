// MainSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainSheet property sheet

$$BEGINLOOP(NUM_PAGES)
#include "$$PAGE_FILE$$.h"
$$ENDLOOP	//NUM_PAGES

$$IF(SEND_TO_TASKBAR)
const UINT WM_ICONNOTIFY = ::RegisterWindowMessage (_T ("WM_ICONNOTIFY"));
$$ENDIF	//SEND_TO_TASKBAR

class CMainSheet : public CPropertySheet
{
// Construction
public:
	CMainSheet();

// Attributes
public:
$$BEGINLOOP(NUM_PAGES)
	$$PAGE_CLASS$$	$$PAGE_VAR$$;
$$ENDLOOP	//NUM_PAGES

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainSheet)
	protected:
	virtual void PostNcDestroy();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainSheet();
$$IF(TOOLTIPS)
	virtual BOOL PreTranslateMessage (MSG* pMsg);
$$ENDIF	//TOOLTIPS

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainSheet)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
$$IF(ABOUT_BOX)
	afx_msg void OnAboutbox();
$$ENDIF	//ABOUT_BOX
$$IF(SEND_TO_TASKBAR)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnIconShutdown();
	afx_msg void OnIconRestore();
$$ENDIF	//SEND_TO_TASKBAR
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
$$IF(BITMAP_PAGES)
	CImageList m_imgTabBmps;
$$ENDIF	//BITMAP_PAGES
	HICON m_hIcon;
$$IF(TOOLTIPS)
protected:
	CToolTipCtrl m_tooltip;
$$ENDIF	//TOOLTIPS
};

/////////////////////////////////////////////////////////////////////////////
