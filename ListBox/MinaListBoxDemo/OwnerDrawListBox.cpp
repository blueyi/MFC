// OwnerDrawListBox.cpp : implementation file
//

#include "stdafx.h"
#include "MinaListBoxDemo.h"
#include "OwnerDrawListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox

COwnerDrawListBox::COwnerDrawListBox()
{
}

COwnerDrawListBox::~COwnerDrawListBox()
{
}


BEGIN_MESSAGE_MAP(COwnerDrawListBox, CListBox)
//{{AFX_MSG_MAP(COwnerDrawListBox)
ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox message handlers

// Delete the Pointer which holds the List Box Data Items
void COwnerDrawListBox::Destroy()
{
	int ItemCount;
	ItemCount = GetCount();

	if (ItemCount != 0 )
		for (int i = 0; i < ItemCount; i++)
		{
			m_pListBoxDataItems = (DataItems*) GetItemDataPtr(i);
			delete m_pListBoxDataItems;
		}
}

// This is where is handle the Drag and Drop Event
void COwnerDrawListBox::OnDropFiles(HDROP hDropInfo)
{
	char strFileName[MAX_PATH], strDrive[MAX_PATH], strDir[MAX_PATH], strExt[MAX_PATH];
	char szFilePath[MAX_PATH];
				
	::DragQueryFile (hDropInfo, 0, szFilePath, sizeof (szFilePath));
		
	HICON h = ::ExtractIcon(NULL,szFilePath,0);

	// This function splits the whole path into Drive, Dir, File Name and Extension
	::_splitpath(szFilePath, strDrive, strDir, strFileName, strExt);
		
    if (h)
	{
		// After getting the the Icon handle and the Icon file name,
		// Add them to the list box
		Add(strFileName,h);
    }
    	
	SetCurSel(this->GetCount()-1);
	
	::DragFinish(hDropInfo);
}

void COwnerDrawListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// Changes the Width and the Height of item in the list box	
	lpMeasureItemStruct->itemHeight = 40;
	lpMeasureItemStruct->itemWidth = 100;
}

void COwnerDrawListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	CRect *rectIcon, *rectText;
	
	COLORREF crOldTextColor = pDC->GetTextColor();
	COLORREF crOldBkColor = pDC->GetBkColor();
	
	m_rectListBoxItem = lpDrawItemStruct->rcItem;
	
	// Returns the required struct which holds the Data (Text ,Icon) to be drawn
	DataItems *pListDataItem = (DataItems *)GetItemDataPtr(lpDrawItemStruct->itemID);
	
	// Setting the Text and icon Position in the List Box
	
	// Checking if the User choose to set the text position as he supposed to do so,
	// then see whether if the user has set the icon to the right position or not
	// If yes the text and the icon rects are set to different position
	// if no the text and the icon rects are set to the same position

	// Checking if the User choose to set the Icon position as he supposed to do so,
	// then see whether if the user has set the text to the right position or not
	// If yes the text and the icon rects are set to different position
	// if no the text and the icon rects are set to the same position

	if (m_TextPos == ITEM_RIGHT )
	{
		if (m_IconPos == ITEM_LEFT)
		{
			// Set the Text on the right and the Icon on the left, if the user chooses so
			rectIcon = new CRect(m_rectListBoxItem.left,m_rectListBoxItem.top,m_rectListBoxItem.left+40,m_rectListBoxItem.top+40); 
			rectText = new CRect(rectIcon->right-40,m_rectListBoxItem.top,m_rectListBoxItem.right-20,m_rectListBoxItem.bottom);	
		}else
		{
			// If the user set the icon position on the right as he set the text,
			// draw the text and the icon on the same side
			rectIcon = new CRect(m_rectListBoxItem.left+100,m_rectListBoxItem.top,m_rectListBoxItem.right,m_rectListBoxItem.bottom);
			rectText = new CRect(m_rectListBoxItem.left+40,m_rectListBoxItem.top,m_rectListBoxItem.right-20,m_rectListBoxItem.bottom);
		}
		
		
	}else if (m_TextPos == ITEM_LEFT )
	{
		if (m_IconPos == ITEM_RIGHT)
		{
			// Set the Text on the left and the Icon on the right, if the user chooses so
			rectText = new CRect(m_rectListBoxItem.left+10,m_rectListBoxItem.top,m_rectListBoxItem.left+100,m_rectListBoxItem.bottom);
			rectIcon = new CRect(rectText->right,m_rectListBoxItem.top,m_rectListBoxItem.right,m_rectListBoxItem.bottom);
		}else
		{
			// If the user set the icon position on the left as he set the text,
			// draw the text and the icon on the same side
			rectText = new CRect(m_rectListBoxItem.left+10,m_rectListBoxItem.top,m_rectListBoxItem.left+100,m_rectListBoxItem.bottom);
			rectIcon = new CRect(m_rectListBoxItem.left+10,m_rectListBoxItem.top,m_rectListBoxItem.left+100,m_rectListBoxItem.bottom);
		}
		
		
	}else if ( m_IconPos == ITEM_RIGHT)
	{
		if ( m_TextPos == ITEM_LEFT)
		{
			// Set the Text on the left and the Icon on the right, if the user chooses so
			rectText = new CRect(m_rectListBoxItem.left+10,m_rectListBoxItem.top,m_rectListBoxItem.left+100,m_rectListBoxItem.bottom);
			rectIcon = new CRect(rectText->right,m_rectListBoxItem.top,m_rectListBoxItem.right,m_rectListBoxItem.bottom);
		}
		else
		{
			// If the user set the icon position on the left as he set the text,
			// draw the text and the icon on the same side
			rectIcon = new CRect(m_rectListBoxItem.left+100,m_rectListBoxItem.top,m_rectListBoxItem.right,m_rectListBoxItem.bottom);
			rectText = new CRect(m_rectListBoxItem.left+40,m_rectListBoxItem.top,m_rectListBoxItem.right-20,m_rectListBoxItem.bottom);
		}
	}
	else if ( m_IconPos == ITEM_LEFT)
	{
		if ( m_TextPos == ITEM_RIGHT)
		{
			// Set the text on the right and the icon on the left, if the user chooses so
			rectIcon = new CRect(m_rectListBoxItem.left,m_rectListBoxItem.top,m_rectListBoxItem.left+40,m_rectListBoxItem.top+40); 
			rectText = new CRect(rectIcon->right-40,m_rectListBoxItem.top,m_rectListBoxItem.right-20,m_rectListBoxItem.bottom);	
		}
		else
		{
			// If the user set the icon position on the right as he set the text,
			// draw the text and the icon on the same side
			rectText = new CRect(m_rectListBoxItem.left+10,m_rectListBoxItem.top,m_rectListBoxItem.left+100,m_rectListBoxItem.bottom);
			rectIcon = new CRect(m_rectListBoxItem.left+10,m_rectListBoxItem.top,m_rectListBoxItem.left+100,m_rectListBoxItem.bottom);
			
		}
	}
	else
	{
		// If the user didnt set the Icon or the Text positions, draw them to the default positions
		// The text default position is on the right and the Icon default position is on the left
		rectIcon = new CRect(m_rectListBoxItem.left,m_rectListBoxItem.top,m_rectListBoxItem.left+40,m_rectListBoxItem.bottom); 
		rectText = new CRect(rectIcon->right-40,m_rectListBoxItem.top,m_rectListBoxItem.right-20,m_rectListBoxItem.bottom);	
	}	
	
	
	// If the List box has the focus,
	// draw around the first item the focus rect, which is a black dotted rectangle
	if((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
		(lpDrawItemStruct->itemState & ODS_FOCUS))
		
	{
		CRect rect(m_rectListBoxItem);
		pDC->DrawFocusRect(m_rectListBoxItem);
		
	}
	// If the user has selected an item from the list box, or the selection has been changed
	// draw the item of the list box and fill it with the color of selected item
	else if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
		(lpDrawItemStruct->itemState & ODS_SELECTED))
		
	{	
		CRect rect(m_rectListBoxItem);
		
		// Fill the item rect with the highlight blue color
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem,::GetSysColor(COLOR_HIGHLIGHT));		
		// Set the color of the background of the text rect
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		// Set the color of the text
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));	
		
		// If the user has chosen to set the text and the icon position, draw both
		// If the user has chosen to set the text position only, draw the text only
		// If the user has chosen to set the icon position only, draw the icon only
		if ( m_TextPos == ITEM_LEFT )
		{
			pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
			
			if (m_IconPos == ITEM_RIGHT)
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
			else if (m_IconPos == ITEM_LEFT )
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
		}
		else if (m_TextPos == ITEM_RIGHT)
		{
			pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			
			if(m_IconPos == ITEM_LEFT)
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
			else if ( m_IconPos == ITEM_RIGHT )
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
		}
		else if ( m_IconPos == ITEM_RIGHT )
		{
			pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			
			if ( m_TextPos == ITEM_LEFT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
			else if ( m_TextPos == ITEM_RIGHT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			
		}
		else if ( m_IconPos == ITEM_LEFT)
		{
			pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			
			if ( m_TextPos == ITEM_RIGHT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			else if ( m_TextPos == ITEM_LEFT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
		}
		else
		{
			pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		}
		
	}
	// Draw the icons by the default colors as no item is selected
	else
	{
		// Fill the item rect with white
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);

		// If the user has chosen to set the text and the icon position, draw both
		// If the user has chosen to set the text position only, draw the text only
		// If the user has chosen to set the icon position only, draw the icon only
		
		if ( m_TextPos == ITEM_LEFT )
		{
			pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
			
			if (m_IconPos == ITEM_RIGHT)
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
			else if (m_IconPos == ITEM_LEFT )
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
		}
		else if (m_TextPos == ITEM_RIGHT)
		{
			pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			
			if(m_IconPos == ITEM_LEFT)
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
			else if ( m_IconPos == ITEM_RIGHT )
			{
				pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			}
		}
		else if ( m_IconPos == ITEM_RIGHT )
		{
			pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			
			if ( m_TextPos == ITEM_LEFT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
			else if ( m_TextPos == ITEM_RIGHT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			
		}
		else if ( m_IconPos == ITEM_LEFT)
		{
			pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			
			if ( m_TextPos == ITEM_RIGHT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			else if ( m_TextPos == ITEM_LEFT)
				pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText,DT_VCENTER|DT_SINGLELINE|DT_VCENTER);
		}
		else
		{
			pDC->DrawIcon(rectIcon->left,rectIcon->top,pListDataItem->hIcon);
			pDC->DrawText(pListDataItem->strItemData,strlen(pListDataItem->strItemData),rectText, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		}
		
		
	}
	
	pDC->Detach();	
	delete rectText;
	delete rectIcon;
}

void COwnerDrawListBox::SetTextPosition(Item_Pos Txt_Pos)
{
	m_TextPos = Txt_Pos;
}

void COwnerDrawListBox::SetIconPosition(Item_Pos Ico_Pos)
{
	m_IconPos = Ico_Pos;
}

void COwnerDrawListBox::Add(CString strItemName, HICON hDataIcon)
{
	m_pListBoxDataItems = new DataItems;
	
	m_pListBoxDataItems->hIcon = hDataIcon;
	m_pListBoxDataItems->strItemData = strItemName;
	
	int index = AddString("");
	SetItemDataPtr(index, m_pListBoxDataItems);
}