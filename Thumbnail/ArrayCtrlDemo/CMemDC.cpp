/////////////////////////////////////////////////////////////////////////////
// 
// CMemDC.cpp : implementation of the CMemDC class
// 
//
// Using in MFC environment.
//
// Written by Adriano Asnaghi <aasnaghi@mail.tim.it>
// Version 1.0 2004.
//
// This code may be freely used in any way you desire. There is no
// copyright applied on it. If it is helpful for your application
// an email letting me know how you are using it would be nice as well. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author don't accepts liability for any damage or loss of business
// that this product may cause.
//
//        
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CMemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMemDC

//-------------------------------------------------------------------------//
// Constructor                                                             //
//-------------------------------------------------------------------------//
CMemDC::CMemDC()
{
	// The default constructor creates an empty object 
	// It will be created next otherwise it is unusable
	m_pDC			= (CDC*)NULL;
	m_pOrigBitmap	= (CBitmap*)NULL;
	m_pOrigBrush	= (CBrush*)NULL;
	m_nWidth		= 0;
	m_nHeight		= 0;
	m_crBack		= RGB(0,0,0);
}

//-------------------------------------------------------------------------//
// Constructor                                                             //
//-------------------------------------------------------------------------//
CMemDC::CMemDC(int nWidth, int nHeight, COLORREF crBack)
{
	m_pDC			= (CDC*)NULL;
	m_pOrigBitmap	= (CBitmap*)NULL;
	m_pOrigBrush	= (CBrush*)NULL;
	this->Create(nWidth, nHeight, crBack);
}

//-------------------------------------------------------------------------//
// Destroyer                                                               //
//-------------------------------------------------------------------------//
CMemDC::~CMemDC()
{
	CBitmap		*pBitmap = NULL;
	CBrush		*pBrush = NULL;

	if( m_pDC == NULL ) return;

	// delete background brush object
	if( m_pOrigBrush )
	{
		pBrush = m_pDC->SelectObject(m_pOrigBrush);
		if( pBrush )
		{
			DeleteObject((HBRUSH)pBrush->Detach());
			delete pBrush;
		}
	}

	// delete bitmap object
	if( m_pOrigBitmap )
	{
		pBitmap = m_pDC->SelectObject(m_pOrigBitmap);
		if( pBitmap )
		{
			DeleteObject((HBITMAP)pBitmap->Detach());
			delete pBitmap;
		}
	}

	// delete the DC
	delete m_pDC;
}

//-------------------------------------------------------------------------//
// Create method                                                           //
//-------------------------------------------------------------------------//
BOOL CMemDC::Create(int nWidth, int nHeight, COLORREF crBack)
{
	HDC			hDC;
	CDC			ScreenDC;
	CBitmap*	pBitmap;
	CBrush*		pBrush;

	if( m_pDC ) return FALSE;
	m_nWidth = (nWidth <= 0? 1: nWidth);
	m_nHeight = (nHeight <= 0? 1: nHeight);

	// obtain a screen DC
	hDC = ::GetDC(NULL);
	ScreenDC.Attach(hDC);

	// Create primary offscreen DC
	m_pDC = new CDC;
	m_pDC->CreateCompatibleDC(&ScreenDC);

	// Create a new bitmap object
	pBitmap = new CBitmap;
	pBitmap->CreateCompatibleBitmap(&ScreenDC, m_nWidth, m_nHeight);
	m_pOrigBitmap = m_pDC->SelectObject(pBitmap);

	// Create a new brush object and select it into DC
	pBrush = new CBrush;
	pBrush->CreateSolidBrush(crBack);
	m_pOrigBrush = m_pDC->SelectObject(pBrush);

	// fill it with background color
	m_pDC->PatBlt(0, 0, m_nWidth, m_nHeight, PATCOPY);

	// release the screen DC
	hDC = ScreenDC.Detach();
	::ReleaseDC(NULL, hDC);
	return TRUE;
}

//-------------------------------------------------------------------------//
// Resize the DC                                                           //
//-------------------------------------------------------------------------//
void CMemDC::Resize(int nWidth, int nHeight) 
{
	CBitmap		*pBitmap, *pOldBitmap;

	ASSERT(m_pDC);

	if( (nWidth <= 0) || (nHeight <= 0) ) return; 
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	// delete old bitmap object and acquire new one
	pBitmap = new CBitmap;
	pBitmap->CreateCompatibleBitmap(m_pDC, m_nWidth, m_nHeight);
	pOldBitmap = m_pDC->SelectObject(pBitmap);
	DeleteObject((HBITMAP)pOldBitmap->Detach());
	delete pOldBitmap;

	// fill it with background color
	m_pDC->PatBlt(0, 0, m_nWidth, m_nHeight, PATCOPY);
}

//----------------------------------------------------------------------------------//
// Change the background color                                                      //
//----------------------------------------------------------------------------------//
void CMemDC::SetColor(COLORREF crBack)
{
	CBrush*		pBrush;
	CBrush*		pOldBrush;

	ASSERT(m_pDC);

	// Create a new brush object
	pBrush = new CBrush;
	pBrush->CreateSolidBrush(crBack);
	pOldBrush = m_pDC->SelectObject(pBrush);
	DeleteObject((HBRUSH)pOldBrush->Detach());
	delete pOldBrush;

	// fill it with background color
	m_pDC->PatBlt(0, 0, m_nWidth, m_nHeight, PATCOPY);
}

//-------------------------------------------------------------------//
// Erase DC background                                               //
//-------------------------------------------------------------------//
void CMemDC::Erase()
{
	ASSERT(m_pDC);

	m_pDC->PatBlt(0, 0, m_nWidth, m_nHeight, PATCOPY);
}

//-------------------------------------------------------------------//
// Copy rectangle from source DC                                     //
//-------------------------------------------------------------------//
void CMemDC::Copy(int nDestX, int nDestY, int nDestW, int nDestH, CMemDC* pSrc, int nSrcX, int nSrcY) 
{
	ASSERT(m_pDC);
	ASSERT(pSrc);
	ASSERT(pSrc->m_pDC);

	m_pDC->BitBlt(nDestX, nDestY, nDestW, nDestH, pSrc->m_pDC, nSrcX, nSrcY, SRCCOPY);
}

