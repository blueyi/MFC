///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   ComCatInformation.cpp  $
// Version        : $Revision:   1.3  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 21:12:36  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/ComCatInformation.cpv  $
// 
//    Rev 1.3   Oct 25 1998 21:12:36   len
// 
//    Rev 1.2   Oct 25 1998 21:08:50   len
// 
//    Rev 1.1   Jun 06 1998 07:53:28   Len
// 
//    Rev 1.0   May 18 1998 07:34:40   Len
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

#include "ComCatInformation.hpp"
#include "ComUtils.hpp"
#include "OleString.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// CComCatInformation
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

CComCatInformation::CComCatInformation()
   :  CComUsesCom(), 
      m_pICatInformation(0)
{
   HRESULT hr = CoCreateInstance(
      CLSID_StdComponentCategoriesMgr,
      NULL, 
      CLSCTX_INPROC_SERVER, 
      IID_ICatInformation, 
      (void**) &m_pICatInformation);

   if (!SUCCEEDED(hr))
   {
      throw Exception(_T("CComCatInformation::CComCatInformation()"), hr);
   }
}

CComCatInformation::~CComCatInformation()
{
	m_pICatInformation = SafeRelease(m_pICatInformation);
}

///////////////////////////////////////////////////////////////////////////////
// Do stuff
///////////////////////////////////////////////////////////////////////////////


LPCTSTR CComCatInformation::GetCategoryDesc(
	REFCATID rcatid, 
   LCID lcid /*= GetUserDefaultLCID()*/) const
{
   LPCTSTR lpCatDesc = 0;

   PWCHAR lpwDesc = 0;

   HRESULT hr = m_pICatInformation->GetCategoryDesc(rcatid, lcid, &lpwDesc);

   if (SUCCEEDED(hr))
   {
      COleString wString(lpwDesc);

      lpCatDesc = wString.DuplicateAs_tchar();
      
      CoTaskMemFree(lpwDesc);
   }
   else
   {
      throw Exception(_T("CComCatInformation::GetCategoryDesc()"), hr);
   }

   return lpCatDesc;
}

void CComCatInformation::EnumCategories(
   IEnumCATEGORYINFO **ppIEnumCatInfo,
   LCID lcid /*= GetUserDefaultLCID()*/) const
{
   HRESULT hr = m_pICatInformation->EnumCategories(
      lcid, 
      ppIEnumCatInfo);

   if (FAILED(hr))
   {
      throw Exception(_T("CComCatInformation::FirstCategory()"), hr);
   }
}


CIterateCATEGORYINFO CComCatInformation::IterateCategories(
   LCID lcid /*= GetUserDefaultLCID()*/) const
{
   IEnumCATEGORYINFO *pIEnumCatInfo = 0;

	EnumCategories(&pIEnumCatInfo, lcid);

   CIterateCATEGORYINFO it(pIEnumCatInfo);

	pIEnumCatInfo = SafeRelease(pIEnumCatInfo);

	return it;
}

CIterateGUID CComCatInformation::IterateClassesOfCategory(
   REFCATID catid) const
{
   return IterateClassesOfCategories(1, (CATID *)&catid, 0, 0);
}
/*
CIterateGUID CComCatInformation::IterateClassesOfCategories(
   ComCats &implemented, 
   ComCats &required) const
{
   return IterateClassesOfCategories(
      implemented.GetCount(),
      implemented.GetArray(),
      required.GetCount(),
      required.GetArray());
}
*/
CIterateGUID CComCatInformation::IterateClassesOfCategories(
   ULONG cImplemented,
   CATID *pCatidImpl, 
   ULONG cRequired /* = 0 */, 
   CATID *pCatidReq /* = 0 */) const
{
   IEnumGUID *pIEnumGUID = 0;

   HRESULT hr = m_pICatInformation->EnumClassesOfCategories(
      cImplemented,
      pCatidImpl, 
      cRequired,
      pCatidReq,
      &pIEnumGUID);

   if (FAILED(hr))
   {
      throw Exception(_T("CComCatInformation::IterateClassesOfCategories()"),hr);
   }

   CIterateGUID it(pIEnumGUID);

	pIEnumGUID = SafeRelease(pIEnumGUID);

	return it;
}

CIterateCATID CComCatInformation::IterateImplCategoriesOfClass(
   REFCLSID rclsid) const
{
	IEnumCATID *pIEnumCATID = 0;
	
	EnumImplCategoriesOfClass(rclsid, &pIEnumCATID);
	
	CIterateCATID it(pIEnumCATID);

	pIEnumCATID = SafeRelease(pIEnumCATID);

	return it;
}

void CComCatInformation::EnumImplCategoriesOfClass(
   REFCLSID rclsid,
	IEnumCATID **ppIEnumCATID) const
{
   HRESULT hr = m_pICatInformation->EnumImplCategoriesOfClass(
      rclsid,
      ppIEnumCATID);

   if (FAILED(hr))
   {
      throw Exception(_T("CComCatInformation::EnumImplCategoriesOfClass()"), hr);
   }
}

CIterateCATID CComCatInformation::IterateReqCategoriesOfClass(
   REFCLSID rclsid) const
{
	IEnumCATID *pIEnumCATID = 0;
	
	EnumReqCategoriesOfClass(rclsid, &pIEnumCATID);
	
	CIterateCATID it(pIEnumCATID);

	pIEnumCATID = SafeRelease(pIEnumCATID);

	return it;
}

void CComCatInformation::EnumReqCategoriesOfClass(
	REFCLSID rclsid,
	IEnumCATID **ppIEnumCATID) const
{

   HRESULT hr = m_pICatInformation->EnumReqCategoriesOfClass(
      rclsid,
      ppIEnumCATID);

   if (FAILED(hr))
   {
      throw Exception(_T("CComCatInformation::EnumReqCategoriesOfClass()"), hr);
   }
}

bool CComCatInformation::IsClassOfCategory(
   REFCLSID rclsid, 
   REFCATID rcatid) const
{
   return IsClassOfCategories(rclsid, 1, (CATID*)&rcatid, 0, 0);
}

/*
bool CComCatInformation::IsClassOfCategories(
      REFCLSID rclsid, 
      ComCats &implemented, 
      ComCats &required) const
{
   return IsClassOfCategories(
      rclsid, 
      implemented.GetCount(), 
      implemented.GetArray(),
      required.GetCount(),
      required.GetArray());
}
*/

bool CComCatInformation::IsClassOfCategories(
   REFCLSID rclsid, 
   ULONG cImplemented,
   CATID *pCatidImpl, 
   ULONG cRequired /* = 0 */, 
   CATID *pCatidReq /* = 0 */) const
{
   bool ok = false;

   HRESULT hr = m_pICatInformation->IsClassOfCategories(
      rclsid,
      cImplemented,
      pCatidImpl,
      cRequired,
      pCatidReq);

   if (SUCCEEDED(hr))
   {
      ok = (S_OK == hr);
   }
   else
   {
      throw Exception(_T("CComCatInformation::IsClassOfCategories()"), hr);
   }

   return ok;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file...
///////////////////////////////////////////////////////////////////////////////
