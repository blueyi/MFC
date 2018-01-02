#ifndef OGLT_H
	#define OGLT_H

#ifndef _OGLTOOLS_LIB 
	#pragma message("     _Adding library: Jpegmt.lib, OpenGL32.lib, glu32.lib" ) 
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "glu32.lib")
	#pragma comment(lib, "Jpegmt.lib")
	#ifdef _DEBUG
		#pragma message("     _Adding library: OGLToolsd.lib (Debug version)" ) 
		#pragma comment(lib, "OGLToolsd.lib")
	#else
		#pragma message("     _Adding library: OGLTools.lib(Release version)" ) 
		#pragma comment(lib, "OGLTools.lib")
	#endif
#endif

	#include <afxmt.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "CWGL.h"
	#include "CGLImage.h"
	#include "CGLTexture.h"
	#include "CRGBSurface.h"
#endif
