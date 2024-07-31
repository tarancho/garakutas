/*
 * 指定した曜日の週番号と日付の一覧表示
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#define VERSION "0.1 (" __DATE__ " " __TIME__ ")"
#define SEC_PER_DAY (60 * 60 * 24)              /* 一日の秒数 */
#define SEC_PER_WEEK (SEC_PER_DAY * 7)          /* 1週の秒数 */

static void
showVersion()
{
    printf("weeknum %s\n"
           "Copyright (C) 2024 T.Furukawa.\n"
           "指定した曜日の週番号と日付の一覧表示。\n",
           VERSION);
}

static void
showHelp()
{
    printf(
        "使用法: weeknum [オプション]\n"
        "特定の曜日の週番号と日付を出力します。\n"
        "\n"
        "  -y, --year <年>  対象の西暦年を指定。\n"
        "                   指定しない場合は現在の西暦年。\n"
        "  -w, --week <週>  対象の曜日を指定します(0=日, 1=月, ..., 6=土)。\n"
        "                   指定しない場合は 3=水 を使用します。\n"
        "  -f, --fmt <書式> 日付の書式。\n"
        "                   指定しない場合は %%Y/%%m/%%d を使用します。\n"
        "  -h, --help       この使い方を表示して終了。\n"
        "  -v, --version    バージョン情報を表示して終了。\n"
        );
}

int
main(int argc, char *argv[])
{
    time_t t = time(NULL);
    int wday = 3;                               /* 水曜日 */
    int c;
    const char *lpszFmt = "%Y/%m/%d";
    struct tm tm;
    struct tm *ptm;

    int option_index;
    static struct option options[] = {
        {"year", required_argument, NULL, 'y'},
        {"week", required_argument, NULL, 'w'},
        {"fmt", required_argument, NULL, 'f'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };

    /* 初期値設定 */
    if (-1 == t) {
        int err = errno;
        fprintf(stderr, "%s %s(%d) %s\n",
                __FUNCTION__, __FILE__, __LINE__, strerror(err));
        return 1;
    }
    ptm = localtime(&t);
    tm.tm_year = ptm->tm_year;

    while (-1 != (c = getopt_long(argc, argv, "y:w:f:hv",
                                  options, &option_index))) {
        switch (c) {
        case 'y':
            tm.tm_year = atoi(optarg) - 1900; /* 年 [1900からの経過年数] */
            break;
        case 'w':
            wday = atoi(optarg);
            break;
        case 'f':
            lpszFmt = optarg;
            break;
        case 'h':
            showHelp();
            return 0;
        case 'v':
            showVersion();
            return 0;
        default:
            fprintf(stderr, "不明なオプション: %c\n", c);
            return 1;
        }
    }

    tm.tm_mon = 0;                              /* 月 [0-11] */
    tm.tm_mday = 1;                             /* 日 [1-31] */

    tm.tm_hour = 0;                             /* 時 [0-23] */
    tm.tm_min = 0;                              /* 分 [0-59] */
    tm.tm_sec = 0;                              /* 秒 [0-61] */

    t = mktime(&tm);
    ptm = localtime(&t);

    /* 指定の曜日まで移動 */
    while (ptm->tm_wday != wday) {
        t += SEC_PER_DAY;
        ptm = localtime(&t);
    }

    while (ptm->tm_year == tm.tm_year) {
        char szBuf[80];

        strftime(szBuf, sizeof(szBuf) - 1, "%U", ptm);
        printf("%02d: ", (int) strtol(szBuf, NULL, 10) + 1);

        strftime(szBuf, sizeof(szBuf) - 1, lpszFmt, ptm);
        printf("%s\n", szBuf);

        t += SEC_PER_WEEK;
        ptm = localtime(&t);
    }
    return 0;
}
