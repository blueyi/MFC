/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  de Halleux Jonathan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact: de Halleux Jonathan, pglinfo@patabelgos.org
*/
// GLUtility.h: interface for the CPGLUtility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLGLUTILITY_H__0E205062_3FFE_4548_9974_C5136B8D6580__INCLUDED_)
#define AFX_PGLGLUTILITY_H__0E205062_3FFE_4548_9974_C5136B8D6580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLColor.h"
#include "PGLView.h"

enum PGL_COLORMAP
{
	pglCmHsv,
	pglCmJet,
	pglCmGray,
	pglCmPink,
	pglCmCool,
	pglCmBone,
	pglCmCopper,
	pglCmHot,
	pglCmAutumn,
	pglCmWinter,
	pglCmSpring,
	pglCmSummer
};

class PGL_EXT_CLASS CPGLUtility  
{
public:

	// color map functions...
	static void DrawColorMap(gfxinterface::CGfxInterface& gfx, PGL_COLORMAP eCM, CPGLView* pView);

	/**name Colormap function
	*/
	static inline void ColorMap(PGL_COLORMAP eCM,double alpha, CPGLColor& col);

	/**name Hue-Saturation-Value color map
		An HSV colormap varies the hue commponent of the hue-saturation-value color model.
		The colors with red, pass trhough yellow, green, cyan, blue, magenta and return
		to red.
	*/
	static inline void HSV(double alpha, CPGLColor& col);
	/// Variant of HSV.
	static inline void Jet(double alpha, CPGLColor& col);
	/// Linear pglCmGray-scale color map
	static inline void Gray(double alpha, CPGLColor& col);
	/// Pastel shades of pglCmPink color map.
	static inline void Pink(double alpha, CPGLColor& col);
	/// Shades of cyan and magenta color map
	static inline void Cool(double alpha, CPGLColor& col);
	/// Gray-scale with a tinge of blue color map.
	static inline void Bone(double alpha, CPGLColor& col);
	/// Linear pglCmCopper-tone color map
	static inline void Copper(double alpha, CPGLColor& col);
	/// Black-red-yellow-white color map
	static inline void Hot(double alpha, CPGLColor& col);
	/// Shades of red and yellow color map.
	static inline void Autumn(double alpha, CPGLColor& col);
	/// Shades of blue and green color map.
	static inline void Winter(double alpha, CPGLColor& col);
	/// Shades of magenta and yellow color map.
	static inline void Spring(double alpha, CPGLColor& col);
	/// Shades of green and yellow colormap.
	static inline void Summer(double alpha, CPGLColor& col);

	static CString ColorMap2String(PGL_COLORMAP cm);
	static PGL_COLORMAP String2ColorMap(CString str);
};

#endif // !defined(AFX_PGLGLUTILITY_H__0E205062_3FFE_4548_9974_C5136B8D6580__INCLUDED_)

inline void CPGLUtility::ColorMap(PGL_COLORMAP eCM, double alpha, CPGLColor& col)
{
	switch(eCM)
	{
	case pglCmHsv:
		HSV(alpha,col);
		break;
	case pglCmJet:
		Jet(alpha,col);
		break;
	case pglCmGray:
		Gray(alpha,col);
		break;
	case pglCmPink:
		Pink(alpha,col);
		break;
	case pglCmCool:
		Cool(alpha,col);
		break;
	case pglCmBone:
		Bone(alpha,col);
		break;
	case pglCmCopper:
		Copper(alpha,col);
		break;
	case pglCmHot:
		Hot(alpha,col);
		break;
	case pglCmAutumn:
		Autumn(alpha,col);
		break;
	case pglCmWinter:
		Winter(alpha,col);
		break;
	case pglCmSpring:
		Spring(alpha,col);
		break;
	case pglCmSummer:
		Summer(alpha,col);
		break;
	}
}


/// Black-red-yellow-white color map
inline void CPGLUtility::HSV(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);
	
	double h=alpha*6;
	double s=1.0;
	double v=1.0;

	int k=(int)floor(h);
	double f=h-k;
	float t=(float)(1.0-s);
	float n=(float)(1.0-s*f);
	float p=(float)((1.0-(s*(1.0-f))));
	float e=1.0f;

	// reshaping
	float scale;

	switch(k)
	{
	case 0:
		scale=1.0f/(__max(e, __max(p, t)));
		e*=scale;
		p*=scale;
		t*=scale;
		col.SetColor(e,p,t);
		break;
	case 1:
		scale=1.0f/(__max(e, __max(n, t)));
		e*=scale;
		n*=scale;
		t*=scale;
		col.SetColor(n,e,t);
		break;
	case 2:
		scale=1.0f/(__max(e, __max(p, t)));
		e*=scale;
		p*=scale;
		t*=scale;
		col.SetColor(t,e,p);
		break;
	case 3:
		scale=1.0f/(__max(n, __max(p, 1)));
		n*=scale;
		t*=scale;
		col.SetColor(t,n,1);
		break;
	case 4:
		scale=1.0f/(__max(t, __max(p, 1)));
		p*=scale;
		t*=scale;
		col.SetColor(p,t,1);
		break;
	case 5:
		scale=1.0f/(__max(e, __max(n, t)));
		e*=scale;
		n*=scale;
		t*=scale;
		col.SetColor(e,t,n);
		break;
	}

}

inline void CPGLUtility::Jet(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);

	if (alpha<=0.125)
	{
		col.SetColor(0,0,(float)((0.125+alpha)/0.25));
	}
	else if (alpha<=0.375)
	{
		col.SetColor(0,
			(float)((alpha-0.125)/0.25),
			1.0f);
	}
	else if (alpha<=0.625)
	{
		col.SetColor((float)((alpha-0.375)/0.25),
				1.0f,
				(float)(1.0-(alpha-0.375)/0.25));
	}
	else if (alpha<=0.875)
	{
		col.SetColor(1.0f,
			(float)(1.0-(alpha-0.625)/0.25),
			0.0f);
	}
	else
	{
		col.SetColor((float)(1.0-(alpha-0.875)/0.25),
			0.0,0.0);
	}
}

inline void CPGLUtility::Gray(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);
	col.SetColor((float)alpha,(float)alpha,(float)alpha);
}

inline void CPGLUtility::Pink(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);
	static CPGLColor vh;

	Hot(alpha,vh);

	col.SetColor((float)sqrt((2*alpha + vh.GetRed())/3),
		(float)sqrt((2*alpha + vh.GetGreen())/3),
		(float)sqrt((2*alpha + vh.GetBlue())/3));
}

inline void CPGLUtility::Cool(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);

	col.SetColor((float)alpha,
		1.0f-(float)alpha,
		1.0f);
}

inline void CPGLUtility::Bone(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);
	static CPGLColor vh;

	Hot(alpha,vh);

	col.SetColor((float)((7.0*alpha+vh.GetBlue())/8.0),
		(float)((7.0*alpha+vh.GetGreen())/8.0),
		(float)((7.0*alpha+vh.GetRed())/8.0));
}

inline void CPGLUtility::Copper(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);

	col.SetColor((float)__min(1.0,alpha*1.25),
		(float)__min(1.0,alpha*0.7812),
		(float)__min(1.0,alpha*0.4975));
}

inline void CPGLUtility::Hot(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);
	static const double c38=3.0/8.0;
	if (alpha<=c38)
	{
			col.SetColor((float)(alpha/c38),
			0,0);
	}
	else if (alpha<=2*c38)
	{
		col.SetColor(1.0f,
			(float)((alpha-c38)/c38),
			0);
	}
	else
	{
		col.SetColor(1.0f,1.0f,
		(float)((alpha-2*c38)/(1.0-2*c38)));
	}
}

inline void CPGLUtility::Autumn(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);

	col.SetColor(1.0f,
		(float)alpha,
		0);
}

inline void CPGLUtility::Winter(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);

	col.SetColor(0.0,
		(float)alpha,
		(float)(0.5+(1.0-alpha)/2.0));
}

inline void CPGLUtility::Spring(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);
	col.SetColor(1.0f,
		(float)alpha,
		(float)(1.0-alpha));
}

inline void CPGLUtility::Summer(double alpha, CPGLColor& col)
{
	ASSERT(alpha<=1.0);
	ASSERT(alpha>=0.0);

	col.SetColor((float)alpha,
		(float)(0.5+alpha/2.0),
		0.4f);
}

