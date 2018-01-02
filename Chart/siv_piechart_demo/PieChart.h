//************************************************************
//*
//*	PieChart.h
//*
//*	CPieChart and CPieSlice class interface.
//*
//*	DESCRIPTION:
//*		Two CObject derived classes to implement a pie chart
//*
//*	ASSUMES:
//*		You know how to use it :-)
//*
//*	AUTHOR: T1TAN <t1tan@cmar-net.org>
//*
//*	COPYLEFT:
//*		Copyleft (C) T1TAN 2004 - 3827
//*		Copyleft (C) SprdSoft Inc.2004 - 3827
//*		FREE for (ab)use in any way except selling the code.
//*		Leave the headers be.
//*
//*	VERSIONS:
//*		VERSION		AUTHOR		DATE		NOTES
//*		-------		------		----		-----
//*		1.0			T1TAN		28/7/2004	initial version
//*
//*
//*	OTHER:
//*		<nothing yet>
//*
//************************************************************


#ifndef __PIECHART_H_INCLUDED__
#define __PIECHART_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef PIECOLORS
#define PIECOLORS

#define PIECOLOR_BLACK		(RGB(0,0,0))
#define PIECOLOR_WHITE		(RGB(255,255,255))
#define PIECOLOR_GRAY		(RGB(128,128,128))
#define PIECOLOR_RED		(RGB(255,0,0))
#define PIECOLOR_GREEN		(RGB(0,255,0))
#define PIECOLOR_BLUE		(RGB(0,0,255))
#define PIECOLOR_YELLOW		(RGB(255,255,0))
#define PIECOLOR_CYAN	 	(RGB(0,255,255))
#define PIECOLOR_PURPLE  	(RGB(255,0,255))

#endif // PIECOLORS

#ifndef PIELEGEND_LOCATIONS
#define PIELEGEND_LOCATIONS

#define PIELEGEND_NONE		0
#define PIELEGEND_RIGHT		1
#define PIELEGEND_BELOW		2

#endif // PIELEGEND_LOCATIONS


class CPieSlice : public CObject
{
	DECLARE_SERIAL(CPieSlice)
public:
	CPieSlice();
	CPieSlice( int nPercentage );
	CPieSlice( int nPercentage, COLORREF clrFace );
	CPieSlice( int nPercentage, COLORREF clrFace, CString szDescription );
	virtual ~CPieSlice();

	//*************************
	//* inline functions
	void SetPercentage( UINT nPercentage )
	{
		if ( nPercentage < 0 )
		{
			TRACE(_T("WARNING: PieSlice size truncation!\n"));
			m_nPercentage = 0;
		}
		else if ( nPercentage > 100 )
		{
			TRACE(_T("WARNING: PieSlice size truncation!\n"));
			m_nPercentage = 100;
		}
		else
			m_nPercentage = nPercentage;
	}

	void SetColor( COLORREF clrFace ) {	m_clrFace = clrFace; }
	UINT GetPercentage() { return m_nPercentage; }

	COLORREF GetColor() { return m_clrFace; }

	void SetDescription( CString szDecription ) { m_szDescription = szDecription; }
	CString GetDescription() { return m_szDescription; }
	//* end of inline functions
	//*************************

	void Serialize( CArchive &ar );

private:
	UINT m_nPercentage;			// how big is our piece of cake?
	COLORREF m_clrFace;			// filling the slice with this one
	CString m_szDescription;	// used for drawing the legend
	static const UINT m_nClassVersion;	// for serialization
};

class CPieChart : public CObject
{
	DECLARE_SERIAL(CPieChart)
public:
	CPieChart();
	virtual ~CPieChart();

	int AddSlice( CPieSlice& newSlice );
	CPieSlice* GetSlice( int nPos );
	CPieSlice* RemoveSlice( int nPos );
	void DeleteAllSlices();

	//*************************
	//* inline functions
	void SetBorderColor( COLORREF clrBorder ) { m_clrBorders = clrBorder; }
	COLORREF GetBorderColor() {	return m_clrBorders; }

	void SetTextColor( COLORREF clrText ) { m_clrText = clrText; }
	COLORREF GetTextColor() { return m_clrText; }

	void SetTitle( CString szTitle ) { m_szTitle = szTitle;	}
	CString GetTitle() { return m_szTitle; }

	void SetAutoDelete( BOOL bAutoDel = TRUE ) { m_bAutoDel = bAutoDel; }
	BOOL GetAutoDelete() { return m_bAutoDel; }

	UINT GetCount() { return m_oaSlices.GetSize(); }
	//* end of inline functions
	//*************************

	void Serialize( CArchive &ar );

	void Draw2D(
		CPaintDC* pDC,
		CPoint ptCenter,
		int nRadius,
		BOOL bShowTitle = TRUE,
		int nLegend = PIELEGEND_NONE,
		BOOL bFillExtra = FALSE );

	void DrawLegend(
		CPaintDC* pDC,
		CPoint ptLocation,
		BOOL bFillExtra = FALSE );

private:
	BOOL m_bAutoDel;	// determines if this class will delete stuff when destroyed
	CString m_szTitle;					// graph title, drawn above the graph itself
	CObArray m_oaSlices;				// an array of "slices"
	static const double m_dPI;			// you know, 3.14159... (-:
	COLORREF m_clrBorders;				// color used to draw the lines on our cake
	COLORREF m_clrText;					// color used to output text to DC
	static const UINT m_nClassVersion;	// used for serialization
};

#endif // __PIECHART_H_INCLUDED__
