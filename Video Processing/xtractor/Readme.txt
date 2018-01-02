CD-DA X-Tractor v0.24, 24 April 2003
Copyright (c) 2000-2003 - Jay A. Key, akey@users.sourceforge.net

Table of Contents
  1. Introduction
  2. Building from the source code
  3. Credits
  4. Useful links

-------------------------------------------------------------------------
1. Introduction

CD-DA X-Tractor is an open-source "ripper" for 32-bit Windows platforms.
It is released under the GNU Public License (see COPYING-2.0), which
means, among other things, that the source code is available for 
anyone to download, examine, and build.  It is designed to be 
built using freely available tools, making it accessible for anyone with
a computer -- it does not require the purchase of expensive compilers.

It features:
  * Rip and encode on-the-fly
  * Support for NT/2000 natively (no ASPI manager required)
  * Support for WAV, MP3 and OGG output
  * Normalization of output tracks
  * Freedb database support

-------------------------------------------------------------------------
2. Building from the source code

To build CD-DA X-Tractor, you'll need the source code, available at
http://www.sourceforge.net/projects/xtractor and a compiler.  Currently
supported compilers are Mingw32(gcc-2.95.3) and Visual C++ 6.0.  If
your compiler is not listed here, feel free to send me project files.

To build with MSVC6, simply use the provided project files.

To build with Mingw32, use the provided makefiles:
  a. For a release build, you must set the RELEASEMODE environment
     variable appropriately.  If it is not set, or set to another 
     value, the makefiles will create a debug build.
     
       e:\xtractor> set RELEASEMODE=release
     
  b. Build the component DLLs in subdirectories AKRIP, CDCACHE, ENC, and 
     CONTROLS.  Use the provided makefile in each directory:
     
     Assuming that the source code was unpacked in e:\xtractor:
       e:\xtractor> cd akrip
       e:\xtractor\akrip> make
     ... and so on
  
  c. Build xtractor.exe in the base directory.
       e:\xtractor> make
  
  d. If you wish to build vorb_enc.dll, you'll need to obtain libvorbis
     and vorbisfile from www.xiph.org.  Because they are not released 
     under a license compatible with the GPL, I do not include them
     in this project.
  
  e. If you wish to build lame_enc.dll, you'll need to obtain the source
     from either the CDEX project (http://cdexos.sourceforge.net/) or
     from Lame (http://lame.sourceforge.net/)  Lame is released under the
     LGPL, and is available with full source code.

-------------------------------------------------------------------------
3. Credits
  * Main icon and logo in the "About" dialog by Liquid Dust 
  * Main program executable packed by UPX
  * Vorb_Enc.dll is linked against libvorbis and vorbisfile from www.xiph.org
  * lame_enc.dll part of the Lame project, released under the LGPL, available
    at http://lame.sourceforge.net/
    

-------------------------------------------------------------------------
4. Useful links
  Mingw32 compiler:    http://www.mingw.org/
  Ogg Vorbis:          http://www.xiph.org/
  CDEX:                http://cdexos.sourceforge.net/
  Lame encoder:        http://lame.sourceforge.net/

Questions, comments, complaints, suggestions, etc... should be sent to
akey@users.sourceforge.net

-Andy Key
