//

#include "stdafx.h"
//#include "svizres.h"
#include "HatchWellBtn.h"
//#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSVizHatchWell

#define INVALID_HATCH -1
/////////////////////////////////////////////////////////////////////////////
CString CSVizHatchWell::m_hatchName[] = 
{
    "Horizontal",
    "Vertical",
    "ForwardDiagonal",
	"BackwardDiagonal",
	"Cross",
	"???",
	"???",
	"???",
	"???",
	"???",

	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",

	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",

	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",

	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",
	"???",

	"???",
	"???",
	"???",
	"No"
};

IMPLEMENT_DYNCREATE(CSVizHatchWell, CSVizWellCtrl)

/////////////////////////////////////////////////////////////////////////////
// CSVizHatchWell
CSVizHatchWell::CSVizHatchWell() : CSVizWellCtrl()
{
    Initialise();
	
}

void CSVizHatchWell::Initialise()
{
	CSVizWellCtrl::Initialise();
    m_nNumWells		 = 53;
	m_nNumColumns	 = 9;
    m_nBoxSize.cx    = 30;
    m_nBoxSize.cy    = 30;
}

CSVizHatchWell::~CSVizHatchWell()
{
}


BEGIN_MESSAGE_MAP(CSVizHatchWell, CSVizWellCtrl)
    //{{AFX_MSG_MAP(CSVizHatchWell)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




void CSVizHatchWell::DrawCellContent(CDC* pDC, int nIndex, CRect rect, BYTE state)
{
	Graphics graphics(pDC->m_hDC);

	Rect theRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 

	HatchBrush hBrush((HatchStyle)nIndex, m_foreColor,m_backColor);

	graphics.FillRectangle(&hBrush,theRect);

}


