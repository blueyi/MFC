#if !defined(AFX_COLOURPICKER_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
#define AFX_COLOURPICKER_H__D0B75901_9830_11D1_9C0F_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "ColourPopupWnd.h"
#define GRADIENTFILL 0x01
#define PATTERNFILL  0x02
#define PICTUREFILL  0x04
/////////////////////////////////////////////////////////////////////////////
// CColourPicker window

void AFXAPI DDX_ColourPicker(CDataExchange *pDX, int nIDC, COLORREF& crColour);

/////////////////////////////////////////////////////////////////////////////
// CColourPicker window

#define CP_MODE_TEXT 1  // edit text colour
#define CP_MODE_BK   2  // edit background colour (default)

#define CP_MODE_LINE  3  // gdi+, pen effect
#define CP_MODE_BRUSH 4  // gdi+, brush effect

//#include "SVizDrawProperty.h"

Color SetA(Color &c,	BYTE a);

class SVIZDLLEXPORT CColourPicker : public CButton
{
// Construction
public:
    CColourPicker();
    DECLARE_DYNCREATE(CColourPicker);

// Attributes
public:
    COLORREF GetColour();
    void     SetColour(COLORREF crColour); 

    void     SetDefaultText(LPCTSTR szDefaultText);
    void     SetCustomText(LPCTSTR szCustomText);

    void     SetTrackSelection(BOOL bTracking = TRUE)  { m_bTrackSelection = bTracking; }
    BOOL     GetTrackSelection()                       { return m_bTrackSelection; }

    void     SetSelectionMode(UINT nMode)              { m_nSelectionMode = nMode; }
    UINT     GetSelectionMode()                        { return m_nSelectionMode; };

    void     SetBkColour(COLORREF crColourBk);
    COLORREF GetBkColour()                             { return m_crColourBk; }
    
    void     SetTextColour(COLORREF crColourText);
    COLORREF GetTextColour()                           { return m_crColourText;}

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPicker)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CColourPicker();

protected:
    void SetWindowSize();

// protected attributes
protected:
    BOOL     m_bActive,                // Is the dropdown active?
             m_bTrackSelection;        // track colour changes?
    COLORREF m_crColourBk;
    COLORREF m_crColourText;
	COLORREF m_defalultColor;
    UINT     m_nSelectionMode;
    CRect    m_ArrowRect;

//	CSVizBrushProperty	m_BrushProperty;

	Color  						m_brushColor; //when hatch pattern used, this is foreColor

	BYTE						m_Alpha; //for alpha blending; when 00 totally transparent
									    // when 0xFF, totally opage
	DWORD						m_style;
	
	BrushType					m_brushType;
	
	Color  						m_gradientColor; //when hatch pattern used, this is backgroun Color
								
	LinearGradientMode			m_linearGradientMode; //for linear gradient only;
	
	HatchStyle					m_hatchStyle;

	CString						m_fillImage; //source image name

	WrapMode					m_wrapMode;

	PointF						m_Center;



public:

    CString				m_strDefaultText,
						m_strCustomText,
						m_strEffectText,
						m_strNoText;

//GDI+
	BOOL	            m_noColor;
	int					m_effectpage;  // 0, no effect, 1: effect page for Pen only, 2: effect page for Brush

	
	
	//wrap of m_BrushProperty
	
	virtual Color				GetColor1(){ return m_brushColor;}
	virtual void				SetColor1(Color color){m_brushColor = color;}
	virtual void				SetColor1(COLORREF color){	Color c;
															c.SetFromCOLORREF(color);
															SetA (c,0xFF);
															m_brushColor = c;
														}

	virtual Color				GetColor2(){ return m_gradientColor;}
	virtual void				SetColor2(Color color){m_gradientColor = color;}
	virtual void				SetColor2(COLORREF color){	Color c;
															c.SetFromCOLORREF(color);
															SetA (c,0xFF);
															m_gradientColor = c;
														}

	virtual BrushType			GetBrushType(){ return m_brushType;}
	virtual void				SetBrushType(BrushType style){m_brushType = style;}

	virtual LinearGradientMode	GetLinearGradientMode(){ return m_linearGradientMode;}
	virtual void				SetLinearGradientMode(LinearGradientMode mode){m_linearGradientMode = mode;}
	 
	virtual HatchStyle			GetHatchStyle(){ return m_hatchStyle;}
	virtual void				SetHatchStyle(HatchStyle style){m_hatchStyle =style;}

	virtual WrapMode			GetWrapMode(){ return m_wrapMode;}
	virtual void				SetWrapMode(WrapMode mode){m_wrapMode = mode;}


	virtual CString				GetImageName(){ return m_fillImage;}
	virtual void				SetImageName(CString name){m_fillImage = name;}

	virtual BYTE				GetAlpha(){ return m_Alpha;}
	virtual void				SetAlpha(BYTE t){m_Alpha = t;}

	virtual UINT				GetToCenter		()const{ if (m_style & BRUSHSTYLE_CENTER) return 1;
															 else return 0;}


	virtual void				SetToCenter		(BOOL b = TRUE)	{ if (b) m_style = m_style | BRUSHSTYLE_CENTER;
															else m_style = m_style &(0xFFFFFFFF^BRUSHSTYLE_CENTER);}

	virtual UINT				GetStretch		()const{ if (m_style & BRUSHSTYLE_STRETCH) return 1;
															else return 0;}


	virtual void				SetStretch		(BOOL b = TRUE){ if (b) m_style = m_style | BRUSHSTYLE_STRETCH;
															else m_style = m_style &(0xFFFFFFFF^BRUSHSTYLE_STRETCH);}

    // Generated message map functions
protected:
    //{{AFX_MSG(CColourPicker)
    afx_msg BOOL OnClicked();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);

    DECLARE_MESSAGE_MAP()
};



/** @class CColourPicker
 *  @brief Control for choosing different colour and type of gdi+ brush
 *
 * The CColourPicker class provides the basic functionality to choose brush style
 * It is derived from CButton.
 * 
 * For more information on CColourPicker, see CColourPopupWnd.
 */

#endif 
///////////////////////////////////////////////////////////////////////
// This file is a part of the SViz MFC Extention Class.
// 2001-2002 SVizSoft Software, All Rights Reserved.
//
// SVIZSOFT GRANTS TO YOU THE LIMITED RIGHT TO USE THIS SOFTWARE ON 
// A SINGLE COMPUTER. 
// THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE THE PROPERTY
// OF SVIZSOFT AND ARE NOT TO BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER
// WITHOUT THE EXPRESSED WRITTEN CONSENT OF SVIZ SOFTWARE.
// 
// You can contact us.
// admin@svizsoft.com
///////////////////////////////////////////////////////////////////////
