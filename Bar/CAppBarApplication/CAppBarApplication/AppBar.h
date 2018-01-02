#pragma once


// CAppBar dialog
#define CX_DEFWIDTH 	60
#define CY_DEFHEIGHT 	40


#define APPBAR_LEFT		0
#define APPBAR_RIGHT	1

typedef struct tagOPTIONS
{

	BOOL fHiding;
	UINT uSide;
	DWORD cxWidth;
	DWORD cyHeight;
} OPTIONS, *POPTIONS;

#define APPBAR_CALLBACK     WM_USER + 1010

class CAppBar : public CDialog
{
	DECLARE_DYNAMIC(CAppBar)

public:
	CAppBar(UINT ID, CWnd* pParent = NULL);   
	virtual ~CAppBar();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();

	afx_msg LONG OnHotKey(WPARAM wParam,LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	

	inline BOOL IsRegistered () {return m_bAppRegistered;}
	BOOL SetAppbarData (POPTIONS pOptions);
	POPTIONS GetAppbarData ();		
	BOOL SetSide (UINT uSide);
	BOOL UnRegister ();
	BOOL Register ();
	LONG AppBarCallback (WPARAM wParam, LPARAM lParam);
	void QuerySetPos (UINT uEdge, LPRECT lprc, PAPPBARDATA pabd, BOOL bMove);
	void QueryPos (LPRECT lprc);	
	void FefreshDesktop();
	void MyRegisterHotKey(UINT uNum1, UINT uNum2);
	void UnMyRegisterHotKey();

public:
	void getTransparentHwnd(HWND *hwnd);

private:
	POPTIONS m_pOptions;	
	BOOL m_bAppRegistered;
	BOOL m_bHidden;
	BOOL m_bMoving;
	BOOL m_bLButionDown;
	BOOL m_bFirstMouseMove;
	CPoint m_ptLast;
	CRect m_rcLast;
	CRectTracker m_RectTracker;
	CPoint m_oldestPoint;
	int m_nHotKeyID;
	HWND m_transparent_hwnd;
	CRect m_rcAppBar;
	UINT m_uOriginSide; //用来控制刷新
public:
	afx_msg void OnClose();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
