# $Id: makefile 1315 2013-03-19 01:40:05Z tfuruka1 $
#
.c.o :
	$(CC) $(CFLAGS) -c $<

CC = x86_64-w64-mingw32-gcc
STRIP = x86_64-w64-mingw32-strip

CFLAGS = -g -Wall --exec-charset=cp932 --input-charset=utf-8
OBJS = main.o
tvmaker.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(STRIP) $@

$(OBJS) : makefile

clean:
	rm -f *.o *~
