# -*- mode: makefile; coding: sjis; -*-
# Copyright (C) 2005 Tadamegu Furukawa
# $Id: makefile,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
# $Name:  $
#
# batkeyのmakefile
#
# $Log: makefile,v $
# Revision 1.1  2006/11/15 12:08:04  tfuruka1
# 新規追加
#
#
include version

O = obj
CFLAGS = /W3 /Zi
CC = cl

#O = o
#CFLAGS = -Wall -g -mno-cygwin
#CC = gcc

EXE = batkey.exe
OBJS = main.$(O)

all : ../../bin/$(EXE) ../../bin/batkey-sample.cmd

../../bin/$(EXE) : $(EXE)
	cp $(EXE) ../../bin/.
../../bin/batkey-sample.cmd : batkey-sample.cmd
	cp batkey-sample.cmd ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

tar : clean
	sh -c "(cd ../..; tar cvzf batkey-$(MAKE_VERSION).tar.gz batkey)"	

clean :
	rm -f *.obj *.o *.exe *~
	rm -f *.pdb *.ilk

