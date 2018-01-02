// TestWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLTest.h"
#include "TestWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Vertices DataSets (convex polygons to tessellate)
// NOTE: the polygons will be automatically closed
		GLdouble star[5][3]={ 
		{0.2, 0.0, 0.0},
		{0.5, 0.9, 0.0},
		{0.8, 0.0, 0.0},
		{0.0, 0.6, 0.0},
		{1.0, 0.6, 0.0},
		};
		GLdouble Quad[4][3]={ 
		{0.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{1.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		};
		GLdouble Triang[3][3]={ 
		{0.3, 0.3, 0.0},
		{0.7, 0.3, 0.0},
		{0.5, 0.7, 0.0},
		};
		GLdouble Triang2[3][3]={ 
		{0.5, 0.5, 0.0},
		{1.5, 1.0, 0.0},
		{1.5, 0.5, 0.0},
		};


/////////////////////////////////////////////////////////////////////////////
// CTestWnd

CTestWnd::CTestWnd() :
	X_Angle(0.0), Y_Angle(0.0),
	TessWindRule(GLU_TESS_WINDING_ODD), TessFilling(TRUE),
	sceneselect(0),	quadricNormals(GLU_NONE),
	quadricDwStyle(GLU_LINE), quadricOrientation(GLU_OUTSIDE)
{
}

CTestWnd::~CTestWnd()
{
}


BEGIN_MESSAGE_MAP(CTestWnd, COpenGLWnd)
	//{{AFX_MSG_MAP(CTestWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTestWnd message handlers
void CTestWnd::OnCreateGL()
{
// perform hidden line/surface removal (enable Z-Buffering)
	glEnable(GL_DEPTH_TEST);
// set background color to black
	glClearColor(0.f,0.f,0.f,1.0f );
// set clear Z-Buffer value
	glClearDepth(1.0f);
// create and enable a white directional light
	float  color[]={1.f,1.f,1.f,1.f};// RGBA color spec
	glLightfv(GL_LIGHT0,GL_DIFFUSE,color);
	float  ambient[]={.3f,.3f,.3f,1.f};// RGBA color spec
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	float pos[]={1.f,1.f,1.f,0.f};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glEnable(GL_LIGHT0);
// prepare a bunch of line segments (carthesian axes arrows)
	StartStockDListDef();
	glBegin(GL_LINES);
		// yellow x axis arrow
		glColor3f(1.f,1.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,0.1f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,-0.1f,0.0f);
		// cyan y axis arrow
		glColor3f(0.f,1.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.1f,0.9f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.1f,0.9f,0.0f);
		// magenta z axis arrow
		glColor3f(1.f,0.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.1f,0.9f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,-0.1f,0.9f);
	glEnd();
	EndStockListDef();
// prepare a single display list (yet another cube)
	anothercube.StartDef();// <- do not execute list immediately
		glBegin(GL_QUADS);
			glColor3f(0.4f,.2f,.7f);
			glVertex3f(0.1f,0.1f,.1f);
			glVertex3f(0.6f,.1f,.1f);
			glVertex3f(0.6f,0.6f,.1f);
			glVertex3f(0.1f,0.6f,.1f);
			glColor3f(.8f,1.f,.2f);
			glVertex3f(0.1f,0.1f,.6f);
			glVertex3f(0.6f,.1f,.6f);
			glVertex3f(0.6f,0.6f,.6f);
			glVertex3f(0.1f,0.6f,.6f);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(0.4f,.2f,.7f);
			glVertex3f(0.1f,0.1f,.1f);
			glVertex3f(0.1f,0.1f,.6f);
			glColor3f(.8f,1.f,.2f);
			glVertex3f(0.6f,.1f,.1f);
			glVertex3f(0.6f,.1f,.6f);
			glColor3f(0.4f,.2f,.7f);
			glVertex3f(0.6f,0.6f,.1f);
			glVertex3f(0.6f,0.6f,.6f);
			glColor3f(.8f,1.f,.2f);
			glVertex3f(0.1f,0.6f,.1f);
			glVertex3f(0.1f,0.6f,.6f);
			glColor3f(0.4f,.2f,.7f);
			glVertex3f(0.1f,0.1f,.1f);
			glVertex3f(0.1f,0.1f,.6f);
		glEnd();
		anothercube.EndDef();
// prepare tesselator demo objects
		BuildTessDispList();
// prepare quadric disp list
		BuildQuadrDispList();	
}

void CTestWnd::OnDrawGL()
{
// the couple glPush - glPop is necessary because the entire
// scene is rotated of the given angle (which is absolute) at every redraw
	glPushMatrix();
// rotate the objects of the given angle
	glRotated(X_Angle,1.0,0.0,0.0);
	glRotated(Y_Angle,0.0,1.0,0.0);
// this should be self explanatory
	DrawStockDispLists();


		glBegin(GL_QUAD_STRIP);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, 0.3f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.3f, -0.3f, 0.3f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, 0.3f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.3f, -0.3f, 0.3f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, -0.3f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.3f, -0.3f, -0.3f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, -0.3f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.3f, -0.3f,  -0.3f);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, 0.3f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.3f, -0.3f, 0.3f);
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, 0.3f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, 0.3f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, -0.3f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, -0.3f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.3f, -0.3f, 0.3f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.3f, -0.3f, 0.3f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.3f, -0.3f, -0.3f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(-0.3f, -0.3f, -0.3f);
		glEnd();

		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, 1.3f, 1.3f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.3f, 1.3f, 1.3f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(1.3f, 1.3f, 1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, 1.3f, 2.0f);
		glEnd();

// execute previously prepared displ. list 2 times
// Note:All translations are relative (imagine to deal with a "3D cursor")
		glTranslatef(-1.35f,-0.2f,-0.2f);
		anothercube.Draw();
		glTranslatef(2.f,0.f,0.f);
		anothercube.Draw();


	glPopMatrix();	
}

void CTestWnd::BuildQuadrDispList()
{
	const int SECTIONS=16;
	const double RADIUS=.5;
// construct a quadric object
	CGLQuadric q(quadricDwStyle,quadricNormals,quadricOrientation);
// open disp list definition
	quadric.StartDef();
// draw an azure sphere
	glColor3f(.2f,.5f,.8f);
	q.DrawSphere(RADIUS,SECTIONS,SECTIONS);
	glTranslatef(1.2f, 0.0f, 0.0f);
// draw a maroon cylinder
	glColor3f(.8f,.5f,.2f);
	q.DrawCylinder(RADIUS,RADIUS,1.0,SECTIONS,2);
	glTranslatef(-2.4f, 0.0f, 0.0f);
// draw a green disk
	glColor3f(.5f,.8f,.2f);
	q.DrawDisk(RADIUS-.3,RADIUS,SECTIONS,2);
// close disp list definition
	quadric.EndDef();
	
}

void CTestWnd::BuildTessDispList()
{
// create a display list for the convex polygons
		CGLTesselator t;
		tessPolygon.StartDef();
// set winding rule and filling
		t.SetWindingRule(TessWindRule);
		t.SetFilling(TessFilling);
// first polygon: a quadrilateral with a triangular hole
		t.StartDef();
// define exterior
		t.AddVertexArray(Quad,4);
// define hole
		t.ContourSeparator();
		t.AddVertexArray(Triang,3);
		t.EndDef();
// move "the 3d cursor" right
		glTranslatef(1.f,0.f,0.f);
// second polygon: a star (defined vertex per vertex)
		t.StartDef();
		for (int c=0;c<5;c++)
		{
			t.AddVertex(star[c]);
		};
		t.EndDef();
// move "the 3d cursor" right again
		glTranslatef(1.f,0.f,0.f);
// third polygon: a quadrilateral and an intersecting triangle
// NOTE: the intersecting triangle has vertices in CCW order
//       this has effect on positive and negative winding rule
		t.StartDef();
		t.AddVertexArray(Quad,4);
		t.ContourSeparator();
		t.AddVertexArray(Triang2,3);
		t.EndDef();
// close disp list definition
		tessPolygon.EndDef();
	
}


void CTestWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// remember where we clicked
	MouseDownPoint=point;
// capture mouse movements even outside window borders
	SetCapture();
	
//	COpenGLWnd::OnLButtonDown(nFlags, point);
}

void CTestWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// forget where we clicked
	MouseDownPoint=CPoint(0,0);
// release mouse capture
	ReleaseCapture();	

//	COpenGLWnd::OnLButtonUp(nFlags, point);
}

void CTestWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// check if we have captured the mouse
	if (GetCapture()==this)
	{
// increment the object rotation angles
		X_Angle+=double(point.y-MouseDownPoint.y)/3.6;
		Y_Angle+=double(point.x-MouseDownPoint.x)/3.6;
// redraw the view
		Invalidate(TRUE);
// remember the mouse point
		MouseDownPoint=point;
	};
	
//	COpenGLWnd::OnMouseMove(nFlags, point);
}
