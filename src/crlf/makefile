# $Id: makefile,v 1.2 2011/03/03 13:38:58 tfuruka1 Exp $
#
# 改行コードの変換
#
# 2006/11/15 新規追加
#
EXE=crlf.exe
OBJS=main.obj

CFLAGS=/W3 /Zi /I../libs/getopt /D_CRT_SECURE_NO_WARNINGS
LDFLAGS=/debug /libpath:../libs/getopt

../../bin/$(EXE) : ../../bin $(EXE)
	-cp $(EXE) $@
../../bin :
	sh -c "mkdir $@"

$(EXE) : $(OBJS) getopt
	$(CC) $(CFLAGS) $(OBJS) /link $(LDFLAGS) getopt.lib -out:$@

getopt :
	sh -c "(cd ../libs/getopt; nmake)";

clean :
	-rm -f *.obj *~ *.pdb *.ilk

clean-all : clean
	-rm -f *.exe
