# $Id: makefile,v 1.7 2011/03/03 13:38:58 tfuruka1 Exp $
# $Name:  $
#
# makeの親玉
#
# $Log: makefile,v $
# Revision 1.7  2011/03/03 13:38:58  tfuruka1
# getoptに対応等
#
# 2011/03/01 teeコマンドを新規追加
# 2007/10/04 MegaFileを追加
# 2006/12/06 単純なコーディングミスを修正しました。
# 2006/12/06 ydmモジュール回線低品質エミュレータを新規追加
# 2006/12/06 lha32を新規追加
# 2006/11/15 新規追加
#

all :
	sh -c "(cd libs/getopt; nmake)"
	sh -c "(cd batkey; nmake)"
	sh -c "(cd crlf; nmake)"
	sh -c "(cd ExSleep; nmake)"
	sh -c "(cd img2java; nmake)"
	sh -c "(cd lha32; nmake)"
	sh -c "(cd MegaFile; nmake)"
	sh -c "(cd wlsfonts; nmake)"
	sh -c "(cd YdmPoorLineEmu; nmake)"
	sh -c "(cd tee; nmake)"

clean :
	sh -c "(cd libs/getopt; nmake clean)"
	sh -c "(cd batkey; nmake clean)"
	sh -c "(cd crlf; nmake clean)"
	sh -c "(cd ExSleep; nmake clean)"
	sh -c "(cd img2java; nmake clean)"
	sh -c "(cd lha32; nmake clean)"
	sh -c "(cd MegaFile; nmake clean)"
	sh -c "(cd wlsfonts; nmake clean)"
	sh -c "(cd YdmPoorLineEmu; nmake clean)"
	sh -c "(cd tee; nmake clean)"
	-rm -fr ../bin
