#if !defined(AFX_LISTIMAGECTRL_H__91095A76_23A7_4E7D_9DBF_21928269B8F9__INCLUDED_)
#define AFX_LISTIMAGECTRL_H__91095A76_23A7_4E7D_9DBF_21928269B8F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListImageCtrl.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CListImageCtrl window

class CListImageCtrl : public CListCtrl
{
// Construction
public:
	CListImageCtrl();

// Attributes
public:
	void CreateColumn();
	HBITMAP LoadPicture(CString mFile);
// Operations
public:
	CImageList m_imageList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListImageCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListImageCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListImageCtrl)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTIMAGECTRL_H__91095A76_23A7_4E7D_9DBF_21928269B8F9__INCLUDED_)
