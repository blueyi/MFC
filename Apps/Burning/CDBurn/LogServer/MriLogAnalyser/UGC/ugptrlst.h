class CUGPtrList: public CObject{

protected:
	
	typedef struct UGPtrListTag{
		BOOL    isUsed;
		LPVOID	pointer;
		long	param;
		UGID	id;
	}UGPtrList;

	UGPtrList * m_arrayPtr;

	int		m_maxElements;
	int		m_elementsUsed;

	int AddMoreElements();

public:

	CUGPtrList();
	~CUGPtrList();

	int AddPointer(void *ptr,long param = 0,UGID *id = NULL);
	
	LPVOID GetPointer(int index);
	long GetParam(int index);
	UGID* GetUGID(int index);

	int GetPointerIndex(void * ptr);

	int UpdateParam(int index,long param);

	int DeletePointer(int index);
	int EmptyList();

	int GetCount();
	int GetMaxCount();

	int InitEnum();
	void *EnumPointer();
};
