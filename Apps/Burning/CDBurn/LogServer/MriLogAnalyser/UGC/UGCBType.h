class CUGCheckBoxType: public CUGCellType{

	CPen	Darkpen;
	CPen	Lightpen;
	CPen	Facepen;

	CUGCell m_cell;

public:

	CUGCheckBoxType();
	~CUGCheckBoxType();

	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();

	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnDClicked(int col,long row,RECT *rect,POINT *point);
	virtual BOOL OnCharDown(int col,long row,UINT *vcKey);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,
		int selected,int current);

};