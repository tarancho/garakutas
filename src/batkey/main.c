/* -*- mode: c++; coding: sjis; -*-
 * Copyright (C) 2005 Tadamegu Furukawa
 * $Id: main.c,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
 * $Name:  $
 *
 * �L�[�{�[�h����ꕶ���ǂݍ��݁A�ǂݍ��񂾌��ʂ�ԋp���܂��B�o�b�`��
 * �����Ŏg�p���鎖��z�肵�Ă��܂��B
 *
 * $Log: main.c,v $
 * Revision 1.1  2006/11/15 12:08:04  tfuruka1
 * �V�K�ǉ�
 *
 */

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

static int
GetCh()
{
    // ��s���̓o�b�t�@���t���b�V������
    while (_kbhit()) {
        _getch();
    }
    // �����L�[�����������܂ő҂�
    while (!_kbhit());

    return _getch();
}

static void
Usage()
{
    // �\=��\x94\x5c�A�\��=\x95\x5c��
    fprintf(stderr, "$Id: main.c,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $\n"
            "Usage: betkey <KeyLists> <Message>\n\n"
            "KeyLists ���͉�\x94\x5c�ȓ��͕����𗅗񂵂܂��B\n"
            "Message  \x95\x5c�����郁�b�Z�[�W\n"
            "\n"
            "���͂��ꂽ������KeyLists�̓Y��(0 align)��ԋp���܂��B\n"
            "�W�����͎͂g�p�ł��܂���B�K���R���\�[��������͂���\n"
            "�K�v������܂��B\n"
            "\n"
            "�g�p��:\n"
            "    batkey yn �������p�����ċX�����ł���(y/n)\n"
            "    y ���� n �����͂���閘�A�����𒆒f���܂��B\n"
        );
}

int main(int argc, char *argv[])
{
    char *p;
    char c;
    int i;

    if (argc < 3) {
        Usage();
        return 255;
    }

    for (i = 2; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf(":");
    fflush(stdout);

    while (!(p = strchr(argv[1], c = GetCh())));
    printf(" [%c]\n", c);

    return (int)((ULONG)p - (ULONG)argv[1]);
}
