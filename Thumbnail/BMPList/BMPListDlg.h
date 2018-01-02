// BMPListDlg.h : header file
//

#pragma once
#include "afxcmn.h"

// Data object handling class
class CMyDataInfo : public CObject
{
// Construction/Destruction
public:
	CMyDataInfo() {};
	~CMyDataInfo() {};
// Attributes
public:
	CString m_csColumn1;
	CString m_csColumn2;
	CString m_csColumn3;
	CString m_csColumn4;
	CString m_csImage; // BMP to show

// Implementation
};

class CMyDataArray : public CObArray
{
// Construction/Destruction
public:
	CMyDataArray() {};
	~CMyDataArray() {
		for(int i = 0; i < GetSize(); ++ i)
			delete GetAt(i);
		RemoveAll();
	};

// Attributes
public:
};

// CBMPListDlg dialog
class CBMPListDlg : public CDialog
{
// Construction
public:
	CBMPListDlg(CWnd* pParent = NULL);	// standard constructor
	~CBMPListDlg(){m_imageList.DeleteImageList();};
	
// Dialog Data
	enum { IDD = IDD_BMPLIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CImageList	m_imageList;
	void InsertItems();
	int m_nItems;
	CMyDataArray m_MyDataArray;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void GetDispInfo(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_cList;
};
