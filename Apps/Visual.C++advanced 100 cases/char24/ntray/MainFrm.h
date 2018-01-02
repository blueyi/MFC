#include "ntray.h"


class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	virtual ~CMainFrame();

protected:
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	DECLARE_DYNCREATE(CMainFrame)

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHappy();
	afx_msg void OnUpdateHappy(CCmdUI* pCmdUI);
	afx_msg void OnSad();
	afx_msg void OnUpdateSad(CCmdUI* pCmdUI);
	afx_msg void OnAnimated();
	afx_msg void OnUpdateAnimated(CCmdUI* pCmdUI);
	//}}AFX_MSG
  afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

  CTrayNotifyIcon m_TrayIcon;
  HICON m_hIcons[2];
  BOOL m_bHappy;
};

