//////////////////////////////////////////////////////////////////////
// Portable HTML logger class
// HtmlLogger.h: interface for the CHtmlLogger class.
//
// (c) Copyright 2002 FileX software
// Written by: Desyatnikov Stas
// 
// "You have achieved a perfect design not when u have nothing to add 
//  but when you have nothing to take away"
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLLOGGER_H__E64EC0FE_30CF_414D_8CC9_E2C751C31319__INCLUDED_)
#define AFX_HTMLLOGGER_H__E64EC0FE_30CF_414D_8CC9_E2C751C31319__INCLUDED_

#ifdef WIN32
#include "Windows.h"
#endif

//Portable includes
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "GenFile.h"
#include "SmartString.h"
#include "synchronizations.h"

class CLogColor
{
	int m_iColor;
public:
	CLogColor() { m_iColor = 0; }
	CLogColor( int iColor ) { m_iColor = iColor; }
	void operator = ( int iColor ) { SetColor(iColor); }
	void operator = ( CLogColor color ) { SetColor( color.GetColor() ); }
	operator int() { return GetColor(); }
	//Assues int is 32 bit and colors are least significant bytes
	//COLORREF can be used as iColor param
	void SetColor( int iColor )
	{
		/*r = (char)iColor;
		g = (char)( iColor >> 8 );
		b = (char)( iColor >> 16 );
		*/
		m_iColor = iColor;
	}
	int GetColor()
	{
		//int iColor = r | ( ((short)g) << 8 ) | ( ((int)b) << 16 );
		return m_iColor;
	}
	
#ifdef WIN32
	operator COLORREF() { return m_iColor; }
#endif
};

class CLogFont
{
public:
	enum EFontWeight { FW_ExtraLight=1, FW_Light, FW_DemiLight, 
						FW_Medium, FW_DemiBold, FW_Bold, FW_ExtraBold };
	enum EFontStyle { FS_Normal, FS_Oblique, FS_Italic };

	CLogFont() 
	{ 
		//40 is a max font family
		m_szFontFamily.Reallocate( 40 );
		m_szFontFamily = "Times New Roman";

		m_Weight = FW_Medium;

		m_Style = FS_Normal;
		
		//Black default
		m_ColorText = 0;
	}
	
	CLogFont( CLogColor colorText, EFontWeight fw, const char* szFamily=NULL )
	{
		m_szFontFamily.Reallocate( 40 );
		if ( szFamily )
			m_szFontFamily = szFamily;

		m_Weight = fw;
		m_ColorText = colorText;
	}
	
	void SetTextColor( CLogColor colorText=0 ) 
	{ 
		m_ColorText = colorText; 
	}


	void SetWeight( EFontWeight fw=FW_Medium ) { m_Weight=fw; }
	void SetFamily( char* szFamily ) { m_szFontFamily = szFamily; }

	CLogColor GetTextColor() { return m_ColorText; }
	EFontWeight GetWeight()  { return m_Weight; }
	const char* GetFamily() { return m_szFontFamily; }

protected:
	CSmartString	m_szFontFamily;
	EFontStyle		m_Style;
	CLogColor		m_ColorText; //black default
	EFontWeight		m_Weight;
};

class CHtmlLogger  
{

public:
	class CColumn
	{
		CSmartString	m_szText;
		//Width string value, pixels or % in the ""
		char			m_szWidth[ 24 ];
		//true - indicates pixel units, false - %
		bool			m_bAbsolute; 
	public:
		CColumn() 
		{ 
			m_bAbsolute = false; 
			m_szText.Reallocate(100); //prealloc 100 chars for cols
			m_szWidth[0] = 0;
		}

		bool SetText( const char* szText ) 
		{ 
			return m_szText.SetString( szText ); 
		}

		const char* GetText() { return m_szText.GetString(); }

		bool SetWidth( uint uiWidth, bool bAbs=false )
		{
			if ( !bAbs )
			{
				if ( uiWidth > 100 )
					return false;
				sprintf( m_szWidth, "WIDTH=\"%d%%\"", uiWidth );
			}
			else
			{
				sprintf( m_szWidth, "WIDTH=\"%d\"", uiWidth );
			}
			return true;
		}
		const char* GetWidth() { return m_szWidth; }
	};
	enum ELoggerFlags { LF_Append, LF_Create };
	enum EAlign { A_Left, A_Right, A_Center };
	enum ELineType { LT_Line, LT_Header, LT_Summary };

	CHtmlLogger();
	virtual ~CHtmlLogger();

	bool Create( char* szFile, bool bInterLocked=false, 
				ELoggerFlags flags=LF_Create, char* szTitle=NULL,
				CLogColor colorBack=0xFFFFFF, CLogColor colorTxt=0 );
	void Close();
	
	bool CreateTable( int iColumns, char* szCaption=0, int iBorder=1, 
					int iWidth=100, EAlign al=A_Center );
	
	bool SetColumn( int iColumn, char* szData );
	bool SetColumnWidth( int iColumn, int iWidth, bool bAbs=false );
	bool SetSummaryLine( char* szData ) { return SetColumn(0, szData); }
	bool AddLine( CLogFont* pFont=NULL, ELineType lt=LT_Line );

	//Colors
	void SetEvenLinesColor( CLogColor color )
	{
		m_colorEvenLines = color;
	}
	void SetOddLinesColor( CLogColor color )
	{
		m_colorOddLines = color;
	}
	void SetCurrentLineColor( CLogColor color )
	{
		m_colorCurentLine = color;
		m_bForcedColor = true;
	}
	void SetSummaryLineColor( CLogColor color )
	{
		m_colorSummaryLine = color;
	}

protected:
	CSmartString	m_szFile;
	int				m_iColumns;
	CColumn*		m_pColumnArr;
	//Colors
	CLogColor		m_colorEvenLines;
	CLogColor		m_colorOddLines;
	CLogColor		m_colorCurentLine;
	CLogColor		m_colorSummaryLine;

	bool			m_bForcedColor;
	bool			m_bEven;
	
	bool			m_bNewFile;
	CGenFile		m_File;
	uint			m_uiLineNumber;
	CLock*			m_pLock;
};

#endif // !defined(AFX_HTMLLOGGER_H__E64EC0FE_30CF_414D_8CC9_E2C751C31319__INCLUDED_)
