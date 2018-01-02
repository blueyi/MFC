
#include "gl/gl.h"
#include "CRGBSurface.h"

#ifndef _CGLIMAGE_H_
#define _CGLIMAGE_H_

typedef GLvoid* GL_PTR_TO_VOID;
typedef BYTE*	PTR_TO_BYTE;

/*! \brief An rendering context for GL.

\ingroup OGLToolsGroup
 CGLImage class adds red and blue component swaping 
 to some CRGBSurface::Create() methods.

 A GDI DIB section object created by CGLImage,
 may be used directly as a source image 
 for OpenGL texture object, as OpenGL or GDI rendering surface,
 or for a direct bit manipulations.
  

Examples:
\code
	CGLImage glImage;
	glImage.Create(10, 10, GL_RGBA);  // create empty, black image
	glImage.Create(&CBitmapObject);	  // create from DDB bitmap GDI object
	glImage.Create("D:/TestImg/testimg.bmp", GL_RGBA); // create from file DIB 
	glImage.Render(0, 100);   // render image                               
	GLvoid* ptr = glImage.GetPixels();  // get save pointer for direct bit manipulation
	glTexImage2D(...., glImage); // use GL_PTR_TO_VOID() conversion operator to get save pointer
\endcode
\sa CRGBSurface
\sa CWGL
\author (c) W.Weyna 'Voytec', http://shiptech.tuniv.szczecin.pl/~weyna/OpenGL/
*/
class CGLImage : public CRGBSurface
{
// Attributes
public:
	/*! \name Attributes: */
	//@{
	/*! \brief Get Frame Pixels

	Flushes OpenGL calls and returns a pointer to the frame buffer.
	\la CRGB::GetPixels
	*/
	GLvoid* GetPixels() {glFlush(); return (GLvoid*)CRGBSurface::GetPixels();}
	/*! \brief Pixel format
	
	Returns pixel format :
	<ul>
	<li> GL_RGB 24 bits.
	<li> GL_RGBA 32 bits
	</ul>
	It produces an assert otherwize.
	
	\sa GetImagePixelFormatName
	\sa CWGL::SetPixelFormat
	*/
	int GetImagePixelFormat();
	/*! \brief Pixel format
	
	Returns pixel format :
	<ul>
	<li> "GL_RGB" 24 bits.
	<li> "GL_RGBA" 32 bits
	</ul>
	It produces an assert otherwize.
	\sa GetImagePixelFormatName
	\sa CWGL::SetPixelFormat
	*/
	const char* GetImagePixelFormatName();
	//@}
// Convertions
public:
	/*! \name Conversions: */
	//@{
	//! returns GetPixels()
	operator GL_PTR_TO_VOID() {return GetPixels(); }
	//! returns (BYTE*)GetPixels()
	operator PTR_TO_BYTE() {return (BYTE*)GetPixels(); }
	//@}

// Operations
public:  
	/*! \name Operations:
	*/
	//@{
	//! Create DIB using CRGBSurface::Create(CRGBSurface* const)
	bool Create(CRGBSurface* const pSourceSurface)
		{return CRGBSurface::Create(pSourceSurface); }  // must be explisitly declared because of ambiguity with Create(const HBITMAP hBitmap ...
	/*! \brief  Create cx x cy DIB

	\param cx width of DIB
	\param cy height of DIB
	\param nBitsPerPixel nb of pits per pixels (default is 24). RGBA image need 32.
	\sa CRGBSurface::Create(int, int, int)
	*/
	bool Create(int cx, int cy, int nBitsPerPixel = 24)
		{return CRGBSurface::Create(cx, cy, GLPFtoBPP(nBitsPerPixel));}

	//! Create DIB using CRGBSurface::Create(HBITMAP,int,CDC*) then swap Red and Blue.
	bool Create(const HBITMAP hBitmap, int nBitsPerPixel = 24, CDC* pDC = NULL)
		{bool bRetVal = CRGBSurface::Create(hBitmap, GLPFtoBPP(nBitsPerPixel), pDC); SwapRB(); return bRetVal;}
	//! Create DIB using CRGBSurface::Create(CBitmap*,int,CDC*) then swap Red and Blue.
	bool Create(CBitmap* pBitmap, int nBitsPerPixel = 24, CDC* pDC = NULL) 
		{bool bRetVal = CRGBSurface::Create(pBitmap, GLPFtoBPP(nBitsPerPixel), pDC); SwapRB(); return bRetVal;}	
	//! Create DIB using CRGBSurface::Create(const CBitmap&,int,CDC*) then swap Red and Blue.
	bool Create(const CBitmap& bitmap, int nBitsPerPixel = 24, CDC* pDC = NULL)
		{bool bRetVal = CRGBSurface::Create(bitmap, GLPFtoBPP(nBitsPerPixel), pDC); SwapRB(); return bRetVal;}
	//! Create DIB using CRGBSurface::Create(const char*,int) then swap Red and Blue.	
	bool Create(const CString& strPath, int nBitsPerPixel = 24)
		{bool bRetVal = CRGBSurface::Create(strPath, GLPFtoBPP(nBitsPerPixel)); SwapRB(); return bRetVal;}

	//! Wraper to glDrawPixels().
	void Render(int x, int y, int z = 0);

	//! Sets the pixel storage mode to GL_UNPACK_ALIGNMENT.
	void PixelStore() { glPixelStorei(GL_UNPACK_ALIGNMENT, 4); }

	/*! \brief Swap red and blue bytes in all pixels of DIB section.
	*/
	void SwapRB();
	/*! \brief Convert pixel mode from RGB to RGBA
	
	Convert from OpenGL pixel format name GL_RGB or GL_RGBA
	to a number of bits per pixel.
	If bits per pixel are passed instead of pixel format name,
	check if this number is valid for OpenGL image (24 bits or 32 bits)
	 and return valid value;
	*/
	int GLPFtoBPP(const int nGLPForBPP);
	//@}
public:
	/*! \name Multi-Threading
	*/
	//@{
	//! Locks the object on this thread
	BOOL Lock();
	//! Unlocks the object on this thread
	BOOL Unlock();
	//! returns TRUE if locked
	BOOL IsLocked() const;
	//@}
protected:
	CMutex* m_pThreadSynchro;
	CSingleLock* m_pLock;
};

#endif

////////////////////////////////////////////////////////////