# $Id: makefile 1313 2013-03-19 00:10:02Z tfuruka1 $
CC = x86_64-w64-mingw32-gcc
CC = i686-w64-mingw32-gcc
CFLAGS= -g -Wall -W -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings \
	-Wconversion -Wfloat-equal -Wpointer-arith \
	--exec-charset=cp932 --input-charset=utf-8

disrdpcp.exe : main.o makefile
	$(CC) $(CFLAGS) -o $@ main.o
	strip $@
clean :
	-rm -f *.o *~
