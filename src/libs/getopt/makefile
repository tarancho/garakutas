# -*- mode:makefile; coding:shift_jis-unix -*-
# $Id: makefile,v 1.2 2011/03/03 13:38:58 tfuruka1 Exp $

SHELL=/bin/sh
O=obj
DLL=getopt.dll
OBJS=getopt.$(O) getopt_long.$(O)
CFLAGS=/Zi /DGETOPT_API=__declspec(dllexport) /W3\
	/I. /D_CRT_SECURE_NO_WARNINGS

LDFLAGS=/DLL /debug

../../../bin/$(DLL) : ../../../bin $(DLL) test.exe
	cp $(DLL) $@

../../../bin :
	sh -c "mkdir $@"

$(DLL) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) /link $(LDFLAGS) /def:getopt.def /OUT:$@

$(OBJS) : makefile

test.exe : test.c
	$(CC) test.c /link getopt.lib /OUT:$@

clean:
	-rm -f *.obj *.o *.pdb *~ *.ilk *.exp *.cache

clean-all: clean
	-rm -f *.dll *.lib *.exe
