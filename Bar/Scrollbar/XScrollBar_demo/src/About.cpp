#include "stdafx.h"
#include "About.h"

#define BACKGROUND_COLOR1	RGB(255,237,210)
#define BACKGROUND_COLOR2	RGB(255,203,125)
#define BACKGROUND_COLOR3	RGB(255,230,190)

#pragma message("automatic link to msimg32.lib")
#pragma comment(lib, "msimg32.lib")		// needed for GradientFill()

//=============================================================================
BEGIN_MESSAGE_MAP(CAboutDlg, ABOUT_BASE_CLASS)
//=============================================================================
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//=============================================================================
CAboutDlg::CAboutDlg() : ABOUT_BASE_CLASS(CAboutDlg::IDD)
//=============================================================================
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_brush.CreateSolidBrush(BACKGROUND_COLOR3);
}

//=============================================================================
CAboutDlg::~CAboutDlg()
//=============================================================================
{
	if (m_brush.GetSafeHandle())
		m_brush.DeleteObject();
}

//=============================================================================
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//=============================================================================
{
	ABOUT_BASE_CLASS::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_EMAIL, m_ctrlEmail);
	//}}AFX_DATA_MAP
}

//=============================================================================
BOOL CAboutDlg::OnInitDialog()
//=============================================================================
{
	ABOUT_BASE_CLASS::OnInitDialog();
		
	CString strMailTo = _T("");
	strMailTo.LoadString(IDS_MAILTO);

	m_ctrlEmail.SetURL(strMailTo);
	m_ctrlEmail.SetBackgroundColour(BACKGROUND_COLOR2);
	m_ctrlEmail.SetColours(RGB(0,0,255), RGB(0,0,255), RGB(0,0,255));

	CenterWindow();

	return TRUE;
}

//=============================================================================
HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//=============================================================================
{
	// must call base class to get hyperlink colors drawn
	HBRUSH hbr = ABOUT_BASE_CLASS::OnCtlColor(pDC, pWnd, nCtlColor);
	 
	if ((pWnd->m_hWnd != GetDlgItem(IDC_HANS)->m_hWnd) && (nCtlColor == CTLCOLOR_STATIC))
	{
		pDC->SetBkMode(TRANSPARENT);      // Set the Background Mode to TRANSPARENT  
		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH); // return handle to a NULL brush  
	}
	else
	{
		hbr = m_brush;
	}
	return hbr;
}

//=============================================================================
BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC) 
//=============================================================================
{
	CRect rectClient;
	GetClientRect(&rectClient);

#pragma warning(disable : 4310)

	TRIVERTEX vert[2];
	vert[0].x      = 0;
	vert[0].y      = 0;
	vert[0].Red    = (COLOR16) (GetRValue(BACKGROUND_COLOR1) << 8);
	vert[0].Green  = (COLOR16) (GetGValue(BACKGROUND_COLOR1) << 8);
	vert[0].Blue   = (COLOR16) (GetBValue(BACKGROUND_COLOR1) << 8);
	vert[0].Alpha  = 0x0000;

	vert[1].x      = rectClient.right;
	vert[1].y      = rectClient.bottom; 
	vert[1].Red    = (COLOR16) (GetRValue(BACKGROUND_COLOR2) << 8);
	vert[1].Green  = (COLOR16) (GetGValue(BACKGROUND_COLOR2) << 8);
	vert[1].Blue   = (COLOR16) (GetBValue(BACKGROUND_COLOR2) << 8);
	vert[1].Alpha  = 0x0000;

	GRADIENT_RECT rect;
	rect.UpperLeft  = 0;
	rect.LowerRight = 1;

	::GradientFill(pDC->m_hDC, vert, 2, &rect, 1, GRADIENT_FILL_RECT_V);

	return TRUE;
	//return ABOUT_BASE_CLASS::OnEraseBkgnd(pDC);
}
