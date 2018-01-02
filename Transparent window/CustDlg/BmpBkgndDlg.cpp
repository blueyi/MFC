// BmpBkgndDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustDlg.h"
#include "BmpBkgndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpBkgndDlg dialog


CBmpBkgndDlg::CBmpBkgndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBmpBkgndDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBmpBkgndDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_HollowBrush.CreateStockObject(HOLLOW_BRUSH);
	m_BkGndBmp.LoadBitmap(IDB_BMP_BKGND);
}

CBmpBkgndDlg::~CBmpBkgndDlg()
{
	m_HollowBrush.DeleteObject();
	m_BkGndBmp.DeleteObject();
}

void CBmpBkgndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBmpBkgndDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBmpBkgndDlg, CDialog)
	//{{AFX_MSG_MAP(CBmpBkgndDlg)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpBkgndDlg message handlers

HBRUSH CBmpBkgndDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_BTN || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)m_HollowBrush;
	}
	
	pDC->SetTextColor(RGB(0,0,255));
	pDC->SetBkMode(TRANSPARENT);
	return hbr;
}

BOOL CBmpBkgndDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect rcClient;
	GetClientRect(&rcClient);
	BITMAP bm;
	m_BkGndBmp.GetBitmap(&bm);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBmp = memDC.SelectObject(&m_BkGndBmp);
	pDC->StretchBlt(0,0,rcClient.Width(),rcClient.Height(),&memDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	return TRUE;
	
//	return CDialog::OnEraseBkgnd(pDC);
}
