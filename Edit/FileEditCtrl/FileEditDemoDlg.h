// FileEditDemoDlg.h : header file
//

#if !defined(AFX_FILEEDITDEMODLG_H__C9C86F86_5803_11D5_B625_A6E8A2E11D22__INCLUDED_)
#define AFX_FILEEDITDEMODLG_H__C9C86F86_5803_11D5_B625_A6E8A2E11D22__INCLUDED_

#include "PJA_Icon.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileEditCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDumpDialog dialog

class CDumpDialog : public CDialog
{
// Construction
public:
    CDumpDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDumpDialog)
	enum { IDD = IDD_DIALOG1 };
	CStatic	m_static;
    CListBox    m_List;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDumpDialog)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDumpDialog)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CFileEditDemoDlg dialog

class CFileEditDemoDlg : public CDialog
{
// Construction
public:
    LPTSTR pBuffer;
    CFileEditDemoDlg(CWnd* pParent = NULL); // standard constructor
    ~CFileEditDemoDlg();

// Dialog Data
    //{{AFX_DATA(CFileEditDemoDlg)
	enum { IDD = IDD_FILEEDITDEMO_DIALOG };
	CButton	m_gray;
	CButton	m_flat;
	CSpinButtonCtrl	m_spin;
	CButton	m_setwidth;
	CEdit	m_butwidth;
	CButton	m_transparent;
	CButton	m_stretch;
	CButton	m_icon;
	CButton	m_image;
	CButton	m_bitmap;
    CButton m_noderef;
    CButton m_wild;
    CButton m_validate;
    CButton m_left;
    CFileEditCtrl   m_fileeditctrl;
    CButton m_SetDir;
    CButton m_dump;
    CButton m_multi;
    CButton m_fold;
    CButton m_disable;
    CStatic m_stattext;
    CButton m_file;
    CEdit   m_editclitip;
    CButton m_drag;
    CButton m_clitip;
    CButton m_buttip;
    CButton m_browse;
    CButton m_Add;
    int     m_styles;
    int     m_flags;
	int		m_nicon;
	//}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CFileEditDemoDlg)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    void OnPreBrowse(NMHDR* pNMHDR, LRESULT* pResult);
    void OnPostBrowse(NMHDR* pNMHDR, LRESULT* pResult);
    void OnDrop(NMHDR* pNMHDR, LRESULT* pResult);
    BOOL OnToolTipText (UINT, NMHDR *pNMHDR, LRESULT*);
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CFileEditDemoDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnAdd();
    afx_msg void OnButtip();
    afx_msg void OnClitip();
    afx_msg void OnDisable();
    afx_msg void OnDrag();
    afx_msg void OnChangeEdit2();
    afx_msg void OnFile();
    afx_msg void OnFold();
    afx_msg void OnNormal();
    afx_msg void OnRead();
    afx_msg void OnMulti();
    afx_msg void OnDump();
    afx_msg void OnLeft();
    afx_msg void OnValidate();
    afx_msg void OnBrowse();
    afx_msg void OnWild();
    afx_msg void OnNoderef();
	afx_msg void OnImage();
	afx_msg void OnBitmap();
	afx_msg void OnMyIcon();
	afx_msg void OnStretch();
	afx_msg void OnTransparent();
	afx_msg void OnSetbuttonwidth();
	afx_msg void OnChangeEdit3();
	afx_msg void OnFlat();
	afx_msg void OnGray();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEEDITDEMODLG_H__C9C86F86_5803_11D5_B625_A6E8A2E11D22__INCLUDED_)
