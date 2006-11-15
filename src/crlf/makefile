# $Id: makefile,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
# $Name:  $
#
# 改行コードの変換
#
# $Log: makefile,v $
# Revision 1.1  2006/11/15 12:08:04  tfuruka1
# 新規追加
#
#
EXE=crlf.exe
OBJS=main.obj

CFLAGS=/W3 /Zi
LDFLAGS=/link /debug

../../bin/$(EXE) : $(EXE)
	-cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean :
	-rm -f *.obj *~ *.pdb *.ilk

clean-all : clean
	-rm -f *.exe
