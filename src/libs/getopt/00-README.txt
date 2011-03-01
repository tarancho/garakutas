Win32でgetoptを使用する。

多分、色々と公開されていると思うが、私は、

以下のリポジトリからsvnでチェックアウト

    http://svn.xiph.org/trunk/theora-exp/win32/compatibility/

/ - Revision 17875: /trunk/theora-exp/win32/compatibility

オリジナルファイルは以下の通り

    README.txt
    getopt.c
    getopt.h
    getopt_long.c
    unistd.h

以下のファイルは古川が追加したファイルです

    makefile
    getopt.def
    test.c

nmake で getopt.dllとtest.exeを作成します。
