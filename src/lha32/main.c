/* -*- mode: C; coding: utf-8; -*-
 * $Id: main.c,v 1.1 2006/12/06 14:05:27 tfuruka1 Exp $
 * $Name:  $
 *
 * LHA コマンド unlha.dll使用
 *
 * $Log: main.c,v $
 * Revision 1.1  2006/12/06 14:05:27  tfuruka1
 * 新規追加
 *
 */
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "unlha32.h"

#define BUILD "(BUILD: " __DATE__ " " __TIME__ ")"
#define VERSION "LHA32 Version 1.00 " BUILD\
    "\nCopyright(c) 2006 T.Furukawa"\
    "\n\nImplement UNLHA.DLL "


#define BUF_SIZE (1024 * 1024)

int
main(int argc, char *argv[])
{
    int ret;
    LPTSTR lpszBuf = malloc(BUF_SIZE + 1);
    LPTSTR p = strchr(GetCommandLine(), ' ');

    printf("%s(Version %1g.%1g)\n", VERSION,
           (double)UnlhaGetVersion() / 100,
           (double)UnlhaGetSubVersion() / 100);

    if (1 == argc) {
        printf("USAGE: LHA32 %s\n\n"
               "詳細はUNLHA.DLLのドキュメントを参照して下さい\n",
               "[<command>] [[-<switch>[+|-|0|1|2]]...] "
               "<archive_file_name>[.LZH]"
               "\n\t [[<base_directory_name>\\] "
               "[<path_name>|<wild_name>]...]]...");

        return 1;
    }

    if (p) {
        p++;
    } else {
        p = "";
    }

    ret = Unlha(NULL, p, lpszBuf, BUF_SIZE);
    printf("%s", lpszBuf);
    return ret;
}
