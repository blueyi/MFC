// TitleBarButton.h : Haupt-Header-Datei für die Anwendung TITLEBARBUTTON
//

#if !defined(AFX_TITLEBARBUTTON_H__EE2F9C13_A9B0_48D7_9D0C_D19BA404E6E5__INCLUDED_)
#define AFX_TITLEBARBUTTON_H__EE2F9C13_A9B0_48D7_9D0C_D19BA404E6E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CTitleBarButtonApp:
// Siehe TitleBarButton.cpp für die Implementierung dieser Klasse
//

class CTitleBarButtonApp : public CWinApp
{
public:
	CTitleBarButtonApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CTitleBarButtonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CTitleBarButtonApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_TITLEBARBUTTON_H__EE2F9C13_A9B0_48D7_9D0C_D19BA404E6E5__INCLUDED_)
