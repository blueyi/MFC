// IGfxTestView.cpp : implementation of the CIGfxTestView class
//

#include "stdafx.h"
#include "IGfxTest.h"

#include "IGfxTestDoc.h"
#include "IGfxTestView.h"

#include "GDIpInterface.h"
#include "SVGInterface.h"
#include "EPSInterface.h"

#include <math.h>
#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestView

IMPLEMENT_DYNCREATE(CIGfxTestView, CView)

BEGIN_MESSAGE_MAP(CIGfxTestView, CView)
	//{{AFX_MSG_MAP(CIGfxTestView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_TEST_TOMETAFILE, OnTestTometafile)
	ON_COMMAND(ID_TEST_MULTIOUPUT, OnTestMultiouput)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestView construction/destruction

CIGfxTestView::CIGfxTestView()
{
	m_pInterface = new CGDIpInterface();
}

CIGfxTestView::~CIGfxTestView()
{
}

BOOL CIGfxTestView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

void TestArrow(CGfxInterface& wr)
{	
	double llx=0;
	double lly=0;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;

	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);

	// Testing simple arrow
	wr.DrawArrow(llx+w*0.5, lly+h*0.5, w*0.4, h*0.4,1,6,7);
	wr.DrawArrow(llx+w*0.5, lly+h*0.4, -w*0.2, -h*0.1, 0,10,15,false);
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}

void TestLine(CGfxInterface& wr)
{
	double llx=0.25;
	double lly=0;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);
	// Testing simple line
	// adding a line.
	wr.DrawLine(llx+w*0.1, lly+h*0.1, llx+w*0.9, lly+h*0.9);
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}


void TestLineStrip(CGfxInterface& wr)
{
	double llx=0.5;
	double lly=0;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);
		
	// testing line strip. (open)
	int i;
	const int n=15;
	double pX[n];
	double pY[n];
	for (i=0;i<n;i++)
	{
		pX[i]=llx+i*w/(n-1)/2;
		pY[i]=(ury+lly)/2.0*((1+2/3.0*sin(i/(double)(n-1)*3.14)));
	}
	wr.DrawLineStrip(n,pX,pY);
	wr.DrawTextCenter(pX[n/2],pY[n/2],"Line strip (open)");
	
	// testing line strip. (closed)
	for (i=0;i<n;i++)
	{
		pX[i]=llx+w*0.3+w/8.0*cos(i/(double)(n-1)*3.14);
		pY[i]=(ury+lly)/4.0*(1+3/5.0*pow(sin(i/(double)(n-1)*3.14),2));
	}
	wr.DrawLineStrip(n,pX,pY,false);
	wr.DrawTextCenter(pX[n/2],pY[n/2],"Line strip (closed)");
	
	for (i=0;i<n;i++)
	{
		pX[i]=llx+w*0.7+w/8.0*cos(i/(double)(n-1)*3.14);
		pY[i]=lly+h*0.5*sin(i/(double)(n-1)*3.14);
	}
	wr.SetFillColor(0.5,0.5,1,0.8);
	wr.DrawLineStrip(n,pX,pY,false,true);
	wr.DrawTextCenter(pX[n/2],pY[n/2],"Line strip (closed and filled)");
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}

void TestStepStrip(CGfxInterface& wr)
{
	double llx=0.75;
	double lly=0;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;

	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);
	
	// testing line strip. (open)
	int i;
	const int n=15;
	double pX[n];
	double pY[n];
	for (i=0;i<n;i++)
	{
		pX[i]=llx+i*w/(n-1)/2;
		pY[i]=(ury+lly)/2.0*((1+2/3.0*sin(i/(double)(n-1)*3.14)));
	}
	wr.DrawStepStrip(n,pX,pY);
	wr.DrawTextCenter(pX[n/2],pY[n/2],"Step strip (open)");
	
	// testing line strip. (closed)
	for (i=0;i<n;i++)
	{
		pX[i]=llx+w*0.3+w/8.0*cos(i/(double)(n-1)*3.14);
		pY[i]=(ury+lly)/4.0*(1+3/5.0*pow(sin(i/(double)(n-1)*3.14),2));
	}
	wr.DrawStepStrip(n,pX,pY,false);
	wr.DrawTextCenter(pX[n/2],pY[n/2],"Step strip (closed)");

	for (i=0;i<n;i++)
	{
		pX[i]=llx+w*0.7+w/8.0*cos(i/(double)(n-1)*3.14);
		pY[i]=lly+h*0.1+h*0.5*sin(i/(double)(n-1)*3.14);
	}

	wr.SetFillColor(0.5,0.5,1,0.8);
	wr.DrawStepStrip(n,pX,pY,false,true);
	wr.DrawTextCenter(pX[n/2],pY[n/2],"Step strip (closed and filled)");
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}


void TestGraphicState(CGfxInterface& wr)
{
	double llx=0;
	double lly=0.25;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);
	// setting font for text
	wr.SetFont(10);

	double x;
	// Testing linewidth
	x=llx+w*0.05;
	wr.DrawTextLeft(x, lly+w*0.6,"Line width");
	wr.SetLineWidth(1);
	wr.DrawLine(x, lly, x, lly+w*0.5);
	x+=w*0.1;
	wr.SetLineWidth(2);
	wr.DrawLine(x, lly, x, lly+w*0.5);
	x+=w*0.1;
	wr.SetLineWidth(4);
	wr.DrawLine(x, lly, x, lly+w*0.5);
	
	// Testing color
	x+=w*0.15;
	wr.SetColor(1,0,0);
	wr.DrawTextLeft(x, lly+w*0.6,"Color");
	wr.SetLineWidth(2);
	wr.SetColor(1,0,0);
	wr.DrawLine(x, lly, x, lly+w*0.5);
	x+=w*0.1;
	wr.SetColor(0,0,1);
	wr.DrawLine(x, lly, x, lly+w*0.5);
	x+=w*0.1;
	wr.SetColor(0.8,0.8,0);
	wr.DrawLine(x, lly, x, lly+w*0.5);
	
	// Testing dash
	x+=w*0.15;
	wr.SetColor(0,0,0);
	wr.DrawTextLeft(x, lly+w*0.6,"Dash");
	wr.SetDash("4 1");
	wr.DrawLine(x, lly, x, lly+w*0.5);
	x+=w*0.1;
	wr.SetDash("4 4 1");
	wr.DrawLine(x, lly, x, lly+w*0.5);
	x+=w*0.1;
	wr.SetDash("2 2");
	wr.DrawLine(x, lly, x, lly+w*0.5);
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}


void TestGrid(CGfxInterface& wr)
{
	double llx=0.25;
	double lly=0.25;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);

	wr.SetDash("1 3");
	wr.SetLineWidth(1.5);
	wr.DrawGridHor(llx, urx, lly, (ury+lly)/2, (ury-lly)/15);		
	wr.SetDash("3 1 3");
	wr.SetLineWidth(2);
	wr.DrawGridVer(llx, urx, (ury+lly)/2, ury, (urx-llx)/20);
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}

void TestShapes(CGfxInterface& wr)
{
	double llx=0.5;
	double lly=0.25;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);

	double x;
	// Testing box, triangles and others
	x=llx+w*0.2;
	wr.DrawTextCenter(x,(ury-lly)/2+h*0.05,"Single shapes",30);
	wr.SetFillColor(0.5,0.0,0.5,0.5);
	wr.DrawBox(x,(ury-lly)/2,5,10);
	wr.DrawBox(x,(ury-lly)/2-h*.2,30,15,true);
	x+=w*0.05;
	wr.SetFillColor(0.5,0.5,0.5,0.5);
	wr.DrawCircle(x,(ury-lly)/2,7);
	wr.DrawCircle(x,(ury-lly)/2-h*0.2,15,true);
	x+=w*0.05;
	wr.SetFillColor(0.0,0.5,0.5,0.5);
	wr.DrawTriangle(x,(ury-lly)/2,8);
	wr.DrawTriangle(x,(ury-lly)/2-h*0.2,15,true);
	x+=w*0.05;
	wr.SetFillColor(0.5,0.5,0.0,0.5);
	wr.DrawSquare(x,(ury-lly)/2,10);
	wr.DrawSquare(x,(ury-lly)/2-h*0.2,15,true);
	
	// testing line strip. (open)
	int i;
	const int n=20;
	double pX[n];
	double pY[n];
	for (i=0;i<n;i++)
	{
		pX[i]=llx+w/(n)*(i+1)*0.9;
		pY[i]=lly+h*0.5+h/3.0*sin(2*i/(double)(n-1)*3.14);
	}
	
	wr.DrawTextCenter(pX[n/2]+w*0.1,pY[n/2]+h*0.1,"Shape strip");

	wr.SetFillColor(0,0,0.8,0.5);	
	wr.DrawSquareStrip(n,pX,pY,5,true);
	wr.DrawCircleStrip(n,pX,pY,10);
	wr.SetColor(0.8,0,1);
	wr.DrawTriangleStrip(n,pX,pY,10);
	wr.SetColor(1,0,0);
	wr.DrawLineStrip(n,pX,pY);
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}

void TestSurf(CGfxInterface& wr)
{
	double llx=0.75;
	double lly=0.25;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);

	// testing surf...
	const int nx=10;
	const int ny=15;
	int i,j,k;
	double dx=w/(nx-1);
	double dy=h/(ny-1);
	double pColor[3*nx*ny];
	for (i=0;i<ny;i++)
	{
		for (j=0;j<nx;j++)
		{
			k=i*nx+j;
			pColor[k*3]=(j*j*dx*dx)/(w*w);
			pColor[k*3+1]=(j*dx+i*dy)/(w+h);
			pColor[k*3+2]=(i*dx*j*dy)/(w*h)-0.1;
		}
	}
	wr.DrawSurf(nx,ny,llx,lly,dx,dy,pColor);
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}

void TestVectorField(CGfxInterface& wr)
{
	double llx=0;
	double lly=0.5;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);

	// testing surf...
	const int nx=10;
	const int ny=15;
	int i,j,k;
	double dx=w/(nx-1);
	double dy=h/(ny-1);
	// testing vector field
	double pV[2*nx*ny];
	for (i=0;i<ny;i++)
	{
		for (j=0;j<nx;j++)
		{
			k=i*nx+j;
			pV[k*2]=0.2*cos(j*dx/w*3.14);
			pV[k*2+1]=0.2*sin(2*i*dy/w*3.14);
		}
	}
	wr.DrawVectorField(nx,ny,llx,lly,dx,dy,pV,1.5);
	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}

void TestRect(CGfxInterface& wr)
{
	double llx=0.25;
	double lly=0.5;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);

	// Testing simple line
	// adding a line.
	for (int i=0;i<11;i++)
	{
		wr.SetColor(i/(float)10,0,(9-i)/(float)10);
		wr.DrawRect(llx+w*0.5 + w*0.2*sin(i*3.14/10), lly+h*0.4+ h*0.2*cos(i*3.14/10), llx+w*0.6+ w*0.2*sin(i*3.14/10), lly+h*0.5+h*0.2*cos(i*3.14/10));
	}	
	for (i=0;i>-11;i--)
	{
		wr.SetFillColor(-i/(float)10,0,(9+i)/(float)10, (9+i)/(float)15+0.4);
		wr.SetColor(0,0,0,1-((9+i)/(float)15+0.4));
		wr.DrawRect(llx+w*0.4 + w*0.2*sin(i*3.14/10), lly+h*0.4+ h*0.2*cos(i*3.14/10), llx+w*0.5+ w*0.2*sin(i*3.14/10), lly+h*0.5+h*0.2*cos(i*3.14/10),true);
	}	

	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}

void TestText(CGfxInterface& wr)
{
	double llx=0.5;
	double lly=0.5;
	double w=0.25;
	double h=0.25;
	double urx=llx+w;
	double ury=lly+h;
	wr.PushState(); wr.PushClipWorld(llx,lly,urx,ury);
	wr.SetColor(0,0,0);
	wr.SetFont(6);

	// Testing simple line
	// adding a line.
	wr.DrawTextLeft(llx+w*0.3, lly+h*0.1, "Left text");
	wr.DrawTextRight(llx+w*0.3, lly+h*0.2, "Right text");
	wr.DrawTextCenter(llx+w*0.3, lly+h*0.3, "Centered text");

	wr.SetColor(0,0,1);
	wr.DrawTextLeft(llx+w*0.7, lly+h*0.5, "Left text, vertical",90);
	wr.DrawTextRight(llx+w*0.8, lly+h*0.5, "right text, vertical", 90);
	wr.DrawTextCenter(llx+w*0.9, lly+h*0.5, "Centered text, vertical", 90);

	wr.SetColor(1,0,0);
	wr.DrawTextLeft(llx+w*0.4, lly+h*0.8, "Left text, 390deg",390);
	wr.DrawTextRight(llx+w*0.5, lly+h*0.8, "right text, -330deg", -330);
	wr.DrawTextCenter(llx+w*0.6, lly+h*0.8, "Centered text, 30deg", 30);

	std::vector<std::string> vString(5);
	std::vector<gfxinterface::SPointF> vPoints(5);
	vString[0]="This";
	vString[1]="is";
	vString[2]="a";
	vString[3]="text";
	vString[4]="strip";
	vPoints[0].x=llx+w*0.1; 	vPoints[0].y=lly+h*0.9;
	vPoints[1].x=llx+w*0.15; 	vPoints[1].y=lly+h*0.9;
	vPoints[2].x=llx+w*0.2; 	vPoints[2].y=lly+h*0.9;
	vPoints[3].x=llx+w*0.25; 	vPoints[3].y=lly+h*0.9;
	vPoints[4].x=llx+w*0.3; 	vPoints[4].y=lly+h*0.9;
	wr.SetColor(0,0.8,0);
	wr.DrawTextStrip(vPoints, vString, TextAlignmentLeft, 25);

	wr.PopClipWorld(); wr.PopState();
	wr.DrawRect(llx,lly,urx,ury);
}


/////////////////////////////////////////////////////////////////////////////
// CIGfxTestView drawing
void CIGfxTestView::OnDraw(CDC* pDC)
{
	using namespace Gdiplus;

    RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right - rect.left + 1;
	int nHeight = rect.bottom - rect.top + 1;
	
	Graphics graphics(pDC->m_hDC);	

	double llx=0;
	double urx=1;
	double lly=0;
	double ury=1;
	double w=urx-llx;
	double h=ury-lly;

	m_pInterface->SetMainBoundingBox(0,0,nWidth, nHeight);
	m_pInterface->SetWorldBoundingBox(llx,lly,urx,ury);
	m_pInterface->SetGraphics(&graphics);

	m_pInterface->BeginPaint();
	m_pInterface->PushState();
	TestArrow(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestGraphicState(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestGrid(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestLine(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestLineStrip(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestRect(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestShapes(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestStepStrip(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestSurf(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestVectorField(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestText(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->EndPaint();

}

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestView printing

BOOL CIGfxTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIGfxTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIGfxTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestView diagnostics

#ifdef _DEBUG
void CIGfxTestView::AssertValid() const
{
	CView::AssertValid();
}

void CIGfxTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIGfxTestDoc* CIGfxTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIGfxTestDoc)));
	return (CIGfxTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestView message handlers

void CIGfxTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
}

void CIGfxTestView::OnDestroy() 
{
	CView::OnDestroy();
	delete m_pInterface;	
}

void CIGfxTestView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_pInterface->SetMainBoundingBox(10,10,cx-10,cy-10);
}

void CIGfxTestView::OnTestTometafile() 
{
	using namespace Gdiplus;

   HDC hdcPrint;

   DOCINFO docInfo;
   ZeroMemory(&docInfo, sizeof(DOCINFO));
   docInfo.cbSize = sizeof(DOCINFO);
   docInfo.lpszDocName = "GdiplusPrint";

    RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right - rect.left + 1;
	int nHeight = rect.bottom - rect.top + 1;

 // Get a device context for the printer.
  hdcPrint = CreateDC(NULL, TEXT("\\\\NESTOR\\PC-Szut"), NULL, NULL);


    StartDoc(hdcPrint, &docInfo);
    StartPage(hdcPrint);
	Graphics graphics(hdcPrint);
	double llx=0;
	double urx=1;
	double lly=0;
	double ury=1;
	double w=urx-llx;
	double h=ury-lly;

	m_pInterface->SetMainBoundingBox(0,0,nWidth, nHeight);
	m_pInterface->SetWorldBoundingBox(llx,lly,urx,ury);
	m_pInterface->SetGraphics(&graphics);
	m_pInterface->BeginPaint();
	m_pInterface->PushState();
	TestArrow(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestGraphicState(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestGrid(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestLine(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestLineStrip(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestRect(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestShapes(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestStepStrip(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestSurf(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->PushState();
	TestVectorField(*m_pInterface);
	m_pInterface->PopState();

	m_pInterface->EndPaint();
         EndPage(hdcPrint);
      EndDoc(hdcPrint);

      DeleteDC(hdcPrint);	
}

void CIGfxTestView::OnTestMultiouput() 
{
    RECT rect;
	GetClientRect(&rect);
	int nWidth = rect.right - rect.left + 1;
	int nHeight = rect.bottom - rect.top + 1;

	double llx=0;
	double urx=1;
	double lly=0;
	double ury=1;
	double w=urx-llx;
	double h=ury-lly;

	CSVGInterface svg("test.svg",true);
	CEPSInterface eps("test.eps");

	svg.SetMainBoundingBox(0,0,800, 600);
	svg.SetWorldBoundingBox(llx,lly,urx,ury);
	if (svg.Open())
		DrawDemo(&svg);
	svg.Close();

	eps.SetMainBoundingBox(0,0,250, 100);
	eps.SetWorldBoundingBox(llx,lly,urx,ury);
	if (eps.Open())
		DrawDemo(&eps);
	eps.Close();
}

void CIGfxTestView::DrawDemo(CGfxInterface *pInterface)
{
	pInterface->BeginPaint();
	pInterface->PushState();
	TestArrow(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestGraphicState(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestGrid(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestLine(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestLineStrip(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestRect(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestShapes(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestStepStrip(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestSurf(*pInterface);
	pInterface->PopState();

	pInterface->PushState();
	TestVectorField(*pInterface);
	pInterface->PopState();

	pInterface->EndPaint();
}
