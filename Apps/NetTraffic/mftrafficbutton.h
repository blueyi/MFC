/*******************************************

	MFTrafficButton

	Version:	1.0
	Date:		31.10.2001
	Author:		Michael Fatzi
	Mail:		Michael_Fatzi@hotmail.com
	Copyright 1996-1997, Keith Rule

	You may freely use or modify this code provided this
	Copyright is included in all derived versions.
	
	History: 10.2001 Startup

	Handy little button control to display current 
	nettraffic as graph in a button.

********************************************/

#if !defined(AFX_MFTRAFFICBUTTON_H__9F2EABAA_E8C7_48B4_94A5_EC279905F50C__INCLUDED_)
#define AFX_MFTRAFFICBUTTON_H__9F2EABAA_E8C7_48B4_94A5_EC279905F50C__INCLUDED_

#include "MFNetTraffic.h"	// Added by ClassView
#include "Globals.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MFTrafficButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MFTrafficButton window

//VOID CALLBACK InterfaceChanged(int newInterface);

//typedef FARPROC INTERFACECHANCEDPROC;
typedef VOID (CALLBACK* INTERFACECHANCEDPROC)(int);

class MFTrafficButton : public CButton
{
// Construction
public:
	MFTrafficButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MFTrafficButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetAdaptiveScaling(BOOL adaptive);
	void SetInterfaceNumber(int interfacenumber);
	enum traffictype
	{
		Traffic_Total		= 0,
		Traffic_Incoming	= 1,
		Traffic_Outgoing	= 2
	};

	void SelectTrafficType(int trafficType);
	void SetInterfaceNumberNotificationFunction(INTERFACECHANCEDPROC callfunct);
	void SetUpdateSpeed(UINT netspeed, UINT gridspeed);
	void ReInit(int newInterface);
	void ReInit(RECT newSize);
	virtual ~MFTrafficButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(MFTrafficButton)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void InterfaceHasChanged();

	INTERFACECHANCEDPROC interfaceCallBack;

	MFNetTraffic m_cTrafficClass;

	CFont	smallFont;
	CBrush	colorbrush;

	COLORREF red, green, back, cyan, darkblue, darkgray, white, black, lightgreen, darkgreen;
	CBitmap	colorbrushbmp;
	CPen	GridPen;
	CSize	TGSize;

	CBrush	greenbrush;
	CBrush	redbrush;
	CPoint	orgBrushOrigin; 

	RECT	TrafficDrawRectangle;
	RECT	TrafficDrawUpdateRectangle;

	CString CurrentTraffic;
	CString MaximalTraffic;
	CString AllTraffic;

	DWORD	TrafficEntries;

	BOOL	initalized;
	BOOL	isOnline;
	BOOL	brushInitalized;

	CRgn	ShapeWNDRegion;
	CRgn	ShapeDCRegion;

	double	MaxTrafficAmount;
	CString	ToggleStatusText;

	int SelectedInterface;

	BOOL useAdaptiveScale;

	TRAFFICENTRY* TrafficStats;

	int gridxstartpos;		
	int gridystartpos;
	int plotgranularity;		

	// Public modification variables
public:
	int gridxresolution;		// The size of grid raster
	int gridyresolution;
	int gridscrollxspeed;		// Scroll speed of the grid
	int gridscrollyspeed; 
	int netupdatespeed;			// Should be set via SetUpdateSpeet method
	int gridupdatespeed;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFTRAFFICBUTTON_H__9F2EABAA_E8C7_48B4_94A5_EC279905F50C__INCLUDED_)
