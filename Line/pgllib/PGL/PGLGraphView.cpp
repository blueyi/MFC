// PGLGraphView.cpp : implementation file
//

#include "stdafx.h"
#include <objbase.h>
#include "PGL/pgl.h"
#include "PGL/PGLGraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphView

IMPLEMENT_DYNCREATE(CPGLGraphView, CView)

CPGLGraphView::CPGLGraphView()
{
	m_pGraph = NULL;
#ifndef _DEBUG
	m_pMemBitmap = NULL;
#endif
}

CPGLGraphView::~CPGLGraphView()
{
	if (m_pGraph) 
	{
		delete m_pGraph;
		m_pGraph = NULL;
	}
}


BEGIN_MESSAGE_MAP(CPGLGraphView, CView)
	//{{AFX_MSG_MAP(CPGLGraphView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_COMMAND(ID_PGL_OBJECTS_EXPLORER, OnObjectsExplorer)
	ON_COMMAND(ID_PGL_FILE_EXPORT, OnPglFileExport)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CPGLGraphView drawing

void CPGLGraphView::OnDraw(CDC* pDC)
{
	using namespace Gdiplus;

	if (!m_pGraph)
		return;

	ASSERT(m_pGraph);	

	Gdiplus::Graphics graphics(pDC->m_hDC);

#ifdef _DEBUG
	Gdiplus::Bitmap MemBitmap(m_GDIpInterface.GetMainBBWidth(), m_GDIpInterface.GetMainBBHeight());
	Gdiplus::Bitmap* m_pMemBitmap = &MemBitmap;
#else
	if (!m_pMemBitmap)
		m_pMemBitmap = new Bitmap(m_GDIpInterface.GetMainBBWidth(),m_GDIpInterface.GetMainBBHeight());
	else
	{
		RectF rect; Unit unit;
		m_pMemBitmap->GetBounds(&rect,&unit);
		if ( rect.Width != m_GDIpInterface.GetMainBBWidth() ||
			rect.Height != m_GDIpInterface.GetMainBBHeight() )
		{
			// resetting memory bitmap
			if (m_pMemBitmap)
				delete m_pMemBitmap;
			m_pMemBitmap = new Bitmap(m_GDIpInterface.GetMainBBWidth(),m_GDIpInterface.GetMainBBHeight());
		}
	}
#endif

	ASSERT(m_pMemBitmap);
	ASSERT(m_pMemBitmap->GetLastStatus() == Ok);

	Gdiplus::Graphics* pMemGraphics = Gdiplus::Graphics::FromImage(m_pMemBitmap);	
	m_GDIpInterface.SetGraphics(pMemGraphics);

	m_GDIpInterface.BeginPaint();
	m_pGraph->PlotGfx(m_GDIpInterface);
	m_GDIpInterface.EndPaint();
	
	// Draw the image.
	graphics.DrawImage(m_pMemBitmap, 0,0);
	
	delete pMemGraphics;
}

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphView diagnostics

#ifdef _DEBUG
void CPGLGraphView::AssertValid() const
{
	CView::AssertValid();

}

void CPGLGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphView message handlers

void CPGLGraphView::OnSize(UINT nType, int cx, int cy) 
{
	using namespace Gdiplus;

	CView::OnSize(nType, cx, cy);

	// setting interface...
	m_GDIpInterface.SetMainBoundingBox(0,0,cx,cy);

	if (m_pGraph == NULL)
		return;

	m_pGraph->SetViewport(0,0,cx,cy);
	m_pGraph->ZoomAll(TRUE);
}

void CPGLGraphView::SetGraph(CPGLGraph *pGraph)
{
	m_pGraph = pGraph;

	CRect rect;
	GetClientRect(&rect);

	if (rect.IsRectEmpty())
		return;

	m_GDIpInterface.SetMainBoundingBox(rect.left,rect.top,rect.Width(),rect.Height());
	m_pGraph->SetViewport(rect.left,rect.top,rect.Width(),rect.Height());
	m_pGraph->ZoomAll(TRUE);
}

BOOL CPGLGraphView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	DoPreparePrinting(pInfo);
	
	return CView::OnPreparePrinting(pInfo);
}

void CPGLGraphView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{	
	if (m_pGraph)
	{
		Gdiplus::Graphics graphics(pDC->m_hDC);

		m_GDIpInterface.SetMainBoundingBox(pInfo->m_rectDraw);

		m_pGraph->SetViewport(pInfo->m_rectDraw.left, pInfo->m_rectDraw.top, 
			m_GDIpInterface.GetMainBBWidth(),m_GDIpInterface.GetMainBBHeight());

		m_pGraph->ZoomAll(TRUE);
		m_GDIpInterface.SetGraphics(&graphics);
		m_GDIpInterface.BeginPaint();
		m_pGraph->PlotGfx(m_GDIpInterface);
		m_GDIpInterface.EndPaint();
	}
}

void CPGLGraphView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	CView::OnLButtonDown(nFlags, point);
}

void CPGLGraphView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	CView::OnLButtonUp(nFlags, point);
}

void CPGLGraphView::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	CView::OnMouseMove(nFlags, point);
}

void CPGLGraphView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (!m_pGraph)
	{
		CView::OnRButtonDown(nFlags, point);
		return;
	}

	ASSERT_VALID(m_pGraph);
	CPGLAllPropsDlg propDlg;
	propDlg.SetGraph(m_pGraph);
	propDlg.DoModal();	
	
	InvalidateRect(NULL,FALSE);
	CView::OnRButtonDown(nFlags, point);
}

void CPGLGraphView::OnEditCopy()
{
	using namespace Gdiplus;

	if (!m_pGraph)
		return;

	if ( !OpenClipboard() )
	{
		AfxMessageBox( "Cannot open the Clipboard" );
		return;
	}
	// Remove the current Clipboard contents
	if( !EmptyClipboard() )
	{
		AfxMessageBox( "Cannot empty the Clipboard" );
		return;
	}

	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	Gdiplus::CGDIRect gdirect(rect);

	Gdiplus::Metafile metafile(dc.m_hDC, (Gdiplus::Rect)gdirect, Gdiplus::MetafileFrameUnitPoint); 
	{
		Gdiplus::Graphics graphics(&metafile);

		m_GDIpInterface.SetGraphics(&graphics);

		m_GDIpInterface.BeginPaint();
		m_pGraph->PlotGfx(m_GDIpInterface);
		m_GDIpInterface.EndPaint();		
	}

	HENHMETAFILE hEnhMetaFile=metafile.GetHENHMETAFILE();

	HANDLE hResult = ::SetClipboardData(CF_ENHMETAFILE,hEnhMetaFile);
	if (hResult == NULL)
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		AfxMessageBox((LPCTSTR)lpMsgBuf);
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}

	// ...
	CloseClipboard();
}


BOOL CPGLGraphView::OnEraseBkgnd(CDC* pDC) 
{
	if (m_pGraph)	
		return TRUE;
	else
		return CView::OnEraseBkgnd(pDC);
}

void CPGLGraphView::OnDestroy() 
{
	using namespace Gdiplus;

	CView::OnDestroy();

	if (m_pGraph)
		m_pGraph->Delete();

#ifndef _DEBUG
	if (m_pMemBitmap)
		delete m_pMemBitmap;
#endif
}


CMenu* CPGLGraphView::LoadMenu()
{
		// saving old ressource.
	HINSTANCE hOldInst=AfxGetResourceHandle();
	// setting dll ressource
	AfxSetResourceHandle(AfxGetInstanceHandle());

	
	// Load the new menu.
	CMenu* pNewMenu = new CMenu();
	pNewMenu->LoadMenu(IDR_PGL_MENU_VIEW);
	ASSERT(pNewMenu);

	// restoring old ressource.
	AfxSetResourceHandle(hOldInst);

	return pNewMenu;
}

void CPGLGraphView::OnObjectsExplorer() 
{
	if (!m_pGraph)
		return;

	ASSERT_VALID(m_pGraph);
	CPGLAllPropsDlg propDlg;
	propDlg.SetGraph(m_pGraph);
	propDlg.DoModal();	
	
	InvalidateRect(NULL,FALSE);
}

void CPGLGraphView::OnPglFileExport() 
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
	MultiByteToWideChar(CP_THREAD_ACP,MB_PRECOMPOSED, szFile,-1,wzFile,512);

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
		gfxinterface::CSVGInterface svg(szFile,true);
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
		Gdiplus::Metafile metafile(wzFile); 
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
		wcsncpy(codec,L"image/jpeg",10);
	else if (szExtension == "png")
		wcsncpy(codec,L"image/png",9);
	else if (szExtension == "tiff")
		wcsncpy(codec,L"image/tiff",10);
	else if (szExtension == "gif")
		wcsncpy(codec,L"image/gif",9);
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
