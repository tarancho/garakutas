# $Id: makefile,v 1.1 2006/11/15 12:08:03 tfuruka1 Exp $
# $Name:  $
#
# 俗に言うスリープ
#
# $Log: makefile,v $
# Revision 1.1  2006/11/15 12:08:03  tfuruka1
# 新規追加
#
CC = x86_64-w64-mingw32-gcc
CC = i686-w64-mingw32-gcc
CFLAGS=-g -Wall --exec-charset=cp932 --input-charset=utf-8

O = o
EXE = ExSleep.exe
OBJS = main.$(O)

../../bin/$(EXE) : $(EXE)
	cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean :
	-rm -f *.$(O) *~ *.ilk *.opt *.pdb

clean-all : clean
	-rm -f *.exe

