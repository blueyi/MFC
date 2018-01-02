// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "seek.h"
#include "MyEdit.h"
#include "seekButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_SEEKBUTTONVALUECHANGED, OnSeekButtonValueChanged )	
END_MESSAGE_MAP()

LONG CMyEdit::OnSeekButtonValueChanged( UINT /* id */, LONG value )
{
	static CString str;
	str.Format("%d", value );
	SetWindowText( str );
	RedrawWindow();

	return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers
