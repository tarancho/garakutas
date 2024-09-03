/* $Id$
 * RDPでのファイルの複写とクリップボードの使用を抑止します。
 */
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <getopt.h>

/*--------------------------------------------------------------------
 * dwErr で指定されたエラーコードに対応するエラーメッセージを関数にシ
 * ステムメッセージテーブルリソースから検索して一時的な文字列へのポイ
 * ンタを返却する。dwErr は GetLastError から得た値を指定する事。lpsz
 * はエラーメッセージへ追加する文字列を指定する。API 名等を指定する。
 * *-------------------------------------------------------------------*/
static LPCSTR WINAPI
GetLastErrorMessage(LPCSTR lpsz, DWORD dwErr)
{
    static char sz[1024];
    char szTmp[256];
    DWORD i;

    if (!(i = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                            FORMAT_MESSAGE_IGNORE_INSERTS,
                            NULL, dwErr, 0, szTmp, sizeof(szTmp), NULL))) {
        strcpy(szTmp, "---");
    } else {
        szTmp[i] = '\0';
        for (i--; 0 <= (int) i; i--) {
            if ('\n' == szTmp[i] || '\r' == szTmp[i]) {
                szTmp[i] = '\0';
            }
        }
    }
    wsprintf(sz, "[WIN32] %s: Error Code = %d(%#02x): %s",
             lpsz, dwErr, dwErr, szTmp);
    return (LPCTSTR)sz;
}


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
    char szValueNames[][80] = {
        "gEjtbcmfDen",  // "fDisableCdm"
        "gEjtbcmfDmjq", // "fDisableClip"
        "\0"
    };
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
        fprintf(stderr, "%s %lx\n",
                GetLastErrorMessage("Registory Open", dwResult), hResult);
        MessageBox(NULL, TEXT("エラーが発生しました。"
                              "詳細はコンソールの"
                              "メッセージを確認して下さい。"),
                   TEXT("エラー"),
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
            fprintf(stderr, "%s %lx\n",
                    GetLastErrorMessage("Registory set value",
                                        dwResult), hResult);
            RegCloseKey(hKey);
            return 1;
        }
    }
    RegCloseKey(hKey);
    MessageBox(NULL, TEXT("正常に更新しました。"), TEXT("正常終了"),
               MB_ICONINFORMATION);
    return 0;
}
