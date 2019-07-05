/* -*- mode: c++; coding: sjis-dos; -*-
 * $Id: main.c,v 1.3 2011/03/03 13:38:58 tfuruka1 Exp $
 *
 * �W�����͂���ǂݍ��񂾒l�̍s����CRLF�ɕϊ����A�W���o�͂ɏo�͂��܂��B
 *
 * �����Ƃ��ẮAWindows�̃f�t�H���g��stdout(�f�t�H���g�Ńe�L�X�g���[
 * �h\n�ŏo�͂����\r\n�ɂȂ�)�̋@�\�𗘗p���Ă��邾���ŁA���ʂȏ�����
 * ��؍s�Ȃ��Ă��܂���BCygwin��sed���ŏ�������ƁA�s����lf�ɕϊ�����
 * ��̂ŁA�t�B���^�[�Ƃ��Ďg�p���鎖��z�肵�Ă��܂��B
 *
 * 2007/10/04 Copyright�̔N���ԈႦ�Ă܂����B
 * 2006/11/15 �V�K�ǉ�
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "getopt.h"

#define VERSION "Crlf Version 1.0"
#define COPYRIGHT "Copyright (c) 2006 T.Furukawa\n\n"\
        "�W�����͖��̓t�@�C������ǂݍ��񂾃e�L�X�g�̉��s�R�[�h�� CR+LF\n"\
        "�ɕϊ����ĕW���o�͂֏o�͂��܂��B\n\n"\
        "���̃\�t�g�E�G�A�̓t���[�\�t�g�E�G�A�ł��B�]�ځA�Еz�͓��肵���A�[\n"\
        "�J�C�u�̂܂܂ł���΁A���R�ɍs���Ă��������B"
#define USAGE "Usage: crlf [-d | --direct] [--usage] [--version] [--help] "\
        "[<InputFile>]"
#define HELP \
 "  -d, --direct ���ʂ���̓t�@�C���ɏ����߂��܂��B\n"\
 "               ���̃I�v�V�������w�肵���ꍇ�A���̓t�@�C���͕K�{�ł��B\n"\
 "  -h, --help   ���̃w���v���b�Z�[�W��\�����܂��B\n"\
 "  --usage      �Ȍ��Ȏg�p���@��\�����܂��B\n"\
 "  --version    ���@�[�W��������\�����܂��B\n"\
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
            fprintf(stderr, "�ڂ����� `crlf --help' �����s���ĉ�����.\n");
            return 1;
        default:
            fprintf(stderr, "�z��O��getopt����̖߂�: %c\n", c);
            return 1;
        }
    }

    if (bDirect) {
        //�����������������������������������������������_�C���N�g�w��
        LPTSTR lpBuf;
        struct _stat stat;
        FILE *fp;
        size_t size;
        size_t cnt;
        int ret;

        if (!argv[optind]) {
            fprintf(stderr, "-d, --direct�I�v�V�������w�肵���ꍇ��"
                    "���̓t�@�C���͕K�{�ł��B\n");
            return 2;
        }
        for (; argv[optind]; optind++) {
            if (0 != _stat(argv[optind], &stat)) {
                perror(argv[optind]);
                ret++;
                continue;
            }

            if (!(lpBuf = (LPTSTR) malloc(stat.st_size + 1))) {
                fprintf(stderr, "�������s���ł��B\n");
                ret++;
                continue;
            }

            if (!(fp = fopen(argv[optind], "rb"))) {
                perror(argv[optind]);
                free(lpBuf);
                ret++;
                continue;
            }
            size = fread(lpBuf, 1, stat.st_size, fp);
            if (size != (size_t) stat.st_size) {
                fprintf(stderr, "���̓t�@�C�����Ō㖘�ǂݍ��߂܂���B\n"
                        "\t�t�@�C���T�C�Y: %u\n"
                        "\t�ǂݍ��݃T�C�Y: %u\n", stat.st_size, size);
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
        //���������������������������������������������������W���o�͂�
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
