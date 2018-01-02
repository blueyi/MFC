/////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Cristi Posea
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes
// (don't get me blamed for your possible bugs), don't alter or remove
// this notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc.,
// and I'll try to keep a version up to date.  I can be reached at:
//    cristi@gds.ro
/////////////////////////////////////////////////////////////////////////
//
// Acknowledgements:
//  o   Thanks to Harlan R. Seymour (harlan@hcube.com) for motivating me
//      to update this code. Also he prompted me to a bug durring 
//      the developement phase.
//  o   Thanks to Zafir Anjum (zafir@codeguru.com) for publishing this
//      code on his cool site (www.codeguru.com).
//  o   Some ideeas for the gripper came from the CToolBarEx flat toolbar
//      by Joerg Koenig (Joerg.Koenig@rhein-neckar.de). Also he inspired
//      me on writting this notice:) . Thanks, Joerg!
//  o   Thanks to Jakawan Ratiwanich (jack@alpha.fsec.ucf.edu) and to
//      Udo Schaefer(Udo.Schaefer@vcase.de) for the dwStyle bug fix under
//      VC++ 6.0.
//  o   Thanks to Microsoft developers for the MFC source code. After
//      all, most of this class code came from there.
//
/////////////////////////////////////////////////////////////////////////
//
// Usage:
// o    Derive your class from CSizingControlBar. Then create your child
//      controls/windows on it.
// o    Include your class header in Mainfrm.cpp and add a member 
//      variable to CMainFrame. In CMainFrame::OnCreate(), create the
//      control bar, enable it to dock, and so on... like a toolbar or
//      any control bar.
// o    More details at
//      http://www.codeguru.com/docking/docking_window.shtml or search
//      http://www.codeguru.com for my name if the article has moved.
//
/////////////////////////////////////////////////////////////////////////

#if !defined(SIZECBAR_H_INCLUDED)
#define SIZECBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// sizecbar.h : header file
//

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar control bar

class CSizingControlBar : public CControlBar
{
public:
    CSizingControlBar();

// Attributes
public:
    CSize m_sizeHorz;
    CSize m_sizeVert;
    CSize m_sizeFloat;
    BOOL IsHorzDocked() const;
    BOOL IsVertDocked() const;

// Operations
public:

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSizingControlBar)
	public:
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CSize sizeDefault, BOOL bHasGripper, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);
    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	//}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CSizingControlBar();
    
protected:
    // implementation helpers
    void StartTracking();
    void StopTracking(BOOL bAccept);
	void OnTrackUpdateSize(CPoint& point);
    void OnTrackInvertTracker();
	virtual CSize CalcMaxSize();
	virtual BOOL QueryDragFullWindows() const;

protected:
	// used for resizing
    CSize	m_sizeMin;
    CSize   m_sizeMax;
	CPoint	m_ptOld;
    CRect   m_rectBorder;
    BOOL    m_bTracking;
	BOOL	m_bDragShowContent;
	CSize	m_sizeOld;

    BOOL    m_bInRecalcNC;
    UINT    m_nDockBarID;
    int     m_cxEdge;
    BOOL    m_bHasGripper;
    int     m_cyGripper;
    CRect   m_rectGripper;

// Generated message map functions
protected:
    //{{AFX_MSG(CSizingControlBar)
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(SIZECBAR_H_INCLUDED)

