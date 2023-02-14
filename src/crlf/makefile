# -*- mode: makefile; coding: utf-8;
# $Id: makefile,v 1.2 2011/03/03 13:38:58 tfuruka1 Exp $
#
# 改行コードの変換
#
# 2019/07/03 MinGW に getopt が含まれているので、Windows版のgetoptは不
#            要になりました。
#
# 2006/11/15 新規追加
#
EXE=crlf.exe
OBJS=main.o

CC = x86_64-w64-mingw32-gcc
# CC = i686-w64-mingw32-gcc
CFLAGS=-g -Wall -W -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings \
	-Wconversion -Wfloat-equal -Wpointer-arith \
	--exec-charset=cp932 --input-charset=utf-8

../../bin/$(EXE) : ../../bin $(EXE)
	-cp $(EXE) $@
../../bin :
	sh -c "mkdir $@"

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean :
	-rm -f *.o *~

clean-all : clean
	-rm -f *.exe
