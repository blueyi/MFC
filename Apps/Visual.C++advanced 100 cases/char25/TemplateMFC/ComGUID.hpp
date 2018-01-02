#ifndef __COM_GUID__
#define __COM_GUID__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   ComGUID.hpp  $
// Version        : $Revision:   1.3  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:05:24  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/ComGUID.hpv  $
// 
//    Rev 1.3   Oct 25 1998 21:05:24   len
// Added GetDescription().
// 
//    Rev 1.2   Oct 25 1998 20:56:32   len
// 
//    Rev 1.1   Jun 06 1998 07:55:10   Len
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

#pragma warning(disable: 4201)   // nameless struct/union

#ifndef _WINDOWS_
//#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#undef WIN32_LEAN_AND_MEAN
#endif

#ifndef _INC_TCHAR
#include <tchar.h>
#endif

#pragma warning(disable: 4201)

#ifndef __REGISTRY_KEY__
#include "RegistryKey.hpp"
#endif 

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
 
///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file...
///////////////////////////////////////////////////////////////////////////////

class CComGUID;

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CComGUID
///////////////////////////////////////////////////////////////////////////////

class CComGUID
{
   public :

		static LPCTSTR AsString(const GUID &guid);


      CComGUID(const GUID &guid);
      CComGUID(const CComGUID &rhs);
      CComGUID(LPCTSTR pGuidAsString);

      ~CComGUID();

      // This is who we are...

      LPCTSTR AsString() const;

      LPCTSTR Description() const;
      LPCTSTR GetDescription() const;

      //bool TreatAs() const;

      operator const GUID() const { return m_guid; }

      //operator LPCTSTR() const { return AsString(); }

      CComGUID &operator=(const CComGUID &rhs);

   private :

      GUID FromString(LPCTSTR pGuidAsString) const;

      GUID m_guid;

      mutable LPCTSTR m_pGuid;

      mutable LPCTSTR m_pDesc;
      mutable LPCTSTR m_pRealDesc;

      CRegistryKey m_regKey;
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __COM_GUID__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
