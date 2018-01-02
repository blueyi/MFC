/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// ObjInfo.cpp : implementation of the CObjInfo class                      //
//                                                                         //
// This class could use <vector> container of standard template library.   //
// To make code easy I have choosed an explicit implementation.            //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjInfo.h"


/////////////////////////////////////////////////////////////////////////////
// CObjInfo

//-------------------------------------------------------------------------//
// Default Constructor                                                     //
//-------------------------------------------------------------------------//
CObjInfo::CObjInfo()
{
	m_sName.Empty();
	m_dwFormat	= 0;
	m_pThumb	= NULL;
	m_hIcon		= NULL;
	m_sText.Empty();
}

//-------------------------------------------------------------------------//
// Constructor (filename and filetype)                                     //
//-------------------------------------------------------------------------//
CObjInfo::CObjInfo(LPCTSTR lpszFileName, DWORD dwType)
{
	m_sName		= lpszFileName;
	m_dwFormat	= dwType;
	m_pThumb	= NULL;
	m_hIcon		= NULL;
	m_sText.Empty();
}

//-------------------------------------------------------------------------//
// Constructor (filename, filetype and thumbnail image)                    //
//-------------------------------------------------------------------------//
CObjInfo::CObjInfo(LPCTSTR lpszFileName, DWORD dwType, CBitmap* pImage)
{
	m_sName		= lpszFileName;
	m_dwFormat	= dwType;
	m_pThumb	= pImage;
	m_hIcon		= NULL;
	m_sText.Empty();
}

//-------------------------------------------------------------------------//
// Constructor (filename, filetype and icon handle)                        //
//-------------------------------------------------------------------------//
CObjInfo::CObjInfo(LPCTSTR lpszFileName, DWORD dwType, HICON hImage)
{
	m_sName		= lpszFileName;
	m_dwFormat	= dwType;
	m_pThumb	= NULL;
	m_hIcon		= hImage;
	m_sText.Empty();
}

//-------------------------------------------------------------------------//
// Constructor (filename, filetype and file content)                       //
//-------------------------------------------------------------------------//
CObjInfo::CObjInfo(LPCTSTR lpszFileName, DWORD dwType, LPCTSTR lpszHead)
{
	m_sName		= lpszFileName;
	m_dwFormat	= dwType;
	m_pThumb	= NULL;
	m_hIcon		= NULL;
	m_sText		= lpszHead;
}

//-------------------------------------------------------------------------//
// Destroyer                                                               //
//-------------------------------------------------------------------------//
CObjInfo::~CObjInfo()
{
	m_sName.Empty();
	if( m_hIcon ) ::DestroyIcon(m_hIcon);
	if( m_pThumb )
	{
		::DeleteObject(m_pThumb->Detach());
		delete m_pThumb;
	}
	m_sText.Empty();
}

//-------------------------------------------------------------------------//
// Set icon handle                                                         //
//-------------------------------------------------------------------------//
void CObjInfo::SetIcon(HICON hImage)
{
	if( m_hIcon ) ::DestroyIcon(m_hIcon);
	m_hIcon = hImage;
}

//-------------------------------------------------------------------------//
// Set text string                                                         //
//-------------------------------------------------------------------------//
void CObjInfo::SetText(LPCTSTR lpszHead)
{
	m_sText.Empty();
	m_sText = lpszHead;
}

//-------------------------------------------------------------------------//
// Set bitmap pointer                                                      //
//-------------------------------------------------------------------------//
void CObjInfo::SetBitmap(CBitmap* pImage)
{
	if( m_pThumb ) delete m_pThumb;
	m_pThumb = pImage;
}


/////////////////////////////////////////////////////////////////////////////
// CClrInfo

//-------------------------------------------------------------------------//
// Default Constructor                                                     //
//-------------------------------------------------------------------------//
CClrInfo::CClrInfo()
{
	m_dwRGB	= 0;
	m_dwHSB = 0;
}

//-------------------------------------------------------------------------//
// Constructor (colorname and color-spaces values)                         //
//-------------------------------------------------------------------------//
CClrInfo::CClrInfo(COLORREF dwRGB, COLORREF dwHSB)
{
	m_dwRGB	= dwRGB;
	m_dwHSB = dwHSB;
}

//-------------------------------------------------------------------------//
// Destroyer                                                               //
//-------------------------------------------------------------------------//
CClrInfo::~CClrInfo()
{
}

