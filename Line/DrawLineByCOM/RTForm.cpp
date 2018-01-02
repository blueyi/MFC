// RTForm.cpp : implementation file
//

#include "stdafx.h"
#include "RTDemo.h"
#include "RTForm.h"
#include "RTDemoDoc.h"
#include "RTDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TipsPerPixel 15
static CString m_ColHead[] = 
{
	"颜色", 
	"名称", 
	"包数", 
	"单位", 
	"值"//, 
	//"Minimum", 
	//"Maximum", 
	//"Scaled Min", 
	//"Scaled Max"
};

/////////////////////////////////////////////////////////////////////////////
// CRTForm

IMPLEMENT_DYNCREATE(CRTForm, CFormView)

CRTForm::CRTForm()
	: CFormView(CRTForm::IDD)
{
	//{{AFX_DATA_INIT(CRTForm)
	//}}AFX_DATA_INIT
}

CRTForm::~CRTForm()
{
}

void CRTForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRTForm)
	DDX_Control(pDX, IDC_SLIDERPAGE, m_SliderPage);
	DDX_Control(pDX, IDC_RTGRID, m_RTGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRTForm, CFormView)
	//{{AFX_MSG_MAP(CRTForm)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTForm diagnostics

#ifdef _DEBUG
void CRTForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CRTForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

CWnd* CRTForm::GetRTDemoView()
{
	CSplitterWnd* pWnd = (CSplitterWnd*)GetParent();
	return pWnd->GetPane(0, 0);
}

void CRTForm::MoveWindows()
{
	CRect rect;
	GetClientRect(rect);

	CWnd* pView = GetRTDemoView();
	RECT& plotRect = ((CRTDemoView*)pView)->GetGraphRect();
	if (plotRect.right - plotRect.left > 0)
	{
		m_sRect.left	= plotRect.left - 10;
		m_sRect.right	= plotRect.right + 10;
		m_SliderPage.MoveWindow(m_sRect);
	}
	else
	{
		m_sRect.left	= rect.left;
		m_sRect.right	= rect.right;
		m_SliderPage.MoveWindow(m_sRect);
	}

	rect.top = m_sRect.top + m_sRect.Height();
	m_RTGrid.MoveWindow(rect);
}

void CRTForm::InitialSlider(int nMin, int nMax, int nPage, int nPos, BOOL nFlag)
{
	m_SliderPage.SetRange(nMin, nMax, TRUE);
	//m_SliderPage.SetTic(nMax - nMin);
	m_SliderPage.SetPageSize(nPage);
	m_SliderPage.SetPos(m_SliderPage.GetPos() + 1);
	m_SliderPage.EnableWindow(TRUE);
}

void CRTForm::RedrawGrid()
{
	CRTDemoView* pView = (CRTDemoView*)GetRTDemoView();
	long Rows = pView->m_Graph.m_LineArray.GetSize() + 1;
	m_RTGrid.SetRows(Rows);
	CString str;
	m_RTGrid.SetCol(1);
	for(long row = 1; row <Rows; row ++)
	{
		m_RTGrid.SetRow(row);

		// column 0 : index
		str.Format("%d", row);
		m_RTGrid.SetTextMatrix(row, 0, str);

		// column 1 : color
		m_RTGrid.SetCellBackColor(pView->m_Graph.m_LineArray[row - 1].m_nColor);

		// column 2 : name
		m_RTGrid.SetTextMatrix(row, 2, pView->m_Graph.m_LineArray[row - 1].m_sName.GetChar());

		// column 3 : description
		m_RTGrid.SetTextMatrix(row, 3, pView->m_Graph.m_LineArray[row - 1].m_sDescription.GetChar());

		// column 4 : unit
		m_RTGrid.SetTextMatrix(row, 4, pView->m_Graph.m_LineArray[row - 1].m_sUnit.GetChar());
		
		// column 6 : minimum value
		//str.Format("%.f", pView->m_Graph.m_LineArray[row - 1].m_dMin);
		//m_RTGrid.SetTextMatrix(row, 6, str);

		// column 7 : maximum value
		//str.Format("%.f", pView->m_Graph.m_LineArray[row - 1].m_dMax);
		//m_RTGrid.SetTextMatrix(row, 7, str);

		// column 8 : scaled minimum value
		//str.Format("%.f", pView->m_Graph.m_LineArray[row - 1].m_dScaleLow);
		//m_RTGrid.SetTextMatrix(row, 8, str);

		// column 9 : scaled maximum value
		//str.Format("%.f", pView->m_Graph.m_LineArray[row - 1].m_dScaleHigh);
		//m_RTGrid.SetTextMatrix(row, 9, str);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRTForm message handlers

void CRTForm::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if(::IsWindow(m_RTGrid.m_hWnd) && ::IsWindow(m_SliderPage.m_hWnd))
		MoveWindows();
}

void CRTForm::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_SliderPage.SetType(m_SliderPage.sType::PAGE);
	m_SliderPage.GetClientRect(m_sRect);
	m_SliderPage.SetRange(0, 1, TRUE);
	//m_SliderPage.SetTic(1);
	m_SliderPage.SetPos(1);
	m_SliderPage.SetPageSize(1);
	m_SliderPage.EnableWindow(FALSE);
	MoveWindows();

	m_RTGrid.SetColWidth(0, 30  * TipsPerPixel);
	m_RTGrid.SetColWidth(1, 70  * TipsPerPixel);
	m_RTGrid.SetColWidth(2, 100 * TipsPerPixel);
	m_RTGrid.SetColWidth(3, 150 * TipsPerPixel);
	m_RTGrid.SetColWidth(4, 70  * TipsPerPixel);
	m_RTGrid.SetColWidth(5, 70  * TipsPerPixel);
	//m_RTGrid.SetColWidth(6, 70  * TipsPerPixel);
	//m_RTGrid.SetColWidth(7, 70  * TipsPerPixel);
	//m_RTGrid.SetColWidth(8, 70  * TipsPerPixel);
	//m_RTGrid.SetColWidth(9, 70  * TipsPerPixel);

	long Cols = m_RTGrid.GetCols();
	m_RTGrid.SetColAlignment(0, 4); // center alignment
	for(long col = 1; col <Cols; col ++)
	{
		m_RTGrid.SetColAlignment(col, 4);
		m_RTGrid.SetTextMatrix(0, col, m_ColHead[col-1]);
	}

	RedrawGrid();


}



