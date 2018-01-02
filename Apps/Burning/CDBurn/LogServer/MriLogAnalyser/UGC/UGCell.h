#define UGCELL_TEXT_SET			1
#define UGCELL_STRING_SET		1
#define UGCELL_MASK_SET			2
#define UGCELL_LABEL_SET		4
#define UGCELL_DATATYPE_SET		8
#define UGCELL_PARAM_SET		16
#define UGCELL_CELLTYPE_SET		32
#define UGCELL_CELLTYPEEX_SET	64
#define UGCELL_TEXTCOLOR_SET	128
#define UGCELL_BACKCOLOR_SET	256
#define UGCELL_HTEXTCOLOR_SET	512
#define UGCELL_HBACKCOLOR_SET	1024
#define UGCELL_BORDERSTYLE_SET	2048
#define UGCELL_BORDER_SET		2048
#define UGCELL_BORDERCOLOR_SET	4096
#define UGCELL_FONT_SET			8192
#define UGCELL_BITMAP_SET 		16384
#define UGCELL_ALIGNMENT_SET	32768
#define UGCELL_EXTRAMEMORY_SET	65536l
#define UGCELL_JOIN_SET			131072l
#define UGCELL_FORMAT_SET		2097152l
#define UGCELL_NOTUSED			4194304l
#define UGCELL_STYLE_SET		8388608l
#define UGCELL_READONLY_SET		16777216l
#define UGCELL_NUMBERDEC_SET	33554432l


#define UGCELLDATA_STRING		1
#define UGCELLDATA_NUMBER		2
#define UGCELLDATA_BOOL			3
#define UGCELLDATA_TIME			4
#define UGCELLDATA_CURRENCY		5


class CUGCtrl;


class CUGCell: public CObject{


protected:

	unsigned long m_propSetFlags;	//one bit is used as a set/unset flag 
									//for each cell property


	CUGCellFormat* m_format;	//CUGCellFormat *m_format;
								//pointer to a format class
								//to validate editing and general setting
								//also used for diplay formating
	
	CUGCell * m_cellStyle;		//CUGCell *m_cellStyle;
								//pointer to a property style cell object

	CString m_string;
	CString m_mask;
	CString m_label;

	short	m_dataType;		//bit level flag - string,date,time,
							//time&date,number,bool,binary, currency
		
	BOOL	m_readOnlyFlag; //TRUE for readonly

	long	m_param;		//general purpose param

	short	m_numDecimals;	//number of decimal points for numbers
	
	int		m_cellType;		//cell type index to use
	long	m_cellTypeEx;	//extended cell type param

	COLORREF m_textColor;	//colors
	COLORREF m_backColor;
	COLORREF m_hTextColor;
	COLORREF m_hBackColor;

	short	 m_borderStyle;	//border
	CPen *	 m_borderColor;

	CFont *	 m_font;	
	CBitmap* m_bitmap;

	short	m_alignment;		//text alignment

	LPBYTE  m_extraMem;		//extra memory pointer
	long	m_extraMemSize;

	short	m_joinOrigin;	//joined cells
	long	m_joinRow;		//relative position
	long	m_joinCol;	

public:

	CUGCell();
	~CUGCell();

	void ClearAll();

	//cell information copying functions
	int		CopyInfoTo(CUGCell *dest);
	int		CopyInfoFrom(CUGCell *source);
	int		CopyCellInfo(CUGCell *src,CUGCell *dest);

	//cell information appending funcitons - only updates items that are set
	int		AddInfoTo(CUGCell *dest);
	int		AddInfoFrom(CUGCell *source);
	int		AddCellInfo(CUGCell *src,CUGCell *dest);

	//
	BOOL	IsPropertySet(long propertyFlag);
	int		ClearPropertySetFlag(long propertyFlag);
	int		ClearProperty(long propertyFlag);
	long	GetPropertyFlags();
	int		SetPropertyFlags(long flags);

	//***** text data type functions *****
	int		SetText(LPCTSTR text);
	int		GetText(CString *text);
	LPCTSTR	GetText();
	int		AppendText(LPCTSTR text);
	int		GetTextLength();

	int		SetMask(LPCTSTR text);
	int		GetMask(CString *text);
	LPCTSTR	GetMask();

	int		SetLabelText(LPCTSTR text);
	int		GetLabelText(CString *text);
	LPCTSTR	GetLabelText();

	//***** BOOL data type functions *****
	int		SetBool(BOOL state);
	BOOL	GetBool();

	//***** Number data type functions *****
	int		SetNumber(double number);
	int		GetNumber(int *number);
	int		GetNumber(long *number);
	int		GetNumber(float *number);
	int		GetNumber(double *number);
	double	GetNumber();

	int		SetNumberDecimals(int number);
	int		GetNumberDecimals();

	//***** Time data type functions *****
	int		SetTime(short second,short minute,short hour,short day,short month,short year);
	int		GetTime(short* second,short* minute,short* hour,short* day,short* month,short* year);
	
	//***** set and get data types
	int		SetDataType(short type);
	int		GetDataType();
	
	int			SetTextColor(COLORREF color);
	COLORREF	GetTextColor();
	int			SetBackColor(COLORREF color);
	COLORREF	GetBackColor();

	int			SetHTextColor(COLORREF color);
	COLORREF	GetHTextColor();
	int			SetHBackColor(COLORREF color);
	COLORREF	GetHBackColor();

	int		SetAlignment(short align);
	short	GetAlignment();

	int		SetBorder(short style);
	short	GetBorder();
	int		SetBorderColor(CPen *pen);
	CPen* 	GetBorderColor();

	int		SetFont(CFont *font);
	CFont *	GetFont();

	int		SetBitmap(CBitmap *bitmap);
	CBitmap* GetBitmap();

	//read-only flag
	int		SetReadOnly(BOOL state);
	BOOL	GetReadOnly();

	//style type settings
	int		SetCellType(int index);
	int		GetCellType();

	int		SetCellTypeEx(long type);
	long	GetCellTypeEx();

	//extra cell information
	void *	AllocExtraMem(long len);
	void *	GetExtraMemPtr();
	long	GetExtraMemSize();
	int		ClearExtraMem();

	//join information
	int SetJoinInfo(BOOL origin,int col,long row);
	int GetJoinInfo(BOOL *origin,int *col,long *row);

	//formating and validation
	int		SetFormatClass(CUGCellFormat * format);
	CUGCellFormat*	GetFormatClass();

	int		SetCellStyle(CUGCell *cell);
	CUGCell * GetCellStyle();

	//conversion functions
	int StringToNumber(CString *string,double *number);
	int StringToBool(CString *string,BOOL * state);
	int StringToTime(CString *string,int *second,int *minute,int *hour,
		int *day,int *month,int *year);	

	//defaults
	int SetDefaultInfo();

	//set/get the general param
	int SetParam(long param);
	long GetParam();
};
