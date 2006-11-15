/* -*- mode: c++; coding:sjis; -*-
 * $Id: main.c,v 1.1 2006/11/15 12:08:03 tfuruka1 Exp $
 * $Name:  $
 *
 * ���Ɍ����X���[�v
 *
 * $Log: main.c,v $
 * Revision 1.1  2006/11/15 12:08:03  tfuruka1
 * �V�K�ǉ�
 *
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define OPT_FEEDBACK "--FEEDBACK="

int
main(int argc, char *argv[])
{
    int i;
    int nFeedBack = 0;
    int cnt = 0;

    for (i = 1; i < argc; i++) {
        if ('-' != *argv[i]) {
            break;
        }
        if (0 == strnicmp(argv[i], OPT_FEEDBACK, strlen(OPT_FEEDBACK))) {
            nFeedBack = atoi(strchr(argv[i], '=') + 1);
        }
        // �I�v�V�����͌��
    }
    if (!argv[i]) {
        return 0;
    }
    cnt = atoi(argv[i]);
    for (i = 0; i < cnt; i++) {
        if (nFeedBack && (0 == (i % nFeedBack))) {
            printf(".");
            fflush(stdout);
        }
        Sleep(1000);
    }
    printf("\n");
    return 0;
}
