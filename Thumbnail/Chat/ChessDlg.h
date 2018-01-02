
#pragma once
#include "afxwin.h"
#include "TcpChessSocket.h"
#include "WinXPButtonST.h"
// CChessDlg 对话框
#define WAS_ACCEPT WM_USER+101
class Step

{

public:
	Step():x(0),y(0),side(0),deep(0)
	{

	}
	int x; //x,y表示在数组中的位置

	int y;

	int side; //side表示下子方
	int deep ;

};
class GameStatus
{
public:
	GameStatus():deep(0),score(0),is_machine(false),ab(0)
	{

	}
	
	int deep;
	int score;
	bool is_machine;
	int ab;
	Step st;//当前走步
	int  fivearray[20][20];

};

class CChessDlg : public CDialog
{
	DECLARE_DYNAMIC(CChessDlg)

public:
	CChessDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChessDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	void DrawGrid();
	void DrawChess(CPoint point);
	void DrawChess(int x,int y,bool is_current);
	void DrawAllChess();
	void OnReceive();
	bool IsSuccess();
	void SocketClose();
	int LeftRight(int i, int j,int side);
	int UpDown(int i, int j,int side);
	int LupToRdown(int i, int j,int side);
	int RuptoLdown(int i, int j,int side);
	void GetCurrentScore( GameStatus &board_situation);
	int LeftToRight_Status(int i, int j ,int arrray[][20]);
	int UpToDown_Status(int i, int j ,int arrray[][20]);
	int LeftUpToRightDown_Status(int i, int j ,int arrray[][20]);
	int LeftDownToRightUp_Status(int i, int j ,int array[][20]);
	int  MachineSearchGoodPlace(Step & st);
	int  MachineSearchBadPlace(Step &st);
	int  SearchMaxValue(Step &st,int array[][20]);
	int DeepSearch(GameStatus ts,Step &st,bool machine,int value);
	int SearchValue(int array[][20],Step &st,bool machine);
	int  Fivearray[20][20];
	int step_x;
	int step_y;
	Step m_currentstep;
	Step oldstep;
	bool is_server;
	bool is_myturn;
	bool is_connect;
	bool set_netflag;
	bool m_and_p_flag;
	bool flag;
	CList<Step,Step&>StepList;
	CStatic m_smain;
	CTcpChessSocket m_socket;
	CTcpChessSocket m_con_socket;
	afx_msg void OnRegret();
	afx_msg void OnNet();
	afx_msg LRESULT OnMyMessage(WPARAM wParam,LPARAM lParam);
protected:
//	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnSendMessage();
	CEdit m_edit;
	CListBox m_listbox;
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnClose();
	CWinXPButtonST bt1;
	CWinXPButtonST bt2;
	CWinXPButtonST bt3;
	CWinXPButtonST bt4;
	CWinXPButtonST bt5;
	CWinXPButtonST bt7;
	afx_msg void OnMachineAndPeson();
	CComboBox m_combox;
	afx_msg void OnTimer(UINT nIDEvent);
};
