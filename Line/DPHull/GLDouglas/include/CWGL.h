
#ifndef _CWGL_H_
#define _CWGL_H_


#define	WGL_DONT_SWAP_BUFFERS	true
#define WGL_FONTS_LISTBASE		1000


// define group
/*!
	\defgroup OGLToolsGroup OGLTools Library : OpenGL Tools for MFC
*/

/*! \brief A Windows OpenGL rendering interface class. 

\ingroup OGLToolsGroup
CWGL is a Windows OpenGL rendering interface class.
This header defines also a few interfaceing wgl_ inlines.
 
The idea behing the CWGL is to make use
of OpenGL in Microsoft Windows as simple as possible.
 
Under Windows only one OpenGL rendering context may be active 
in a single thread. CWGL helps you write a single threaded 
windows applications which need more than one OpenGL 
rendering context.
 
\b Usage:
 
<ol>
<il> Optionaly, set different pixelformat if you are
      not satisfied with CWGL's default one.
 
<li> Enable OpenGL telling it where it should render.
 
 \code		wgl.Begin(&windowOrBitmapDC); \endcode
 
<li> Call OpenGL API functions to do the rendering.
 
<li> Disable OpenGL, first optionaly showing the rendered image.
 
\code       wgl.End(); \endcode
</ol> 
 
\b Examples:
 
In MFC view, render to window's backbuffer and swap buffers.

\code  
	CView.h
		CWGL m_wgl;
 
	CView.cpp
 		CView::OnDraw(pDC)
 		{
 			m_wgl.Begin(pDC);
 				glClearColor(1.0, 1.0, 1.0, 0.0);
 				glClear(GL_COLOR_BUFFER_BIT);
 			m_wgl.End();
 		}
\endcode
 
Render on DIB section GDI object and copy it to clipboard.
  
\code
	CRGBSurface tmpSurf;	// CRGBSurface encapsulates a DIB section GDI object
 	tmpSurf.Create(10, 10);
 
 	CWGL wgl;
 	wgl.Begin(tmpSurf.GetDC());
 		glClearColor(1.0, 1.0, 1.0, 0.0)
 		glClear(GL_COLOR_BUFFER_BIT);
 	wgl.End();
 
 	tmpSurf.CopyToClipboard();
\endcode 
 
Rendering contexts may be 'nested' if different
CWGL objects are used,
but remember that only one RC can be created for one window.

\code 
	wgl1.Begin(&windowDC);
	{
		CWGL wgl2;
		wgl2.Begin(&bitmapDC);
		wgl2.End();
		// here wgl2 destructor delete's wgl2 RC and makes
		// wgl1 RC current again.
	}
	// here all the display lists and textures of wgl1 RC
	// remain valid
	wgl1.End(); 
\endcode

If you need an RC for a window for which you
no longer have a device context available,
you may call wgl.Begin() with no DC
to make last used RC of this window current again.

\code
	wgl.Begin(&windowDC);
	wgl.End(); 
	...

	// some time in the future...
	wgl.Begin();
	wgl.End(); 
\endcode

After a call to CWGL::End() you may ask what the
rendering time was with GetRenderingTime().


NOTES: 

When rendering on different DIB sections or bitmaps, a new RC with
PFD_DRAW_TO_BITMAP pixelformat is always created for that bitmap.

WindowsNT: CWGL synchronizes GDI and OpenGL access to
rendering surface automaticaly.

When switching RC's of different pixelformats with CWGL,
all textures and display lists must be recreated in a new RC.
Display list sharing is possible when RCs are of the same pixelformat
(this means also that you cannot share between window and bitmap RC).

Please also note that under Windows only one RC 
may be created for a given window and this RC cannot be
used for another window.

\sa CGLImage
\sa CRGBSurface
\author (c) W.Weyna 'Voytec', http://shiptech.tuniv.szczecin.pl/~weyna/OpenGL/
\author Independent JPEG library : http://www.ijg.org
*/
class CWGL
{
public:
	//! Default constructor.
	CWGL();
	//! Default destructor. Destroy all.
	virtual ~CWGL();

// Attributes
public:
	/*! \name Attributes */
	//@{
	//! TRUE if a new RC has been created.
	bool	NewRCCreated() {return m_bNewRCCreated; }
	//! Rendering time
	DWORD	GetRenderingTime() {return m_dwRenderingTime; }
	//! Pointer to DC	
	CDC*	GetRenderingDC() {return m_pDC; }
	//! true if rendering to bitmap.
	bool	RenderingToBitmap() {return m_pDC ? false : true;}
	//! true if full screen mode	
	bool	IsFullScreen() {return m_bFullScreen; }
	//! returns window width (in pixels)
	int		GetFSWidth() {return m_windowRect.Width(); }
	//! returns window height (in pixels)
	int		GetFSHeight() {return m_windowRect.Height(); }
	//@}
protected:
	CDC*	m_pDC;
	CDC*	m_pBitmapDC;
	CWnd*	m_pWnd;
	HWND	m_hWnd;
	HGLRC	m_hWndRC;
	HGLRC	m_hFSWndRC;
	HGLRC	m_hBmpRC;
	HDC		m_hPrevDC;
	HGLRC	m_hPrevRC;
	bool    m_bNewRCCreated;
	bool    m_bWeCreatedDC;

	DWORD	m_dwRenderingTime;
	DWORD	m_dwStartRenderingTime;

	LOGFONT m_defaultLogfont;
	CFont	m_defaultFont;

	LOGFONT m_currentLogfont;
	CFont	m_currentFont;

	CFont*	m_pFont;

	HWND	m_hFSWnd;
	HWND	m_hViewWnd;
	CView*	m_pView;
	bool	m_bFullScreen;
	int		m_nMode;
	CRect	m_windowRect;
	
// Operations
public:
	/*! \name Operations: */
	//@{
	/*! \brief Enables OpenGL.

	It enables OpenGL and makes all subsequent OpenGL calls
	render on a surface associated with supplied DC.
	After all OpenGL calls have been made, 
	CWGL::End() must be called. 
	Any OpenGL calls made before a call to CWGL::Begin()
	have no effect.
	\sa CWGL::End
	*/
	bool Begin(CDC* pDC = NULL);
	/*! \brief End OpenGL

	Finish rendering and if rendered to double-buffered window, 
	show the rendered image.
	Release currently selected RC.
	After a call to this function is made, any subsequent
	OpenGL calls will have no effect.
	\sa CWGL::Begin
	*/
	void End(bool m_bDontSwapBuffers = false);
	/*! \brief Toggle full screen on/off

	Call this function to toggle full screen mode.
	This function will also subclass the created full screen window
	if a pointer to a CView derived view is passed.
	See switch statement for description of nMode parameter.
	*/
	bool FullScreen(int nMode = -1, CView* pView = NULL); 
	/*! \brief Draw string str at raster position.
	
	\sa CWGL::CompileFonts
	*/
	void TextOut(const CString& str);
	//@}
// Helpers
public:
	/*! \name Helpers */
	//@{
	/*! \brief Time helper.
	
	  This fuction returns a time difference in miliseconds
	between the current time and dwStartTime obtained 
	with GetTickCount(). It works also when tick counter will
	reset which happens after every 49.5 days.
	*/
	DWORD GetTimeDif(DWORD dwStartTime);
	//@}	
protected:
	/*! \brief Sets the pixel format.
	
	Set pixelformat, default is 24bit RGB double-buffered window.
	If you want to work with different pixelformats,
	add appropriate methods by yourself.
	*/
	bool SetPixelFormat(CDC* pDC, DWORD dwFlags = 
		                   PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
						int nBitsPerPixel = 24);
	/*! \brief Compile font lists.
	
	\sa CWGL::TextOut
	*/
	void CompileFonts();
};

inline BYTE GetAValue(DWORD rgb)  {    return (BYTE)((rgb)>>24); }

inline void wgl_ClearColorCR(COLORREF cr, float fAlpha = 1.0)
{
	glClearColor(GetRValue(cr)/255.0f, GetGValue(cr)/255.0f, GetBValue(cr)/255.0f, fAlpha);
}

inline void wgl_ColorCR(COLORREF cr, float fAlpha = 1.0, float fBrightness = 1.0)
{
	glColor4f(fBrightness * GetRValue(cr)/255.0f, fBrightness * GetGValue(cr)/255.0f, fBrightness * GetBValue(cr)/255.0f, fAlpha);
}

inline void wgl_ColorCRA(COLORREF cr)
{
	glColor4f(GetRValue(cr)/255.0f, GetGValue(cr)/255.0f, GetBValue(cr)/255.0f, GetAValue(cr)/255.0f);
}

inline void wgl_ColorCRB(COLORREF cr, float fAlpha = 1.0, int nBrightness = 0)
{
	float fBrightness = 1.0;
	switch(nBrightness)
	{
	case 0:
		fBrightness = 1.0;
		break;
	case 1:
		fBrightness = 0.85f;
		break;
	case 2:
		fBrightness = 1.15f;
		break;
	}

	glColor4f(fBrightness * GetRValue(cr)/255.0f, fBrightness * GetGValue(cr)/255.0f, fBrightness * GetBValue(cr)/255.0f, fAlpha);
}


#ifdef _DEBUG
inline bool wgl_ErrorCheck()
{
	GLenum errCode;
	if((errCode = glGetError()) != GL_NO_ERROR)
	{
		AfxMessageBox((TCHAR*)gluErrorString(errCode));
		ASSERT(0);
		return false;
	}
	return true;
}
#else
	inline bool wgl_ErrorCheck() {return glGetError() == GL_NO_ERROR; }
#endif

#endif
//////////////////////////////////////////////////////////////////////