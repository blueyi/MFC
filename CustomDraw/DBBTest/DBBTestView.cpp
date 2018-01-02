// DBBTestView.cpp : implementation of the CDBBTestView class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "DBBTest.h"

#include "DBBTestDoc.h"
#include "DBBTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView

IMPLEMENT_DYNCREATE(CDBBTestView, CView)

BEGIN_MESSAGE_MAP(CDBBTestView, CView)
	//{{AFX_MSG_MAP(CDBBTestView)
	ON_WM_TIMER()
	ON_COMMAND(ID_TEST_NORMAL, OnTestNormal)
	ON_COMMAND(ID_TEST_DBB, OnTestDbb)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView construction/destruction

CDBBTestView::CDBBTestView()
{
	// TODO: add construction code here
	m_bStart = FALSE;
	m_bUseDBB = FALSE;
	m_nRadius = 1;
}

CDBBTestView::~CDBBTestView()
{
}

BOOL CDBBTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView drawing

void CDBBTestView::OnDraw(CDC* pDC)
{
	CDBBTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView printing

BOOL CDBBTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDBBTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDBBTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView diagnostics

#ifdef _DEBUG
void CDBBTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDBBTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBBTestDoc* CDBBTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBBTestDoc)));
	return (CDBBTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView message handlers

void CDBBTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// 初始化和双缓冲相关的要素
	InitialDBB();

	// 设置定时器
	SetTimer(1, 100, NULL);
}

void CDBBTestView::OnTimer(UINT nIDEvent) 
{
	if(!m_bStart)	return;	// 是否开始?

	// 响应定时器事件
	
	if(m_nRadius < 16)		// 半径控制
	{
		m_nRadius++;
	}
	else
	{
		m_nRadius = 0;
	}

	// 使用不同的绘图方式
	if(!m_bUseDBB)
	{
		DrawManyCircle();
	}
	else
	{
		DrawManyCircleUseDBB();
	}

	CView::OnTimer(nIDEvent);
}


void CDBBTestView::DrawManyCircle()
{
	// 在View内画很多的圆

	CDC *pdcView = this->GetDC();						// 得到View的DC

	CRect rt;
	this->GetClientRect(&rt);							// 绘图区域

	pdcView->FillSolidRect(&rt, 0x00FFFFFF);			// 先拿白色抹去上一次绘制的图形

	// 画圆
	for(int i = 0; i < rt.Width() - 1; i+= 16)
	{
		for(int j = 0; j < rt.Height() - 1; j+= 16)
		{
			pdcView->Ellipse(i, j, i + m_nRadius, j + m_nRadius);
		}
	}

	this->ReleaseDC(pdcView);							// 释放view的设备环境
}


void CDBBTestView::DrawManyCircleUseDBB()
{
	// 在View内用双缓冲画很多的圆

	CDC *pdcView = this->GetDC();

	CRect rt;
	this->GetClientRect(&rt);

	m_dcMemory.FillSolidRect(&rt, 0x00FFFFFF);			// 白色填充, 注意,这次是画在内存设备环境上

	// 画圆
	for(int i = 0; i < rt.Width() - 1; i+= 16)
	{
		for(int j = 0; j < rt.Height() - 1; j+= 16)
		{
			m_dcMemory.Ellipse(i, j, i + m_nRadius, j + m_nRadius);
		}
	}

	// 一次性的将内存设备环境上绘制完毕的图形"贴"到屏幕上
	pdcView->BitBlt(0, 0, rt.Width(), rt.Height(), &m_dcMemory, 0, 0, SRCCOPY);

	this->ReleaseDC(pdcView);							// 释放view的设备环境


}

// 初始化和双缓冲相关的要素
void CDBBTestView::InitialDBB()
{
	CRect rt;
	this->GetClientRect(&rt);

	// 为屏幕DC创建兼容的内存DC
	if(!m_dcMemory.CreateCompatibleDC(NULL))				
	{														
		::PostQuitMessage(0);
	}	

	// 创建位图
	m_Bmp.CreateCompatibleBitmap(&m_dcMemory, rt.Width(), rt.Height());

	// 相当于选择画布
	::SelectObject(m_dcMemory.GetSafeHdc(), m_Bmp);			
	
}

void CDBBTestView::OnTestNormal() 
{
	// 使用普通绘图模式
	m_bUseDBB = FALSE;

	m_bStart = TRUE;
}

void CDBBTestView::OnTestDbb() 
{
	// 使用双缓冲模式
	m_bUseDBB = TRUE;
	
	m_bStart = TRUE;

}
