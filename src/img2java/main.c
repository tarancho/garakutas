#include <windows.h>
#include <stdio.h>


static BOOL
convert(LPTSTR lpszFileName)
{
    static int idx = 0;
    int i;
    FILE *fp;
    int c;

    idx++;
    
    if (!(fp = fopen(lpszFileName, "rb"))) {
        perror(lpszFileName);
        return FALSE;
    }
    
    printf("    /** %s ����ϊ������C���[�W�B*/\n", lpszFileName);
    printf("    Image img%d = Toolkit.getDefaultToolkit()."
           "createImage(new byte[] {", idx);

    for (i = 0; EOF != (c = getc(fp)); i++) {
        if (0 != i) {
            printf(", ");
        }
        if (0 == (i % 12)) {
            printf("\n        ");
        }
        printf("%d", (char) c);
    }
    fclose(fp);
    printf("});\n");
    return TRUE;
}

int
main(int argc, char *argv[])
{
    int i;

    printf("    /* ����!�z��̗v�f�������߂���ꍇ�̓R���p�C���G���["
           "�ɂȂ�܂��B*/\n");
    for (i = 1; i < argc; i++) {
        convert(argv[i]);
    }
}
