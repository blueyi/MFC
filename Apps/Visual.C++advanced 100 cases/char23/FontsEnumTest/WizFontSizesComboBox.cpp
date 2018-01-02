// WizFontSizesComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "fontsTest.h"
#include "WizFontSizesComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizFontSizesComboBox

CWizFontSizesComboBox::CWizFontSizesComboBox()
{
}

CWizFontSizesComboBox::~CWizFontSizesComboBox()
{
}


BEGIN_MESSAGE_MAP(CWizFontSizesComboBox, CComboBox)
	//{{AFX_MSG_MAP(CWizFontSizesComboBox)
	ON_WM_COMPAREITEM_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizFontSizesComboBox message handlers
void	CWizFontSizesComboBox::Initialize (const CWizFontsEnumerator::Font* font)
{
	ResetContent();
	ASSERT(font);

	CWordArray sizes;
	font->FillSizes(sizes);
	const int imax = sizes.GetSize();
	ASSERT(imax > 0);
	CString str;
	for (int i = 0; i < imax; i++)
		{
		int s = sizes[i];
		str.Format(_T("%d"), s);
		int j = AddString(str);
		if (j >= 0)
			{
			SetItemData(j, s);
			}
		else
			{
			ASSERT(0);
			}
		}
	if (imax > 0)
		SetCurSel(0);
}

int CWizFontSizesComboBox::OnCompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	int i = (int(lpCompareItemStruct->itemData1) - int(lpCompareItemStruct->itemData2));
	if (i < 0)
		return -1;
	else if (i == 0)
		return 0;
	else
		return 1;
}

int CWizFontSizesComboBox::GetCurrentSize()
{
	int i = GetCurSel();
	if (i >= 0)
	{
		int j = GetItemData(i);
		if (j >= 0)
		{
			return j;
		}
		else
		{	ASSERT(0);	}
	}
	else
	{	ASSERT(0); }

	return -1;
}

