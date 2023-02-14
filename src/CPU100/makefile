# $Id: makefile 1313 2013-03-19 00:10:02Z tfuruka1 $

CC = x86_64-w64-mingw32-gcc
STRIP = x86_64-w64-mingw32-strip

#CC = i686-w64-mingw32-gcc
#STRIP = i686-w64-mingw32-strip

CFLAGS=-g -Wall --exec-charset=cp932 --input-charset=utf-8

cpu100.exe : main.o makefile
	$(CC) $(CFLAGS) -o $@ main.o
	$(STRIP) $@
clean :
	-rm -f *.o *~
