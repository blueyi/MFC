// ColourPicker.cpp : implementation file
//

#include "stdafx.h"
#include "ColourPopupWnd.h"
#include "ColourPicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void AFXAPI DDX_ColourPicker(CDataExchange *pDX, int nIDC, COLORREF& crColour)
{
    HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
    ASSERT (hWndCtrl != NULL);                
    
    CColourPicker* pColourPicker = (CColourPicker*) CWnd::FromHandle(hWndCtrl);
    if (pDX->m_bSaveAndValidate)
    {
        crColour = pColourPicker->GetColour();
    }
    else // initializing
    {
        pColourPicker->SetColour(crColour);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CColourPicker

//!Constructor
CColourPicker::CColourPicker()
{
    SetBkColour(GetSysColor(COLOR_3DFACE));
    SetTextColour(GetSysColor(COLOR_BTNTEXT));

    m_bTrackSelection = FALSE;
    m_nSelectionMode = CP_MODE_BK;
    m_bActive = FALSE;
	m_noColor = FALSE;

    m_strDefaultText = _T("Automatic");
    m_strCustomText  = _T("More Colours...");
	m_strEffectText  = _T("Fill Effect...");
	m_strNoText      = _T("No Fill");
}

CColourPicker::~CColourPicker()
{
}

IMPLEMENT_DYNCREATE(CColourPicker, CButton)

BEGIN_MESSAGE_MAP(CColourPicker, CButton)
    //{{AFX_MSG_MAP(CColourPicker)
    ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
    ON_REGISTERED_MESSAGE(WELL_SELENDOK,     OnSelEndOK)
    ON_REGISTERED_MESSAGE(WELL_SELENDCANCEL, OnSelEndCancel)
    ON_REGISTERED_MESSAGE(WELL_SELCHANGED,    OnSelChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColourPicker message handlers

LONG CColourPicker::OnSelEndOK(UINT lParam, LONG /*wParam*/)
{
    COLORREF crNewColour = (COLORREF) lParam;
    m_bActive = FALSE;
    SetColour(crNewColour);

    CWnd *pParent = GetParent();
    if (pParent) {
        pParent->SendMessage(WELL_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(WELL_SELENDOK, lParam, (WPARAM) GetDlgCtrlID());
    }

    if (crNewColour != GetColour())
        if (pParent) pParent->SendMessage(WELL_SELCHANGED, lParam, (WPARAM) GetDlgCtrlID());

    return TRUE;
}

LONG CColourPicker::OnSelEndCancel(UINT lParam, LONG /*wParam*/)
{
    m_bActive = FALSE;
    SetColour((COLORREF) lParam);

    CWnd *pParent = GetParent();
    if (pParent) {
        pParent->SendMessage(WELL_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(WELL_SELENDCANCEL, lParam, (WPARAM) GetDlgCtrlID());
    }

    return TRUE;
}

LONG CColourPicker::OnSelChange(UINT lParam, LONG /*wParam*/)
{
    if (m_bTrackSelection) SetColour((COLORREF) lParam);

    CWnd *pParent = GetParent();
    if (pParent) pParent->SendMessage(WELL_SELCHANGED, lParam, (WPARAM) GetDlgCtrlID());

    return TRUE;
}

int CColourPicker::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CButton::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    SetWindowSize();    // resize appropriately
    return 0;
}

// On mouse click, create and show a CSVizColorWell window for colour selection
BOOL CColourPicker::OnClicked()
{
    m_bActive = TRUE;
    CRect rect;
    GetWindowRect(rect);

	CSVizColorWell *pPopup = new CSVizColorWell(
					 WELL_STYLE_OFFICE | WELL_STYLE_AUTODELETE | WELL_STYLE_POPUP,
                     GetColour(),                       // Selected colour
					 m_defalultColor,					// deafault Color
                     m_strDefaultText,                  // "Default" text area
                     m_strCustomText,					// Custom Text
					 m_strEffectText,					// Gdi+ effect
					 m_strNoText);                      // No fill 

    CWnd *pParent = GetParent();
 	
	if (pPopup->IsPopupWnd())
	    pPopup->Create(CPoint(rect.left, rect.bottom), this,  WS_VISIBLE|WS_POPUP);
	else
	    pPopup->Create(CPoint(rect.left, rect.bottom), this,  WS_VISIBLE|WS_CHILD);

	pPopup->FindCellFromColour(GetColour());

	if (pParent)
        pParent->SendMessage(WELL_DROPDOWN, (LPARAM)GetColour(), (WPARAM) GetDlgCtrlID());

    return TRUE;
}

void CColourPicker::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    USES_CONVERSION;

    ASSERT(lpDrawItemStruct);
    
    CDC*    pDC     = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect   rect    = lpDrawItemStruct->rcItem;
    UINT    state   = lpDrawItemStruct->itemState;
    CString m_strText;

    CSize Margins(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));
    // Draw arrow
    if (m_bActive) state |= ODS_SELECTED;
    pDC->DrawFrameControl(&m_ArrowRect, DFC_SCROLL, DFCS_SCROLLDOWN  | 
                          ((state & ODS_SELECTED) ? DFCS_PUSHED : 0) |
                          ((state & ODS_DISABLED) ? DFCS_INACTIVE : 0));

    pDC->DrawEdge(rect, EDGE_SUNKEN, BF_RECT);

    // Must reduce the size of the "client" area of the button due to edge thickness.
    rect.DeflateRect(Margins.cx, Margins.cy);

    // Fill remaining area with colour
    rect.right -= m_ArrowRect.Width();

	Graphics graphics(pDC->m_hDC);

	Rect theRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 

	Brush *pBrush =NULL;
	Color c1;
	c1.SetFromCOLORREF(GetColour());
	SolidBrush solidBrush(c1); //solid brush
    //hatch brush
	HatchBrush hBrush(GetHatchStyle(), GetColor1(),GetColor2());

	GraphicsPath path;
	path.AddRectangle(theRect);

	PathGradientBrush pthGrBrush(&path);
	
	// Set the color at the center of the path to blue.

	if (GetToCenter()) {
		pthGrBrush.SetCenterColor(GetColor2());

		// Set the color along the entire boundary of the path to aqua.
		Color colors[] = {GetColor1()};
		int count = 1;
		pthGrBrush.SetSurroundColors(colors, &count);
	}
	else{
		pthGrBrush.SetCenterColor(GetColor1());

		// Set the color along the entire boundary of the path to aqua.
		Color colors[] = {GetColor2()};
		int count = 1;
		pthGrBrush.SetSurroundColors(colors, &count);
	}

	//line gradient brush
	LinearGradientBrush linGrBrush( theRect, GetColor1(),  GetColor2(), GetLinearGradientMode());
 
#ifdef _UNICODE
	Image *image = Image::FromFile(GetImageName());
#else if
    LPWSTR lpwstr = A2W(GetImageName());
	Image *image = Image::FromFile(lpwstr);
#endif

	TextureBrush tBrush(image);

	if (GetStretch())//strech
		tBrush.SetTransform(&Matrix(1.0*rect.Width()/image->GetWidth(), 0.0f, 0.0f,
				1.0*rect.Height()/image->GetHeight(), 0.0f, 0.0f));
	else{ 
		tBrush.SetWrapMode(GetWrapMode());
	}

	BrushType brushType = GetBrushType();
	if (brushType == BrushTypeSolidColor){
		pBrush = &solidBrush;
	}
	else if( brushType ==  BrushTypeHatchFill){
		pBrush = &hBrush;
	}
	else if (brushType ==  BrushTypeTextureFill){
		pBrush = &tBrush;
	}
	else if (brushType == BrushTypePathGradient){
		pBrush = &pthGrBrush;
	}
	else if (brushType == BrushTypeLinearGradient){
		pBrush = &linGrBrush;
	}
	else
		pBrush = &solidBrush; //default is the solid brush
	if (!m_noColor)	
		graphics.FillRectangle(pBrush,theRect);
	graphics.ReleaseHDC(pDC->m_hDC);


    // Draw the window text (if any)
    GetWindowText(m_strText);
    if (m_strText.GetLength())
    {
        pDC->SetBkMode(TRANSPARENT);
        if (state & ODS_DISABLED)
        {
            rect.OffsetRect(1,1);
            pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
            pDC->DrawText(m_strText, rect, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
            rect.OffsetRect(-1,-1);
            pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
            pDC->DrawText(m_strText, rect, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
        }
        else
        {
            pDC->SetTextColor((m_crColourText == CLR_DEFAULT)? 0 : m_crColourText);
            pDC->DrawText(m_strText, rect, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
        }
    }

    // Draw focus rect
    if (state & ODS_FOCUS) 
    {
        rect.DeflateRect(1,1);
        pDC->DrawFocusRect(rect);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CColourPicker overrides

void CColourPicker::PreSubclassWindow() 
{
    ModifyStyle(0, BS_OWNERDRAW);        // Make it owner drawn
    CButton::PreSubclassWindow();
    SetWindowSize();                     // resize appropriately
}

/////////////////////////////////////////////////////////////////////////////
// CColourPicker attributes

COLORREF CColourPicker::GetColour()
{ 
    return (m_nSelectionMode == CP_MODE_TEXT)? 
        GetTextColour(): GetBkColour(); 
}

void CColourPicker::SetColour(COLORREF crColour)
{ 
    (m_nSelectionMode == CP_MODE_TEXT)? 
        SetTextColour(crColour): SetBkColour(crColour); 
}

void CColourPicker::SetBkColour(COLORREF crColourBk)
{
    m_crColourBk = crColourBk;
    if (IsWindow(m_hWnd)) RedrawWindow();
}

void CColourPicker::SetTextColour(COLORREF crColourText)
{
    m_crColourText = crColourText;
    if (IsWindow(m_hWnd)) RedrawWindow();
}

void CColourPicker::SetDefaultText(LPCTSTR szDefaultText)
{
    m_strDefaultText = (szDefaultText)? szDefaultText : _T("");
}

void CColourPicker::SetCustomText(LPCTSTR szCustomText)
{
    m_strCustomText = (szCustomText)? szCustomText : _T("");
}

/////////////////////////////////////////////////////////////////////////////
// CColourPicker implementation

void CColourPicker::SetWindowSize()
{
    // Get size dimensions of edges
    CSize MarginSize(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

    // Get size of dropdown arrow
    int nArrowWidth = max(::GetSystemMetrics(SM_CXHTHUMB), 5*MarginSize.cx);
    int nArrowHeight = max(::GetSystemMetrics(SM_CYVTHUMB), 5*MarginSize.cy);
    CSize ArrowSize(max(nArrowWidth, nArrowHeight), max(nArrowWidth, nArrowHeight));

    // Get window size
    CRect rect;
    GetWindowRect(rect);

    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rect);

    // Set window size at least as wide as 2 arrows, and as high as arrow + margins
    int nWidth = max(rect.Width(), 2*ArrowSize.cx + 2*MarginSize.cx);
    MoveWindow(rect.left, rect.top, nWidth, ArrowSize.cy+2*MarginSize.cy, TRUE);

    // Get the new coords of this window
    GetWindowRect(rect);
    ScreenToClient(rect);

    // Get the rect where the arrow goes, and convert to client coords.
    m_ArrowRect.SetRect(rect.right - ArrowSize.cx - MarginSize.cx, 
                        rect.top + MarginSize.cy, rect.right - MarginSize.cx,
                        rect.bottom - MarginSize.cy);
}

Color SetA(Color &c,	BYTE a)
{
	DWORD a1 = a;
	ARGB argb = c.GetValue();
	a1 = a1*0x1000000;
	argb = argb & 0x00ffffff;
	argb = argb | a1;
	Color c1(argb);
	return c1;
}
