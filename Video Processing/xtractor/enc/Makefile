# Makefile for AKRip32.dll
# using gcc 2.95.2(Mingw32) from
#   http://www.xraylith.wisc.edu/~khan/software/gnu-win32/gcc.html

# rm and cp are available in the Virtually Unix archive 
#   http://www.itribe.net/virtunix
RM = rm -f
CP = cp

#release build
CFLAGS    = -O0 -Wall
CPPFLAGS  = -O0 -Wall
LFLAGS    =

#emit OutputDebugString() calls
#CFLAGS    = -O0 -D_DEBUG
#CPPFLAGS  = -O0 -D_DEBUG
#LFLAGS    =

#full symbolic debugging under GDB & OutputDebugString
#CFLAGS    = -O0 -ggdb -D_DEBUG
#CPPFLAGS  = -O0 -ggdb -D_DEBUG
#LFLAGS    = -g


DLLNAME   = xtenc
DLL       = $(DLLNAME).dll
LIBDLL    = lib$(DLLNAME).a

CC        = gcc
CPP	       = g++
WINDRES   = windres
DLLTOOL   = dlltool
DLLWRAP   = dllwrap
WRAPOPT   = --dllname $(DLL) -def $(DLLNAME).def --target i386-mingw32 --implib $(LIBDLL)

OBJ = xtenc.o encbase.o RawStream.o WavStream.o MP3Stream.o VorbisStream.o \
	BladeStream.o LameStream.o utf8.o

all: $(DLLNAME).dll test.exe

clean:
	$(RM) *.o *~ *.dll base.tmp junk.tmp *.a temp.exp


xtenc.o: xtenc.cpp encbase.h xtenc.h RawStream.h WavStream.h MP3Stream.h
	$(CPP) $(CFLAGS) -c $< -o $@

encbase.o: encbase.cpp encbase.h xtenc.h
	$(CPP) $(CFLAGS) -c $< -o $@

RawStream.o: RawStream.cpp encbase.h xtenc.h RawStream.h
	$(CPP) $(CFLAGS) -c $< -o $@

WavStream.o: WavStream.cpp encbase.h xtenc.h WavStream.h
	$(CPP) $(CFLAGS) -c $< -o $@

MP3Stream.o: MP3Stream.cpp encbase.h xtenc.h MP3Stream.h
	$(CPP) $(CFLAGS) -c $< -o $@

VorbisStream.o: VorbisStream.cpp encbase.h xtenc.h MP3Stream.h VorbisStream.h
	$(CPP) $(CFLAGS) -c $< -o $@

BladeStream.o: BladeStream.cpp encbase.h xtenc.h MP3Stream.h BladeStream.h
	$(CPP) $(CFLAGS) -c $< -o $@

LameStream.o: LameStream.cpp encbase.h xtenc.h MP3Stream.h LameStream.h
	$(CPP) $(CFLAGS) -c $< -o $@

utf8.o: utf8.c utf8.h
	$(CC) $(CFLAGS) -c $< -o $@

$(DLLNAME).dll: $(OBJ) $(DLLNAME).def
	$(RM) $(LIBDLL)
	$(DLLWRAP) $(WRAPOPT) $(OBJ)
	-@$(CP) $(DLLNAME).dll ..

$(DLLNAME)rc.o: $(DLLNAME).rc
	$(WINDRES) -i $< -o $@

test.exe: test.c $(LIBDLL)
	$(CC) $(CFLAGS) -o $@ test.c -L. -l$(DLLNAME)

