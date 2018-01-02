// ThumbNailDlg.h : header file
//

#if !defined(AFX_THUMBNAILDLG_H__75EDA145_4781_4857_A499_0FF0E7EF3085__INCLUDED_)
#define AFX_THUMBNAILDLG_H__75EDA145_4781_4857_A499_0FF0E7EF3085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CThumbNailDlg dialog

#include "ThumbNailControl.h"

class CThumbNailDlg : public CDialog
  {
  private:
    CThumbNailControl	m_cThumbFrame;

  // Construction
  public:
	  CThumbNailDlg(CWnd* pParent = NULL);	// standard constructor

  // Dialog Data
	  //{{AFX_DATA(CThumbNailDlg)
	enum { IDD = IDD_THUMBNAIL_DIALOG };
	CString	m_sMsg;
	//}}AFX_DATA

	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CThumbNailDlg)
	  protected:
	  virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	  //}}AFX_VIRTUAL

  // Implementation
  protected:
	  HICON m_hIcon;

	  // Generated message map functions
	  //{{AFX_MSG(CThumbNailDlg)
	  virtual BOOL OnInitDialog();
	  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	  afx_msg void OnPaint();
	  afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
    afx_msg LRESULT OnTnbLClicked( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnTnbRClicked( WPARAM wParam, LPARAM lParam );
	  DECLARE_MESSAGE_MAP()
  };

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBNAILDLG_H__75EDA145_4781_4857_A499_0FF0E7EF3085__INCLUDED_)
