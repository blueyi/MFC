// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTDLG_H__F07ACE1E_B032_43B3_A4DB_6978D504D146__INCLUDED_)
#define AFX_ABOUTDLG_H__F07ACE1E_B032_43B3_A4DB_6978D504D146__INCLUDED_

#include "../../Include/Titlebar.h"

class CAboutDlg : public CDialogImpl<CAboutDlg>,
		public FreshUI::Titlebar < CAboutDlg, FreshUI::WrittenInMidnight < FreshUI::SystemButton > >
{
public:
	enum { IDD = IDD_ABOUTBOX };

	typedef FreshUI::Titlebar < CAboutDlg, FreshUI::WrittenInMidnight < FreshUI::SystemButton > > baseClass;

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		CHAIN_MSG_MAP (baseClass)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow(GetParent());
		Init();
		return TRUE;
	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif // !defined(AFX_ABOUTDLG_H__F07ACE1E_B032_43B3_A4DB_6978D504D146__INCLUDED_)
