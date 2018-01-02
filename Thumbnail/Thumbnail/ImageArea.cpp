// ImageArea.cpp : implementation file
//

#include "stdafx.h"
#include "thumbnail.h"
#include "ImageArea.h"
#include "thumbnailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageArea

CImageArea::CImageArea()
{
}

CImageArea::~CImageArea()
{
}


BEGIN_MESSAGE_MAP(CImageArea, CStatic)
	//{{AFX_MSG_MAP(CImageArea)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageArea message handlers

void CImageArea::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CThumbnailDlg*  pWnd = static_cast<CThumbnailDlg*>(GetParent());
	if(pWnd->m_ListThumbnail.GetItemCount() != 0)
	 pWnd->DrawSelectedImage();
	
	// Do not call CStatic::OnPaint() for painting messages
}
