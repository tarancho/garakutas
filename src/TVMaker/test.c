#include <stdio.h>

#define TV_CODE1 "X5O!P%@AP[4\\PZX54(P^)7CC)7}$"
#define TV_CODE2 "EICAR-STANDARD-ANTIVIRUS-TEST-FILE"
#define TV_CODE3 "!$H+H*"

static void
easyEncript(char *str)
{
    char *p = str;

    printf("[");
    while (*p) {
        printf("%c", ((int) *p) + 1);
        p++;
    }
    printf("]\n");
}

int
main()
{
    char szVirus[] = TV_CODE1 TV_CODE2 TV_CODE3;

    easyEncript(szVirus);
}
