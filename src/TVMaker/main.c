/*
 * $Id: main.c 1314 2013-03-19 01:37:36Z tfuruka1 $
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define VERSION "R1.0.0.0"
#define TV_CODE1 "X5O!P%@AP[4\\PZX54(P^)7CC)7}$"
#define TV_CODE2 "EICAR-STANDARD-ANTIVIRUS-TEST-FILE"
#define TV_CODE3 "!$H+H*"

int
main(int argc, char *argv[])
{
    FILE *fp;
    char filename[MAX_PATH];
    char *p;

    printf("EICAR準拠 Virus Test File %s [Build:"
           __DATE__ " " __TIME__ "]\n", VERSION);

    if (!(p = getenv("TEMP")) && !(p = getenv("TMP"))) {
        fprintf(stderr, "環境変数 TEMP/TMP が存在しません。\n");
        return 1;
    }
    sprintf(filename, "%s/eicar.com", p);

    if (NULL == (fp = fopen(filename, "wb"))) {
        perror(NULL);
        return 1;
    }
    fprintf(fp, "%s%s%s", TV_CODE1, TV_CODE2, TV_CODE3);
    fclose(fp);

    printf("%s にテスト用ウィルスファイルを作成しました。\n", filename);

    return 0;
}

/*
 * Local Variables:
 * mode: c
 * coding: utf-8
 * End:
 */
