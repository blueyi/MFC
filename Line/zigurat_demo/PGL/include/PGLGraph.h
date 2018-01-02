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
// GraphGL.h: interface for the CPGLGraph class.
//
//////////////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_PGLGRAPH_H__CF898C3B_8166_11D4_8267_00A024D26A1F__INCLUDED_)
#define AFX_PGLGRAPH_H__CF898C3B_8166_11D4_8267_00A024D26A1F__INCLUDED_

#include "PGLColor.h"	// Added by ClassView
#include "PGLRegion.h"
#include "PGLObjectManager.h"
#include "PGLLine2D.h"
#include "PGLLine2DPropPage.h"
#include "PGLAxe.h"
#include "PGLView2D.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*! \brief  A graph class.

\ingroup PGLRegionGroup
This class acts like a containers for all the graphical 
you want to put in your graph:
lines, surface, texts, ect. But you can also include graphs in graphs.

Here are 2 examples on creating a graph :
<ul>
<li> Example 1: Creating a graph in a \b modal dialog box (using CPGLGraphDCDlg)
\code
// Allocating memory for new graph
CPGLGraph pGraph=new CPGLGraph();

CPGLLine2D* pLine2D	// creating line

int n=N_POINTS; // number of points.

// allocating memory for data. It MUST BE dynamic allocating
// since PGL will free these arrays when destroying dialog 
double* x=new double[n];
double* y=new double[n];	

// computing sinus
for (int i = 0;i<n;i++) 
{
    x[i]=i/(double)n*3.14;
    y[i]=sinus(x[i]);
}

// Allocating memory for line. It MUST BE dynamic allocating.
pLine2D=new CPGLLine2D();
pLine2D->SetDatas(n,x,y);

// adding line to graph
pGraph->AddObject(pLine2D0); 

// let's build a dialog box and show it.
CPGLGraphDCDlg graphDlg(pGraph);
// showing dialog
graphDlg.DoModal();

// cleaning the graph object.
// The cleaning of the pLine2D's, x, y, etc. is done automatically.
delete pGraph;
\endcode

<li>Example 2: Creating a graph (without dialog box) and creating a EPS

\code
    // file is a opened file (text mode)
	CStdio file;

	// Create DIB
	CGLImage image;
	image.Create(640,480);
	// Create graph
	CPGLGraph graph(image.GetDC());
	// Create GL context
	CWGL wgl;
	// Start GL
	wgl.Begin(image.GetDC());

	// Generate line
	CPGLLine2D* pLine2D	// line pointer
	int n=N_POINTS; // number of points.

	// allocating memory for data. It MUST BE dynamic allocating
	// since PGL will free these arrays when destroying dialog 
	double* x=new double[n];
	double* y=new double[n];	
	// computing sinus
	for (int i = 0;i<n;i++) 
	{
	    x[i]=i/(double)n*3.14;
	    y[i]=sinus(x[i]);
	}
	// Allocating memory for line. It MUST BE dynamic allocating.
	pLine2D=new CPGLLine2D();
	pLine2D->SetDatas(n,x,y);
	// Adding to graph
	graph.AddObject(pLine2D);

	// Setting viewport and preparing view.
	graph.SetViewport(0,0,640,480);
	graph.ZoomAll();

	// Exporting to EPS
	graph.PlotToEPS(&file);

	// Cleaning graph
	graph.Delete();

	// ending GL
	wgl.End();
\endcode
</ul>

\sa CPGLGraphBitDlg
\sa CPGLGraphDCDlg
\sa CPGLGraphDlgList
*/
class PGL_EXT_CLASS CPGLGraph : public CPGLRegion
{
public:
	DECLARE_SERIAL(CPGLGraph);
	/*! \name Class Members*/
	//@{
	//!  constructor
	CPGLGraph();
	//!  copy constructor
	CPGLGraph(const CPGLGraph& g);
	//!  assignement constructor
	CPGLGraph& operator =(const CPGLGraph& g);
	//!  returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLGraph(*this); return pCopy; };
	//!  destructor
	virtual ~CPGLGraph();

	//!  adds context menu items...
	virtual void AddContextMenuItems(CMenu* pMenu);
	//!  show context menu...
	void ShowContextMenu();

	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	//! not implemented yet
	void FormatSelectedText();

	//!  Serialize functions
	void Serialize(CArchive& archive);

	//!  Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;    // Override
	#endif
	//@}
protected:
	/*! \name Class Parameters*/
	//@{
	//@}
};

#endif // !defined(AFX_GRAPHGL_H__CF898C3B_8166_11D4_8267_00A024D26A1F__INCLUDED_)

