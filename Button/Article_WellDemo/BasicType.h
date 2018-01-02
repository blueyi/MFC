#if !defined(AFX_BASICTYPE__INCLUDED_)
#define AFX_BASICTYPE__INCLUDED_


#define SVIZ_E 0.0001
#define PI 	3.1415926536


//SVizProperty ID 6000-6050 reserved. Customized ID start at 6051 please

#define ID_PROPERTY_BASIC_BRUSH 6000
#define ID_PROPERTY_BRUSH		6001
#define ID_PROPERTY_PEN			6002
#define ID_PROPERTY_TEXT        6004
#define ID_PROPERTY_ARROW       6003
#define ID_PROPERTY_RICHTEXT    6005
#define ID_PROPERTY_LABEL		6006
#define ID_PROPERTY_PERSPECTIVE 6007

#if defined _AFXDLL && !defined _SVIZ_STATIC_
	#ifdef _SVIZ_
	   #define SVIZDLLEXPORT  _declspec(dllexport)
	#else
	   #define SVIZDLLEXPORT  _declspec(dllimport)
	#endif
#else
	#define SVIZDLLEXPORT
#endif


#define _FASTDRAW

#if _MSC_VER >= 1300
	#define WPD_CHARFORMAT CHARFORMAT2
	#define WPD_PARAFORMAT PARAFORMAT2
#else
	#define WPD_CHARFORMAT CHARFORMAT
	#define WPD_PARAFORMAT PARAFORMAT
#endif

struct SVIZDLLEXPORT CCharFormat : public WPD_CHARFORMAT
{
	CCharFormat() {cbSize = sizeof(WPD_CHARFORMAT);}
	BOOL operator==(CCharFormat& cf);
};

SVIZDLLEXPORT typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
} ColourTableEntry;

struct SVIZDLLEXPORT FOCUSHEADINFO
{
	UINT pObj;
	POINT point;
};


SVIZDLLEXPORT enum ArrowType {
	NoAnchor		= 0x10,   //LineCap::LineCapNoAnchor
	SquareAnchor	= 0x11,   //LineCap::LineCapSquareAnchor
	RoundAnchor     = 0x12,   //LineCap::LineCapRoundAnchor
	DimondAnchor	= 0x13,   //LineCap::LineCapDimondAnchor
	ArrowAnchor		= 0x14,
	OpenAnchor		= 0xF1,
	StealthAnchor   = 0xF2,
	UpStealthAnchor = 0xF3,
	LowStealthAnchor   = 0xF4,
	CustomAnchor    = 0xFF    //LineCap::LineCapNoAnchor
};

/*
struct BRUSHPROPERTY {

	BrushType					m_brushType;
	
	Color  						m_Color1,
								m_Color2; //when hatch pattern used, this is backgroun Color
								
	BYTE						bFill;

	union {
		LinearGradientMode		m_linearGradientMode; //for linear gradient only;
		HatchStyle				m_hatchStyle;
		WrapMode				m_wrapMode;
	} m_Mode;

	union {
		BYTE					m_bToCenter; //0, - center path gradient.
		BYTE					m_nStretch;
	} m_style;

	CString						m_ImageName;
};

*/



#define BRUSHSTYLE_STRETCH				0x0001
#define BRUSHSTYLE_CENTER				0x0002
#define BRUSHSTYLE_USEBOUND				0x0004
#define BRUSHSTYLE_ROUNDBOUND			0x0008
#define	BRUSHSTYLE_PATHCENTER			0x0010
#define BRUSHSTYLE_GAMMA				0X0020
#define BRUSHSTYLE_CUSTOMEPATH			0x0040
#define BRUSHSTYLE_CUSTOMEINNERPATH		0x0080

#define PENSYTLE_CUSTOMDASH				0x0001











#endif
