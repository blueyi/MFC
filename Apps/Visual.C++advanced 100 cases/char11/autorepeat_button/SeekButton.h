//==========================================================================================
//==========================================================================================
// SeekButton.h : header file
//
// Declaration of class CSeekButton
//
// Copyright 1998 Langis Pitre
//==========================================================================================
//==========================================================================================
#ifndef _SEEKBUTTON_H_
#define _SEEKBUTTON_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define WM_SEEKBUTTONVALUECHANGED (WM_USER+10)

//==========================================================================================
class CSeekButton : public CButton
//==========================================================================================
{
public:

	enum{ FORWARD, BACKWARD };
	CSeekButton( int InitialValue = 0, 
				 int Direction = FORWARD, 
				 int Increment = 1,
				 int min = -10000,
				 int max =  10000 );
	virtual ~CSeekButton(){}

	void SetParameters(HWND hWnd,
		int InitialValue, 
		int Direction, 
		int Increment,
		int min,
		int max );

	//{{AFX_VIRTUAL( CSeekButton )
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG( CSeekButton )
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	//}}AFX_MSG
	
	int mCurrentValue;
	int mDirection;
	int mIncrement;
	int mMin, mMax;
	HWND mhWnd;

	DECLARE_MESSAGE_MAP()
};

//==========================================================================================


#endif // _SEEKBUTTON_H_