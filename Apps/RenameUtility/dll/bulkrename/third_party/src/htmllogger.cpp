//////////////////////////////////////////////////////////////////////
// Portable HTML logger class
// HtmlLogger.cpp: interface for the CHtmlLogger class.
//
// (c) Copyright 2002 FileX software
// Written by: Desyatnikov Stas
// 
// "You have achieved a perfect design not when u have nothing more 
//  to add but when you have nothing more to take away"
//////////////////////////////////////////////////////////////////////

#include "HtmlLogger.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHtmlLogger::CHtmlLogger()
{
	m_iColumns = 0;
	m_bForcedColor = false;
	m_bEven = true;
	m_bNewFile = true;
	m_pColumnArr = NULL;
	m_uiLineNumber = 0;
	m_pLock = 0;
	
	//Set default colors
	m_colorEvenLines.SetColor( 0x00FFFFFF );
	m_colorOddLines.SetColor( 0x00F0F0F0 );;
	//Make it read to emphasize emergencies
	m_colorCurentLine.SetColor( 0x00FF0000 );
	//Green summary lines
	m_colorSummaryLine.SetColor( 0x0080FF80 );
}

CHtmlLogger::~CHtmlLogger()
{
	Close();
}

//Create a HTML file, dumps initial HTML headers
bool CHtmlLogger::Create( char* szFile, bool bInterLocked, ELoggerFlags flags, char* szTitle,
						 CLogColor colorBack, CLogColor colorTxt)
{
	if ( m_pLock )
		Close();

	if ( bInterLocked )
		m_pLock = new CSectionLock;
	else
		m_pLock = new CNULLLock;

	if ( !m_pLock )
		return false;

	CGuard guard( m_pLock );
	guard.Lock();

	if ( !m_pLock )
		return false;

	m_szFile.SetString( szFile );
	
	char* szMode = "bw+";
	switch( flags )
	{
	case LF_Create:
		szMode = "w+b";
		break;

	case LF_Append:
		szMode = "ab";
		if ( CGenFile::IsFile( szFile ) )
			m_bNewFile = false;
		break;
	}
	if ( !m_File.Open( szFile, szMode ) )
		return false;
	
	//if the requested file exist, then find </body> tag
	if ( !m_bNewFile )
	{
		return false; //currently not supported
	}
	else
	{
		char szBuf[ 300 ], szBuf2[ 300 ];
		//Write HTML headers
		if ( !szTitle )
			szTitle = "HTML Log";
		
		//Set body background and text colors
		sprintf( szBuf2, "<BODY BACKCOLOR=\"#%06X\" TEXT=\"#%06X\">", 
				(int)colorBack, colorTxt );
		//Set head and title
		sprintf( szBuf, 
			"<HTML>\n<HEAD>\n <TITLE>%s</TITLE>\n</HEAD>\n\n%s", 
			szTitle, szBuf2 );

		//Write doctype		
		char* szStr = "<!DOCTYPE HTML PUBLIC ""-//W3C//DTD HTML 3.2//EN"">";
		if ( !m_File.WriteLine( szStr ) )
			return false;
		//Write initial header
		if ( !m_File.WriteLine( szBuf ) )
			return false;
	}

	return true;
}

void CHtmlLogger::Close()
{
	CGuard guard( m_pLock );
	guard.Lock();

	m_uiLineNumber = 0;
	delete[] m_pColumnArr;
	m_pColumnArr = NULL;

	//Write the closing tags
	if ( (FILE*)m_File )
	{
		char* szStr = "\n</TABLE>\n</BODY>\n</HTML>";
		m_File.WriteLine( szStr );
	}
	guard.Unlock();
	SAFE_DELETE( m_pLock );
}

//Creates the HTML table with caption on top of it. iWidth is in % (0..100)
bool CHtmlLogger::CreateTable( int iColumns, char* szCaption, int iBorder, 
							  int iWidth, EAlign al )
{
	CGuard guard( m_pLock );
	guard.Lock();

	m_uiLineNumber = 0;

	if ( !(FILE*)m_File )
		return false;

	//If table was created b4 then close the TABLE tag first
	if ( m_pColumnArr )
	{
		delete[] m_pColumnArr;
		if ( !m_File.WriteLine( "</TABLE><br>" ) )
			return false;
	}

	m_pColumnArr = new CColumn[ iColumns ];
	if ( !m_pColumnArr )
		return false; //Out of mem

	m_iColumns = iColumns;

	//write table tag to the file
	char* szAlign[] = { "LEFT", "RIGHT", "CENTER" };
	char szBuf[300];
	sprintf( szBuf, "<TABLE WIDTH=\"%d%%\" BORDER=%d CELLSPACING=\"0\" ALIGN=\"%s\">", 
			iWidth, iBorder, szAlign[ al ] );
	if ( !m_File.WriteLine( szBuf ) )
			return false;

	if ( szCaption )
	{
		//Add the caption element
		sprintf( szBuf, 
			"<CAPTION ALIGN=\"TOP\"><FONT size=\"5\">%s</FONT></CAPTION>", 
			szCaption );
		if ( !m_File.WriteLine( szBuf ) )
			return false;
	}

	return true;
}

//Sets the selected column text
bool CHtmlLogger::SetColumn( int iColumn, char* szData )
{
	CGuard guard( m_pLock );
	guard.Lock();

	if ( !m_pColumnArr )
		return false;
	if ( iColumn >= m_iColumns || iColumn < 0 )
		return false;
	
	return m_pColumnArr[ iColumn ].SetText( szData );
}

bool CHtmlLogger::SetColumnWidth( int iColumn, int iWidth, bool bAbs )
{
	CGuard guard( m_pLock );
	guard.Lock();

	if ( !m_pColumnArr )
		return false;
	if ( iColumn >= m_iColumns || iColumn < 0 )
		return false;
	
	return m_pColumnArr[ iColumn ].SetWidth( iWidth, bAbs );
}

//Dumps the set columns to the table row
bool CHtmlLogger::AddLine( CLogFont* pFont, ELineType lt )
{
	CGuard guard( m_pLock );
	guard.Lock();

	char szBuf[ 300 ];

	int iLen = strlen( "<TR ALIGN=\"CENTER\">" );
	if ( m_File.Write( "<TR ALIGN=\"CENTER\">", iLen ) != iLen )
		return false;

	CLogColor colorThisLine;
	if ( m_uiLineNumber & 1 ) //parity check
		colorThisLine = m_colorOddLines;
	else
		colorThisLine = m_colorEvenLines;
	
	if ( lt == LT_Summary )
		colorThisLine = m_colorSummaryLine;

	//This is a forced color for this line only, 
	//used for urgent msgs, errors, etc...
	if ( m_bForcedColor )
		colorThisLine = m_colorCurentLine;

	//choose if this is a header line or a regular line
	const char* szCellDef = (lt == LT_Header) ? "TH" : "TD";

	//Summary line will be read from the first column
	if ( lt == LT_Summary )
	{
		if ( !pFont )
		{
			sprintf( szBuf, "<%s %s COLSPAN=\"%d\" BGCOLOR=\"#%06X\">%s", 
				szCellDef, m_pColumnArr[ 0 ].GetWidth(), m_iColumns, 
				colorThisLine, m_pColumnArr[ 0 ].GetText() );
		}
		else //use the supplied font
		{
			sprintf( szBuf, "<%s %s COLSPAN=\"%d\" BGCOLOR=\"#%06X\"><FONT SIZE=\"%d\" COLOR=\"#%06X\">%s</FONT>", 
				szCellDef, m_pColumnArr[ 0 ].GetWidth(), m_iColumns, 
				colorThisLine, pFont->GetWeight(), pFont->GetTextColor(), 
				m_pColumnArr[ 0 ].GetText() );
		}

		iLen = strlen(szBuf);
		if ( iLen != m_File.Write( szBuf, iLen ) )
			return false;
		
		return true;
	}

	//Loop through the columns that must be set already
	for ( int i=0; i<m_iColumns; i++ )
	{
		if ( !pFont )
		{
			sprintf( szBuf, "<%s BGCOLOR=\"#%06X\">%s", 
				szCellDef, colorThisLine, 
				m_pColumnArr[i].GetText() );
		}
		else //use the supplied font
		{
			sprintf( szBuf, "<%s %s BGCOLOR=\"#%06X\"><FONT SIZE=\"%d\" COLOR=\"#%06X\">%s</FONT>", 
				szCellDef, m_pColumnArr[i].GetWidth(), colorThisLine, 
				pFont->GetWeight(), pFont->GetTextColor(), 
				m_pColumnArr[i].GetText() );
		}

		iLen = strlen(szBuf);
		if ( iLen != m_File.Write( szBuf, iLen ) )
			return false;
	}
	if ( !m_File.WriteLine(" ") ) //just a \n for clarity
		return false;

	m_bForcedColor = false;
	m_uiLineNumber++;

	return true;
}
