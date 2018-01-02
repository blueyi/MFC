// OpenGLView.cpp : implementation file
//

#include "stdafx.h"
#include "DynViews.h"
#include "OpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CMyView)

COpenGLView::COpenGLView()
{
}

COpenGLView::~COpenGLView()
{
}


BEGIN_MESSAGE_MAP(COpenGLView, CMyView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glLoadIdentity();

	glRotated(m_rotation[0], 1.0, 0.0, 0.0);
	glRotated(m_rotation[1], 0.0, 1.0, 0.0);
	glRotated(m_rotation[2], 0.0, 0.0, 1.0);

	glPushMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
	gluCylinder(m_quadric, 1.0, 1.0, 1.0, 16, 16);
	gluDisk(m_quadric, 0.0, 1.0, 16, 1);
	glTranslated(0.0, 0.0, 1.0);
	gluDisk(m_quadric, 0.0, 1.0, 16, 1);

	glPopMatrix();
	
	SwapBuffers(m_pDC->GetSafeHdc());
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CMyView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CMyView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMyView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitGL();
	
	return 0;
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	
	return CMyView::PreCreateWindow(cs);
}

void COpenGLView::InitGL()
{
	m_pDC = new CClientDC(this);
	
	SetupPixelFormat();

	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);
	
	GLfloat color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPos[4] = {3.0f, 3.0f, 3.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	m_quadric = gluNewQuadric();

	for(int i=0; i<3; i++) {
		m_rotation[i] = (((double) rand() / (double) RAND_MAX) * 2.0) - 1.0;
	}

	SetTimer(m_idView, 10, NULL);
}

void COpenGLView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0,
	};

	int pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);
}

BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}


void COpenGLView::OnDestroy() 
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	if(m_pDC) delete m_pDC;

	gluDeleteQuadric(m_quadric);

	CMyView::OnDestroy();
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CMyView::OnSize(nType, cx, cy);
	
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double) cx / (double) cy, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void COpenGLView::OnTimer(UINT nIDEvent) 
{
	Invalidate();
	
	CMyView::OnTimer(nIDEvent);
}
