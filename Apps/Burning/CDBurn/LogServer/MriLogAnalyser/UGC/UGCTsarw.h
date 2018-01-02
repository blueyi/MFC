#ifndef UGCT_SORTARROW
#define UGCT_SORTARROW

//celltype notifications
#define UGCT_SORTARROWUP	16
#define UGCT_SORTARROWDOWN	32



class CUGSortArrowType: public CUGCellType{

	int m_ArrowWidth;

public:

	CUGSortArrowType();
	~CUGSortArrowType();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
};

#endif
//
