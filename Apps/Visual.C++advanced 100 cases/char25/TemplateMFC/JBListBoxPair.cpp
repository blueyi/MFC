///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   JBListBoxPair.cpp  $
// Version        : $Revision:   1.0  $
// Function       : Implements CJBListBoxPair.
//
// Author         : $Author:   Len  $
// Date           : $Date:   Dec 29 1997 11:14:58  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   D:/Documents/Len/Sources/Stuff/JBListBoxTest/PVCS/JBListBoxPair.cpv  $
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
#include "JBListBoxPair.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// CJBListBoxPair
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

CJBListBoxPair::CJBListBoxPair()
   :  m_list1Processor(m_box2),
      m_list2Processor(m_box1)
{
   // All work done in the initialiser list
}

///////////////////////////////////////////////////////////////////////////////
// Control manipulation
///////////////////////////////////////////////////////////////////////////////

void CJBListBoxPair::Create(CWnd &parentWnd,
	UINT nList1ID, 
	UINT nList2ID, 
	UINT nButton1ID, 
	UINT nButton2ID)
{
	m_box1.SubclassDlgItem(nList1ID, &parentWnd);

	m_box1.AssociateButton(nButton1ID);

	m_box1.SetDefaultProcessor(&m_list1Processor);


	m_box2.SubclassDlgItem(nList2ID, &parentWnd);

	m_box2.AssociateButton(nButton2ID);

	m_box2.SetDefaultProcessor(&m_list2Processor);
}

///////////////////////////////////////////////////////////////////////////////
// End of CJBListBoxPair
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CJBListBoxPair::ListSwapProcessor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

CJBListBoxPair::ListSwapProcessor::ListSwapProcessor(CJBListBox &list)
	: m_pList(&list)
{
   // All work done in initialiser list
}

///////////////////////////////////////////////////////////////////////////////
// Implement CJBListProcessor
///////////////////////////////////////////////////////////////////////////////

void CJBListBoxPair::ListSwapProcessor::ProcessSelectedItem(
   const int,                      
   const CString &theString,              
   void *pData,                           
   CJBListBox::PostProcessAction_e &action)
{
	m_pList->AddItem(theString, pData);

   action = CJBListBox::Delete;
}

///////////////////////////////////////////////////////////////////////////////
// End of CJBListBoxPair::ListSwapProcessor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
