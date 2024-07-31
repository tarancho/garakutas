#include <stdio.h>
#include <string.h>
#define PI "3.141592653"
int
main(int argc, char *argv[])
{
    double pi = 0.0;
    char szpi[1024];
    long i;

    (void) argc;
    (void) argv;

    for (i = 0; i <= 1000000000; i++) {
        double a = (1.0 / (double) (1 + i * 2));
        if (0 == (i % 2)) {
            pi += a;
        } else {
            pi -= a;
        }
        sprintf(szpi, "%10.9lf", pi * 4.0);
        if (0 == (i % 1000)) {
            printf("%s\r", szpi);
            fflush(stdout);
        }
        if (0 == strcmp(PI, szpi)) {
            printf("%s\r", szpi);
            printf("\n%ld", i);
            break;
        }
    }
}
