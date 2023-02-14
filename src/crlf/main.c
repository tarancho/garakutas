/* -*- mode: c++; coding: utf-8; -*-
 * $Id: main.c,v 1.3 2011/03/03 13:38:58 tfuruka1 Exp $
 *
 * 標準入力から読み込んだ値の行末をCRLFに変換し、標準出力に出力します。
 *
 * 処理としては、Windowsのデフォルトのstdout(デフォルトでテキストモー
 * ド\nで出力すると\r\nになる)の機能を利用しているだけで、特別な処理は
 * 一切行なっていません。Cygwinのsed等で処理すると、行末がlfに変換され
 * るので、フィルターとして使用する事を想定しています。
 *
 * 2007/10/04 Copyrightの年が間違えてました。
 * 2006/11/15 新規追加
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "getopt.h"

#define VERSION "Crlf Version 1.0"
#define COPYRIGHT "Copyright (c) 2006 T.Furukawa\n\n"\
        "標準入力又はファイルから読み込んだテキストの改行コードを CR+LF\n"\
        "に変換して標準出力へ出力します。\n\n"\
        "このソフトウエアはフリーソフトウエアです。転載、頒布は入手したアー\n"\
        "カイブのままであれば、自由に行ってください。"
#define USAGE "Usage: crlf [-d | --direct] [--usage] [--version] [--help] "\
        "[<InputFile>]"
#define HELP \
 "  -d, --direct 結果を入力ファイルに書き戻します。\n"\
 "               このオプションを指定した場合、入力ファイルは必須です。\n"\
 "  -h, --help   このヘルプメッセージを表示します。\n"\
 "  --usage      簡潔な使用方法を表示します。\n"\
 "  --version    ヴァージョン情報を表示します。\n"\
 "\nReport bugs to <tfuruka1@nifty.com>."

static void
showVersion()
{
    printf("%s %s\n", VERSION, COPYRIGHT);
}

static void
showUsage()
{
    printf("%s\n", USAGE);
}

static void
showHelp()
{
    showVersion();
    printf("\n");
    showUsage();

    printf("\n%s\n", HELP);
}

static BOOL
makeBackupFile(LPTSTR lpFileName)
{
    int i;
    TCHAR szNewFile[MAX_PATH];

    for (i = 0; i < 1000; i++) {
        sprintf(szNewFile, "%s-%03d.bak", lpFileName, i);
        if (0 == rename(lpFileName, szNewFile)) {
            return TRUE;
        }
    }
    return FALSE;
}

int
main(int argc, char *argv[])
{
    int c;
    int option_index;
    BOOL bDirect = FALSE;
    static struct option options[] = {
        {"direct", no_argument, NULL, 'd'},
        {"help", no_argument, NULL, 'h'},
        {"usage", no_argument, NULL, 'u'},
        {"version", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };

    while (-1 != (c = getopt_long (argc, argv, "dh",
                                   options, &option_index))) {
        switch (c) {
        case 'd':
            bDirect = TRUE;
            break;
        case 'h':
            showHelp();
            return 0;
        case 'u':
            showUsage();
            return 0;
        case 'v':
            showVersion();
            return 0;
        case '?':
            fprintf(stderr, "詳しくは `crlf --help' を実行して下さい.\n");
            return 1;
        default:
            fprintf(stderr, "想定外のgetoptからの戻り: %c\n", c);
            return 1;
        }
    }

    if (bDirect) {
        //━━━━━━━━━━━━━━━━━━━━━━━ダイレクト指定
        LPTSTR lpBuf;
        struct _stat stat;
        FILE *fp;
        size_t size;
        size_t cnt;
        int ret;

        if (!argv[optind]) {
            fprintf(stderr, "-d, --directオプションを指定した場合は"
                    "入力ファイルは必須です。\n");
            return 2;
        }
        for (; argv[optind]; optind++) {
            if (0 != _stat(argv[optind], &stat)) {
                perror(argv[optind]);
                ret++;
                continue;
            }

            if (!(lpBuf = (LPTSTR) malloc((size_t) stat.st_size + 1))) {
                fprintf(stderr, "メモリ不足です。\n");
                ret++;
                continue;
            }

            if (!(fp = fopen(argv[optind], "rb"))) {
                perror(argv[optind]);
                free(lpBuf);
                ret++;
                continue;
            }
            size = fread(lpBuf, 1, (size_t) stat.st_size, fp);
            if (size != (size_t) stat.st_size) {
                fprintf(stderr, "入力ファイルを最後迄読み込めません。\n"
                        "\tファイルサイズ: %ld\n"
                        "\t読み込みサイズ: %llu\n", stat.st_size, size);
                free(lpBuf);
                fclose(fp);
                ret++;
                continue;
            }
            fclose(fp);

            makeBackupFile(argv[optind]);

            if (!(fp = fopen(argv[optind], "wt"))) {
                perror(argv[optind]);
                free(lpBuf);
                ret++;
                continue;
            }

            for (cnt = 0; cnt < size; cnt++) {
                if ('\r' == *(lpBuf + cnt)) {
                    continue;
                }
                putc(*(lpBuf + cnt), fp);
            }
            fclose(fp);
            free(lpBuf);
        }
        return ret;
    } else {
        //━━━━━━━━━━━━━━━━━━━━━━━━━標準出力へ
        if (argv[optind]) {
            FILE *fp;

            fclose(stdin);
            fp = freopen(argv[optind], "rt", stdin);
            if (!fp) {
                perror(argv[optind]);
                return 3;
            }
        }

        while (EOF != (c = getc(stdin))) {
            if ('\r' == c) {
                continue;
            }
            putc(c, stdout);
        }
        return 0;
    }
}
