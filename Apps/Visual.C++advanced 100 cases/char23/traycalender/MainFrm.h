// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
// Operations
public:
	CMainFrame();

	DECLARE_DYNCREATE(CMainFrame)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Shutdown();
	void SetOptions();
	void CheckDate();
	BOOL StartIcon(HICON hIcon);

	void Shuffle();
	void KillShuffleTimer();
	void KillDateCheckTimer();
	void StartShuffleTimer();
	void StartCheckDateTimer();
    void GetDateCheckTime();
    COleDateTimeSpan GetTimeTillDateCheck();

// Attributes
protected:
	CSystemTray m_TrayIcon;
	CMenu m_Menu;					// popup menu
	UINT  m_DateCheckTimerID;		// Timer ID for periodic date check recieved from "SetTimer"
	UINT  m_ShuffleTimerID;			// Timer ID for initial reshuffle
	BOOL  m_bInitialShuffleDone;	// Shuffled icon yet?
    COleDateTime m_DateCheckTime;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTimeChange();
	//}}AFX_MSG
	afx_msg LONG OnTrayNotification(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
