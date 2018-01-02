///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   ComGUID.cpp  $
// Version        : $Revision:   1.3  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:04:34  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/ComGUID.cpv  $
// 
//    Rev 1.3   Oct 25 1998 21:04:34   len
// Added GetDescription() as an alternative to Description()...
// 
//    Rev 1.2   Oct 25 1998 21:01:06   len
// 
//    Rev 1.1   Jun 06 1998 07:55:04   Len
// 
//    Rev 1.0   May 18 1998 07:34:44   Len
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

///////////////////////////////////////////////////////////////////////////////
// Include files
///////////////////////////////////////////////////////////////////////////////

#include "ComGUID.hpp"
#include "OleString.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// CComGUID
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

CComGUID::CComGUID(const GUID &guid)
   :  m_guid(guid), 
      m_pGuid(0),
      m_pDesc(0),
      m_pRealDesc(0),
      m_regKey(CRegistryKey(HKEY_CLASSES_ROOT).OpenKey(_T("CLSID")).OpenKey(AsString()))
{

}

CComGUID::CComGUID(const CComGUID &rhs)
   :  m_guid(rhs.m_guid),
      m_pGuid(0), 
      m_pDesc(0),
      m_pRealDesc(0),
      m_regKey(rhs.m_regKey)
{
   
}

CComGUID::CComGUID(LPCTSTR pGuidAsString)
   :  m_guid(FromString(pGuidAsString)),
      m_pGuid(0), 
      m_pDesc(0),
      m_pRealDesc(0),
      m_regKey(CRegistryKey(HKEY_CLASSES_ROOT).OpenKey(_T("CLSID")).OpenKey(AsString()))
{
   
}

CComGUID::~CComGUID()
{
   free((void*)m_pGuid);
   free((void*)m_pRealDesc);
   m_pDesc = 0;
}

CComGUID &CComGUID::operator=(const CComGUID &rhs)
{
   if (this != &rhs)
   {
      m_guid = rhs.m_guid;
      free((void*)m_pGuid);
      free((void*)m_pRealDesc);
      m_pGuid = 0;
      m_pDesc = 0;
      m_pRealDesc = 0,

      m_regKey = rhs.m_regKey;
   }

   return *this;
}


LPCTSTR CComGUID::AsString() const
{
   if (!m_pGuid)
   {
      m_pGuid = AsString(m_guid);
   }

   return m_pGuid;
}

LPCTSTR CComGUID::GetDescription() const
{
	return Description();
}

LPCTSTR CComGUID::Description() const
{
   if (!m_pDesc)
   {
      if (m_regKey.QueryValue(NULL, &m_pRealDesc))
      {
         if (*m_pRealDesc == _T('\0'))
         {
            free((void*)m_pRealDesc);
            m_pRealDesc = 0;  
         }
         else
         {
            m_pDesc = m_pRealDesc;
         }
      }

      if (!m_pDesc)
      {
         m_pDesc = AsString();
      }

   }

   return m_pDesc;
}

///////////////////////////////////////////////////////////////////////////////
// Private helpers
///////////////////////////////////////////////////////////////////////////////

GUID CComGUID::FromString(LPCTSTR pGuidAsString) const
{
   GUID guid;

   if (S_OK != IIDFromString((LPOLESTR)_ONCC(pGuidAsString), &guid))
   {
      throw "ARRRGH";
   }

   return guid;

}

LPCTSTR CComGUID::AsString(const GUID &guid)
{
	LPCTSTR pGuidAsString = 0;

   LPOLESTR lpGUIDString;

   if (S_OK == StringFromIID(guid, &lpGUIDString))
   {
      pGuidAsString = COleString(lpGUIDString).DuplicateAs_tchar();

      CoTaskMemFree(lpGUIDString);
   }

   return pGuidAsString;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file...
///////////////////////////////////////////////////////////////////////////////
