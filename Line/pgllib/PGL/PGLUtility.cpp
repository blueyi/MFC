// GLUtility.cpp: implementation of the CPGLUtility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLUtility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CPGLUtility::ColorMap2String(PGL_COLORMAP cm)
{
	switch (cm)
	{
	case pglCmHsv:
		return CString("HSV");
	case pglCmJet:
		return CString("Jet");
	case pglCmGray:
		return CString("Gray");
	case pglCmPink:
		return CString("Pink");
	case pglCmCool:
		return CString("Cool");
	case pglCmBone:
		return CString("Bone");
	case pglCmCopper:
		return CString("Copper");
	case pglCmHot:
		return CString("Hot");
	case pglCmAutumn:
		return CString("Autumn");
	case pglCmWinter:
		return CString("Winter");
	case pglCmSpring:
		return CString("Spring");
	case pglCmSummer:
		return CString("Summer");
	default:
		return CString("HSV");
	}
}

PGL_COLORMAP CPGLUtility::String2ColorMap(CString str)
{
	if (str=="HSV")
		return pglCmHsv;

	if (str=="Jet")
		return pglCmJet;
	
	if (str=="Gray")
		return pglCmGray;
	
	if (str=="Pink")
		return pglCmPink;

	if (str=="Cool")
		return pglCmCool;

	if (str=="Bone")
		return pglCmBone;

	if (str=="Copper")
		return pglCmCopper;

	if (str=="Hot")
		return pglCmHot;

	if (str=="Autumn")
		return pglCmAutumn;

	if (str=="Winter")
		return pglCmWinter;

	if (str=="Spring")
		return pglCmSpring;

	if (str=="Summer")
		return pglCmSummer;
	
	return pglCmHsv;
}

#pragma optimize( "", off )

void CPGLUtility::DrawColorMap(gfxinterface::CGfxInterface& gfx, PGL_COLORMAP eCM, CPGLView* pView)
{
	CPGLColor col;
	float w,h;
	float x,y;
	
	x=(float)(pView->GetWidth()-20);
	w=10;
	if (x<1)
		return;

	y=(float)(pView->GetHeight()*0.25);
	h=(float)(pView->GetHeight()*0.5);
/*	
	// drawing colormap
	switch(eCM)
	{
	case pglCmHsv:
		glBegin(GL_QUAD_STRIP);
		// line 0
		HSV(0,col);
		col.MakeCurrent(gfx);
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// line 1
		HSV(1.0/6.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h/6.0f);
		glVertex2f(x+w,y+h/6.0f);
		// line 1
		HSV(1.0/3.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h/3.0f);
		glVertex2f(x+w,y+h/3.0f);
		// line 1
		HSV(0.5f,col);
		col.MakeCurrent();
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x+w,y+h*0.5f);
		// line 1
		HSV(2.0/3.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h*2.0f/3.0f);
		glVertex2f(x+w,y+h*2.0f/3.0f);
		// line 1
		HSV(5.0/6.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h*5.0f/6.0f);
		glVertex2f(x+w,y+h*5.0f/6.0f);
		// line 1
		HSV(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		HSV(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmJet:
		glBegin(GL_QUAD_STRIP);
		// first line
		Jet(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Jet(0.125,col);
		col.MakeCurrent();
		glVertex2f(x,y+0.125f*h);
		glVertex2f(x+w,y+0.125f*h);
		// third line
		Jet(0.375,col);
		col.MakeCurrent();
		glVertex2f(x,y+0.375f*h);
		glVertex2f(x+w,y+0.375f*h);
		// fourth line
		Jet(0.625,col);
		col.MakeCurrent();
		glVertex2f(x,y+0.625f*h);
		glVertex2f(x+w,y+0.625f*h);
		// fifth line
		Jet(0.875,col);
		col.MakeCurrent();
		glVertex2f(x,y+0.875f*h);
		glVertex2f(x+w,y+0.875f*h);
		// sixth line
		Jet(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Jet(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmGray:
		glBegin(GL_QUAD_STRIP);
		// first line
		Gray(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Gray(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Gray(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmPink:
		glBegin(GL_QUAD_STRIP);
		// first line
		Pink(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Pink(3.0/8.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+3.0f/8.0f*h);
		glVertex2f(x+w,y+3.0f/8.0f*h);
		// line 3
		Pink(3.0/4.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+3.0f/4.0f*h);
		glVertex2f(x+w,y+3.0f/4.0f*h);
		// line 4
		Pink(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Pink(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmCool:
		glBegin(GL_QUAD_STRIP);
		// first line
		Cool(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Cool(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Cool(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmBone:
		glBegin(GL_QUAD_STRIP);
		// first line
		Bone(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Bone(3.0/8.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+3.0f/8.0f*h);
		glVertex2f(x+w,y+3.0f/8.0f*h);
		// line 3
		Bone(3.0/4.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+3.0f/4.0f*h);
		glVertex2f(x+w,y+3.0f/4.0f*h);
		// line 4
		Bone(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Bone(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmCopper:
		glBegin(GL_QUAD_STRIP);
		// first line
		Copper(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Copper(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Copper(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmHot:
		glBegin(GL_QUAD_STRIP);
		// first line
		Hot(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Hot(3.0/8.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+3.0f/8.0f*h);
		glVertex2f(x+w,y+3.0f/8.0f*h);
		// line 3
		Hot(3.0/4.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+3.0f/4.0f*h);
		glVertex2f(x+w,y+3.0f/4.0f*h);
		// line 4
		Hot(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Hot(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmAutumn:
		glBegin(GL_QUAD_STRIP);
		// first line
		Autumn(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Autumn(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Autumn(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmWinter:
		glBegin(GL_QUAD_STRIP);
		// first line
		Winter(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Winter(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Winter(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
	case pglCmSpring:
		glBegin(GL_QUAD_STRIP);
		// first line
		Spring(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Spring(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();

		// drawing little triangle...
		Spring(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;

	case pglCmSummer:
		glBegin(GL_QUAD_STRIP);
		// first line
		Summer(0,col);
		col.MakeCurrent();
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		// second line
		Summer(1.0,col);
		col.MakeCurrent();
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glEnd();
		// drawing little triangle...
		Summer(0.5,col);
		col.MakeCurrent();
		glBegin(GL_TRIANGLES);
		glVertex2f(x,y+h*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glVertex2f(x-(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		
		glVertex2f(x+w,y+h*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f-w*0.5f);
		glVertex2f(x+w+(float)(w/sqrt(2.0)),y+h*0.5f+w*0.5f);
		glEnd();
		break;
		}
*/
		// drawing rectangle
		gfx.DrawRect(x,y,x+w,y+h);

		// drawing middle
		gfx.DrawLine(x,y+h*0.5f,x+w,y+h*0.5f);
}
