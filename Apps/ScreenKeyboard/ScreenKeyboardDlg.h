// ScreenKeyboardDlg.h : 头文件
//

#pragma once
#include "KeyDefine.h"
#include "AfxTempl.h"

// CScreenKeyboardDlg 对话框
class CScreenKeyboardDlg : public CDialog
{
// 构造
public:
	CScreenKeyboardDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCREENKEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	HWND gFocus;
	int cCurrentKeyState;
	int pKeyWidth;   
	int pKeyHeight;
	CTypedPtrList<CPtrList, KEYDEF*> cKeys;
	BOOL bActive;
	CFont  m_TextFont;
	CBrush m_BTBkColor[64];

private:
	void ReleaseFocus();
	void AddKey(char pNormal,char pShifted,	int pWidth);
	void CalcWidthHeight();
	void DrawKey(CDC * dc, KEYDEF * key);
	void SendKey(KEYDEF * key);
	int  DescribeKeyState();
	void DrawKeyboard();
	void DoGradientFill(CDC *pDC, CRect* rect);
	void FillBkBrushColor();
	void FreeBkBrushColor();

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 计算按键的矩形区域
	void CalKeyRect(void);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
