// StateGL.h: interface for the CStateGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATEGL_H__3EA79A79_DA8C_45B6_A6BE_12B1BB386762__INCLUDED_)
#define AFX_STATEGL_H__3EA79A79_DA8C_45B6_A6BE_12B1BB386762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector3.h"

class CStateGL : public CObject  
{
DECLARE_SERIAL(CStateGL);
public:
	CStateGL();
	CStateGL(const CStateGL& sgl);
	CStateGL& operator =(const CStateGL &sgl);
	virtual ~CStateGL();


	BOOL GetStateFromDC();
	
	/// ask for state updating at next draw operation
	void PostSetState()
	{	m_bPostSetState=TRUE;};
	/// ask for state updating at next draw operation
	BOOL NeedSetState()
	{	return m_bPostSetState;};
	/// updates the OpenGL states (context must be valid)
	void SetStateGL();

	// antialiasing
	BOOL GetAntialias() const
	{	return m_bAntialias;};
	void SetAntialias(BOOL _aa=TRUE)
	{	m_bAntialias=_aa;	m_bPostSetState=TRUE;};

	// BackFaceCulling
	BOOL GetBackFaceCulling() const
	{	return m_bBackFaceCulling;};
	void SetBackFaceCulling(BOOL _bc=TRUE)
	{	m_bBackFaceCulling=_bc;	m_bPostSetState=TRUE;};

	// blending
	BOOL GetBlending() const
	{	return m_bBlending;};
	void SetBlending(BOOL _b=TRUE)
	{	m_bBlending=_b;	m_bPostSetState=TRUE;};

	// DepthTest
	BOOL GetDepthTest() const
	{	return m_bDepthTest;};
	void SetDepthTest(BOOL _dt=TRUE)
	{	m_bDepthTest=_dt;	m_bPostSetState=TRUE;};

	// StencilTest
	BOOL GetStencilTest() const
	{	return m_bStencilTest;};
	void SetStencilTest(BOOL _st=TRUE)
	{	m_bStencilTest=_st;	m_bPostSetState=TRUE;};

	// Lighting
	BOOL GetLighting() const
	{	return m_bLighting;};
	void SetLighting(BOOL _l=TRUE)
	{	m_bLighting=_l;	m_bPostSetState=TRUE;};

	// Gouraud
	BOOL GetGouraud() const
	{	return m_bGouraud;};
	void SetGouraud(BOOL _g=TRUE)
	{	m_bGouraud=_g;	m_bPostSetState=TRUE;};

	// LineWidth
	GLfloat GetLineWidth() const
	{	return m_fLineWidth;};
	void SetLineWidth(GLfloat _lw=1.5f)
	{	m_fLineWidth=(GLfloat)__max(0.0,_lw);	m_bPostSetState=TRUE;};

	// LineStipple
	BOOL GetLineStipple() const
	{	return m_bLineStipple;};
	void SetLineStipple(BOOL _ls=FALSE)
	{	m_bLineStipple=_ls;	m_bPostSetState=TRUE;};

	// Polygon mode
	GLint GetPolygonMode() const
	{	return m_iPolygonMode;};
	void SetPolygonMode(int _pm=GL_FILL)
	{	ASSERT((_pm==GL_POINT) ||
		(_pm==GL_LINE) ||
		(_pm==GL_FILL));
		m_iPolygonMode=_pm; m_bPostSetState=TRUE;
	};

	// Background color
	const CVector3& GetBkgColor() const
	{	return m_cBkgColor;};
	void SetBkgColor(const CVector3& _bc)
	{	m_cBkgColor=_bc;	m_bPostSetState=TRUE;};

	/// Debugging stuff
#ifdef _DEBUG
    virtual void AssertValid() const;    // Override
    virtual void Dump( CDumpContext& dc ) const;
#endif
    /// Serialization
    void Serialize( CArchive& archive );

protected:
	BOOL m_bPostSetState;

	BOOL m_bAntialias;
	BOOL m_bBlending;
	BOOL m_bLighting;
	BOOL m_bLineStipple;
	BOOL m_bGouraud;
	BOOL m_bDepthTest;
	BOOL m_bBackFaceCulling;
	BOOL m_bStencilTest;
	GLfloat m_fLineWidth;
	GLint m_iPolygonMode; 
	CVector3 m_cBkgColor;
};

#endif // !defined(AFX_STATEGL_H__3EA79A79_DA8C_45B6_A6BE_12B1BB386762__INCLUDED_)
