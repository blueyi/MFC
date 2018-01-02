#ifndef __OLE_STRING__
#define __OLE_STRING__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   Olestring.hpp  $
// Version        : $Revision:   1.2  $
// Function       : 
//
// Author         : $Author:   Len  $
// Date           : $Date:   Jun 04 1998 00:03:08  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   D:/Documents/JetByte/Source/JetByteTools/Win32Tools/PVCS/Olestring.hpv  $
// 
//    Rev 1.2   Jun 04 1998 00:03:08   Len
// Only include what we need.
// 
//    Rev 1.1   May 25 1998 11:03:18   Len
// Added a non const correct wrapper (dangerous!) and a new ctor.
// 
//    Rev 1.0   May 18 1998 07:49:24   Len
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

#ifndef _INC_TCHAR
#include <tchar.h>
#endif

#ifndef __wtypes_h__
#include <wtypes.h>
#endif

#pragma warning(default: 4201)

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
 
///////////////////////////////////////////////////////////////////////////////
// Classes defined in this file...
///////////////////////////////////////////////////////////////////////////////

class COleString;

///////////////////////////////////////////////////////////////////////////////
// COleString
///////////////////////////////////////////////////////////////////////////////

class COleString
{
   public :

      // Construction and destruction

      COleString(LPCOLESTR lpOleString);
      COleString(LPCSTR lpString);
      
      virtual ~COleString();

      // Conversion

      operator const char *();
      operator const wchar_t *(); 

      // Duplication
      
      wchar_t *DuplicateAs_wchar_t() const;
      char *DuplicateAs_char() const;
      TCHAR *DuplicateAs_tchar() const;

   private :

      bool m_bOleString;

      LPOLESTR m_lpOleString;
      char *m_lpString;
};

class CNonConstOleString : public COleString
{
   public :

      CNonConstOleString(LPCOLESTR lpOleString) : COleString(lpOleString) {}
      CNonConstOleString(LPCSTR lpString) : COleString(lpString) {}

      // Conversion for non-const correct code
      // Handle with care...

      operator char *() { return (char*)operator const char *(); }
      operator wchar_t *() { return (wchar_t*)operator const wchar_t *(); } 
};

typedef COleString _O;

typedef CNonConstOleString _ONCC;

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __OLE_STRING__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
