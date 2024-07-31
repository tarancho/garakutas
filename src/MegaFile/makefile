# $Id: makefile,v 1.1 2007/10/04 14:42:58 tfuruka1 Exp $
# $Name:  $
#
# 巨大なファイルの作成
#
# $Log: makefile,v $
# Revision 1.1  2007/10/04 14:42:58  tfuruka1
# 新規追加
#
#
CC = x86_64-w64-mingw32-gcc
CC = i686-w64-mingw32-gcc
CFLAGS=-g -Wall --exec-charset=cp932 --input-charset=utf-8

EXE=MegaFile.exe
OBJS=main.o

../../bin/$(EXE) : $(EXE)
	-cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean :
	-rm -f *.o *~

clean-all : clean
	-rm -f *.exe
