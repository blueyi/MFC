///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   JBListButtonList.cpp  $
// Version        : $Revision:   1.0  $
// Function       : Implements CJBListButtonList.
//
// Author         : $Author:   Len  $
// Date           : $Date:   Dec 29 1997 11:15:00  $
//
// Notes          : A list of buttons which can be enabled or disabled 
//                  together. Intended for use with list box, each button
//                  can be set to become enabled only if a single item is 
//                  selected, only if multiple items are select, if any number
//                  of items are selected, or if there are more than a certain
//                  number of items (selected or not) in the list box.
//
// Modifications  :
//
// $Log:   D:/Documents/Len/Sources/Stuff/JBListBoxTest/PVCS/JBListButtonList.cpv  $
// 
//    Rev 1.0   Dec 29 1997 11:15:00   Len
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
#include "JBListButtonList.hpp"
#include "JBListButton.hpp"

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

/////////////////////////////////////////////////////////////////////////////
// CJBListBox::ButtonList
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Construction and destruction 
/////////////////////////////////////////////////////////////////////////////

CJBListBox::ButtonList::~ButtonList()
{
	POSITION pos = m_ButtonList.GetHeadPosition();

	while (pos)
	{
		ListNode *pButtonNode = (ListNode *)m_ButtonList.GetNext(pos);

		delete pButtonNode;
	}
}

/////////////////////////////////////////////////////////////////////////////
// List maniplulation
/////////////////////////////////////////////////////////////////////////////

void CJBListBox::ButtonList::AddButton(
	CWnd &parentWnd, 
	UINT nButtonID, 
	CJBListBox &theList,
   ItemProcessor *pProcessor	      /* = NULL */,
   SelectionType_e selection  /*= AnySelection*/,
	int nItems				      /* = 1 */)
{
	ListNode *pButtonNode = new ListNode(parentWnd, 
	   nButtonID, 
	   theList, 
	   pProcessor, 
	   selection, 
	   nItems);

	if (!pButtonNode)
	{
		throw ENoMemory();
	}

	m_ButtonList.AddTail(pButtonNode);
}

void CJBListBox::ButtonList::AddButton(
	CButton &button, 	
   SelectionType_e selection  /* = AnySelection*/,
	int nItems				      /* = 1 */)
{
	ListNode *pButtonNode = new ListNode(button, 
										selection,
										nItems);
	if (!pButtonNode)
	{
		throw ENoMemory();
	}

	m_ButtonList.AddTail(pButtonNode);
}

void CJBListBox::ButtonList::SetButtonState(
   int nItems, 
   int nSelected,
   bool bTopSelected,
   bool bBottomSelected)
{
	POSITION pos = m_ButtonList.GetHeadPosition();

	while (pos)
	{
		ListNode *pButtonNode = m_ButtonList.GetNext(pos);

		ASSERT(pButtonNode);

		pButtonNode->SetButtonState(
         nItems, 
         nSelected, 
         bTopSelected, 
         bBottomSelected);
	}

}

/////////////////////////////////////////////////////////////////////////////
// End of CJBListButtonList
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CJBListBox::ButtonList::ListNode
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Construction and destruction
/////////////////////////////////////////////////////////////////////////////

CJBListBox::ButtonList::ListNode::ListNode(
	CButton &theButton, 
   SelectionType_e selection  /* = AnySelection*/,
	int nItems				      /* = 1 */)
	:	m_nItems(nItems),
		m_selection(selection),
		m_bOurButton(false),
		m_pButton(&theButton)
{
   // All the work's done in the initialiser list...
}

CJBListBox::ButtonList::ListNode::ListNode(
	CWnd &parentWnd, 
	UINT nButtonID,
	CJBListBox &theList,
   ItemProcessor *pProcess	   /* = NULL */,
   SelectionType_e selection  /* = AnySelection*/,
	int nItems				      /* = 1 */)
	:	m_nItems(nItems),
		m_selection(selection),
		m_bOurButton(false),
		m_pButton(NULL)
{
	ListButton *pButton = new ListButton(theList, pProcess);

	if (!pButton)
	{
		throw ENoMemory();
	}

	pButton->Connect(nButtonID, parentWnd);

	m_bOurButton = true;
	m_pButton = pButton;
}

CJBListBox::ButtonList::ListNode::~ListNode()
{
	if (m_bOurButton)
	{
		delete m_pButton;
		m_pButton = NULL;
	}
}

void CJBListBox::ButtonList::ListNode::SetButtonState(
   int nItems, 
   int nSelected,
   bool bTopSelected,
   bool bBottomSelected)
{
	ASSERT(m_pButton);

	bool bEnable = false;

	if (nItems >= m_nItems)
	{
		// There are enough items in the list box to enable this button.

		if (m_selection == NoSelection)
		{
			bEnable = true;
		} 
      else if ((m_selection & SingleSelection) && (nSelected == 1))
		{
			bEnable = true;
		}
		else if ((m_selection & MultiSelection) && (nSelected > 1))
		{
			bEnable = true;
		}

      // Now check to see if we are allowed to select the top or bottom
      // element...
         
      if (bEnable && 
          ((m_selection & NotTop) && bTopSelected) ||
          ((m_selection & NotBottom) && bBottomSelected))
      {
         bEnable = false;
      }
	}

   if (m_pButton)
   {
	   m_pButton->EnableWindow(bEnable);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
