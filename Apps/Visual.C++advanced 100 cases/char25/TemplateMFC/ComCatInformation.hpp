#ifndef __COM_CAT_INFORMATION__
#define __COM_CAT_INFORMATION__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   ComCatInformation.hpp  $
// Version        : $Revision:   1.3  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:12:28  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/ComCatInformation.hpv  $
// 
//    Rev 1.3   Oct 25 1998 21:12:28   len
// 
//    Rev 1.2   Oct 25 1998 21:08:42   len
// 
//    Rev 1.1   Jun 06 1998 07:53:38   Len
// 
//    Rev 1.0   May 18 1998 07:34:42   Len
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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#ifndef _INC_TCHAR
#include <tchar.h>
#endif

#ifndef __comcat_h__
#include <comcat.h>
#endif

#pragma warning(disable: 4201)

#ifndef __COM_USES_COM__
#include "ComUsesCom.hpp"
#endif

#ifndef __COM_EXCEPTION__
#include "ComException.hpp"
#endif

#ifndef __COM_CAT_INFO__
#include "ComCatInfo.hpp"
#endif

#ifndef __ITERATE_CATEGORYINFO__
#include "IterateCATEGORYINFO.hpp"
#endif

#ifndef __ITERATE_GUID__
#include "IterateGUID.hpp"
#endif

#ifndef __ITERATE_CATID__
#include "IterateCATID.hpp"
#endif

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
 
///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file...
///////////////////////////////////////////////////////////////////////////////

class CComCatInformation;

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CComCatInformation
///////////////////////////////////////////////////////////////////////////////

class CComCatInformation : private CComUsesCom
{
   public :

      // Exceptions we might throw

      class Exception : public CComException
      {
         private :

            friend class CComCatInformation;

            Exception(LPCTSTR pWhere, HRESULT hr)
               :  CComException(pWhere, hr)
            {
            }
      };

      // Construction and destruction

      CComCatInformation();
      
      ~CComCatInformation();

      // Iterate through all categories

		void EnumCategories(
			IEnumCATEGORYINFO **ppIEnumCatInfo,
			LCID lcid = GetUserDefaultLCID()) const;

		CIterateCATEGORYINFO IterateCategories(
				LCID lcid = GetUserDefaultLCID()) const;
      
      LPCTSTR GetCategoryDesc(
         REFCATID rcatid, 
         LCID lcid = GetUserDefaultLCID()) const;

//      class ComCats;


      CIterateGUID IterateClassesOfCategory(
         REFCATID rcatid) const;
/*
      CIterateGUID IterateClassesOfCategories(
         ComCats &implemented, 
         ComCats &required) const;
*/
      CIterateGUID IterateClassesOfCategories(
         ULONG cImplemented,
         CATID *pCatidImpl, 
         ULONG cRequired = 0, 
         CATID *pCatidReq = 0) const;

      bool IsClassOfCategory(
         REFCLSID rclsid, 
         REFCATID rcatid) const;
/*
      bool IsClassOfCategories(
         REFCLSID rclsid, 
         ComCats &implemented, 
         ComCats &required) const;
*/
      bool IsClassOfCategories(
         REFCLSID rclsid, 
         ULONG cImplemented,
         CATID *pCatidImpl, 
         ULONG cRequired = 0, 
         CATID *pCatidReq = 0) const;

		void EnumImplCategoriesOfClass(
			REFCLSID rclsid,
			IEnumCATID **ppIEnumCATID) const;

		CIterateCATID IterateImplCategoriesOfClass(
			REFCLSID rclsid) const;

		void EnumReqCategoriesOfClass(
			REFCLSID rclsid,
			IEnumCATID **ppIEnumCATID) const;

		CIterateCATID IterateReqCategoriesOfClass(
			REFCLSID rclsid) const;

   private :

      CComCatInformation(const CComCatInformation &rhs);
      CComCatInformation &operator=(const CComCatInformation &rhs);

      ICatInformation *m_pICatInformation;
};

/*
class CComCatManager::ComCats
{
   public :

//      void AddCategory(REFCATID rcatid) { m_array.push_back(rcatid); }

      void AddCategory(REFCATID rcatid) { throw 0; }
      // Access...

//      long GetCount() { return m_array.size(); }

//      CATID *GetArray() { return &(m_array[0]); }

   private :

//      std::vector<CATID> m_array;
};
*/

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __COM_CAT_INFORMATION__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
