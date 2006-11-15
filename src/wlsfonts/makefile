# -*- mode: makefile; coding: shift_jisx0213; -*-
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
EXE = wlsfonts.exe
OBJS = main.obj
CFLAGS = /W3 /Zi
LDFLAGS = /link /debug gdi32.lib

../../bin/$(EXE) : $(EXE)
	cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean :
	rm -f *.obj *~ *.ilk *.pdb

clean-all : clean
	rm -f *.exe
