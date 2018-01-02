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
///////////////////////////////////////
// Constant definitions

//define group

/*!
	\defgroup PGLGroup PGL Library : Plot Graphic Library for MFC
*/

/*! 
\defgroup ConstantGroup Constants
\ingroup PGLGroup 
*/
//@{
//! line interpolation type : piecewize interpolation
#define PGL_INTERPOLATION_STEP 0
//! line interpolation type : piecewize interpolation
#define PGL_INTERPOLATION_LINEAR 1
//! line segments
#define PGL_INTERPOLATION_SEGMENT 2

//! point type: no point
#define PGL_POINT_NONE			10
//! point type: simple circle
#define PGL_POINT_SIMPLE		11
//! a simple empty circle
#define PGL_POINT_CONTOUR		12
//! a triangle (equilateral)
#define PGL_POINT_TRIANGLE		13
//! a square
#define PGL_POINT_SQUARE		14

//! line type: no line
#define PGL_LINE_NONE			20
//! line type: continuous line
#define PGL_LINE_CONT			21
//! line type: - - - pattern
#define PGL_LINE_BARBAR			22
//! line type: _._._ pattern
#define PGL_LINE_BARPOINT		23
//! line type: _._._ pattern
#define PGL_LINE_POINTPOINT		24

//! surface type : no surface
#define PGL_SURFACE_NONE		20
//! surface type : flat shading
#define PGL_SURFACE_FLAT		21
//! surface type : smooth shading (gouraud)
#define PGL_SURFACE_GOURAUD		22

//! selection buffer size step
#define PGL_SELECTION_BUFFER_STEP 50

//! mouse mode: selection mode
#define PGL_MODE_TOOLS_SELECTION 30
//! mouse mode: adding line
#define PGL_MODE_TOOLS_ADD_LINE2D 31
//! mouse mode: adding surface2D
#define PGL_MODE_TOOLS_ADD_SURFACE2D 32
//! mouse mode: adding text with mouse
#define PGL_MODE_TOOLS_ADD_TEXT 33
//! mouse mode: view panning mode
#define PGL_MODE_VIEW_PAN 34
//! mouse mode: view zooming mode
#define PGL_MODE_VIEW_ZOOM 35

//! left aligned text
#define PGL_TEXT_ALIGN_LEFT 40
//! centered text
#define PGL_TEXT_ALIGN_CENTER 41
//! right aligned text
#define PGL_TEXT_ALIGN_RIGHT 42


//! desired number of line in grid
#define PGL_AXE_NSTEPS 5

//! Maximum number of characters
#define PGL_FONT_MAXCHAR 255

//! frustum utility
#define PGL_FAR_AWAY 1000.0
//! famous number pi
#define PGL_PI 3.141592653589
//! machine precision
#define PGL_EPS 1e-10
//@}
