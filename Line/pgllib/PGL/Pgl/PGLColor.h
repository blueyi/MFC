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
// ColorGL.h: interface for the CPGLColor class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_PGLCOLOR_H__4DACBB75_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
#define AFX_PGLCOLOR_H__4DACBB75_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*!
	\defgroup PGLBasicGroup Miscellanous
	\ingroup PGLGroup
*/

/*! \brief A simple RGBA color object.

\ingroup PGLBasicGroup
This object represent a RGAB color. All values for colors must be in [0,1].
*/
class PGL_EXT_CLASS CPGLColor  : public CObject
{
public:
///
	DECLARE_SERIAL(CPGLColor);

	/**@name Class Members*/
	//@{
	/// a constructor
	CPGLColor(float red=1.0f, float green=0.0f, float blue=0.0f, float alpha=1.0f)
	{	m_c[0]=(float)__max(0.0f,__min(1.0f,red)); 
		m_c[1]=(float)__max(0.0f,__min(1.0f,green)); 
		m_c[2]=(float)__max(0.0f,__min(1.0f,blue)); 
		m_c[3]=(float)__max(0.0f,__min(1.0f,alpha));};
	/// a constructor
	CPGLColor(float _c[4])
	{	m_c[0]=(float)__max(0.0f,__min(1.0f,_c[0])); 
		m_c[1]=(float)__max(0.0f,__min(1.0f,_c[1])); 
		m_c[2]=(float)__max(0.0f,__min(1.0f,_c[2])); 
		m_c[3]=(float)__max(0.0f,__min(1.0f,_c[3]));};
	/// copy constructor
	CPGLColor(const CPGLColor& col)
	{	m_c[0]=col.m_c[0]; 
		m_c[1]=col.m_c[1]; 
		m_c[2]=col.m_c[2]; 
		m_c[3]=col.m_c[3];};
	/// assignement constructor
	CPGLColor& operator = (const CPGLColor& col)
	{	// prevent self-assignement
		if (&col != this)
		{m_c[0]=col.m_c[0];
			m_c[1]=col.m_c[1];
			m_c[2]=col.m_c[2];
			m_c[3]=col.m_c[3];}
		return *this;};

	/// destructor
	virtual ~CPGLColor(){};


	/// sets a new color
	void SetColor(float _c[4]) 
	{	m_c[0]=(float)__max(0.0,__min(1.0f,_c[0])); 
		m_c[1]=(float)__max(0.0,__min(1.0f,_c[1]));
		m_c[2]=(float)__max(0.0,__min(1.0f,_c[2]));
		m_c[3]=(float)__max(0.0,__min(1.0f,_c[3])); };
	///sets the color
	void SetColor(float red,float green,float blue,float alpha=1.0f)
	{	m_c[0]=(float)__max(0.0,__min(1.0f,red)); 
		m_c[1]=(float)__max(0.0,__min(1.0f,green));
		m_c[2]=(float)__max(0.0,__min(1.0f,blue));
		m_c[3]=(float)__max(0.0,__min(1.0f,alpha)); };
	/// sets the red component of color (must be in [0, 1])
		void SetRed(float f)		{	m_c[0]=f;};
	/// sets the green component of color (must be in [0, 1])
	void SetGreen(float f)	{	m_c[1]=f;};
	/// sets the blue component of color (must be in [0, 1])
	void SetBlue(float f)		{	m_c[2]=f;};
	/// sets the alpha component of color (must be in [0, 1])
	void SetAlpha(float f)	{	m_c[3]=f;};
	/// getting color component (c must of size >=4)
	void GetColor(float *_c) const
	{	_c[0]=m_c[0]; 
		_c[1]=m_c[1];
		_c[2]=m_c[2];
		_c[3]=m_c[3]; };
	/// gets red component
	float GetRed()	const	{ return m_c[0];}; 
	/// gets green component
	float GetGreen()	const	{ return m_c[1];};
	/// gets blue component
	float GetBlue()const	{ return m_c[2];};
	/// gets alpha component
	float GetAlpha()const	{ return m_c[3];};
	/// gets color component (0 for red, 1 for green, 2 for blue and 3 for alpha)
	float operator [] (int i) const
	{ ASSERT(i>=0 && i<4); return m_c[i];};
	/// gets a reference to color component (0 for red, 1 for green, 2 for blue and 3 for alpha)
	float& operator [] (int i)
	{ ASSERT(i>=0 && i<4); return m_c[i];};

	void MakeCurrent(gfxinterface::CGfxInterface& gfx){	gfx.SetColor(m_c[0],m_c[1],m_c[2],m_c[3]);};

	/// Serialize functions
	void Serialize(CArchive& archive);

	/// Debuggin functions
	#ifdef _DEBUG
///
	    virtual void Dump( CDumpContext& dc ) const;
///
	    virtual void AssertValid() const;    // Override
	#endif
	//@}
protected:
	/**@name Class Parameters*/
	//@{
	/// the color
	float m_c[4];
	//@}
};

#endif // !defined(AFX_PGLCOLOR_H__4DACBB75_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
