// viewGL.h: interface for the CViewGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWCLASS_H__338966C8_1C93_11D4_8D89_00409503B978__INCLUDED_)
#define AFX_VIEWCLASS_H__338966C8_1C93_11D4_8D89_00409503B978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StateGL.h"
/**An abstratc class that defines a view.
This class is used as a base to build 2D and 3D views. These
views will be used with OpenGL to render the channels.
@see CTimer
*/
class CViewGL : public CObject
{
DECLARE_SERIAL(CViewGL);

public:

	/// default constructor
	CViewGL()
	{	m_iTx=m_iTy=m_iWidth=m_iHeight=0; m_bPostReshape=TRUE; m_bViewportInfo=TRUE;};
	/// copy construtor
	CViewGL(const CViewGL& v)
	{	m_iTx=v.m_iTx; m_iTy=v.m_iTy; m_iWidth=v.m_iWidth; m_iHeight=v.m_iHeight;m_bPostReshape=TRUE; 
	    m_StateGL=v.m_StateGL;};
	/// assignement constructor
	CViewGL& operator=(const CViewGL& v)
	{	
		if (&v!=this)
		{ m_iTx=v.m_iTx; m_iTy=v.m_iTy; m_iWidth=v.m_iWidth; m_iHeight=v.m_iHeight;m_bPostReshape=TRUE;
		m_StateGL=v.m_StateGL;}
		return *this;
	}
	/// destructor
	virtual ~CViewGL() {};
	/// initialize OpenGL states (virtual function to override in children classes).
	virtual void InitGLState()
	{	m_StateGL.SetStateGL();};
	/// resizing view (virtual function to override in children classes).
	virtual void Reshape()
	{	// view is reshaped...
		m_bPostReshape=FALSE;};

	/// returns m_iHeight of the viewport
	GLsizei GetHeight() const
	{ return m_iHeight;};
	/// returns m_iWidth of the viewport
	GLsizei GetWidth() const
	{ return m_iWidth;};
	/// returns starting pixel of the viewport in x direction
	GLint GetTx() const
	{ return m_iTx;};
	/// returns starting pixel of the viewport in xy direction
	GLint GetTy() const
	{ return m_iTy;};

	CStateGL* GetState()
	{	return &m_StateGL;};
	void SetState(const CStateGL& _sgl)
	{	m_StateGL=_sgl;};

	/** Sets the viewport charateristics\\
	    {\bf Parameters :}
	    \begin{description}
			\item[\_Tx] starting x pixel of the viewport (must be >=0)
			\item[\_Ty] starting y pixel of the viewport (must be >=0)
			\item[\_width] width (in pixels) of the viewport (must be >=0)
			\item[\_height] height (in pixels) of the viewport (must be >=0)
	    \end{description}
	*/
	void SetViewport(GLint _Tx, GLint _Ty, GLsizei _width, GLsizei _height)
	{
		ASSERT(_Tx>=0); 
		ASSERT(_Ty>=0);
		ASSERT(_width>=0);
		ASSERT(_height>=0);
		m_iTx=_Tx; m_iTy=_Ty; m_iWidth=_width; m_iHeight=_height;

		// Viewport updated
		m_bViewportInfo=FALSE;

		// Needs redrawing...
		PostReshape();
	}
	void PostViewportInfo()
	{	m_bViewportInfo=TRUE;};
	BOOL NeedViewportInfo()
	{	return m_bViewportInfo;};

	/// Tells the view it needs to be reshape at the next draw...
	void PostReshape()
	{	m_bPostReshape=TRUE; };
	/// returns TRUE if the view needs reshape, FALSE otherwize.
	BOOL NeedReshape()
	{	return m_bPostReshape;};

	/// Debugging stuff
#ifdef _DEBUG
    virtual void AssertValid() const;    // Override
    virtual void Dump( CDumpContext& dc ) const;
#endif
    /// Serialization
    void Serialize( CArchive& archive );

protected:
	/// the starting x pixel of the viewport
	GLint m_iTx;
	/// the starting y pixel of the viewport
	GLint m_iTy;
	/// m_iWidth of the viewport (in pixels)
	GLsizei m_iWidth;
	/// m_iHeight of the viewport (in pixels)
	GLsizei m_iHeight;
	/// the OpenGL state
	CStateGL m_StateGL;
private:
	/// TRUE if view needs viewport informations
	BOOL m_bViewportInfo;
	/// TRUE if view needs reshaping... FALSE otherwise
	BOOL m_bPostReshape;
};

#endif // !defined(AFX_VIEWCLASS_H__338966C8_1C93_11D4_8D89_00409503B978__INCLUDED_)
