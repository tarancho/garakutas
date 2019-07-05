/* -*- mode: c++; coding: sjis-dos; -*-
 * $Id: main.c,v 1.2 2007/10/04 14:49:36 tfuruka1 Exp $
 * $Name:  $
 *
 * �W�����͂���ǂݍ��񂾒l�̍s����CRLF�ɕϊ����A�W���o�͂ɏo�͂��܂��B
 *
 * �����Ƃ��ẮAWindows�̃f�t�H���g��stdout(�f�t�H���g�Ńe�L�X�g���[
 * �h\n�ŏo�͂����\r\n�ɂȂ�)�̋@�\�𗘗p���Ă��邾���ŁA���ʂȏ�����
 * ��؍s�Ȃ��Ă��܂���BCygwin��sed���ŏ�������ƁA�s����lf�ɕϊ�����
 * ��̂ŁA�t�B���^�[�Ƃ��Ďg�p���鎖��z�肵�Ă��܂��B
 *
 * $Log: main.c,v $
 * Revision 1.2  2007/10/04 14:49:36  tfuruka1
 * Copyright�̔N���ԈႦ�Ă܂����B
 *
 * Revision 1.1  2006/11/15 12:08:04  tfuruka1
 * �V�K�ǉ�
 *
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

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
 "  -?, --help   ���̃w���v���b�Z�[�W��\�����܂��B\n"\
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
            fprintf(stderr, "�s���ȃI�v�V�����ł�: %s\n", argv[i]);
            showUsage();
            return 2;
        }
    }

    if (bDirect) {
        //�����������������������������������������������_�C���N�g�w��
        LPTSTR lpBuf;
        struct _stat stat;
        FILE *fp;
        size_t size;
        size_t cnt;

        if (!argv[i]) {
            fprintf(stderr, "-d, --direct�I�v�V�������w�肵���ꍇ��"
                    "���̓t�@�C���͕K�{�ł��B\n");
            return 2;
        }

        if (0 != _stat(argv[i], &stat)) {
            perror(argv[i]);
            return 3;
        }

        if (!(lpBuf = (LPTSTR) malloc(stat.st_size + 1))) {
            fprintf(stderr, "�������s���ł��B\n");
            return 3;
        }

        if (!(fp = fopen(argv[i], "rb"))) {
            perror(argv[i]);
            free(lpBuf);
            return 3;
        }
        size = fread(lpBuf, 1, stat.st_size, fp);
        if (size != (size_t) stat.st_size) {
            fprintf(stderr, "���̓t�@�C�����Ō㖘�ǂݍ��߂܂���B\n"
                    "\t�t�@�C���T�C�Y: %u\n"
                    "\t�ǂݍ��݃T�C�Y: %u\n", stat.st_size, size);
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
        //���������������������������������������������������W���o�͂�
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
