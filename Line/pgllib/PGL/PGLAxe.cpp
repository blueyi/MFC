// AxeGL.cpp: implementation of the CPGLAxe2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLAxe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <float.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPGLAxe2D, CPGLObject,1);


void CPGLAxe2D::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLObject::Serialize( archive );
	int i;
	for (i=0;i<4;i++)
	{
		m_pLabels[i].Serialize(archive);
		m_pNumbers[i].Serialize(archive);
	}

	for (i=0;i<2;i++)
	{
	    if( archive.IsStoring() )
			archive << m_pStarts[i] << m_pEnds[i] 
			<< m_pSteps[i] << m_pAutoSteps[i] << m_pGridVisible[i]<<m_pLogAxis[i];
	    else
			archive >> m_pStarts[i] >> m_pEnds[i] 
			>> m_pSteps[i] >> m_pAutoSteps[i] >> m_pGridVisible[i]>>m_pLogAxis[i];
	}

	if( archive.IsStoring() )
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CPGLAxe2D::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLObject::Dump( dc );

	// now dumping..
	dc << _T("--- CPGLAxe2D ID ") << GetID() <<_T(" --- ")<< endl;
	dc <<_T("Bounding box : bottom : ")<<m_pStarts[1]<<
		_T(" top : ")<<m_pEnds[1]<<
		_T(" left : ")<<m_pStarts[0]<<
		_T(" right : ")<<m_pEnds[0]<<endl;
}

void CPGLAxe2D::AssertValid() const
{
    // call inherited AssertValid first
    CPGLObject::AssertValid();

	ASSERT_VALID(m_pView);
	for (int i=0;i<4;i++)
	{
		m_pLabels[i].AssertValid();
	}
} 
#endif

CPGLAxe2D::CPGLAxe2D(CPGLView2D* pView)
: CPGLObject()
{
	SetColor(0.0,0.0,0.0,1.0f);
	for (int i=0;i<2;i++)
	{
		m_pStarts[i]=0.0;
		m_pEnds[i]=1.0;
		m_pAutoSteps[i]=TRUE;
		// setting m_pSteps
		GenerateSteps(i);
		m_pGridVisible[i]=TRUE;
		m_pLogAxis[i]=FALSE;
	}

	m_pView=pView;

	m_bTimeLabel = FALSE;
	m_tTimeLabelOrig = CTime::GetCurrentTime();
	m_tsDt = CTimeSpan(0,1,0,0);
	m_sTimeLabel = "%H";

	SetName("Axis");

	m_rBorders.left=40;
	m_rBorders.right=40;
	m_rBorders.top=40;
	m_rBorders.bottom=40;

	m_pLabels[0]=CPGLText(_T("x"));
	m_pLabels[0].SetName("Bottom label");
	m_pLabels[0].SetAlign(PGL_TEXT_ALIGN_CENTER);

	m_pLabels[1]=CPGLText(_T("y"));
	m_pLabels[1].SetName("Left label");
	m_pLabels[1].SetAngle(90);
	m_pLabels[1].SetAlign(PGL_TEXT_ALIGN_CENTER);

	m_pLabels[2]=CPGLText(_T("y"));
	m_pLabels[2].SetName("Right label");
	m_pLabels[2].SetAngle(90);
	m_pLabels[2].SetAlign(PGL_TEXT_ALIGN_CENTER);
	m_pLabels[2].Hide();

	m_pLabels[3]=CPGLText(_T("Title"));
	m_pLabels[3].SetName("Top label");
	m_pLabels[3].SetAlign(PGL_TEXT_ALIGN_CENTER);

	// numbering
	m_pNumbers[0]=CPGLText(_T(""));
	m_pNumbers[0].SetName("Bottom numbering");
	m_pNumbers[0].SetAlign(PGL_TEXT_ALIGN_CENTER);
	m_pNumberPos[0]=0;

	m_pNumbers[1]=CPGLText(_T(""));
	m_pNumbers[1].SetName("Left Numbering");
	m_pNumbers[1].SetAlign(PGL_TEXT_ALIGN_RIGHT);
	m_pNumberPos[1]=0;

	m_pNumbers[2]=CPGLText(_T(""));
	m_pNumbers[2].SetName("Top Numbering");
	m_pNumbers[2].SetAlign(PGL_TEXT_ALIGN_LEFT);
	m_pNumbers[2].Hide();
	m_pNumberPos[2]=1;

	m_pNumbers[3]=CPGLText(_T(""));
	m_pNumbers[3].SetName("Top Numbering");
	m_pNumbers[3].SetAlign(PGL_TEXT_ALIGN_CENTER);
	m_pNumbers[3].Hide();
	m_pNumberPos[3]=1;

	for (i=0;i<4;i++)
	{
		m_pMainTicksSize[i]=8;
		m_pSecondTicksSize[i]=6;
		m_pSecondTicksNb[i]=1;
	}

	LoadBitmap(IDB_PGL_AXE2D_BITMAP);
}

CPGLAxe2D::CPGLAxe2D(const CPGLAxe2D& a)
: CPGLObject(a)
{
	int i;

	for (i=0;i<4;i++)
	{
		m_pLabels[i]=a.m_pLabels[i];
		m_pNumbers[i]=a.m_pNumbers[i];
		m_pNumberPos[i]=a.m_pNumberPos[i];
		m_pMainTicksSize[i]=a.m_pMainTicksSize[i];
		m_pSecondTicksSize[i]=a.m_pSecondTicksSize[i];
		m_pSecondTicksNb[i]=a.m_pSecondTicksNb[i];
	}

	// copy the operand
	for (i=0;i<2;i++)
	{
		m_pStarts[i]=a.m_pStarts[i];
		m_pEnds[i]=a.m_pEnds[i];
		m_pSteps[i]=a.m_pSteps[i];
		m_pAutoSteps[i]=a.m_pAutoSteps[i];
		m_pGridVisible[i]=a.m_pGridVisible[i];
		m_pLogAxis[i]=a.m_pLogAxis[i];
	}

	m_rBorders=a.m_rBorders;

	m_pView=a.m_pView;

	m_bTimeLabel = a.m_bTimeLabel;
	m_tsDt = a.m_tsDt;
	m_tTimeLabelOrig = a.m_tTimeLabelOrig;
	m_sTimeLabel = a.m_sTimeLabel;
	
	LoadBitmap(IDB_PGL_AXE2D_BITMAP);
}

CPGLAxe2D& CPGLAxe2D::operator=(const CPGLAxe2D& a)
{
	int i;
	// prevent self-assignement
	if (&a != this)
	{
		// invoke CPGLObject copy assignement operator
		this->CPGLObject::operator =(a);

		// copy the operand
		for (i=0;i<4;i++)
		{
			m_pLabels[i]=a.m_pLabels[i];
			m_pNumbers[i]=a.m_pNumbers[i];
			m_pNumberPos[i]=a.m_pNumberPos[i];
			m_pMainTicksSize[i]=a.m_pMainTicksSize[i];
			m_pSecondTicksSize[i]=a.m_pSecondTicksSize[i];
			m_pSecondTicksNb[i]=a.m_pSecondTicksNb[i];
		}

		for (i=0;i<2;i++)
		{
			m_pStarts[i]=a.m_pStarts[i];
			m_pEnds[i]=a.m_pEnds[i];
			m_pSteps[i]=a.m_pSteps[i];
			m_pAutoSteps[i]=a.m_pAutoSteps[i];
			m_pGridVisible[i]=a.m_pGridVisible[i];
			m_pLogAxis[i]=a.m_pLogAxis[i];
		}

		m_rBorders=a.m_rBorders;
		m_pView=a.m_pView;
		m_bTimeLabel = a.m_bTimeLabel;
		m_tTimeLabelOrig = a.m_tTimeLabelOrig;
		m_tsDt = a.m_tsDt;
		m_sTimeLabel = a.m_sTimeLabel;
	}
	return *this;
}

	/// destructor
CPGLAxe2D::~CPGLAxe2D()
{
};

void CPGLAxe2D::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	if (!IsVisible())
		return;

	// calling base class function
	CPGLObject::PlotGfx(gfx);

	// commentary
	gfx.AddComment("--- CPGLAxe2D ---");	

	// x grid
	if (m_pGridVisible[0])
		DrawGridGfx(0,gfx);
	// y grid
	if (m_pGridVisible[1])
		DrawGridGfx(1,gfx);

	// line of axe
	DrawLinesGfx(gfx);

	// draw numbering
	DrawNumbersGfx(gfx);
}

void CPGLAxe2D::SetLimits(int iaxe,double _start, double _end)
{
	// setting datas
	ASSERT(iaxe>=0);
	ASSERT(iaxe<2);
	if (_start==_end)
		_end++;

	if (!m_pLogAxis[iaxe])
	{
		m_pStarts[iaxe]=_start;
		m_pEnds[iaxe]=_end;
	}
	else
	{
		m_pStarts[iaxe]=log(_start);
		m_pEnds[iaxe]=log(_end);
	}
	// generating m_pStgfx...
	if (m_pAutoSteps[iaxe])
		GenerateSteps(iaxe);

	// repositioning label
	UpdateLabels();
}			

void CPGLAxe2D::GetLimits(int iaxe, double* pLimits)
{
	ASSERT(iaxe>=0);
	ASSERT(iaxe<2);
	pLimits[0]=m_pStarts[iaxe];
	pLimits[1]=m_pEnds[iaxe];
}


void CPGLAxe2D::GenerateSteps(int iaxe)
{
	ASSERT(iaxe >= 0 && iaxe <= 1);

	double dStart=m_pStarts[iaxe];
	double dEnd=m_pEnds[iaxe];
	
	if (m_pLogAxis[iaxe])
	{
		return ;
	}

	int numberOfTicks = 10; // TODO: Should be computed so that no overlap exists
	int bases [] = {1,5,2}; // Tick bases selection
	int currentBase;
	int n;
	double intervalSize, upperBound, lowerBound;
    int nIntervals,nMaxIntervals;

	// Vertical axis ticks
	if (fabs(dStart-dEnd) <= PGL_EPS) // Flat plo
	{
		dEnd=1;
		dStart=0;
	}
	
	// init step size
	m_pSteps[iaxe]=(dEnd-dStart)/2.0;

	int exponentYmax = (int)floor( log10(fabs(dEnd)) );
	double mantissaYmax = dEnd/pow(10,exponentYmax);        
	
	nMaxIntervals=0;
	for (int k = 1; k <= 4; ++k)
	{
        // Loop initialisation
        currentBase = bases[k];
        n = 4; // This value only allows results smaller than about 1000 = 10^n
		
		
        do // Tick vector length reduction 
        {
			--n;
			intervalSize = currentBase*pow(10, exponentYmax-n);
			upperBound =
				(int)ceil(mantissaYmax*pow(10,double(n))/currentBase)*intervalSize;
			nIntervals = (int)ceil((upperBound-dStart)/intervalSize);
			lowerBound = upperBound -nIntervals*intervalSize;
        }
        while ((nIntervals+1) > numberOfTicks);
        
        if (nIntervals > nMaxIntervals)
        {
			nMaxIntervals=nIntervals;
			m_pSteps[iaxe]=intervalSize;
			m_pStarts[iaxe]=lowerBound;
			m_pEnds[iaxe]=upperBound;
        }
	}
}

void CPGLAxe2D::DrawLinesGfx(gfxinterface::CGfxInterface& gfx)
{
	gfx.AddComment("--- CPGLAxe2D: Drawing lines and ticks");	
	// setting linewidth and line stipple
	gfx.SetDash("");
	gfx.SetLineWidth(1.8);

	gfx.DrawRect(m_pStarts[0], m_pStarts[1], m_pEnds[0], m_pEnds[1]);

	// bottom
	if (m_pNumbers[0].IsVisible())
	{
		gfx.DrawLine(m_pStarts[0],  m_pStarts[1] + m_pNumberPos[0]*(m_pEnds[1]-m_pStarts[1]),
			 m_pEnds[0], m_pStarts[1] + m_pNumberPos[0]*(m_pEnds[1]-m_pStarts[1]) );
	}

	//left
	if (m_pNumbers[1].IsVisible())
	{
		gfx.DrawLine( m_pStarts[0]+ m_pNumberPos[1]*(m_pEnds[0]-m_pStarts[0]) , m_pStarts[1],
				m_pStarts[0]+ m_pNumberPos[1]*(m_pEnds[0]-m_pStarts[0]) , m_pEnds[1]);

	}

	//right

	if (m_pNumbers[2].IsVisible())
	{
		gfx.DrawLine(m_pStarts[0]+ m_pNumberPos[2]*(m_pEnds[0]-m_pStarts[0]) , m_pStarts[1],
			m_pStarts[0]+ m_pNumberPos[2]*(m_pEnds[0]-m_pStarts[0]) , m_pEnds[1]);
	}

	//top
	if (m_pNumbers[3].IsVisible())
	{
		gfx.DrawLine(m_pStarts[0], m_pStarts[1] + m_pNumberPos[3]*(m_pEnds[1]-m_pStarts[1]),
				m_pEnds[0], m_pStarts[1] + m_pNumberPos[3]*(m_pEnds[1]-m_pStarts[1]));
	}

	// draw secondary ticks
	// bottom
	if (m_pSecondTicksNb[0]>0)
		gfx.DrawGridVer(m_pStarts[0],m_pEnds[0],m_pStarts[1],m_pStarts[1]+gfx.BBToWorldAbsy( m_pSecondTicksSize[0] ),m_pSteps[0]/(m_pSecondTicksNb[0]+1));
	//left
	if (m_pSecondTicksNb[1]>0)
		gfx.DrawGridHor(m_pStarts[0],m_pStarts[0]+gfx.BBToWorldAbsx( m_pSecondTicksSize[2] ),m_pStarts[1],m_pEnds[1],m_pSteps[1]/(m_pSecondTicksNb[1]+1));
	//right
	if (m_pSecondTicksNb[2]>0)
		gfx.DrawGridHor(m_pEnds[0],m_pEnds[0]-gfx.BBToWorldAbsx( m_pSecondTicksSize[3] ),m_pStarts[1],m_pEnds[1],m_pSteps[1]/(m_pSecondTicksNb[2]+1));
	// top
	if (m_pSecondTicksNb[3]>0)
		gfx.DrawGridVer(m_pStarts[0],m_pEnds[0],m_pEnds[1],m_pEnds[1]-gfx.BBToWorldAbsy( m_pSecondTicksSize[1] ),m_pSteps[0]/(m_pSecondTicksNb[3]+1));

	// draw main ticks
	gfx.DrawGridVer(m_pStarts[0],m_pEnds[0],m_pStarts[1],m_pStarts[1]+gfx.BBToWorldAbsy( m_pMainTicksSize[0] ),m_pSteps[0]);
	gfx.DrawGridVer(m_pStarts[0],m_pEnds[0],m_pEnds[1],m_pEnds[1]-gfx.BBToWorldAbsy( m_pMainTicksSize[1] ),m_pSteps[0]);
	gfx.DrawGridHor(m_pStarts[0],m_pStarts[0]+gfx.BBToWorldAbsx( m_pMainTicksSize[2] ),m_pStarts[1],m_pEnds[1],m_pSteps[1]);
	gfx.DrawGridHor(m_pEnds[0],m_pEnds[0]-gfx.BBToWorldAbsx( m_pMainTicksSize[3] ),m_pStarts[1],m_pEnds[1],m_pSteps[1]);

}

void CPGLAxe2D::DrawNumbersGfx(gfxinterface::CGfxInterface& gfx)
{
	// choosing and setting font
	CString str;
	CTime curtime;
	CTimeSpan dt;
	UINT nLabels,i;
	UINT nsec;
	UINT secnow; 
	double x,y;

	// sending grid number to gfx...	
	// bottom
	if (m_pNumbers[0].IsVisible())
	{
		// creating vectors
		nLabels=(UINT)(floor) ((m_pEnds[0]-m_pStarts[0])/m_pSteps[0])+1;
		std::vector<gfxinterface::SPointF> vPoints(nLabels);
		std::vector<std::string> vStrings(nLabels);

		// Creating strings...
		x=m_pStarts[0];
		y=m_pStarts[1] - gfx.BBToWorldAbsy( m_pNumbers[0].GetFont().GetHeight()+3 ) + m_pNumberPos[0]*(m_pEnds[1] - m_pStarts[1]);
		for (i=0;i<nLabels;i++)
		{
			// checking x
			if (fabs(x) < m_pSteps[0]*1e-3)
				x=0;

			// first point
			if (m_bTimeLabel)
			{
				nsec = m_tsDt.GetTotalSeconds();
				secnow = (int)floor(x*nsec);
				dt=CTimeSpan( secnow/(24*3600), 
					(secnow%(24*3600))/3600, 
					(secnow%3600)/60,
					secnow%60);
				curtime = m_tTimeLabelOrig+dt;
				str=curtime.Format(m_sTimeLabel);
			}
			else
			{
				str.Format("%g",x);
			}

			vPoints[i].x=x;
			vPoints[i].y=y;
			vStrings[i]=str;
			// updating x
			x+=m_pSteps[0];
		}
		// Drawing...
		// setting font
		m_pNumbers[0].GetFont().SetFontGfx(gfx);
		// setting color
		m_pNumbers[0].CPGLObject::PlotGfx(gfx);

		switch( m_pNumbers[0].GetAlign())
		{
		case PGL_TEXT_ALIGN_LEFT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentLeft, m_pNumbers[0].GetAngle());
			break;
		case PGL_TEXT_ALIGN_RIGHT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentRight, m_pNumbers[0].GetAngle());
			break;
		case PGL_TEXT_ALIGN_CENTER:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentCenter, m_pNumbers[0].GetAngle());
			break;
		}
	}

	// left
	if (m_pNumbers[1].IsVisible())
	{
		// creating vectors
		nLabels=(UINT)(floor) ((m_pEnds[1]-m_pStarts[1])/m_pSteps[1])+1;
		std::vector<gfxinterface::SPointF> vPoints(nLabels);
		std::vector<std::string> vStrings(nLabels);
		

		x=m_pStarts[0] - gfx.BBToWorldAbsx(3) + m_pNumberPos[1]*(m_pEnds[0] - m_pStarts[0]);
		y=m_pStarts[1];
		for (i=0;i<nLabels;i++)
		{
			// checking x
			if (fabs(y) < m_pSteps[1]*1e-3)
				y=0;
			// first point
			str.Format("%g",y);

			vPoints[i].x=x;
			vPoints[i].y=y;
			vStrings[i]=str;
			// updating y
			y+=m_pSteps[1];
		}

		// setting font
		m_pNumbers[1].GetFont().SetFontGfx(gfx);
		// setting color
		m_pNumbers[1].CPGLObject::PlotGfx(gfx);
		switch( m_pNumbers[1].GetAlign())
		{
		case PGL_TEXT_ALIGN_LEFT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentLeft, m_pNumbers[1].GetAngle());
			break;
		case PGL_TEXT_ALIGN_RIGHT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentRight, m_pNumbers[1].GetAngle());
			break;
		case PGL_TEXT_ALIGN_CENTER:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentCenter, m_pNumbers[1].GetAngle());
			break;
		}
	}

	// sending grid number to gfx...	
	// right
	if (m_pNumbers[2].IsVisible())
	{
		// creating vectors
		nLabels=(UINT)(floor) ((m_pEnds[1]-m_pStarts[1])/m_pSteps[1])+1;
		std::vector<gfxinterface::SPointF> vPoints(nLabels);
		std::vector<std::string> vStrings(nLabels);


		x=m_pStarts[0] + gfx.BBToWorldAbsx(3) + m_pNumberPos[2]*(m_pEnds[0] - m_pStarts[0]);
		y=m_pStarts[1];
		for (i=0;i<nLabels;i++)
		{
			// checking x
			if (fabs(y) < m_pSteps[1]*1e-3)
				y=0;
			// first point
			str.Format("%g",y);

			vPoints[i].x=x;
			vPoints[i].y=y;
			vStrings[i]=str;
			// updating y
			y+=m_pSteps[1];
		}
		// setting font
		m_pNumbers[2].GetFont().SetFontGfx(gfx);
		// setting color
		m_pNumbers[2].CPGLObject::PlotGfx(gfx);
		// Drawing...
		switch( m_pNumbers[2].GetAlign())
		{
		case PGL_TEXT_ALIGN_LEFT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentLeft, m_pNumbers[2].GetAngle());
			break;
		case PGL_TEXT_ALIGN_RIGHT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentRight, m_pNumbers[2].GetAngle());
			break;
		case PGL_TEXT_ALIGN_CENTER:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentCenter, m_pNumbers[2].GetAngle());
			break;
		}
	}

	// top
	if (m_pNumbers[3].IsVisible())
	{
		// creating vectors
		nLabels=(UINT)(floor) ((m_pEnds[1]-m_pStarts[1])/m_pSteps[1])+1;
		std::vector<gfxinterface::SPointF> vPoints(nLabels);
		std::vector<std::string> vStrings(nLabels);

		// setting font
		m_pNumbers[3].GetFont().SetFontGfx(gfx);
		// setting color
		m_pNumbers[3].CPGLObject::PlotGfx(gfx);

		x=m_pStarts[0];
		y=m_pStarts[1] + gfx.BBToWorldAbsy(3) + m_pNumberPos[3]*(m_pEnds[1] - m_pStarts[1]);
		for (i=0;i<nLabels;i++)
		{
			// checking x
			if (fabs(x) < m_pSteps[0]*1e-3)
				x=0;

			if (m_bTimeLabel)
			{
				nsec = m_tsDt.GetTotalSeconds();
				secnow = (int)floor(x*nsec);
				dt=CTimeSpan( secnow/(24*3600), 
					(secnow%(24*3600))/3600, 
					(secnow%3600)/60,
					secnow%60);
				curtime = m_tTimeLabelOrig+dt;
				str=curtime.Format(m_sTimeLabel);
			}
			else
			{
				str.Format("%g",x);
			}

			vPoints[i].x=x;
			vPoints[i].y=y;
			vStrings[i]=str;

			// updating x
			x+=m_pSteps[0];
		}

		// setting font
		m_pNumbers[3].GetFont().SetFontGfx(gfx);
		// setting color
		m_pNumbers[3].CPGLObject::PlotGfx(gfx);
		switch( m_pNumbers[3].GetAlign())
		{
		case PGL_TEXT_ALIGN_LEFT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentLeft, m_pNumbers[3].GetAngle());
			break;
		case PGL_TEXT_ALIGN_RIGHT:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentRight, m_pNumbers[3].GetAngle());
			break;
		case PGL_TEXT_ALIGN_CENTER:
			gfx.DrawTextStrip(vPoints, vStrings, gfxinterface::TextAlignmentCenter, m_pNumbers[3].GetAngle());
			break;
		}
	}


	// drawing labels...
	for (i=0;i<4;i++)
	{
		// writing down text...
		m_pLabels[i].PlotGfx(gfx);
	}
}

void CPGLAxe2D::DrawGridGfx(int iaxe, gfxinterface::CGfxInterface& gfx)
{
	gfx.SetDash("1 5");
	gfx.SetLineWidth(0);

	switch(iaxe)
	{
	case 0:
		gfx.DrawGridVer(m_pStarts[0],m_pEnds[0],m_pStarts[1],m_pEnds[1],m_pSteps[0]);
		break;
	case 1:
		gfx.DrawGridHor(m_pStarts[0],m_pEnds[0],m_pStarts[1],m_pEnds[1],m_pSteps[1]);
		break;
	}
}

void CPGLAxe2D::SetLabel(int iLabel, const CPGLText& newLabel)
{
	ASSERT_VALID(m_pView);
	ASSERT_VALID(&newLabel);
	ASSERT((iLabel>=0) && (iLabel<4));

	m_pLabels[iLabel]=newLabel;

	// placing label...
	UpdateLabels();
}

void CPGLAxe2D::SetLabel(int iLabel, const CString& newLabel)
{
	ASSERT_VALID(m_pView);
	ASSERT((iLabel>=0) && (iLabel<4));

	m_pLabels[iLabel].SetString(newLabel);

	// placing label...
	UpdateLabels();
}


void CPGLAxe2D::UpdateLabels()
{
	float pos[2];

	// bottom
	pos[0]=(float)((m_pStarts[0]+m_pEnds[0])/2.0);
	pos[1]=(float)(m_pStarts[1]-m_pView->PixelToWorld(1, m_pLabels[0].GetFont().GetHeight()+10));
	if (m_pNumbers[0].IsVisible())
		pos[1]-=m_pView->PixelToWorld(1, m_pNumbers[0].GetFont().GetHeight());
	m_pLabels[0].SetPosition(pos);

	// left
	pos[0]=(float)(m_pStarts[0]-m_pView->PixelToWorld(0, m_pLabels[1].GetFont().GetHeight()+5));
	if (m_pNumbers[1].IsVisible())
		pos[0]-=m_pView->PixelToWorld(0, m_pNumbers[1].GetFont().GetHeight()*4);
	pos[1]=(float)((m_pStarts[1]+m_pEnds[1])/2.0);
	m_pLabels[1].SetPosition(pos);

	// right
	pos[0]=(float)(m_pEnds[0]+m_pView->PixelToWorld(0, m_pLabels[2].GetFont().GetHeight()+5));
		if (m_pNumbers[2].IsVisible())
			pos[0]+=m_pView->PixelToWorld(0,m_pNumbers[2].GetFont().GetHeight()*4);
	pos[1]=(float)((m_pStarts[1]+m_pEnds[1])/2.0);
	m_pLabels[2].SetPosition(pos);

	// top
	pos[0]=(float)((m_pStarts[0]+m_pEnds[0])/2.0);
	pos[1]=(float)(m_pEnds[1]+m_pView->PixelToWorld(1, 20));
	if (m_pNumbers[3].IsVisible())
		pos[1]+=m_pView->PixelToWorld(1,m_pNumbers[3].GetFont().GetHeight()+5);
	m_pLabels[3].SetPosition(pos);
}

void CPGLAxe2D::Delete()
{
}

void CPGLAxe2D::Pan(double dx, double dy)
{
	m_pStarts[0]+=dx;
	m_pEnds[0]+=dx;
	m_pStarts[1]+=dy;
	m_pEnds[1]+=dy;

	UpdateLabels();
}

void CPGLAxe2D::ClipGfx(gfxinterface::CGfxInterface& gfx)
{
	if (!IsVisible())
		return;

	gfx.AddComment("Axe2D: Clipping inside axis");
	gfx.PushClipWorld(m_pStarts[0],m_pStarts[1],m_pEnds[0],m_pEnds[1]);
}

void CPGLAxe2D::UnClipGfx(gfxinterface::CGfxInterface& gfx)
{
	if (!IsVisible())
		return;

	gfx.AddComment("Axe2D: Unclipping");
	gfx.PopClipWorld();
}


void CPGLAxe2D::AddPropertyPage(CPropertySheet *pPropSheet)
{
	ASSERT_VALID(pPropSheet);

	// call own functions
	CPGLAxe2DPropPage* propPage=new CPGLAxe2DPropPage(this);
	pPropSheet->AddPage(propPage);
}

HTREEITEM CPGLAxe2D::AddPropTree(CTreeCtrl* pTree, HTREEITEM hParent)
{
	int i;
	ASSERT_VALID(pTree);
	CImageList* pImgList=pTree->GetImageList(TVSIL_NORMAL);
	ASSERT_VALID(pImgList);
	ASSERT(hParent);
	COLORREF crMask=0;
	// adding bitmap
	pImgList->Add(CBitmap::FromHandle(GetBitmap()),crMask);
	// adding to tree
	HTREEITEM htAxe;
	htAxe=pTree->InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM  /* nMask*/, 
				GetName() /* lpszItem*/, 
				pImgList->GetImageCount()-1 /* nImage */, 
				0 /* nSelectedImage */, 
				0 /* nState */, 
				0 /* nStateMask */, 
				GetID() /*  lParam */, 
				hParent /* hParent */, 
				TVI_LAST /* hInsertAfter */);
	ASSERT(htAxe!=NULL);

	// adding title and labels
	for (i=0;i<4;i++)
	{
		m_pLabels[i].AddPropTree(pTree,htAxe);
	}

	// adding numbers
	for (i=0;i<4;i++)
	{
		m_pNumbers[i].AddPropTree(pTree,htAxe);
	}

	return htAxe;
}


CPGLObject* CPGLAxe2D::FindObject(UINT ID)
{
	// test if it is himself
	if (CheckID(ID))
		return this;

	// check if it is title
	for (int i=0;i<4;i++)
	{
		if (m_pLabels[i].CheckID(ID))
			return &m_pLabels[i];
	}

	// check if it is numbering
	for (i=0;i<4;i++)
	{
		if (m_pNumbers[i].CheckID(ID))
			return &m_pNumbers[i];
	}

	// none return NULL
	return NULL;
}

void CPGLAxe2D::SetTimeLabelFormat(const COleDateTime& _otOrig, const COleDateTimeSpan& _otsDt, LPCSTR _szTimeLabel)
{
	CTime _tOrig( _otOrig.GetYear(),
		_otOrig.GetMonth(),
		_otOrig.GetDay(),
		_otOrig.GetHour(),
		_otOrig.GetMinute(),
		_otOrig.GetSecond());

	CTimeSpan _tsDt(_otsDt.GetDays(),
		_otsDt.GetHours(),
		_otsDt.GetMinutes(),
		_otsDt.GetSeconds());

	SetTimeLabelFormat(_tOrig, _tsDt, _szTimeLabel);
}


void CPGLAxe2D::GrowExtent(double *pExt)
{
	ASSERT_VALID(m_pView);

	///////////////////////////////////////////////////////////////////////////////////////////////
	// getting screen size (in pixels)
	int iW=m_pView->GetWidth();
	int iH=m_pView->GetHeight();

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Compute optimal borders...
	// left
	m_rBorders.left=10;
	if ( GetLeftLabel()->IsVisible() )
		m_rBorders.left+= GetLeftLabel()->GetFont().GetHeight() + 10; 
	if ( GetLeftNumber()->IsVisible() )
	{
		m_rBorders.left+= GetLeftNumber()->GetFont().GetHeight()*4;
	}

	// right
	m_rBorders.right=10;
	if ( GetRightLabel()->IsVisible() )
		m_rBorders.right+= GetRightLabel()->GetFont().GetHeight() + 10; 
	if ( GetRightNumber()->IsVisible())
		m_rBorders.right+= GetRightNumber()->GetFont().GetHeight()*4;

	// bottom
	m_rBorders.bottom=10;
	if ( GetBottomLabel()->IsVisible())
		m_rBorders.bottom+= GetBottomLabel()->GetFont().GetHeight() + 10; 
	if ( GetBottomNumber()->IsVisible() )
	{
		m_rBorders.bottom+= GetBottomNumber()->GetFont().GetHeight()+ 8;
	}

	// top
	m_rBorders.top=10;
	if ( GetTopLabel()->IsVisible())
		m_rBorders.top+= GetTopLabel()->GetFont().GetHeight() + 10; 
	if ( GetTopNumber()->IsVisible() )
		m_rBorders.top+= GetTopNumber()->GetFont().GetHeight()+ 8;

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Horizontal scaling
	// we want to have iAxeLeft pixels on the left and iAxeRight pixels on the right...
	int iWPlot=__max(1,iW-m_rBorders.left-m_rBorders.right);	// pixels left to draw data
	double dWScale=(pExt[1]-pExt[0])/iWPlot;

	// updating extent
	pExt[0]-=m_rBorders.left*dWScale;
	pExt[1]+=m_rBorders.right*dWScale;

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Vertical scaling
	int iHPlot=__max(1,iH-m_rBorders.bottom-m_rBorders.top);	// pixels left to draw data
	double dHScale=(pExt[3]-pExt[2])/iHPlot;

	// updating extent
	pExt[2]-=m_rBorders.bottom*dHScale;
	pExt[3]+=m_rBorders.top*dHScale;
}