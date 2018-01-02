// GradualChangeView.cpp : implementation of the CGradualChangeView class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "GradualChange.h"

#include "GradualChangeDoc.h"
#include "GradualChangeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BMP_SIZE 1440000

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView

IMPLEMENT_DYNCREATE(CGradualChangeView, CView)

BEGIN_MESSAGE_MAP(CGradualChangeView, CView)
	//{{AFX_MSG_MAP(CGradualChangeView)
	ON_COMMAND(ID_MYPLAY, OnMyplay)
	ON_WM_TIMER()
	ON_COMMAND(ID_MYSTOP, OnMystop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView construction/destruction

CGradualChangeView::CGradualChangeView()
{
	// TODO: add construction code here
	m_pb1 = NULL;
	m_pb2 = NULL;
	m_pb3 = NULL;
}

CGradualChangeView::~CGradualChangeView()
{
	//如果没有正常释放堆空间则在程序退出前释放之
	if(m_pb1 != NULL)
	{
		free(m_pb1);
	}
	if(m_pb2 != NULL)
	{
		free(m_pb2);
	}
	if(m_pb3 != NULL)
	{
		free(m_pb3);
	}
}

BOOL CGradualChangeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView drawing

void CGradualChangeView::OnDraw(CDC* pDC)
{
	CGradualChangeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView diagnostics

#ifdef _DEBUG
void CGradualChangeView::AssertValid() const
{
	CView::AssertValid();
}

void CGradualChangeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGradualChangeDoc* CGradualChangeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGradualChangeDoc)));
	return (CGradualChangeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeView message handlers

void CGradualChangeView::OnMyplay() 
{
	// TODO: Add your command handler code here
	if(m_pb1 == NULL)
	{
		//初始化工作，m_nCase为1表示当前要演示第一幅图片的淡入
		m_nCount = 0;
		m_nCase = 1;

		//读取bmp文件头信息
		CFile f1, f2;
		f1.Open("bmp1.bmp", CFile::modeRead, NULL);
		f1.Seek(14, CFile::begin);
		f1.Read(&m_header, 40);
		f2.Open("bmp2.bmp", CFile::modeRead, NULL);
		f2.Seek(14, CFile::begin);
		f2.Read(&m_header, 40);

		//动态分配空间，定义宏#define BMP_SIZE 1440000
		m_pb1 = (BYTE *)malloc(BMP_SIZE);
		m_pb2 = (BYTE *)malloc(BMP_SIZE);
		m_pb3 = (BYTE *)malloc(BMP_SIZE);
	
		//读取bmp文件的数据区数据
		f1.ReadHuge(m_pb1, BMP_SIZE);
		f1.Close();
		f2.ReadHuge(m_pb2, BMP_SIZE);
		f2.Close();

		//开启计时器，命名为1，每100毫秒中断一次
		SetTimer(1, 100, NULL);
	}
}

void CGradualChangeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//还没有显示第二幅图片则显示第二幅图片
	if(m_nCount >= 64 && m_nCase == 1)
	{
		m_nCase = 2;
		m_nCount = 0;
	}
	//两幅图片都显示过了
	else if( m_nCount >= 64 && m_nCase == 3)
	{
		OnMystop();
		MessageBox("演示完毕", "完毕", MB_OK);
	}
	else
	{
		//显示第一幅图片
		if(m_nCase == 1)
		{
			m_nCount++;
			for(int i = 0; i < BMP_SIZE; i++)
				m_pb3[i] = m_nCount * m_pb1[i]/64;

			StretchDIBits(GetDC()->m_hDC, 0, 0, 800, 600, 0, 0, 800, 600, m_pb3, 
							((BITMAPINFO*)(&m_header)), DIB_RGB_COLORS, SRCCOPY);
		
		}
	
		else if(m_nCase == 2)
		{
			//显示第二幅图片，并消隐第一幅图片
			m_nCount++;
			for(int i = 0; i < BMP_SIZE; i++)
				m_pb3[i] = ((64 - m_nCount) * m_pb1[i] + m_nCount * m_pb2[i]) / 64;

			StretchDIBits(GetDC()->m_hDC, 0, 0, 800, 600, 0, 0, 800, 600, m_pb3, 
							((BITMAPINFO*)(&m_header)), DIB_RGB_COLORS, SRCCOPY);

			//如果完全消隐了，m_nCase值变为3
			if(m_nCount >= 64)
				m_nCase = 3;
		}
	}
}

void CGradualChangeView::OnMystop() 
{
	// TODO: Add your command handler code here

	//释放堆空间
	if(m_pb1 != NULL)
	{
		free(m_pb1);
		m_pb1 = NULL;
	}
	if(m_pb2 != NULL)
	{
		free(m_pb2);
		m_pb2 = NULL;
	}
	if(m_pb3 != NULL)
	{
		free(m_pb3);
		m_pb3 = NULL;
	}

	//关闭计时器
	KillTimer(1);
}
