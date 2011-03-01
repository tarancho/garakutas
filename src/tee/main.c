/* $Id: main.c,v 1.1 2011/03/01 11:00:07 tfuruka1 Exp $
 *
 * tee�R�}���h�̃N���[��
 *
 * tee�R�}���h���g�p�ł��Ȃ����̏ꍇ�ɃR���p�C�����Ďg�p����B
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

#define VERSION "1.0 ($Rev$)"

#define BSIZE (8 * 1024)

#ifndef STDIN_FILENO
#    define STDIN_FILENO 0
#endif

#ifndef STDOUT_FILENO
#    define STDOUT_FILENO 1
#endif

typedef struct _list {
    struct _list *next;
    int fd;     /* �t�@�C���L�q�q */
    char *name; /* argv����擾�����t�@�C���� */
} LIST;
LIST *head;

static void
showVersion()
{
    printf("tee (clone) %s\n"
           "Copyright (C) 2011 T.Furukawa.\n"
           "tee�R�}���h�̃N���[���ł��B\n",
           VERSION);
}

static void
showHelp()
{
    printf("�g�p�@: tee [�I�v�V����]... [�t�@�C��]...\n"
           "�W�����͂��e�X�̃t�@�C���ɃR�s�[��, �W���o�͂ɂ��o��.\n"
           "\n"
           "  -a, --append            �w�肳�ꂽ�t�@�C���ɒǉ���,"
           " �㏑�����Ȃ�\n"
           "  -i, --ignore-interrupts �����݃V�O�i���𖳎�\n"
           "  --help     ���̎g������\�����ďI��\n"
           "  --version  �o�[�W��������\�����ďI��\n"
           "\n"
           "�t�@�C���� - ���w�肵���ꍇ�́A�ēx�A�W���o�͂ɏo�͂��܂�.\n"
           "\n"
           "�{�R�}���h�̓I���W�i����tee�R�}���h�̋����Ɠ��l�ɂȂ�悤��"
           "T.Furukawa�������������̂ł��B"
           "�]���āA�I���W�i���ƈقȂ镔�������邩������܂���B\n");
}

static void
err(int exitCode, char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(exitCode);
}

static void
warn(char *lpFmt, ...)
{
    va_list args;                               // �����W�J�p

    fprintf(stderr, "tee: ");

    // ������������ɍ����Đ��`����
    va_start(args, lpFmt);
    vfprintf(stderr, lpFmt, args);
    va_end(args);
}

void
add(int fd, char *name)
{
    LIST *p;

    if ((p = malloc((size_t)sizeof(LIST))) == NULL) {
        err(1, "malloc");
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
                fprintf(stderr, "����������܂���: %s",
                        options[option_index].name);
                return 1;
            }
        case 'a':
            /* �t�@�C���֒ǋL���� */
            append = 1;
            break;
        case 'i':
            /* SIGINT�𖳎����� */
            signal(SIGINT, SIG_IGN);
            break;
        case '?':
            fprintf(stderr, "�ڂ����� `tee --help' �����s���ĉ�����.\n");
            return 1;
        default:
            fprintf(stderr, "�z��O��getopt����̖߂�: %c\n", c);
            return 1;
        }
    }

    /* �o�b�t�@�̈�̊m�� */
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
                if ((wval = _write(p->fd, bp, n)) == -1) {
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
            // �W���o�͕͂�����g�p�ł���̂ŁA�����ł͕��Ȃ��B
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

