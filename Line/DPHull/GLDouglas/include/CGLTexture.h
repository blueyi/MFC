


#ifndef _CGLTEXTURE_H_
#define _CGLTEXTURE_H_

#include "cglimage.h"

/*! \brief A texture wrapper for OpenGL

\ingroup OGLToolsGroup
CGLTexture is a simple wrapper to OpenGL texture object.
It enables easy changing of texture images, 
reusing existing texture object when possible.
Call ChangeImage(&CGLImage) to create/recreate/reuse
a texture and copy CGLImage image to the texture object.
Use Bind() to bind a texture. 
Use Invalidate() before switching to a new RC.
If Invalidate() is called and then Bind() is called in a new RC,
the texture will be automaticaly recreated using a backup copy
of the image. If you are not going to use the same texture 
in multiple RC's, call ChangeImage() with second parameter 
set to 'false' so it won't make unnecessary 
backup copy of the image.

\code
	if(bChangeImage)
	{
      // Handle a request to use a different image 
      // for texture.

	bChangeImage = false;
	CGLImage glImage;
	glImage.Create(m_strNewImageFilePath, GL_RGBA);
	m_tex1.ChangeImage(&glImage, false); 
	}

	m_tex1.Bind();  
\endcode

Use Coordn() function to generate texture coordinates 
which point to the four corners of current subimage
inside a possibly larger texture.

\code
	glBegin(GL_QUADS);
		m_tex1.Coord0(); glVertex3f(-5.0, -5.0, 0.0);
		m_tex1.Coord1(); glVertex3f(-5.0, 5.0, 0.0);
		m_tex1.Coord2(); glVertex3f(5.0, 5.0, 0.0);
		m_tex1.Coord3(); glVertex3f(5.0, -5.0, 0.0);
	glEnd();

	glFlush();
	glDisable(GL_TEXTURE_2D);
\endcode
\sa CGLImage
\sa CWGL
\author (c) W.Weyna, http://shiptech.tuniv.szczecin.pl/~weyna/OpenGL/
*/
class CGLTexture
{
public:
	//! Default constructor
	CGLTexture(); 
	//! Destroy textures (see glDeleteTextures)
	~CGLTexture();

// Attributes
public:
	/*! \name Attributes: */
	//@{
	//! returns identifier of texture
	UINT GetTexName() {ASSERT(m_bTextureObjectValid); return m_nTexName; }
	//! returns width (in pixels)	
	int	GetWidth() {ASSERT(m_bTextureObjectValid); return m_nTexWidth; }
	//! returns height (in pixels)
	int GetHeight() {ASSERT(m_bTextureObjectValid); return m_nTexHeight; }
	//! returns width (in pixels) of base image	
	int	GetImageWidth()	{ASSERT(m_bTextureObjectValid); return m_nImageWidth; }
	//! returns height (in pixels) of base image	
	int	GetImageHeight()	{ASSERT(m_bTextureObjectValid); return m_nImageHeight; }
	
	//! TRUE if texture is valid
	bool IsValid() {return m_bTextureObjectValid; }
	//! TRUE if texture is reused
	bool IsReused() {return m_bSubImage; }

	//! returns length in X direction (in texture coordinates)
	GLfloat GetCoordX() {return m_fCoordX; }
	//! returns length in Y direction (in texture coordinates)
	GLfloat GetCoordY() {return m_fCoordY; }
	//@}

protected:
	UINT	m_nTexName;
	
	int		m_nTexWidth;
	int		m_nTexHeight;

	int		m_nImageWidth;
	int		m_nImageHeight;

	bool	m_bTextureObjectValid;
	bool	m_bReadyToSubimage;
	bool	m_bSubImage;

	GLfloat m_fCoordX;
	GLfloat m_fCoordY;

	CGLImage m_texSurface;      // temp surface, needed for texture object creation only
	CGLImage m_backupTexImage;  // optional backup copy of image, used to restore texture if it is invalid.
	
	bool m_bBackupCopyValid;

// Operations
public:
	/*! \name Operations: */
	//@{
	/*! \brief Change texture to pImage
	
	Use this function to supply a source image for a texture.
	See inside of the code for details.

	If bCopyImage is true (default),
	a backup copy of the image is created and if later
	CGLTexture::Invalidate() is called and then CGLTexture::Bind()
	the texture will be automaticaly recreated using a backup copy
	of the image. This is usefull for recreating the same textures 
	when you switch to a new RC. If you don't intend to do this,
	set this parameter to false to avoid alocating extra memory.
	*/
	bool ChangeImage(CGLImage* pImage, bool bCopyImage = true);
	/*! \brief Create an OpenGL texture object.
	
	The image for the texture is copied by OpenGL
	from m_texSurface CGLImage object. 
	If m_texSurface wasn't created
	prior to the call to CreateTextureObject() or
	the size of previously created m_texSurface differs, 
	CreateTextureObject() will create an empty, black, 
	texture object.
	After a call to CreateTextureObject() the m_texSurface
	surface is lost.
	*/
	bool CreateTextureObject(int nWidth, int nHeight, GLenum pixelFormat = GL_RGBA);
	/*! \brief Bind texture.
	
	  Bind OpenGL texture object.
	If texture object is invalid, recreate it
	and initialize with a backup copy of the image,
	if one is available.
	*/
	bool Bind();
	//! Invalidate this CGLTexture object and delete the attached OpenGL texture object.
	void Invalidate();

	//! Sets (0,0) tex coordinate.
	void Coord0() {glTexCoord2f(0.0, 0.0); }
	//! Sets (0,m_fCoordY) tex coordinate.
	void Coord1() {glTexCoord2f(0.0, m_fCoordY); }
	//! Sets (m_fCoordX,m_fCoordY) tex coordinate.
	void Coord2() {glTexCoord2f(m_fCoordX, m_fCoordY); }
	//! Sets (m_fCoordX,0) tex coordinate.
	void Coord3() {glTexCoord2f(m_fCoordX, 0.0); }
	//@}
	
// Helpers
private:
	/*! \name Helpers: */
	//@{
	DWORD AlignToPow2(DWORD dwValue);
	//@}
};

#endif

/////////////////////////////////////////////////////////////////////////////////