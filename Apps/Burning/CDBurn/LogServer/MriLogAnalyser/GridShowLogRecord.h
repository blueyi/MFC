#include "UGC\\ugctrl.h"
#include "UGC\\ugctsarw.h"

#if !defined(___GRID_SHOW_LOG_RECORD_H___)
#define ___GRID_SHOW_LOG_RECORD_H___

class CGridShowLogRecord : public CUGCtrl
{

public:
	CUGSortArrowType	m_sortArrow;
	CUGCellType         m_normalCellType;
	int					m_sArrowIndex;
	int                 m_normalCellIndex;
	BOOL                m_bMuteFlag;
	
	int		m_sortCol;
	BOOL	m_sortedAscending;//TRUE - Ωµ

public:
	void Refresh();

	CGridShowLogRecord();
	~CGridShowLogRecord();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CGridShowLogRecord)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	virtual void OnSetup();
	virtual void OnGetCell(int col,long row,CUGCell *cell);

	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	
public:
	long m_nRows;
	CPen  m_blackPen;
	CFont m_font;

/*
	vAlmLstLnk		m_vAlmRecLstLnk;
	vector<int>		m_vAlmLstIdx;
	int             *m_pAlmLstIdx;	// ”√”⁄≈≈–Ú
*/
	
	
};

#endif