/*
 * RawStream.cpp - Copyright (C) 2000 Jay A. Key
 *
 * Implementation for the RawStream class, which simply writes unencoded
 * data to a file.
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#include "RawStream.h"


unsigned int RawStream::Encode( unsigned char *pData, unsigned int len )
{
  if ( !_fpOut )
    return 0;

  return fwrite( pData, 1, len, _fpOut );
}


int RawStream::SetOption( int opt, char *pszData )
{
  return this->BaseEncoderStream::SetOption( opt, pszData );
};
