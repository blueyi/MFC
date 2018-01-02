# Makefile for cdcache.dll
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

#full symbolic debugging under GDB & OutputDebugString
#CFLAGS    = -O0 -ggdb -D_DEBUG
#CPPFLAGS  = -O0 -ggdb -D_DEBUG
#LFLAGS    = -g


DLLNAME   = cdcache
DLL       = $(DLLNAME).dll
LIBDLL    = lib$(DLLNAME).a

CC        = gcc
CPP	       = g++
WINDRES   = windres
DLLTOOL   = dlltool
DLLWRAP   = dllwrap
WRAPOPT   = --dllname $(DLL) -def $(DLLNAME).def --target i386-mingw32 --implib $(LIBDLL)

OBJ = growstring.o parsecddb.o cddbentry.o

all: $(DLLNAME).dll test.exe

clean:
	$(RM) *.o *~ *.dll base.tmp junk.tmp *.a temp.exp

%.o : %.cpp
	$(CPP) $(CFLAGS) -D_MAKING_DLL -c $< -o $@

$(DLLNAME).dll: $(OBJ) $(DLLNAME).def
	$(RM) $(LIBDLL)
	$(DLLWRAP) $(WRAPOPT) $(OBJ)
	-@$(CP) $(DLLNAME).dll ..

#$(DLLNAME)rc.o: $(DLLNAME).rc
#	$(WINDRES) -i $< -o $@

test.exe: test.c $(LIBDLL)
	$(CC) -o test.exe test.c $(LIBDLL)

growstring.o: growstring.h growstring.cpp

cddbentry.o: cddbentry.h growstring.h cddbentry.cpp

parsecddb.o: parsecddb.cpp cddbentry.h