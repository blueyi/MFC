// AniButton.cpp : implementation file
//

#include "stdafx.h"
#include "CDib.h"
#include "CAniButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAniButton

// Constant definition for the animation timer ID.
const int ANIMATION_TIMER_ID = 512;

// Default Constructor
CAniButton::CAniButton()
{
    m_pDIB = NULL;
    m_pDisabledDIB = NULL;

    m_uTimer = 0;
    m_nCurFrame = 0;
    m_nNumFrames = 0;
    m_nFramesPerSecond = 0;

    m_nFrameWidth = 0;
    m_nFrameHeight = 0;

    m_bStretchToFit = FALSE;
    m_hCursor = NULL;
}


// Destructor
CAniButton::~CAniButton()
{
    if(m_pDIB) delete m_pDIB;
    if(m_pDisabledDIB) delete m_pDisabledDIB;
}


BEGIN_MESSAGE_MAP(CAniButton, CButton)
	//{{AFX_MSG_MAP(CAniButton)
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAniButton message handlers

// OnSetCursor method
BOOL CAniButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CButton::OnSetCursor(pWnd, nHitTest, message);
}


// DrawItem method
void CAniButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	UINT    uState = lpDIS->itemState;
	CRect	rect;
    CDIB*   pDIB = m_pDIB;
    int     nYFrameOffset = 0;
    int     nXFrameOffset = m_nCurFrame * m_nFrameWidth + 1;
    
	//
    // if the button is disabled and the timer
    // is enabled, disable the timer.
    //
    if((uState & ODS_DISABLED) && m_uTimer)
    {
        KillTimer(m_uTimer);
        m_uTimer = 0;
        m_nCurFrame = 0;
    }
    //
    // else if the button is not disabled, and the
    // timer is not enabled... Start the timer.
    //
    else if(!(uState & ODS_DISABLED) && 
            !m_uTimer &&
            m_nNumFrames > 1)
    {
        m_uTimer = SetTimer(ANIMATION_TIMER_ID,
                            1000 / m_nFramesPerSecond,
                            NULL);
    }
    
    //
	// Determine the state and set the bitmap position accordingly.
	//
	if (uState & ODS_SELECTED) // The button is pressed
	{
		nYFrameOffset = m_nFrameHeight * 2;
	}
    else if (uState & ODS_FOCUS) // button has focus but not pressed
	{
		nYFrameOffset = m_nFrameHeight;
	}
	else if ((uState & ODS_DISABLED) && m_pDisabledDIB != NULL)
	{
		pDIB = m_pDisabledDIB;
	    nXFrameOffset = 0;
    }


	// Get the device context for drawing.
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

    ASSERT(pDC);
    ASSERT(pDIB);
    if(pDC && pDIB)
    {

	    // Draw the bitmap onto the window device context.
	    rect.CopyRect(&lpDIS->rcItem);

        //
        // If we are not stretching (or shrinking) the bitmap
        // to fit inside of the window, just draw in the center.
        //
        if(!m_bStretchToFit)
        {
            pDIB->Draw( pDC,
                        rect.left + (rect.Width() - m_nFrameWidth) / 2,
                        rect.top + (rect.Height() - m_nFrameHeight) / 2, 
                        m_nFrameWidth,
                        m_nFrameHeight,
                        nXFrameOffset,
                        nYFrameOffset );
        }
        else // Strect the bitmap to fit!
        {
            pDIB->Stretch( pDC,
                           rect.left,
                           rect.top, 
                           rect.Width(),
                           rect.Height(),
                           nXFrameOffset,
                           nYFrameOffset,
                           m_nFrameWidth,
                           m_nFrameHeight);
        }
    }
}


// The AutoLoad method is called to load the desired bitmaps before
// the button is displayed. 
BOOL CAniButton::AutoLoad(UINT  nID,
                          CWnd* pParent,
                          UINT  nBitmapID,
                          UINT  nDisabledID,
                          UINT  nFramesPerSecond,
                          UINT  nNumFrames,
                          BOOL  bStretchToFit,
                          BOOL  bChangeFaceColor,
                          UINT  nCursorID)
{
    //
    // First Create the bitmaps which the button will display.
    // Only the Main bitmap is needed because there is not
    // always a need to disable a button.
    //
    m_pDIB = new CDIB(nBitmapID);
    if( !m_pDIB || !m_pDIB->IsPaletteLoaded() )
    {
        return FALSE;
    }
    if( nDisabledID != 0 )
    {
        m_pDisabledDIB = new CDIB(nDisabledID);
        if( !m_pDisabledDIB->IsPaletteLoaded() )
        {
            return FALSE;
        }
    }

    // Now make the call to Init to initialize the rest of the variables
    return Init(nID,
                pParent,
                nFramesPerSecond,
                nNumFrames,
                bStretchToFit,
                bChangeFaceColor,
                nCursorID);

}


// The AutoLoad method is called to load the desired bitmaps before
// the button is displayed. 
BOOL CAniButton::AutoLoad(UINT  nID,
                          CWnd* pParent,
                          const char* szFilename,
                          const char* szDisabledFilename,
                          UINT  nFramesPerSecond,
                          UINT  nNumFrames,
                          BOOL  bStretchToFit,
                          BOOL  bChangeFaceColor,
                          UINT  nCursorID)
{

    //
    // First Create the bitmaps which the button will display.
    // Only the Main bitmap is needed because there is not
    // always a need to disable a button.
    //
    m_pDIB = new CDIB(szFilename);
    if( !m_pDIB || !m_pDIB->IsPaletteLoaded() )
    {
        return FALSE;
    }
    if( szDisabledFilename != NULL )
    {
        m_pDisabledDIB = new CDIB(szDisabledFilename);
        if( !m_pDisabledDIB->IsPaletteLoaded() )
        {
            return FALSE;
        }
    }

    // Now make the call to Init to initialize the rest of the variables
    return Init(nID,
                pParent,
                nFramesPerSecond,
                nNumFrames,
                bStretchToFit,
                bChangeFaceColor,
                nCursorID);
}


// Init method.  Helper method for the AutoLoad methods.
BOOL CAniButton::Init(UINT  nID,
                      CWnd* pParent,
                      UINT  nFramesPerSecond,
                      UINT  nNumFrames,
                      BOOL  bStretchToFit,
                      BOOL  bChangeFaceColor,
                      UINT  nCursorID)
{
    // Attach the button to the dialog control
	if (!SubclassDlgItem(nID,
                         pParent))
    {
        return FALSE;
    }
    
    //
    // If we want to change the face color of the button
    // to match the windows System color...
    //
    if(bChangeFaceColor)
    {
        m_pDIB->ConvertColor( 0, 0, GetSysColor(COLOR_3DFACE) );
        if(m_pDisabledDIB)
        {
            m_pDisabledDIB->ConvertColor( 0, 0, GetSysColor(COLOR_3DFACE) );
        }
    }

    //
    // If the nNumFrames argument is 0, we can automatically calculate the
    // number of frames by dividing the width of the main bitmap by the
    // width of the Disabled Bitmap. NOTE: This can only be done if the
    // disabled bitmap is the same width as each individual frame in the
    // main bitmap.
    //
    if(nNumFrames == 0)
    {
        ASSERT(m_pDisabledDIB);
        m_nNumFrames = m_pDIB->GetWidth() / m_pDisabledDIB->GetWidth();
    }
    else
    {
        m_nNumFrames = nNumFrames;
    }

    // set the other necessary member variables
    m_nFramesPerSecond = nFramesPerSecond;
    m_nFrameWidth      = m_pDIB->GetWidth() / m_nNumFrames;
    m_nFrameHeight     = m_pDIB->GetHeight() / 3; // Three Rows of animation.
    m_bStretchToFit    = bStretchToFit;

    // Load the cursor to use for the button if desired.
    if(nCursorID != 0)
    {
        m_hCursor = AfxGetApp()->LoadCursor(nCursorID);
    }
    else
    {
        m_hCursor = NULL;
    }

    if(m_nNumFrames > 1)
    {
        m_uTimer = SetTimer(ANIMATION_TIMER_ID,
                            1000 / m_nFramesPerSecond,
                            NULL);
        ASSERT(m_uTimer);
    }

	return TRUE;
}


// RealizePalette method.  This method needs to be called whenever
// the buttons parent window gets a WM_QUERYNEWPALETTE message.
void CAniButton::RealizePalette()
{
    // Determine which palette to realize.
    CPalette* pPal;
    IsWindowEnabled() ? pPal = m_pDIB->GetPalette() : 
                        pPal = m_pDisabledDIB->GetPalette();

    // Get the buttons device context for drawing.
    CDC* pDC = GetDC();
    
    // Realize the new palette.
    CPalette* pOldPalette = pDC->SelectPalette(pPal, FALSE);
    pDC->RealizePalette();

    // Be nice to the existing palette.
    pDC->SelectPalette(pOldPalette, TRUE);
    pDC->RealizePalette();

    ReleaseDC(pDC);

    // Redraw the button
    Invalidate();
}


void CAniButton::OnTimer(UINT nIDEvent) 
{
	// Increment the frame wrapping if necessary
    m_nCurFrame = (m_nCurFrame >= m_nNumFrames-1) ? 0 : m_nCurFrame + 1;
    
    // invalidate the button, to force it to redraw
    Invalidate(FALSE);
	
	CButton::OnTimer(nIDEvent);
}


void CAniButton::OnDestroy() 
{
	// be sure that the timer is dead
    if(m_uTimer)
    {
        KillTimer(m_uTimer);
    }

    CButton::OnDestroy();
}
