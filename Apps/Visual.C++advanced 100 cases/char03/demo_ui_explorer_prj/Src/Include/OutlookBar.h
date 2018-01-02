// OutlookBar.h : header file
// Copyright ©1998 - Kirk Stowell
// All Rights Reserved.
//
// Email: kstowel@sprynet.com
// URL:   www.geocities.com/SiliconValley/Haven/8230
//
// You are free to use, modify and distribute this source, as long as
// it is not sold for profit, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND. The user
// agrees to hold the author(s) blameless from any or all problems that
// may arise from the use or distribution of this code.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(OUTLOOKBAR_H_INCLUDED)
#define OUTLOOKBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CContentItems - Container class for menu items.

class CLASS_EXPORT CContentItems
{
protected:
	UINT m_nImageID;
	CString m_csText;

public:
	CContentItems( UINT nID, CString str ) :
	  m_nImageID( nID ), m_csText( str ) {
	}

	void operator = ( CContentItems& pItems ) {
		m_nImageID = pItems.m_nImageID;
		m_csText = pItems.m_csText;
	}

	UINT GetImageID() { return m_nImageID; }
	CString GetText() { return m_csText;  }
};

/////////////////////////////////////////////////////////////////////////////
// COutlookBar class

class CLASS_EXPORT COutlookBar : public CListBox
{
	DECLARE_DYNAMIC(COutlookBar)

// Construction
public:
	COutlookBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookBar)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void OnSelButton() = 0;
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetImageList( UINT uList, UINT uSize, COLORREF clrMask );
	void SetItems( CContentItems* pItems, int nNumItems );
	virtual ~COutlookBar();

// Generated message map functions
protected:
	//{{AFX_MSG(COutlookBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
    CPoint          m_point;
	CImageList*		m_pImageList;
	CContentItems*  m_pContents;
    int             m_nNumItems;
	int             m_nIndex;
    bool            m_bHilight;
    bool            m_bLBDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(OUTLOOKBAR_H_INCLUDED)

