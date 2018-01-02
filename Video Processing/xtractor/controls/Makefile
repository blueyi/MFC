# using gcc 2.95.3(Mingw32)

# rm and cp are available in the Virtually Unix archive 
#   http://www.itribe.net/virtunix
RM = rm -f
CP = cp

#release build
CFLAGS    = -O0 -Wall -D_WIN32_IE=0x0400
CPPFLAGS  = -O0 -Wall
LFLAGS    =

#emit OutputDebugString() calls
#CFLAGS    = -O0 -D_DEBUG  -D_WIN32_IE=0x0400
#CPPFLAGS  = -O0 -D_DEBUG
#LFLAGS    =

#full symbolic debugging under GDB & OutputDebugString
#CFLAGS    = -O0 -ggdb -D_DEBUG -D_WIN32_IE=0x0400
#CPPFLAGS  = -O0 -ggdb -D_DEBUG
#LFLAGS    = -g


DLLNAME   = xtrctl32
DLL       = $(DLLNAME).dll
LIBDLL    = lib$(DLLNAME).a

CC        = gcc
CPP       = g++
WINDRES   = windres
DLLTOOL   = dlltool
DLLWRAP   = dllwrap
WRAPOPT   = --dllname $(DLL) -def $(DLLNAME).def --target i386-mingw32 --implib $(LIBDLL)

OBJ = treeopt.o treeoptrc.o

all: $(DLLNAME).dll test.exe

clean:
	$(RM) *.o *~ *.dll base.tmp junk.tmp *.a temp.exp

treeopt.o: treeopt.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DLLNAME).dll: $(OBJ) $(DLLNAME).def
	$(RM) $(LIBDLL)
	$(DLLWRAP) $(WRAPOPT) $(OBJ) -lcomctl32 -lgdi32
	-@$(CP) $(DLLNAME).dll ..

$(DLLNAME)rc.o: $(DLLNAME).rc
	$(WINDRES) -i $< -o $@

test.exe: test.c testrc.o $(LIBDLL)
	$(CC) $(CFLAGS) -o $@ test.c  testrc.o -L. -l$(DLLNAME)

testrc.o: test.rc
	$(WINDRES) -i $< -o $@

treeoptrc.o: treeopt.rc
	$(WINDRES) -i $< -o $@
