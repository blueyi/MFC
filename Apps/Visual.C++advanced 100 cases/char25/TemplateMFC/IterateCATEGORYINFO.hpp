#ifndef __ITERATE_CATEGORYINFO__
#define __ITERATE_CATEGORYINFO__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   IterateCATEGORYINFO.hpp  $
// Version        : $Revision:   1.2  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 20:55:38  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/IterateCATEGORYINFO.hpv  $
// 
//    Rev 1.2   Oct 25 1998 20:55:38   len
// Added cache size.
// 
//    Rev 1.1   Jun 06 1998 07:56:34   Len
// 
//    Rev 1.0   May 18 1998 07:34:46   Len
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

#ifndef __IENUM_ITERATOR__
#include "IEnumIterator.hpp"
#endif

#ifndef __comcat_h__
#include <comcat.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
 
///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file...
///////////////////////////////////////////////////////////////////////////////

class CIterateCATEGORYINFO;

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CIterateCATEGORYINFO
///////////////////////////////////////////////////////////////////////////////

class CIterateCATEGORYINFO
   :  public IEnumIterator<CIterateCATEGORYINFO, IEnumCATEGORYINFO, CATEGORYINFO>
{
   public :

      CIterateCATEGORYINFO(IEnumCATEGORYINFO *pIEnumCATEGORYINFO, unsigned long max = 64)
         : IEnumIterator<CIterateCATEGORYINFO, IEnumCATEGORYINFO, CATEGORYINFO> (pIEnumCATEGORYINFO, max)
      {
      }
         
      CATID GetCATID() const { return Enumerated().catid; }
      LCID GetLCID() const { return Enumerated().lcid; }
      LPCOLESTR GetDescription() const { return Enumerated().szDescription; }
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __ITERATE_CATEGORYINFO__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
