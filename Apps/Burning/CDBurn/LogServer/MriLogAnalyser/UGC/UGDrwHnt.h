//drawing hint linked list structure
typedef struct UGDrwHintListTag{
	int startCol;
	long startRow;
	int endCol;
	long endRow;
	
	UGDrwHintListTag * next;

}UGDrwHintList;

typedef struct UGDrwHintVListTag{
	int Col;
	long Row;
	
	UGDrwHintVListTag * next;

}UGDrwHintVList;




//drawing hint class
class CUGDrawHint{

private:

	UGDrwHintList * m_List;
	UGDrwHintVList * m_VList;

	int  m_minCol,m_maxCol;
	long m_minRow,m_maxRow;

	int  m_vMinCol,m_vMaxCol;
	long m_vMinRow,m_vMaxRow;

public:
	CUGDrawHint();
	~CUGDrawHint();

	void AddHint(int col,long row);
	void AddHint(int startCol,long startRow,int endCol,long endRow);

	void AddToHint(int col,long row);
	void AddToHint(int startCol,long startRow,int endCol,long endRow);
	void ClearHints();

	int IsInvalid(int col,long row);
	int IsValid(int col,long row);
	int GetTotalRange(int *startCol,long *startRow,int *endCol,long *endRow);

	void SetAsValid(int col,long row);
	void SetAsValid(int startCol,long startRow,int endCol,long endRow);
};