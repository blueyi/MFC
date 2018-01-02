/*
   FILNAME:       splitterTabWnd.cpp

   PURPOSE:       Manage view's that you can switch between by clicking at the tab.

   CREATED BY:    Per Ghosh
   ENVIRONMENT:	Visual C++


INFO:
*/

#include "stdafx.h"
#include "tab.h"

#include "TabView.h"

#include "splitterTabWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CsplitterTabWnd, CSplitterWnd)

/************************************************
   *   Constructor/Destructor 
   *
 * * *
  ***
   *
*/

CsplitterTabWnd::CsplitterTabWnd() :
   m_pwndTab(NULL), m_uSelectedViewIndex(0)
{
   m_cxSplitter    = m_cySplitter    = 0;   // size of splitter bar
   m_cxSplitterGap = m_cySplitterGap = 0;   // amount of space between panes
   m_cxBorder      = m_cyBorder      = 0;   // borders in client area
}

CsplitterTabWnd::~CsplitterTabWnd()
{
   if( m_pwndTab ) delete m_pwndTab;
}

/************************************************
   *   Virtual functions
   *
 * * *
  ***
   *
*/
/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 

Param:

Return:
*/
void CsplitterTabWnd::RecalcLayout()
{
   CWnd* pWnd;
   CRect rectClient;

   HDWP hdwp;

   GetClientRect( rectClient );

   // Set position for the tab window
   pWnd = GetPane( 1, 0 );

   hdwp = ::BeginDeferWindowPos( 2 );

   DeferWindowPos( hdwp,
                   pWnd->m_hWnd,
                   NULL,
                   rectClient.left,
                   rectClient.bottom - m_pwndTab->GetHeight(),
                   rectClient.right,
                   m_pwndTab->GetHeight(),
                   SWP_NOACTIVATE|SWP_NOZORDER );

   // Set position for the working-window
   pWnd = GetPane( 0, 0 );
   DeferWindowPos( hdwp,
                   pWnd->m_hWnd,
                   NULL,
                   rectClient.left,
                   rectClient.top,
                   rectClient.right,
                   rectClient.bottom - m_pwndTab->GetHeight(), 
                   SWP_NOACTIVATE|SWP_NOZORDER );

   EndDeferWindowPos( hdwp );

}

/************************************************
   *   Functions 
   *
 * * *
  ***
   *
*/
/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 

Param:

Return:
*/
BOOL CsplitterTabWnd::Create( CWnd* pwndParent, CCreateContext* pContext )
{
   ASSERT( m_ptrarrayRCView.GetSize() );         // must be one or more
   ASSERT( pwndParent->IsKindOf( RUNTIME_CLASS( CFrameWnd ) ) );

   CRuntimeClass* pRCView;                       // runtime class for first working view

   SIZE  size;                                   // 
   CRect rect;                                   //

   pRCView = (CRuntimeClass*)m_ptrarrayRCView[0];
   ASSERT( pRCView->IsDerivedFrom( RUNTIME_CLASS( CWnd ) ) );

   CreateStatic( pwndParent, 2, 1, WS_CHILD );   // create two panes

   pwndParent->GetClientRect( &rect );           // get rect for frame window
   
   size.cx = rect.right;
   size.cy = rect.bottom - 20;
   
   VERIFY( CreateView( 0, 0, pRCView, size, pContext ) );

   size.cy = 20;
   VERIFY( CreateView( 1, 0, RUNTIME_CLASS(CwndTab), size, pContext ) );

   m_pwndTab = (CwndTab*)GetPane( 1, 0 );
   m_pwndTab->SetSplitterTabWnd( this );
   
   ShowWindow( SW_SHOWNORMAL );
   UpdateWindow();

   return TRUE;

}

/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 

Param:

Return:
*/
UINT CsplitterTabWnd::AddView( CRuntimeClass* pRCView, LPCTSTR pszViewName )
{
   ASSERT( pRCView->IsDerivedFrom( RUNTIME_CLASS( CWnd ) ) );
   m_ptrarrayRCView.Add( pRCView );
   m_sarrayViewName.Add( pszViewName );

   if( m_pwndTab ) m_pwndTab->SetModified();

   return m_ptrarrayRCView.GetSize();
}

/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 

Param:
*/
void CsplitterTabWnd::InsertView( UINT uIndex, CRuntimeClass* pRCView, LPCTSTR pszViewName )
{
   ASSERT( pRCView->IsDerivedFrom( RUNTIME_CLASS( CWnd ) ) );
   ASSERT( uIndex < 100 );                                 // Realistic
   ASSERT( uIndex < (UINT)m_ptrarrayRCView.GetSize() );

   if( uIndex <= m_uSelectedViewIndex ) m_uSelectedViewIndex++;

   m_ptrarrayRCView.InsertAt( (int)uIndex, pRCView );
   m_sarrayViewName.InsertAt( (int)uIndex, pszViewName );

   if( m_pwndTab ) m_pwndTab->SetModified();
}

/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 

Param:
*/
void CsplitterTabWnd::SelectView( UINT uIndex )
{
   ASSERT( uIndex < (UINT)m_ptrarrayRCView.GetSize() );

   ReplaceView( (CRuntimeClass*)m_ptrarrayRCView[uIndex] );
   m_uSelectedViewIndex = uIndex;

   if( m_pwndTab ) m_pwndTab->Invalidate();
}

/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 

Param:
*/
void CsplitterTabWnd::RemoveView( CRuntimeClass* pRCView )
{
   int iIndex;
   CRuntimeClass* pRCViewInList;

   iIndex = m_ptrarrayRCView.GetSize();

   while( iIndex )
   {
      pRCViewInList = (CRuntimeClass*)m_ptrarrayRCView[iIndex];
      if( pRCViewInList == pRCView )
      {
         ASSERT( m_uSelectedViewIndex != (UINT)iIndex );
         m_ptrarrayRCView.RemoveAt( iIndex );

         if( m_pwndTab )
         {
            m_pwndTab->SetModified();
            m_pwndTab->Invalidate();
         }// endif
      }// endif
   }// endwhile

   TRACE1("CsplitterTabWnd::RemoveView()\nWarning: Did not find %s\n", pRCView->m_lpszClassName );
}

/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 

Param:
*/
void CsplitterTabWnd::RemoveView( UINT uIndex )
{
   ASSERT( uIndex < 100 );                                 // Realistic
   ASSERT( uIndex < (UINT)m_ptrarrayRCView.GetSize() );
   ASSERT( m_uSelectedViewIndex != uIndex );

   m_ptrarrayRCView.RemoveAt( (int)uIndex );

   if( m_pwndTab )
   {
      m_pwndTab->SetModified();
      m_pwndTab->Invalidate();
   }
}



/*-------------------------------------------------------------------------------------------------
Name:    ReplaceView()
Type:    Function
Purpose: Destroy current working view and creates a new

 Param:  pViewClass = Pekare till CRuntimeClass'en för den view som vi skall skapa
 Info:
 Med denna funktion tar vi och byter den view som finns i huvudfönstret. Den view som tidigare
 där raderas vilket också betyder att dess destruktor anropas.
*/
BOOL CsplitterTabWnd::ReplaceView(CRuntimeClass* pRCView)
{
   CCreateContext context; // For connecting to document and creating view
   CView* pviewCurrent;    // Current active view
   CView* pviewNew;        // View that are going to be created

   BOOL  bSaveAutoDelete;  // For storing auto delete flag
   SIZE  size;             // Size for new view
   CRect rect;             // Client rect
                                                                        
   VERIFY( pviewCurrent = (CView*)GetPane( 0, 0 ) );       // Get Window
   
   if( pviewCurrent->IsKindOf( pRCView ) ) return TRUE;    // same as before

   pviewCurrent->GetClientRect( &rect );                   // get rect
   size.cx = rect.right;                                   // width
   size.cy = rect.bottom;                                  // height

   CDocument* pDoc = pviewCurrent->GetDocument();          // get document

   if( pDoc )                                              // if document
   {
      bSaveAutoDelete = pDoc->m_bAutoDelete;               // save auto delete flag
      pDoc->m_bAutoDelete = FALSE;                         // don't delete document
   }

   pviewCurrent->DestroyWindow();                          // destroy view
   if( pDoc )
   {
      pDoc->m_bAutoDelete = bSaveAutoDelete;               // restore auto delete flag
   }

   // ***
   // Set connections for the new view
   // ***
   context.m_pNewViewClass   = pRCView;                                  
   context.m_pCurrentDoc     = pDoc;
   context.m_pNewDocTemplate = pDoc->GetDocTemplate();
   context.m_pLastView       = NULL;
   context.m_pCurrentFrame   = GetParentFrame();

   if( ! CreateView( 0, 0, pRCView, size, &context) )      // create view in working pane
   {
      TRACE0("Warning: View was not created !!!\n");
      return FALSE;
   }
   
   pviewNew = (CView*)GetPane( 0, 0 );                     // get view in working pane

   RecalcLayout();                                         // reposition
   pviewNew->UpdateWindow();                               // update
   GetParentFrame()->SetActiveView(pviewNew);              // activate

   return TRUE;
}

BEGIN_MESSAGE_MAP(CsplitterTabWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CsplitterTabWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/************************************************
   *   Messages
   *
 * * *
  ***
   *
*/
/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 
*/
void CsplitterTabWnd::OnLButtonDown(UINT nFlags, CPoint point)
{     
    // prevent the user from dragging the splitter bar
	return;
}

/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 
*/
BOOL CsplitterTabWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{   
    // Don't allow the cursor to change over splitbar
	return FALSE;
	
}

/*-------------------------------------------------------------------------------------------------
Name:	 
Type:    
Purpose: 
*/
void CsplitterTabWnd::OnMouseMove(UINT nFlags, CPoint point)
{       
    // Don't allow the cursor to change over splitbar
    CWnd::OnMouseMove(nFlags, point);
}


/************************************************
*************************************************
******                                     ******
****                                         ****
****    class CwndTab                        ****
****                                         ****
******                                     ******
*************************************************
************************************************/


IMPLEMENT_DYNCREATE( CwndTab, CWnd );

CString CwndTab::m_stringWindowClass;

/************************************************
   *   Constructor/Destructor 
   *
 * * *
  ***
   *
*/
CwndTab::CwndTab() :
   m_dwFlag(0), m_uHeight(15), m_bTabModified(TRUE), m_pFont(NULL), m_iOffsetToLeft(20),
   m_uOffsetFontGap(3)
{
}

CwndTab::~CwndTab()
{
   if( m_dwFlag & PG_WNDTAB_FONT ) delete m_pFont;
}

/*-------------------------------------------------------------------------------------------------
Name:	   SetHeight()
Type:    Function
Purpose: Set height for tabs

Param:   uHeight = tab height
*/
void CwndTab::SetHeight( UINT uHeight )
{ 
   m_uHeight      = uHeight;
   Invalidate();
}


/************************************************
   *   Virtual functions
   *
 * * *
  ***
   *
*/
/*-------------------------------------------------------------------------------------------------
Name:	   PreCreateWindow()
Type:    Virtual function
Purpose: Register a new window class
*/
BOOL CwndTab::PreCreateWindow(CREATESTRUCT& cs) 
{
   if( CwndTab::m_stringWindowClass.IsEmpty() )
   {
      CwndTab::m_stringWindowClass =
         ::AfxRegisterWndClass( CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW,
                                AfxGetApp()->LoadStandardCursor(IDC_ARROW),
                                (HBRUSH)(COLOR_BTNFACE+1),
                                NULL );
   }

   cs.lpszClass = CwndTab::m_stringWindowClass;
	
	return CWnd::PreCreateWindow(cs);
}

/************************************************
   *   Functions 
   *
 * * *
  ***
   *
*/
/*-------------------------------------------------------------------------------------------------
Name:	   CreateFont()
Type:    Function
Purpose: Create font for text on tabs
*/
void CwndTab::CreateFont()
{
   LOGFONT logfont;

   memset( &logfont, 0, sizeof( LOGFONT ) );
   
   logfont.lfHeight = m_uHeight - 2;
   strcpy(logfont.lfFaceName,"MS Sans Serif"); 
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont); 

   m_dwFlag |= PG_WNDTAB_FONT;
}

/*-------------------------------------------------------------------------------------------------
Name:	   DrawTab()
Type:    Function
Purpose: Draw all the tabs

Param:   pDC           = DC that the tabs should be drawn on.
*/
void CwndTab::DrawTab( CDC* pDC )
{
   UINT  uTabIndex;          // tab that are drawn
   POINT ppoint[4];          // points that will be used to draw tab                                                                   
                             
   UINT  uTabHeight;         // the tab height 
   UINT  uDistanceToNextTab; // distance between tabs
   int   iOffsetToLeft;      // distance from left side of client edge                                                                 
                             
   CRect    rect;
   CPen     penBlack( PS_SOLID, 1, RGB(0,0,0) );
   CPen*    ppenOld;

   if( m_bTabModified ) UpdateTabWidth( pDC );             // update tab ?

   ppenOld = pDC->SelectObject( &penBlack );               // select a black pen

   pDC->SetBkMode( TRANSPARENT );                          // just text

   GetClientRect( &rect );                                 // get client rect
   pDC->MoveTo( rect.left, rect.top );                     // move to upper left
   pDC->LineTo( rect.right, rect.left );                   // draw a line from left to right

   uTabHeight         = m_uHeight - 1;
   uDistanceToNextTab = uTabHeight / 2;
   iOffsetToLeft      = m_iOffsetToLeft;

   for( uTabIndex = 0; uTabIndex < (UINT)m_dwarrayTabWidth.GetSize(); uTabIndex++ )
   {
      // ***
      // set all points for tab, then we will be able to draw it
      // ***
      ppoint[0].x = iOffsetToLeft;                         // ""
      ppoint[0].y = 0;

      iOffsetToLeft += uDistanceToNextTab;                 // "\" 
      ppoint[1].x   =  iOffsetToLeft;
      ppoint[1].y   =  uTabHeight;

      //draw tab-text 
      pDC->TextOut( ppoint[1].x + m_uOffsetFontGap,         
                    1,
                    m_psplitterTabWnd->m_sarrayViewName[uTabIndex] );

      iOffsetToLeft += m_dwarrayTabWidth[uTabIndex];       // "\____"
      ppoint[2].x   =  iOffsetToLeft;
      ppoint[2].y   =  uTabHeight;

      if( uTabIndex == (UINT)(m_dwarrayTabWidth.GetSize() - 1) ) // "\____/"
      {
         iOffsetToLeft += uDistanceToNextTab;
         ppoint[3].x   =  iOffsetToLeft;
         ppoint[3].y   =  0;
      }
      else
      {
         iOffsetToLeft += (uDistanceToNextTab / 2);
         ppoint[3].x   =  iOffsetToLeft;
         ppoint[3].y   =  (uTabHeight / 2);

         iOffsetToLeft -= (uDistanceToNextTab / 2);
      }

      pDC->Polyline( ppoint, 4 );
   }

   pDC->SelectObject( ppenOld );
}

/*-------------------------------------------------------------------------------------------------
Name:	   DrawSelectedTab
Type:    Function
Purpose: Draw the tab for selected view

Param:   pDC           = DC that the tabs should be drawn on.
*/
void CwndTab::DrawSelectedTab( CDC* pDC )
{
   CRgn   rgn;               // filling region
   CBrush brush;             // brush that the selected tab will be filled with

   UINT  uTabHeight;         // the tab height
   UINT  uDistanceToNextTab; // distance between tabs
   int   iOffsetToLeft;      // distance from left side of client edge

   POINT  ppoint[4];         // points that will be used to draw tab

   uTabHeight         = m_uHeight - 1;                     // set tab height
   uDistanceToNextTab = uTabHeight / 2;                    // distance to next tab
   iOffsetToLeft      = m_iOffsetToLeft;                   // distance to left side

   // *** loop to selected tab ***
   for( UINT uCounter = 0; uCounter < m_psplitterTabWnd->m_uSelectedViewIndex; uCounter++ )
   {
      iOffsetToLeft += m_dwarrayTabWidth[uCounter];
      iOffsetToLeft += uDistanceToNextTab;
   }

   // ***
   // set all points for selected tab, then we will be able to draw it
   // ***
   ppoint[0].x = iOffsetToLeft;                            // ""
   ppoint[0].y = 0;

   iOffsetToLeft += uDistanceToNextTab;                    // "\"
   ppoint[1].x   =  iOffsetToLeft;
   ppoint[1].y   =  uTabHeight;

   iOffsetToLeft += m_dwarrayTabWidth[uCounter];           // "\____"
   ppoint[2].x   =  iOffsetToLeft;
   ppoint[2].y   =  uTabHeight;

   iOffsetToLeft += uDistanceToNextTab;                    // "\____/"
   ppoint[3].x   =  iOffsetToLeft;
   ppoint[3].y   =  0;

   brush.CreateSolidBrush( ::GetSysColor( COLOR_WINDOW ) );
   rgn.CreatePolygonRgn( ppoint, 4, ALTERNATE );

   pDC->FillRgn( &rgn, &brush );
   pDC->Polyline( ppoint, 4 );
   pDC->TextOut( ppoint[1].x + m_uOffsetFontGap, 1, m_psplitterTabWnd->m_sarrayViewName[uCounter] );
}

/*-------------------------------------------------------------------------------------------------
Name:	   UpdateTabWidth()
Type:    Function
Purpose: Update widenes for all tabs

Param:   pDC = DC that the tabs should be drawn on.
*/
void CwndTab::UpdateTabWidth( CDC* pDC )
{
   CSize size;

   m_dwarrayTabWidth.RemoveAll();

   for( int iCounter = 0; iCounter < m_psplitterTabWnd->m_sarrayViewName.GetSize(); iCounter++ )
   {
      // get text size
      size = pDC->GetTextExtent( m_psplitterTabWnd->m_sarrayViewName[iCounter] );
      // add the width for text plus gap to array
      m_dwarrayTabWidth.Add( size.cx + (m_uOffsetFontGap << 1) );
   }

   m_bTabModified = FALSE;                                 // tabs updated
}


BEGIN_MESSAGE_MAP(CwndTab, CWnd)
	//{{AFX_MSG_MAP(CwndTab)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/************************************************
   *   Messages
   *
 * * *
  ***
   *
*/

/*-------------------------------------------------------------------------------------------------
Name:	   OnPaint()
Type:    Message
Purpose: Draw all the information in the tab window
*/
void CwndTab::OnPaint() 
{
   CFont*   pfontOld;   // pointer to old font

   CPaintDC dc(this);                                      // device context for painting

   if( m_pFont == NULL ) CreateFont();                     // if no tab font, create one

   pfontOld = dc.SelectObject( m_pFont );                  // select tab font

   DrawTab( &dc );                                         // draw the tabs
   DrawSelectedTab( &dc );                                 // draw th selected tab

   dc.SelectObject( pfontOld );                            // select old font
}



/*-------------------------------------------------------------------------------------------------
Name:	   OnLButtonDown()
Type:    Message
Purpose: Check if klicked on a tab, and if so switch view
*/
void CwndTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
   int  iOffsetToLeft;
   UINT uDistanceToNextTab;

   uDistanceToNextTab = (m_uHeight - 1) / 2;
   
   iOffsetToLeft = m_iOffsetToLeft;

   // *** check if clicked on a tab ***
   for( UINT uCounter = 0; uCounter < (UINT)m_dwarrayTabWidth.GetSize(); uCounter++ )
   {
      iOffsetToLeft += uDistanceToNextTab;

      if( ( point.x >= (iOffsetToLeft - 1) ) && 
          ( point.x <= (int)(iOffsetToLeft + m_dwarrayTabWidth[uCounter] + 1) ) )
      {
         m_psplitterTabWnd->SelectView( uCounter );
         break;
      }

      iOffsetToLeft += m_dwarrayTabWidth[uCounter];
   }

	CWnd::OnLButtonDown(nFlags, point);
}



