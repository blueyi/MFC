# rm and cp are available in the Virtually Unix archive 
#   http://www.itribe.net/virtunix
RM = rm -f
CD = cd

# default to a debug release
ifeq ($(RELEASEMODE),release)
CFLAGS    = -O2 -c -Wall -D_WIN32_IE=0x0400
DFLAGS   = 
else
CFLAGS    = -O0 -ggdb -c -Wall -D_WIN32_IE=0x0400
DFLAGS    = -ggdb
TESTSUBMIT = true
endif

# TESTSUBMITMODE determines if CDDB submissions are in test mode
ifdef TESTSUBMIT
CFLAGS += -DTESTSUBMITMODE=TRUE
endif

CC        = gcc
WINDRES   = windres

OBJ = xtractor.o xtractorrc.o trackwnd.o config.o globals.o cddlg.o outdlg.o \
	dirsel.o gauge.o wrqueue.o riptracks.o mp3dlg.o id3.o statusbar.o \
	about.o cddbdlg.o ripseg.o rangeslider.o miscdlg.o cddbsubmit.o \
	vorbdlg.o

all: xtractor.exe

xtractor.exe: $(OBJ)
	$(CC) $(DFLAGS) -o xtractor $(OBJ) -lcomctl32 -lgdi32 -L./akrip -lakrip32 -lwsock32 -L./enc -lxtenc -L./cdcache -lcdcache -L./controls -lxtrctl32 -mwindows

xtractor.o: xtractor.c resources.h trackwnd.h globals.h id3.h cddbdlg.h config.h xtractor.h
	$(CC) $(CFLAGS) -o $@ $<

trackwnd.o: trackwnd.c trackwnd.h resources.h globals.h statusbar.h
	$(CC) $(CFLAGS) -o $@ $<

config.o: config.c resources.h globals.h gauge.h
	$(CC) $(CFLAGS) -o $@ $<

globals.o: globals.c
	$(CC) $(CFLAGS) -o $@ $<

cddlg.o: cddlg.c resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

cddbdlg.o: cddbdlg.c resources.h globals.h cddbdlg.h
	$(CC) $(CFLAGS) -o $@ $<

outdlg.o: outdlg.c resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

dirsel.o: dirsel.c resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

gauge.o: gauge.c gauge.h
	$(CC) $(CFLAGS) -o $@ $<

wrqueue.o: wrqueue.c wrqueue.h
	$(CC) $(CFLAGS) -o $@ $<

riptracks.o: riptracks.c riptracks.h resources.h globals.h trackwnd.h gauge.h id3.h
	$(CC) $(CFLAGS) -o $@ $<

mp3dlg.o: mp3dlg.c globals.h resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

id3.o: id3.c id3.h resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

statusbar.o: statusbar.c globals.h
	$(CC) $(CFLAGS) -o $@ $<

about.o: about.c resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

ripseg.o: ripseg.c resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

rangeslider.o: rangeslider.c rangeslider.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

miscdlg.o: miscdlg.c resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

vorbdlg.o: vorbdlg.c resources.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

cddbsubmit.o: cddbsubmit.c resources.h id3.h globals.h
	$(CC) $(CFLAGS) -o $@ $<

xtractorrc.o: xtractor.rc resources.h toolbar.bmp
	$(WINDRES) -i xtractor.rc -o xtractorrc.o

clean:
	$(RM) *.o *~ *.exe *.dat

