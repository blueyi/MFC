// GisInterface.cpp: implementation of the CGisInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vgis.h"
#include "GisInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "Math.H"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGisInterface::CGisInterface()
{
	//初始化屏幕参数
	m_StartX	=	10;
	m_StartY	=	10;
	m_blc		=	100;
	m_MapMode	=	1;
	m_Brink		=	10;
	m_BkColor	=	0;
	
	m_PenColor	=	0;					//当前画笔颜色序号
	m_BkColor	=	5;					//背景颜色序号
	m_BrushColor=	2;					//当前画刷颜色序号
	m_LineWide	=	1;					//当前线宽度
	m_LineType	=	0;					//当前线型
	m_Layer		=	1;						//当前图层
	m_bFill		=	0;
	m_Graph.SetInterface(this);

	m_Ps=new PointStruct[1000];

}

CGisInterface::~CGisInterface()
{
	delete m_Ps;
}
BEGIN_MESSAGE_MAP(CGisInterface, CWnd)
	//{{AFX_MSG_MAP(COscillogram)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TEXT_CHANGE,ChangeLabel)
END_MESSAGE_MAP()

BOOL CGisInterface::Create(CWnd* lParent,const RECT& rect  ,DWORD dwStyle )
{
	CString wndcls=AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,0,
		(HBRUSH)GetStockObject(WHITE_BRUSH),LoadIcon(NULL,IDI_APPLICATION));
	
//	m_TitleTip.Create(CRect(0,0,0,0));
//	SetWindowAlpha(m_TitleTip,180);
	BOOL re = CWnd::Create(wndcls,"波形图",dwStyle,rect,lParent,600);
	ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	return re;
}


void CGisInterface::OnPaint() 
{
	CPaintDC dc(this);
	this->Draw(&dc);
}
void CGisInterface::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);


	float r;

	CPen pen(0,0,RGB(0,0,0));
	CPen *pOldPen=dc.SelectObject(&pen);
	dc.SetROP2(R2_NOT);
	
	switch (m_DrawCurrent)
	{
	case G_LINE:
		m_cursor=::SetCursor(AfxGetApp()->LoadCursor(IDC_LINE));
		if (m_PushNumber==1)
		{
			if (pt2!=point)
			{
				dc.MoveTo(pt1);
				dc.LineTo(pt2);
				dc.MoveTo(pt1);
				dc.LineTo(point);
				pt2=point;
			}
		}
		break;
	case G_CIRCLE:
		if (m_PushNumber==1)
		{
			if (pt2!=point)
			{
				if (!m_bFill)
					dc.SelectStockObject(NULL_BRUSH);
				r=(float)sqrt((float)(pt1.x-pt2.x)*(pt1.x-pt2.x)+(float)(pt1.y-pt2.y)*(pt1.y-pt2.y));
				dc.Ellipse((int)(pt1.x-r),(int)(pt1.y-r),(int)(pt1.x+r),(int)(pt1.y+r));
				
				r=(float)sqrt((float)(pt1.x-point.x)*(pt1.x-point.x)+(float)(pt1.y-point.y)*(pt1.y-point.y));
				dc.Ellipse((int)(pt1.x-r),(int)(pt1.y-r),(int)(pt1.x+r),(int)(pt1.y+r));
				pt2=point;
			}
		}
		break;
	case G_ARC:
		break;
	case G_MLINERGN:
	case G_MLINE:
		m_cursor=::SetCursor(AfxGetApp()->LoadCursor(IDC_LINE));
		if (m_PushNumber>0)
		{
			if (pt2!=point)
			{
				dc.MoveTo(pt1);
				dc.LineTo(pt2);
				dc.MoveTo(pt1);
				dc.LineTo(point);
				pt2=point;
			//	ReleaseCapture();
			}
		}
		
		break;
	case G_TAG:
		break;

	case G_LINENET:
		break;
	case G_TEXT:
		break;
	case G_MOVE:
		m_cursor=::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVE));	
		if (m_PushNumber>0)
		{
			CRect rect;
			GetClientRect(&rect);
			dc.BitBlt(point.x-pt1.x,point.y-pt1.y,rect.Width(),rect.Height(),&m_MemDC,0,0,SRCCOPY);
		}
		break;
	case G_RECT:
		m_cursor=::SetCursor(AfxGetApp()->LoadCursor(IDC_RECT));
		if (m_PushNumber>0)
		{
			if (pt2!=point)
			{
				dc.SelectStockObject(NULL_BRUSH);
				dc.Rectangle(pt1.x,pt1.y,pt2.x,pt2.y);
				dc.Rectangle(pt1.x,pt1.y,point.x,point.y);
				pt2=point;
			}
		}
		break;
	case G_BIG:
		m_cursor=::SetCursor(AfxGetApp()->LoadCursor(IDC_ADD));
		break;
	case G_SMALL:
		m_cursor=::SetCursor(AfxGetApp()->LoadCursor(IDC_DEC));
		break;

	}
	dc.SelectObject(pOldPen);
	CWnd::OnMouseMove(nFlags, point);
}
BOOL CGisInterface::OnEraseBkgnd(CDC* pDC) 
{
	m_Graph.DrawBack(pDC,m_ScreenWidth,m_ScreenHeight,m_BkColor);
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}
void CGisInterface::OnDestroy() 
{

	CWnd::OnDestroy();
}



void CGisInterface::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	float D_x1,D_y1,D_x2,D_y2;
//	int x1,x2,y1,y2,index;
	int id;
	float r;
	switch (m_DrawCurrent)
	{
	case G_LINE:
		::HideCaret(this->m_hWnd);
		if (this->m_PushNumber==0)//第一次按下鼠标左键
		{
			m_PushNumber++;
			pt1=point;
			pt2=point;
			SetCapture();
		}
		else if (m_PushNumber==1)
		{
			VPtoDP(pt1.x,pt1.y,D_x1,D_y1);
			VPtoDP(point.x,point.y,D_x2,D_y2);
			id=m_Graph.CreateID(m_DrawCurrent);
			m_Graph.AddLine(m_PenColor,m_BrushColor,m_LineWide,m_LineType,m_Layer,id,0,D_x1,D_y1,D_x2,D_y2)->Draw(&dc,0,0,this->m_BkColor);
			m_PushNumber=0;
			ReleaseCapture();
		}
		break;
	case G_CIRCLE:
		::HideCaret(this->m_hWnd);
		if (this->m_PushNumber==0)//第一次按下鼠标左键
		{
			m_PushNumber++;
			pt1=point;
			pt2=point;
			SetCapture();
		}
		else if (m_PushNumber==1)
		{
			//计算得到圆的半径
			r=(float)sqrt((float)(pt1.x-point.x)*(pt1.x-point.x)+(pt1.y-point.y)*(pt1.y-point.y));
			//得到圆心的实际坐标
			VPtoDP(pt1.x,pt1.y,D_x1,D_y1);
			id=m_Graph.CreateID(m_DrawCurrent);
			r=VLtoDL((int)r);
			//保存圆并重新画
			m_Graph.AddCircle(m_PenColor,m_BrushColor,(float)m_LineWide,m_LineType,m_Layer,id,0,D_x1,D_y1,r,m_bFill)->Draw(&dc,0,0,m_BkColor);
			m_PushNumber=0;
			ReleaseCapture();
		}
		break;
	case G_ARC:
		break;
	case G_MLINE:
	case G_MLINERGN:
		VPtoDP(point.x,point.y,m_Ps[m_PushNumber].x,m_Ps[m_PushNumber].y);
		if (m_PushNumber==0)
		{
			SetCapture();
			pt1=point;
			pt2=point;
		}
		else
		{
			pt1=pt2;
			pt2=point;
		}
		m_PushNumber++;
		break;
	case G_TAG:
		break;
	case G_LINENET:
		break;
	case G_TEXT:
		pt1=pt2=point;
		VPtoDP(pt1.x,pt1.y,T_x1,T_y1);
		break;
	case G_LABEL:
		{
			pt1=pt2=point;
			VPtoDP(pt1.x,pt1.y,T_x1,T_y1);
			CLabel la;
			this->m_TextDlg.Create(this,m_blc,la);
			::CreateCaret(this->m_hWnd,NULL,1,16);
			::SetCaretPos(point.x,point.y);
			::ShowCaret(this->m_hWnd);
		}
		break;
	case G_MOVE:
		{
			pt1=pt2=point;
			CRect rect;
			this->GetClientRect(&rect);
			
			if (m_MemDC.m_hDC)
				m_MemDC.DeleteDC();
			
			if (m_pBitmap.m_hObject)
				m_pBitmap.DeleteObject();
			
			m_pBitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());  
			
			m_MemDC.CreateCompatibleDC(&dc);
			m_MemDC.SelectObject(m_pBitmap);
			m_MemDC.FillSolidRect(&rect,RGB(255,255,255));
			
			this->Draw(&m_MemDC);
			m_PushNumber=1;
			SetCapture();
		}
		break;
	case G_RECT:
		pt1=pt2=point;
		m_PushNumber++;

		break;
	case G_BIG:
		this->SetBlc(-14,point);
		break;
	case G_SMALL:
		this->SetBlc(14,point);
		break;
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CGisInterface::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int x1,y1,x2,y2;
	CClientDC dc(this);
	switch (m_DrawCurrent)
	{
	case G_MOVE:
		if (m_PushNumber>0)
		{
			m_StartX=m_StartX+(pt1.x-point.x)*m_blc;
			m_StartY=m_StartY-(pt1.y-point.y)*m_blc;
			this->Invalidate();
			if (m_MemDC.m_hDC)
				m_MemDC.DeleteDC();
			ReleaseCapture();
		}
		break;
	case G_RECT:
		if (m_PushNumber>0)
		{
			dc.SetROP2(R2_NOT);
			m_PushNumber=0;
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(pt1.x,pt1.y,point.x,point.y);
		
			//太小不进行放大
			CRect rect(pt1,point);
			if (rect.Width()<30)
				break;
			if (rect.Height()<30)
				break;


			if (pt1.x<point.x)
			{
				x1=pt1.x;
				x2=point.x;
			}
			else
			{
				x1=point.x;
				x2=pt1.x;
			}
			
			if (pt1.y<point.y)
			{
				y2=pt1.y;
				y1=point.y;
			}
			else
			{
				y2=point.y;
				y1=pt1.y;
			}
			
			
			//设置开始位置
			VPtoDP(x1,y1,m_StartX,m_StartY);
			
			//确定放大比例
			float bl1=(float)m_ScreenWidth/(float)(x2-x1);
			float bl2=(float)m_ScreenHeight/(float)(y1-y2);
			if (bl2<bl1)
				bl1=bl2;
			m_blc=m_blc/bl1;
			
			this->Invalidate();
		}
		break;
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void CGisInterface::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	float r;
	CClientDC dc(this);
	CPen pen(0,0,RGB(0,0,0));
	CPen *pOldPen=dc.SelectObject(&pen);
	dc.SetROP2(R2_NOT);

	switch (m_DrawCurrent)
	{
	case G_LINE:
		if (m_PushNumber==1)
		{
				dc.MoveTo(pt1);
				dc.LineTo(pt2);
				m_PushNumber=0;
				ReleaseCapture();

		}
		break;
	case G_CIRCLE:
	
		if (m_PushNumber==1)
		{
			if (!m_bFill)
				dc.SelectStockObject(NULL_BRUSH);
			r=(float)sqrt((float)(pt1.x-pt2.x)*(pt1.x-pt2.x)+(float)(pt1.y-pt2.y)*(pt1.y-pt2.y));
			dc.Ellipse((int)(pt1.x-r),(int)(pt1.y-r),(int)(pt1.x+r),(int)(pt1.y+r));
			ReleaseCapture();
			m_PushNumber=0;
		}

		break;
	case G_ARC:
		break;
	case G_MLINE:
	case G_MLINERGN:
		if (m_PushNumber>0)
		{
			dc.MoveTo(pt1);
			dc.LineTo(pt2);
			if (m_DrawCurrent==G_MLINE && m_PushNumber>1)
			{
				m_Graph.AddMLine(m_PenColor,m_BrushColor,m_LineWide,m_LineType,m_Layer,m_Graph.CreateID(G_MLINE),0,m_PushNumber,m_Ps)->Draw(&dc,0,0,m_BkColor);
				ReleaseCapture();
			}
			else if (m_DrawCurrent == G_MLINERGN && m_PushNumber>2)
			{
				m_Graph.AddMLineRgn(m_PenColor,m_BrushColor,m_LineWide,m_LineType,m_Layer,m_Graph.CreateID(G_MLINERGN),0,m_PushNumber,m_Ps,0,1)->Draw(&dc,0,0,m_BkColor);
				ReleaseCapture();
			}
			m_PushNumber=0;
			ReleaseCapture();
		}
		break;
	case G_TAG:
		break;
	case G_LINENET:
		break;
	case G_TEXT:
		break;
	case G_MOVE:

		this->Invalidate();
		if (m_MemDC.m_hDC)
			m_MemDC.DeleteDC();
		ReleaseCapture();
		m_PushNumber=0;
		break;
	case G_RECT:
		if (m_PushNumber>0)
		{
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(pt1.x,pt1.y,point.x,point.y);
		}
		ReleaseCapture();
		m_PushNumber=0;
		break;
	}
	dc.SelectObject(pOldPen);

	CWnd::OnRButtonDown(nFlags, point);
}

void CGisInterface::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	this->SetScreen(cx,cy);
}

void CGisInterface::Draw(CDC *pDC)
{
	m_Graph.Draw(pDC,0,0,this->m_BkColor);
}
float CGisInterface::DPtoVP(float x, float y,int &X,int &Y)
{
	X=(int)((x-m_StartX)/m_blc);
	if (m_MapMode==1)//MM_TEXT映射模式
		Y=m_ScreenHeight-(int)((y-m_StartY)/m_blc);
	else
		Y=(int)((y-m_StartY)/m_blc)-m_ScreenHeight;
	return m_blc;
}

float CGisInterface::VPtoDP(int x, int y, float &X, float &Y)
{
	X=m_StartX+x*m_blc;
	if (m_MapMode==1)//MM_TEXT影射模式
		Y=m_StartY+m_blc*(m_ScreenHeight-y);
	else
		Y=m_StartY+m_blc*(m_ScreenHeight+y);
	return m_blc;
}

void CGisInterface::SetStartOrg(float x, float y, float blc)
{
	m_StartX=x;
	m_StartY=y;
	m_blc=blc;
}

void CGisInterface::SetScreen(int ScreenWidth, int ScreenHeight)
{
	m_ScreenWidth=ScreenWidth;
	m_ScreenHeight=ScreenHeight;
}


float CGisInterface::VLtoDL(int l)
{
	return m_blc*l;
}

int CGisInterface::DLtoVL(float l)
{
	return (int)(l/m_blc);
}

void CGisInterface::SetMapMode(int MapMode)
{
	m_MapMode=MapMode;
}

void CGisInterface::SetScreenFromMaxMin(float MaxX, float MaxY, float MinX, float MinY, int Brink)
{


	m_Brink=Brink;
	float blc1,blc2;
	blc1=(MaxX-MinX)/(m_ScreenWidth-m_Brink*2);
	blc2=(MaxY-MinY)/(m_ScreenHeight-m_Brink*2);
	if (blc1<blc2)
		blc1=blc2;

	m_blc=blc1;

	m_StartX=MinX-m_Brink*m_blc;
	m_StartY=MinY-m_Brink*m_blc;

}



BOOL CGisInterface::GetNetXY(int NetID, float &x, float &y, BOOL &Delete)
{
	int nn=this->m_Graph.GetGraphIndex(G_LINENET,NetID);
	if (nn<0)
		return 0;
	LineNet *pNet=(LineNet*)m_Graph.GetGraph(G_LINENET,nn);
	Delete=pNet->m_Delete;
	x=pNet->m_x;
	y=pNet->m_y;
	return 1;
}

int CGisInterface::SetDraw(int style)
{
	int ret=m_DrawCurrent;
	m_DrawCurrent=style;
	m_PushNumber=0;
	return ret;
}

void CGisInterface::SetBlc(float blc,CPoint pt)
{
	m_blc=m_blc+blc;
	this->Invalidate();
}

void CGisInterface::ChangeText(CText *pText, int lParam)
{
	CClientDC dc(this);
	CString temp;
	float lw=VLtoDL(m_LineWide);
//	float hi=VLtoDL(pText->m_TextHeight);
//	float wd=VLtoDL(pText->m_TextWide);
//	float owd=VLtoDL(pText->m_OffWide);

//	float lw=(m_LineWide);
//	float hi=(pText->m_TextHeight);
//	float wd=(pText->m_TextWide);
//	float owd=(pText->m_OffWide);

	switch (lParam)
	{
	case 0://cancel
		T_PreText.Empty();
		break;
	case 1://change
		temp=pText->m_Text;
		
//		pText->SetPara(m_BkColor,m_BrushColor,//,m_LineType,m_Layer,1,0,T_x1,T_y1,pText->m_Angle1,pText->m_Angle2,hi,wd,owd,0,T_PreText);
		pText->SetGraphPara(&m_Graph.m_GraphPara);
		pText->SetInterface(this);
		pText->Draw(&dc,0,0,m_BkColor);
		T_PreText=temp;
	//	pText->SetPara(m_PenColor,m_BrushColor,lw,m_LineType,m_Layer,1,0,T_x1,T_y1,pText->m_Angle1,pText->m_Angle2,hi,wd,owd,0,T_PreText);
		pText->SetGraphPara(&m_Graph.m_GraphPara);
		pText->SetInterface(this);
		pText->Draw(&dc,0,0,m_BkColor);
		break;
	case 2://OK
//		m_Graph.AddText(m_PenColor,m_BrushColor,lw,m_LineType,m_Layer,m_Graph.CreateID(G_TEXT),0,T_x1,T_y1,pText->m_Lf,pText->m_Text);
		break;

	}
}

float CGisInterface::GetBlc()
{
	return m_blc;
}

LRESULT CGisInterface::ChangeLabel(WPARAM wPram,LPARAM lParam)
{

    CLabel *pLabel = (CLabel *)wPram;
    int lParamm = (int)lParam;

	CClientDC dc(this);
	CString temp;

	switch (lParamm)
	{
	case 0://cancel
		T_PreText.Empty();
		break;
	case 1://change
		temp=pLabel->m_Text;
		
		pLabel->SetPara(m_BkColor,m_BrushColor,1,m_LineType,m_Layer,1,0,T_x1,T_y1,pLabel->m_MaxDisp,pLabel->m_MinDisp,pLabel->m_lf,T_PreText);
		pLabel->SetGraphPara(&m_Graph.m_GraphPara);
		pLabel->SetInterface(this);
		pLabel->Draw(&dc,0,0,m_BkColor);
		T_PreText=temp;
		pLabel->SetPara(m_PenColor,m_BrushColor,1,m_LineType,m_Layer,1,0,T_x1,T_y1,pLabel->m_MaxDisp,pLabel->m_MinDisp,pLabel->m_lf,T_PreText);
		pLabel->SetGraphPara(&m_Graph.m_GraphPara);
		pLabel->SetInterface(this);
		pLabel->Draw(&dc,0,0,m_BkColor);
		break;
	case 2://OK
		m_Graph.AddLabel(m_PenColor,m_BrushColor,1,m_LineType,m_Layer,1,0,T_x1,T_y1,pLabel->m_MaxDisp,pLabel->m_MinDisp,pLabel->m_lf,pLabel->m_Text);
		break;

	}

    return 1;
}

void CGisInterface::SetStartXY(float x, float y)
{
	m_StartX+=(x*m_blc);
	m_StartY+=(y*m_blc);
}

void CGisInterface::AllGraph()
{
	float minx,miny,maxx,maxy;
	SetCapture();
	::SetCursor(AfxGetApp()->LoadCursor(IDC_WAIT));
	BOOL pb=m_Graph.GetRect(minx,miny,maxx,maxy);
	::SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));
	ReleaseCapture();
	if (!pb)
		return;
	float bl1,bl2;

	bl1=(maxx-minx)/(m_ScreenWidth-m_Brink*2);
	bl2=(maxy-miny)/(m_ScreenHeight-m_Brink*2);
	
	if (bl1>bl2)
		bl2=bl1;
	
	m_blc=bl2;

	m_StartX=minx-m_Brink*m_blc;
	m_StartY=miny-m_Brink*m_blc;

	this->Invalidate();
}

void CGisInterface::Serialize(CArchive &ar)
{
	m_Graph.Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<m_blc<<m_StartX<<m_StartY<<m_Layer<<m_LineType<<m_LineWide<<m_MapMode<<m_DrawCurrent<<m_BrushColor<<m_Brink<<m_BkColor<<m_PenColor<<m_ScreenHeight<<m_ScreenWidth;
	}
	else
	{
		ar>>m_blc>>m_StartX>>m_StartY>>m_Layer>>m_LineType>>m_LineWide>>m_MapMode>>m_DrawCurrent>>m_BrushColor>>m_Brink>>m_BkColor>>m_PenColor>>m_ScreenHeight>>m_ScreenWidth;
	}
}
