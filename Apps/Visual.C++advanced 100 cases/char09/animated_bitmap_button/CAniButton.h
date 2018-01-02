#if !defined(AFX_ANIBUTTON_H__CBAD41B1_3245_11D2_8C4F_000000000000__INCLUDED_)
#define AFX_ANIBUTTON_H__CBAD41B1_3245_11D2_8C4F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AniButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAniButton window

class CDIB;

class CAniButton : public CButton
{
// Construction
public:
	CAniButton();

// Attributes
public:
	CDIB*   m_pDIB;             // Main Bitmap Object
	CDIB*   m_pDisabledDIB;     // Disabled Bitmap Object
    UINT    m_uTimer;           // Animation Timer
    int     m_nCurFrame;        // Curent Frame of Animation
    int     m_nNumFrames;       // Total number of frames in animation
    int     m_nFramesPerSecond; // Frames to show each second
    int     m_nFrameWidth;      // Width of each frame in pixels
    int     m_nFrameHeight;     // Height of each frame in pixels
    BOOL    m_bStretchToFit;    // Flag for force fitting the bitmap
    HCURSOR m_hCursor;          // Handle to the cursor to display

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAniButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
protected:
    BOOL Init(UINT  nID,              // Resource ID for this button.
              CWnd* pParent,          // Button's Parent window.
              UINT  nFramesPerSecond, // Number of frames per second
              UINT  nNumFrames,       // Total number of frames
              BOOL  bStretchToFit,    // Flag for force fitting the bitmap
              BOOL  bChangeFaceColor, // Flag to change the face color
              UINT  nCursorID);       // Resource ID for cursor

public:
	
    virtual ~CAniButton(); // Destructor

    BOOL AutoLoad(UINT  nID,
                  CWnd* pParent,
                  UINT  nBitmapID,
                  UINT  nDisabledID,
                  UINT  nFramesPerSecond,
                  UINT  nNumFrames = 0,
                  BOOL  bStretchToFit = FALSE,
                  BOOL  bChangeFaceColor = TRUE,
                  UINT  nCursorID = 0);

	BOOL AutoLoad(UINT  nID,
                  CWnd* pParent,
                  const char* szFilename,
                  const char* szDisabledFilename,
                  UINT  nFramesPerSecond,
                  UINT  nNumFrames = 0,
                  BOOL  bStretchToFit = FALSE,
                  BOOL  bChangeFaceColor = TRUE,
                  UINT  nCursorID = 0);

    void RealizePalette();
    
// Generated message map functions
protected:
	//{{AFX_MSG(CAniButton)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIBUTTON_H__CBAD41B1_3245_11D2_8C4F_000000000000__INCLUDED_)
