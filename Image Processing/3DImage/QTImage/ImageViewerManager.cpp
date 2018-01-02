// ImageViewerManager.cpp: implementation of the CImageViewerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QTImage.h"
#include "ImageViewerManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C2DViewerManager::C2DViewerManager()
{
	m_pParent=NULL;
	m_ctrler=NULL;
	m_ImageList=NULL;
	m_pSeriesManager=NULL;
	m_groundColor=RGB(0,0,0);
}

C2DViewerManager::~C2DViewerManager()
{
	
}

void C2DViewerManager::SetParent(CWnd *pWnd)
{
	m_pParent=pWnd;
}

void C2DViewerManager::Init()
{
	m_ctrler=new C2DCtrler(m_pParent);
	m_ctrler->Create(IDD_IMAGE_CTRL2D,m_pParent);
	m_ctrler->ShowWindow(SW_HIDE);

	m_ImageList=new CSeriesList(m_pParent);
	m_ImageList->Create(IDD_IMAGE_LIST,m_pParent);
	m_ImageList->ShowWindow(SW_HIDE);

}

void C2DViewerManager::ShowSeries(vtkImageData *pImage)
{
	if(m_list.GetCount()<4)
	{

		C2DViewer *pView2D=new C2DViewer(m_pParent);
		pView2D->Create(IDD_IMAGE_VIEW2D,m_pParent);
		pView2D->ShowWindow(SW_HIDE);
		pView2D->m_pList=&m_list;
		pView2D->m_pManager=m_pSeriesManager;
		pView2D->SetSeries(pImage);
		pView2D->SetGroundColor(m_groundColor);

		m_list.AddTail(pView2D);

		Update();

		POSITION pos=m_list.GetHeadPosition();
		C2DViewer *pView;
		while(pos)
		{
			pView=m_list.GetNext(pos);
			if(pView==pView2D)
			{
				pView->UpdateSelectedStatus(TRUE);
			}else
			{
				pView->UpdateSelectedStatus(FALSE);
			}
		}
	}

	m_ImageList->AddSeries();  //update image list window
}

void C2DViewerManager::Update()
{
	int ctrlerWidht=1,ctrlerHeight=1;
	int x=m_rect.left;
	int y=m_rect.top;
	int w=m_rect.Width();
	int h=m_rect.Height();
	
	if(!m_ctrler)
		return;

	
	m_ctrler->MoveWindow(x,y,ctrlerWidht,ctrlerHeight);
	m_ImageList->MoveWindow(x,y+ctrlerHeight,113,h-ctrlerHeight);
	if(m_list.GetCount()>0)
	{
		m_ctrler->ShowWindow(SW_SHOW);
		m_ImageList->ShowWindow(SW_SHOW);
	}

	x=x+113;
	w=w-113;
	
	C2DViewer *pView2D;
	POSITION pos=m_list.GetHeadPosition();
	int count=0;
	
	m_pParent->Invalidate(TRUE);
	
	switch(m_list.GetCount())
	{
	case 3:
	case 4:
		while(pos)
		{
			pView2D=m_list.GetNext(pos);
			count++;
			if(count==1)
			{
				pView2D->MoveWindow(x,y+ctrlerHeight,w/2,(h-ctrlerHeight)/2);
			}else if(count==2)
			{
				pView2D->MoveWindow(x+w/2,y+ctrlerHeight,w/2,(h-ctrlerHeight)/2);
			}else if(count==3)
			{
				pView2D->MoveWindow(x,y+ctrlerHeight+(h-ctrlerHeight)/2,w/2,(h-ctrlerHeight)/2);
			}else if(count==4)
			{
				pView2D->MoveWindow(x+w/2,y+ctrlerHeight+(h-ctrlerHeight)/2,w/2,(h-ctrlerHeight)/2);
			}
		}
		break;
	case 2:
		while(pos)
		{
			pView2D=m_list.GetNext(pos);
			pView2D->MoveWindow(x,y+ctrlerHeight,w/2,h-ctrlerHeight);
			x=x+w/2;
		}
		break;
	default:
		if(pos)
		{
			pView2D=m_list.GetNext(pos);
			pView2D->MoveWindow(x,y+ctrlerHeight,w,h-ctrlerHeight);
		}
		break;
	}

	pos=m_list.GetHeadPosition();
	while(pos)
	{
		pView2D=m_list.GetNext(pos);
		if(!pView2D->IsWindowVisible())
		{
			pView2D->ShowWindow(SW_SHOW);
		}
	}
	
}

void C2DViewerManager::SetWndRect(CRect rect)
{
	m_rect=rect;
	Update();
}

void C2DViewerManager::RemoveAll()
{
	if(m_ctrler)
	{
		if(m_ctrler->m_hWnd)
		{
			m_ctrler->DestroyWindow();
		}
		delete m_ctrler;
	}

	if(m_ImageList)
	{
		if(m_ImageList->m_hWnd)
		{
			m_ImageList->DestroyWindow();
		}
		delete m_ImageList;
	}
	
	C2DViewer *pView2D;
	POSITION pos=m_list.GetHeadPosition();
	while(pos)
	{
		pView2D=m_list.GetNext(pos);
		if(pView2D)
		{
			if(pView2D->m_hWnd)
			{
				pView2D->DestroyWindow();
			}
			delete pView2D;
		}
	}
	m_list.RemoveAll();
}

void C2DViewerManager::SetSeriesManager(CSeriesManager *pManager)
{
	m_pSeriesManager=pManager;
	m_ImageList->SetSeriesManager(m_pSeriesManager);
}

void C2DViewerManager::ShowSeriesInCurWnd(vtkImageData *pImage)
{
	
	POSITION pos=m_list.GetHeadPosition();
	C2DViewer *pView;
	while(pos)
	{
		pView=m_list.GetNext(pos);
		if(pView->m_bSelected)
		{
			pView->SetSeries(pImage);
			break;
		}
	}
}

vtkImageData* C2DViewerManager::GetSeriesInCurWnd()
{
	vtkImageData *pImage=NULL;
	POSITION pos=m_list.GetHeadPosition();
	C2DViewer *pView;
	while(pos)
	{
		pView=m_list.GetNext(pos);
		if(pView->m_bSelected)
		{
			pImage=pView->GetSeries();
			break;
		}
	}

	return pImage;
}

void C2DViewerManager::GetSeriesWWWLInCurWnd(short &ww,short &wl)
{
	vtkImageData *pImage=NULL;
	POSITION pos=m_list.GetHeadPosition();
	C2DViewer *pView;
	while(pos)
	{
		pView=m_list.GetNext(pos);
		if(pView->m_bSelected)
		{
			ww=pView->m_pViewer->GetColorWindow();
			wl=pView->m_pViewer->GetColorLevel();
			break;
		}
	}

	return;
}

void C2DViewerManager::SetGroundColor(COLORREF color)
{
	m_groundColor=color;
	POSITION pos=m_list.GetHeadPosition();
	C2DViewer *pView;
	while(pos)
	{
		pView=m_list.GetNext(pos);
		pView->SetGroundColor(color);
	}
}

C2DViewer* C2DViewerManager::GetCurView()
{
	POSITION pos=m_list.GetHeadPosition();
	C2DViewer *pView;
	while(pos)
	{
		pView=m_list.GetNext(pos);
		if(pView->m_bSelected)
		{
			return pView;
		}
	}

	return NULL;
}
