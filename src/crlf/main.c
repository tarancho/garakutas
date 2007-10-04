/* -*- mode: c++; coding: sjis-dos; -*-
 * $Id: main.c,v 1.2 2007/10/04 14:49:36 tfuruka1 Exp $
 * $Name:  $
 *
 * 標準入力から読み込んだ値の行末をCRLFに変換し、標準出力に出力します。
 *
 * 処理としては、Windowsのデフォルトのstdout(デフォルトでテキストモー
 * ド\nで出力すると\r\nになる)の機能を利用しているだけで、特別な処理は
 * 一切行なっていません。Cygwinのsed等で処理すると、行末がlfに変換され
 * るので、フィルターとして使用する事を想定しています。
 *
 * $Log: main.c,v $
 * Revision 1.2  2007/10/04 14:49:36  tfuruka1
 * Copyrightの年が間違えてました。
 *
 * Revision 1.1  2006/11/15 12:08:04  tfuruka1
 * 新規追加
 *
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

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
 "  -?, --help   このヘルプメッセージを表示します。\n"\
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
    int i;
    int c;
    BOOL bDirect = FALSE;

    for (i = 1; i < argc; i++) {
        if ('-' != *argv[i]) {
            break;
        }
        if (0 == strcmp("--version", argv[i])
            || 0 == strcmp("--v", argv[i])) {
            showVersion();
            return 1;
        } else if (0 == strcmp("--usage", argv[i])) {
            showUsage();
            return 1;
        } else if (0 == strcmp("--help", argv[i])
                   || 0 == strcmp("-?", argv[i])) {
            showHelp();
            return 1;
        } else if (0 == strcmp("-d", argv[i])
                   || 0 == strcmp("--direct", argv[i])) {
            bDirect = TRUE;
        } else {
            fprintf(stderr, "不正なオプションです: %s\n", argv[i]);
            showUsage();
            return 2;
        }
    }

    if (bDirect) {
        //━━━━━━━━━━━━━━━━━━━━━━━ダイレクト指定
        LPTSTR lpBuf;
        struct _stat stat;
        FILE *fp;
        size_t size;
        size_t cnt;

        if (!argv[i]) {
            fprintf(stderr, "-d, --directオプションを指定した場合は"
                    "入力ファイルは必須です。\n");
            return 2;
        }

        if (0 != _stat(argv[i], &stat)) {
            perror(argv[i]);
            return 3;
        }

        if (!(lpBuf = (LPTSTR) malloc(stat.st_size + 1))) {
            fprintf(stderr, "メモリ不足です。\n");
            return 3;
        }

        if (!(fp = fopen(argv[i], "rb"))) {
            perror(argv[i]);
            free(lpBuf);
            return 3;
        }
        size = fread(lpBuf, 1, stat.st_size, fp);
        if (size != (size_t) stat.st_size) {
            fprintf(stderr, "入力ファイルを最後迄読み込めません。\n"
                    "\tファイルサイズ: %u\n"
                    "\t読み込みサイズ: %u\n", stat.st_size, size);
            free(lpBuf);
            fclose(fp);
            return 3;
        }
        fclose(fp);

        makeBackupFile(argv[i]);

        if (!(fp = fopen(argv[i], "wt"))) {
            perror(argv[i]);
            free(lpBuf);
            return 3;
        }

        for (cnt = 0; cnt < size; cnt++) {
            if ('\r' == *(lpBuf + cnt)) {
                continue;
            }
            putc(*(lpBuf + cnt), fp);
        }
        fclose(fp);
        free(lpBuf);
    } else {
        //━━━━━━━━━━━━━━━━━━━━━━━━━標準出力へ
        if (argv[i]) {
            FILE *fp;

            fclose(stdin);
            fp = freopen(argv[i], "rt", stdin);
            if (!fp) {
                perror(argv[i]);
                return 3;
            }
        }

        while (EOF != (c = getc(stdin))) {
            if ('\r' == c) {
                continue;
            }
            putc(c, stdout);
        }
    }
    return 0;
}
