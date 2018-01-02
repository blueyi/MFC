// GraphGLDlg.cpp : implementation pFile
//

#include "stdafx.h"
#include "PGL/PGLGraphDCDlg.h"
#include "PGL/PGLAllPropsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphDCDlg dialog

CPGLGraphDCDlg::CPGLGraphDCDlg(CWnd* pParent,CPGLGraph* _pGraph /*=NULL*/)
: CPGLGraphDlg(pParent,_pGraph)
{
	//{{AFX_DATA_INIT(CPGLGraphDCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPGLGraphDCDlg::DoDataExchange(CDataExchange* pDX)
{
	CPGLGraphDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLGraphDCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLGraphDCDlg, CDialog)
	//{{AFX_MSG_MAP(CPGLGraphDCDlg)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PGL_FIGURE_OPEN, OnFigureOpen)
	ON_COMMAND(ID_PGL_FIGURE_SAVEAS, OnFigureSaveas)
	ON_COMMAND(ID_PGL_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_PGL_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_PGL_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_PGL_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_PGL_SELECTION_ORDER_MOVEDOWN, OnSelectionOrderMovedown)
	ON_COMMAND(ID_PGL_SELECTION_ORDER_MOVEUP, OnSelectionOrderMoveup)
	ON_COMMAND(ID_PGL_SELECTION_ORDER_TOBACK, OnSelectionOrderToback)
	ON_COMMAND(ID_PGL_SELECTION_ORDER_TOFRONT, OnSelectionOrderTofront)
	ON_COMMAND(ID_PGL_SELECTION_SELECTALL, OnSelectionSelectall)
	ON_COMMAND(ID_PGL_SELECTION_UNHIDEALL, OnSelectionUnhideall)
	ON_COMMAND(ID_PGL_SELECTION_UNSELECT, OnSelectionUnselect)
	ON_COMMAND(ID_PGL_TOOLS_ADDTEXT, OnToolsAddtext)
	ON_COMMAND(ID_PGL_TOOLS_SELECT, OnToolsSelect)
	ON_COMMAND(ID_PGL_VIEW_PAN, OnViewPan)
	ON_COMMAND(ID_PGL_VIEW_SELECT, OnViewSelect)
	ON_COMMAND(ID_PGL_AXE_PROPERTIES, OnAxeProperties)
	ON_COMMAND(ID_PGL_VIEW_PROPERTIES, OnViewProperties)
	ON_COMMAND(ID_PGL_VIEW_ZOOM, OnViewZoom)
	ON_COMMAND(ID_PGL_VIEW_ZOOMALL, OnViewZoomAll)
	ON_COMMAND(ID_PGL_FIGURE_EXPORTTOJPEG, OnFigureExportToJPEG)
	ON_COMMAND(ID_PGL_FIGURE_EXPORTTOEPS, OnFigureExportToVectors)
	ON_WM_CLOSE()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphDCDlg message handlers

int CPGLGraphDCDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	PGL_TRACE("PGL-GraphDCDlg: Creating dialog box\n");

	if (CPGLGraphDlg::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Allocating memory for menu...
	m_pContextMenu=new CMenu();
	if (!m_pContextMenu)
		return-1;

	return 0;
}

void CPGLGraphDCDlg::OnDestroy() 
{
	PGL_TRACE("PGL-GraphDCDlg: Destroying dialog\n");

	 CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);
	// Starting gl
	m_wgl.Begin(&dc);

	PGL_TRACE("PGL-GraphDCDlg: Cleaning OpenGL\n");

	// making rendering context current


	// cleaning graph object
	if (m_pGraph!=NULL)
	{
		PGL_TRACE("PGL-GraphDCDlg: Cleaning Graph\n");
		// cleaning graph
		m_pGraph->Delete();
	}

	// ending gl
	m_wgl.End();

	// Cleaning memory
	if (m_pContextMenu!=NULL)
	{
		m_pContextMenu->DestroyMenu();
		delete m_pContextMenu;
	}

	CPGLGraphDlg::OnDestroy();
}

BOOL CPGLGraphDCDlg::OnInitDialog() 
{
	PGL_TRACE("PGL-GraphDCDlg: Initialisating graph\n");

	CPGLGraphDlg::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// checking graph...
	ASSERT_VALID(m_pGraph);

	// Getting device context
	CClientDC dc(this);
	// assiging to graph
	m_pGraph->SetDC(&dc);

	// setting OpenGL Rendering context current
	m_wgl.Begin(&dc);

	CPGLView* pView=m_pGraph->GetView();
	ASSERT_VALID(pView);

	pView->InitGLState();
	m_pGraph->ZoomAll();
	
	m_wgl.End();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPGLGraphDCDlg::OnPaint() 
{	
	PGL_TRACE("PGL-GraphDCDlg: Painting graph\n");

	CPaintDC dc(this);	
	// getting viewport dimensions...
//	GLint vp[4];
//	m_pGraph->GetViewport(vp);
	// Init graph DC
	m_pGraph->SetDC(&dc);
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// Starting context
		m_wgl.Begin(&dc);

		// creating fonts
		m_pGraph->CompileFontsGL();

		// drawing
		RenderScene();

		// Releasing OpenGL
		m_wgl.End();

		// swapping
		SwapBuffers(dc.m_hDC);

		CDialog::OnPaint();
	}
}

void CPGLGraphDCDlg::OnSize(UINT nType, int cx, int cy) 
{
	ASSERT_VALID(m_pGraph);
	PGL_TRACE("PGL-GraphDCDlg: Resizing graph\n");

	CPGLGraphDlg::OnSize(nType, cx, cy);

	// Getting DC
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);
	m_pGraph->SetViewport(0,0,__max(1,cx), __max(1,cy));

	InvalidateRect(NULL,FALSE);
}


void CPGLGraphDCDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	ASSERT_VALID(m_pGraph);
	CPGLView* pView=m_pGraph->GetView();
	ASSERT_VALID(pView);

	// keeping information
	m_mouse.RightBtnPressed(point.x,point.y);
	// stopping mouse
	m_mouse.Stop();

	// Getting DC
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);
	m_wgl.Begin(&dc);

	//Let's try to select...
	//first translate window screen coordinate to opengl screen coordinate
	// setting the m_view...
	pView->PostReshape();
	pView->PushSelectionMatrices(point.x,point.y,4,4);

	//selection...
	GLuint objID;
	if (m_pGraph->PlotAndSelectOne(objID))
	{
		CPGLObject* pObject=m_pGraph->FindObject(objID);
		ASSERT_VALID(pObject);
		CPGLAllPropsDlg propDlg;

		// if selection is non empty and is not the pointed object is not.
		if (  (!m_pGraph->IsSelectionEmpty()) 
			&&(!pObject->IsSelected()) )
		{
			// unselect all
			m_pGraph->UnselectAll();
		}
		// select the pointed object...
		pObject->Select();
		propDlg.SetGraph(m_pGraph);
		propDlg.SetSelection(pObject);
		propDlg.DoModal();
	}
	else
	{
		m_pGraph->UnselectAll();
	}


	// restoring view
	pView->PopSelectionMatrices();

	m_wgl.End();

	CPGLGraphDlg::OnRButtonDown(nFlags, point);

	// redraw dialog
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// keeping mouse
	SetCapture();

	// keeping information
	m_mouse.LeftBtnPressed(point.x,point.y);
	
	CPGLGraphDlg::OnLButtonDown(nFlags, point);
}

void CPGLGraphDCDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ASSERT_VALID(m_pGraph);
	CPGLView* pView=m_pGraph->GetView();
	ASSERT_VALID(pView);

	int firstx,firsty;
	int lastx,lasty;

	//Releasing mouse
	ReleaseCapture();

	// Get Device context
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);
	// setting OpenGLContext current
	m_wgl.Begin(&dc);

	// checking with mode
	switch(m_iMouseMode)
	{
		case PGL_MODE_TOOLS_SELECTION: 
			if (m_mouse.IsLeftMoving())
			{
				// keeping information
				m_mouse.LeftBtnReleased(firstx,firsty);	
				// we need the corner and the dimensions of the selection box...
				GLint xc=(firstx+point.x)/2;
				GLint yc=(firsty+point.y)/2;
				GLsizei width=abs(firstx-point.x);
				GLsizei height=abs(firsty-point.y);

				width=__max(1,width);
				height=__max(1,height);
				//first translate window screen coordinate to opengl screen coordinate
				// setting the m_view...
				pView->PushSelectionMatrices(xc,yc,width,height);

				// unselecting everything...
				if ( (!(nFlags & MK_SHIFT)) && (!(nFlags & MK_CONTROL)) )
				{
					// new selection
					m_pGraph->UnselectAll();
				}

				//selection...
				GLuint* objID=NULL;
				GLuint hits;
				if (m_pGraph->PlotAndSelectBox(&objID,hits))
				{
					for (unsigned int i=0;i < hits;i++)
					{
						CPGLObject* pObject=m_pGraph->FindObject(objID[i]);
						ASSERT_VALID(pObject);
						pObject->Select();
						switch (nFlags)
						{
						case MK_SHIFT: // Add to selection...
							pObject->Select();
							break;
						case MK_CONTROL: // take out from selection
							pObject->Deselect();
							break;
						}
					}
				}
				// resetting the view
				pView->PopSelectionMatrices();
				// cleaning memory
				delete[] objID;
			}
			else
			{
				// keeping information
				m_mouse.LeftBtnReleased(firstx,firsty);	
				//first translate window screen coordinate to opengl screen coordinate
				// setting the m_view...
				pView->PushSelectionMatrices(point.x,point.y,2,2);

				// unselecting everything...
				m_pGraph->UnselectAll();
				//selection...
				GLuint objID;
				if (m_pGraph->PlotAndSelectOne(objID))
				{
					CPGLObject* pObject=m_pGraph->FindObject(objID);
					ASSERT_VALID(pObject);
					pObject->Select();
				}
				// restoring the view
				pView->PopSelectionMatrices();

			}
			break;
		case PGL_MODE_TOOLS_ADD_TEXT: 
			break;
		//////////////////////////////////////////////////////////////////////////
		// panning the m_view...
		case PGL_MODE_VIEW_PAN: 
			m_mouse.LeftBtnReleased(lastx,lasty);
			m_mouse.GetLeftLastPos(lastx,lasty);
			m_pGraph->Pan(point.x-lastx,point.y-lasty);
			break;
		//////////////////////////////////////////////////////////////////////////
		// zomming the m_view...
		case PGL_MODE_VIEW_ZOOM:
			if (m_mouse.IsLeftMoving())
			{
				// keeping information
				m_mouse.LeftBtnReleased(firstx,firsty);	
				m_pGraph->ZoomBox(firstx,firsty,point.x,point.y);
			}
			else
			{
				// keeping information
				m_mouse.LeftBtnReleased(firstx,firsty);	
				if (nFlags==MK_CONTROL)
					m_pGraph->ZoomOut();
				else
					m_pGraph->ZoomIn();
			}
			break;
	}
	// stop mouse...
	m_mouse.Stop();
	m_wgl.End();


	CPGLGraphDlg::OnLButtonUp(nFlags, point);
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	ASSERT_VALID(m_pGraph);
	CPGLView* pView=m_pGraph->GetView();
	ASSERT_VALID(pView);

	// Get Device context
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);
	// setting OpenGLContext current
	m_wgl.Begin(&dc);

	// handle left button...
	int lastx,lasty;
	if (m_mouse.IsLeftBtnDown(lastx,lasty))
	{
		m_mouse.LeftMove();
		// checking with mode
		switch(m_iMouseMode)
		{
			case PGL_MODE_TOOLS_SELECTION: 
			case PGL_MODE_VIEW_ZOOM:
			case PGL_MODE_TOOLS_ADD_TEXT: break;
			case PGL_MODE_VIEW_PAN: // panning the m_view...
				m_pGraph->Pan(-(point.x-lastx),point.y-lasty);
				glFinish();
				break;
		}
		// updating mouse position
		m_mouse.UpdateLeftPos(point.x,point.y);
		InvalidateRect(NULL,FALSE);
	}
	// both button are not allowed
	// handle right button
//	else if	(mouse.isRightBtnDown(lastx,lasty))
//	{
//		// checking mode...
//	}
	
	m_wgl.End();

	CPGLGraphDlg::OnMouseMove(nFlags, point);
}

//////////////////////////////////////////////////////////////////
// Figure menu Callbacks
//////////////////////////////////////////////////////////////////

void CPGLGraphDCDlg::OnFigureOpen() 
{
	char szFilter[] = "PlotGL Files (*.pgl)|*.pgl|All Files (*.*)|*.*||";
	// pFileDlg...
	CFileDialog pFileDlg(
		TRUE /* open */,
		NULL	/* default extension */,
		NULL	/* initial pFilename in name box*/,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter);

	// Getting pFile name
	if (pFileDlg.DoModal()!=IDOK)
		return;

	// OK has been pressed...

	CString szFile=pFileDlg.GetPathName();
	// Opening the pFile 
	CFile file;
	if (!file.Open(szFile,CFile::modeRead))
	{
		AfxMessageBox("Failed to load file");
		return;
	}

	// saving
	CArchive archive(&file,CArchive::load);
	Serialize(archive);

	// Updating Dialog title
	szFile=_T("PlotGL - ")+szFile;
	SetWindowText(szFile);

	// Updating m_view
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CPGLGraphDCDlg::OnFigureSaveas() 
{
	char szFilter[] = "PlotGL Files (*.pgl)|*.pgl|All Files (*.*)|*.*||";
	// pFileDlg...
	CFileDialog pFileDlg(
		FALSE /* open */,
		"pgl"	/* default extension */,
		NULL	/* initial pFilename in name box*/,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter);

	// Getting pFile name
	if (pFileDlg.DoModal()!=IDOK)
		return;

	// OK has been pressed...

	CString szFile=pFileDlg.GetPathName();
	// Opening the pFile 
	CFile file;
	if (!file.Open(szFile,CFile::modeWrite | CFile::modeCreate))
	{
		AfxMessageBox("Failed to load pFile");
		return;
	}

	// saving
	CArchive archive(&file,CArchive::store);
	Serialize(archive);

	// Updating Dialog title
	szFile=_T("PlotGL - ")+szFile;
	SetWindowText(szFile);

	// Updating m_view
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

//////////////////////////////////////////////////////////////////
// Edit menu Callbacks
//////////////////////////////////////////////////////////////////
void CPGLGraphDCDlg::OnEditCut() 
{
	ASSERT_VALID(m_pGraph);

	// Get Device context
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);

	m_pGraph->CutSelection(); 
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnEditCopy() 
{
	ASSERT_VALID(m_pGraph);

	// Get Device context
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);

	m_pGraph->CopySelection();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnEditPaste() 
{
	ASSERT_VALID(m_pGraph);

	// Get Device context
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);

	m_pGraph->PasteSelection();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnEditDelete() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->DeleteSelection();
	InvalidateRect(NULL,FALSE);
}

//////////////////////////////////////////////////////////////////
// Selection menu Callbacks
//////////////////////////////////////////////////////////////////

void CPGLGraphDCDlg::OnSelectionOrderMovedown() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphDCDlg::OnSelectionOrderMoveup() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphDCDlg::OnSelectionOrderToback() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphDCDlg::OnSelectionOrderTofront() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphDCDlg::OnSelectionSelectall() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->SelectAll();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnSelectionUnhideall() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->UnhideAll();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnSelectionUnselect() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->UnselectAll();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnToolsAddtext() 
{
	m_iMouseMode=PGL_MODE_TOOLS_ADD_TEXT;
}

void CPGLGraphDCDlg::OnToolsSelect() 
{
	m_iMouseMode=PGL_MODE_TOOLS_SELECTION;
}

void CPGLGraphDCDlg::OnViewSelect() 
{
	m_iMouseMode=PGL_MODE_TOOLS_SELECTION;
}

void CPGLGraphDCDlg::OnViewPan() 
{
	m_iMouseMode=PGL_MODE_VIEW_PAN;
}

void CPGLGraphDCDlg::OnViewProperties() 
{
	CPGLAllPropsDlg allDlg;

	ASSERT_VALID(m_pGraph);
	allDlg.SetGraph(m_pGraph);
	allDlg.SetSelection(m_pGraph->GetAxe());
	allDlg.DoModal();

	//updating view
	InvalidateRect(NULL,FALSE);
}


void CPGLGraphDCDlg::OnAxeProperties() 
{
	ASSERT_VALID(m_pGraph);

	// getting axis
	m_pGraph->GetAxe()->ShowModalPropertySheet();
}

void CPGLGraphDCDlg::OnViewZoom() 
{
	m_iMouseMode=PGL_MODE_VIEW_ZOOM;
}


void CPGLGraphDCDlg::OnViewZoomAll() 
{
	ASSERT_VALID(m_pGraph);

	// Getting DC
	CClientDC dc(this);
	// Init graph DC
	m_pGraph->SetDC(&dc);
	// zooming m_pGraph extents
	m_pGraph->ZoomAll();

	InvalidateRect(NULL,FALSE);
}

void CPGLGraphDCDlg::OnClose() 
{
	PGL_TRACE("PGL-GraphDCDlg: Closing dialog\n");
	CDialog::OnClose();
}

void CPGLGraphDCDlg::OnFigureExportToJPEG() 
{
	ASSERT(m_pGraph);

	CClientDC dc(this);

	GLint vp[4];
	m_pGraph->GetViewport(vp);
	
	CGLImage image;
	
	image.Create(vp[2],vp[3]);
	ExportToJPEG(&image);
}

void CPGLGraphDCDlg::OnFigureExportToVectors() 
{
	CClientDC dc(this);
	ExportToVectors(&dc);
}
