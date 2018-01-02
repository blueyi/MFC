// SVGInterface.cpp: implementation of the CSVGInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SVGInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace gfxinterface
{

// SVGWriter.cpp: implementation of the CSVGInterface class.
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <strstream>
#include <math.h>
#include "zlib/zlib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSVGInterface::CSVGInterface(const char* sFileName, bool bZipped)
: CFileGfxInterface(sFileName)
{
	m_pssFile = NULL;
	m_pssDefs = NULL;
	m_pssMain = NULL;
	m_bZipped = bZipped;
	InitState();
}

CSVGInterface::~CSVGInterface()
{
	if (m_pssFile)
		delete m_pssFile;
	if (m_pssDefs)
		delete m_pssDefs;
	if (m_pssMain)
		delete m_pssMain;
}


void CSVGInterface::InitState()
{
	memset(&m_state.strokecol,0,sizeof(SRGBA));
	memset(&m_state.fillcol,1,sizeof(SRGBA));
	m_state.strokecol.a=1;
	m_state.dash="";
	m_state.linewidth=1;
	GetDefaultLOGFONT(m_state.m_font);

	m_liCurDef=0;

	if (m_pssFile)
		delete m_pssFile;
	if (m_pssDefs)
		delete m_pssDefs;
	if (m_pssMain)
		delete m_pssMain;

	m_pssFile=new std::ostrstream();
	m_pssDefs=new std::ostrstream();
	m_pssMain=new std::ostrstream();
}

bool CSVGInterface::Open(const char* filename)
{
	if (filename)
	{
		m_sFileName=filename;
		// testing if eps extension...
		if (m_sFileName.rfind(".svg") != m_sFileName.size() - 4)
		{
			m_sFileName+=".svg";
		}
	}

	// init state
	InitState();

	// init EPS header
	WriteHeader();
	return true;
}

void CSVGInterface::Close()
{
	//flushing
	m_pssDefs->flush();
	m_pssMain->flush();

	if ((*m_pssDefs).pcount())
	{
		(*m_pssFile)<<"<defs>\n";
		m_pssFile->write(m_pssDefs->str(), m_pssDefs->pcount());
		(*m_pssFile)<<"\n</defs>\n";
	}

	// flushing main
	if ((*m_pssMain).pcount())
	{
		m_pssFile->write(m_pssMain->str(), m_pssMain->pcount());
	}

	(*m_pssFile)<<"</svg>\n";
	m_pssFile->flush();

	// zipping file
	if (m_bZipped)
	{
		gzFile gzf = gzopen(m_sFileName.c_str(),"wb9");

		// writing
		gzwrite(gzf,m_pssFile->str(), m_pssFile->pcount());

		gzclose(gzf);
	}
	else
	{
		FILE* fout = fopen(m_sFileName.c_str(), "w");
		fwrite( m_pssFile->str(), sizeof(char), m_pssFile->pcount(), fout);
		fclose(fout);
	}
}

void CSVGInterface::DrawRect(double llx, double lly, double urx, double ury, bool filled)
{
	(*m_pssMain)<<"<rect ";
	
	PutFillColorString((*m_pssMain),filled);
	PutFillAlphaString((*m_pssMain));

	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));

	(*m_pssMain)<<" stroke-width=\""<<m_state.linewidth<<"\" "
		<<"x=\""<<WorldToBBx(llx)<<"\" "
		<<"y=\""<<WorldToBBy(ury)<<"\" "
		<<"width=\""<<WorldToBBAbsx(urx-llx)<<"\" "
		<<"height=\""<<WorldToBBAbsy(lly-ury)<<"\" "
		<<"/>\n";
}

void CSVGInterface::DrawArrow(double tailx, double taily, double tipx, double tipy, double tailthickness, double  headthickness, double headlength, bool filled)
{
	
}

void CSVGInterface::DrawArrowAbs(double tailx, double taily, double dtipx, double dtipy, double tailthickness, double  headthickness, double headlength, bool filled)
{

}

void CSVGInterface::DrawLine(double x1, double y1, double x2, double y2)
{
	(*m_pssMain)<<"<line ";
	PutStrokeColorString((*m_pssMain));
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<"stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	(*m_pssMain)<<"stroke-width=\""<<m_state.linewidth<<"\" "
		<<"x1=\""<<WorldToBBx(x1)<<"\" "
		<<"y1=\""<<WorldToBBy(y1)<<"\" "
		<<"x2=\""<<WorldToBBx(x2)<<"\" "
		<<"y2=\""<<WorldToBBy(y2)<<"\" ";
	
	(*m_pssMain)<<"/>\n";
}

void CSVGInterface::DrawLineStrip(int n, double* pX, double* pY, bool open, bool filled)
{
	// open or closed
	if (open)
		(*m_pssMain)<<"<polyline ";
	else
		(*m_pssMain)<<"<polygon ";

	// fill type
	PutFillColorString((*m_pssMain),filled);
	PutFillAlphaString((*m_pssMain));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// linewidth
	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));

	(*m_pssMain)<<" stroke-width=\""<<m_state.linewidth<<"\"  points=\"";
	if (filled)
	{
		(*m_pssMain)<<std::endl<<WorldToBBx(pX[0])<<","<<WorldToBBy(BBToWorldy(GetBBBottom()))<<" ";
	}
	for (int i=0;i<n;i++)
	{
		if (i%5 == 0)	
			(*m_pssMain)<<"\n";
		(*m_pssMain)<<WorldToBBx(pX[i])<<","<<WorldToBBy(pY[i])<<" ";
	}

	if (filled)
	{
		(*m_pssMain)<<WorldToBBx(pX[n-1])<<","<<WorldToBBy(BBToWorldy(GetBBBottom()))<<" ";
	}

	(*m_pssMain)<<"\"/>\n";

}

void CSVGInterface::DrawStepStrip(int n, double* pX, double* pY, bool open, bool filled)
{
	// open or closed
	if (open)
		(*m_pssMain)<<"<polyline ";
	else
		(*m_pssMain)<<"<polygon ";

	// fill type
	PutFillColorString((*m_pssMain),filled);
	PutFillAlphaString((*m_pssMain));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));

	// linewidth
	(*m_pssMain)<<" stroke-width=\""<<m_state.linewidth<<"\"  points=\"";
	if (filled)
	{
		(*m_pssMain)<<std::endl<<WorldToBBx(pX[0])<<","<<WorldToBBy(BBToWorldy(GetBBBottom()))<<" ";
	}
	for (int i=0;i<n-1;i++)
	{
		if (i%5 == 0)	
			(*m_pssMain)<<"\n";
		(*m_pssMain)<<WorldToBBx(pX[i])<<","<<WorldToBBy(pY[i])<<" ";
		(*m_pssMain)<<WorldToBBx(pX[i+1])<<","<<WorldToBBy(pY[i])<<" ";
	}

	if (filled)
	{
		(*m_pssMain)<<WorldToBBx(pX[n-1])<<","<<WorldToBBy(BBToWorldy(GetBBBottom()))<<" ";
	}

	(*m_pssMain)<<"\"/>\n";

}


void CSVGInterface::DrawBox(double llx, double lly, double dx, double dy, bool filled)
{
	(*m_pssMain)<<"<rect ";
	// fill type
	PutFillColorString((*m_pssMain),filled);
	PutFillAlphaString((*m_pssMain));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// characteristics linewidth
	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));
	(*m_pssMain)<<"stroke-width=\""<<m_state.linewidth<<"\" "
		<<"x=\""<<WorldToBBx(llx)<<"\" "
		<<"y=\""<<WorldToBBy(lly)<<"\" "
		<<"width=\""<<dx<<"\" "
		<<"height=\""<<dy<<"\" ";
	
	(*m_pssMain)<<"/>\n";
}

void CSVGInterface::DrawCircle(double cx, double cy, double radius, bool filled)
{
	(*m_pssMain)<<"<circle ";

	// fill type
	PutFillColorString((*m_pssMain),filled);
	PutFillAlphaString((*m_pssMain));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// characteristics linewidth
	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));
	(*m_pssMain)<<"stroke-width=\""<<m_state.linewidth<<"\" ";
	(*m_pssMain)<<"cx=\""<<WorldToBBx(cx)<<"\" "
		<<"cy=\""<<WorldToBBy(cy)<<"\" "
		<<"r=\""<<radius<<"\" ";
	
	(*m_pssMain)<<"/>\n";
}

void CSVGInterface::DrawTriangle(double cx, double cy, double radius, bool filled)
{
	double sr3 = radius/(sqrt(3));

	(*m_pssMain)<<"<polygon ";

	// fill type
	PutFillColorString((*m_pssMain),filled);
	PutFillAlphaString((*m_pssMain));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// linewidth
	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));

	(*m_pssMain)<<" stroke-width=\""<<m_state.linewidth<<"\"  points=\"\n";
	(*m_pssMain)<<WorldToBBx(cx)-sqrt(2)*sr3<<","<<WorldToBBy(cy)+sr3<<" ";
	(*m_pssMain)<<WorldToBBx(cx)+sqrt(2)*sr3<<","<<WorldToBBy(cy)+sr3<<" ";
	(*m_pssMain)<<WorldToBBx(cx)<<","<<WorldToBBy(cy)-radius/2<<" ";

	(*m_pssMain)<<"\"/>\n";
}

void CSVGInterface::DrawSquare(double cx, double cy, double radius, bool filled)
{
	(*m_pssMain)<<"<rect ";

	// fill type
	PutFillColorString((*m_pssMain),filled);
	PutFillAlphaString((*m_pssMain));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// characteristics linewidth
	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));
	(*m_pssMain)<<"stroke-width=\""<<m_state.linewidth<<"\" ";
	(*m_pssMain)<<"x=\""<<WorldToBBx(cx)-radius/2<<"\" "
		<<"y=\""<<WorldToBBy(cy)+radius/2<<"\" "
		<<"width=\""<<radius/sqrt(2)<<"\" "
		<<"height=\""<<radius/sqrt(2)<<"\" ";
	(*m_pssMain)<<"/>\n";
}


void CSVGInterface::DrawBoxStrip(int n, double* pLlx, double* pLly, double dx, double dy, bool filled)
{
	(*m_pssDefs)<<"<rect id=\"d"<<m_liCurDef<<"\" ";
	// fill type
	PutFillColorString((*m_pssDefs),filled);
	PutFillAlphaString((*m_pssDefs));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssDefs)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// characteristics linewidth
	PutStrokeColorString((*m_pssDefs));
	PutStrokeAlphaString((*m_pssDefs));
	(*m_pssDefs)<<"stroke-width=\""<<m_state.linewidth<<"\" "
		<<"width=\""<<dx<<"\" "
		<<"height=\""<<dy<<"\"/>\n";
	
	for (int i=0;i<n;i++)
	{
		(*m_pssMain)<<"<use x=\""<<WorldToBBx(pLlx[i])<<"\" y=\""<<WorldToBBy(pLly[i])<<"\" xlink:href=\"#d"<<m_liCurDef<<"\" />\n";
	}

	m_liCurDef++;
}

void CSVGInterface::DrawCircleStrip(int n, double* pCx, double* pCy, double radius, bool filled )
{
	(*m_pssDefs)<<"<circle id=\"d"<<m_liCurDef<<"\" ";

	// fill type
	PutFillColorString((*m_pssDefs),filled);
	PutFillAlphaString((*m_pssDefs));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssDefs)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// characteristics linewidth
	PutStrokeColorString((*m_pssDefs));
	PutStrokeAlphaString((*m_pssDefs));
	(*m_pssDefs)<<"stroke-width=\""<<m_state.linewidth<<"\" "
		<<"r=\""<<radius<<"\"/>\n";
	

	for (int i=0;i<n;i++)
	{
		(*m_pssMain)<<"<use x=\""<<WorldToBBx(pCx[i])<<"\" y=\""<<WorldToBBy(pCy[i])<<"\" xlink:href=\"#d"<<m_liCurDef<<"\" />\n";
	}

	m_liCurDef++;
}

void CSVGInterface::DrawTriangleStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	double sr3 = radius/(sqrt(3));

	(*m_pssDefs)<<"<polygon id=\"d"<<m_liCurDef<<"\" ";

	// fill type
	PutFillColorString((*m_pssDefs),filled);
	PutFillAlphaString((*m_pssDefs));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssDefs)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// linewidth
	PutStrokeColorString((*m_pssDefs));
	PutStrokeAlphaString((*m_pssDefs));

	(*m_pssDefs)<<" stroke-width=\""<<m_state.linewidth<<"\"  points=\"\n"
		<<-sqrt(2)*sr3<<","<<sr3<<" "
		<<+sqrt(2)*sr3<<","<<sr3<<" "
		<<"0,"<<-radius<<" "
		<<"\"/>\n";


	for (int i=0;i<n;i++)
	{
		(*m_pssMain)<<"<use x=\""<<WorldToBBx(pCx[i])<<"\" y=\""<<WorldToBBy(pCy[i])<<"\" xlink:href=\"#d"<<m_liCurDef<<"\" />\n";
	}

	m_liCurDef++;
}

void CSVGInterface::DrawSquareStrip(int n, double* pCx, double* pCy, double radius, bool filled)
{
	(*m_pssDefs)<<"<rect id=\"d"<<m_liCurDef<<"\" ";

	// fill type
	PutFillColorString((*m_pssDefs),filled);
	PutFillAlphaString((*m_pssDefs));

	// dash if needed
	if (!m_state.dash.empty())
	{
		(*m_pssDefs)<<" stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}

	// characteristics linewidth
	PutStrokeColorString((*m_pssDefs));
	PutStrokeAlphaString((*m_pssDefs));
	(*m_pssDefs)<<"stroke-width=\""<<m_state.linewidth<<"\" "
		<<"width=\""<<radius<<"\" "
		<<"height=\""<<radius<<"\" "
		<<"/>\n";

	for (int i=0;i<n;i++)
	{
		(*m_pssMain)<<"<use x=\""<<WorldToBBx(pCx[i])-radius/2<<"\" y=\""<<WorldToBBy(pCy[i])-radius/2<<"\" xlink:href=\"#d"<<m_liCurDef<<"\" />\n";
	}

	m_liCurDef++;
}

void CSVGInterface::PushClipWorld(double llx, double lly, double urx, double ury)
{
	CFileGfxInterface::PushClipWorld(llx,lly,urx,ury);

	(*m_pssMain)<<"<svg"
		<<" width=\""<< WorldToBBAbsx(urx-llx) << "px\" height=\"" << WorldToBBAbsy(lly-ury) << "px\"" 
		<<" x=\""<<WorldToBBx(llx)<<"\" y=\""<<WorldToBBy(ury)<<"\""
		<<" viewBox=\""<<WorldToBBx(llx)<<" "<<WorldToBBy(ury)<<" "<<WorldToBBAbsx(urx-llx)<<" "<<WorldToBBAbsy(lly-ury)<<"\" >\n";
}

void CSVGInterface::PopClipWorld()
{
	CFileGfxInterface::PopClipWorld();
	(*m_pssMain)<<" </svg>\n";
}

void CSVGInterface::SetDash(const char* dash)
{
	int count;
	char buf[256];
	std::istrstream istr(dash);
	int length;

	m_state.dash="";
	count = 0;
	while ( !istr.eof())
	{
		istr>>length;
		sprintf(buf,"%d",length);
		if (count!=0)
			m_state.dash+=",";

		m_state.dash+=buf;
		count++;
	}
}

void CSVGInterface::SetFont(long scale)
{
	m_state.m_font.lfHeight=scale;
}

void CSVGInterface::SetFont(const LOGFONT& logFont)
{
	m_state.m_font=logFont;
}

void CSVGInterface::SetLineWidth(double width)
{
	m_state.linewidth=__max(1,width);
}

void CSVGInterface::SetColor(double r, double g, double b, double a)
{
	m_state.strokecol.r = __max(0, __min( 1, r));
	m_state.strokecol.g = __max(0, __min( 1, g));
	m_state.strokecol.b = __max(0, __min( 1, b));
	m_state.strokecol.a = __max(0, __min( 1, a));
}

void CSVGInterface::SetFillColor(double r, double g, double b, double a)
{
	m_state.fillcol.r = __max(0, __min( 1, r));
	m_state.fillcol.g = __max(0, __min( 1, g));
	m_state.fillcol.b = __max(0, __min( 1, b));
	m_state.fillcol.a = __max(0, __min( 1, a));
}

void CSVGInterface::DrawTextLeft(double x, double y, const char* str, double angle)
{
	(*m_pssMain)<<"<text font-family=\"Verdana\" font-size=\""<<m_state.m_font.lfHeight<<"\" ";
	SRGBA temp = m_state.fillcol;
	m_state.fillcol = m_state.strokecol;
	PutFillColorString((*m_pssMain),true);
	PutFillAlphaString((*m_pssMain));
	m_state.fillcol = temp;

	// rotating if necessary
	if (angle!=0)
	{
	(*m_pssMain)<<" x=\"0\" y=\"0\" transform=\""
		<<"translate("
		<<WorldToBBx(x)<<","
		<<WorldToBBy(y)<<") rotate("<<-angle<<")\" ";
	}
	else
	{
	(*m_pssMain)<<" "
		<<"x=\""<<WorldToBBx(x)<<"\" "
		<<"y=\""<<WorldToBBy(y)<<"\"";
	}
	(*m_pssMain)<<">\n"
		<<str
		<<"</text>\n";
}

void CSVGInterface::DrawTextRight(double x, double y, const char* str, double angle)
{
	(*m_pssMain)<<"<text font-family=\"Verdana\" font-size=\""<<m_state.m_font.lfHeight<<"\" "
		<<"text-anchor=\"end\" ";
	SRGBA temp = m_state.fillcol;
	m_state.fillcol = m_state.strokecol;
	PutFillColorString((*m_pssMain),true);
	PutFillAlphaString((*m_pssMain));
	m_state.fillcol = temp;

	// rotating if necessary
	if (angle!=0)
	{
	(*m_pssMain)<<" x=\"0\" y=\"0\" transform=\""
		<<"translate("
		<<WorldToBBx(x)<<","
		<<WorldToBBy(y)<<") rotate("<<-angle<<")\" ";
	}
	else
	{
	(*m_pssMain)<<" "
		<<"x=\""<<WorldToBBx(x)<<"\" "
		<<"y=\""<<WorldToBBy(y)<<"\"";
	}

	(*m_pssMain)<<">\n"
	<<str
	<<"</text>\n";
}

void CSVGInterface::DrawTextCenter(double x, double y, const char* str, double angle)
{
	(*m_pssMain)<<"<text font-family=\"Verdana\" font-size=\""<<m_state.m_font.lfHeight<<"\" "
		<<"text-anchor=\"middle\" ";
	SRGBA temp = m_state.fillcol;
	m_state.fillcol = m_state.strokecol;
	PutFillColorString((*m_pssMain),true);
	PutFillAlphaString((*m_pssMain));
	m_state.fillcol = temp;

	// rotating if necessary
	if (angle!=0)
	{
	(*m_pssMain)<<" x=\"0\" y=\"0\" transform=\""
		<<"translate("
		<<WorldToBBx(x)<<","
		<<WorldToBBy(y)<<") rotate("<<-angle<<")\" ";
	}
	else
	{
	(*m_pssMain)<<" "
		<<"x=\""<<WorldToBBx(x)<<"\" "
		<<"y=\""<<WorldToBBy(y)<<"\"";
	}

	(*m_pssMain)<<">\n"
		<<str
		<<"</text>\n";
}


void CSVGInterface::DrawTextStrip(const std::vector<SPointF>& vPoints, const std::vector<std::string>& vStrings, ETextAlignment ta, double angle )
{
	ASSERT(vPoints.size() == vStrings.size());
	for (UINT i=0;i<vPoints.size();i++)
	{
		switch(ta)
		{
		case TextAlignmentLeft:
			DrawTextLeft(vPoints[i].x, vPoints[i].y, vStrings[i].c_str(), angle);
			break;
		case TextAlignmentCenter:
			DrawTextCenter(vPoints[i].x, vPoints[i].y, vStrings[i].c_str(), angle);
			break;
		case TextAlignmentRight:
			DrawTextRight(vPoints[i].x, vPoints[i].y, vStrings[i].c_str(), angle);
			break;
		}
	}
}

void CSVGInterface::DrawSurf(int nx, int ny, double llx, double lly, double dx, double dy, double* pColor)
{
	int i,j,k;
	int index[4];
	double r,g,b;
	for (i=0;i<ny-1;i++)
	{	
		for (j=0;j<nx-1;j++)
		{
			index[0]  = i*nx+j;
			index[1]  = (i+1)*nx+j;
			index[2]  = i*nx+j+1;
			index[3]  = (i+1)*nx+j+1;

			// setting color as average
			r=g=b=0;
			for (k=0; k<4; k++)
			{
				r+=pColor[index[k]*3];
				g+=pColor[index[k]*3+1];
				b+=pColor[index[k]*3+2];
			}
			r/=4;
			g/=4;
			b/=4;

			SetFillColor(r,g,b);
			SetColor(r,g,b);
			(*m_pssMain)<<"<rect ";
			// fill type
			PutFillColorString((*m_pssMain),true);
			PutStrokeColorString((*m_pssMain));

			(*m_pssMain)<<"x=\""<<WorldToBBx(llx + j*dx)<<"\" "
				<<"y=\""<<WorldToBBy(lly + (ny-(i+1))*dy)<<"\" "
				<<"width=\""<<WorldToBBAbsx(dx)<<"\" "
				<<"height=\""<<WorldToBBAbsy(-dy)<<"\" ";
		
			(*m_pssMain)<<"/>\n";
		}
	}
}

void CSVGInterface::DrawVectorField(int nx, int ny, double llx, double lly, double dx, double dy, double* pV, double lineWidth )
{

}

void CSVGInterface::WriteHeader()
{
	//svg header
	(*m_pssFile)<<"<?xml version=\"1.0\" standalone=\"no\"?>\n"
		<<"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/TR/2002/WD-SVG11-20020215/DTD/svg11.dtd\">\n"
		<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
		<<"width=\""<< GetBBWidth() << "px\" height=\"" << GetBBHeight() << "px\" viewBox=\"" 
		<<GetBBLeft()<<" "<<GetBBBottom()<<" "<<GetBBWidth()<<" "<<GetBBHeight()<<"\" >\n"
		<<"<title>"<<m_sTitle<<"</title>\n"
		<<"<desc>Author: "<<m_sCreator<<", "<<m_sCreationDate<<"</desc>\n";

}

void CSVGInterface::DrawGridHor(double llx, double urx, double lly, double ury,double dy)
{
	AddComment("Drawing horizontal grid");
	double y=lly;
	
	int count;
	(*m_pssMain)<<"<path ";
	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));

	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<"stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}
	(*m_pssMain)<<"stroke-width=\""<<m_state.linewidth<<"\" d=\"";
	// sending points
	count=0;
	y=lly;
	(*m_pssMain)<<"M "<<WorldToBBx(urx)<<" "<<WorldToBBy(y)<<" ";
	while (y<ury)
	{
		(*m_pssMain)<<" h "<<-WorldToBBAbsx(urx-llx)<<" m "<<WorldToBBAbsx(urx-llx)<<" "<<WorldToBBAbsy(dy);
		count++;
		y+=dy;
		if (count%5==0)
			(*m_pssMain)<<"\n";
	}
	(*m_pssMain)<<"\" />\n";
}

void CSVGInterface::DrawGridVer(double llx, double urx, double lly, double ury,double dx)
{
	AddComment("Drawing vertical grid");
	double x;
	
	int count;
	(*m_pssMain)<<"<path ";
	PutStrokeColorString((*m_pssMain));
	PutStrokeAlphaString((*m_pssMain));
	if (!m_state.dash.empty())
	{
		(*m_pssMain)<<"stroke-dasharray=\""<<m_state.dash.c_str()<<"\" ";
	}
	(*m_pssMain)<<"stroke-width=\""<<m_state.linewidth<<"\" d=\"";
	// sending points
	// sending points
	count=0;
	x=llx;
	(*m_pssMain)<<"M "<<WorldToBBx(x)<<" "<<WorldToBBy(ury)<<" ";
	while (x<urx)
	{
		(*m_pssMain)<<" v "<<-WorldToBBAbsy(ury-lly)<<" m "<<WorldToBBAbsx(dx)<<" "<<WorldToBBAbsy(ury-lly);
		count++;
		x+=dx;
		if (count%5==0)
			m_file<<"\n";
	}

	(*m_pssMain)<<"\" />\n";
}

void CSVGInterface::PutStrokeColorString(std::ostrstream& ssout)
{
	ssout<<"stroke=\"rgb("
		<<(int)floor(m_state.strokecol.r*100)<<"%,"
		<<(int)floor(m_state.strokecol.g*100)<<"%,"
		<<(int)floor(m_state.strokecol.b*100)<<"%"
		<<")\" ";
}

void CSVGInterface::PutFillColorString(std::ostrstream& ssout,bool filled)
{
	if (filled)
	{
		ssout<<"fill=\"rgb("
			<<(int)floor(m_state.fillcol.r*100)<<"%,"
			<<(int)floor(m_state.fillcol.g*100)<<"%,"
			<<(int)floor(m_state.fillcol.b*100)<<"%"
			<<")\" ";
	}
	else
	{
		ssout<<"fill=\"none\" ";
	}
}

void CSVGInterface::PutStrokeAlphaString(std::ostrstream& ssout)
{
	if (m_state.strokecol.a != 1)
		ssout<<" stroke-opacity=\""<<m_state.strokecol.a<<"\" ";
}

void CSVGInterface::PutFillAlphaString(std::ostrstream& ssout)
{
	if (m_state.fillcol.a != 1)
		ssout<<" fill-opacity=\""<<m_state.fillcol.a<<"\" ";
}

}