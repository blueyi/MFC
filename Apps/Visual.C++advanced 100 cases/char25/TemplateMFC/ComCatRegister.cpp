///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   ComCatRegister.cpp  $
// Version        : $Revision:   1.2  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:08:16  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/ComCatRegister.cpv  $
// 
//    Rev 1.2   Oct 25 1998 21:08:16   len
// 
//    Rev 1.1   Jun 06 1998 07:54:08   Len
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

///////////////////////////////////////////////////////////////////////////////
// Include files
///////////////////////////////////////////////////////////////////////////////

#include "ComCatRegister.hpp"
#include "OleString.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// CComCatRegister
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

CComCatRegister::CComCatRegister()
   :  CComUsesCom(),
      m_pICatRegister(0)
{
   HRESULT hr = CoCreateInstance(
      CLSID_StdComponentCategoriesMgr,
      NULL, 
      CLSCTX_INPROC_SERVER, 
      IID_ICatRegister, 
      (void**) &m_pICatRegister);

   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatRegister::CComCatRegister()"), hr);
   }
}

CComCatRegister::~CComCatRegister()
{
   m_pICatRegister->Release();
   m_pICatRegister = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Do stuff
///////////////////////////////////////////////////////////////////////////////


void CComCatRegister::RegisterCategory(
         REFCLSID rcatid, 
         LPCTSTR lpCatDesc,
         LCID lcid /* = GetUserDefaultLCID() */) const
{
   CATEGORYINFO catInfo;

   catInfo.catid = rcatid;
   catInfo.lcid = lcid; 
   
   wcsncpy(catInfo.szDescription, JetByteTools::_O(lpCatDesc), 127);

   RegisterCategories(&catInfo);
}

void CComCatRegister::RegisterCategories(
   CATEGORYINFO *rgCategoryInfo, 
   ULONG cCategories /* = 1 */) const
{
   HRESULT hr = m_pICatRegister->RegisterCategories(cCategories, rgCategoryInfo);

   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatRegister::RegisterCategories()"), hr);
   }
}

void CComCatRegister::UnRegisterCategories(
   CATID *pCatid, 
   ULONG cCategories /* = 1 */) const
{
   HRESULT hr = m_pICatRegister->UnRegisterCategories(cCategories, pCatid);

   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatRegister::UnRegisterCategories()"), hr);
   }
}

void CComCatRegister::RegisterClassImplCategories(
   REFCLSID rclsid, 
   CATID *pCatid, 
   ULONG cCategories /* = 1 */) const
{
   HRESULT hr = m_pICatRegister->RegisterClassImplCategories(
      rclsid, 
      cCategories, 
      pCatid);

   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatRegister::RegisterClassImplCategories()"), hr);
   }
}

void CComCatRegister::UnRegisterClassImplCategories(
   REFCLSID rclsid, 
   CATID *pCatid, 
   ULONG cCategories /* = 1 */) const
{
   HRESULT hr = m_pICatRegister->UnRegisterClassImplCategories(
      rclsid, 
      cCategories, 
      pCatid);

   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatRegister::UnRegisterClassImplCategories()"), hr);
   }
}

void CComCatRegister::RegisterClassReqCategories(
   REFCLSID rclsid, 
   CATID *pCatid, 
   ULONG cCategories /* = 1 */) const
{
   HRESULT hr = m_pICatRegister->RegisterClassReqCategories(
      rclsid, 
      cCategories, 
      pCatid);

   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatRegister::RegisterClassReqCategories()"), hr);
   }
}

void CComCatRegister::UnRegisterClassReqCategories(
   REFCLSID rclsid, 
   CATID *pCatid, 
   ULONG cCategories /* = 1 */) const
{
   HRESULT hr = m_pICatRegister->UnRegisterClassReqCategories(
      rclsid, 
      cCategories, 
      pCatid);
   
   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatRegister::UnRegisterClassReqCategories()"), hr);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file...
///////////////////////////////////////////////////////////////////////////////
