// EditHelper.cpp : implementation file
//

#include "stdafx.h"

#include "EditHelper.h"

#include "TreeHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditHelper

CEditHelper::CEditHelper()
{
	m_nBitmapID = 0;
	m_sSeparator = _T(",");
}

CEditHelper::~CEditHelper()
{
}


BEGIN_MESSAGE_MAP(CEditHelper, CEdit)
	//{{AFX_MSG_MAP(CEditHelper)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditHelper message handlers

void CEditHelper::OnRButtonDown(UINT nFlags, CPoint point) 
{
	((CDialog*)GetParent())->UpdateData();

	CString sText;
	GetWindowText( sText );

	CTreeHelper*	poTree = new CTreeHelper( m_nBitmapID );
	poTree->ShowTree( &sText , m_sSeparator, this, &point );
}

void CEditHelper::SetHelperFlags(LPCTSTR sSeparator, UINT nResID)
{
	m_sSeparator = _T(sSeparator);
	m_nBitmapID = nResID;
}
