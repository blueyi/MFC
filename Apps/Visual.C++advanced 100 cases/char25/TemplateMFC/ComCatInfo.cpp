///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   ComCatInfo.cpp  $
// Version        : $Revision:   1.2  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:15:40  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/ComCatInfo.cpv  $
// 
//    Rev 1.2   Oct 25 1998 21:15:40   len
// 
//    Rev 1.1   Jun 06 1998 07:52:56   Len
// 
//    Rev 1.0   May 18 1998 07:34:38   Len
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

#include "ComCatInfo.hpp"
#include "OleString.hpp"
#include "ComCatInformation.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// CComCatInfo
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

CComCatInfo::CComCatInfo(const CATEGORYINFO &catInfo)
   :  m_catInfo(catInfo), 
      m_pDesc(0), 
      m_pGuid(0)
{
#ifdef _UNICODE
   m_pDesc = m_catInfo.szDescription;
#endif
}

CComCatInfo::CComCatInfo(const CATID &catid)
   :  m_pDesc(0), 
      m_pGuid(0)
{
	m_catInfo.catid = catid;

	CComCatInformation CatMgr;
	
   LPCTSTR pDesc = CatMgr.GetCategoryDesc(catid);

	wcsncpy(m_catInfo.szDescription, _O(pDesc), 127);

	free((void*)pDesc);

	m_catInfo.lcid = GetUserDefaultLCID();

#ifdef _UNICODE
   m_pDesc = m_catInfo.szDescription;
#endif
}

CComCatInfo::~CComCatInfo()
{
#ifndef _UNICODE
   free(m_pDesc);
#endif
   free(m_pGuid);
}

CComCatInfo &CComCatInfo::operator=(const CComCatInfo &rhs)
{
   if (this != &rhs)
   {
      m_catInfo = rhs.m_catInfo;
#ifndef _UNICODE
		free(m_pDesc);
#endif
      free((void*)m_pGuid);
      m_pGuid = 0;
      m_pDesc = 0;
   }

   return *this;
}


///////////////////////////////////////////////////////////////////////////////
// This is who we are...
///////////////////////////////////////////////////////////////////////////////

CATID CComCatInfo::GetCATID() const
{
   return m_catInfo.catid;
}

LPCTSTR CComCatInfo::GetCATIDAsString() const
{
   if (!m_pGuid)
   {
      LPOLESTR lpGUIDString;

      if (S_OK == StringFromIID(m_catInfo.catid, &lpGUIDString))
      {
         m_pGuid = COleString(lpGUIDString).DuplicateAs_tchar();
  
         CoTaskMemFree(lpGUIDString);
      }
   }

   return m_pGuid;
}

LCID CComCatInfo::GetLCID() const
{
   return m_catInfo.lcid;
}

LPCTSTR CComCatInfo::GetDescription() const
{

#ifndef _UNICODE
   if (!m_pDesc)
   {
      m_pDesc = COleString(m_catInfo.szDescription).DuplicateAs_tchar();
   }
#endif

   return m_pDesc;
}


///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file...
///////////////////////////////////////////////////////////////////////////////
