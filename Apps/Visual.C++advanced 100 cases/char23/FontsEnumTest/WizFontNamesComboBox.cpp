// WizFontNamesComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "fontsTest.h"
#include "WizFontNamesComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizFontNamesComboBox

CWizFontNamesComboBox::CWizFontNamesComboBox()
{
}

CWizFontNamesComboBox::~CWizFontNamesComboBox()
{
}


BEGIN_MESSAGE_MAP(CWizFontNamesComboBox, CComboBox)
	//{{AFX_MSG_MAP(CWizFontNamesComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizFontNamesComboBox message handlers
void CWizFontNamesComboBox::Initialize(const CWizFontsEnumerator& fonts)
{
	ResetContent();
	for (int i = 0; i < fonts.GetFontsCount(); i++)
		{
		const CWizFontsEnumerator::Font* pFont = fonts.GetFont(i);
		if (pFont)
			{
			CString name = pFont->Name();
			if (pFont->IsTrueType())
				name += _T("(TT)");

			int j = AddString(name);
			if (j >= 0)
				{
				SetItemData(j, i);
				}
			else
				{
				ASSERT(0);
				}
			}
		else
			{ ASSERT(0); }
		}
	if (fonts.GetFontsCount() > 0)
		SetCurSel(0);
}

BOOL CWizFontNamesComboBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CComboBox::PreCreateWindow(cs);
}

const CWizFontsEnumerator::Font* CWizFontNamesComboBox::GetCurrentFont(const CWizFontsEnumerator& fonts)
{
	int i = GetCurSel();
	if (i >= 0)
	{
		int j = GetItemData(i);
		if (j >= 0)
		{
			const CWizFontsEnumerator::Font* font = fonts.GetFont(j);
			ASSERT(font);
			return font;
		}
		else
		{	ASSERT(0);	}
	}
	else
	{	ASSERT(0); }

	return NULL;
}