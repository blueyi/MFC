// Demo_DevStudioView.cpp : implementation of the CDemo_DevStudioView class
//

#include "stdafx.h"
#include "Demo_DevStudio.h"

#include "Demo_DevStudioDoc.h"
#include "Demo_DevStudioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioView

IMPLEMENT_DYNCREATE(CDemo_DevStudioView, CHtmlView)

BEGIN_MESSAGE_MAP(CDemo_DevStudioView, CHtmlView)
	//{{AFX_MSG_MAP(CDemo_DevStudioView)
	ON_COMMAND(ID_WEBBACK, OnWebback)
	ON_COMMAND(ID_WEBFORWARD, OnWebforward)
	ON_COMMAND(ID_WEBHOME, OnWebhome)
	ON_COMMAND(ID_WEBREFRESH, OnWebrefresh)
	ON_COMMAND(ID_WEBSTOP, OnWebstop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioView construction/destruction

CDemo_DevStudioView::CDemo_DevStudioView()
{
	// TODO: add construction code here

}

CDemo_DevStudioView::~CDemo_DevStudioView()
{
}

BOOL CDemo_DevStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioView drawing

void CDemo_DevStudioView::OnDraw(CDC* pDC)
{
	CDemo_DevStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CDemo_DevStudioView::OnInitialUpdate() 
{
	//TODO: This code navigates to a popular spot on the web.
	//Change the code to go where you'd like.
#if _MSC_VER >= 1200
	CString csURL;
	csURL.LoadString(IDS_ARTICLE_URL);
	Navigate2(csURL,NULL,NULL);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioView printing


/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioView diagnostics

#ifdef _DEBUG
void CDemo_DevStudioView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CDemo_DevStudioView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CDemo_DevStudioDoc* CDemo_DevStudioView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo_DevStudioDoc)));
	return (CDemo_DevStudioDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioView message handlers

void CDemo_DevStudioView::OnWebhome() 
{
#if _MSC_VER >= 1200
	CString csURL;
	csURL.LoadString(IDS_HOME_URL);
	Navigate2(csURL,NULL,NULL);
#endif
}

void CDemo_DevStudioView::OnWebback() 
{
#if _MSC_VER >= 1200
	GoBack();	
#endif
}

void CDemo_DevStudioView::OnWebforward() 
{
#if _MSC_VER >= 1200
	GoForward();
#endif
}

void CDemo_DevStudioView::OnWebstop() 
{
#if _MSC_VER >= 1200
	Stop();
#endif
}

void CDemo_DevStudioView::OnWebrefresh() 
{
#if _MSC_VER >= 1200
	Refresh();
#endif
}
