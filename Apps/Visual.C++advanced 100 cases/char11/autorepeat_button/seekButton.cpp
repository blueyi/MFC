//==========================================================================================
//==========================================================================================
// CSeekButton implementation
//
// Copyright 1998 Langis Pitre
//==========================================================================================
//==========================================================================================
#include "stdafx.h"
#include "SeekButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------------------------------------------------
CSeekButton::CSeekButton(int InitialValue, int Direction, int Increment, int min, int max ) 
: CButton()
{
	mhWnd = NULL;
	SetParameters( mhWnd, InitialValue, Direction, Increment, min, max );
}

BEGIN_MESSAGE_MAP( CSeekButton, CButton )
	//{{AFX_MSG_MAP( CSeekButton )
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//<=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=><=>
// Name   : SetParameters
//          
// Descr. : 
//          
// Return : void
// Arg    : HWND hWnd        : 
// Arg    : int InitialValue : 
// Arg    : int Direction    : 
// Arg    : int Increment    : 
// Arg    : int min          : 
// Arg    : int max          : 
//------------------------------------------------------------------------------------------
void CSeekButton::SetParameters(HWND hWnd,
								int InitialValue, 
								int Direction, 
								int Increment,
								int min,
								int max )
{
	mhWnd         = hWnd;
	mCurrentValue = InitialValue;
	mDirection    = Direction;
	mIncrement    = Increment;
	mMin          = min;
	mMax          = max;
}

//------------------------------------------------------------------------------------------
// Descr. : Called when the user presses either the IDC_RWND or the IDC_FRWD button.
//          It initiates a seek loop ( forward or backward ) that lasts as long as the button
//          is pressed. The loop is terminated when a WM_LBUTTONUP message is received.
//          
//==========================================================================================
void CSeekButton::OnLButtonDown( UINT nFlags, CPoint point ) 
//==========================================================================================
{
	CButton::OnLButtonDown( nFlags, point );
		
	int   nbiter = 0;
	MSG   mess;
	int   id  = GetDlgCtrlID( );

	HWND hWnd = GetSafeHwnd();

	if( mhWnd == NULL )
		mhWnd = GetParent()->GetSafeHwnd();

	while( !PeekMessage( &mess, hWnd, WM_LBUTTONUP, WM_LBUTTONUP, PM_REMOVE ) )
	{
		if( nbiter < 10 )
		{
			Sleep( 100 );
		}
		else if( nbiter < 20 )
		{
			Sleep( 75 );
		}
		else if( nbiter < 30 )
		{
			Sleep( 50 );
		}
		else 
		{
			Sleep( 25 );
		}
		
		nbiter++;

		mCurrentValue += ( mDirection == FORWARD )? mIncrement : -mIncrement;
		
		if( mCurrentValue < mMin )
		{
			mCurrentValue = mMax;
		}
		if( mCurrentValue >  mMax)
		{
			mCurrentValue = mMin;
		}
		TRACE("Value = %d\n", mCurrentValue );

		::SendMessage( mhWnd, WM_SEEKBUTTONVALUECHANGED, id, mCurrentValue );
	}

	SendMessage( WM_LBUTTONUP );
}

