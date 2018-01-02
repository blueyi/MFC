// TrayWnd.h : header file
//

#define WM_MY_TRAY_NOTIFICATION WM_USER+0

/////////////////////////////////////////////////////////////////////////////
// CTrayWnd window

class CTrayWnd : public CFrameWnd
{
public:
	CTrayWnd();
	~CTrayWnd();

protected:
	CPropertySheet* m_pSheet;
	NOTIFYICONDATA m_trayData;

	BOOL IsValidHotKey();
	afx_msg LRESULT OnTrayNotification(WPARAM uID, LPARAM lEvent);

	//{{AFX_VIRTUAL(CTrayWnd)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTrayWnd)
	afx_msg void OnTrayExit();
	afx_msg void OnTrayChangeSettings();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTrayActivate();
	afx_msg void OnUpdateTrayActivate(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_DYNAMIC(CTrayWnd)
	DECLARE_MESSAGE_MAP()
};
