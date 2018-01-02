// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PeekPocket.h"
#include "OptionsDlg.h"
#include "PPDlg.h"

// COptionsDlg dialog
IMPLEMENT_DYNAMIC(COptionsDlg, CColoredDlg)

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CColoredDlg(COptionsDlg::IDD, pParent)
{
	m_strScanSpeed=_T("Normal");
}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CColoredDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADAPTERS_COMBO, m_adapters);
	DDX_Control(pDX, IDC_SCANSPEED_SLIDER, m_speed);
	DDX_Control(pDX, IDC_HIDE_PEERS, m_hidepeers);
	DDX_Control(pDX, IDC_HIDE_SEC, m_hidesec);
	DDX_Control(pDX, IDC_SOUND_OFF, m_soundoff);
	DDX_Text(pDX, IDC_SCANTIME, m_strScanSpeed);
	DDX_Control(pDX, IDC_FONTSIZE_SLIDER, m_fontsize);
	DDX_Control(pDX, IDC_ABOUT_BTN, m_btnAbout);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CColoredDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_HIDE_PEERS, &COptionsDlg::OnBnClickedHidePeers)
	ON_BN_CLICKED(IDC_HIDE_SEC, &COptionsDlg::OnBnClickedHideSec)
	ON_BN_CLICKED(IDC_SOUND_OFF, &COptionsDlg::OnBnClickedSoundOn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ABOUT_BTN, &COptionsDlg::OnBnClickedAboutBtn)
END_MESSAGE_MAP()

// COptionsDlg message handlers

//////////////////////////////////////////////////////////////////////////
BOOL COptionsDlg::OnInitDialog()
{
int nH;
CRect rc;
CPoint pt;
HBITMAP hBmpCh, hBmpTI, hBmpTA, hBmpL1, hBmpL2, hBmpS1, hBmpS2, hBmpP1, hBmpP2;

	CColoredDlg::OnInitDialog();

	//set the dropped-down width of the combo
	CWnd *pcombo=GetDlgItem(IDC_ADAPTERS_COMBO);
	if(pcombo!=NULL)
	{
		nH=pcombo->SendMessage(CB_GETITEMHEIGHT);
		nH*=6;  //number of visible items+2
		pcombo->GetWindowRect(&rc);
		pt.x=rc.left; pt.y=rc.top;
		ScreenToClient(&pt);
		pcombo->MoveWindow(pt.x, pt.y, rc.Width(), nH);
	}

	//init speed slider

	//first resize to 30x80 px - size of bitmap used
	m_speed.GetWindowRect(&rc);
	pt.x=rc.left; pt.y=rc.top;
	rc.right=rc.left+80;		//width
	rc.bottom=rc.top+30;		//height
	ScreenToClient(&pt);
	m_speed.MoveWindow(pt.x, pt.y, rc.Width(), rc.Height());

	//setup range
	m_speed.SetRange(0, 50);
	m_speed.SetPos(25);
	
	//setup color/bitmaps
	m_speed.SetBkgColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));

	hBmpCh=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_CHANNEL));
	hBmpTI=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_THUMBI));
	hBmpTA=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_THUMBA));
	m_speed.SetBitmaps(hBmpCh, hBmpTI, hBmpTA);

	//init fontsize slider

	//first resize to 30x80 px - size of bitmap used
	m_fontsize.GetWindowRect(&rc);
	pt.x=rc.left; pt.y=rc.top;
	rc.right=rc.left+80;		//width
	rc.bottom=rc.top+30;		//height
	ScreenToClient(&pt);
	m_fontsize.MoveWindow(pt.x, pt.y, rc.Width(), rc.Height());

	//setup range
	m_fontsize.SetRange(10, 20);
	m_fontsize.SetPos(12);

	//setup color/bitmaps
	m_fontsize.SetBkgColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));

	hBmpCh=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_CHANNEL));
	hBmpTI=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_THUMBI));
	hBmpTA=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_THUMBA));
	m_fontsize.SetBitmaps(hBmpCh, hBmpTI, hBmpTA);

	//init checkboxes
	m_hidepeers.SetCaption(_T("Show peers"), _T("Hide peers"));
	m_hidepeers.SetBkgIdleColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	m_hidepeers.SetBkgActiveColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	hBmpP1=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_PEER));
	hBmpP2=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HIDE_PEER));
	m_hidepeers.SetBitmaps(hBmpP1, hBmpP2);
	m_hidepeers.SetCheck(BST_CHECKED);

	m_hidesec.SetCaption(_T("Show secure"), _T("Hide secure"));
	m_hidesec.SetBkgIdleColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	m_hidesec.SetBkgActiveColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	hBmpL1=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_LOCK));
	hBmpL2=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_LOCK_C));
	m_hidesec.SetBitmaps(hBmpL1, hBmpL2);
	m_hidesec.SetCheck(BST_CHECKED);

	m_soundoff.SetCaption(_T("Sound on"), _T("Sound off"));
	m_soundoff.SetBkgIdleColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	m_soundoff.SetBkgActiveColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	hBmpS1=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_SND_ON));
	hBmpS2=::LoadBitmap(AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_SND_OFF));
	m_soundoff.SetBitmaps(hBmpS1, hBmpS2);

	//sound off by default
	m_soundoff.SetCheck(BST_CHECKED);

	//init about btn
	m_btnAbout.SetBkgIdleColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	m_btnAbout.SetBkgActiveColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
	m_btnAbout.SetGradientColors(GetSysColor(COLOR_ACTIVECAPTION), RGB(200, 200, 200));
	m_btnAbout.SetFlags(bfHGradient);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//handle slider events
void COptionsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
int sp;

	//is the sender a CCustomSlider?
	if(pScrollBar != NULL && pScrollBar->IsKindOf(RUNTIME_CLASS(CCustomSlider)))
	{
		//yes, which slider was it?
		switch(pScrollBar->GetDlgCtrlID())
		{
			case IDC_SCANSPEED_SLIDER:
			{
				//2000...500
				sp=2000-30*nPos;
				switch(sp/375)
				{
					case 5:
					{
						m_strScanSpeed=_T("Slowest");
						break;
					}
					case 4:
					{
						m_strScanSpeed=_T("Slow");
						break;
					}
					case 3:
					{
						m_strScanSpeed=_T("Normal");
						break;
					}
					case 2:
					{
						m_strScanSpeed=_T("Fast");
						break;
					}
					case 1:
					{
						m_strScanSpeed=_T("Fastest");
						break;
					}
				}//switch slider pos
				UpdateData(FALSE);
				CWnd *pParent;
				pParent=GetParent();
				if(pParent != NULL)
				{
					((CPPDlg *)pParent)->m_iRefreshRate=sp;
				}
				break;
			}//case scanspeed slider
			case IDC_FONTSIZE_SLIDER:
			{
				DrawListFontSizeText();
				CWnd *pParent;
				pParent=GetParent();
				if(pParent != NULL)
				{
					((CPPDlg *)pParent)->m_pScannerDlg->SetListFont(nPos);
				}
				break;
			}//case fontsize slider
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void COptionsDlg::OnPaint()
{
	CColoredDlg::OnPaint();

	DrawListFontSizeText();
}

//////////////////////////////////////////////////////////////////////////
//draw list font selection text
void COptionsDlg::DrawListFontSizeText()
{
HGDIOBJ hOldObj;
CString str;
CFont font;
CRect rc;

	CDC *pDC=GetDC();
	if(pDC != NULL)
	{
		font.CreateFont(m_fontsize.GetPos(), 0, 0, 0, FW_BOLD, FALSE /*italic*/, FALSE /*underline*/, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Tahoma")) ;

		hOldObj=pDC->SelectObject(font);

		str.Format(_T("%d"), m_fontsize.GetPos());

		//let the dialog setup colors in DC
		SendMessage(WM_CTLCOLORSTATIC, (WPARAM)pDC->GetSafeHdc(), -1);

		rc.SetRect(175, 67, 200, 92);
		pDC->FillSolidRect(rc, pDC->GetBkColor());

		//center the text
		pDC->DrawText(str, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		pDC->SelectObject(hOldObj);
		ReleaseDC(pDC);
	}
}

//////////////////////////////////////////////////////////////////////////
//set option
void COptionsDlg::OnBnClickedHidePeers()
{
CWnd *pParent;
bool bOption;

	//store option
	pParent=GetParent();
	if(pParent != NULL)
	{
		bOption=(m_hidepeers.GetCheck() == BST_CHECKED);
		((CPPDlg *)pParent)->m_bHidePeer=bOption;
	}
}

//////////////////////////////////////////////////////////////////////////
//set option
void COptionsDlg::OnBnClickedHideSec()
{
CWnd *pParent;
bool bOption;

	//store option
	pParent=GetParent();
	if(pParent != NULL)
	{
		bOption=(m_hidesec.GetCheck() == BST_CHECKED);
		((CPPDlg *)pParent)->m_bHideSecure=bOption;
	}
}

//////////////////////////////////////////////////////////////////////////
//set option
void COptionsDlg::OnBnClickedSoundOn()
{
CWnd *pParent;
bool bOption;

	//store option
	pParent=GetParent();
	if(pParent != NULL)
	{
		bOption=(m_soundoff.GetCheck() == BST_CHECKED);
		((CPPDlg *)pParent)->m_bSoundOff=bOption;
	}
}

//////////////////////////////////////////////////////////////////////////
//popup about message
void COptionsDlg::OnBnClickedAboutBtn()
{
	AfxMessageBox(_T("PeekPocket 1.0\nFree WiFi scanner\nhttp://dzolee.blogspot.com"), MB_ICONINFORMATION);
}
