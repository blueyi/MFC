class CUGCellType: public CObject{

protected:
	BOOL	m_canTextEdit;		//allow inline editing
	BOOL	m_drawLabelText;	//draw the label instead of the string
	BOOL	m_canOverLap;		//can the cell overlap over cells
	double	m_dScaleFactor;

	CUGCtrl		*	m_ctrl;		//pointer to the main class
	
	friend CUGCtrl;

	int		m_ID;				//ID which is the index in the celltype list


public:

	//general purpose routines
	int DrawBitmap(CDC *dc,CBitmap * bitmap,RECT *rect,COLORREF backcolor);
	void DrawBorder(CDC *dc,RECT *rect,RECT *rectout,CUGCell * cell);
	void DrawText(CDC *dc,RECT *rect,int offset,int col,long row,CUGCell *cell,
		int selected,int current);
	int GetCellOverlapInfo(CDC* dc,int col,long row,int *overlapCol,CUGCell *cell);

public:

	CUGCellType();
	virtual ~CUGCellType();

	//cell type information
	int 	GetID();
	void	SetID(int ID);

	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();

	//text editing functions
	BOOL CanTextEdit();
	int SetTextEditMode(int mode); // TRUE and FALSE

	//cell overlapping
	BOOL CanOverLap(CUGCell *cell);

	//drawing setup functions
	int DrawTextOrLabel(int mode); // 0-text 1-label
	int SetDrawScale(float scale);
	
	//virtual functions
	virtual int GetEditArea(RECT *rect);

	virtual int SetOption(long option,long param);
	virtual int GetOption(long option,long* param);

	virtual int OnSystemChange();

	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnRClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnDClicked(int col,long row,RECT *rect,POINT *point);

	virtual BOOL OnKeyDown(int col,long row,UINT *vcKey);
	virtual BOOL OnCharDown(int col,long row,UINT *vcKey);

	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT nFlags);
	
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,
		int selected,int current);

	virtual void OnPrint(CDC *dc,RECT *rect,int col,long row,CUGCell *cell);

	virtual void OnSetFocus(int col,long row,CUGCell *cell);
	virtual void OnKillFocus(int col,long row,CUGCell *cell);

	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};