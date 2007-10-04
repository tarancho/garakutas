/* -*- mode: c++; coding: sjis; -*-
 * $Id: main.c,v 1.1 2007/10/04 14:42:58 tfuruka1 Exp $
 * $Name:  $
 *
 * 巨大なファイルを生成する
 *
 * $Log: main.c,v $
 * Revision 1.1  2007/10/04 14:42:58  tfuruka1
 * 新規追加
 *
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define VERSION "MegaFile Version 1.0"
#define COPYRIGHT "Copyright (c) 2007 T.Furukawa\n\n"\
        "巨大なファイルを作成するだけのツールです。\n"\
        "ファイルは1MB単位(但し1KB=1024Byte)になります。\n\n"\
        "このソフトウエアはフリーソフトウエアです。転載、頒布は入手したアー\n"\
        "カイブのままであれば、自由に行ってください。"
#define USAGE "Usage: MegaFile [--usage] [--version] [--help] "\
        "<FileName> <Size>"

#define HELP \
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

int main(int argc, char *argv[])
{
    FILE *fp;
    unsigned long i;
    char *lpszFileName;
    size_t cbMB;

    for (i = 1; i < (ULONG) argc; i++) {
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
        } else {
            fprintf(stderr, "不正なオプションです: %s\n", argv[i]);
            showUsage();
            return 2;
        }
    }

    lpszFileName = argv[i];
    if (!lpszFileName) {
        fprintf(stderr, "ファイル名を指定して下さい。\n");
        showUsage();
        return 3;
    }
    if (!argv[i + 1]) {
        fprintf(stderr, "ファイルサイズをMB単位で指定して下さい。\n");
        showUsage();
        return 4;
    }
    cbMB = strtoul(argv[i + 1], NULL, 10);
    if (!cbMB) {
        fprintf(stderr, "ファイルサイズが不正です: %sn", argv[i + 1]);
        showUsage();
        return 5;
    }

    if (!(fp = fopen(lpszFileName, "wb"))) {
        fprintf(stderr, "ファイルを作成できません。%s\n", _strerror(0));
        return 6;
    }
    for (i = 0; i < cbMB - 1; i++) {
        if (0 != fseek(fp, 1024 * 1024, SEEK_CUR)) {
            fprintf(stderr, "シークエラー: %s\n", _strerror(0));
            fclose(fp);
            return 7;
        }
    }
    if (0 != fseek(fp, 1024 * 1024 - 6, SEEK_CUR)) {
        fprintf(stderr, "シークエラー: %s\n", _strerror(0));
        fclose(fp);
        return 7;
    }
    fprintf(fp, "\nHOGE\n");
    fclose(fp);
    return 0;
}
