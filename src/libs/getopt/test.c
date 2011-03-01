#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include "getopt.h"
int
main (int argc, char **argv)
{
    int c;
    int digit_optind = 0;
    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"add", required_argument, NULL, 0},
            {"append", no_argument, NULL, 0},
            {"delete", required_argument, NULL, 0},
            {"verbose", no_argument, NULL, 0},
            {"create", required_argument, NULL, 'c'},
            {"file", required_argument, NULL, 0},
            {NULL, 0, NULL, 0}
        };
        c = getopt_long (argc, argv, "abc:d:012",
                         long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 0:
            // ロングオプションのみの場合
            printf("option %s ", long_options[option_index].name);
            if (optarg) {
                printf("with arg %s", optarg);
            }
            printf("\n");
            break;
        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind) {
                printf ("digits occur in two different argv-elements.\n");
            }
            digit_optind = this_option_optind;
            printf("option %c\n", c);
            break;
        case 'a':
            printf("option a\n");
            break;
        case 'b':
            printf("option b\n");
            break;
        case 'c':
            // create ロングオプションは此方で処理される
            printf("option c with value '%s'\n", optarg);
            break;
        case 'd':
            printf("option d with value '%s'\n", optarg);
            break;
        case '?':
            printf("メッセージは getopt内で出力\n");
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc) {
            printf("%s ", argv[optind++]);
        }
        printf("\n");
    }
    exit(0);
}

