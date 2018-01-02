// DlgImageContainer.cpp : implementation file
//

#include "stdafx.h"
#include "IPC.h"
#include "DlgImageContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImageContainer dialog


CDlgImageContainer::CDlgImageContainer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImageContainer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImageContainer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_vecEdge.clear();

	m_pCxImage		= NULL;
}

CDlgImageContainer::~CDlgImageContainer()
{
	if (NULL != m_pCxImage) 
	{
		delete m_pCxImage;
		m_pCxImage = NULL;
	}
}

void CDlgImageContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImageContainer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImageContainer, CDialog)
	//{{AFX_MSG_MAP(CDlgImageContainer)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImageContainer message handlers

BOOL CDlgImageContainer::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL retValue= CDialog::OnEraseBkgnd(pDC);
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc,RGB(0,0,0));
	return retValue;
}

void CDlgImageContainer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	int i;

	if (m_pCxImage) 
	{
		m_pCxImage->Draw(dc.GetSafeHdc());
	}

	m_RectangleROI.RePaint(FromHandle(m_hWnd));

	m_EdgeInteraction.RePaint(FromHandle(m_hWnd));

	if (m_RectangleROI.GetShowROI()) 
	{
		int iImageHeight = m_pCxImage->GetHeight();
		CPoint	ptTopLeft = m_RectangleROI.GetTopLeftPt();
		CPoint	ptBottomRight = m_RectangleROI.GetBottomRightPt();
		CPoint	ptROIStart(ptTopLeft.x, ptBottomRight.y);	//BottomLeft (x, y)
		CPoint	ptEdgeForScreen;
		if (m_vecEdge.size() > 0)
		{
			for(i=0; i<m_vecEdge.size(); i++)
			{
				ptEdgeForScreen.x = ptROIStart.x + m_vecEdge[i].x;
				ptEdgeForScreen.y = ptROIStart.y - m_vecEdge[i].y;
				dc.SetPixel(ptEdgeForScreen.x, ptEdgeForScreen.y, RGB(0, 255, 0));
			}
		}
	}
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgImageContainer::SetCxImage(CxImage *pCxImage)
{
	m_pCxImage = pCxImage;
}

void CDlgImageContainer::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_RectangleROI.MouseMove(FromHandle(m_hWnd), point);

	CRect rtBordor(m_RectangleROI.GetTopLeftPt(), m_RectangleROI.GetBottomRightPt());
	m_EdgeInteraction.MouseMove(FromHandle(m_hWnd), rtBordor, point, m_vecEdge);

	Invalidate(FALSE);
	
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgImageContainer::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_RectangleROI.LButtonDown(FromHandle(m_hWnd), point);

	CRect rtBordor(m_RectangleROI.GetTopLeftPt(), m_RectangleROI.GetBottomRightPt());
	m_EdgeInteraction.LButtonDown(FromHandle(m_hWnd), rtBordor, point, m_vecEdge);

	Invalidate(FALSE);
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgImageContainer::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_RectangleROI.LButtonUp(FromHandle(m_hWnd), point);

	CRect rtBordor(m_RectangleROI.GetTopLeftPt(), m_RectangleROI.GetBottomRightPt());
	m_EdgeInteraction.LButtonUp(FromHandle(m_hWnd), rtBordor, point, m_vecEdge);

	Invalidate(FALSE);
	
	CDialog::OnLButtonUp(nFlags, point);
}
