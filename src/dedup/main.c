/* $Id: main.c,v 1.1 2011/03/01 11:00:07 tfuruka1 Exp $
 *
 * uniqコマンドで対応できなかったのでdedupを作る。
 *
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <signal.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <getopt.h>

#define VERSION "0.1 ($Rev$)"

#ifndef TRUE
#    define TRUE 1
#    define FALSE 0
#endif

#define LINE_SIZE (1024)

static void
showVersion()
{
    printf("dedup %s\n"
           "Copyright (C) 2019 T.Furukawa.\n"
           "重複行(複数行の繰返し行)の排除。\n",
           VERSION);
}

static void
showHelp()
{
    printf(
        "使用法: dedup [オプション]\n"
        "重複行を排除します。単行のみでなく複数行の繰返しも排除できます。\n"
        "\n"
        "  -d, --deduplicate <行数> 繰返し行を指定します。\n"
        "  -h, --help               この使い方を表示して終了\n"
        "  -v, --version            バージョン情報を表示して終了\n"
        "\n"
        "行数に 1を指定した場合は uniq コマンドと同じ動作になります。"
        "\n");
}

void
deduplicate(FILE *in, FILE *out, char *buf, int line)
{
    int i;
    int b;
    char *rb;

    /* 初期化 */
    for (i = 0; i < line * 2; i++) {
        *(buf + i * LINE_SIZE) = '\0';
    }

    rb = buf + (line * 2 - 1) * LINE_SIZE;
    while (fgets(rb, LINE_SIZE, in)) {
        /* 先頭 n 行はチェックしない */
        for (i = 0; i < line; i++) {
            if ('\0' == *(buf + i * LINE_SIZE)) {
                fwrite(rb, strlen(buf + (line * 2 - 1) * LINE_SIZE), 1, out);
                strcpy(buf + i * LINE_SIZE, rb);
                break;
            }
        }
        if (i < line) {
            continue;
        }

        /* データの詰め込み */
        for (i = line; i < line * 2 - 1; i++) {
            if ('\0' == *(buf + i * LINE_SIZE)) {
                strcpy(buf + i * LINE_SIZE, rb);
                *rb = '\0';
                break;
            }
        }

        /* データの比較 */
        b = TRUE;
        for (i = 0; i < line; i++) {
            if ('\0' == *(buf + (line + i) * LINE_SIZE)) {
                /* 一部一致(未だ判定できない) */
                break;
            }
            if (0 != strcmp(
                    buf + i * LINE_SIZE,
                    buf + (line + i) * LINE_SIZE)) {
                b = FALSE;
                break;
            }
        }

        if (b) {
            if (i == line) {
                /* 完全一致 */
                for (i = line; i < line * 2 - 1; i++) {
                    *(buf + i * LINE_SIZE) = '\0';
                }
            }
            continue;
        }

        /* 以下は不一致の場合の処理 */
        for (i = 0; i < line * 2 - 1; i++) {
            strcpy(buf + i * LINE_SIZE,
                   buf + (i + 1) * LINE_SIZE);
        }
        fwrite(buf + (line - 1) * LINE_SIZE,
               strlen(buf + (line - 1) * LINE_SIZE), 1, out);
    }

    /* 残っているデータを出力 */
    for (i = line; i < line * 2 - 1; i++) {
        if ('\0' == *(buf + i * LINE_SIZE)) {
            break;
        }
        fwrite(buf + i * LINE_SIZE, strlen(buf + i * LINE_SIZE), 1, out);
    }
}

int
main(int argc, char *argv[])
{
    int dupline = 1;
    char *buf;
    int c;
    int option_index;
    static struct option options[] = {
        {"dedupulicate", required_argument, NULL, 'd'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };

    while (-1 != (c = getopt_long(argc, argv, "d:hv",
                                  options, &option_index))) {
        switch (c) {
        case 'd':
            if (0 == (dupline = strtol(optarg, NULL, 10))) {
                dupline = 1;
            }
            break;
        case 'h':
            showHelp();
            return 0;
        case 'v':
            showVersion();
            return 0;
        default:
            fprintf(stderr, "想定外のgetoptからの戻り: %c\n", c);
            return 1;
        }
    }

    /* バッファ領域の確保 */
    if (NULL == (buf = malloc((size_t) (LINE_SIZE * dupline * 2)))) {
        int err = errno;
        fprintf(stderr, "%s %s(%d) %s\n",
                __FUNCTION__, __FILE__, __LINE__, strerror(err));
        return 1;
    }

    setmode(0, O_BINARY);
    setmode(1, O_BINARY);

    deduplicate(stdin, stdout, buf, dupline);

    free(buf);
    return 0;
}

