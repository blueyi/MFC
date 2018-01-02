// SeriesList.cpp : implementation file
//

#include "stdafx.h"
#include "QTImage.h"
#include "SeriesList.h"
#include "ImageViewerManager.h"
#include "QTImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesList dialog
extern CQTImageDlg* gpMainDlg;

CSeriesList::CSeriesList(CWnd* pParent /*=NULL*/)
	: CDialog(CSeriesList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeriesList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pManager=NULL;
}


void CSeriesList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeriesList)
	DDX_Control(pDX, IDC_LIST_IMAGE, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeriesList, CDialog)
	//{{AFX_MSG_MAP(CSeriesList)
	ON_WM_SIZE()
	ON_WM_MEASUREITEM()
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMAGE, OnClickListImage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeriesList message handlers

BOOL CSeriesList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD dwExStyle = LVS_EX_FULLROWSELECT ;
	m_list.SetExtendedStyle(dwExStyle);
	m_list.InsertColumn( 0, "Series", LVCFMT_LEFT, 110);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSeriesList::AddSeries()
{
	m_list.AddSeries();
}

void CSeriesList::SetSeriesManager(CSeriesManager *pManager)
{
	m_list.SetSeriesManager(pManager);
	m_pManager=pManager;
}

void CSeriesList::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_list.m_hWnd)
	{
		m_list.MoveWindow(0,0,cx,cy);
	}
}

void CSeriesList::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	m_list.MeasureItem(lpMeasureItemStruct);
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSeriesList::OnClickListImage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CQTImageDlg* pMainDlg = gpMainDlg;
	C2DViewerManager *pViewer2DManager=&pMainDlg->m_view2DManager;
	if(m_list.GetSelectedCount()>0)
	{
		POSITION pos=m_list.GetFirstSelectedItemPosition();
		if(pos) 
		{
			int i = m_list.GetNextSelectedItem(pos);
			vtkImageData *pImage=m_pManager->GetAt(i);
			pViewer2DManager->ShowSeriesInCurWnd(pImage);
		}
	}

	*pResult = 0;
}
