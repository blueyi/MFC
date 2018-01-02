/////////////////////////////////////////////////////////////////////////////
// InfoDlg.cpp : implementation file
//
// Operationg system checking.
// All rights reserved.
//
// Written by Naveen Kohli (naveen@a3ds.com)
// Version 1.0
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc. to
//    naveen@a3ds.com
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OSDetect.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InfoDlg dialog


InfoDlg::InfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(InfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void InfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InfoDlg, CDialog)
	//{{AFX_MSG_MAP(InfoDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InfoDlg message handlers

BOOL InfoDlg::OnInitDialog() 
{
	
	m_InfoStatic.SubclassDlgItem (IDC_OS_STATIC, this);
	m_MinorVerStatic.SubclassDlgItem (IDC_BUILD_STATIC, this);
	m_ServPackStatic.SubclassDlgItem (IDC_SPAK_STATIC, this);
	m_BuildNoStatic.SubclassDlgItem (IDC_BUILDNO_STATIC, this);

	CDialog::OnInitDialog();

	CheckOSVersion ();
	
	m_InfoStatic.SetWindowText (m_stInfo);
	m_MinorVerStatic.SetWindowText (m_stMinorVer);
	m_ServPackStatic.SetWindowText (m_stServPack);
	m_BuildNoStatic.SetWindowText (m_stBuildNumber);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void InfoDlg::CheckOSVersion ()
{
	int stat = 0;
	char buffer[20];
	TCHAR data [64];
	DWORD dataSize;
	DWORD win95Info;
	OSVERSIONINFO versionInfo;
	HKEY hKey;
	LONG result;

	// set the size of OSVERSIONINFO, before calling the function

	versionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);

	// Get the version information

	if (!::GetVersionEx (&versionInfo)) {
		m_stInfo = (_T ("Not able to get OS information"));
		return;
	}

	// If NT ,then check if its server or workstation.

	if (versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) {
		// there is no direct way of telling from ODVERSIONINFO thats is it 
		// workstation or server version.
		// There we need to check in the registry.

		m_stInfo =  (_T ("Windows NT"));

		dataSize = sizeof (data);
		
		result = ::RegOpenKeyEx (HKEY_LOCAL_MACHINE,
			"System\\CurrentControlSet\\Control\\ProductOptions",
			0, KEY_QUERY_VALUE, &hKey);

		// If there is error in opening the registry key, return

		if (result != ERROR_SUCCESS) {
			SetLastError (result);
			return;
		}

		result = ::RegQueryValueEx (hKey, _T("ProductType"), NULL, NULL,
			(LPBYTE) data, &dataSize);

		// Make sure to close the reg key

		RegCloseKey (hKey);

		if (result != ERROR_SUCCESS) {
			SetLastError (result);
			return;
		}

		// Check what string has been returned

		if (lstrcmpi (data, "WinNT") == 0) {
			m_stInfo = _T ("Windows NT Workstation");
		}
		else if (lstrcmpi (data, "ServerNT") == 0) {
			m_stInfo = _T ("Windows NT Server");
		}
		else {
			m_stInfo = _T ("Windows NT Server - Domain Controller");
		}

		// Check the version number

		if (versionInfo.dwMajorVersion == 3 || versionInfo.dwMinorVersion == 51) {
			m_stMinorVer = _T ("3.51");
		}
		else {
			m_stMinorVer = _T ("4.0");
		}

		// Get the build number.

		_itoa( versionInfo.dwBuildNumber, buffer, 10 );
		m_stBuildNumber = CString (buffer);
	}
	else if (versionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
		m_stInfo = _T ("Windows 95");

		if ((versionInfo.dwMajorVersion > 4) || ((versionInfo.dwMajorVersion == 4)
			&& (versionInfo.dwMinorVersion > 0))) {
			m_stInfo = _T ("Windows 98");
		}

		// For win95, build number is low order word
		
		win95Info = (DWORD)(LOBYTE(LOWORD(versionInfo.dwBuildNumber)));

		// Get the build number.

		_itoa( win95Info, buffer, 10 );
		m_stBuildNumber = CString (buffer);
	}
	else {
		m_stInfo = _T ("Windows 3.1");
	}

	// Get service pack information.

	m_stServPack = CString (versionInfo.szCSDVersion);
	m_stServPack.FreeExtra ();
}
