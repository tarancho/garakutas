/* -*- mode: c++; coding: sjis; -*-
 * $Id: main.c,v 1.1 2007/10/04 14:42:58 tfuruka1 Exp $
 * $Name:  $
 *
 * ����ȃt�@�C���𐶐�����
 *
 * $Log: main.c,v $
 * Revision 1.1  2007/10/04 14:42:58  tfuruka1
 * �V�K�ǉ�
 *
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define VERSION "MegaFile Version 1.0"
#define COPYRIGHT "Copyright (c) 2007 T.Furukawa\n\n"\
        "����ȃt�@�C�����쐬���邾���̃c�[���ł��B\n"\
        "�t�@�C����1MB�P��(�A��1KB=1024Byte)�ɂȂ�܂��B\n\n"\
        "���̃\�t�g�E�G�A�̓t���[�\�t�g�E�G�A�ł��B�]�ځA�Еz�͓��肵���A�[\n"\
        "�J�C�u�̂܂܂ł���΁A���R�ɍs���Ă��������B"
#define USAGE "Usage: MegaFile [--usage] [--version] [--help] "\
        "<FileName> <Size>"

#define HELP \
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
            fprintf(stderr, "�s���ȃI�v�V�����ł�: %s\n", argv[i]);
            showUsage();
            return 2;
        }
    }

    lpszFileName = argv[i];
    if (!lpszFileName) {
        fprintf(stderr, "�t�@�C�������w�肵�ĉ������B\n");
        showUsage();
        return 3;
    }
    if (!argv[i + 1]) {
        fprintf(stderr, "�t�@�C���T�C�Y��MB�P�ʂŎw�肵�ĉ������B\n");
        showUsage();
        return 4;
    }
    cbMB = strtoul(argv[i + 1], NULL, 10);
    if (!cbMB) {
        fprintf(stderr, "�t�@�C���T�C�Y���s���ł�: %sn", argv[i + 1]);
        showUsage();
        return 5;
    }

    if (!(fp = fopen(lpszFileName, "wb"))) {
        fprintf(stderr, "�t�@�C�����쐬�ł��܂���B%s\n", _strerror(0));
        return 6;
    }
    for (i = 0; i < cbMB - 1; i++) {
        if (0 != fseek(fp, 1024 * 1024, SEEK_CUR)) {
            fprintf(stderr, "�V�[�N�G���[: %s\n", _strerror(0));
            fclose(fp);
            return 7;
        }
    }
    if (0 != fseek(fp, 1024 * 1024 - 6, SEEK_CUR)) {
        fprintf(stderr, "�V�[�N�G���[: %s\n", _strerror(0));
        fclose(fp);
        return 7;
    }
    fprintf(fp, "\nHOGE\n");
    fclose(fp);
    return 0;
}
