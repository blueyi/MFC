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
	#ifdef _DEBUG
		//#pragma message("     _Adding library: PGLd.lib (Debug version)" ) 
		//#pragma comment(lib, "PGLd.lib")
	#else
		//#pragma message("     _Adding library: PGL.lib (Release version)" ) 
		#pragma comment(lib, "PGL.lib")
	#endif
#endif


#include <afxtempl.h>
#include <afxdlgs.h>

#include "GfxInterface.h"
#include "FileGfxInterface.h"
#include "GDIpInterface.h"
#include "EPSInterface.h"
#include "SVGInterface.h"

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>



#undef max
#undef min

#include "AlgoTools.h"

// the rest
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
