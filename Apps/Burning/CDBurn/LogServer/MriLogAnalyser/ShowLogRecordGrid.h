// ShowLogRecordGrid.h: interface for the CShowLogRecordGrid class.
//
//////////////////////////////////////////////////////////////////////
#include "UGC\\ugctrl.h"
#include "UGC\\ugctsarw.h"

#if !defined(AFX_SHOWLOGRECORDGRID_H__51E844F4_945F_4FD8_84F2_EBA0072BAF16__INCLUDED_)
#define AFX_SHOWLOGRECORDGRID_H__51E844F4_945F_4FD8_84F2_EBA0072BAF16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShowLogRecordGrid : public CUGCtrl 
{
public:
	CShowLogRecordGrid();
	virtual ~CShowLogRecordGrid();

private:
	virtual void OnSetup();
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	
private:
	CUGSortArrowType	m_sortArrow;
	CUGCellType         m_normalCellType;
	int					m_sArrowIndex;
	int                 m_normalCellIndex;
	
	int		m_sortCol;
	BOOL	m_sortedAscending;	//TRUE - ½µ
	
private:
	long m_nRows;
	CPen  m_blackPen;
	CFont m_font;

public:
	void Refresh();
	
};

#endif // !defined(AFX_SHOWLOGRECORDGRID_H__51E844F4_945F_4FD8_84F2_EBA0072BAF16__INCLUDED_)
