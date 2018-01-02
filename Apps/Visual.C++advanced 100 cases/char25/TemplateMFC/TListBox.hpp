#ifndef __TLIST_BOX__
#define __TLIST_BOX__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   TListBox.hpp  $
// Version        : $Revision:   1.1  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:54:50  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/MFCTools/PVCS/TListBox.hpv  $
// 
//    Rev 1.1   Oct 25 1998 21:54:50   len
// 
//    Rev 1.0   May 18 1998 07:44:30   Len
// Initial revision.
// 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 1998 JetByte Limited.
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

#include "TemplateAFX.hpp"
#include "JBListBox.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file...
///////////////////////////////////////////////////////////////////////////////

template <class T> class TListBox;

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TListBox
///////////////////////////////////////////////////////////////////////////////

template <class T> 
class TListBox : public CJBListBox
{
   public : 

      TListBox();

      int AddItem(LPCTSTR lpszItem, T *pItem);
      void DeleteItem(UINT nIndex);
      int InsertItem(int nIndex, LPCTSTR lpszItem, T *pItem);
      T *RemoveItemData(int nIndex);
      T *GetItemData(int nIndex);
      void DeleteAll();

	protected:

      // override to add "just after the window's been created" functionality

      virtual void PostWindowCreate() {}

		// Generated message map functions
		//{{AFX_MSG(TListBox<T>)
		afx_msg void OnDestroy();
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()

      // Overrides
	   // ClassWizard generated virtual function overrides
	   //{{AFX_VIRTUAL(TListBox<T>)
	   virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	   //}}AFX_VIRTUAL

   private :

      bool m_bFirstTime;      // One time switch for PostWindowCreate()
};

BEGIN_TEMPLATE_MESSAGE_MAP(class T, TListBox<T>, CJBListBox)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

template <class T> 
TListBox<T>::TListBox()
   :  m_bFirstTime(true)
{
}

template <class T> 
afx_msg void TListBox<T>::OnDestroy()
{
   DeleteAll();

   CJBListBox::OnDestroy();
}

template <class T> 
int TListBox<T>::AddItem(LPCTSTR lpszItem, T *pItem)
{
   int nIndex = AddString(lpszItem);

   if (nIndex != LB_ERR && nIndex != LB_ERRSPACE)
   {
      if (LB_ERR == SetItemDataPtr(nIndex, pItem))
      {
         DeleteString(nIndex);
         nIndex = LB_ERR;
      }
      else
      {
         CancelSelection();
      }
   }

   return nIndex;
}

template <class T> 
void TListBox<T>::DeleteItem(UINT nIndex)
{
   T *pItem = (T*)GetItemDataPtr(nIndex);

   if (-1 != (int)pItem)
   {
      delete pItem;
      DeleteString(nIndex);
      CancelSelection();
   }
}

template <class T> 
int TListBox<T>::InsertItem(int nIndex, LPCTSTR lpszItem, T *pItem)
{
   int nNewIndex = InsertString(nIndex, lpszItem);

   if (nNewIndex != LB_ERR && nNewIndex != LB_ERRSPACE)
   {
      if (LB_ERR == SetItemDataPtr(nNewIndex, pItem))
      {
         DeleteString(nNewIndex);
         nIndex = LB_ERR;
      }
      else
      {
         CancelSelection();
      }
   }

   return nNewIndex ;
}

template <class T> 
T *TListBox<T>::GetItemData(int nIndex)
{
   T *pItem = (T*)GetItemDataPtr(nIndex);

   if (-1 == (int)pItem)
   {
      pItem = 0;
   }

   return pItem;
}

template <class T> 
T *TListBox<T>::RemoveItemData(int nIndex)
{
   T *pItem = (T*)GetItemDataPtr(nIndex);

   if (-1 != (int)pItem)
   {
      SetItemDataPtr(nIndex, 0);
   }
   else
   {
      pItem = 0;
   }

   return pItem;
}

template <class T> 
void TListBox<T>::DeleteAll()
{
   int nMaxIndex = GetCount();

   for (int i = 0; i < nMaxIndex; i++)
   {
      T *pItem = (T*)GetItemDataPtr(i);

      if (-1 != (int)pItem)
      {
         delete pItem;
      }
   }

   ResetContent();
}

template <class T> 
LRESULT TListBox<T>::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
   if (m_bFirstTime)
   {
      m_bFirstTime = false;
      PostWindowCreate();
   }

	return CJBListBox::DefWindowProc(message, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __TLIST_BOX__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
