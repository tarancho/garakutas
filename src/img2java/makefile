# $Id: makefile,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
# $Name:  $
#
# 画像ファイルからJavaのImage classに変換
#
# $Log: makefile,v $
# Revision 1.1  2006/11/15 12:08:04  tfuruka1
# 新規追加
#
CC = x86_64-w64-mingw32-gcc
CC = i686-w64-mingw32-gcc
CFLAGS=-g -Wall --exec-charset=cp932 --input-charset=utf-8

O = o
EXE = img2java.exe
OBJS = main.$(O)

../../bin/$(EXE) : $(EXE)
	cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean :
	-rm -f *.$(O) *~

clean-all : clean
	-rm -f *.exe

