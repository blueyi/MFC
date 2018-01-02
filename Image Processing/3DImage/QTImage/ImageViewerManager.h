// ImageViewerManager.h: interface for the CImageViewerManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEVIEWERMANAGER_H__D68D7577_976D_49AF_802E_B26A86208FC9__INCLUDED_)
#define AFX_IMAGEVIEWERMANAGER_H__D68D7577_976D_49AF_802E_B26A86208FC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AfxTempl.h"
#include "ImageViewer.h"
#include "GlobalHeader.h"
#include "Ctrler2D.h"
#include "Viewer2D.h"
#include "SeriesList.h"

class C2DViewerManager  
{
public:
	C2DViewer* GetCurView();
	void SetGroundColor(COLORREF color);
	void GetSeriesWWWLInCurWnd(short &ww,short &wl);
	vtkImageData* GetSeriesInCurWnd();
	void ShowSeriesInCurWnd(vtkImageData *pImage);
	void SetSeriesManager(CSeriesManager *pManager);
	void RemoveAll();
	void SetWndRect(CRect rect);
	void ShowSeries(vtkImageData *pImage);
	void Init();
	void SetParent(CWnd *pWnd);

	C2DViewerManager();
	virtual ~C2DViewerManager();

private:
	void Update();
	C2DCtrler *m_ctrler;
	CSeriesList *m_ImageList;
	CList<C2DViewer*,C2DViewer*> m_list;

	CWnd *m_pParent;
	CRect m_rect;
	COLORREF m_groundColor;
	CSeriesManager *m_pSeriesManager;
};

#endif // !defined(AFX_IMAGEVIEWERMANAGER_H__D68D7577_976D_49AF_802E_B26A86208FC9__INCLUDED_)
