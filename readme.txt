私の環境以外で確実に修正が必要なmakefile

src/lha32/makefile

    UNLHA32.DLLのヘッダファイルとライブラリファイルを使用しています。
    これらのファイルが別途必要になります。

    http://www2.nsknet.or.jp/~micco/

    等から別途入手して下さい。そして、当該ファイルの先頭付近の

        UNLHA_BASE_DIR=../../../other-c-apis/unlha32
        INC_DIR=$(UNLHA_BASE_DIR)
        LIBS_DIR=$(UNLHA_BASE_DIR)

    の部分を適切に書換えて下さい。

