/* $Id: main.c,v 1.1 2011/03/01 11:00:07 tfuruka1 Exp $
 *
 * teeコマンドのクローン
 *
 * teeコマンドを使用できない環境の場合にコンパイルして使用する。
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

#define VERSION "1.0 (Build: " __DATE__ " " __TIME__ ")"

#define BSIZE (8 * 1024)

#ifndef STDIN_FILENO
#    define STDIN_FILENO 0
#endif

#ifndef STDOUT_FILENO
#    define STDOUT_FILENO 1
#endif

typedef struct _list {
    struct _list *next;
    int fd;                           /* ファイル記述子 */
    const char *name;                 /* argvから取得したファイル名 */
} LIST;
LIST *head;

static void
showVersion()
{
    printf("tee (clone) %s\n"
           "Copyright (C) 2011 T.Furukawa.\n"
           "teeコマンドのクローンです。\n",
           VERSION);
}

static void
showHelp()
{
    printf("使用法: tee [オプション]... [ファイル]...\n"
           "標準入力を各々のファイルにコピーし, 標準出力にも出力.\n"
           "\n"
           "  -a, --append            指定されたファイルに追加し,"
           " 上書きしない\n"
           "  -i, --ignore-interrupts 割込みシグナルを無視\n"
           "  --help     この使い方を表示して終了\n"
           "  --version  バージョン情報を表示して終了\n"
           "\n"
           "ファイルに - を指定した場合は、再度、標準出力に出力します.\n"
           "\n"
           "本コマンドはオリジナルのteeコマンドの挙動と同様になるように"
           " T.Furukawa が実装したものです。"
           "従って、オリジナルと異なる部分もあるかもしれません。\n");
}

static void
err(int exitCode, const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(exitCode);
}

static void
warn(const char *lpFmt, ...)
{
    va_list args;                               // 引数展開用

    fprintf(stderr, "tee: ");

    // 文字列を書式に合せて整形する
    va_start(args, lpFmt);
    vfprintf(stderr, lpFmt, args);
    va_end(args);
}

void
add(int fd, const char *name)
{
    LIST *p;

    if ((p = malloc((size_t)sizeof(LIST))) == NULL) {
        err(1, (const char *) "malloc");
    }
    p->fd = fd;
    p->name = name;
    p->next = head;
    head = p;
}

int
main(int argc, char *argv[])
{
    LIST *p;
    int n, fd, rval, wval;
    char *bp;
    int append, exitval;
    char *buf;
    int c;
    int option_index;
    static struct option options[] = {
        {"append", no_argument, NULL, 'a'},
        {"ignore-interrupts", no_argument, NULL, 'i'},
        {"help", no_argument, NULL, 0},
        {"version", no_argument, NULL, 0},
        {NULL, 0, NULL, 0}
    };

    append = 0;

    while (-1 != (c = getopt_long (argc, argv, "ai",
                                   options, &option_index))) {
        switch (c) {
        case 0:
            if (0 == strcmp("help", options[option_index].name)) {
                showHelp();
                return 0;
            } else if (0 == strcmp("version", options[option_index].name)) {
                showVersion();
                return 0;
            } else {
                fprintf(stderr, "処理がありません: %s",
                        options[option_index].name);
                return 1;
            }
        case 'a':
            /* ファイルへ追記する */
            append = 1;
            break;
        case 'i':
            /* SIGINTを無視する */
            signal(SIGINT, SIG_IGN);
            break;
        case '?':
            fprintf(stderr, "詳しくは `tee --help' を実行して下さい.\n");
            return 1;
        default:
            fprintf(stderr, "想定外のgetoptからの戻り: %c\n", c);
            return 1;
        }
    }

    /* バッファ領域の確保 */
    if (NULL == (buf = malloc((size_t)BSIZE))) {
        err(1, "malloc");
    }

    add(STDOUT_FILENO, "stdout");

    for (exitval = 0; argv[optind]; optind++) {
        if (0 == strcmp("-", argv[optind])) {
            add(STDOUT_FILENO, "stdout");
            continue;
        }
        if ((fd = _open(argv[optind], append ? O_WRONLY|O_CREAT|O_APPEND :
                        O_WRONLY|O_CREAT|O_TRUNC,
                        _S_IREAD | _S_IWRITE)) < 0) {
            warn("%s: %s", argv[optind], _strerror(NULL));
            exitval = 1;
        } else {
            add(fd, *argv);
        }
    }

    while ((rval = _read(STDIN_FILENO, buf, BSIZE)) > 0) {
        for (p = head; p; p = p->next) {
            n = rval;
            bp = buf;
            do {
                if ((wval = _write(p->fd, bp, (unsigned int) n)) == -1) {
                    warn("%s: %s", p->name, _strerror(NULL));
                    exitval = 1;
                    break;
                }
                bp += wval;
            } while (n -= wval);
        }
    }

    if (rval < 0) {
        warn("read");
        exitval = 1;
    }

    for (p = head; p; p = p->next) {
        if (STDOUT_FILENO == p->fd) {
            // 標準出力は複数回使用できるので、ここでは閉じない。
            continue;
        }
        if (_close(p->fd) == -1) {
            warn("%s: %s ", p->name, _strerror(NULL));
            exitval = 1;
        }
    }
    _close(STDOUT_FILENO);
    return exitval;
}
