# $Id: makefile,v 1.1 2007/10/04 14:42:58 tfuruka1 Exp $
# $Name:  $
#
# 巨大なファイルの作成
#
# $Log: makefile,v $
# Revision 1.1  2007/10/04 14:42:58  tfuruka1
# 新規追加
#
#
EXE=MegaFile.exe
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
