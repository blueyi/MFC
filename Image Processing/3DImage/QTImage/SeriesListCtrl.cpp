// SeriesListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "QTImage.h"
#include "SeriesListCtrl.h"
#include "DrawSeries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesListCtrl

CSeriesListCtrl::CSeriesListCtrl()
{
	m_bMeasured=FALSE;

	m_clSelected=RGB(249,177,142);
	m_clUnselected=RGB(232,232,232);

	LOGFONT lf;
	lf.lfHeight=-15;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=0;
	lf.lfUnderline=0;
	lf.lfStrikeOut=0;
	lf.lfCharSet=DEFAULT_CHARSET; //ANSI_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_ROMAN;
	strcpy(lf.lfFaceName, "Tahoma");

	m_font.CreateFontIndirect(&lf);

	m_pManager=NULL;

	m_bSized=FALSE;
}

CSeriesListCtrl::~CSeriesListCtrl()
{
	m_font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CSeriesListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSeriesListCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeriesListCtrl message handlers
void CSeriesListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
	LPDRAWITEMSTRUCT lpDIS=lpDrawItemStruct;
	
	// drawn device context for draw menu
	CDC dc;
	dc.Attach(lpDIS->hDC);

	// rect region of device context
	CRect rect=CRect(lpDIS->rcItem);	

	BOOL bFocus=(GetFocus()==this);
	int nItem=lpDrawItemStruct->itemID;
	// get item data

	_TCHAR szBuff[MAX_PATH];
	LVITEM lvi;
	lvi.mask=LVIF_TEXT | HDI_WIDTH | LVIF_STATE;
	lvi.iItem=nItem;
	lvi.iSubItem=0;
	lvi.pszText=szBuff;
	lvi.cchTextMax=sizeof(szBuff);
	lvi.stateMask=0xFFFF;		// get all state flags

	HDITEM hdi;
	hdi.mask = HDI_WIDTH;

	GetItem(&lvi);

	BOOL bSelected=(bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
	bSelected=bSelected || (lvi.state & LVIS_DROPHILITED);

	if(bSelected)
	{
		dc.FillSolidRect(&rect,m_clSelected); //206,231,231));

	}else
	{
		dc.FillSolidRect(&rect,m_clUnselected);
	}

	

	CFont *pOldFont=dc.SelectObject(&m_font);

	CDrawSeries drawImage;
	drawImage.EnableAutoWindowLevel();
	if(m_pManager)
	{
		CRect rc=rect;
		rc.top=rc.bottom-105;
		rc.bottom=rc.top+100;
		rc.left=(rc.Width()-100)/2;
		rc.right=rc.left+100;
		drawImage.Draw(&dc,rc,m_pManager->GetAt(nItem));
	}
	//dc.DrawText(szBuff,-1,&rect,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
		

	dc.SelectObject(pOldFont);
	dc.Detach();
}


void CSeriesListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	lpMIS->itemHeight=150;
	
}

void CSeriesListCtrl::SetSeriesManager(CSeriesManager *pManager)
{
	m_pManager=pManager;
}

void CSeriesListCtrl::AddSeries()
{
	while(GetItemCount()<m_pManager->Count())
	{
		InsertItem(0, "ss");
	}
	//Invalidate(FALSE);
}


