// DisplayView.cpp : implementation file
//

#include "stdafx.h"
#include "BigSee.h"
#include "DisplayView.h"
#include "MenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayView

IMPLEMENT_DYNCREATE(CDisplayView, CScrollView)
 
CDisplayView::CDisplayView():IsHaveImage(FALSE),m_lImagecx(0),m_lImagecy(0)
                             ,m_dwbytes(0),m_loriginalXImageSize(450),m_loriginalYImageSize(320)
							 ,m_nScale(1),IsUseRegularScale(FALSE), m_uiChoice(NORMAL_IMAGE)
{
	
    
}

CDisplayView::~CDisplayView()
{
}


BEGIN_MESSAGE_MAP(CDisplayView, CScrollView)
	//{{AFX_MSG_MAP(CDisplayView)
	ON_COMMAND(ID_IMAGE_ZOOMIN, OnImageZoomin)
	ON_COMMAND(ID_IMAGE_ZOOMOUT, OnImageZoomout)
	ON_COMMAND(ID_SCALE_ABSOLUTELY, OnScaleAbsolutely)
	ON_UPDATE_COMMAND_UI(ID_SCALE_ABSOLUTELY, OnUpdateScaleAbsolutely)
	ON_COMMAND(ID_CENTY_SEVENTY_FIVE, OnCentySeventyFive)
	ON_UPDATE_COMMAND_UI(ID_CENTY_SEVENTY_FIVE, OnUpdateCentySeventyFive)
	ON_COMMAND(ID_CENTY_FIFTY, OnCentyFifty)
	ON_UPDATE_COMMAND_UI(ID_CENTY_FIFTY, OnUpdateCentyFifty)
	ON_COMMAND(ID_CENTY_THIRTY, OnCentyThirty)
	ON_UPDATE_COMMAND_UI(ID_CENTY_THIRTY, OnUpdateCentyThirty)
	ON_COMMAND(ID_CENTY_TWENTY, OnCentyTwenty)
	ON_UPDATE_COMMAND_UI(ID_CENTY_TWENTY, OnUpdateCentyTwenty)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_ZOOMIN, OnUpdateImageZoomin)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_ZOOMOUT, OnUpdateImageZoomout)
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayView drawing

void CDisplayView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx =100;
	sizeTotal.cy = 100;//100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
    
}

void CDisplayView::OnDraw(CDC* pDC)
{
	CBigSeeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
 if(!IsHaveImage)
 {
	 return;
 }
 else
 {
    IPicture*pPicture;
    IStream*pStrm;
    CFileStatus fstatus;
    CFile file;
    
    if(file.Open(m_strDisplayFileName,CFile::modeRead)
		&&file.GetStatus(m_strDisplayFileName,fstatus)
		&&((m_dwbytes=fstatus.m_size)!=-1))
	{
	 HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,m_dwbytes);
	 LPVOID pvData=NULL;
	 CDC*pDC;
	 
	 //get the DC of the CDisplayView
	 pDC=this->GetDC();
	 
	 if(hGlobal!=NULL)
	 {
		 if((pvData=GlobalLock(hGlobal))!=NULL)
		 {
			 file.Read(pvData,m_dwbytes);
			 GlobalUnlock(hGlobal);
			 CreateStreamOnHGlobal(hGlobal,TRUE,&pStrm);
		     if(SUCCEEDED(OleLoadPicture(pStrm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPicture)))
			 {
				 OLE_XSIZE_HIMETRIC Width;
				 OLE_YSIZE_HIMETRIC Height;
			     pPicture->get_Width(&Width);
                 pPicture->get_Height(&Height);
                 // CRect rect;
				 //pDisplayView->GetClientRect(&rect);
				 //if(FAILED(pPicture->Render(*pDC,0,0,rect.Width(),rect.Height(),0,Height,Width,-Height,NULL)))
				 if(FAILED(pPicture->Render(*pDC,0,0,m_lImagecx,m_lImagecy,0,Height,Width,-Height,NULL)))
				 {
					  AfxMessageBox("Failed");
				      pPicture->Release();
					  IsHaveImage=FALSE;
			     }
				 else
				 {
				 ;
				 }//AfxMessageBox("Error");
			 }
		}
	 }
	 else
	 {
        AfxMessageBox("can't open the Image file");
	 }
	}	
 }

}


/////////////////////////////////////////////////////////////////////////////
// CDisplayView diagnostics

#ifdef _DEBUG
void CDisplayView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDisplayView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}


CBigSeeDoc* CDisplayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBigSeeDoc)));
	return (CBigSeeDoc*)m_pDocument;
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CDisplayView message handlers

void CDisplayView::OnImageZoomin() 
{
	// TODO: Add your command handler code here
	m_uiChoice=ZOOMIN_IMAGE;

	IsUseRegularScale=FALSE;
	//::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMIN));
    
}

void CDisplayView::OnImageZoomout() 
{
	// TODO: Add your command handler code here
  	m_uiChoice=ZOOMOUT_IMAGE;
	IsUseRegularScale=FALSE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMOUT));

}

void CDisplayView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  if(lHint==0x5A)
  {
	  LPTSTR ItemInfo=(LPTSTR)(pHint);
	  m_strDisplayFileName=ItemInfo;
      Invalidate();
	  CString StrCurPath=m_strDisplayFilePath;
	  LPTSTR pCurFolder=StrCurPath.GetBufferSetLength(StrCurPath.GetLength()
		         -m_strDisplayFileName.GetLength());//ÁôÏÂ'\';
      CString temp(pCurFolder);
	  temp=temp+m_strDisplayFileName;
	  (AfxGetMainWnd())->SetWindowText(LPCTSTR(temp));
  }

}

void CDisplayView::OnScaleAbsolutely() 
{
	// TODO: Add your command handler code here
    m_lImagecx=m_loriginalXImageSize;
	m_lImagecy=m_loriginalYImageSize;
    IsUseRegularScale=TRUE;
	m_nScale=1;//±ÈÀý
    Invalidate();
	m_uiChoice=NORMAL_IMAGE;
	
}

void CDisplayView::OnUpdateScaleAbsolutely(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsHaveImage);
	pCmdUI->SetCheck(m_nScale==1&&IsUseRegularScale&&IsHaveImage);
}

void CDisplayView::OnCentySeventyFive() 
{
	// TODO: Add your command handler code here
	
	m_lImagecx=3*m_loriginalXImageSize/4;
	m_lImagecy=3*m_loriginalYImageSize/4;
    IsUseRegularScale=TRUE;
    m_nScale=0.75;
    Invalidate();
	m_uiChoice=NORMAL_IMAGE;
}

void CDisplayView::OnUpdateCentySeventyFive(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsHaveImage);
	pCmdUI->SetCheck(m_nScale==0.75&&IsUseRegularScale&&IsHaveImage);
}

void CDisplayView::OnCentyFifty() 
{
	// TODO: Add your command handler code here
	m_lImagecx=m_loriginalXImageSize/2;
	m_lImagecy=m_loriginalYImageSize/2;
    m_nScale=0.5;
	IsUseRegularScale=TRUE;
    Invalidate();
	m_uiChoice=NORMAL_IMAGE;
}

void CDisplayView::OnUpdateCentyFifty(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsHaveImage);
	pCmdUI->SetCheck(m_nScale==0.5&&IsUseRegularScale&&IsHaveImage);
}

void CDisplayView::OnCentyThirty() 
{
	// TODO: Add your command handler code here
	m_lImagecx=3*m_loriginalXImageSize/10;
	m_lImagecy=3*m_loriginalYImageSize/10;
    m_nScale=0.3;
	IsUseRegularScale=TRUE;
    Invalidate();
	m_uiChoice=NORMAL_IMAGE;
}

void CDisplayView::OnUpdateCentyThirty(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsHaveImage);
	pCmdUI->SetCheck(m_nScale==0.3&&IsUseRegularScale&&IsHaveImage);
}

void CDisplayView::OnCentyTwenty() 
{
	// TODO: Add your command handler code here
    m_lImagecx=2*m_loriginalXImageSize/10;
	m_lImagecy=2*m_loriginalYImageSize/10;
    m_nScale=0.2;
	IsUseRegularScale=TRUE;
    Invalidate();
	m_uiChoice=NORMAL_IMAGE;
}

void CDisplayView::OnUpdateCentyTwenty(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsHaveImage);
	pCmdUI->SetCheck(m_nScale==0.2&&IsUseRegularScale&&IsHaveImage);
}

void CDisplayView::OnUpdateImageZoomin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsHaveImage);
	pCmdUI->SetCheck(IsHaveImage&&m_uiChoice==ZOOMIN_IMAGE&&(!IsUseRegularScale));
}

void CDisplayView::OnUpdateImageZoomout(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(IsHaveImage);
  pCmdUI->SetCheck(IsHaveImage&&(m_uiChoice==ZOOMOUT_IMAGE)&&(!IsUseRegularScale));
}

void CDisplayView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(IsHaveImage)
	{
	  if(m_uiChoice==ZOOMIN_IMAGE)
	  {
      m_lImagecx=12*m_lImagecx/10;
	  m_lImagecy=12*m_lImagecy/10;
	  IsUseRegularScale=FALSE;
	  ::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMIN));
   	  Invalidate();
	  }
	  else if(m_uiChoice==ZOOMOUT_IMAGE)
	  {
    	m_lImagecx=10*m_lImagecx/12;
    	m_lImagecy=10*m_lImagecy/12;
    	IsUseRegularScale=FALSE;
	    ::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMOUT));
	    Invalidate();
	  }
      else
	  {
		  ::SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));
	  }
	}
    
	CScrollView::OnLButtonDown(nFlags, point);
}

BOOL CDisplayView::PreCreateWindow(CREATESTRUCT& cs) 
{
   
	return CScrollView::PreCreateWindow(cs);
}


void CDisplayView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDisplayView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CDisplayView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush backBrush(RGB(0, 0, 0)); 
    
    // Save old brush 
    CBrush* pOldBrush = pDC->SelectObject(&backBrush); 
    CRect rect; 
    pDC->GetClipBox(&rect); 
    
    // Erase the area needed 
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY); 
    pDC->SelectObject(pOldBrush); 
    
    return TRUE; 

	//return CScrollView::OnEraseBkgnd(pDC);
}

void CDisplayView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    CMenuDlg dlg;
    dlg.DoModal();
	CScrollView::OnRButtonDown(nFlags, point);
}
