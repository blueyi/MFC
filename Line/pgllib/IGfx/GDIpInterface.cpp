// GDIpInterface.cpp: implementation of the CGDIpInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "GDIpInterface.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace gfxinterface
{

CGDIpInterface::CGDIpInterface()
{
	m_pGraphics = NULL;
	m_pDash=NULL;
}

CGDIpInterface::~CGDIpInterface()
{
	ASSERT(m_lStates.empty());

	if( m_pDash)
	{
		delete[] m_pDash;
		m_pDash=NULL;
	}
}

void CGDIpInterface::BeginPaint()
{	
	CGfxInterface::BeginPaint();

	ASSERT(m_pGraphics); 
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	ASSERT(!m_pDash);
	ASSERT(m_lStates.empty());

	m_curState.m_curColor=Gdiplus::Color(0,0,0);
	m_curState.m_fillColor=Gdiplus::Color(1,1,1);
	m_curState.m_lineWidth=1;
	GetDefaultLOGFONT(m_curState.m_font);
	m_curState.m_dash.clear();

	m_pGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	m_pGraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::EndPaint()			
{	
	CGfxInterface::EndPaint();

	m_pGraphics = NULL;
	ASSERT(m_lStates.empty());
};

void CGDIpInterface::PushState()
{	
	ASSERT(m_pGraphics); 
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	// saving state
	SGDIpState oldstate=m_curState;
	m_lStates.push(oldstate);

	// saving state in GDI+
	oldstate.m_gState=m_pGraphics->Save();
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::PopState()
{	
	ASSERT(m_pGraphics); 
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	// restoring state
	m_curState=m_lStates.top();
	m_pGraphics->Restore(m_curState.m_gState);	
	m_lStates.pop();

	// delete dash if needed
	if(m_pDash)
	{
		delete[] m_pDash;
		m_pDash=NULL;
	}

	if (!m_curState.m_dash.empty())
	{
		m_pDash = new Gdiplus::REAL[ m_curState.m_dash.size()];
		std::list<Gdiplus::REAL>::const_iterator ir;
		UINT i;
		for (ir=m_curState.m_dash.begin(), i=0;ir!=m_curState.m_dash.end();ir++,i++)
			m_pDash[i]=*ir;
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};


void CGDIpInterface::DrawArrow(double tailx, double taily, double tipx, double tipy, double tailthickness, double  headthickness, double headlength, bool filled)
{
}

void CGDIpInterface::DrawArrowAbs(double tailx, double taily, double dtipx, double dtipy, double tailthickness, double  headthickness, double headlength, bool filled)
{
}

void CGDIpInterface::DrawLine(double x1, double y1, double x2, double y2)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);

	m_pGraphics->DrawLine(&pen, (Gdiplus::REAL)WorldToBBx(x1), (Gdiplus::REAL)WorldToBBy(y1), 
		(Gdiplus::REAL)WorldToBBx(x2), (Gdiplus::REAL)WorldToBBy(y2));
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawLineStrip(int n, double* pX, double* pY, bool open, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	if (n==0)
		return;

	Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);

	//allocating memory
	Gdiplus::PointF* pPoints;

	if (!filled)
		pPoints = new Gdiplus::PointF[n];
	else
	{
		// adding bottom if filled
		pPoints = new Gdiplus::PointF[n+2];
	}


	for (UINT i=0;i<n;i++)
	{
		pPoints[i].X = (float) WorldToBBx(pX[i]);
		pPoints[i].Y = (float) WorldToBBy(pY[i]);
	}

	if (filled)
	{
		pPoints[n].X=WorldToBBx(pX[n-1]);
		pPoints[n].Y=GetBBClipBottom();
		pPoints[n+1].X=WorldToBBx(pX[0]);
		pPoints[n+1].Y=GetBBClipBottom();
	}

	if (open)	
	{
		// Drawing
		m_pGraphics->DrawLines(&pen, pPoints, (INT)n);
	}
	else
	{
		if (!filled)
		{
			m_pGraphics->DrawClosedCurve(&pen, pPoints, (INT)n, 0);
		}
		else
		{
			Gdiplus::SolidBrush brush(m_curState.m_fillColor);
			m_pGraphics->FillClosedCurve(&brush, pPoints, (INT)n+2, Gdiplus::FillModeWinding, 0);
		}
	}

	// cleaning
	delete[] pPoints;
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawMultipleLineStrip(int n, int ns, double* pX, double* pY, bool open, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	
	INT nscur, index;
	Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);

	//allocating memory
	Gdiplus::PointF* pPoints;

	if (!filled)
	{
		pPoints = new Gdiplus::PointF[ns];
	}
	else
	{
		// adding bottom if filled
		pPoints = new Gdiplus::PointF[ns+2];
	}

	index=0;
	nscur=0;
	do
	{
		nscur=__min(ns,n-index);
		for (UINT i=index;i<index+nscur;i++)
		{
			pPoints[i-index].X = (float) WorldToBBx(pX[i]);
			pPoints[i-index].Y = (float) WorldToBBy(pY[i]);
		}
		if (filled)
		{
			pPoints[nscur].X=WorldToBBx(pX[index+nscur-1]);
			pPoints[nscur].Y=GetBBClipBottom();
			pPoints[nscur+1].X=WorldToBBx(pX[index]);
			pPoints[nscur+1].Y=GetBBClipBottom();
		}
	
		if (open)
		{
			// Drawing
			m_pGraphics->DrawLines(&pen, pPoints, (INT)nscur);
		}
		else
		{
			if (!filled)
			{
				m_pGraphics->DrawClosedCurve(&pen, pPoints, (INT)nscur, 0);
			}
			else
			{
				Gdiplus::SolidBrush brush(m_curState.m_fillColor);
				m_pGraphics->FillClosedCurve(&brush, pPoints, (INT)nscur+2, Gdiplus::FillModeWinding, 0);
			} 
		}

		// udpating index...
		index+=ns;
	} while (index<n);

	// cleaning
	delete[] pPoints;
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}


void CGDIpInterface::DrawStepStrip(int n, double* pX, double* pY, bool open, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);

	//allocating memory
	//allocating memory
	Gdiplus::PointF* pPoints;

	if (!filled)
		pPoints = new Gdiplus::PointF[n*2-2];
	else
	{
		// adding bottom if filled
		pPoints = new Gdiplus::PointF[2*n];
	}


	for (UINT i=0;i<n-1;i++)
	{
		pPoints[2*i].X = (float) WorldToBBx(pX[i]);
		pPoints[2*i].Y = (float) WorldToBBy(pY[i]);

		pPoints[2*i+1].X = (float) WorldToBBx(pX[i+1]);
		pPoints[2*i+1].Y = (float) WorldToBBy(pY[i]);
	}

	if (filled)
	{
		pPoints[2*n-2].X=WorldToBBx(pX[n-1]);
		pPoints[2*n-2].Y=GetBBClipBottom();
		pPoints[2*n-1].X=WorldToBBx(pX[0]);
		pPoints[2*n-1].Y=GetBBClipBottom();
	}

	if (open)
	{
		// Drawing
		m_pGraphics->DrawLines(&pen, pPoints, (INT)(n*2-2)) ;
	}
	else
	{
		if (!filled)
		{
			m_pGraphics->DrawClosedCurve(&pen, pPoints, (INT)(n*2-2), 0);
		}
		else
		{
			Gdiplus::SolidBrush brush(m_curState.m_fillColor);
			m_pGraphics->FillClosedCurve(&brush, pPoints, (INT)(n*2), Gdiplus::FillModeWinding,0);
		}
	}

	// cleaning
	delete[] pPoints;
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawGridHor(double llx, double urx, double lly, double ury,double dy)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth);
	SetCurPenState(pen);

	UINT n = (UINT)floor( (ury-lly)/dy)+1;

	n=__min(n,100);
	for (UINT i=0;i<n;i++)
	{
		m_pGraphics->DrawLine(&pen,
			(float) WorldToBBx(llx),
			(float) WorldToBBy(lly+i*dy),
			(float) WorldToBBx(urx),
			(float) WorldToBBy(lly+i*dy));
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawGridVer(double llx, double urx, double lly, double ury,double dx)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth);
	SetCurPenState(pen);

	UINT n = (UINT)floor( (urx-llx)/dx)+1;

	n=__min(n,100);
	for (UINT i=0;i<n;i++)
	{
		m_pGraphics->DrawLine(&pen,
			(float) WorldToBBx(llx+i*dx),
			(float) WorldToBBy(lly),
			(float) WorldToBBx(llx+i*dx),
			(float) WorldToBBy(ury));
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawRect(double llx, double lly, double urx, double ury, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		m_pGraphics->FillRectangle(&brush, (Gdiplus::REAL)WorldToBBx(llx),(Gdiplus::REAL)WorldToBBy(ury),
			(Gdiplus::REAL)WorldToBBAbsx(urx-llx),(Gdiplus::REAL)WorldToBBAbsy(ury-lly));
	}

	Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
	m_pGraphics->DrawRectangle(&pen, (Gdiplus::REAL)WorldToBBx(llx),(Gdiplus::REAL)WorldToBBy(ury),
		(Gdiplus::REAL)WorldToBBAbsx(urx-llx),(Gdiplus::REAL)WorldToBBAbsy(ury-lly));

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawBox(double llx, double lly, double dx, double dy, bool filled)
{
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		m_pGraphics->FillRectangle(&brush, 
			(Gdiplus::REAL)WorldToBBx(llx), 
			(Gdiplus::REAL)(WorldToBBy(lly)+dy),(Gdiplus::REAL)dx,(Gdiplus::REAL)dy );
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		m_pGraphics->DrawRectangle(&pen, 
			(Gdiplus::REAL)WorldToBBx(llx), 
			(Gdiplus::REAL)(WorldToBBy(lly)+dy),(Gdiplus::REAL)dx,(Gdiplus::REAL)dy );
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawCircle(double cx, double cy, double radius, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	Gdiplus::RectF rect(WorldToBBx(cx)-radius, WorldToBBy(cy)-radius, 2*radius, 2*radius);

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		m_pGraphics->FillEllipse(&brush,rect);
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		m_pGraphics->DrawEllipse(&pen, rect);
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawTriangle(double cx, double cy, double radius, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	static Gdiplus::PointF tri[3];
	double sr3 = radius/(sqrt(3));
	tri[0].X=WorldToBBx(cx)-sqrt(2)*sr3;
	tri[0].Y=WorldToBBy(cy)+sr3;
	tri[1].X=WorldToBBx(cx)+sqrt(2)*sr3;
	tri[1].Y=WorldToBBy(cy)+sr3;
	tri[2].X=WorldToBBx(cx);
	tri[2].Y=WorldToBBy(cy)-radius*sqrt(2)/2;

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);

		m_pGraphics->FillClosedCurve(&brush,tri,(INT)3, Gdiplus::FillModeWinding,0);
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		m_pGraphics->DrawClosedCurve(&pen, tri,(INT)3,0);
	}

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawSquare(double cx, double cy, double radius, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		m_pGraphics->FillRectangle(&brush, 
			(Gdiplus::REAL)(WorldToBBx(cx)-radius), 
			(Gdiplus::REAL)(WorldToBBy(cy)-radius), (Gdiplus::REAL)(2*radius), (Gdiplus::REAL)(2*radius));
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		m_pGraphics->DrawRectangle(&pen, 
			(Gdiplus::REAL)(WorldToBBx(cx)-radius), 
			(Gdiplus::REAL)(WorldToBBy(cy)-radius),(Gdiplus::REAL)(2*radius),(Gdiplus::REAL)(2*radius));
	}

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawBoxStrip(int n, double* pLlx, double* pLly, double dx, double dy, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		for (UINT i=0;i<n;i++)
			m_pGraphics->FillRectangle(&brush, 
				(Gdiplus::REAL)(WorldToBBx(pLlx[i])-dx/2), 
				(Gdiplus::REAL)(WorldToBBy(pLly[i])-dy/2),(Gdiplus::REAL)dx,(Gdiplus::REAL)dy);
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		for (UINT i=0;i<n;i++)
			m_pGraphics->DrawRectangle(&pen, 
				(Gdiplus::REAL)(WorldToBBx(pLlx[i])-dx/2), 
				(Gdiplus::REAL)(WorldToBBy(pLly[i])-dy/2),(Gdiplus::REAL)dx,(Gdiplus::REAL)dy);
	}

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawCircleStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	Gdiplus::RectF rect(0,0,2*radius,2*radius);

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		for (UINT i=0;i<n;i++)
		{
			rect.X=WorldToBBx(pCx[i])-radius;
			rect.Y=WorldToBBy(pCy[i])-radius;
			m_pGraphics->FillEllipse(&brush,rect);
		}
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		for (UINT i=0;i<n;i++)
		{
			rect.X=WorldToBBx(pCx[i])-radius;
			rect.Y=WorldToBBy(pCy[i])-radius;
			m_pGraphics->DrawEllipse(&pen, rect);
		}
	}

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawTriangleStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	static Gdiplus::PointF tri[3];
	double sr3 = radius/(sqrt(3));

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		for (UINT i=0;i<n;i++)
		{
			tri[0].X=WorldToBBx(pCx[i])-sqrt(2)*sr3;
			tri[0].Y=WorldToBBy(pCy[i])+sr3;
			tri[1].X=WorldToBBx(pCx[i])+sqrt(2)*sr3;
			tri[1].Y=WorldToBBy(pCy[i])+sr3;
			tri[2].X=WorldToBBx(pCx[i]);
			tri[2].Y=WorldToBBy(pCy[i])-radius*sqrt(2)/2;
			m_pGraphics->FillClosedCurve(&brush,tri,(INT)3, Gdiplus::FillModeWinding,0);
		}
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		for (UINT i=0;i<n;i++)
		{
			tri[0].X=WorldToBBx(pCx[i])-sqrt(2)*sr3;
			tri[0].Y=WorldToBBy(pCy[i])+sr3;
			tri[1].X=WorldToBBx(pCx[i])+sqrt(2)*sr3;
			tri[1].Y=WorldToBBy(pCy[i])+sr3;
			tri[2].X=WorldToBBx(pCx[i]);
			tri[2].Y=WorldToBBy(pCy[i])-radius*sqrt(2)/2;
			m_pGraphics->DrawClosedCurve(&pen, tri,(INT)3,0);
		}
	}

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawSquareStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

	if (filled)
	{
		Gdiplus::SolidBrush brush(m_curState.m_fillColor);
		for (UINT i=0;i<n;i++)
			m_pGraphics->FillRectangle(&brush, 
				(Gdiplus::REAL)(WorldToBBx(pCx[i])-radius), 
				(Gdiplus::REAL)(WorldToBBy(pCy[i])-radius), (Gdiplus::REAL)(2*radius), (Gdiplus::REAL)(2*radius));
	}
	else
	{
		Gdiplus::Pen pen(m_curState.m_curColor, m_curState.m_lineWidth); SetCurPenState(pen);
		for (UINT i=0;i<n;i++)
			m_pGraphics->DrawRectangle(&pen, 
				(Gdiplus::REAL)(WorldToBBx(pCx[i])-radius), 
				(Gdiplus::REAL)(WorldToBBy(pCy[i])-radius),(Gdiplus::REAL)(2*radius),(Gdiplus::REAL)(2*radius));
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
}

void CGDIpInterface::DrawSurf(int nx, int ny, double llx, double lly, double dx, double dy, double* pColor)
{
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	ASSERT(m_pGraphics);
	int i,j,k;
	int index[4];
	double r,g,b;
	Gdiplus::PointF psF[4];
	Gdiplus::Color colors[4];
	Gdiplus::Color center;
	Gdiplus::RectF rect;

	for (i=0;i<ny-1;i++)
	{	
		for (j=0;j<nx-1;j++)
		{
			index[0]  = i*nx+j;
			index[1]  = (i+1)*nx+j;
			index[2]  = (i+1)*nx+j+1;
			index[3]  = i*nx+j+1;

			r=g=b=0;
			for (k=0; k<4; k++)
			{
				colors[k]= Gdiplus::Color( (INT)floor(pColor[index[k]*3]*255), 
					(INT)floor(pColor[index[k]*3+1]*255),
					(INT)floor(pColor[index[k]*3+2]*255));
				r+=pColor[index[k]*3];
				g+=pColor[index[k]*3+1];
				b+=pColor[index[k]*3+2];
			}
			center = Gdiplus::Color((INT)floor(r/4*255.0),(INT)floor(g/4*255.0),(INT)floor(b/4*255.0));
				
			psF[0]=Gdiplus::PointF(WorldToBBx(llx + j*dx)-1,WorldToBBy(lly + (ny-(i+1))*dy) -1);
			psF[1]=Gdiplus::PointF(WorldToBBx(llx + j*dx)-1,WorldToBBy(lly + (ny-(i+1)-1)*dy)+1 );
			psF[2]=Gdiplus::PointF(WorldToBBx(llx + (j+1)*dx)+1,WorldToBBy(lly + (ny-(i+1)-1)*dy)+1 );
			psF[3]=Gdiplus::PointF(WorldToBBx(llx + (j+1)*dx)+1,WorldToBBy(lly + (ny-(i+1))*dy)-1 );

			Gdiplus::PathGradientBrush brush(psF,4);
			int count = 4;
			brush.SetSurroundColors(colors, &count);	
			brush.SetCenterColor(center);

			m_pGraphics->FillRectangle(&brush,
				Gdiplus::RectF(WorldToBBx(llx + j*dx)-1,WorldToBBy(lly + (ny-(i+1))*dy)-1, WorldToBBAbsx(dx)+2, WorldToBBAbsy(dy)+2));
		}
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawTextLeft(double x, double y, const char* str, double angle)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);

/*	HDC hDC = m_pGraphics->GetHDC();
	// setting size of font
	long lfHeight=m_curState.m_font.lfHeight;
	m_curState.m_font.lfHeight= -MulDiv(m_curState.m_font.lfHeight, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	Gdiplus::Font        font(hDC, &m_curState.m_font);
	// reseting changes
	m_curState.m_font.lfHeight=lfHeight;
	m_pGraphics->ReleaseHDC(hDC);
*/
	Gdiplus::FontFamily  fontFamily(L"Verdana");
	Gdiplus::Font        font(&fontFamily, abs(m_curState.m_font.lfHeight), Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
	Gdiplus::SolidBrush  solidBrush(m_curState.m_curColor);
	Gdiplus::PointF      pointF(WorldToBBx(x), WorldToBBy(y));
	Gdiplus::StringFormat sf;
	Gdiplus::GraphicsContainer  graphicsContainer;
	int nchar;
	angle = NormalizeAngle(angle);
	
	nchar=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,str,-1,m_wBuffer,2048);
	if (nchar)
	{
		pointF.Y-=m_curState.m_font.lfHeight;
		if (angle==0)
		{
			m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);
		}
		else
		{
			graphicsContainer = m_pGraphics->BeginContainer();
			m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
			m_pGraphics->TranslateTransform(pointF.X,pointF.Y);
			m_pGraphics->RotateTransform(-angle);
			m_pGraphics->TranslateTransform(-pointF.X,-pointF.Y);
			m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);
			m_pGraphics->EndContainer(graphicsContainer);
		}
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawTextRight(double x, double y, const char* str, double angle)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
/*
	HDC hDC = m_pGraphics->GetHDC();
	// setting size of font
	long lfHeight=m_curState.m_font.lfHeight;
	m_curState.m_font.lfHeight= -MulDiv(m_curState.m_font.lfHeight, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	Gdiplus::Font        font(hDC, &m_curState.m_font);
	// reseting changes
	m_curState.m_font.lfHeight=lfHeight;
	m_pGraphics->ReleaseHDC(hDC);
*/
	Gdiplus::FontFamily  fontFamily(L"Verdana");
	Gdiplus::Font        font(&fontFamily, abs(m_curState.m_font.lfHeight), Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
	Gdiplus::SolidBrush  solidBrush(m_curState.m_curColor);
	Gdiplus::PointF      pointF(WorldToBBx(x), WorldToBBy(y));
	Gdiplus::RectF		boundingbox;
	Gdiplus::StringFormat sf;
	Gdiplus::GraphicsContainer  graphicsContainer;
	int nchar;

	sf.SetAlignment(Gdiplus::StringAlignmentFar);
	angle = NormalizeAngle(angle);

	nchar=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,str,-1,m_wBuffer,2048);
	if (nchar)
	{
		pointF.Y-=m_curState.m_font.lfHeight;
		if (angle==0)
		{
			m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);
		}
		else
		{
			graphicsContainer = m_pGraphics->BeginContainer();
			m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
			m_pGraphics->TranslateTransform(pointF.X,pointF.Y);
			m_pGraphics->RotateTransform(-angle);
			m_pGraphics->TranslateTransform(-pointF.X,-pointF.Y);

			m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);

			m_pGraphics->EndContainer(graphicsContainer);
		}
	}
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::DrawTextCenter(double x, double y, const char* str, double angle)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
/*
	HDC hDC = m_pGraphics->GetHDC();
	// setting size of font
	long lfHeight=m_curState.m_font.lfHeight;
	m_curState.m_font.lfHeight= -MulDiv(m_curState.m_font.lfHeight, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	Gdiplus::Font        font(hDC, &m_curState.m_font);
	// reseting changes
	m_curState.m_font.lfHeight=lfHeight;
	m_pGraphics->ReleaseHDC(hDC);
*/
	Gdiplus::FontFamily  fontFamily(L"Verdana");
	Gdiplus::Font        font(&fontFamily, abs(m_curState.m_font.lfHeight), Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
	Gdiplus::PointF      pointF(WorldToBBx(x), WorldToBBy(y));
	Gdiplus::RectF		boundingbox;
	Gdiplus::SolidBrush  solidBrush(m_curState.m_curColor);
	Gdiplus::StringFormat sf;
	Gdiplus::GraphicsContainer  graphicsContainer;
	int nchar;

	angle = NormalizeAngle(angle);

	sf.SetAlignment(Gdiplus::StringAlignmentCenter);

	nchar=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,str,-1,m_wBuffer,2048);
	if (nchar)
	{
		if (angle==0)
		{
			pointF.Y-=m_curState.m_font.lfHeight;
			m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);
		}
		else
		{
			graphicsContainer = m_pGraphics->BeginContainer();
			m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
			m_pGraphics->TranslateTransform(pointF.X,pointF.Y);
			m_pGraphics->RotateTransform(-angle);
			m_pGraphics->TranslateTransform(-pointF.X,-pointF.Y);

			pointF.Y-=m_curState.m_font.lfHeight;
			m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);

			m_pGraphics->EndContainer(graphicsContainer);
		}
	}

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};


void CGDIpInterface::DrawTextStrip(const std::vector<SPointF>& vPoints, const std::vector<std::string>& vStrings, ETextAlignment ta, double angle)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	ASSERT(vPoints.size() == vStrings.size());
/*
	HDC hDC = m_pGraphics->GetHDC();
	// setting size of font
	long lfHeight=m_curState.m_font.lfHeight;
	m_curState.m_font.lfHeight= -MulDiv(m_curState.m_font.lfHeight, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	Gdiplus::Font        font(hDC, &m_curState.m_font);
	// reseting changes
	m_curState.m_font.lfHeight=lfHeight;
	m_pGraphics->ReleaseHDC(hDC);
*/
	Gdiplus::FontFamily  fontFamily(L"Verdana");
	Gdiplus::Font        font(&fontFamily, abs(m_curState.m_font.lfHeight), Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
	Gdiplus::SolidBrush  solidBrush(m_curState.m_curColor);
	Gdiplus::PointF      pointF;
	Gdiplus::RectF		boundingbox;
	Gdiplus::GraphicsContainer  graphicsContainer;
	Gdiplus::StringFormat sf;
	int nchar;
	UINT i;
	const UINT n = vStrings.size();
	angle = NormalizeAngle(angle);

	// text alignement
	switch(ta)
	{
	case  TextAlignmentRight:
		sf.SetAlignment(Gdiplus::StringAlignmentFar);
		break;
	case  TextAlignmentCenter:
		sf.SetAlignment(Gdiplus::StringAlignmentCenter);
		break;
	}

	if (angle==0)
	{
		for (i=0;i<n;i++)
		{
			nchar=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,vStrings[i].c_str(),-1,m_wBuffer,2048);
			if (nchar)
			{
				pointF.X=WorldToBBx(vPoints[i].x);
				pointF.Y=WorldToBBy(vPoints[i].y)-m_curState.m_font.lfHeight;
				m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);
			}
		}
	}
	else
	{
		// setting vertical text
		for (i=0;i<n;i++)
		{
			nchar=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,vStrings[i].c_str(),-1,m_wBuffer,2048);
			if (nchar)
			{
				pointF.X=WorldToBBx(vPoints[i].x);
				pointF.Y=WorldToBBy(vPoints[i].y)-m_curState.m_font.lfHeight;

				graphicsContainer = m_pGraphics->BeginContainer();
				m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
				m_pGraphics->TranslateTransform(pointF.X,pointF.Y);
				m_pGraphics->RotateTransform(-angle);
				m_pGraphics->TranslateTransform(-pointF.X,-pointF.Y);
				m_pGraphics->DrawString(m_wBuffer, -1, &font, pointF, &sf,&solidBrush);
				m_pGraphics->EndContainer(graphicsContainer);
			}
		}
	}

	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
};

void CGDIpInterface::SetCurPenState(Gdiplus::Pen &pen)
{
	if (!m_curState.m_dash.empty())
	{
		ASSERT(m_pDash);
		pen.SetDashPattern( m_pDash, m_curState.m_dash.size());
	}
}

void CGDIpInterface::SetDash(const char* dash)
{	
	m_curState.m_dash.clear();

	// no dashing
	if (dash == "")
	{
		if (m_pDash)
		{
			delete[] m_pDash;
			m_pDash=NULL;
		}
		m_curState.m_dash.clear();
		return;
	}

	std::istrstream istr(dash);	
	int length;

	while ( !istr.eof())
	{
		istr>>length;
		m_curState.m_dash.push_back(length);
	}	

	if(m_pDash)
	{
		delete[] m_pDash;
		m_pDash=NULL;
	}

	if (!m_curState.m_dash.empty())
	{
		m_pDash = new Gdiplus::REAL[ m_curState.m_dash.size()];
		std::list<Gdiplus::REAL>::const_iterator ir;
		UINT i;
		for (ir=m_curState.m_dash.begin(), i=0;ir!=m_curState.m_dash.end();ir++,i++)
			m_pDash[i]=*ir;
	}
};


int CGDIpInterface::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

Gdiplus::RectF CGDIpInterface::MeasureString(LPCSTR str)
{
	ASSERT(m_pGraphics);
	ASSERT(m_pGraphics->GetLastStatus()==Gdiplus::Ok);
	Gdiplus::Font        font(m_pGraphics->GetHDC(), &m_curState.m_font);
	Gdiplus::PointF      origin(0,0);
	Gdiplus::RectF		boundingBox;
	int nchar;

	ASSERT(m_pGraphics);

	nchar=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,str,-1,m_wBuffer,2048);
	if (nchar)
	{
		m_pGraphics->MeasureString(m_wBuffer, -1, &font, origin, &boundingBox);
	}

	return boundingBox;
}


} // end namespace gfxinterface
