// PropPage1.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Example.h"
#include "PropPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld PropPage1 


PropPage1::PropPage1(CWnd* pParent /*=NULL*/)
	: CDialog(PropPage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(PropPage1)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void PropPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropPage1)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

// ESC-Button not allowed here
void PropPage1::OnCancel (void) {

	return ;
}
// ENTER-Button not allowed here
void PropPage1::OnOK (void) {

	return ;
}




BEGIN_MESSAGE_MAP(PropPage1, CDialog)
	//{{AFX_MSG_MAP(PropPage1)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PropPage1 
