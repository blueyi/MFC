///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   JBListButton.cpp  $
// Version        : $Revision:   1.1  $
// Function       : Implements CJBListBox::ButtonList::ListButton.
//
// Author         : $Author:   Len  $
// Date           : $Date:   May 18 1998 07:42:40  $
//
// Notes          : A button that can be associated with a list box. The box
//                  is supplied a processor which it can apply to the items
//                  in the list box when it is pressed.
//
//                  Had to jump through a few hoops to get a nested class to
//                  work with the message map macros.
// 
// Modifications  :
//
// $Log:   D:/Documents/JetByte/Source/JetByteTools/MFCTools/PVCS/JBListButton.cpv  $
// 
//    Rev 1.1   May 18 1998 07:42:40   Len
// Changes to make the code compile as UNICODE.
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
// Helper functions
/////////////////////////////////////////////////////////////////////////////

inline bool BOOL_to_bool(const BOOL bResult)
{
   // Convert a make believe BOOL into a real bool.
   // Removes warning C4800...

   return (TRUE == bResult);
}

/////////////////////////////////////////////////////////////////////////////
// Construction and destruction 
/////////////////////////////////////////////////////////////////////////////

CJBListBox::ButtonList::ListButton::ListButton(
   CJBListBox &list, 
   ItemProcessor *pProcessor /* = NULL */)
	:	m_pProcessor(pProcessor),
		m_pList(&list)
{
	// All work done in initialiser list
}

///////////////////////////////////////////////////////////////////////////////
// Message map
///////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CJBListBox::ButtonList::ListButton, CBitmapButton)
	//{{AFX_MSG_MAP(CJBListBox::ButtonList::ListButton)
	ON_CONTROL_REFLECT(BN_CLICKED, CJBListBox::ButtonList::ListButton::OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// Message handlers
///////////////////////////////////////////////////////////////////////////////

void CJBListBox::ButtonList::ListButton::OnClicked() 
{
	// if we have a custom process, use it, else use default

	if (m_pProcessor)
	{
		m_pList->ProcessSelectedItems(m_pProcessor);
	}
	else
	{
		m_pList->ProcessSelectedItems();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Button subclassing...
///////////////////////////////////////////////////////////////////////////////


// Connect()
// Connect the button to a dialog item, like SubclassDlgItem only it
// distinguishes between the button being a CBitmapButton (and needing
// AutoLoad() called and a normal CButton which only needs SubclassDlgItem.

bool CJBListBox::ButtonList::ListButton::Connect(UINT nButtonID, CWnd &parentWnd)
{
	CButton *pButton = (CButton*)parentWnd.GetDlgItem(nButtonID);

	ASSERT(pButton);

   bool ok = false;

   if (pButton)
   {
	   // If the BS_OWNERDRAW bit is set in the button's style bits...

	   if (!(BS_OWNERDRAW & ~pButton->GetButtonStyle()))
	   {
		   // We're an owner draw button, so we should have the appropriate 
		   // bitmaps available to be a normal CBitmapButton

         ok = BOOL_to_bool(AutoLoad(nButtonID, &parentWnd));

		   if (!ok)
		   {
		      TRACE0("CJBListButton::Connect() - AutoLoad of button failed - No bitmaps?");
		   }
	   }
	   else
	   {
		   // We're just a normal button, so we just attach like a normal button
	   
         ok = BOOL_to_bool(SubclassDlgItem(nButtonID, &parentWnd));

		   if (!ok)
		   {
			   TRACE0("CJBListButton::Connect() - Failed to attach to button - Already has a CButton attached?");
		   }
	   }
   }
   else 
	{
      TRACE(_T("CJBListButton::Connect() - Can't locate button with ID of %d"), nButtonID);
	}
   
   return ok;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
