/*******************************************

	MFTrafficButton

	Version:	1.0
	Date:		31.10.2001
	Author:		Michael Fatzi
	Mail:		Michael_Fatzi@hotmail.com
	Copyright 1996-1997, Keith Rule

	You may freely use or modify this code provided this
	Copyright is included in all derived versions.
	
	History: 10.2001 Startup

	Handy little button control to display current 
	nettraffic as graph in a button.

********************************************/

// NetTrafficButtonDlg.h : Header-Datei
//

#if !defined(AFX_NETTRAFFICBUTTONDLG_H__F1CE9C31_5EF8_4B96_8897_29C1FAE99A6E__INCLUDED_)
#define AFX_NETTRAFFICBUTTONDLG_H__F1CE9C31_5EF8_4B96_8897_29C1FAE99A6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MFTrafficButton.h"

/////////////////////////////////////////////////////////////////////////////
// CNetTrafficButtonDlg Dialogfeld

class CNetTrafficButtonDlg : public CDialog
{
// Konstruktion
public:
	CNetTrafficButtonDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CNetTrafficButtonDlg)
	enum { IDD = IDD_NETTRAFFICBUTTON_DIALOG };
	MFTrafficButton	m_cOutgoing;
	MFTrafficButton	m_cIncoming;
	MFTrafficButton	m_cTotalTraffic;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CNetTrafficButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CNetTrafficButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_NETTRAFFICBUTTONDLG_H__F1CE9C31_5EF8_4B96_8897_29C1FAE99A6E__INCLUDED_)
