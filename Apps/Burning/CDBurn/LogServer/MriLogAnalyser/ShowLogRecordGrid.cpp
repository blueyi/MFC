// ShowLogRecordGrid.cpp: implementation of the CShowLogRecordGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MriLogAnalyser.h"
#include "ShowLogRecordGrid.h"
#include "DataManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
#define NUM_COLUMNS	10
/*
static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("日期"),
	_T("时间"),
	_T("Study ID"),  
	_T("Series ID"),
	_T("序列名称"), 
	_T("线圈类型"),
	_T("发射增益(TG)"),
	_T("接收增益(RG)"),
	_T("频率偏移(O1,Hz)"),
	_T("中心频率(SF,MHz)"),
};
*/
static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("Date"),
	_T("Time"),
	_T("Study ID"),  
	_T("Series ID"),
	_T("Sequence Name"), 
	_T("Coil Type"),
	_T("TG"),
	_T("RG"),
	_T("O1(Hz)"),
	_T("SF(MHz)"),
};

static int _gnColumnFmt[NUM_COLUMNS] = 
{
	UG_ALIGNCENTER, 
	UG_ALIGNCENTER,
	UG_ALIGNCENTER,
	UG_ALIGNCENTER,
	UG_ALIGNCENTER,
	UG_ALIGNCENTER,
	UG_ALIGNRIGHT,
	UG_ALIGNRIGHT,
	UG_ALIGNRIGHT,
	UG_ALIGNRIGHT,
};
static int _gnColumnWidth[NUM_COLUMNS] = 
{
	120,
	120,
	120,
	120,
	120,
	120,
	120,
	120,
	120,
	120,
};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShowLogRecordGrid::CShowLogRecordGrid()
{

}

CShowLogRecordGrid::~CShowLogRecordGrid()
{

}

void CShowLogRecordGrid::OnSetup()
{
	int rows = 1;
	int cols = NUM_COLUMNS;

	m_font.CreateFont( 14,0,0,0,500,0,0,0,0,0,0,0,0,"Arial" );
	SetDefFont(&m_font);
	
	m_sArrowIndex = AddCellType(&m_sortArrow);
	m_normalCellIndex = AddCellType(&m_normalCellType);
	SetUniformRowHeight(TRUE);

	CUGCell cell;
	GetGridDefault( &cell );
	cell.SetAlignment(UG_ALIGNLEFT);
	cell.SetHBackColor( RGB(0,0,0)/*RGB(255,192,192)*/);
	cell.SetHTextColor( RGB(255,255,255));
//	cell.SetBackColor( RGB(255,255,255));
	cell.SetTextColor( RGB(0,0,255));
	SetGridDefault( &cell );

	SetNumberRows(rows);
	SetNumberCols(cols);

	SetVScrollMode(UG_SCROLLTRACKING);

	SetBallisticMode(3);
	SetBallisticDelay(100);

	m_blackPen.CreatePen(PS_SOLID,1,RGB(100,100,100));

	SetCurrentCellMode(2);

	SetColWidth( -1, 50 );
	for ( int i=0; i< NUM_COLUMNS; i++ )
	{
		SetColWidth( i, _gnColumnWidth[i] );
	}
	SetDoubleBufferMode(1);

/*
	QuickSetCellType(m_sortCol,-1,m_sArrowIndex);
	QuickSetCellTypeEx(m_sortCol,-1,UGCT_SORTARROWDOWN);
*/

}

void CShowLogRecordGrid::OnGetCell(int col,long row,CUGCell *cell)
{
	CString temp;

	if (row < 0)
	{
		// Title
		cell->SetBackColor( GetSysColor( COLOR_BTNFACE ) );

		if (col < 0)
		{
			temp = "编号";
		}
		else if ( col >=0 && col < NUM_COLUMNS )
		{
			temp = _gszColumnLabel[col];	
		}
	}
	else
	{
		if ( col == -1 )
		{	// 编号
			cell->SetBackColor( GetSysColor( COLOR_BTNFACE ) );
			cell->SetAlignment( UG_ALIGNCENTER );
		}
		else
		{
			cell->SetBackColor( RGB(255,255,255) );
			cell->SetAlignment( _gnColumnFmt[col] );
		}
		
		if ( CDataManager::GetHandle().m_vShownRecords.size() == 0 
			|| row >= CDataManager::GetHandle().m_vShownRecords.size() )
		{
			return;
		}
				
		switch(col)
		{
			case -1:// 编号
				temp.Format( "%d", row + 1 );
				break;
				
			case 0:// Date
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sDate;
				break;
			case 1:// Time
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sTime;
				break;
			case 2:// Study ID
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sStudyID;
				break;
			case 3:// Series ID
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sSeriesID;
				break;
			case 4:// Sequence Name
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sSequenceName;
				break;
			case 5:// Coil Type
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sCoilType;
				break;							
			case 6:// TG
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sTG;
				break;							
			case 7:// RG
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sRG;
				break;							
			case 8:// O1
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sO1;
				break;
			case 9:// SF
				temp = CDataManager::GetHandle().m_vShownRecords[row]->sSF;
				break;
				
			default:
				temp = "";
				break;
		}
	}

	cell->SetText(temp);

	if ( row >= 0 && col >= 0 )
	{
//		cell->SetTextColor( GetAlmColorBySTypCode( m_vAlmRecLstLnk[  m_vAlmLstIdx[row]  ].nAlmStyp ) );
	}
}

void CShowLogRecordGrid::Refresh()
{
	SetNumberRows( CDataManager::GetHandle().m_vShownRecords.size() );
}

void CShowLogRecordGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	
	if(updn == 0) return;
}
