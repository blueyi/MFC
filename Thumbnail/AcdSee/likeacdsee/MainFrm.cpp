// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BigSee.h"


#include "MainFrm.h"
#include "BigSeeView.h"
#include "DisplayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_IMAGE_OPEN, OnImageOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame(): m_lImagecx(450),m_lImagecy(320)//:m_strFilePath(_T(""))
{
	// TODO: add member initialization code here
	m_pCurrentDoc=(CBigSeeDoc*)GetActiveDocument( );

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
    

	//设置工具条显示风格为图标加下方文本方式
	CString strButton;
	CRect rectButton;
	for(int i = 0; i < m_wndToolBar.GetCount(); i++)		//为每个按钮增加文本
	{
		UINT id = m_wndToolBar.GetItemID(i);
		if(!strButton.LoadString(id)) continue;
		int j = strButton.Find(_T('\n'));
		if(j < 0) continue;//used for SEPERATOR
		strButton = strButton.Right(strButton.GetLength() - j - 1);
		m_wndToolBar.SetButtonText(i,strButton); 
	}
	m_wndToolBar.GetItemRect(0,&rectButton);				//调整新的工具条大小
	m_wndToolBar.SetSizes(rectButton.Size(),CSize(16,15));
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	

	return 0;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    //cs.style=~FWS_ADDTOTITLE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!m_wndSplitter.CreateStatic(this,1,2)||!m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CBigSeeView),CSize(64,54),pContext)
	  ||!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CDisplayView),CSize(443,395),pContext))
	 return FALSE;
    return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnImageOpen() 
{
	// TODO: Add your command handler code here
  CString filename;
  CString pathname;
  CString fileExt;
  static char szFilter[]="JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp|GIF(*gif)|(*gif)||";
  CFileDialog dlg(TRUE,"jpg",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
  if(dlg.DoModal()==IDOK)
 	 filename=dlg.GetFileName();
     pathname=dlg.GetPathName();
	 fileExt=dlg.GetFileExt();

 SetWindowText(LPCTSTR(pathname));    
 IPicture*pPicture;
 IStream*pStrm;
 CFileStatus fstatus;
 CFile file;
 LONG cb;

 if(file.Open(filename,CFile::modeRead)&&file.GetStatus(filename,fstatus)&&((cb=fstatus.m_size)!=-1))
 {
	 HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,cb);
	 LPVOID pvData=NULL;
	 CDC*pDC;
	 //get the DC of the CDisplayView
	 CWnd*pPane1=m_wndSplitter.GetPane(0,0);
	 CDisplayView*pDisplayView=static_cast<CDisplayView*>(pPane1);
	
	 pDC=pDisplayView->GetDC();
	 pDisplayView->m_strDisplayFileName=filename;
	 pDisplayView->m_strDisplayFilePath=pathname;
	 pDisplayView->IsHaveImage=TRUE;
     pDisplayView->m_lImagecx=m_lImagecx;
	 pDisplayView->m_lImagecy=m_lImagecy;
	 pDisplayView->m_dwbytes=cb;
     
     CWnd*pPane2=m_wndSplitter.GetPane(0,1);
	 CBigSeeView*pBigSeeView=static_cast<CBigSeeView*>(pPane2);

	 pBigSeeView->m_strFilePath=pathname;
     pBigSeeView->m_strFileName=filename;
     pBigSeeView->m_strFileExt=fileExt;
     pBigSeeView->IsHaveImage=TRUE;
	 pBigSeeView->EnumFiles();
	 
	 if(hGlobal!=NULL)
	 {
		 if((pvData=GlobalLock(hGlobal))!=NULL)
		 {
			 file.Read(pvData,cb);
			 GlobalUnlock(hGlobal);
			 CreateStreamOnHGlobal(hGlobal,TRUE,&pStrm);
		     if(SUCCEEDED(OleLoadPicture(pStrm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPicture)))
			 {
				 OLE_XSIZE_HIMETRIC Width;
				 OLE_YSIZE_HIMETRIC Height;
			     pPicture->get_Width(&Width);
                 pPicture->get_Height(&Height);
                
				 if(FAILED(pPicture->Render(*pDC,0,0,m_lImagecx,m_lImagecy,0,Height,Width,-Height,NULL)))
				  {
					  AfxMessageBox("Failed");
				      pPicture->Release();
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




