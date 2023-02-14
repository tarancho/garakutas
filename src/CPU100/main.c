/* $Id: main.c 1313 2013-03-19 00:10:02Z tfuruka1 $
 *
 * CPU 使用率を100%にするツール
 *
 * CPU使用率を100%にしますが、システムの負荷は軽いです。
 */
#include <windows.h>
#include <stdio.h>

#define VERSION "R0.1.0.0 ($Rev: 1313 $)"

#define LINE_STR "━━━━━━━━━━━━━━━━━"\
                 "━━━━━━━━━━━━━━━━━━"

BOOL (WINAPI *lpGetSystemTimes)(LPFILETIME lpIdleTime,
                                LPFILETIME lpKernelTime,
                                LPFILETIME lpUserTime);

static LPCTSTR
GetProcessorArchitectureStr(WORD wPA)
{
    static char szBuf[256];

    switch (wPA) {
    case PROCESSOR_ARCHITECTURE_INTEL:
        strcpy(szBuf, "INTEL");
        break;
    case PROCESSOR_ARCHITECTURE_MIPS:
        strcpy(szBuf, "MIPS");
        break;
    case PROCESSOR_ARCHITECTURE_ALPHA:
        strcpy(szBuf, "ALPHA");
        break;
    case PROCESSOR_ARCHITECTURE_PPC:
        strcpy(szBuf, "POWER-PC");
        break;
    case PROCESSOR_ARCHITECTURE_SHX:
        strcpy(szBuf, "SH");
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        strcpy(szBuf, "ARM");
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        strcpy(szBuf, "INTEL-64");
        break;
    case PROCESSOR_ARCHITECTURE_ALPHA64:
        strcpy(szBuf, "ALPHA-64");
        break;
    case PROCESSOR_ARCHITECTURE_UNKNOWN:
        strcpy(szBuf, "UNKNOWN");
        break;
    default:
        sprintf(szBuf, "UNKNOWN: %x", wPA);
        break;
    }
    return szBuf;
}

static LPCTSTR
GetProcessorTypeStr(DWORD dwPt)
{
    static char szBuf[256];

    switch (dwPt) {
    case PROCESSOR_INTEL_386:
        sprintf(szBuf, "INTEL386(%lu)", dwPt);
        break;
    case PROCESSOR_INTEL_486:
        sprintf(szBuf, "INTEL486(%lu)", dwPt);
        break;
    case PROCESSOR_INTEL_PENTIUM:
        sprintf(szBuf, "INTEL PENTIUM(%lu)", dwPt);
        break;
    case PROCESSOR_MIPS_R4000:
        sprintf(szBuf, "MIPS R4000(%lu", dwPt);
        break;
    case PROCESSOR_ALPHA_21064:
        sprintf(szBuf, "ALPHA 21064(%lu)", dwPt);
        break;
    default:
        sprintf(szBuf, "UNKNOWn(%lu)", dwPt);
        break;
    }
    return szBuf;
}

static LPCTSTR
GetActiveProcessorMaskStr(DWORD dwAPM)
{
    static char szBuf[36];
    int i;

    szBuf[0] = '\0';
    for (i = 0; i < 32; i++) {
        strcat(szBuf, ((dwAPM >> i) & 1) ? "*" : ".");
    }
    return szBuf;
}

static DWORD WINAPI
ThreadFunc(LPVOID lpPara)
{
    printf("CPU %d 占有開始...\n", *(int *) lpPara);
    while (TRUE) {
    }
    return 0;
}

static void
selfLoop()
{
    unsigned char kaiten[] = "―＼｜／";

    unsigned char wk[4];
    unsigned int i = 0;
    unsigned int j;
    unsigned int iSleep = 1000;

    LONGLONG ftOldIdle = 0;
    LONGLONG ftOldKernel = 0;
    LONGLONG ftOldUser = 0;

    LONGLONG ftIdle;
    LONGLONG ftKernel;
    LONGLONG ftUser;

    HANDLE lpLib = LoadLibrary("kernel32.dll");
    printf("Library Handle: %llx\n", (ULONGLONG) lpLib);
    if (!lpLib) {
        return;
    }
    lpGetSystemTimes = GetProcAddress(lpLib, "GetSystemTimes");

    printf("GetSystemTimes API Address: %lx\n", (ULONG) lpGetSystemTimes);
    if (!lpGetSystemTimes) {
        return;
    }
    printf("終了する場合は CTRL-C を押下して下さい。\n\n");

    while (TRUE) {
        j = i++ % 4;
        wk[0] = kaiten[j * 2];
        wk[1] = kaiten[j * 2 + 1];
        wk[2] = '\0';

        lpGetSystemTimes((LPFILETIME)&ftIdle,
                         (LPFILETIME)&ftKernel,
                         (LPFILETIME)&ftUser);
        if (0 != ftOldIdle) {
            LONGLONG llIdle = ftIdle - ftOldIdle;
            LONGLONG llKernel = ftKernel - ftOldKernel;
            LONGLONG llUser = ftUser - ftOldUser;
            LONGLONG llTotal = llIdle + llKernel + llUser;
            TCHAR szBuf[1024];

            sprintf(szBuf,
                    "[%s] %5.1f%% user, %5.1f%% system, %5.1f%% idle",
                    wk,
                    ((LONGLONG) 1000 * llUser / llTotal) / 10.0,
                    ((LONGLONG) 1000 * llKernel / llTotal) / 10.0,
                    ((LONGLONG) 1000 * llIdle / llTotal) / 10.0);
            printf("\r%s", szBuf);
            fflush(stdout);

            SetConsoleTitle(szBuf);
        }
        ftOldIdle = ftIdle;
        ftOldKernel = ftKernel;
        ftOldUser = ftUser;

        Sleep(iSleep);
        if (50 < iSleep) {
            iSleep -= 1;
        }
    }
}

int
main(int argc, char *argv[])
{
    SYSTEM_INFO si;
    int i;

    GetSystemInfo(&si);

    printf("$Id: main.c 1313 2013-03-19 00:10:02Z tfuruka1 $\n");
    printf("CPU使用率100%% %s[Build:" __DATE__ " " __TIME__ "]\n", VERSION);
    printf(LINE_STR "\n");
    printf("OEM-ID                     : %lx\n", si.dwOemId);
    printf("Processor architecture     : %s\n",
           GetProcessorArchitectureStr(si.wProcessorArchitecture));
    printf("Page size                  : %ld\n", si.dwPageSize);
    printf("Minimun application address: %lx\n",
           (ULONG) si.lpMinimumApplicationAddress);
    printf("Maximum application address: %lx\n",
           (ULONG) si.lpMaximumApplicationAddress);
    printf("Active processor mask      : 0123456789*123456789*123456789*1\n");
    printf("                           : %s\n",
           GetActiveProcessorMaskStr(si.dwActiveProcessorMask));
    printf("Number of processors       : %ld\n", si.dwNumberOfProcessors);
    printf("Processor type             : %s\n",
           GetProcessorTypeStr(si.dwProcessorType));
    printf("Allocation granularity     : %ld\n", si.dwAllocationGranularity);
    printf("Processor level            : %d\n", si.wProcessorLevel);
    printf("Processor revision         : %x.%x\n",
           (si.wProcessorRevision >> 8) & 0xff,
           si.wProcessorRevision & 0xff);
    printf(LINE_STR "\n");

    for (i = 0; i < si.dwNumberOfProcessors; i++) {
        DWORD dwThreadId;
        HANDLE hThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID) &i, 0,
                                      &dwThreadId);
        // ハンドルは使用しないのでクローズ
        CloseHandle(hThread);
        Sleep(1000);
    }
    selfLoop();

    return 0;
}

/*
 * Local Variables:
 * mode: c
 * coding: utf-8
 * End:
 */
