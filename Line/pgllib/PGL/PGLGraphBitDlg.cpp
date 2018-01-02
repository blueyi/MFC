// GraphGLDlg.cpp : implementation pFile
//

#include "stdafx.h"
#include "PGL/PGLGraphBitDlg.h"
#include "PGL/PGLAllPropsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphBitDlg dialog


CPGLGraphBitDlg::CPGLGraphBitDlg(CWnd* pParent,CPGLGraph* _pGraph /*=NULL*/)
: CPGLGraphDlg( pParent,_pGraph )
{
	//{{AFX_DATA_INIT(CPGLGraphBitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPGLGraphBitDlg::DoDataExchange(CDataExchange* pDX)
{
	CPGLGraphDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLGraphBitDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLGraphBitDlg, CDialog)
	//{{AFX_MSG_MAP(CPGLGraphBitDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	ON_COMMAND(ID_PGL_VIEW_SELECT, OnViewSelect)
	ON_COMMAND(ID_PGL_VIEW_PAN, OnViewPan)
	ON_COMMAND(ID_PGL_VIEW_PROPERTIES, OnViewProperties)
	ON_COMMAND(ID_PGL_AXE_PROPERTIES, OnAxeProperties)
	ON_COMMAND(ID_PGL_VIEW_ZOOM, OnViewZoom)
	ON_COMMAND(ID_PGL_VIEW_ZOOMALL, OnViewZoomAll)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphBitDlg message handlers

int CPGLGraphBitDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	PGL_TRACE("PGL-GraphBitDlg: Creating dialog box\n");

	if (CPGLGraphDlg::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CPGLGraphBitDlg::OnInitDialog() 
{
	PGL_TRACE("PGL-GraphBitDlg: Initialisating graph\n");

	CPGLGraphDlg::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// checking graph...
	ASSERT_VALID(m_pGraph);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPGLGraphBitDlg::OnPaint() 
{	

	CRect rect;
	CClientDC dc(this);

	// Init graph DC
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	

		// blitting...
		if (GetUpdateRect(&rect))
		{
			CPaintDC paintDC(this);
			Gdiplus::Graphics graphics(paintDC.m_hDC);
			ASSERT(m_pGraph);	

			Gdiplus::Bitmap MemBitmap(m_GDIpInterface.GetMainBBWidth(), m_GDIpInterface.GetMainBBHeight());;
			Gdiplus::Graphics* pMemGraphics = Gdiplus::Graphics::FromImage(&MemBitmap);	

			m_GDIpInterface.SetGraphics(pMemGraphics);
			m_GDIpInterface.BeginPaint();
			m_pGraph->PlotGfx(m_GDIpInterface);
			m_GDIpInterface.EndPaint();

			// Draw the image.
			graphics.DrawImage(&MemBitmap, (INT)rect.left, (INT)rect.top,  (INT)rect.left, (INT)rect.top,  
				(INT) rect.Width(),(INT)rect.Height(), Gdiplus::UnitPixel);

			delete pMemGraphics;
		}

		CPGLGraphDlg::OnPaint();
	}
}


void CPGLGraphBitDlg::OnSize(UINT nType, int cx, int cy) 
{
	PGL_TRACE("PGL-GraphBitDlg: Resizing graph\n");

	m_GDIpInterface.SetMainBoundingBox(0,0,cx,cy);

	m_pGraph->SetViewport(0,0,cx,cy);
	m_pGraph->ZoomAll(TRUE);
	
	Invalidate(FALSE);

	CPGLGraphDlg::OnSize(nType, cx, cy);
}


void CPGLGraphBitDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	ASSERT_VALID(m_pGraph);
	CPGLView* pView=m_pGraph->GetView();
	ASSERT_VALID(pView);

	// keeping information
	m_mouse.RightBtnPressed(point.x,point.y);
	// stopping mouse
	m_mouse.Stop();


	CPGLAllPropsDlg propDlg;

	propDlg.SetGraph(m_pGraph);
	propDlg.DoModal();

	CPGLGraphDlg::OnRButtonDown(nFlags, point);

	// redraw dialog
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// keeping mouse
	SetCapture();

	// keeping information
	m_mouse.LeftBtnPressed(point.x,point.y);
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CPGLGraphBitDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//Releasing mouse
	ReleaseCapture();

	// stop mouse...
	m_mouse.Stop();

	CPGLGraphDlg::OnLButtonUp(nFlags, point);
	InvalidateRect(NULL,FALSE);
}

//////////////////////////////////////////////////////////////////
// Figure menu Callbacks
//////////////////////////////////////////////////////////////////

void CPGLGraphBitDlg::OnFigureOpen() 
{
	return ;

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

void CPGLGraphBitDlg::OnFigureSaveas() 
{
	using namespace Gdiplus;

	CString szFilter = "EPS (Encapsulated Postscript) (*.eps)|*.eps|";
	szFilter+="SVG (Scalable Vector Graphics) (*.svg)|*.svg|";
	szFilter+="WMF (Windows Metafile) (*.wmf)|*.wmf|";
	szFilter+="EMF (Enhanced Windows Metafile) (*e.emf)|*.emf|";
	szFilter+="JPEG (*.jpg,*.jpeg)|*.jpg;*.jpeg|";
	szFilter+="TIFF (*.tiff)|*.tiff|";
	szFilter+="GIF (*.gif)|*.gif|";
	szFilter+="PNG (Portable Network Graphics) (*.png)|*.png||";

	// pFileDlg...
	CFileDialog pFileDlg(
		FALSE /* open */,
		NULL	/* default extension */,
		"untitled"	/* initial pFilename in name box*/,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter);

	// Getting pFile name
	if (pFileDlg.DoModal()!=IDOK)
		return;

	// OK has been pressed...
	CString szFile=pFileDlg.GetPathName();
	szFile.TrimRight(pFileDlg.GetFileName());
	CString szExtension = pFileDlg.GetFileExt();
	szExtension.MakeLower();

	if (szExtension=="jpg")
		szExtension="jpeg";

	szFile+=pFileDlg.GetFileTitle()+"."+szExtension;

	// Title and time creation...
	CString szCreator="Plot Graphic Library";
	CString szCreationDate = CTime::GetCurrentTime().Format( "%A, %B %d, %Y" );
	CString szTitle;
	GetWindowText(szTitle);
	// getting main bounding box...
	CPGLView* pView=m_pGraph->GetView();

	// wide character
	static WCHAR wzFile[512];
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED, szFile,-1,wzFile,512);

	if (szExtension == "eps")
	{
		gfxinterface::CEPSInterface eps(szFile);
		eps.SetCreator(szCreator);
		eps.SetCreationDate(szCreationDate);
		eps.SetTitle(szTitle);
		eps.SetMainBoundingBox(pView->GetTx(), pView->GetTy(), 
			pView->GetTx()+pView->GetWidth(), pView->GetTy()+pView->GetHeight());
		if (eps.Open())
		{
			eps.BeginPaint();
			m_pGraph->PlotGfx(eps);
			eps.EndPaint();
			eps.Close();
		}
		return;
	}

	if (szExtension == "svg")
	{
		gfxinterface::CSVGInterface svg(szFile,false);
		svg.SetCreator(szCreator);
		svg.SetCreationDate(szCreationDate);
		svg.SetTitle(szTitle);
		svg.SetMainBoundingBox(pView->GetTx(), pView->GetTy(), 
			pView->GetTx()+pView->GetWidth(), pView->GetTy()+pView->GetHeight());
		if (svg.Open())
		{
			svg.BeginPaint();
			m_pGraph->PlotGfx(svg);
			svg.EndPaint();
			svg.Close();
		}
		return;
	}

	if (szExtension == "wmf" || szExtension == "emf")
	{
		CClientDC dc(this);
		Gdiplus::Metafile metafile(wzFile, dc.m_hDC); 
		{
			Gdiplus::Graphics graphics(&metafile);

			m_GDIpInterface.SetGraphics(&graphics);

			m_GDIpInterface.BeginPaint();
			m_pGraph->PlotGfx(m_GDIpInterface);
			m_GDIpInterface.EndPaint();			
		}
		return;
	}	


	CLSID Clsid;
	WCHAR codec[20];
	Gdiplus::EncoderParameters encoderParameters;
	ULONG             quality;

	if (szExtension == "jpg" || szExtension == "jpeg")
		wcsncpy(codec,L"image/jpeg\0",11);
	else if (szExtension == "png")
		wcsncpy(codec,L"image/png\0",10);
	else if (szExtension == "tiff")
		wcsncpy(codec,L"image/tiff\0",11);
	else if (szExtension == "gif")
		wcsncpy(codec,L"image/gif\0",10);
	else
		return;
	
	if (!m_GDIpInterface.GetEncoderClsid(codec, &Clsid))
	{
		AfxMessageBox("Codec not available.");
		return;
	}
	
	encoderParameters.Count = 1;
	encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
	encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues = 1;
	quality = 75;
	encoderParameters.Parameter[0].Value = &quality;
	
	
	Gdiplus::Bitmap image(m_GDIpInterface.GetMainBBWidth(), m_GDIpInterface.GetMainBBHeight());
	Gdiplus::Graphics* pGraphics = Gdiplus::Graphics::FromImage(&image);

	m_GDIpInterface.SetGraphics(pGraphics);
	m_GDIpInterface.BeginPaint();
	m_pGraph->PlotGfx(m_GDIpInterface);
	m_GDIpInterface.EndPaint();			
	image.Save(wzFile, &Clsid, &encoderParameters);
	
	delete pGraphics;
}

//////////////////////////////////////////////////////////////////
// Edit menu Callbacks
//////////////////////////////////////////////////////////////////
void CPGLGraphBitDlg::OnEditCut() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->CutSelection(); 
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnEditCopy() 
{
	ASSERT_VALID(m_pGraph);
	m_pGraph->CopySelection();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnEditPaste() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->PasteSelection();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnEditDelete() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->DeleteSelection();
	InvalidateRect(NULL,FALSE);
}

//////////////////////////////////////////////////////////////////
// Selection menu Callbacks
//////////////////////////////////////////////////////////////////

void CPGLGraphBitDlg::OnSelectionOrderMovedown() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphBitDlg::OnSelectionOrderMoveup() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphBitDlg::OnSelectionOrderToback() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphBitDlg::OnSelectionOrderTofront() 
{
	// TODO: Add your command handler code here
	
}

void CPGLGraphBitDlg::OnSelectionSelectall() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->SelectAll();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnSelectionUnhideall() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->UnhideAll();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnSelectionUnselect() 
{
	ASSERT_VALID(m_pGraph);

	m_pGraph->UnselectAll();
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnToolsAddtext() 
{
	m_iMouseMode=PGL_MODE_TOOLS_ADD_TEXT;
}

void CPGLGraphBitDlg::OnToolsSelect() 
{
	m_iMouseMode=PGL_MODE_TOOLS_SELECTION;
}

void CPGLGraphBitDlg::OnViewSelect() 
{
	m_iMouseMode=PGL_MODE_TOOLS_SELECTION;
}

void CPGLGraphBitDlg::OnViewPan() 
{
	m_iMouseMode=PGL_MODE_VIEW_PAN;
}

void CPGLGraphBitDlg::OnViewProperties() 
{
	CPGLAllPropsDlg allDlg;

	allDlg.SetGraph(m_pGraph);
	allDlg.DoModal();

	//updating view
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnAxeProperties() 
{
	ASSERT_VALID(m_pGraph);

	// getting axis
	m_pGraph->GetAxe()->ShowModalPropertySheet();
}

void CPGLGraphBitDlg::OnViewZoom() 
{
	m_iMouseMode=PGL_MODE_VIEW_ZOOM;
}


void CPGLGraphBitDlg::OnViewZoomAll() 
{
	ASSERT_VALID(m_pGraph);

	// zooming m_pGraph extents
	m_pGraph->ZoomAll(TRUE);

	InvalidateRect(NULL,FALSE);
}

void CPGLGraphBitDlg::OnClose() 
{
	PGL_TRACE("PGL-GraphBitDlg: Closing dialog\n");
	CDialog::OnClose();
}
