# $Id: makefile,v 1.1 2011/03/01 11:00:07 tfuruka1 Exp $
#
# uniqコマンドで対応できなかったので dedup を作る。
#
#
CC = x86_64-w64-mingw32-gcc
CC = i686-w64-mingw32-gcc
CFLAGS= -g -Wall -W -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings \
	-Wconversion -Wfloat-equal -Wpointer-arith \
	--exec-charset=cp932 --input-charset=utf-8

EXE=dedup
OBJS=main.o

../../bin/$(EXE) : $(EXE)
	-cp $(EXE) $@

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS)  -o $@ $(OBJS)

clean :
	-rm -f *.o *~

clean-all : clean
	-rm -f *.exe
