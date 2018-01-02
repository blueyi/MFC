// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MyListCtrl.h"
#include "MyScrollBar.h"

class CMainDlg : public CDialogImpl<CMainDlg>
{

public:

	///
	/// Dialog resource
	///
	enum { IDD = IDD_MAINDLG };


	///
	/// Message map
	/// 
	BEGIN_MSG_MAP( CMainDlg )

		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
		COMMAND_ID_HANDLER( IDOK, OnOK )
		COMMAND_ID_HANDLER( IDCANCEL, OnCancel )

		COMMAND_ID_HANDLER( IDC_CUSTOM, OnCustom )
		COMMAND_ID_HANDLER( IDC_STANDARD, OnStandard )

		MESSAGE_HANDLER( WM_DESTROY, OnDestroy )
		MESSAGE_HANDLER( WM_CTLCOLORDLG, OnCtlColor )
		MESSAGE_HANDLER( WM_CTLCOLORSCROLLBAR, OnCtlColor )
		MESSAGE_HANDLER( WM_CTLCOLORSTATIC, OnCtlColor )

		MESSAGE_HANDLER( WM_VSCROLL, OnVScroll )

		REFLECT_NOTIFICATIONS()

	END_MSG_MAP()

	///
	/// Message handlers
	///

	LRESULT OnInitDialog
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnAppAbout
		(
			WORD wNotifyCode, 
			WORD wID, 
			HWND hWndCtl, 
			BOOL& bHandled
		);


	LRESULT OnOK
		(
			WORD wNotifyCode, 
			WORD wID, 
			HWND hWndCtl, 
			BOOL& bHandled
		);


	LRESULT OnCancel
		(
			WORD wNotifyCode, 
			WORD wID, 
			HWND hWndCtl, 
			BOOL& bHandled
		);


	LRESULT OnCustom
		(
			WORD wNotifyCode, 
			WORD wID, 
			HWND hWndCtl, 
			BOOL& bHandled
		);


	LRESULT OnStandard
		(
			WORD wNotifyCode, 
			WORD wID, 
			HWND hWndCtl, 
			BOOL& bHandled
		);


	LRESULT OnDestroy
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnCtlColor
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnVScroll
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);

	///
	/// Methods
	///

private:

	HBRUSH GetBkBrush( const CRect& rect );

	///
	/// Members 
	///

private:

	CBitmap m_Back;
	CBrush m_BackBrush;

	CMyListCtrl m_ListCtrl;
	CBrush m_ListBrush;

	CMyScrollbar m_Scrollbar;
	CBrush m_ScrollbarBrush;

	CBrush m_RadioCustomBrush;
	CBrush m_RadioStandardBrush;
};
