// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MyDialog.h"
#include "Dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialog dialog

CMyDialog::CMyDialog(const UINT IDD,CWnd* pParent,LPCTSTR pBmpName)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Initialize();
	if((pBmpName != NULL)&&LoadBmp(pBmpName))
		m_nBackStyle = BACK_STYLE_BITMAP;
}

CMyDialog::~CMyDialog()
{
	Empty();
}
void CMyDialog::Initialize()
{
	m_pDib			= NULL;
	m_pBackBrush	= NULL;
	m_nBackStyle	= BACK_STYLE_NORMAL;
	m_nBmpStyle		= BMP_STYLE_ORIGIN;
}
void CMyDialog::Empty()
{
	if(m_pDib != NULL)
		delete m_pDib;
	if(m_pBackBrush != NULL)
		delete m_pBackBrush;
}
BOOL CMyDialog::LoadBmp(LPCTSTR pBmpName)
{
	if(m_pDib != NULL)
		delete m_pDib;
	m_pDib = new CDib;
	if(!m_pDib->LoadFromFile(pBmpName))
	{
		delete m_pDib;
		m_pDib = NULL;
		return FALSE;
	}
	else
		return TRUE;
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	//{{AFX_MSG_MAP(CMyDialog)
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialog message handlers

BOOL CMyDialog::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);
	rect -= CPoint(rect.left,rect.top);
	switch(m_nBackStyle)
	{
	//正常显示
	case BACK_STYLE_NORMAL:
		return CDialog::OnEraseBkgnd(pDC);
		break;
	//以位图为背景
	case BACK_STYLE_BITMAP:
		if(m_pDib)
		{
			switch(m_nBmpStyle)
			{
				//按原大小在左上角显示
				case BMP_STYLE_ORIGIN:
				{
					CDialog::OnEraseBkgnd(pDC);	
					ShowDib(pDC,m_pDib,rect,FALSE);
					return TRUE;
					break;
				}
				//拉伸显示
				case BMP_STYLE_STRETCH:
				{
					ShowDib(pDC,m_pDib,rect,TRUE);
					return TRUE;
					break;
				}
				//平铺显示
				case BMP_STYLE_TILE:
				{
					int bmWidth = m_pDib->Width();
					int bmHeight = m_pDib->Height();
					CRect showRect;
					showRect.left = rect.left;
					showRect.top =  rect.top;
					showRect.right = rect.left + bmWidth;
					showRect.bottom = rect.top + bmHeight;
					for(int i=0;i<= rect.Width()/bmWidth; i++)
						for(int j=0;j<= rect.Height()/bmHeight;j++)
							ShowDib(pDC,m_pDib,showRect+CPoint(i*bmWidth,j*bmHeight),FALSE);
					break;
				}
			}
			return FALSE;
		}
		break;
	case BACK_STYLE_COLORED:
		{
			pDC->FillRect(&rect,m_pBackBrush);
			return FALSE;
			break;
		}
	}
	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CMyDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CMyDialog::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	UINT nHitTest = CDialog::OnNcHitTest (point);
	return (nHitTest == HTCLIENT)? HTCAPTION: nHitTest;
}

void CMyDialog::SetBackStyle(int nBackStyle)
{
	ASSERT( nBackStyle == BACK_STYLE_NORMAL || 
		nBackStyle == BACK_STYLE_BITMAP || 
		nBackStyle == BACK_STYLE_COLORED);
	m_nBackStyle = nBackStyle;
}
void CMyDialog::SetBackBrush(COLORREF color)
{
	if(m_pBackBrush!=NULL)
		delete m_pBackBrush;
	m_pBackBrush = new CBrush(color);
}
void CMyDialog::SetBmpStyle(int nBmpStyle)
{
	ASSERT( nBmpStyle == BMP_STYLE_ORIGIN || 
		nBmpStyle == BMP_STYLE_STRETCH || 
		nBmpStyle == BMP_STYLE_TILE);
	m_nBmpStyle = nBmpStyle;
}