// GLDouglasDoc.cpp : implementation of the CGLDouglasDoc class
//

#include "stdafx.h"
#include "GLDouglas.h"

#include "GLDouglasDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasDoc

IMPLEMENT_DYNCREATE(CGLDouglasDoc, CDocument)

BEGIN_MESSAGE_MAP(CGLDouglasDoc, CDocument)
	//{{AFX_MSG_MAP(CGLDouglasDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasDoc construction/destruction

CGLDouglasDoc::CGLDouglasDoc()
{
}

CGLDouglasDoc::~CGLDouglasDoc()
{
}

BOOL CGLDouglasDoc::OnNewDocument()
{
	using namespace hull;
	UINT n=500;

	if (!CDocument::OnNewDocument())
		return FALSE;

	srand( (unsigned)time( NULL ) );

	m_dShrink=0.1;
	m_dp.ResizePoints(n);

	// generate datas
	m_lCount=0;
	Animate();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGLDouglasDoc serialization

void CGLDouglasDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasDoc diagnostics

#ifdef _DEBUG
void CGLDouglasDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGLDouglasDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasDoc commands

void CGLDouglasDoc::Draw(CWGL& wgl)
{
	UINT nIter;
	CString str;
	CGLDouglasApp* pApp=(CGLDouglasApp*)AfxGetApp();

	if (pApp->GetView() != NULL)
		Animate();

	try
	{
		nIter=m_dp.ShrinkNorm(m_dShrink, 0);
	}
	catch(TCHAR* str)
	{
		AfxMessageBox(str);
		pApp->SetView(NULL);
	}


	glColor3f(0,0,0);
	glLineWidth(2);
	m_dp.PlotPoints();

	glColor3f(1,0,0);
	m_dp.PlotKeys(wgl);
	
	glColor3f(0,0,0);
	str.Format(_T("Douglas-Peucker Demo.... Shrink: %g%%, points: %d, keys: %d, tol = %g (Achieved in %d iterations)"),
			m_dShrink*100,
			m_dp.GetPointSize(),
			m_dp.GetKeySize(),
			m_dp.GetTol(),
			nIter);

	AfxGetMainWnd()->SetWindowText(str);
}

void CGLDouglasDoc::Animate()
{
	using namespace hull;

	size_t i;
	m_lCount%=10000;

	size_t n=m_dp.GetPointSize();

	for (i = 0; i < n; i++)
	{
		m_dp.SetPoint(i,i,
			n / 2.0 * (
			sin((2*3.14 * i) / n + m_lCount/100.0)
			*cos((3.14 * i) / n + m_lCount/1000.0)*cos((3.14 * i) / n+ m_lCount/1000.0)
			+sin((8*3.14 * i) / n + m_lCount/5.0)/3.0) 
			);

	}	
	m_lCount++;
}

void CGLDouglasDoc::GetLimits(double pExt[])
{
	CDPHullGL::Hull::SLimits l=m_dp.GetHull().GetBoundingBox();

	pExt[0]=l.dMinX;
	pExt[1]=l.dMaxX;
	pExt[2]=l.dMinY;
	pExt[3]=l.dMaxY;
}

CDPHullGL& CGLDouglasDoc::GetHull()
{
	return m_dp;
}
