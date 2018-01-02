// SliderClrDemoView.cpp : implementation of the CSliderClrDemoView class
//

#include "stdafx.h"
#include "SliderClrDemo.h"

#include "SliderClrDemoDoc.h"
#include "SliderClrDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoView

IMPLEMENT_DYNCREATE(CSliderClrDemoView, CFormView)

BEGIN_MESSAGE_MAP(CSliderClrDemoView, CFormView)
	//{{AFX_MSG_MAP(CSliderClrDemoView)
	ON_BN_CLICKED(IDC_CHGTICS, OnChgtics)
	ON_BN_CLICKED(IDC_CHGCLRS, OnChgclrs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoView construction/destruction

CSliderClrDemoView::CSliderClrDemoView()
	: CFormView(CSliderClrDemoView::IDD)
{
	//{{AFX_DATA_INIT(CSliderClrDemoView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	ticfreq = 100;
	colorScheme = 1;
}

CSliderClrDemoView::~CSliderClrDemoView()
{
}

void CSliderClrDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSliderClrDemoView)
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_SLIDER3, m_Slider3);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_SLIDER2, m_Slider2);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider1);
	//}}AFX_DATA_MAP
}

BOOL CSliderClrDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSliderClrDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	OnChgclrs();

	m_Slider3.m_dumpBitmaps = TRUE;	// debugging feature to save intermediate bitmaps
}

/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoView diagnostics

#ifdef _DEBUG
void CSliderClrDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSliderClrDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSliderClrDemoDoc* CSliderClrDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSliderClrDemoDoc)));
	return (CSliderClrDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoView message handlers

// This function is called by the CSliderCtrlEx control whenever it
// paints. The first argument is really the 'this' value for this
// class instance. sItemUpdate() then passes all its parameters to the
// general member function, ItemUpdate() which does the actual work
void CSliderClrDemoView::sItemUpdate(CSliderClrDemoView *obj, LPARAM data1, int sValue, BOOL IsDragging)
{
	CSliderClrDemoView *me = (CSliderClrDemoView *)obj;
	me->ItemUpdate(data1, sValue, IsDragging);
}

// when the slider is painted, this function is called. data1 is the control
// id (so we know WHICH slider is calling us), sValue is the GetPos() value,
// and IsDragging indicates if the mouse is dragging the slider or not.
//
// We could have simplified this function call by just using the control ID
// to call GetPos() but determining whether the left button is down or not
// is more difficult.
void CSliderClrDemoView::ItemUpdate(LPARAM data1, int sValue, BOOL /* IsDragging */)
{
	double slope1 = 0.05;
	double intercept1 = -25.0;
	double slope2 = 0.08;
	double intercept2 = -15.0;
	CString val;

	switch(data1)
	{
	case IDC_SLIDER1:
		val.Format("%6.2lf", (slope1 * double(sValue)) + intercept1);
		m_Edit1.SetWindowText(val);
		break;
	case IDC_SLIDER2:
		val.Format("%6.2lf", (slope2 * double(sValue)) + intercept2);
		m_Edit2.SetWindowText(val);
		break;
	case IDC_SLIDER3:
		val.Format("%6.2lf", (slope2 * double(sValue)) + intercept2);
		m_Edit3.SetWindowText(val);
		break;
	}
}

void CSliderClrDemoView::OnChgtics() 
{
	// TODO: Add your control notification handler code here
	ticfreq *= 2;
	if(ticfreq > 500) ticfreq = 50;
	m_Slider1.SetTicFreq(ticfreq);
	m_Slider2.SetTicFreq(ticfreq);
	m_Slider3.SetTicFreq(ticfreq);
}

void CSliderClrDemoView::OnChgclrs() 
{
	int maxRange;
	if(colorScheme)
	{
		maxRange = 2000;
		colorScheme = 0;
	}
	else
	{
		maxRange = 1000;
		colorScheme = 1;
	}
	// Slider1 initialization
	m_Slider1.clearCallback();
	m_Slider1.clearColors();
	m_Slider1.SetRange(0,maxRange,TRUE);
	m_Slider1.SetTicFreq(ticfreq);

	// Set up entire background as Orange
	m_Slider1.AddColor(0,maxRange,colOrange);	// entire range is no good

	// Mark one area as marginal
	m_Slider1.AddColor(250,300,colOrange,colYellow);	// these areas are marginal
	m_Slider1.AddColor(300,400,colYellow);
	m_Slider1.AddColor(400,450,colYellow,colOrange);

	// Add a second marginal area
	m_Slider1.AddColor(650,700,colOrange,colYellow);	// these areas are marginal
	m_Slider1.AddColor(700,800,colYellow);
	m_Slider1.AddColor(800,850,colYellow,colOrange);
	m_Slider1.Refresh();	// force screen update of newly configured slider

	// Setup automatic notification when slider changes. Note that update speed
	// is MUCH better if the tab order of the slider is before that of the 
	// corresponding edit control (or whatever you are updating in the callback func)
	m_Slider1.setCallback(CSliderClrDemoView::sItemUpdate,this,(LPARAM)IDC_SLIDER1);


	// Force the Edit control to stick to slider's right
	m_Slider2.clearCallback();
	m_Slider2.clearColors();
	m_Slider2.SetBuddy(&m_Edit2,FALSE);
	m_Slider2.SetRange(0,maxRange,TRUE);
	m_Slider2.SetTicFreq(ticfreq);

	m_Slider2.AddColor(0,maxRange,RGB(255,0,0));	// Pure Red

	// Make a gradient 
	m_Slider2.AddColor(200,300,colRed,colOrange);
	m_Slider2.AddColor(300,400,colOrange,colYellow);
	m_Slider2.AddColor(400,500,colYellow,colGreen);
	m_Slider2.AddColor(500,600,colGreen,colYellow);
	m_Slider2.AddColor(600,750,colYellow,colOrange);
	m_Slider2.AddColor(750,maxRange,colOrange,colRed);
	m_Slider2.Refresh();	// force screen update of newly configured slider

	m_Slider2.setCallback(CSliderClrDemoView::sItemUpdate,this,(LPARAM)IDC_SLIDER2);

	m_Slider3.clearCallback();
	m_Slider3.clearColors();
	m_Slider3.SetBuddy(&m_Edit3,FALSE);
	m_Slider3.SetRange(0,maxRange,TRUE);
	m_Slider3.SetTicFreq(ticfreq);
	m_Slider3.AddColor(0,maxRange,RGB(255,0,0),RGB(0,255,0));
	m_Slider3.setCallback(CSliderClrDemoView::sItemUpdate,this,(LPARAM)IDC_SLIDER3);
	m_Slider3.Refresh();	// force screen update of newly configured slider
}
