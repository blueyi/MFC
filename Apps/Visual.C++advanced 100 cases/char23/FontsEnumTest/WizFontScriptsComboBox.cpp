// WizFontScriptsComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "fontsTest.h"
#include "WizFontScriptsComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizFontScriptsComboBox

CWizFontScriptsComboBox::CWizFontScriptsComboBox()
{
}

CWizFontScriptsComboBox::~CWizFontScriptsComboBox()
{
}


BEGIN_MESSAGE_MAP(CWizFontScriptsComboBox, CComboBox)
	//{{AFX_MSG_MAP(CWizFontScriptsComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizFontScriptsComboBox message handlers
void	CWizFontScriptsComboBox::Initialize (const CWizFontsEnumerator::Font* font)
{
	ResetContent();
	ASSERT(font);
	const int imax = font->GetScriptsCount();
	for (int i = 0; i < imax; i++)
		{
		int j = AddString(font->GetScript(i));
		if (j >= 0)
			{
			SetItemData(j, i);
			}
		else
			{
			ASSERT(0);
			}
		}
	if (font->GetScriptsCount() > 0)
		SetCurSel(0);
}
