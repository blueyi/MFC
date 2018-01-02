#ifndef __JB_LIST_BOX_PAIR__
#define __JB_LIST_BOX_PAIR__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   JBListBoxPair.hpp  $
// Version        : $Revision:   1.0  $
// Function       : A pair of CJBListBoxes with at least one button associated 
//                  with each list box. The default processing action for the
//                  list boxes is to move the item to the other box.
//                  
//
// Author         : $Author:   Len  $
// Date           : $Date:   Dec 29 1997 11:15:14  $
//
// Notes          : 
// 
// Modifications  :
//
// $Log:   D:/Documents/Len/Sources/Stuff/JBListBoxTest/PVCS/JBListBoxPair.hpv  $
// 
//    Rev 1.0   Dec 29 1997 11:15:14   Len
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

#include "JBListBox.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file
///////////////////////////////////////////////////////////////////////////////

class CJBListBoxPair;         // The pair of list boxes...

///////////////////////////////////////////////////////////////////////////////
// class CJBListBoxPair
///////////////////////////////////////////////////////////////////////////////

class CJBListBoxPair
{
	public :

      // Construction and destruction

		CJBListBoxPair();

      void Create(CWnd &parentWnd,
	      UINT nList1ID, 
	      UINT nList2ID, 
	      UINT nButton1ID, 
	      UINT nButton2ID);

      CJBListBox m_box1;              
      CJBListBox m_box2;              
      
 	private :

      // Our standard list processor

      class ListSwapProcessor : public CJBListBox::ItemProcessor
		{
			public :

            // Construction and destruction

				ListSwapProcessor(CJBListBox &list);

            // Implement ItemProcessor

            virtual void ProcessSelectedItem(
               const int nIndex,                      
               const CString &theString,              
               void *pData,                           
               CJBListBox::PostProcessAction_e &action);  

			private :

				CJBListBox *m_pList; // The list we add items to
		};

		ListSwapProcessor m_list1Processor; // The default processors
		ListSwapProcessor m_list2Processor;
};
	
///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __JB_LIST_BOX_PAIR__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
