/*! \page Plot Graphic Library, a C++/MFC charting library.

\par Copyright (C) 2001  de Halleux Jonathan

\par License

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

\author de Halleux Jonathan, pglinfo@patabelgos.org
*/


#ifndef PGLDLL_H
	#define PGLDLL_H

#ifndef PGL_EXT_CLASS
	#ifdef _PGL_DLL
		#define PGL_EXT_CLASS _declspec(dllexport)
	#else
		#define PGL_EXT_CLASS _declspec(dllimport)
	#endif
#endif

#ifndef PGL_TRACE
	#ifdef _DEBUG
		#define PGL_TRACE(a) TRACE(a)
	#else 
		#ifdef _PGL_TRACE_LOG
			PGL_EXT_CLASS extern CStdioFile logerror;
			#define PGL_TRACE(a) logerror.WriteString(a)
		#else
			#define PGL_TRACE(a) 
		#endif
	#endif
#endif


#ifndef _PGL_DLL
#ifndef _PGL_DLL_LOADED
#define _PGL_DLL_LOADED
	#ifdef _MFC_7
		#ifdef _DEBUG
			#ifdef _UNICODE
				#pragma message("     _Adding library: PGL7ud.lib: MFC7.0, Debug, UNICODE" ) 
				#pragma comment(lib, "PGL7ud.lib")
			#else
				#pragma message("     _Adding library: PGL7d.lib: MFC7.0, Debug, MBCS" ) 
				#pragma comment(lib, "PGL7d.lib")
			#endif
		#else
			#ifdef _UNICODE
				#pragma message("     _Adding library: PGL7u.lib: MFC7.0, Release, UNICODE" ) 
				#pragma comment(lib, "PGL7u.lib")
			#else
				#pragma message("     _Adding library: PGL7u.lib: MFC7.0, Release, UNICODE" ) 
				#pragma comment(lib, "PGL7.lib")
			#endif
		#endif
	#else
		#ifdef _DEBUG
			#ifdef _UNICODE
				#pragma message("     _Adding library: PGLud.lib: MFC4.2, Debug, UNICODE" ) 
				#pragma comment(lib, "PGLud.lib")
			#else
				#pragma message("     _Adding library: PGLd.lib: MFC4.2, Debug, MBCS" ) 
				#pragma comment(lib, "PGLd.lib")
			#endif
		#else
			#ifdef _UNICODE
				#pragma message("     _Adding library: PGLu.lib: MFC4.2, Release, UNICODE" ) 
				#pragma comment(lib, "PGLu.lib")
			#else
				#pragma message("     _Adding library: PGLu.lib: MFC4.2, Release, UNICODE" ) 
				#pragma comment(lib, "PGL.lib")
			#endif
		#endif
	#endif
#endif
#endif


#include <afxtempl.h>
#include <afxdlgs.h>

///////////////////////////////////////////////////////////////////////////////////////
// min max handling
#ifdef max
	#undef max
#endif
#ifdef min
	#undef min
#endif

namespace pgl 
{ 
  template <typename T> 
  inline const T& min(const T& a, const T& b) 
  { return b < a ? b : a; } 

  template <typename T> 
  inline const T& max(const T& a, const T& b) 
  { return  a < b ? b : a; } 
} 
// using min, max
using pgl::min;
using pgl::max;

#include "AlgoTools.h"
#include "GfxInterface.h"
#include "FileGfxInterface.h"
#include "GDIpInterface.h"
#include "EPSInterface.h"
#include "SVGInterface.h"

#include <stdlib.h>
#include <math.h>
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

// the rest
#include "PGLGlobal.h"
#include "PGLDef.h"
#include "PGLResource.h"
#include "PGLFont.h"
#include "PGLColor.h"
#include "PGLObject.h"
#include "PGLPie.h"
#include "PGLRegion.h"
#include "PGLObjectManager.h"
#include "PGLAxe.h"
#include "PGLLine.h"
#include "PGLLineVer.h"
#include "PGLLineHor.h"
#include "PGLLine2D.h"
#include "PGLLine2DLOD.h"
#include "PGLMap.h"
#include "PGLMapZ.h"
#include "PGLMapVector.h"
#include "PGLText.h"
#include "PGLGraph.h"
#include "PGLUtility.h"

#include "PGLAllPropsDlg.h"
#include "PGLObjectPropPage.h"
#include "PGLAxe2DPropPage.h"
#include "PGLLinePropPage.h"
#include "PGLLine2DPropPage.h"
#include "PGLMapPropPage.h"
#include "PGLMapZPropPage.h"
#include "PGLMapVectorPropPage.h"
#include "PGLGraphBitDlg.h"
#include "PGLGraphDlgList.h"
#include "PGLGraphView.h"

#endif
