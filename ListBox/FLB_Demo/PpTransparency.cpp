// PpTransparency.cpp : implementation file
//

#include "stdafx.h"
#include "demoflb.h"
#include "PpTransparency.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpTransparency property page

IMPLEMENT_DYNCREATE(CPpTransparency, CPropertyPage)

CPpTransparency::CPpTransparency() : CPropertyPage(CPpTransparency::IDD),
m_listFont(FNTLB_HAS_TOOLTIPS | FNTLB_TOOLTIPTEXT_FONT | FNTLB_TOOLTIPSELECTED | FNTLB_TRACKING_TOOLTIP | FNTLB_MRUCUSTOMLIST, _T("MruPersist"))
{
	//{{AFX_DATA_INIT(CPpTransparency)
	//}}AFX_DATA_INIT
}

CPpTransparency::~CPpTransparency()
{
}

void CPpTransparency::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpTransparency)
	DDX_Control(pDX, IDC_BUTTON1, m_btnFontChange);
	DDX_Control(pDX, IDC_BTNGRAPHIC, m_btnGraphic);
	DDX_Control(pDX, IDC_BTNCLEARSEL, m_btnClearSel);
	DDX_Control(pDX, IDC_IMAGE, m_image);
	DDX_Control(pDX, IDC_LIST, m_listFont);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpTransparency, CPropertyPage)
	//{{AFX_MSG_MAP(CPpTransparency)
	ON_BN_CLICKED(IDC_BTNCHANGEIMAGE, OnBtnChangeImage)
	ON_BN_CLICKED(IDC_BTNCLEARSEL, OnBtnClearSel)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelChangeList)
	ON_BN_CLICKED(IDC_BTNGRAPHIC, OnBtnGraphic)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpTransparency message handlers

BOOL CPpTransparency::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_listFont.Initialize();
	
	if (!AfxFontChangeSupported())
		m_btnFontChange.EnableWindow(FALSE);

	AdaptButtonsState();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPpTransparency::OnBtnChangeImage() 
{
	static UINT	resID = IDB_BITMAP0;
	switch(resID)
	{
	case IDB_BITMAP0:
		resID = IDB_BITMAP1;
		break;
	case IDB_BITMAP1:
		resID = IDB_BITMAP0;
		break;
	}
	m_image.SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance , MAKEINTRESOURCE(resID)));
	RedrawWindow();
}


void CPpTransparency::OnBtnClearSel() 
{
	m_listFont.ClearSelection();
	AdaptButtonsState();	
}

void CPpTransparency::AdaptButtonsState()
{
	if (m_listFont.GetSelectedCount()>0)
		m_btnClearSel.EnableWindow(TRUE);
	else
		m_btnClearSel.EnableWindow(FALSE);

	if (m_listFont.GetFlags() & FNTLB_GRAPHIC)
		m_btnGraphic.SetWindowText(_T("Set List style to Text"));
	else
		m_btnGraphic.SetWindowText(_T("Set List style to Graphic"));
}

void CPpTransparency::OnSelChangeList() 
{
	AdaptButtonsState();	
}

void CPpTransparency::OnBtnGraphic() 
{
	m_listFont.SetFlags(m_listFont.GetFlags() ^ FNTLB_GRAPHIC);
	AdaptButtonsState();	
}

void CPpTransparency::OnButton1() 
{
	::PostMessage(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);
}
