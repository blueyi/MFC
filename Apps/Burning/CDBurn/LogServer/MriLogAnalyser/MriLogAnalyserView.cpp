// MriLogAnalyserView.cpp : implementation of the CMriLogAnalyserView class
//

#include "stdafx.h"
#include "MriLogAnalyser.h"

#include "MriLogAnalyserDoc.h"
#include "MriLogAnalyserView.h"
#include "DataManager.h"
#include "SetQueryingConditionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserView

IMPLEMENT_DYNCREATE(CMriLogAnalyserView, CFormView)

BEGIN_MESSAGE_MAP(CMriLogAnalyserView, CFormView)
	//{{AFX_MSG_MAP(CMriLogAnalyserView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_SET_WORKING_FOLDER, OnBtnSetWorkingFolder)
	ON_BN_CLICKED(IDC_BTN_SET_QUERYING_TIME, OnBtnSetQueryingTime)
	ON_COMMAND(ID_MENU_SET_WORKING_FOLDER, OnMenuSetWorkingFolder)
	ON_COMMAND(ID_MENU_SET_QUERY_LOG_RECORD, OnMenuSetQueryLogRecord)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_SEQUENCE_TYPE, OnSelchangeComboSequenceType)
	ON_CBN_SELCHANGE(IDC_COMBO_COIL_TYPE, OnSelchangeComboCoilType)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserView construction/destruction

CMriLogAnalyserView::CMriLogAnalyserView()
	: CFormView(CMriLogAnalyserView::IDD)
{
	//{{AFX_DATA_INIT(CMriLogAnalyserView)
	m_sCoilType = _T("");
	m_sSequenceType = _T("");
	m_sUserName = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMriLogAnalyserView::~CMriLogAnalyserView()
{
}

void CMriLogAnalyserView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMriLogAnalyserView)
	DDX_Control(pDX, IDC_STATIC_DRAW_CURVE_O1, m_staticDrawCurveO1);
	DDX_Control(pDX, IDC_COMBO_SEQUENCE_TYPE, m_ctrlSequenceype);
	DDX_Control(pDX, IDC_COMBO_COIL_TYPE, m_ctrlCoilType);
	DDX_Control(pDX, IDC_STATIC_LIST_AREA, m_ctrlListArea);
	DDX_CBString(pDX, IDC_COMBO_COIL_TYPE, m_sCoilType);
	DDX_CBString(pDX, IDC_COMBO_SEQUENCE_TYPE, m_sSequenceType);
	DDX_Text(pDX, IDC_EDIT_USER, m_sUserName);
	//}}AFX_DATA_MAP
}

BOOL CMriLogAnalyserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMriLogAnalyserView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CDataManager::GetHandle().ReadOptionsFromFile();
	CString sTitle;
	sTitle.Format( "Log Folder: %s", CDataManager::GetHandle().m_sWorkDirectory );
	m_pDocument->SetTitle( sTitle );

	m_o2DCurve_O1.setOwner( &m_staticDrawCurveO1 );
	m_o2DCurve_O1.setTitle( "The curve for spectrometer center frequency (O1+SF,Hz)" );
	m_o2DCurve_O1.setBGColor( RGB(255,0,0) );
}

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserView printing

BOOL CMriLogAnalyserView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMriLogAnalyserView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMriLogAnalyserView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMriLogAnalyserView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserView diagnostics

#ifdef _DEBUG
void CMriLogAnalyserView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMriLogAnalyserView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMriLogAnalyserDoc* CMriLogAnalyserView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMriLogAnalyserDoc)));
	return (CMriLogAnalyserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserView message handlers

int CMriLogAnalyserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	RECT	rect;
	GetClientRect(&rect);
	
	rect.top+= 50;
	m_oShowLogRecordGrid.CreateGrid( WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_BORDER,
		rect, this,12345);
	
	return 0;
}

void CMriLogAnalyserView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT rect1;
	int iHeight;
	
	if ( m_oShowLogRecordGrid.m_hWnd && m_ctrlListArea.m_hWnd )
	{
		m_ctrlListArea.GetClientRect( &rect1 );
		iHeight = cy - (rect1.bottom+10) - (cy-(rect1.bottom+10))/2;
		m_oShowLogRecordGrid.SetWindowPos( NULL, 
			0+2, rect1.bottom+10, cx-4, iHeight, SWP_NOZORDER );

		m_ctrlListArea.ShowWindow( SW_HIDE );
	}	

	if ( m_staticDrawCurveO1.m_hWnd )
	{
		iHeight = cy-(rect1.bottom+10) - (cy-(rect1.bottom+10))/2;
		m_staticDrawCurveO1.SetWindowPos( NULL, 
			0+2, rect1.bottom+30+iHeight, cx-4, iHeight-2, SWP_NOZORDER );
	}
}

void CMriLogAnalyserView::OnBtnSetWorkingFolder() 
{
	CString str, sWorkDirectory;
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.lpszTitle="Select Log Folder:";
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)
	{
		return;
	}
	
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	
	int nSize = strlen(str);// add "\" on the filepath
	if ( nSize > 3)
	{
		sWorkDirectory = str.GetBuffer(str.GetLength());
		sWorkDirectory +="\\";
	}
	else
	{
		sWorkDirectory = str.GetBuffer(str.GetLength());
	}
		
	CDataManager::GetHandle().m_sWorkDirectory = sWorkDirectory;
	
	// 保存设置
	CDataManager::GetHandle().WriteOptionsToFile();

	CString sTitle;
	sTitle.Format( "Log Folder: %s", CDataManager::GetHandle().m_sWorkDirectory );
	m_pDocument->SetTitle( sTitle );
}

void CMriLogAnalyserView::OnBtnSetQueryingTime() 
{
	CSetQueryingConditionDlg oSetQueryingConditionDlg;
	
	oSetQueryingConditionDlg.m_sStartDate = CDataManager::GetHandle().m_sStartDate;
//	oSetQueryingConditionDlg.m_sStartTime = CDataManager::GetHandle().m_sStartTime;
	oSetQueryingConditionDlg.m_sEndDate = CDataManager::GetHandle().m_sEndDate;
//	oSetQueryingConditionDlg.m_sEndTime = CDataManager::GetHandle().m_sEndTime;

	if ( oSetQueryingConditionDlg.DoModal() == IDOK )
	{
		CDataManager::GetHandle().m_sStartDate = oSetQueryingConditionDlg.m_sStartDate;
//		CDataManager::GetHandle().m_sStartTime = oSetQueryingConditionDlg.m_sStartTime;
		CDataManager::GetHandle().m_sEndDate = oSetQueryingConditionDlg.m_sEndDate;
//		CDataManager::GetHandle().m_sEndTime = oSetQueryingConditionDlg.m_sEndTime;
		
		// 保存设置
		CDataManager::GetHandle().WriteOptionsToFile();

		// 查询Log记录
		BeginWaitCursor();
		CDataManager::GetHandle().ReadLogRecordFromFile();
		EndWaitCursor();

		// 显示Log记录
		InsertToComboBox();
		InsertToGrid();
		DrawCurve_O1();		
	}
}

void CMriLogAnalyserView::OnMenuSetWorkingFolder() 
{
	OnBtnSetWorkingFolder();	
}

void CMriLogAnalyserView::OnMenuSetQueryLogRecord() 
{
	OnBtnSetQueryingTime();
}

void CMriLogAnalyserView::InsertToComboBox()
{
	// Institute name
	UpdateData( TRUE );
	m_sUserName = CDataManager::GetHandle().m_sNameOfInstitution;
	UpdateData( FALSE );
	
	// Sequence Name
	m_ctrlSequenceype.ResetContent();
	for ( std::map<CString,CString>::iterator iter = CDataManager::GetHandle().m_mSequenceName.begin();
	iter != CDataManager::GetHandle().m_mSequenceName.end(); ++iter )
    {
        m_ctrlSequenceype.InsertString( m_ctrlSequenceype.GetCount(), (*iter).second );
    }
	m_ctrlSequenceype.SetCurSel( 0 );
	
	// Coil Type
	m_ctrlCoilType.ResetContent();
	for ( std::map<CString,CString>::iterator iter1 = CDataManager::GetHandle().m_mCoilType.begin();
	iter1 != CDataManager::GetHandle().m_mCoilType.end(); ++iter1 )
    {
        m_ctrlCoilType.InsertString( m_ctrlCoilType.GetCount(), (*iter1).second );
    }
	m_ctrlCoilType.SetCurSel( 0 );
}

void CMriLogAnalyserView::InsertToGrid()
{
	m_oShowLogRecordGrid.Refresh();
}

void CMriLogAnalyserView::DrawCurve_O1()
{
	// 准备数据
	int iRecordCount = CDataManager::GetHandle().m_vShownRecords.size();

	double* X = new double[iRecordCount];
	double* Y = new double[iRecordCount];
	
	if ( iRecordCount == 0 )
	{
		m_o2DCurve_O1.plot( X, Y, 0 );
		m_o2DCurve_O1.draw();
	
		// 释放内存
		if(X)
		{
			delete []X;
		}
		if(Y)
		{
			delete []Y;
		}	

		return;
	}
	
	int nMax = -999999999;
	int nMin =  999999999;

	for( int i=0; i< iRecordCount; i++ )
	{
		X[i] = i + 1;
		Y[i] = atoi( CDataManager::GetHandle().m_vShownRecords[i]->sO1 ) 
			+ atoi( CDataManager::GetHandle().m_vShownRecords[i]->sSF ) * 1000000;
		
		if( nMax < Y[i] )
		{
			nMax = Y[i];
		}
		if( nMin > Y[i] )
		{
			nMin = Y[i];
		}
	}
	
	// 画曲线图
	m_o2DCurve_O1.setXRange( 1, iRecordCount );
	m_o2DCurve_O1.setYRange( nMin, nMax );
	
	int XTickNum;
	if ( (iRecordCount/50*2) > 0 )
	{
		XTickNum = iRecordCount / (iRecordCount/50*2);
	}
	else if ( iRecordCount >= 2 )
	{
		XTickNum = iRecordCount-1;
	}
	else  if ( iRecordCount == 1 )
	{
		XTickNum = 1;
	}
	int YTickNum = 5;
	m_o2DCurve_O1.setDivs( XTickNum, YTickNum );
	
	m_o2DCurve_O1.plot( X, Y, iRecordCount );

	// 释放内存
	if(X)
	{
		delete []X;
	}
	if(Y)
	{
		delete []Y;
	}	
}

void CMriLogAnalyserView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	DrawCurve_O1();

}

void CMriLogAnalyserView::OnSelchangeComboSequenceType() 
{
	CString sSequenceType;
	int nIndex = m_ctrlSequenceype.GetCurSel();
	m_ctrlSequenceype.GetLBText( nIndex, sSequenceType );
	
	for ( int i=0; i< CDataManager::GetHandle().m_vRecords_ScanParams.size(); i++ )
	{
		if ( sSequenceType == "All" )
		{
			CDataManager::GetHandle().m_vRecords_ScanParams[i].bShowBySeqName = true;
		}
		else
		{
			if ( CDataManager::GetHandle().m_vRecords_ScanParams[i].sSequenceName == sSequenceType )
			{
				CDataManager::GetHandle().m_vRecords_ScanParams[i].bShowBySeqName = true;			
			}
			else
			{
				CDataManager::GetHandle().m_vRecords_ScanParams[i].bShowBySeqName = false;			
			}
		}
	}

	CDataManager::GetHandle().GetShownRecords();
	
	// 显示Log记录
	InsertToGrid();
	DrawCurve_O1();	
}

void CMriLogAnalyserView::OnSelchangeComboCoilType() 
{
	CString sCoilType;
	int nIndex = m_ctrlCoilType.GetCurSel();
	m_ctrlCoilType.GetLBText( nIndex, sCoilType );
	
	for ( int i=0; i< CDataManager::GetHandle().m_vRecords_ScanParams.size(); i++ )
	{
		if ( sCoilType == "All" )
		{
			CDataManager::GetHandle().m_vRecords_ScanParams[i].bShowByCoilType = true;
		}
		else
		{
			if ( CDataManager::GetHandle().m_vRecords_ScanParams[i].sCoilType == sCoilType )
			{
				CDataManager::GetHandle().m_vRecords_ScanParams[i].bShowByCoilType = true;
			}
			else
			{
			CDataManager::GetHandle().m_vRecords_ScanParams[i].bShowByCoilType = false;
			}
			
		}
	}

	CDataManager::GetHandle().GetShownRecords();
	
	// 显示Log记录
	InsertToGrid();
	DrawCurve_O1();	
}
