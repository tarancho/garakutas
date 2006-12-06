# $Id: makefile,v 1.1 2006/12/06 14:05:30 tfuruka1 Exp $
# $Name:  $
#
# lha32
#
# 別途 UNLHA32.DLL 用のインクルードファイルとライブラリファイルが必要
# です。
#
# $Log: makefile,v $
# Revision 1.1  2006/12/06 14:05:30  tfuruka1
# 新規追加
#

# unlha32.dll のincludeファイル等の場所
UNLHA_BASE_DIR=../../../other-c-apis/unlha32
INC_DIR=$(UNLHA_BASE_DIR)
LIBS_DIR=$(UNLHA_BASE_DIR)

EXE = lha32.exe

OBJS = main.obj

CFLAGS = /Zi /W3 /I$(INC_DIR)

LDFLAGS = /link /LIBPATH:$(LIBS_DIR) UNLHAVC.LIB

../../bin/$(EXE) : $(EXE)
	-cp $(EXE) ../../bin/.
	-cp $(UNLHA_BASE_DIR)/UNLHA32.DLL ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CLFAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.obj *~ *.pdb

clean-all : clean
	-rm -f *.exe
