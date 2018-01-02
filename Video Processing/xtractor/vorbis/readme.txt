10 July 2000:

First cut of a BladeEnc-style wrapper for the Ogg Vorbis codec.  Must be
linked against libvorbis and vorbisfile -- available at http://www.xiph.org/

As of right now, only one mode, ~128 Kbps is available.  As more modes are
released for the codec, I'll add them in here.  The proper extension for
files encoded with this dll is .ogg.

The dll will automatically place the data in the format.vorb section of the
BE_CONFIG structure into the comment header for the OGG file -- instead of
having to use a hack like ID3 tagging, comments are built in to the OGG
format.  The WinAmp plug-in (and possibly others) are capable of reading
and displaying info from the comment stream.

Have fun with it!

-Andy Key
