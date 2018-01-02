///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   JBListBox.cpp  $
// Version        : $Revision:   1.1  $
// Function       : Implements CJBListBox.
//
// Author         : $Author:   Len  $
// Date           : $Date:   May 18 1998 07:38:36  $
//
// Notes          : A class derived from CListBox that supports the "standard" 
//                  list box paradigm of "double clicking an item tends to do 
//                  something with that item" and "we usually have buttons that
//                  cause processes to occur when items are selected".
// 
// Modifications  :
//
// $Log:   D:/Documents/JetByte/Source/JetByteTools/MFCTools/PVCS/JBListBox.cpv  $
// 
//    Rev 1.1   May 18 1998 07:38:36   Len
// Reflected message handlers are now implemented using ON_CONTROL_REFLECT_EX
// and return FALSE so that the control's parent can handle the message too if
// it wants to.
// 
//    Rev 1.0   Dec 29 1997 11:14:58   Len
// Initial revision.
//
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 1997 JetByte Limited.
//
// JetByte Limited grants you ("Licensee") a non-exclusive, royalty free, 
// licence to use, modify and redistribute this software in source and binary 
// code form, provided that i) this copyright notice and licence appear on all 
// copies of the software; and ii) Licensee does not utilize the software in a 
// manner which is disparaging to JetByte Limited.
//
// This software is provided "AS IS," without a warranty of any kind. ALL
// EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING 
// ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
// OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED. JETBYTE LIMITED AND ITS LICENSORS 
// SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF 
// USING, MODIFYING OR DISTRIBUTING THE SOFTWARE OR ITS DERIVATIVES. IN NO 
// EVENT WILL JETBYTE LIMITED BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, 
// OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE 
// DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, ARISING 
// OUT OF THE USE OF OR INABILITY TO USE SOFTWARE, EVEN IF JETBYTE LIMITED 
// HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// This software is not designed or intended for use in on-line control of
// aircraft, air traffic, aircraft navigation or aircraft communications; or in
// the design, construction, operation or maintenance of any nuclear
// facility. Licensee represents and warrants that it will not use or
// redistribute the Software for such purposes.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JBListBox.hpp"
#include "JBListButtonList.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// MFC/Class wizard things...
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

CJBListBox::CJBListBox()
   : m_pButtonList(0), m_pDefaultProcessor(0)
{
   // All the work done in the initialiser list...
}

CJBListBox::~CJBListBox()
{
   delete m_pButtonList;

   // Keep lint happy...

   m_pButtonList = 0;
   m_pDefaultProcessor = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Message map
///////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CJBListBox, CListBox)
	//{{AFX_MSG_MAP(CJBListBox)
	ON_CONTROL_REFLECT_EX(LBN_DBLCLK, OnDblclk)
	ON_CONTROL_REFLECT_EX(LBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// Message handlers
///////////////////////////////////////////////////////////////////////////////

BOOL CJBListBox::OnDblclk() 
{
   ProcessSelectedItems();

   return FALSE;   // Allow container to process the message too if it wants
}

BOOL CJBListBox::OnSelchange() 
{
	SetButtonState();

   return FALSE;   // Allow container to process the message too if it wants
}

///////////////////////////////////////////////////////////////////////////////
// List box manipulation
///////////////////////////////////////////////////////////////////////////////

// SelectItem()
// Selects the supplied item.
// Selects all items if passed -1 as the index.

int CJBListBox::SelectItem(const int nIndex) 
{
   int actualIndex = SetSel(nIndex, TRUE);
	
   if (LB_ERR == actualIndex && nIndex != -1)
   {
      actualIndex = SetCurSel(nIndex);
   }

	SetButtonState();

   return actualIndex;
}

// CancelSelection()
// Deselects the supplied item.
// Clears the entire selection if passed -1 as the index.

int CJBListBox::CancelSelection(const int nIndex /* -1 */) 
{
   int actualIndex = SetSel(nIndex, FALSE);

	if (LB_ERR == actualIndex && 
      (-1 == nIndex || nIndex == GetCurSel()))
   {
      actualIndex = SetCurSel(-1);
   }

	SetButtonState();

   return actualIndex;
}

// InsertItem()
// Inserts an item, with optional associated item data.

int CJBListBox::InsertItem(
   const int nIndex, 
   const CString &theString, 
   void *pData /* = NULL */)
{
	int actualIndex = InsertString(nIndex, theString);

	if (LB_ERR != actualIndex)
	{
		if (LB_ERR == SetItemDataPtr(actualIndex, pData))
		{
			DeleteString((UINT)actualIndex);
			actualIndex = LB_ERR;
		}
		else
		{
         // could allow this item to be selected automatically, 
         // could allow it to be added to a multi selection...
			CancelSelection();
		}
	}

	return actualIndex;
}

// AddItem()
// Adds an item, with optional associated item data.

int CJBListBox::AddItem(const CString &theString, void *pData /* = NULL */)
{
	int nIndex = AddString(theString);

	if (LB_ERR != nIndex)
	{
		if (LB_ERR == SetItemDataPtr(nIndex, pData))
		{
			DeleteString((UINT)nIndex);
			nIndex = LB_ERR;
		}
		else
		{
         // could allow this item to be selected automatically, 
         // could allow it to be added to a multi selection...
			CancelSelection();
		}
	}

	return nIndex;
}

// RemoveItem()

int CJBListBox::RemoveItem(const UINT nIndex)
{
   int results = DeleteString(nIndex);

   SetButtonState();

   return results;
}

int CJBListBox::MoveItemUp(
   const UINT nIndex, 
   const bool bSelectAfterMove /* = false*/)
{
   return MoveItem(nIndex, -1, bSelectAfterMove);
}

int CJBListBox::MoveItemDown(
   const UINT nIndex, 
   const bool bSelectAfterMove /* = false*/)
{
   return MoveItem(nIndex, 1, bSelectAfterMove);
}

// ItemProcessor
// Sets the item processor that will be used to process double clicks on
// items in the list box and returns the old processor.

CJBListBox::ItemProcessor *CJBListBox::SetDefaultProcessor(
   ItemProcessor *pProcessor)
{
	ItemProcessor *oldProcessor = m_pDefaultProcessor;

	m_pDefaultProcessor = pProcessor;

	return oldProcessor;
}

// ProcessSelectedItems()
// Processes the selected items with the supplied processor, or the default 
// processor if none is supplied.

void CJBListBox::ProcessSelectedItems(ItemProcessor *pProcessor /* = NULL */)
{
   if (!pProcessor)
   {
      pProcessor = m_pDefaultProcessor;
   }
	
	if (pProcessor)
   {
	   int numSelected = GetSelectionCount();

	   if (0 != numSelected)
	   {
		   // TODO: these could be members and we could cache the memory...

		   int *pSelectedItems = new int[numSelected];
		   PostProcessAction_e *pActions = new PostProcessAction_e[numSelected];
		   
		   int selected = GetSelectedItems(numSelected, pSelectedItems);

		   ASSERT(selected == numSelected);

		   int i;

		   for (i = 0; i < selected; i++)
		   {
            pActions[i] = NoAction; // By default, do nothing after processing
            
            ProcessSelectedItem(pProcessor, 
               pSelectedItems[i], 
               pActions[i]); 
		   }

		   // deselect or delete items in reverse order so that we don't have 
         // to reshuffle the indexes as we delete

         // we can also move down in reverse order, but we can't move up as
         // cases where we have 2 items next to each other that both need to
         // be moved up will not work.

         bool bMoveUpRequired = false;

		   for (i = selected - 1; i >= 0; i--)
		   {
			   if (Delete == pActions[i])
			   {
				   RemoveItem((UINT)pSelectedItems[i]);
			   }
            else if (Unselect == pActions[i])
            {
               CancelSelection(pSelectedItems[i]);
            }
            else if (pActions[i] & MoveUp)
            {
               bMoveUpRequired = true;
            }
            else if (pActions[i] & MoveDown)
            {
               MoveItemDown(pSelectedItems[i], !(pActions[i] & Unselect));
            }
		   }

         if (bMoveUpRequired)
         {
            // For a multiple selection move up to work we need to process
            // the items in order..

            for (i = 0; i < selected; i++)
		      {
               if (pActions[i] & MoveUp)
               {
                  MoveItemUp(pSelectedItems[i], !(pActions[i] & Unselect));
               }
            }
         }

		   delete[] pSelectedItems;
		   delete[] pActions;
	   }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Button association
///////////////////////////////////////////////////////////////////////////////

// AssociateButton
// Associates the supplied button with the list box.
// The button's state (enabled/disabled) will be managed by the list box.
// The button can be set to be enabled when a single item is selected, 
// when multiple items are selected and when there are more than n items 
// in the list box.

void CJBListBox::AssociateButton(
	CButton &theButton, 
   SelectionType_e selection  /* = AnySelection*/,
	int nItems				      /* = 1 */)
{
   if (!m_pButtonList)
   {
      m_pButtonList = new ButtonList;

      if (!m_pButtonList)
      {
         throw ENoMemory();
      }
   }

	m_pButtonList->AddButton(
      theButton, 
      selection,
      nItems);

	SetButtonState();
}

// AssociateButton
// As above but the button with the supplied ID is associated to the list box.

void CJBListBox::AssociateButton(
	UINT nButtonID, 
   ItemProcessor *pProcess    /* = NULL */, 
   SelectionType_e selection  /* = AnySelection */,
	int nItems				      /* = 1 */)
{
	CWnd *pParent = GetParent();
	
	ASSERT(pParent);

   if (!m_pButtonList)
   {
      m_pButtonList = new ButtonList;

      if (!m_pButtonList)
      {
         throw ENoMemory();
      }
   }

	m_pButtonList->AddButton(
      *pParent, 
      nButtonID, 
      *this, 
      pProcess, 
      selection,
      nItems);

	SetButtonState();
}

///////////////////////////////////////////////////////////////////////////////
// Helper functions
///////////////////////////////////////////////////////////////////////////////

// GetSelectionCount()
// Returns the number of selected items in the list box. Handles the fact that
// GetSelCount() only works for multi selection list boxes and you need to 
// use GetCurSel() if you have a single selection box.

int CJBListBox::GetSelectionCount()
{
	int numSelected = GetSelCount();

	if (LB_ERR == numSelected)
	{
		numSelected = (GetCurSel() != LB_ERR) ? 1 : 0;
	}

	return numSelected;
}

// GetSelectedItems()
// Returns an array of selected items.
// Handles the fact that GetSelItems() only works for multi selection list
// boxes and you have to use GetCurSel() if the box is single selection.

int CJBListBox::GetSelectedItems(const int nMaxItems, LPINT rgIndex)
{
   int numItems = GetSelItems(nMaxItems, rgIndex);
   
   if (LB_ERR == numItems && nMaxItems > 0)
   {
      int nIndex = GetCurSel();
      
      if (LB_ERR != nIndex)
      {
         rgIndex[0] = nIndex;
         numItems = 1;
      }
   }
   
   return numItems;
}

// SetButtonState()
// Updates the state of all associated buttons based on the number of items
// in the box and the number of items that are selected.

void CJBListBox::SetButtonState()
{
   if (m_pButtonList)
   {
      bool bTopSelected;
      bool bBottomSelected;
      
      TopOrBottomSelected(bTopSelected, bBottomSelected);

	   m_pButtonList->SetButtonState(
         GetCount(), 
         GetSelectionCount(),
         bTopSelected,
         bBottomSelected);
   }
}

// MoveItem
// Does the grunt work for MoveItemUp() and MoveItemDown()
// Could be used to move an item by any offset...

int CJBListBox::MoveItem(
   const UINT nIndex, 
   const int nOffset,
   const bool bSelectAfterMove)
{
   int result = LB_ERR;

   CString theString;

   GetText((int)nIndex, theString);

   if (!theString.IsEmpty())
   {
      void *pData = GetItemDataPtr((int)nIndex);

      if (LB_ERR != RemoveItem(nIndex))
      {
         result = InsertItem(nIndex + nOffset, theString, pData);

         if (LB_ERR !=  result && bSelectAfterMove)
         {
            result = SelectItem(result);
         }
      }
   }

   return result;
}

void CJBListBox::TopOrBottomSelected(bool &bTopSelected, bool &bBottomSelected)
{
   bTopSelected = false;
   bBottomSelected = false;

   int numSelected = GetSelectionCount();

   if (0 != numSelected)
   {
      int *pSelectedItems = new int[numSelected];  // cache this?
	   
      int selected = GetSelectedItems(numSelected, pSelectedItems);

	   ASSERT(selected == numSelected);

      if (pSelectedItems[0] == 0)
      {
         bTopSelected = true;
      }

      // The index of the last item is 1 less than the number of items in
      // the box.

      if (pSelectedItems[numSelected - 1] == GetCount() - 1)
      {
         bBottomSelected = true;
      }

      delete[] pSelectedItems;
   }
}

// ProcessSelectedItem()
// Obtains the item's string and item data and lets the supplied item
// processor process the item.

void CJBListBox::ProcessSelectedItem(
   ItemProcessor *pProcessor, 
   const int nIndex,
   PostProcessAction_e &action)
{
	ASSERT(LB_ERR != nIndex);

	if (LB_ERR != nIndex)
	{
		CString theString;

		GetText(nIndex, theString);

		void *pData = GetItemDataPtr(nIndex);

		if (pProcessor)
		{
			 pProcessor->ProcessSelectedItem(nIndex, 
             theString, 
             pData, 
             action);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////





