# $Id: makefile,v 1.7 2011/03/03 13:38:58 tfuruka1 Exp $
# $Name:  $
#
# makeの親玉
#
# $Log: makefile,v $
# Revision 1.7  2011/03/03 13:38:58  tfuruka1
# getoptに対応等
#
# MinGWについて
#  * 横取り丸については、現在は保留
#
# 2019/07/03 MinGWへ変更。getopt は最早不要となりました。CPU100,
#            TVMaker を追加。
# 2011/03/01 teeコマンドを新規追加
# 2007/10/04 MegaFileを追加
# 2006/12/06 単純なコーディングミスを修正しました。
# 2006/12/06 ydmモジュール回線低品質エミュレータを新規追加
# 2006/12/06 lha32を新規追加
# 2006/11/15 新規追加
#

all :
	cd batkey; make
	cd CPU100; make
	cd crlf; make
	cd ExSleep; make
	cd img2java; make
	cd lha32; make
	cd MegaFile; make
	cd TVMaker; make
	cd pi; make
	cd tee; make
	cd wlsfonts; make
#	cd YdmPoorLineEmu; make

clean :
	cd batkey; make clean
	cd CPU100; make clean
	cd crlf; make clean
	cd ExSleep; make clean
	cd img2java; make clean
	cd lha32; make clean
	cd MegaFile; make clean
	cd TVMaker; make clean
	cd pi; make clean
	cd tee; make clean
	cd wlsfonts; make clean
#	cd YdmPoorLineEmu; make clean
	-rm -f ../bin/*.exe ../bin/*.cmd ../bin/*.dll
