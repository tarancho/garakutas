/* -*- mode: c++; coding: sjis; -*-
 * Copyright (C) 2005 Tadamegu Furukawa
 * $Id: main.c,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
 * $Name:  $
 *
 * キーボードから一文字読み込み、読み込んだ結果を返却します。バッチ処
 * 理内で使用する事を想定しています。
 *
 * $Log: main.c,v $
 * Revision 1.1  2006/11/15 12:08:04  tfuruka1
 * 新規追加
 *
 */

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

static int
GetCh()
{
    // 先行入力バッファをフラッシュする
    while (_kbhit()) {
        _getch();
    }
    // 何かキーが押下されるまで待つ
    while (!_kbhit());

    return _getch();
}

static void
Usage()
{
    // 可能=可\x94\x5c、表示=\x95\x5c示
    fprintf(stderr, "$Id: main.c,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $\n"
            "Usage: betkey <KeyLists> <Message>\n\n"
            "KeyLists 入力可\x94\x5cな入力文字を羅列します。\n"
            "Message  \x95\x5c示するメッセージ\n"
            "\n"
            "入力された文字のKeyListsの添字(0 align)を返却します。\n"
            "標準入力は使用できません。必ずコンソールから入力する\n"
            "必要があります。\n"
            "\n"
            "使用例:\n"
            "    batkey yn 処理を継続して宜しいですか(y/n)\n"
            "    y 又は n が入力される迄、処理を中断します。\n"
        );
}

int main(int argc, char *argv[])
{
    char *p;
    char c;
    int i;

    if (argc < 3) {
        Usage();
        return 255;
    }

    for (i = 2; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf(":");
    fflush(stdout);

    while (!(p = strchr(argv[1], c = GetCh())));
    printf(" [%c]\n", c);

    return (int)((ULONG)p - (ULONG)argv[1]);
}
