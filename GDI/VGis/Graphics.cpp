// Graphics.cpp: implementation of the Graphics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "Graphics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Graphics::Graphics()
{
	p_Interface=0;
	for (int i=0;i<MAX_STYLE;i++)
	{
		m_MaxID[i]=0;
	}
}

Graphics::~Graphics()
{
    int i;
	for (int i=0;i<m_LineArray.GetUpperBound()+1;i++)
	{
		Gis *pGis=m_LineArray.GetAt(i);
		pGis->Release();
	}

	for (i=0;i<m_CircleArray.GetUpperBound()+1;i++)
	{
		Gis *pGis=m_CircleArray.GetAt(i);
		pGis->Release();
	}
}

Line* Graphics::AddLine(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float x1, float y1, float x2, float y2)
{
	Line *p=new Line( ColorPen,  ColorBrush,  LineWide,  LineType,  Layer,  id,  Delete,  x1,  y1,  x2,  y2);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_LineArray.Add(p);
	return p;

}

CArc* Graphics::AddArc(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float CircleX, float CircleY, float CircleR, bool bFill, float Angle1, float Angle2)
{
	CArc *p=new CArc( ColorPen,  ColorBrush,  LineWide,  LineType,  Layer,  id,  Delete,  CircleX,  CircleY,  CircleR,  bFill,  Angle1,  Angle2);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_ArcArray.Add(p);
	return p;

}

Circle* Graphics::AddCircle(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float CircleX, float CircleY, float CircleR, bool bFill)
{
	Circle *p=new Circle( ColorPen,  ColorBrush,  LineWide,  LineType,  Layer,  id,  Delete,    CircleX,  CircleY,  CircleR,  bFill);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_CircleArray.Add(p);
	return p;
}

CText* Graphics::AddText(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2, float TextHeight, float TextWide, float OffWide, byte TextFont, CString text)
{
	CText *p=new CText( ColorPen,  ColorBrush,  LineWide,  LineType,  Layer,  id,  Delete,  StartX,  StartY,  Angle1,  Angle2,  TextHeight,  TextWide,  OffWide,  TextFont,  text);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_TextArray.Add(p);
	return p;
}

MLineRgn* Graphics::AddMLineRgn(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, int Number, PointStruct *PointList, bool bTransparent, bool bFill)
{
	MLineRgn *p=new MLineRgn( ColorPen,  ColorBrush,  LineWide,  LineType,  Layer,  id,  Delete,  Number,  PointList,  bTransparent,  bFill);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_MLineRgnArray.Add(p);
	return p;
}

MLine* Graphics::AddMLine(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, int Number, PointStruct *PointList)
{
	MLine *p=new MLine( ColorPen,  ColorBrush,  LineWide,  LineType,  Layer,  id,  Delete,  Number, PointList);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_MLineArray.Add(p);
	return p;
}

LineNet * Graphics::AddLineNet(short ColorPen, float x, float y, float rRadiu, short Layer, int id)
{
	LineNet *p=new LineNet( ColorPen,  x,  y,  rRadiu,  Layer,  id);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_LineNetArray.Add(p);
	return p;
}

Tag* Graphics::AddTag(short ColorPen, int Layer, bool Delete, float InsertX, float InsertY, float ScaleX, float ScaleY, float Angle, int id, int idBlock)
{
	Tag *p=new Tag( ColorPen,  Layer,  Delete,  InsertX,  InsertY,  ScaleX,  ScaleY,  Angle,  id,  idBlock);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_TagArray.Add(p);
	return p;
}

CLabel* Graphics::AddLabel(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float MaxDisp, float MinDisp,LOGFONT lf, CString text)
{
	CLabel *p=new CLabel( ColorPen,  ColorBrush,  LineWide,  LineType,  Layer,  id,  Delete,  StartX,  StartY, MaxDisp,MinDisp,lf, text);
	p->SetGraphPara(&m_GraphPara);
	p->SetInterface(p_Interface);
	m_LabelArray.Add(p);
	return p;
}


Gis* Graphics::GetGraph(short Lb, int index)//获得指定图形指定索引
{
	if (index<0)
		return 0;
	switch (Lb)
	{
	case 1://返回线
		if (index>m_LineArray.GetUpperBound())
			return 0;
		return m_LineArray.GetAt(index);
		break;
	case 2://返回连续线
		if (index>m_MLineArray.GetUpperBound())
			return 0;
		return m_MLineArray.GetAt(index);
		break;
	case 3://返回圆
		if (index>m_CircleArray.GetUpperBound())
			return 0;
		return m_CircleArray.GetAt(index);
		break;
	case 4://返回圆弧
		if (index>m_ArcArray.GetUpperBound())
			return 0;
		return m_ArcArray.GetAt(index);
		break;
	case 5://返回标注文本
		if (index>m_TextArray.GetUpperBound())
			return 0;
		return m_TextArray.GetAt(index);
		break;
	case 6://返回子图
		if (index>m_TagArray.GetUpperBound())
			return 0;
		return m_TagArray.GetAt(index);
		break;
	case 7://返回多边形
		if (index>m_MLineRgnArray.GetUpperBound())
			return 0;
		return m_MLineRgnArray.GetAt(index);
		break;
	case 8://返回网络点
		if (index>m_LineNetArray.GetUpperBound())
			return 0;
		return m_LineNetArray.GetAt(index);
		break;
	case 9://标签
		if (index>m_LabelArray.GetUpperBound())
			return 0;
		return m_LabelArray.GetAt(index);
		break;
	default:
		return 0;
		break;
	}
}



void Graphics::DeleteGraph(int Lb, int index)//删除指定图形指定索引的
{
	if (index<0)
		return ;
	switch (Lb)
	{
	case 1://返回线
		if (index>m_LineArray.GetUpperBound())
			return ;
		m_LineArray.RemoveAt(index);
		break;
	case 2://返回连续线
		if (index>m_MLineArray.GetUpperBound())
			return ;
		m_MLineArray.RemoveAt(index);
		break;
	case 3://返回圆
		if (index>m_CircleArray.GetUpperBound())
			return ;
		m_CircleArray.RemoveAt(index);
		break;
	case 4://返回圆弧
		if (index>m_ArcArray.GetUpperBound())
			return ;
		m_ArcArray.RemoveAt(index);
		break;
	case 5://返回标注文本
		if (index>m_TextArray.GetUpperBound())
			return ;
		m_TextArray.RemoveAt(index);
		break;
	case 6://返回子图
		if (index>m_TagArray.GetUpperBound())
			return ;
		m_TagArray.RemoveAt(index);
		break;
	case 7://返回多边形
		if (index>m_MLineRgnArray.GetUpperBound())
			return ;
		m_MLineRgnArray.RemoveAt(index);
		break;
	case 8://返回网络点
		if (index>m_LineNetArray.GetUpperBound())
			return ;
		m_LineNetArray.RemoveAt(index);
		break;
	case 9:
		if (index<m_LabelArray.GetUpperBound())
			return;
		m_LabelArray.RemoveAt(index);
		break;
	default:
		return ;
		break;
	}
	return;
}

int Graphics::GetGraphSize(short Lb)//获得指定图形存储的数量
{
	switch (Lb)
	{
	case 1://返回线
		return m_LineArray.GetSize();
		break;
	case 2://返回连续线
		return m_MLineArray.GetSize();
		break;
	case 3://返回圆
		return m_CircleArray.GetSize();
		break;
	case 4://返回圆弧
		return m_ArcArray.GetSize();
		break;
	case 5://返回标注文本
		return m_TextArray.GetSize();
		break;
	case 6://返回子图
		return m_TagArray.GetSize();
		break;
	case 7://返回多边形
		return m_MLineRgnArray.GetSize();
		break;
	case 8://返回网络点
		return m_LineNetArray.GetSize();
		break;
	case 9://返回标签
		return m_LabelArray.GetSize();
		break;
	default:
		return 0;
		break;
	}
}

int Graphics::GetGraphUpperBound(short Lb)//获得指定图形的最大下标
{
	switch (Lb)
	{
	case 1://返回线
		return m_LineArray.GetUpperBound();
		break;
	case 2://返回连续线
		return m_MLineArray.GetUpperBound();
		break;
	case 3://返回圆
		return m_CircleArray.GetUpperBound();
		break;
	case 4://返回圆弧
		return m_ArcArray.GetUpperBound();
		break;
	case 5://返回标注文本
		return m_TextArray.GetUpperBound();
		break;
	case 6://返回子图
		return m_TagArray.GetUpperBound();
		break;
	case 7://返回多边形
		return m_MLineRgnArray.GetUpperBound();
		break;
	case 8://返回网络点
		return m_LineNetArray.GetUpperBound();
		break;
	case 9:
		return m_LabelArray.GetUpperBound();
		break;
	default:
		return -1;
		break;
	}
}

int Graphics::GetGraphIndex(short Lb, int ID)//查找指定ID的图形存放下标
{
	int MaxBound=this->GetGraphUpperBound(Lb);
	for (int i=0;i<MaxBound;i++)
	{
		Gis *pGis=this->GetGraph(Lb,i);
		if (pGis && pGis->GetID()==ID)
			return i;
	}
	return -1;
}

LineNet * Graphics::AddLineNetToLineNet(int sID, int eID)
{
	int index=this->GetGraphIndex(G_LINENET,sID);
	LineNet *pnet=NULL;
	if (index>=0)
	{
		pnet=(LineNet*)this->GetGraph(G_LINENET,index);
		pnet->AddLink(eID);
	}
	return pnet;
}


void Graphics::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	for (int i=0;i<=MAX_STYLE;i++)
	{
		int nn=this->GetGraphUpperBound(i)+1;
		while (nn--)
		{
			Gis *pGis=this->GetGraph(i,nn);
			if (pGis)
				pGis->Draw(pDC,DrawMode,DrawMode1,BackColor);
		}
	}
}

void Graphics::DrawBack(CDC *pDC,int cx,int cy,int bColor)
{
	CBrush brush(this->m_GraphPara.GetColor(bColor));
	CBrush *pOldBrush=pDC->SelectObject(&brush);
	pDC->PatBlt(0,0,cx,cy,PATCOPY);
	pDC->SelectObject(pOldBrush);
}

int Graphics::CreateID(int Lb)
{
	return ++m_MaxID[Lb];
}

void Graphics::SetInterface(void *p)
{
	p_Interface=p;
}


BOOL Graphics::GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY)
{
	
	MinX=(float)1E+20;
	MinY=(float)1E+20;
	MaxX=(float)1E-20;
	MaxY=(float)1E-20;


	float minx,miny,maxx,maxy;
	BOOL pb;
	minx=(float)1E+20;
	miny=(float)1E+20;
	maxx=(float)1E-20;
	maxy=(float)1E-20;
	pb=0;
	for (int i=0;i<MAX_STYLE;i++)
	{
		int nn=this->GetGraphUpperBound(i)+1;
		while (nn--)
		{
			if (this->GetGraph(i,nn))
				this->GetGraph(i,nn)->GetRect(minx,miny,maxx,maxy);
			else
				continue;

			pb=1;

			if (MinX>minx)
				MinX=minx;

			if (MinY>miny)
				MinY=miny;

			
			if (MaxX<maxx)
				MaxX=maxx;

			if (MaxY<maxy)
				MaxY=maxy;

		}
	}
	return pb;
}

void Graphics::Serialize(CArchive &ar)
{	
	m_GraphPara.Serialize(ar);
//	m_LineArray.Serialize(ar);
//	m_MLineArray.Serialize(ar);
//	m_MLineRgnArray.Serialize(ar);
	m_CircleArray.Serialize(ar);


	if (ar.IsStoring())
	{
		for (int i=0;i<MAX_STYLE;i++)
		{
			ar<<m_MaxID[i];
		}
	}
	else
	{
		for (int i=0;i<MAX_STYLE;i++)
		{
			ar>>m_MaxID[i];
		}
	}
}
