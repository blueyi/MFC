/////////////////////////////////////////////////////////////////////////////
// CHardwareInfoDlg.h : header file
//
// Hardware information checking function
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

#if !defined(AFX_HARDWAREINFODLG_H__17BDCA86_50FA_11D2_8B77_000000000000__INCLUDED_)
#define AFX_HARDWAREINFODLG_H__17BDCA86_50FA_11D2_8B77_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHardwareInfoDlg dialog

class CHardwareInfoDlg : public CDialog
{
// Construction
public:
	CHardwareInfoDlg(CWnd* pParent = NULL);	// standard constructor
	bool GetMouseInfo ();
	bool GetProcessorInfo ();

// Dialog Data
	//{{AFX_DATA(CHardwareInfoDlg)
	enum { IDD = IDD_HARDWAREINFO_DIALOG };
	CStatic	m_SpeedStatic;
	CStatic	m_SwappedStatic;
	CStatic	m_MouseStatic;
	CStatic	m_ArchStatic;
	CStatic	m_ProcessorTypeStatic;
	CStatic	m_ProRevStatic;
	CStatic	m_MaskStatic;
	CStatic	m_ProLevelStatic;
	CStatic	m_PageSzStatic;
	CStatic	m_OemIdStatic;
	CStatic	m_NumProcStatic;
	CStatic	m_MinAdStatic;
	CStatic	m_MaxAdStatic;
	CString	m_stMaxAddress;
	CString	m_stNumProcessors;
	CString	m_stOemId;
	CString	m_stMinAdress;
	CString	m_stPageSize;
	CString	m_stProcessorLevel;
	CString	m_stMask;
	CString	m_stProRevision;
	CString	m_stProcessorType;
	CString	m_stArchitecture;
	CString	m_stMouse;
	CString	m_stButtonsSwapped;
	CString	m_stMouseSpeed;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHardwareInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHardwareInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HARDWAREINFODLG_H__17BDCA86_50FA_11D2_8B77_000000000000__INCLUDED_)
