// RTDemoView.cpp : implementation of the CRTDemoView class
//

#include "stdafx.h"
#include "RTDemo.h"

#include "RTDemoDoc.h"
#include "RTDemoView.h"
#include "RTForm.h"
#include "TimerSpeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SliderTickID 12001

/////////////////////////////////////////////////////////////////////////////
// CRTDemoView

IMPLEMENT_DYNCREATE(CRTDemoView, CView)

BEGIN_MESSAGE_MAP(CRTDemoView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CRTDemoView)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_SPEED_TIMERSPEED, OnSpeedTimerspeed)
	ON_UPDATE_COMMAND_UI(ID_SPEED_TIMERSPEED, OnUpdateSpeedTimerspeed)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTDemoView construction/destruction

CRTDemoView::CRTDemoView()
{
	SpeedLevel	 = 4;//6
	CyclesPerSec = 1000.0 / m_Graph.m_SpeedLevel[SpeedLevel];
	MillSeconds	 = m_Graph.m_SpeedLevel[SpeedLevel];
	m_bRealTime	 = FALSE;
	if (!m_bRealTime) 
		CyclesPerSec = 1;
	m_nStartTime = 0;
	mSec		 = m_nStartTime;
	m_nTimeSpan	 = 30;
	m_sTicks	 = (int)(0.5 + m_nTimeSpan * CyclesPerSec);
	MaxSeconds   = 120;
	CanTicks     = TRUE;
	m_bCanSize   = FALSE;
	m_bFlag		 = TRUE;
	m_nTicks	 = 0;
	Rn.init_random();
	m_Graph.SetXNumOfTicks(60);
    

}

CRTDemoView::~CRTDemoView()
{
}

BOOL CRTDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CRTDemoView::DrawFrame(CRect& rect, COLORREF cr, const char* Title)
{
	CRTDemoDoc* pDoc = GetDocument();
	m_Graph.RecalcRects(rect);
	if (pDoc->m_bBoundary)
		m_Graph.DrawBoundary(cr, 2);
	if (pDoc->m_bTitle)
	{
		m_Graph.XAxisTitle("时间");
		m_Graph.YAxisTitle("传感数据");
		//m_Graph.Title(Title);
	}
	m_Graph.Axes();
	if (pDoc->m_bGrid)
		m_Graph.Grid();
}

/////////////////////////////////////////////////////////////////////////////
// CRTDemoView drawing

void CRTDemoView::OnDraw(CDC* pDC)
{
	CRTDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_Graph.m_bSetingFailed)
		return;

	CRect rect;
	if (pDC->IsPrinting())
	{
		rect.left = rect.top = 0;
		rect.right  = pDC->GetDeviceCaps(HORZRES);
		rect.bottom = pDC->GetDeviceCaps(VERTRES);
		m_Graph.SetPrintScale(pDC->m_hDC, rect);
	}
	else
		GetClientRect(rect);

	m_Graph.BeginDraw(pDC->m_hDC);
	
	DrawFrame(rect, RGB(255, 0, 0), "");
	m_Graph.DrawRealTimeLines();	
	
	m_Graph.EndDraw(pDC->m_hDC);
}

/////////////////////////////////////////////////////////////////////////////
// CRTDemoView printing

BOOL CRTDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRTDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRTDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRTDemoView diagnostics

#ifdef _DEBUG
void CRTDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CRTDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRTDemoDoc* CRTDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRTDemoDoc)));
	return (CRTDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRTDemoView message handlers

void CRTDemoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CRTDemoDoc* pDoc = GetDocument();
	pDoc->pView = this;

	if (!m_Graph.SetRange(0, 0, 100, 100))
	{
		m_Graph.m_bSetingFailed = true;
		MessageBox("Setting Range failed");
		return;
	}
	m_Graph.EnableMemoryDraw(pDoc->m_bMemDraw);
	m_Graph.SetBackColor(pDoc->m_nBkColor);

	if (!m_Graph.InitialSetting(CyclesPerSec,  m_nStartTime, m_nTimeSpan, MaxSeconds, 6))
	{
		m_Graph.m_bSetingFailed = true;
		return;
	}
	m_Graph.m_bSetingFailed = false;

	RECT rect;
	GetClientRect(&rect);
	m_Graph.RecalcRects(rect);

	m_Graph.AddALine(RGB(255,   0,   0), 0, 50, "温度","0","℃",0,100,PS_SOLID,1);
	m_Graph.AddALine(RGB(  0, 255,   0), 0, 100, "湿度","0","%RH",0,100,PS_SOLID,1);
	//m_Graph.AddALine(RGB(  0,   0, 255), 30, 40, "Name 3");
	//m_Graph.AddALine(RGB(255,   0, 255), 40, 50, "Name 4");
	//m_Graph.AddALine(RGB(255, 255,   0), 50, 60, "Name 5");
	//m_Graph.AddALine(RGB(  0, 255, 255), 60, 70, "Name 6");
	//m_Graph.AddALine(RGB(128, 128, 128), 70, 80, "Name 7");
	//m_Graph.AddALine(RGB(  0,   0, 128), 80, 90, "Name 8");

	m_bCanSize = TRUE;
	m_sSize    = 17;

	m_SliderTick.Create(WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, 
						m_Graph.TickBarSize(), this, SliderTickID);
	m_SliderTick.SetRange(0, m_sTicks, TRUE);
	m_SliderTick.SetPageSize(1);
	m_SliderTick.SetPos(0);
	m_SliderTick.EnableWindow(FALSE);

	SetTimer(1, MillSeconds, NULL);
	KillTimer(1);
	m_bTimerOn = FALSE;

	//串口初始化
	if(m_mscomm.GetPortOpen())
	m_mscomm.SetPortOpen(FALSE);
	m_mscomm.SetCommPort(1);
    m_mscomm.SetInputMode(1);
    m_mscomm.SetSettings("57600,n,8,1");
    m_mscomm.SetRThreshold(1);
    m_mscomm.SetInputLen(0);
    if(!m_mscomm.GetPortOpen())
	{
	m_mscomm.SetPortOpen(TRUE);
	}
    else
	AfxMessageBox("Open The Serial Port 1 Failurre!");
    m_mscomm.GetInput();     


}

BOOL CRTDemoView::OnEraseBkgnd(CDC* pDC) 
{
	if (!m_Graph.m_bMemoryDraw || m_Graph.m_bSetingFailed)
		return CView::OnEraseBkgnd(pDC) ;
	
	return TRUE;
}

void CRTDemoView::SetData(int i)
{
	//"Rn.randm()" is much faster than "1.0 * rand() / RAND_MAX";
	//m_dY = m_Graph.m_LineArray[i].m_dScaleLow + 
		  //(m_Graph.m_LineArray[i].m_dScaleHigh - 
		  // m_Graph.m_LineArray[i].m_dScaleLow) * Rn.randm();
	if(i==0)
	m_dY = temperature;
	if(i==1)
    m_dY = humidity;
	m_Graph.AddYValue(i, m_dY);
}

void CRTDemoView::TicksRanges()
{
	if (CanTicks && m_Graph.m_nTimes / (m_nTimeSpan + 1) > m_nTicks && 
		MaxSeconds >= m_Graph.m_nTimes + 1)
	{
		m_nTicks = m_Graph.m_nTimes / m_nTimeSpan;
		if (m_nTicks >= m_Graph.m_nMaxPages) 
			CanTicks = FALSE;
		else
		{
			ResetSlider(m_nTicks + 1);
			m_Graph.m_nPage = m_nTicks + 1;
		}
	}
}

void CRTDemoView::OnTimer(UINT nIDEvent) 
{
	CView::OnTimer(nIDEvent);
}

void CRTDemoView::OnDestroy() 
{
	if (!m_Graph.m_bSetingFailed)
		KillTimer(1);

	CView::OnDestroy();
}

void CRTDemoView::GetYValues(int Index)
{   
    char temp[10];
    ltoa(packetnum,temp,10);
	m = m_Graph.m_LineArray.GetSize();
	CRTForm* pForm = (CRTForm*)GetRTForm();
	for(i = 0; i < m; i ++)
	{   
	
		m_dValue = m_Graph.m_LineArray[i].m_pValues[Index].YValue;
		//m_dValue = m_Graph.m_LineArray[i].m_dMin + (m_dValue - m_Graph.m_LineArray[i].m_dScaleLow) *
				   //(m_Graph.m_LineArray[i].m_dMax - m_Graph.m_LineArray[i].m_dMin) / 
				   //(m_Graph.m_LineArray[i].m_dScaleHigh - m_Graph.m_LineArray[i].m_dScaleLow);
		//num.Format("%d", packetnum);
		m_sString.Format("%.2f", m_dValue);
        pForm->m_RTGrid.SetTextMatrix(i + 1, 3, temp);
		pForm->m_RTGrid.SetTextMatrix(i + 1, 5, m_sString);
	}
}

void CRTDemoView::RefreshGraph()
{
	m = m_Graph.GetCursorTimeAndIndex(CurrentTime);
	GetYValues(m);
	m_Graph.Redraw(GetSafeHwnd());
}

void CRTDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if(m_bCanSize)
	{
		RECT rect;
		GetClientRect(&rect);
		m_Graph.RecalcRects(rect);
		m_SliderTick.MoveWindow(&m_Graph.TickBarSize());
	}
}

RECT& CRTDemoView::GetGraphRect()
{
	if (::IsWindow(m_hWnd))
		return m_Graph.m_PlotRect;
	else
	{
		static RECT rt;
		rt.left   = 0;
		rt.top    = 0;
		rt.right  = 0;
		rt.bottom = 0;
		return rt;
	}
}

CWnd* CRTDemoView::GetRTForm()
{
	CSplitterWnd* pWnd = (CSplitterWnd*)GetParent();
	return pWnd->GetPane(1, 0);
}

void CRTDemoView::ResetSlider(int Ticks)
{
	CRTForm* pForm = (CRTForm*)GetRTForm();
	pForm->InitialSlider(0, Ticks - 1, 1, Ticks);
}

void CRTDemoView::RTKillTimer()
{
	KillTimer(1);
	m_bTimerOn = FALSE;
}

void CRTDemoView::RTRestoreTimer()
{
	SetTimer(1, MillSeconds, NULL);
	m_bTimerOn = TRUE;
}

void CRTDemoView::RemoveALine(int Index)
{
	if (!m_Graph.RemoveALine(Index))
		return;

	CRTForm* pForm = (CRTForm*)GetRTForm();
	pForm->RedrawGrid();
}

BOOL CRTDemoView::InsertALine(int index, COLORREF color, double low, double high, 
							  const char* name, const char* desc, const char* unit, 
							  double min, double max, int style, int width)
{
	if (m_Graph.InsertALine(index, color, low, high, name, desc, 
							unit, min, max, style, width))
	{
		CRTForm* pForm = (CRTForm*)GetRTForm();
		pForm->RedrawGrid();
		return TRUE;
	}
	else
		return FALSE;
}

void CRTDemoView::SaveAModifiedLine()
{
	RefreshGraph();
	CRTForm* pForm = (CRTForm*)GetRTForm();
	pForm->RedrawGrid();
}

void CRTDemoView::GetColorAndName(int index, COLORREF& cr, CString& name)
{
	cr   = m_Graph.m_LineArray[index].m_nColor;
	name = m_Graph.m_LineArray[index].m_sName.GetChar();
}

void CRTDemoView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_RTDEMO_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CRTDemoView::OnSpeedTimerspeed() 
{
	CTimerSpeed TSpeed(this);

	TSpeed.m_nTimerSpeed = SpeedLevel;
	if (TSpeed.DoModal() == IDOK)
	{
		if (SpeedLevel != TSpeed.m_nTimerSpeed)
		{
			RTKillTimer();
			SpeedLevel  = TSpeed.m_nTimerSpeed;
			MillSeconds = m_Graph.m_SpeedLevel[SpeedLevel];
			RTRestoreTimer();
		}
	}
}

void CRTDemoView::OnUpdateSpeedTimerspeed(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bRealTime);
}

void CRTDemoView::Redraw()
{
	RECT rect;
	GetClientRect(&rect);
	m_Graph.RecalcRects(rect);
	Invalidate();
}

int CRTDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	DWORD style=WS_VISIBLE|WS_CHILD;

    if(!m_mscomm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM1))

	{

	  TRACE0("Failed to create OLE Communication Controls!\n");

	  return -1;

	}      

	
	return 0;
}

    BEGIN_EVENTSINK_MAP(CRTDemoView, CView)
    //{{AFX_EVENTSINK_MAP(CAboutDlg)
    ON_EVENT(CRTDemoView,IDC_MSCOMM1,1,OnComm,VTS_NONE)
    //}}AFX_EVENTSINK_MAP
    END_EVENTSINK_MAP()      

void CRTDemoView::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //设置BYTE数组
	float t,h;
	//CString strtemp,strhum;
	//if(bReceive)
	//{
	  t = temperature;
   	  h = humidity;

		if(m_mscomm.GetCommEvent()==2)     //事件值为2表示接收缓冲区内有字符
		{
			variant_inp = m_mscomm.GetInput();   //读缓冲区
			safearray_inp = variant_inp;           //VARIANT型变量转换为ColeSafeArray型变量
			len=safearray_inp.GetOneDimSize(); //得到有效数据长度
            for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
            for(k=0;k<len;k++)
			{  
			   if((*(char*)(rxdata+k)==0x7e)&&(*(char*)(rxdata+k+1)!=0x7e))
			   {
				   flag = 1;
               }
				
			   if(flag)
			   {
				   counter++;
                 
			   }
			   if(counter==9)
				   tmp=((*(char*)(rxdata+k))<<8);
			   if(counter==10)
                   tmp|=*(char*)(rxdata+k);
			   if(counter==11)
				   humi|=((*(char*)(rxdata+k))<<8);
               if(counter==12)
			   {
				humi|=*(char*)(rxdata+k);
			    flag=0;
			    counter=0;
			   
			   temperature = tmp/100-40;
               humidity = -humi*humi*28/10000000+humi*405/10000+(temperature-25)*(humi*8/100000+0.01)-4;
			   if(temperature<0)
				   temperature = t;
               if(humidity<0)
				   humidity = h;
			   packetnum++;
               //strtemp.Format("%f",temperature);
               //strhum.Format("%f",humidity);
			   //m_strReceive =m_strReceive+"温度："+strtemp+","+"湿度："+strhum+";";
			   break;
			   }
			}
			//m_strReceive+="\r\n";
		}
	//}
	//UpdateData(FALSE);           //更新编辑框内容
	n = m_Graph.m_LineArray.GetSize();
	for(i=0; i<n; i++)
		SetData(i);
	
	m_Graph.UpdateTimeRange(mSec);
	mSec += (UINT)(0.5 + 1000 / CyclesPerSec);

	m_Graph.SetPrintTime(mSec - m_nStartTime, m_Graph.MaxTime); // Sim time : max time
	n = m_Graph.GetCursorTimeAndIndex(CurrentTime);
	m_Graph.SetPrintTime(CurrentTime - m_nStartTime, m_Graph.CursorTime); // cursor time
	GetYValues(n);
	TicksRanges();

	if (m_bFlag)
	{
		if (m_Graph.m_bIsForwardDrawing)
		{
			if (m_Graph.m_nTick < m_Graph.m_nSTicks)
			{
				m_SliderTick.SetPos(m_Graph.m_nTick);
				m_Graph.m_nTick ++;
			}
			else
			{
				m_SliderTick.SetPos(m_Graph.m_nTick);
				m_SliderTick.EnableWindow(TRUE);
				m_bFlag = FALSE;
			}
		}
		else
		{
			m_SliderTick.SetPos(m_Graph.m_nSTicks);
			m_Graph.m_nTick ++;
			if (m_Graph.m_nTick == m_Graph.m_nSTicks)
			{
				m_SliderTick.EnableWindow(TRUE);
				m_bFlag = FALSE;
			}
		}
	}
		m_Graph.Redraw(GetSafeHwnd());
	
}
