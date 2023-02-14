/*
 * $Id: main.c 1314 2013-03-19 01:37:36Z tfuruka1 $
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define VERSION "R1.0.1"

static void
easyDecript(char *str)
{
    char *p = str;

    while (*p) {
        *p = (char) (((int) *p) - 1);
        p++;
    }
}

int
main(int argc, char *argv[])
{
    FILE *fp;
    char filename[MAX_PATH];
    char *p;
    char szVirus[] = "Y6P\"Q&ABQ\5]Q[Y65)Q_*8DD*8~%FJDBS."
        "TUBOEBSE.BOUJWJSVT.UFTU.GJMF\"%I,I+";

    (void) argc;
    (void) argv;
    
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

    easyDecript(szVirus);
    fprintf(fp, "%s", szVirus);
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
