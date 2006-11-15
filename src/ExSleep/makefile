# $Id: makefile,v 1.1 2006/11/15 12:08:03 tfuruka1 Exp $
# $Name:  $
#
# 俗に言うスリープ
#
# $Log: makefile,v $
# Revision 1.1  2006/11/15 12:08:03  tfuruka1
# 新規追加
#
O = obj
EXE = ExSleep.exe
OBJS = main.$(O)
CFLAGS = /W3 /Zi
LDFLAGS = /link /debug user32.lib

../../bin/$(EXE) : $(EXE)
	cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean :
	-rm -f *.$(O) *~ *.ilk *.opt *.pdb

clean-all : clean
	-rm -f *.exe

