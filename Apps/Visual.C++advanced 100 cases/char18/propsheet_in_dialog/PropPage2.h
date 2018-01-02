#ifndef AFX_PROPPAGE2_H__B5C9BF32_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_
#define AFX_PROPPAGE2_H__B5C9BF32_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_

// PropPage2.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PropPage2 

class PropPage2 : public CDialog
{
// Konstruktion
public:
	PropPage2(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(PropPage2)
	enum { IDD = IDD_PROPPAGE2 };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(PropPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	virtual void OnCancel (void);
	virtual void OnOK (void);
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(PropPage2)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_PROPPAGE2_H__B5C9BF32_86EB_11D2_B6F4_0000C0E36C6E__INCLUDED_
