#ifndef __JB_LIST_BUTTON_LIST__
#define __JB_LIST_BUTTON_LIST__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   JBListButtonList.hpp  $
// Version        : $Revision:   1.0  $
// Function       : A list of buttons which can be enabled or disabled 
//                  together. Intended for use with list box, each button
//                  can be set to become enabled only if a single item is 
//                  selected, only if multiple items are select, if any number
//                  of items are selected, or if there are more than a certain
//                  number of items (selected or not) in the list box.
//
// Author         : $Author:   Len  $
// Date           : $Date:   Dec 29 1997 11:15:16  $
//
// Notes          : 
// 
// Modifications  :
//
// $Log:   D:/Documents/Len/Sources/Stuff/JBListBoxTest/PVCS/JBListButtonList.hpv  $
// 
//    Rev 1.0   Dec 29 1997 11:15:16   Len
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

#include <afxtempl.h>            // For CTypedPtrList
#include "JBListBox.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file
///////////////////////////////////////////////////////////////////////////////

class CJBListBox::ButtonList;

///////////////////////////////////////////////////////////////////////////////
// CJBListBox::ButtonList
///////////////////////////////////////////////////////////////////////////////

class CJBListBox::ButtonList
{
	public :	

     // Construction and destruction

      ~ButtonList();

      // List maniplulation

		void AddButton(
			CWnd &parentWnd, 
			UINT nButtonID, 
			CJBListBox &theList,
         ItemProcessor *pProcessor = NULL,
         SelectionType_e selection = AnySelection,
			int nItems = 1);

		void AddButton(
			CButton &button, 	
         SelectionType_e selection = AnySelection,
			int nItems = 1);

      // Button manipulation

		void SetButtonState(
         int nItems, 
         int nSelected,
         bool bTopSelected,
         bool bBottomSelected);

      class ListButton;    // Our buttons (this should be private really, but
                           // that causes the message map macros in ListButton
                           // to blow up).
   private :

      class ListNode;      // Our list node class.

      // We're implemented in terms of a CPtrList...

		CTypedPtrList<CPtrList, ListNode *> m_ButtonList;
};

///////////////////////////////////////////////////////////////////////////////
// CJBListBox::ButtonList::ListNode
///////////////////////////////////////////////////////////////////////////////

class CJBListBox::ButtonList::ListNode
{
	public :
		
      // Construction and destruction

		ListNode(
			CButton &theButton, 	
         SelectionType_e selection = AnySelection,
			int nItems = 1);

		ListNode(
			CWnd &parentWnd, 
			UINT nButtonID,
			CJBListBox &theList,
         ItemProcessor *pProcess = NULL,
         SelectionType_e selection = AnySelection,
			int nItems = 1);

		~ListNode();

      // Button manipulation

		void SetButtonState(
         int nItems, 
         int nSelected,
         bool bTopSelected,
         bool bBottomSelected);

	private :

		int m_nItems;
      SelectionType_e m_selection;
      
		bool m_bOurButton;

		CButton *m_pButton;

      // Prevent copying
         
      ListNode(const ListNode &rhs);              // Do not implement
      ListNode &operator=(const ListNode &rhs);   // Do not implement
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __JB_LIST_BUTTON_LIST__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
