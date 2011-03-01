# $Id: makefile,v 1.1 2011/03/01 11:00:07 tfuruka1 Exp $
#
# teeƒRƒ}ƒ“ƒh
#
#
EXE=tee.exe
OBJS=main.obj

CFLAGS=/W3 /Zi /D_CRT_SECURE_NO_WARNINGS /I../libs/getopt
LDFLAGS=/debug ../libs/getopt/getopt.lib

../../bin/$(EXE) : $(EXE)
	-cp $(EXE) $@

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) /link $(LDFLAGS) -out:$@

clean :
	-rm -f *.obj *~ *.pdb *.ilk *.suo *.exp *.lib

clean-all : clean
	-rm -f *.exe
