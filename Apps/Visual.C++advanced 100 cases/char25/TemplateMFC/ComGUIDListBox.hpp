#ifndef __COM_GUID_LIST_BOX__
#define __COM_GUID_LIST_BOX__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   ComGUIDListBox.hpp  $
// Version        : $Revision:   1.3  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:51:06  $
//
// Notes          : 
// 
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/MFCTools/PVCS/ComGUIDListBox.hpv  $
// 
//    Rev 1.3   Oct 25 1998 21:51:06   len
// 
//    Rev 1.2   Oct 25 1998 21:34:10   len
// 
//    Rev 1.1   Jun 06 1998 07:50:24   Len
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

#ifndef __AFXWIN_H__
#include "afxwin.h"
#endif

#ifndef __TLIST_BOX__
#include "TListBox.hpp"
#endif

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file
///////////////////////////////////////////////////////////////////////////////

template <class I, class T> class TComGUIDListBox;

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// TComGUIDListBox
///////////////////////////////////////////////////////////////////////////////

template <class I, class T> 
class TComGUIDListBox : public TListBox<T>
{
   public:

      TComGUIDListBox(
         const I &begin, 
         const I &end);

      virtual ~TComGUIDListBox();

      T *GetSelectedClass() const;

		void Populate(
			const I &begin, 
			const I &end);

protected:

   virtual void PostWindowCreate();
 
   // Generated message map functions
   //{{AFX_MSG(CComCatObjectList)
	//afx_msg BOOL OnSelchange();
	afx_msg void OnDestroy();
	//afx_msg BOOL OnSelcancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


private :

   I m_begin;
   const I m_end;

   T *m_pGuid;
};

template <class I, class T>
TComGUIDListBox<I,T>::TComGUIDListBox(
      const I &begin, 
      const I &end)
      : m_begin(begin), m_end(end), m_pGuid(0)
{

}


template <class I, class T>
TComGUIDListBox<I,T>::~TComGUIDListBox()
{
   delete m_pGuid;
}


BEGIN_TEMPLATE_MESSAGE_MAP(TEMPLATE_2(class I, class T), TCLASS_2(TComGUIDListBox, I, T), TListBox<T>)
//BEGIN_MESSAGE_MAP(TComGUIDListBox, TListBox<T>)
	//{{AFX_MSG_MAP(TComGUIDListBox)
//	ON_CONTROL_REFLECT_EX(LBN_SELCHANGE, OnSelchange)
	ON_WM_DESTROY()
//	ON_CONTROL_REFLECT_EX(LBN_SELCANCEL, OnSelcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TComGUIDListBox message handlers

/*template <class I, class T>
BOOL TComGUIDListBox<I,T>::OnSelchange() 
{
   int index = GetCurSel();
   
   m_pGuid = GetItemData(index);

   return TListBox<T>::OnSelchange();
}
*/
template <class I, class T>
T *TComGUIDListBox<I,T>::GetSelectedClass() const
{
   return m_pGuid;
}

template <class I, class T>
void TComGUIDListBox<I,T>::OnDestroy() 
{
   int nIndex = GetCurSel();						// can't use this if it might be multi select

	if (LB_ERR != nIndex)
	{
		m_pGuid = new T(*GetItemData(nIndex));
   }

   TListBox<T>::OnDestroy();
}

template <class I, class T>
void TComGUIDListBox<I,T>::PostWindowCreate()
{
	Populate(m_begin, m_end);
}

template <class I, class T>
void TComGUIDListBox<I,T>::Populate(const I &begin, const I &end)
{
   for (I i = begin; i != end; ++i)
   {
		try
		{
			T *pT = new T(i);

			if (pT)
			{
			   AddItem(pT->GetDescription(), pT);
			}
		}
		catch (...)
		{
		}
   }
}

/*
template <class I, class T>
BOOL TComGUIDListBox<I,T>::OnSelcancel() 
{
  m_pGuid = 0;

   return FALSE;   // Allow container to handle if it wants
//   TListBox<T>::OnSelcancel();
}
*/
///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __COM_GUID_LIST_BOX__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
