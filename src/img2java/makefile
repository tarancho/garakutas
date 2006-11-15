# $Id: makefile,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
# $Name:  $
#
# 画像ファイルからJavaのImage classに変換
#
# $Log: makefile,v $
# Revision 1.1  2006/11/15 12:08:04  tfuruka1
# 新規追加
#
O = obj
EXE = img2java.exe
OBJS = main.$(O)
CFLAGS = /W3 /Zi
LDFLAGS = /link /debug user32.lib

../../bin/$(EXE) : $(EXE)
	cp $(EXE) ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean :
	-rm -f *.$(O) *~ *.ilk *.opt *.pdb

clean-all : clean
	-rm -f *.exe

