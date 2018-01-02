// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Histogram.h"
#include "RandomGenerator.h"

#include "HistogramDemo.h"


#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_HISTOGRAMS_NORMALDISTRIBUTION, OnHistogramsNormaldistribution)
	ON_COMMAND(ID_HISTOGRAMS_EXPONENTIALDISTRIBUTION, OnHistogramsExponentialdistribution)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	RECT rect;
	GetWindowRect( &rect );

	rect.right = rect.left + 200;
	rect.bottom = rect.top + 100;

	MoveWindow( &rect);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::PlotHistogram( CPGLGraph* pGraph, const std::vector<float>& vData, LPCTSTR szTitle, EHistogramType eType)
{
	using namespace std;

	ASSERT(pGraph);
	CString str;

	double fAve, fAdev, fSdev, fVar, fSkew, fCcurt;
	THistogram<float> histo(101);

	histo.Compute(vData);
	histo.GetMoments(vData,fAve, fAdev, fSdev, fVar, fSkew, fCcurt);

	//////////////////////////////////////////////////////////////////////////////////////////////////////:
	// adding theoretical curve...
	CPGLLine2D* pLineTheo = new CPGLLine2D;
	pLineTheo->SetLineWidth(2);
	//pLineTheo->SetName(_T("Theoretical curve"));
	
	vector<double> vTX(histo.GetLeftContainers());	
	vector<double> vTY(vTX.size());
	for (UINT i = 0; i < vTX.size();i++) 
	{
		switch (eType)
		{
		case HistogramTypeExp:
			vTY[i] = CRandomGenerator::TEXP(vTX[i], fAve);
			break;
		default:
			vTY[i] = CRandomGenerator::TNOR(vTX[i], fAve, fSdev);
		}
	}
	pLineTheo->SetDatas( vTX, vTY );
	pLineTheo->SetColor(0,0,1);

	pGraph->AddObject(pLineTheo);

	CPGLLine2D* pLine = new CPGLLine2D;
	pLine->SetInterpolationType(PGL_INTERPOLATION_STEP);
	pLine->SetLineWidth(2);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// putting result in vector
	vector<double> vX(histo.GetLeftContainers());	
	vector<double> vY(histo.GetNormalizedHistogram());
	pLine->SetDatas(vX, vY);

	//Add the line to the graph (note that an object can be added to only one graph): 
	pGraph->AddObject(pLine);

	//Make PGL scale the plot (automatically) 
	pGraph->ZoomAll();

	// setting title
	CPGLAxe2D* pAxe = pGraph->GetAxe();
	str.Format(_T("%s, n=%u, mean=%3.3g, sdev=%3.3g"), szTitle,histo.GetSum(), fAve, fSdev);
	//pAxe->SetTitle(str);

	//Create a dialog box and display the plot: 
	CPGLGraphBitDlg graphdlg(this, pGraph);
	graphdlg.DoModal();
}

void CMainFrame::OnHistogramsNormaldistribution() 
{
	using namespace std;
	UINT n = 10000;

	vector<float> vData(n);

	for (UINT i = 0;i<n;i++)
		vData[i]=CRandomGenerator::RNOR(1.0,0.1);

	CPGLGraph* pGraph = new CPGLGraph;

	// adding histogram
	PlotHistogram(pGraph, vData, _T("Histogram for pdf"), HistogramTypeNorm);
}

void CMainFrame::OnHistogramsExponentialdistribution() 
{
	using namespace std;
	UINT n = 100000;

	vector<float> vData(n);

	for (UINT i = 0;i<n;i++)
		vData[i]=CRandomGenerator::REXP();


	CPGLGraph* pGraph = new CPGLGraph;

	PlotHistogram(pGraph, vData, _T("Histogram for exp(1/x)"), HistogramTypeExp);	
}
