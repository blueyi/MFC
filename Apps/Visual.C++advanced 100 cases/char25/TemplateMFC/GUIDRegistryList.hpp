#ifndef __GUID_REGISTRY_LIST__
#define __GUID_REGISTRY_LIST__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   GUIDRegistryList.hpp  $
// Version        : $Revision:   1.0  $
// Function       : 
//
// Author         : $Author:   Len  $
// Date           : $Date:   Jun 06 1998 07:55:52  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   D:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/GUIDRegistryList.hpv  $
// 
//    Rev 1.0   Jun 06 1998 07:55:52   Len
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

#ifndef __REGISTRY_LIST__
#include "RegistryList.hpp"
#endif

#ifndef __COM_GUID__
#include "ComGUID.hpp"
#endif

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// Templates defined in this file...
///////////////////////////////////////////////////////////////////////////////

class CGUIDRegistryList;

///////////////////////////////////////////////////////////////////////////////
// CGUIDRegistryList
///////////////////////////////////////////////////////////////////////////////

class CGUIDRegistryList : public TRegistryList<CComGUID>
{
   public :

      CGUIDRegistryList(const CRegistryKey &key);

   private :

      virtual LPCTSTR GetItemName(CComGUID &item);

      virtual void AddItem(CRegistryKey &key, CComGUID &item);
      
      virtual void UpdateItem(CRegistryKey &key, CComGUID &item);

      virtual void RemoveItem(CRegistryKey &key, CComGUID &item);

      virtual CComGUID ReadItem(const iterator &it) const;
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __GUID_REGISTRY_LIST__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
