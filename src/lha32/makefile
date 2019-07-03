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

CC = x86_64-w64-mingw32-gcc
CC = i686-w64-mingw32-gcc

# unlha32.dll のincludeファイル等の場所
UNLHA_BASE_DIR="/Program Files (x86)/ArchiverDll/UNLHA32"
INC_DIR=$(UNLHA_BASE_DIR)
LIBS_DIR=$(UNLHA_BASE_DIR)

EXE = lha32.exe
OBJS = main.o

CFLAGS=-g -Wall --exec-charset=cp932 --input-charset=utf-8 -I $(INC_DIR)
LDFLAGS = -L $(LIBS_DIR) -lUNLHA32

../../bin/$(EXE) : $(EXE)
	-cp $(EXE) ../../bin/.
	-cp $(UNLHA_BASE_DIR)/UNLHA32.DLL ../../bin/.

$(EXE) : $(OBJS)
	$(CC) $(CLFAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o *~

clean-all : clean
	-rm -f *.exe
