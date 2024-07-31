# -*- mode: makefile; coding: utf-8; -*-
# Copyright (C) 2006 Tadamegu Furukawa
# $Id: makefile,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
# $Name:  $
#
# フォントの一覧表示
#
# $Log: makefile,v $
# Revision 1.1  2006/11/15 12:08:04  tfuruka1
# 新規追加
#
#

CC = x86_64-w64-mingw32-gcc
#CC = i686-w64-mingw32-gcc

EXE = wlsfonts.exe
OBJS = main.o
CFLAGS = -g -Wall --exec-charset=cp932 --input-charset=utf-8
LDFLAGS = -lgdi32

../../bin/$(EXE) : $(EXE)
	mkdir -pv ../../bin
	cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean :
	rm -f *.o *~

clean-all : clean
	rm -f *.exe
