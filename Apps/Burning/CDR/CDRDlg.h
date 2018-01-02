// CDRDlg.h : header file
//

#if !defined(AFX_CDRDLG_H__A6E875BC_AF13_459F_992F_7DA4BE93BD54__INCLUDED_)
#define AFX_CDRDLG_H__A6E875BC_AF13_459F_992F_7DA4BE93BD54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "hexeditctrl.h"
#include "scsi2.h"
#include "osta_udf.h"
#include "filedroplistctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCDRDlg dialog

class CCDRDlg : public CDialog
{
// Construction
public:
	CCDRDlg(CWnd* pParent = NULL);	// standard constructor
	~CCDRDlg();

// Dialog Data
	//{{AFX_DATA(CCDRDlg)
	enum { IDD = IDD_CDR_DIALOG };
	CFileDropListCtrl	m_fileList;
	CComboBox	m_driveCtrl;
	CString		m_str_offset;
	CString		m_str_length;
	CHexEdit	m_edit;
	BYTE		m_HA;
	BYTE		m_ID;
	BYTE		m_LUN;
	CString		m_fileName;
	int			m_track;
	BOOL		m_header;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMenu* m_menu;
	HICON m_hIcon;
	CString	m_result;
	SCSI2	m_bus;
	long	m_length;
	long	m_offset;
	DRIVEINFO info[64];
	CImageList m_ImageList;
	bool	m_upload;

	// Generated message map functions
	//{{AFX_MSG(CCDRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRead();
	afx_msg void OnEject();
	afx_msg void OnClose();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDeviceChange();
	afx_msg void OnPosChange();
	afx_msg void OnAtip();
	afx_msg void OnPma();
	afx_msg void OnToc();
	afx_msg void OnBusScan();
	afx_msg void OnInquiry();
	afx_msg void OnWriteParameters();
	afx_msg void OnBrowse();
	afx_msg void OnWriteFiles();
	afx_msg void OnFormatDisc();
	afx_msg void OnSetMode1();
	afx_msg void OnCloseSession();
	afx_msg void OnWriteAsTemplate();
	afx_msg void OnReadTrackInfo();
	afx_msg void OnReadDiskInfo();
	afx_msg void OnReserveTrack();
	afx_msg void OnSetMode2();
	afx_msg void OnSelectchangeCombo1();
	afx_msg void OnContent();
	afx_msg void OnSave();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDRDLG_H__A6E875BC_AF13_459F_992F_7DA4BE93BD54__INCLUDED_)
