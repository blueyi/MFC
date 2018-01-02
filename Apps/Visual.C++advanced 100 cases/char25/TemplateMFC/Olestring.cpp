///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   Olestring.cpp  $
// Version        : $Revision:   1.2  $
// Function       : 
//
// Author         : $Author:   Len  $
// Date           : $Date:   Jun 04 1998 00:02:22  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   D:/Documents/JetByte/Source/JetByteTools/Win32Tools/PVCS/Olestring.cpv  $
// 
//    Rev 1.2   Jun 04 1998 00:02:22   Len
// Shuffled order of initialiser list so that there's no chances for surprise.
// 
//    Rev 1.1   May 25 1998 11:04:12   Len
// You can now create an OLE String from non wide char string...
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

///////////////////////////////////////////////////////////////////////////////
// Include files
///////////////////////////////////////////////////////////////////////////////

#include "OleString.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// Static functions defined in this file
///////////////////////////////////////////////////////////////////////////////

static char *ustrdup(const wchar_t *pIn);
static wchar_t *ustrdup(const char *pIn);

///////////////////////////////////////////////////////////////////////////////
// COleString
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

COleString::COleString(LPCOLESTR lpOleString)
   : m_bOleString(true), m_lpOleString((LPOLESTR)lpOleString), m_lpString(0)
{
}

COleString::COleString(LPCSTR lpString)
   : m_bOleString(false), m_lpOleString(0), m_lpString((LPSTR)lpString)
{
}

COleString::~COleString()
{
   if (m_bOleString)
   {
      // Free the char * string rep as we own it.
   
      free(m_lpString);

      m_lpOleString = 0;
   }
   else
   {
      free(m_lpOleString);
      
      m_lpString = 0;
   }
}

///////////////////////////////////////////////////////////////////////////////
// Conversion 
///////////////////////////////////////////////////////////////////////////////

COleString::operator const char *()
{
   if (!m_lpString)
   {
      m_lpString = ustrdup(m_lpOleString);
   }

   return m_lpString;
}

COleString::operator const wchar_t *()
{
   if (!m_lpOleString)
   {
      m_lpOleString = ustrdup(m_lpString);
   }

   return m_lpOleString;
}

///////////////////////////////////////////////////////////////////////////////
// Duplication
///////////////////////////////////////////////////////////////////////////////

char *COleString::DuplicateAs_char() const
{
   return ustrdup(m_lpOleString);
}

wchar_t *COleString::DuplicateAs_wchar_t() const
{
   return wcsdup(m_lpOleString);
}

TCHAR *COleString::DuplicateAs_tchar() const
{
#ifdef  _UNICODE
   return DuplicateAs_wchar_t();
#else
   return DuplicateAs_char();
#endif // _UNICODE
}

///////////////////////////////////////////////////////////////////////////////
// Static functions
///////////////////////////////////////////////////////////////////////////////

wchar_t *ustrdup(const char *pIn)
{
   size_t length = strlen(pIn) + 1;
    
   wchar_t *pOut = (wchar_t*)malloc((sizeof(wchar_t) * length));
    
   if (pOut)
   {
      mbstowcs(pOut, pIn, length);
   }

   return pOut;
}

char *ustrdup(const wchar_t *pIn)
{
   size_t length = wcslen(pIn) + 1;
    
   char *pOut = (char*)malloc((sizeof(char) * length));
    
   if (pOut)
   {
      wcstombs(pOut, pIn, length);
   }

   return pOut;
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// End of file...
///////////////////////////////////////////////////////////////////////////////
