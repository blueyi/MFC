// thumbnailDlg.h : header file
//

#if !defined(AFX_THUMBNAILDLG_H__98C53A4C_3F9C_4588_B819_2CE493C4C690__INCLUDED_)
#define AFX_THUMBNAILDLG_H__98C53A4C_3F9C_4588_B819_2CE493C4C690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include	"ImageArea.h"
#include	<vector>

/////////////////////////////////////////////////////////////////////////////
// CThumbnailDlg dialog

class CThumbnailDlg : public CDialog
{
// Construction
public:
	CThumbnailDlg(CWnd* pParent = NULL);	// standard constructor

	void  DrawSelectedImage();	// draw the selected thumbnail image in full size

// Dialog Data
	//{{AFX_DATA(CThumbnailDlg)
	enum { IDD = IDD_THUMBNAIL_DIALOG };
	CListCtrl	m_ListThumbnail;
	CImageArea	m_ImageRect;
	CString	m_strImageDir;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbnailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON		m_hIcon;

	CImageList				m_ImageListThumb;		// image list holding the thumbnails
	std::vector<CString>	m_VectorImageNames;		// vector holding the image names
	int						m_nSelectedItem;

	BOOL  GetImageFileNames();	// gather the image file names
	void  DrawThumbnails();		// draw the thumbnails in list control

	// Generated message map functions
	//{{AFX_MSG(CThumbnailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnLoad();
	afx_msg void OnOK();
	afx_msg void OnClickListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListThumb(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBNAILDLG_H__98C53A4C_3F9C_4588_B819_2CE493C4C690__INCLUDED_)
