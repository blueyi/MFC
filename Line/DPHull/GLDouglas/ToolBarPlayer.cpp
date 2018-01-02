// ToolBarPlayer.cpp: implementation of the CToolBarShrink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToolBarPlayer.h"
#include "resource.h"
#include "GLDouglasDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE( CToolBarShrink,CToolBarEx);

BEGIN_MESSAGE_MAP(CToolBarShrink, CToolBarEx)
	//{{AFX_MSG_MAP(CToolBarShrink)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CToolBarShrink::CToolBarShrink()
: CToolBarEx(), m_pFrame(NULL),m_dShrinkRatio(0.1), m_pShrinkSlider(NULL)
{
}

void CToolBarShrink::Create()
{
	CRect tsrc(0,0,150,20);
	m_pShrinkSlider= new CSliderCtrl();	
	m_pShrinkSlider->Create(WM_HSCROLL | TBS_HORZ, tsrc, this, ID_SHRINK_SLIDER);
	InsertControl(m_pShrinkSlider, tsrc, ID_SHRINK_SLIDER);
	m_pShrinkSlider->SetRange(1,100);
	m_pShrinkSlider->SetPos((int)floor(m_dShrinkRatio*100));
	m_pShrinkSlider->SetTicFreq(10);
}

CToolBarShrink::~CToolBarShrink()
{
	if (m_pShrinkSlider)
	{
		delete m_pShrinkSlider;
	}
}

void CToolBarShrink::Update(double dShrinkRatio)
{
	m_dShrinkRatio = __max(0, __min( 1, dShrinkRatio));

	m_pShrinkSlider->SetPos( (int)floor(dShrinkRatio*100) );
}

void CToolBarShrink::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_dShrinkRatio=__max(0, __min( 1, m_pShrinkSlider->GetPos()/100.0));
	
	ASSERT(m_pFrame);
	CGLDouglasDoc* pDoc = (CGLDouglasDoc*) m_pFrame->GetActiveDocument();
	ASSERT(pDoc);

	pDoc->SetShrink( m_dShrinkRatio);
	m_pFrame->InvalidateRect(NULL,FALSE);

	CToolBarEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
