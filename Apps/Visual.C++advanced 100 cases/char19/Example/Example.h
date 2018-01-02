// Example.h : Haupt-Header-Datei für die Anwendung EXAMPLE
//

#if !defined(AFX_EXAMPLE_H__B5C9BF27_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_)
#define AFX_EXAMPLE_H__B5C9BF27_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CExampleApp:
// Siehe Example.cpp für die Implementierung dieser Klasse
//

class CExampleApp : public CWinApp
{
public:
	CExampleApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CExampleApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // !defined(AFX_EXAMPLE_H__B5C9BF27_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_)
