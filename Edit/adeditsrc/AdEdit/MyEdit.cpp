// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "AdEdit.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////

/////////
// CMyEdit

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
//{{AFX_MSG_MAP(CMyEdit)
ON_WM_CHAR()
ON_WM_KEYDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////

/////////
// CMyEdit message handlers

//将int型地pos转化为DWORD型地位置
DWORD CMyEdit::FormatPos(int hPos,int lPos)
{
	DWORD dPos=hPos;
	dPos=dPos<<16;
	dPos+=lPos;
	return dPos;
}

void CMyEdit::Initial()
{
	SetLimitText(10);
	SetWindowText("    -  -  ");
}

void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call 
	int oldpos=LOWORD(GetSel());
	CString str;
	GetWindowText(str);
	
	if ( nChar>='0' && nChar<='9' )
	{	
		if ( oldpos<4 || ( oldpos>4 && oldpos<7) || oldpos>7)
		{
			str.Delete(oldpos,1);
			SetWindowText(str);
			SetSel(FormatPos(oldpos,oldpos));
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			if ( LOWORD(GetSel())==4 || LOWORD(GetSel())==7)
			{
				oldpos=LOWORD(GetSel());
				SetSel(FormatPos(oldpos+1,oldpos+1));
			}
		}
		else
			if ( oldpos==4 || oldpos==7 )
			{
				oldpos+=1;
				SetSel(FormatPos(oldpos,oldpos));
				str.Delete(oldpos,1);
				SetWindowText(str);
				SetSel(FormatPos(oldpos,oldpos));
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
	}
	else
		if ( nChar==VK_BACK )
		{
			if ( (oldpos>0 && oldpos<5) || ( oldpos>5 && oldpos<8) || oldpos>8)
			{
				str.Insert(oldpos,' ');
				SetWindowText(str);
				SetSel(FormatPos(oldpos,oldpos));
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
			else
				if ( oldpos==5 || oldpos==8 )
				{	
					SetSel(FormatPos(oldpos-1,oldpos-1));
				}
		}
		
}

void CMyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call 
	CString str;
	int oldpos=LOWORD(GetSel());
	GetWindowText(str);
	if ( nChar==VK_DELETE )
	{
		if ( oldpos<4 || ( oldpos>4 && oldpos<7) || oldpos>7)
		{
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			GetWindowText(str);
			if ( oldpos<7 )
				str.Insert(str.Find('-',oldpos),' ');
			SetWindowText(str);
			SetSel(FormatPos(oldpos,oldpos));
		}
		else
			if ( oldpos==4 || oldpos==7 )
				return ;
	}
	else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}