//============================================================================================
//
//============================================================================================
#include "stdafx.h"
#include "BitmapKeyed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOOLTIP_ID 1

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CBitmapKeyed, CBitmap)

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CBitmapKeyed, CStatic)
    //{{AFX_MSG_MAP(CBitmapKeyed)
    ON_WM_CREATE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
    ON_WM_NCHITTEST()
END_MESSAGE_MAP()

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
UINT CBitmapKeyed::OnNcHitTest(CPoint /*point*/) 
{
   return HTCLIENT;	
}

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
void CBitmapKeyed::Init (CWnd *pParent, int nIDC, int idBitmap, int idBitmapKey)
{
   if (nIDC) pParent->GetDlgItem(nIDC)->ShowWindow(false);

   Bitmap.DeleteObject ();
   BitmapKey.DeleteObject ();
   Bitmap.LoadBitmap(idBitmap);
   BitmapKey.LoadBitmap(idBitmapKey);

   if (nIDC)
   {
      CRect rect;
      pParent->GetDlgItem(nIDC)->GetWindowRect(&rect);
      pParent->ScreenToClient (&rect);
      DestroyWindow();
      Create ("a", WS_VISIBLE|WS_CHILD, rect, pParent, nIDC);
   }

   // Create the tooltip
   if (m_tooltipOverride!="")
   {
      CRect rect; 
      GetClientRect(rect);
      m_ToolTip.Create(this);	
      m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
      m_ToolTip.AddTool(this, m_tooltipOverride, rect, TOOLTIP_ID);
   }
}

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
int CBitmapKeyed::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (CStatic::OnCreate(lpCreateStruct) == -1)
      return -1;
    
   SetWindowSize();    // resize appropriately
   return 0;
}

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
void CBitmapKeyed::OnPaint(void)
{
	CPaintDC dc(this);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	Bitmap.GetBitmap(&bm);

	// Bild zeichnen
	CBitmap* pOldBitmap = dcImage.SelectObject(&BitmapKey);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCAND);
	dcImage.SelectObject(&Bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCPAINT);
	dcImage.SelectObject(pOldBitmap);
}

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
void CBitmapKeyed::PreSubclassWindow() 
{
    ModifyStyle(0, BS_OWNERDRAW);        // Make it owner drawn

    CStatic::PreSubclassWindow();
    SetWindowSize();                     // resize appropriately
}

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
void CBitmapKeyed::SetWindowSize()
{
    // Get size dimensions of edges
    CSize MarginSize(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

    // Get window size
    CRect rect;
    GetWindowRect(rect);

    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rect);

    // Set window size at least as wide as 2 arrows, and as high as arrow + margins
    int nWidth = max(rect.Width(), rect.Height());
    MoveWindow(rect.left, rect.top, nWidth, rect.Height(), TRUE);

    // Get the new coords of this window
    GetWindowRect(rect);
    ScreenToClient(rect);
}

//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
BOOL CBitmapKeyed::PreTranslateMessage(MSG* pMsg) 
{
    if (m_tooltipOverride!="" && m_ToolTip.GetSafeHwnd())
       m_ToolTip.RelayEvent(pMsg);

    return CStatic::PreTranslateMessage(pMsg);
}
