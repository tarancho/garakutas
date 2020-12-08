/* $Id$
 * RDPでのファイルの複写とクリップボードの使用を抑止します。
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <getopt.h>

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
    HRESULT hResult = S_OK;
    // 戻り値
    DWORD dwResult = 0;

    // HKEY
    HKEY hKey = NULL;
    DWORD dwValue = 1;

    // SYSTEM\CurrentControlSet\Control\Terminal Server\WinStations\RDP-Tcp
    char szSubKey[128] = "TZTUFN"
        "]DvssfouDpouspmTfu]Dpouspm]Ufsnjobm!Tfswfs]XjoTubujpot]SEQ.Udq";
    char szValueNames[3][80] = {"gEjtbcmfDen",  // "fDisableCdm"
                                "gEjtbcmfDmjq", //"fDisableClip"
                                "\0"};
    int i;
    int c;

    int option_index;
    static struct option options[] = {
        {"encript", required_argument, NULL, 'e'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };

    while (-1 != (c = getopt_long(argc, argv, "e:hv",
                                  options, &option_index))) {
        switch (c) {
        case 'e':
            easyEncript(optarg);
            return 0;
        case 'h':
            //showHelp();
            return 0;
        case 'v':
            //showVersion();
            return 0;
        default:
            fprintf(stderr, "想定外のgetoptからの戻り: %c\n", c);
            return 1;
        }
    }

    /*
      レジストリオープン
    */
    easyDecript(szSubKey);
    dwResult = (DWORD) RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,            // レジストリキー
        szSubKey,                      // レジストリサブキー
        0,                             // Reserved(0固定)
        KEY_SET_VALUE,                 // アクセス権
        &hKey                          // キーハンドルの受け取り位置
        );
    if (ERROR_SUCCESS != dwResult) {
        // エラー
        hResult = HRESULT_FROM_WIN32(dwResult);
        fprintf(stderr, "Registory Open error: %lx\n", hResult);
        MessageBox(NULL, TEXT("エラーが発生しました。"), TEXT("エラー"),
                   MB_ICONERROR);
        return 1;
    }

    for (i = 0; szValueNames[i][0]; i++) {
        easyDecript(szValueNames[i]);
        dwResult = (DWORD) RegSetValueEx(
            hKey,                                  // キーハンドル
            szValueNames[i],                       // ValueName
            0,                                     // Reserved(0固定)
            REG_DWORD,                             // データ型
            (const LPBYTE) &dwValue,               // 書き込み内容
            sizeof(DWORD)                          // 書き込みサイズ(BYTE)
            );
        if (ERROR_SUCCESS != dwResult) {
            // エラー
            hResult = HRESULT_FROM_WIN32(dwResult);
            fprintf(stderr, "Registory Set value error: %lx\n", hResult);
            return 1;
        }
    }
    RegCloseKey(hKey);
    MessageBox(NULL, TEXT("正常に更新しました。"), TEXT("正常終了"),
               MB_ICONINFORMATION);
    return 0;
}
