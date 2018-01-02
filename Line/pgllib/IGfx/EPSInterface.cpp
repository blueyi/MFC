// EPSInterface.cpp: implementation of the CEPSInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EPSInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace gfxinterface
{

CEPSInterface::CEPSInterface(const char* sFileName)
: CFileGfxInterface(sFileName)
{
	InitState();
}

CEPSInterface::~CEPSInterface()
{
	if (m_file.is_open())
		Close();
}


void CEPSInterface::InitState()
{
	memset(&m_state.curcol,0,sizeof(SRGBA));
	memset(&m_state.strokecol,0,sizeof(SRGBA));
	memset(&m_state.fillcol,1,sizeof(SRGBA));
	m_state.curcol.a=1;
	m_state.strokecol.a=1;
	m_state.dash="";
	m_state.linewidth=0;

	m_lStates.clear();
}

void CEPSInterface::WriteHeader()
{
	double sqrt3=sqrt(3.0);
	_ASSERT(m_file.is_open());
	m_file<<"%!PS_Adobe-3.0 EPSF-3.0\n";
	m_file<<"%%Creator:"<<m_sCreator<<std::endl;
	m_file<<"%%Title:"<<m_sTitle<<std::endl;
	m_file<<"%%CreationDate:"<<m_sCreationDate<<std::endl;

	m_file<<"%%BoundingBox:"<<GetWorldLeft()<<" "<<GetWorldBottom()<<" "
		<<GetWorldRight()<<" "
		<<GetWorldTop()<<std::endl;
	m_file<<"%%LanguageLevel: 2\n";
	m_file<<"% World Bounding Box : "<<GetWorldLeft()<<" "<<GetWorldBottom()<<" "
		<<GetWorldRight()<<" "
		<<GetWorldHeight()<<std::endl;
	AddComment("Begin Operators Definitions:");
	AddComment("Name, description, stack state");

	AddComment("EWRightShow, right aligned text, text");
	m_file<<"/EWRightShow { dup stringwidth pop -1 mul 0 rmoveto show } def\n";

	AddComment("EWCenterShow, centered text, text");
	m_file<<"/EWCenterShow { dup stringwidth pop -0.5 mul 0 rmoveto show } def\n";

	AddComment("EWDownCenterShow, centered text down of cursor, text");
	m_file<<"/EWDownCenterShow { dup stringwidth pop -0.5 mul exch neg rmoveto show } def\n";

	AddComment("EWBox, startx starty dx dy");
	m_file<<"/EWBox {/dy exch def /dx exch def newpath moveto 0 dy rlineto dx 0 rlineto 0 dy -1 mul rlineto closepath} def\n";

	AddComment("EWCircle, no fill, centerx centery radius");
	m_file<<"/EWCircle { 0 360 arc} def\n";

	AddComment("EWTriangle, a triangle inside a circle, centerx centery radius");
	m_file<<"/EWTriangle {dup "<<sqrt3<<" mul /c 2 1 roll def newpath add moveto\n c 2 div c -1 mul rlineto c -1 mul 0 rlineto closepath} def\n";

	AddComment("EWSquare, square inside center, centerx centery radius");
	m_file<<"/EWSquare {/r 2 1 roll def newpath moveto r 2 div r 2 div rmoveto\n 0 r -1 mul rlineto r -1 mul 0 rlineto 0 r rlineto closepath} def\n";

	AddComment("EWArrow, an arrow, tailx taily tipx tipy tailthickness headthickness headlength");
	AddComment("See Postscript language Cookbook, Program 4");
	AddComment("Setting arrow dictionnary");
	m_file<<"/EWArrowDict 14 dict def EWArrowDict begin /mtrx matrix def end\n";	
	AddComment("Defining arrow procedure");
	m_file<<"/EWArrow { EWArrowDict begin "
		<<"/headlength exch def /halfheadthickness exch 2 div def /halfthickness exch 2 div def "
		<<"/tipy exch def /tipx exch def /taily exch def /tailx exch def "
		<<"/dx tipx tailx sub def /dy tipy taily sub def "
		<<"/arrowlength dx dx mul dy dy mul add sqrt def "
		<<"/angle dy dx atan def /base arrowlength headlength sub def "
		<<"/savematrix mtrx currentmatrix def "
		<<"tailx taily translate angle rotate "
		<<"0 halfthickness neg moveto base halfthickness neg lineto "
		<<"base halfheadthickness neg lineto arrowlength 0 lineto "
		<<"base halfheadthickness lineto base halfthickness lineto " 
		<<"0 halfthickness lineto closepath "
		<<"savematrix setmatrix end }def ";
	AddComment("End Preliminary Definitions");
	m_file<<"gsave\n";
}

bool CEPSInterface::Open(const char* filename)
{
	if (filename)
	{
		m_sFileName=filename;
		// testing if eps extension...
		if (m_sFileName.rfind(".eps") != m_sFileName.size() - 4)
		{
			m_sFileName+=".eps";
		}
	}

	if (!CFileGfxInterface::Open())
		return false;

	// init state
	InitState();

	// init EPS header
	WriteHeader();
	return true;
}

void CEPSInterface::Close()
{
	_ASSERT(m_file.is_open());
	m_file<<"grestore\n";

	CFileGfxInterface::Close();
}

void CEPSInterface::DrawLineStrip(int n, double *pX, double *pY, bool open, bool filled)
{
	int count=0;

	m_file<<"newpath\n";
	if (filled)
	{
		m_file<<WorldToBBx(pX[0])<<" "<<GetWorldBottom()<<std::endl;
		count++;
	}

	for (int i=0;i<n;i++)
	{
		m_file<<WorldToBBx(pX[i])<<" "<<WorldToBBy(pY[i])<<std::endl;
		count++;
	}
	if (filled)
	{
		m_file<<WorldToBBx(pX[n-1])<<" "<<GetWorldBottom()<<std::endl;
		count++;
	}

	m_file<<"moveto "<<count-1<<" {lineto} repeat ";

	if (open)
	{
		PutStrokeColorString();
		m_file<<"stroke\n";
	}
	else if (filled)
	{
		m_file<<"closepath ";
		PushState();
		PutFillColorString();		
		m_file<<"fill ";
		PopState();
		PutStrokeColorString();
		m_file<<" stroke\n";
	}
	else
	{
		PutStrokeColorString();
		m_file<<"closepath stroke\n";
	}
}


void CEPSInterface::DrawStepStrip(int n, double *pX, double *pY, bool open, bool filled)
{
	int count=0;

	m_file<<"newpath\n";
	if (filled)
	{
		m_file<<WorldToBBx(pX[0])<<" "<<GetWorldBottom()<<std::endl;
		count++;
	}

	for (int i=0;i<n-1;i++)
	{
		m_file<<WorldToBBx(pX[i])<<" "<<WorldToBBy(pY[i])<<" ";
		m_file<<WorldToBBx(pX[i+1])<<" "<<WorldToBBy(pY[i])<<std::endl;
		count+=2;
	}

	if (filled)
	{
		m_file<<WorldToBBx(pX[n-1])<<" "<<GetWorldBottom()<<std::endl;
		count++;
	}

	m_file<<"moveto "<<count-1<<" {lineto} repeat ";

	if (open)
	{
		PutStrokeColorString();
		m_file<<"stroke\n";
	}
	else if (filled)
	{
		m_file<<"closepath ";
		PushState();
		PutFillColorString();		
		m_file<<"fill ";
		PopState();
		PutStrokeColorString();
		m_file<<" stroke\n";
	}
	else
	{
		PutStrokeColorString();
		m_file<<"closepath stroke\n";
	}
}


void CEPSInterface::AddComment(const char *str)
{
#ifdef _DEBUG
	m_file<<"%"<<str<<std::endl;
#endif
}

void CEPSInterface::SetColor(double r, double g, double b, double a)
{
	m_state.strokecol.r = __max(0, __min( 1, r));
	m_state.strokecol.g = __max(0, __min( 1, g));
	m_state.strokecol.b = __max(0, __min( 1, b));
	m_state.strokecol.a = __max(0, __min( 1, a));
}

void CEPSInterface::SetFillColor(double r, double g, double b, double a)
{
	m_state.fillcol.r = __max(0, __min( 1, r));
	m_state.fillcol.g = __max(0, __min( 1, g));
	m_state.fillcol.b = __max(0, __min( 1, b));
	m_state.fillcol.a = __max(0, __min( 1, a));
}

void CEPSInterface::SetDash(const char* dash)
{
	if (dash!= m_state.dash)
	{
		m_state.dash=dash;
		m_file<<"["<<dash<<"] 0 setdash\n";
	}
}

void CEPSInterface::DrawLine(double x1, double y1, double x2, double y2)
{
	PutStrokeColorString();
	m_file<<"newpath "<<WorldToBBx(x1)<<" "<<WorldToBBy(y1)<<" moveto "
		<<WorldToBBx(x2)<<" "<<WorldToBBy(y2)<<" lineto stroke\n";
}

void CEPSInterface::DrawTextLeft(double x, double y, const char* str, double angle)
{
	PutStrokeColorString();
	m_file<<WorldToBBx(x)<<" "<<WorldToBBy(y)<<" moveto ";

	// rotating if needed
	if (angle)
		m_file<<angle<<" rotate ";

	m_file<<"("<<str<<") show ";

	// rotating back
	if (angle)
		m_file<<-angle<<" rotate ";
	m_file<<std::endl;	
}

void CEPSInterface::DrawTextRight(double x, double y, const char* str, double angle)
{
	PutStrokeColorString();
	m_file<<WorldToBBx(x)<<" "<<WorldToBBy(y)<<" moveto ";

	// rotating if needed
	if (angle)
		m_file<<angle<<" rotate ";

	m_file<<"("<<str<<") EWRightShow ";

	// rotating back
	if (angle)
		m_file<<-angle<<" rotate ";
	m_file<<std::endl;	
}

void CEPSInterface::DrawTextCenter(double x, double y, const char* str, double angle)
{
	PutStrokeColorString();
	m_file<<WorldToBBx(x)<<" "<<WorldToBBy(y)<<" moveto ";

	// rotating if needed
	if (angle)
		m_file<<angle<<" rotate ";

	m_file<<"("<<str<<") EWCenterShow ";

	// rotating back
	if (angle)
		m_file<<-angle<<" rotate ";
	m_file<<std::endl;	
}

void CEPSInterface::DrawTextStrip(const std::vector<SPointF>& vPoints, const std::vector<std::string>& vStrings, ETextAlignment ta, double angle)
{
	ASSERT(vPoints.size() == vStrings.size());
	PutStrokeColorString();
	
	for (UINT i=0; i<vPoints.size();i++)
	{
		m_file<<WorldToBBx(vPoints[i].x)<<" "<<WorldToBBy(vPoints[i].y)<<" moveto ";
		// rotating if needed
		if (angle)
			m_file<<angle<<" rotate ";

		m_file<<"("<<vStrings[i]<<") ";
		switch(ta)
		{
		case TextAlignmentLeft:
			m_file<<"EWLeftShow ";
			break;
		case TextAlignmentCenter:
			m_file<<"EWCenterShow ";
			break;
		case TextAlignmentRight:
			m_file<<"EWRightShow ";
			break;
		}
		// rotating back
		if (angle)
			m_file<<-angle<<" rotate ";
		m_file<<std::endl;	
	}	
};


void CEPSInterface::SetFont(long scale)
{
	m_file<<"/Times-Roman findfont "<<abs(scale)<<" scalefont setfont\n";
}

void CEPSInterface::SetFont(const LOGFONT& logFont)
{
	m_file<<"/Times-Roman findfont "<<fabs(logFont.lfHeight)<<" scalefont setfont\n";
}

void CEPSInterface::DrawBox(double llx, double lly, double dx, double dy, bool filled)
{
	m_file<<WorldToBBx(llx)<<" "<<WorldToBBy(lly)<<" "<<dx<<" "<<dy<<" EWBox ";
	
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";

	m_file<<std::endl;
}

void CEPSInterface::DrawCircle(double cx, double cy, double radius, bool filled)
{
	m_file<<WorldToBBx(cx)<<" "<<WorldToBBy(cy)<<" "<<radius<<" EWCircle ";
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";
	m_file<<std::endl;
}

void CEPSInterface::DrawTriangle(double cx, double cy, double radius, bool filled)
{
	m_file<<WorldToBBx(cx)<<" "<<WorldToBBy(cy)<<" "<<radius<<" EWTriangle ";
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";
	m_file<<std::endl;
}

void CEPSInterface::DrawSquare(double cx, double cy, double radius, bool filled)
{
	m_file<<WorldToBBx(cx)<<" "<<WorldToBBy(cy)<<" "<<radius<<" EWSquare ";
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";
	m_file<<std::endl;
}

void CEPSInterface::DrawBoxStrip(int n, double* pLlx, double* pLly, double dx, double dy, bool filled)
{
	for (int i=0;i<n;i++)
	{
		m_file<<WorldToBBx(pLlx[i])<<" "<<WorldToBBy(pLly[i])<<" "<<dx<<" "<<dy<<std::endl;
	}
	m_file<<n<<" {EWBox ";
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";
	m_file<<"} repeat\n";
}

void CEPSInterface::DrawCircleStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	for (int i=0;i<n;i++)
	{
		m_file<<WorldToBBx(pCx[i])<<" "<<WorldToBBy(pCy[i])<<" "<<radius<<std::endl;
	}
	m_file<<n<<" {EWCircle ";
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";
	m_file<<"} repeat\n";
}

void CEPSInterface::DrawTriangleStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	for (int i=0;i<n;i++)
	{
		m_file<<WorldToBBx(pCx[i])<<" "<<WorldToBBy(pCy[i])<<" "<<radius<<std::endl;
	}
	m_file<<n<<" {EWTriangle ";
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";
	m_file<<"} repeat\n";
}

void CEPSInterface::DrawSquareStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	for (int i=0;i<n;i++)
	{
		m_file<<WorldToBBx(pCx[i])<<" "<<WorldToBBy(pCy[i])<<" "<<radius<<std::endl;
	}
	m_file<<n<<" {EWSquare ";
	// fill if needed
	if (filled)
	{
		PushState();
		PutStrokeColorString();
		m_file<<"fill ";
		PopState();
	}

	// draw contour
	PutStrokeColorString();
	m_file<<"stroke ";
	m_file<<"} repeat\n";
}

void CEPSInterface::SetLineWidth(double width)
{
	if (width != m_state.linewidth)
	{
		m_state.linewidth=__max(0,width-1);
		m_file<<m_state.linewidth<<" setlinewidth\n";
	}
}

void CEPSInterface::DrawSurf(int nx, int ny, double llx, double lly, double dx, double dy, double* pColor)
{
	double xCur,yCur;
	int i,j,k;

	AddComment("Drawing surface");
	AddComment("Init shading dictionnary");
	m_file<<"/DeviceRGB setcolorspace\n";

	AddComment("Define the shading dictionary");
	m_file<<"<<\n/ShadingType 5\n/ColorSpace /DeviceRGB\n"
		<<"/VerticesPerRow "<<nx<<" \n/DataSource [\n";

	// sending points by rows
	yCur=lly+(ny-1)*dy;
	k=0;
	for (i=0;i<ny;i++)
	{
		xCur=llx;
		for (j=0;j<nx;j++)
		{
			_ASSERT(k==i*nx+j);
			// sending to postscript
			m_file<<WorldToBBx(xCur)<<" "<<WorldToBBy(yCur)<<" "
				<<pColor[k*3]<<" "
				<<pColor[k*3+1]<<" "
				<<pColor[k*3+2]<<std::endl;
			// updating xCur
			xCur += dx;
			k++;
		}
		// updating y
		yCur-=dy;
	}
	// stroking
	m_file<<"]\n>> shfill\n";
}

void CEPSInterface::DrawVectorField(int nx, int ny, double llx, double lly, double dx, double dy, double *pV, double lineWidth)
{
	double xCur,yCur;
	int i,j,k,lcount;

	lineWidth = __max(1, lineWidth);
	// draw contour
	PutStrokeColorString();
	AddComment("Vector field");
	m_file<<"newpath\n";
	// sending points by rows
	yCur=lly+(ny-1)*dy;
	k=0;
	lcount=0;
	for (i=0;i<ny;i++)
	{
		xCur=llx;
		for (j=0;j<nx;j++)
		{
			_ASSERT(k==i*nx+j);
			if (sqrt( pV[k*2]*pV[k*2]+pV[k*2+1]*pV[k*2+1] ) > 1e-10)
			{
				// sending to postscript
				m_file<<WorldToBBx(xCur-pV[k*2]/2)<<" "<<WorldToBBy(yCur-pV[k*2+1]/2)<<" "
					<<WorldToBBx(xCur+pV[k*2]/2)<<" "<<WorldToBBy(yCur+pV[k*2+1]/2)<<" "
					<<lineWidth<<" 4.0 6.0"<<std::endl;
				lcount++;
			}
			// updating xCur
			xCur+=dx;
			k++;
		}
		yCur-=dy;
	}
	m_file<<lcount<<" {EWArrow} repeat fill"<<std::endl;
}

void CEPSInterface::PushClipWorld(double llx, double lly, double urx, double ury)
{
	CFileGfxInterface::PushClipWorld(llx,lly,urx,ury);

	m_file<<" gsave ";
	// clipping path...
	m_file<<WorldToBBx(llx)<<" "
		<<WorldToBBy(lly)<<" "
		<<WorldToBBAbsx(urx-llx)<<" "
		<<WorldToBBAbsy(ury-lly)<<" "
		<<"rectclip\n";
}

void CEPSInterface::PopClipWorld()
{
	CFileGfxInterface::PopClipWorld();

	m_file<<" grestore\n";
}

void CEPSInterface::PushState()
{
	m_file<<" gsave\n";
	m_lStates.push_front(m_state);
}

void CEPSInterface::PopState()
{
	_ASSERT(!m_lStates.empty());
	m_state = m_lStates.front();
	m_lStates.pop_front();
	m_file<<" grestore\n";
}

void CEPSInterface::Fill()
{
	m_file<<" fill\n";;
}

void CEPSInterface::DrawGridHor(double llx, double urx, double lly, double ury,double dy)
{
	AddComment("Drawing horizontal grid");
	double y=lly;
	
	int count;
	PutStrokeColorString();
	// Drawing lines
	m_file<<"newpath\n";
	// sending points
	count=0;
	y=lly;
	m_file<<WorldToBBx(urx)<<" "<<WorldToBBy(y)<<" moveto"<<std::endl;
	while (y<ury-dy)
	{
		m_file<<WorldToBBAbsx(urx-llx)<<" 0 "<<-WorldToBBAbsx(urx-llx)<<" "<<WorldToBBAbsy(dy)<<std::endl;
		count++;
		y+=dy;
	}

	m_file<<count<<" {rmoveto rlineto} repeat stroke\n";
}

void CEPSInterface::DrawGridVer(double llx, double urx, double lly, double ury,double dx)
{
	AddComment("Drawing vertical grid");
	double x=llx;
	
	int count;
	PutStrokeColorString();
	// Drawing lines
	m_file<<"newpath\n";
	// sending points
	count=0;
	x=llx;
	m_file<<WorldToBBx(x)<<" "<<WorldToBBy(ury)<<" moveto"<<std::endl;
	while (x<urx-dx)
	{
		m_file<<"0 "<<WorldToBBAbsy(ury-lly)<<" "<<WorldToBBAbsx(dx)<<" "<<-WorldToBBAbsy(ury-lly)<<std::endl;
		count++;
		x+=dx;
	}

	m_file<<count<<" {rmoveto rlineto} repeat stroke\n";
}

void CEPSInterface::DrawArrow(double tailx, double taily, double tipx, double tipy, double tailthickness, double headthickness, double headlength, bool filled)
{
	m_file<<WorldToBBx(tailx)<<" "<<WorldToBBy(taily)<<" "<<WorldToBBx(tipx)<<" "<<WorldToBBy(tipy)<<" "<<tailthickness<<" "<<headthickness<<" "<<headlength<<" EWArrow ";
	if (filled)
	{	
		PushState();
		PutFillColorString();
		m_file<<"fill ";
		PopState();
	}
	PutStrokeColorString();
	m_file<<"stroke\n";
}

void CEPSInterface::DrawArrowAbs(double tailx, double taily, double dtipx, double dtipy, double tailthickness, double headthickness, double headlength, bool filled)
{
	m_file<<WorldToBBx(tailx)<<" "<<WorldToBBy(taily)<<" "<<WorldToBBx(tailx)+dtipx<<" "<<WorldToBBy(taily)+dtipy<<" "<<tailthickness<<" "<<headthickness<<" "<<headlength<<" EWArrow ";
	if (filled)
	{	
		PushState();
		PutFillColorString();
		m_file<<"fill ";
		PopState();
	}
	PutStrokeColorString();
	m_file<<"stroke\n";
}

void CEPSInterface::DrawRect(double llx, double lly, double urx, double ury, bool filled)
{
	m_file<<"newpath "<<WorldToBBx(llx)<<" "<<WorldToBBy(ury)<<" "
		<<WorldToBBx(urx)<<" "<<WorldToBBy(ury)<<" "
		<<WorldToBBx(urx)<<" "<<WorldToBBy(lly)<<" "
		<<WorldToBBx(llx)<<" "<<WorldToBBy(lly)<<" moveto 3 {lineto} repeat closepath ";

	if (filled)
	{
		PushState();
		PutFillColorString();
		m_file<<"fill ";
		PopState();
	}
	PutStrokeColorString();
	m_file<<"stroke\n";		
}

void CEPSInterface::PutFillColorString()
{
	if ( memcmp(&m_state.fillcol, &m_state.curcol , sizeof(SRGBA)))
	{
		m_state.curcol = m_state.fillcol;
		m_file<<m_state.fillcol.r<<" "<<m_state.fillcol.g<<" "<<m_state.fillcol.b<<" setrgbcolor\n";
	}
}

void CEPSInterface::PutStrokeColorString()
{
	if ( memcmp(&m_state.strokecol, &m_state.curcol , sizeof(SRGBA) ))
	{
		m_state.curcol = m_state.strokecol;
		m_file<<m_state.strokecol.r<<" "<<m_state.strokecol.g<<" "<<m_state.strokecol.b<<" setrgbcolor\n";
	}
}

}