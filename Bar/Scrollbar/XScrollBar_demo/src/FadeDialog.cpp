// FadeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FadeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED	0x00080000
#endif
#ifndef LWA_ALPHA
#define LWA_ALPHA		0x00000002
#endif

typedef BOOL(WINAPI *lpfnSetLayeredWindowAttributes)(HWND, COLORREF, BYTE, DWORD);

static lpfnSetLayeredWindowAttributes g_pfnSetLayeredWindowAttributes = NULL;  

//=============================================================================
BEGIN_MESSAGE_MAP(CFadeDialog, CDialog)
//=============================================================================
	//{{AFX_MSG_MAP(CFadeDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//=============================================================================
CFadeDialog::CFadeDialog(UINT nId, CWnd* pParent /*=NULL*/)
//=============================================================================
  : CDialog(nId, pParent),
	m_nTransparency(0),
	m_nStep(3)
{
	//{{AFX_DATA_INIT(CFadeDialog)
	//}}AFX_DATA_INIT

	HMODULE hDLL = LoadLibrary(_T("USER32.DLL")); 
	g_pfnSetLayeredWindowAttributes = 
		(lpfnSetLayeredWindowAttributes) GetProcAddress(hDLL,"SetLayeredWindowAttributes");
}

//=============================================================================
BOOL CFadeDialog::OnInitDialog() 
//=============================================================================
{
	CDialog::OnInitDialog();
	
	if (g_pfnSetLayeredWindowAttributes)
	{
		SetWindowLong(m_hWnd, GWL_EXSTYLE, 
			GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	
		SetTimer(1, 10, NULL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//=============================================================================
void CFadeDialog::OnTimer(UINT nIDEvent) 
//=============================================================================
{
	if (g_pfnSetLayeredWindowAttributes)
	{
		g_pfnSetLayeredWindowAttributes(m_hWnd, 0, 
			(BYTE)m_nTransparency, LWA_ALPHA);

		(m_nTransparency > (255-m_nStep)) ? KillTimer(nIDEvent) 
										  : m_nTransparency += m_nStep;	
	}
	else
	{
		KillTimer(nIDEvent);
	}
	
	CDialog::OnTimer(nIDEvent);
}
