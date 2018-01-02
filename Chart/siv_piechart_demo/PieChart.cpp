//************************************************************
//*
//*	PieChart.cpp
//*
//*	CPieChart and CPieSlice class implementation
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
//*		I suppose some TODOs would be perhaps to use a mem DC,
//*		implement a Draw3D(..) function, make it use not only
//*		percentage data, but also other kinds of data, etc..
//*
//************************************************************


#include "stdafx.h"
#include <math.h>
#include "PieChart.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const UINT CPieSlice::m_nClassVersion = 1;	// ClassVersion is used for...
const UINT CPieChart::m_nClassVersion = 1;	// ...serialization versioning
const double CPieChart::m_dPI = 3.1415926;	// the PI const

IMPLEMENT_SERIAL(CPieSlice, CObject, 1)
IMPLEMENT_SERIAL(CPieChart, CObject, 1)


//*****************************************************************
//* implementation of CPieChart
//*****************************************************************

CPieSlice::CPieSlice()
{
	m_nPercentage = 50;
	m_clrFace = COLORREF(PIECOLOR_RED);
	m_szDescription = _T("<no description>");
}

CPieSlice::CPieSlice( int nPercentage )
{
	SetPercentage(nPercentage);
	m_clrFace = COLORREF(PIECOLOR_RED);
	m_szDescription = _T("<no description>");
}

CPieSlice::CPieSlice( int nPercentage, COLORREF clrFace )
{
	SetPercentage(nPercentage);
	SetColor(clrFace);
	m_szDescription = _T("<no description>");
}

CPieSlice::CPieSlice( int nPercentage, COLORREF clrFace, CString szDescription )
{
	SetPercentage(nPercentage);
	SetColor(clrFace);
	SetDescription(szDescription);
}

CPieSlice::~CPieSlice()
{

}

//**********************************************
//* in case U want to use this in/as a document
void CPieSlice::Serialize( CArchive &ar )
{
	CObject::Serialize( ar );

	if ( ar.IsStoring() )
	{
		ar << m_nClassVersion;
		ar << m_nPercentage << m_clrFace << m_szDescription;
	}
	else
	{
		UINT fileVersion;
		ar >> fileVersion;

		if ( fileVersion == m_nClassVersion )
		{	// version 1
			ar >> m_nPercentage >> m_clrFace >> m_szDescription;
		}
		else
		{
			TRACE(_T("WARNING: CPieSlice version mismatch!\n"));
			TRACE(_T("WARNING: CPieSlice data not loaded!\n"));
			// TODO: if you modify the class, you should
			// modify this to handle previous versions
		}
	}
}

//*****************************************************************
//* implementation of CPieChart
//*****************************************************************

CPieChart::CPieChart()
{
	m_clrBorders	= COLORREF(PIECOLOR_GREEN);
	m_clrText		= COLORREF(PIECOLOR_BLACK);
	m_szTitle		= _T("");
	m_bAutoDel		= FALSE;
}



CPieChart::~CPieChart()
{	// if we need to delete stuff, then delete
	if ( m_bAutoDel == TRUE )
		DeleteAllSlices();
}


int CPieChart::AddSlice( CPieSlice& newSlice )
{
	return m_oaSlices.Add( &newSlice );
}

CPieSlice* CPieChart::GetSlice( int nPos )
{
	if ( nPos > m_oaSlices.GetUpperBound() )
	{	// what is this guy trying to do?
		TRACE(_T("WARNING: CPieChart::GetSlice -> index out of bounds!\n"));
		return NULL;
	}

	return (CPieSlice*)m_oaSlices[nPos];
}

//****************************************************
//* NOTE: this function does NOT delete anything EVER
//* even it the AutoDelete is set to TRUE.
//****************************************************
CPieSlice* CPieChart::RemoveSlice( int nPos )
{
	if ( nPos > m_oaSlices.GetUpperBound() )
	{	// again, what is this guy trying to do?
		TRACE(_T("WARNING: CPieChart::RemoveSlice -> index out of bounds!\n"));
		return NULL;
	}

	CPieSlice* retVal = (CPieSlice*)m_oaSlices[nPos];
	m_oaSlices.RemoveAt( nPos );

	return retVal;
}

void CPieChart::DeleteAllSlices()
{
	CPieSlice* pIter = NULL;
	int nSlices = m_oaSlices.GetSize();

	for ( int i = 0; i < nSlices; i++ )
	{
		delete m_oaSlices[i];
	}

	m_oaSlices.RemoveAll();
}

void CPieChart::Serialize( CArchive &ar )
{
	CObject::Serialize( ar );
	
	if ( ar.IsStoring() )
	{
		ar << m_nClassVersion;

		ar << m_bAutoDel << m_clrBorders << m_clrText << m_szTitle;
	}
	else
	{
		UINT nFileVersion;

		ar >> nFileVersion;

		if ( nFileVersion == m_nClassVersion )
		{
			ar >> m_bAutoDel >> m_clrBorders >> m_clrText >> m_szTitle;
		}
		else
		{
			TRACE(_T("WARNING: CPieChart version mismatch!\n"));
			TRACE(_T("WARNING: CPieChart data not loaded!\n"));
			// TODO: if you modify the class, you should
			// modify this to handly previous versions
		}
	}
	
	// if we don't do this, we'll have a nice
	// and cheesy memory leak..
	if ( ar.IsLoading() )
		DeleteAllSlices();

	// in the end, store our slices
	m_oaSlices.Serialize( ar );

}

//****************************************************
//* the hot stuff! (-:
//*
//* pDC - the target DC
//* ptCenter - the center point of our cheese pie
//* nRadius - radius of the pie, in logical units
//* bShowTitle - do we need to draw a title?
//* nLegend - do we need to draw a legend, and where.
//*	bFillExtra - do we draw a full circle even if
//*				we have invalid data?
//****************************************************
void CPieChart::Draw2D(
					   CPaintDC* pDC,
					   CPoint ptCenter,
					   int nRadius,
					   BOOL bShowTitle,
					   int nLegend,
					   BOOL bFillExtra)
{
	ASSERT(pDC);

	// get the number of slices we have to draw
	int nSlices = m_oaSlices.GetSize();


	// we gotta run a little check here:
	// if our bFillExtra is FALSE, we need to check
	// if the sum of sizes of our slices equals 100%
	// otherwise you get really strange apple pies..
	if ( bFillExtra == FALSE )
	{
		int nSumPercentage = 0;

		for ( int i = 0; i < nSlices; i++ )
		{
			CPieSlice* pIter = NULL;
			pIter = (CPieSlice*)m_oaSlices.GetAt(i);

			if ( pIter != NULL )
			{
				nSumPercentage += pIter->GetPercentage();
			}
		}

		if ( nSumPercentage != 100 )
		{
			TRACE(_T("WARNING: CPieChart data is invalid!\n"));
			TRACE(_T("WARNING: CPieChart not drawn!\n"));
			return;
		}
	}


	// make the world spin around our chart center
	pDC->SetViewportOrg( ptCenter.x, ptCenter.y );

	// some initial values
    int x1 = 0;
    int y1 = -1000;
    int nStep = 0;
	const int nPercent = 100;

	// and some more..
	CPieSlice* pIter2 = NULL;
	COLORREF sliceColor;
	CBrush sliceBrush;
	CPen chartPen;
	// make our DC use the correct pen for the chart borders
	chartPen.CreatePen(PS_SOLID, 0, m_clrBorders );
	CPen* pOldPen = pDC->SelectObject( &chartPen );

	// iterate through all the slices and draw
    for ( int j = 0; j < nSlices; j++)
	{
		pIter2 = (CPieSlice*)m_oaSlices.GetAt(j);
		nStep += pIter2->GetPercentage();

		// if the size of our pie slice is zero,
		// we get a REALLY weird pie (this is due
		// to sin and cos functions, damn thing
		// makes a full circle)
		if ( pIter2->GetPercentage() == 0 && (bFillExtra == FALSE) )
			continue;

		// if we need to fill the extra space with the last pie slice
		if ( (bFillExtra == TRUE) && j == (nSlices-1) )
		{	// yep, this is the last one..
			nStep = 100;
		}

		// a bit of math (-:
		// i kinda 'borrowed' this from a book i read, but it's actually
		// very simple, we calculate the radian value of the next slice
		// and do sin/cos to get x and y pos of the ending point
        double radians = ((double) (nStep * 2 * m_dPI) / (double) nPercent) + m_dPI;
        int x2 = (int) (sin (radians) * 1000);
        int y2 = (int) (cos (radians) * 1000 * 3) / 4;

		// CPaintDC->Pie(..) uses current brush for the pie fill
		sliceBrush.DeleteObject();
		sliceColor = pIter2->GetColor();
		sliceBrush.CreateSolidBrush( sliceColor );
		// take the brush in your left hand
		CBrush* pOldBrush = pDC->SelectObject( &sliceBrush );
		// and draw a pie
        pDC->Pie (-nRadius, -nRadius, nRadius, nRadius, x1, y1, x2, y2);
		// then take the tuna sandwich again..
		pDC->SelectObject( pOldBrush );

		// set our last point as the first point of the next slice
        x1 = x2;
        y1 = y2;
    }

	// do some cleanup
	pDC->SelectObject( pOldPen );
	chartPen.DeleteObject();

	// ok, we got the chart out, now put the title...
	if ( bShowTitle == TRUE )
	{
		CPoint ptTitle;
		pDC->SetTextAlign(TA_CENTER);
		COLORREF oldColor = pDC->SetTextColor( m_clrText );
		pDC->SetBkMode(TRANSPARENT);
		// do some calculations so we get that title
		// centered properly
		ptTitle.x = ptCenter.x;
		ptTitle.y = ptCenter.y - nRadius - 20;

		pDC->DPtoLP(&ptTitle);
		pDC->TextOut( ptTitle.x, ptTitle.y, m_szTitle );
		// put the alignment back
		pDC->SetTextAlign(TA_TOP);
		// put the right color again
		pDC->SetTextColor( oldColor );
	}

	// see if we need to draw the legend
	// NOTE:	i didn't make PIELEGEND_TOP and PIELEGEND_LEFT
	//			because it would require a lot more calculations
	//			than i wanna do right now.
	//			OK, I'm lazy, SO WHAT!
	switch ( nLegend )
	{
	case PIELEGEND_BELOW:
		{
			CPoint thePoint;
			thePoint.y = ptCenter.y + nRadius + 30;
			thePoint.x = ptCenter.x - nRadius;
			DrawLegend( pDC, thePoint, bFillExtra );
		}
		break;
	case PIELEGEND_RIGHT:
		{
			CPoint thePoint;
			// (nSlices*20) equals the height of our
			// legend, so this way we will center it
			// with the center of our pie
			thePoint.y = ptCenter.y - (nSlices*20)/2;
			// BUT, if the legend Y point is ABOVE the
			// pie top, there is a good possibility
			// that our legend will be drawn OVER our
			// title.. and we kinda don't want that..
			if ( thePoint.y < ( ptCenter.y - nRadius ) )
				thePoint.y = ( ptCenter.y - nRadius );

			thePoint.x = ptCenter.x + nRadius + 30;
			DrawLegend( pDC, thePoint, bFillExtra );
		}
		break;
	default:
		// do nothing..
		break;
	}

}


//****************************************************
//* Note that you can use this function to draw a
//* legend anywhere you want, it doesn't have to be
//* 'packed' with the cheese pie itself.
//*
//* pDC - the target DC
//* ptLocation - the upper left cornet of our legend
//*	bFillExtra - do we need to fill in the last
//*				percentage info??
//****************************************************
void CPieChart::DrawLegend( CPaintDC* pDC, CPoint ptLocation, BOOL bFillExtra )
{
	ASSERT(pDC);

	// get the number of slices
	int nSlices = m_oaSlices.GetSize();

	CPoint spot = ptLocation;
	CRect rect;
	COLORREF clrIter;
	CString szIter;
	CPieSlice* pIter = NULL;
	int nPercent = 0;

	// set the correct color
	COLORREF oldColor = pDC->SetTextColor( m_clrText );

	for ( int i = 0; i < nSlices; i++ )
	{
		pIter = (CPieSlice*)m_oaSlices.GetAt(i);

		if ( pIter != NULL )
		{
			clrIter = pIter->GetColor();
			szIter = pIter->GetDescription();
			CString percent;

			if ( (bFillExtra == TRUE) && i == (nSlices-1) )
			{	// if we need to fill the last one, then
				// calculate the rest of the percentage
				percent.Format( _T("(%d%%)"), 100-nPercent );
			}
			else
			{
				percent.Format( _T(" (%d%%)"), pIter->GetPercentage() );
				nPercent += pIter->GetPercentage();
			}
			// concat
			szIter += percent;

			// move our rect to a right position
			rect.top = spot.y;
			rect.left = spot.x;
			rect.bottom = rect.top + 15;
			rect.right = rect.left + 30;

			pDC->DPtoLP(rect);

			// and draw it
			pDC->FillSolidRect( rect, clrIter );
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut( rect.right+5, rect.top, szIter );

		}

		// move down by the height of one line
		spot.y += 20;
	}
	// restore the DC text color
	pDC->SetTextColor( oldColor );
}