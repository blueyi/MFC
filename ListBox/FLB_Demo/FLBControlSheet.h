// FLBControlSheet.h : header file
//

#if !defined(AFX_FLBCONTROLSHEET_H__4C4022FE_E6BE_447E_8054_17054E243845__INCLUDED_)
#define AFX_FLBCONTROLSHEET_H__4C4022FE_E6BE_447E_8054_17054E243845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PpStyles.h"
#include "PpManual.h"
#include "PpMruSync.h"
#include "PpPersistence.h"
#include "PpTransparency.h"

/////////////////////////////////////////////////////////////////////////////
// CFLBControlSheet dialog

class CFLBControlSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CFLBControlSheet)

// Construction
public:
	CFLBControlSheet(CWnd* pParent = NULL);	// standard constructor
	CFLBControlSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CFLBControlSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Dialog Data
	//{{AFX_DATA(CFLBControlSheet)
//	enum { IDD = IDD_DEMOFLB_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFLBControlSheet)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL OnInitDialog();

protected:
	HICON m_hIcon;

	CPpStyles			m_ppStyles;
	CPpManual			m_ppManual;
	CPpMruSync			m_ppMruSync;
	CPpPersistence		m_ppPersistence;
	CPpTransparency	m_ppTransparency;
	// Generated message map functions
	//{{AFX_MSG(CFLBControlSheet)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLBCONTROLSHEET_H__4C4022FE_E6BE_447E_8054_17054E243845__INCLUDED_)
