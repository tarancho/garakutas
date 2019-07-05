#include <windows.h>
#include <winsock.h>
#include <stdio.h>

#include "YdmAPI.h"

#include "resource.h"

#define MY_NAME "����i���G�~�����[�^"

static HINSTANCE g_hInstance = NULL;
static HWND g_hwndModule;
static char g_szModuleClassName[] = MY_NAME "YdmDll";
static ULONG g_uRagTime = 0;

static void
Syslog(char *lpszMsg)
{
    WSADATA wsaData;
    SOCKET finet;
    PSERVENT sp;
    SOCKADDR_IN sin;
    LPHOSTENT lpHost;

    printf("WinSock�������J�n...");
    fflush(stdout);

    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        printf("���������s\n");
		return;
	}
    printf("����\n");
    printf("%s %s\n", wsaData.szDescription, wsaData.szSystemStatus);

    printf("SOCKET�쐬..."); fflush(stdout);
    if (0 > (finet = socket(AF_INET, SOCK_DGRAM, 0))) {
        printf("���s\n");
        return;
    }
    printf("����\n");

    lpHost = gethostbyname("localhost");

    printf("syslog service������..."); fflush(stdout);
    if (NULL == (sp = getservbyname("syslog", "udp"))) {
        printf("������܂���\n");
        return;
    }
    printf("�|�[�g�ԍ�%d\n", sp->s_port);

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(sp->s_port);
    sin.sin_addr = *((LPIN_ADDR)*lpHost->h_addr_list);

    sendto(finet, lpszMsg, strlen(lpszMsg), 0,
           (PSOCKADDR)&sin, sizeof(SOCKADDR));
}

BOOL WINAPI
DllMain(HINSTANCE hInstIn, DWORD fdwReason, LPVOID lpvReserved)
{
	if(fdwReason != DLL_PROCESS_ATTACH) {
		return TRUE;
	}
	g_hInstance = hInstIn;
	return TRUE;
}

HWND GetWindowHandle() {
	return g_hwndModule;
}

/* �N���C�A���g����̃��N�G�X�g�������� */
static BOOL
Requested(HTRANS hTrans) {
    /* ���N�G�X�g���������ꂽ�ꍇ�̂݃X���[�v */
    if (!YdmIsReqBuilded(hTrans)) {
        Syslog("���N�G�X�g�p�P�b�g�������o");
        if (0 < g_uRagTime) {
            char szBuf[1028];
            wsprintf(szBuf, "%lums wait...", g_uRagTime);
            Syslog(szBuf);
            Sleep(g_uRagTime);
        }
    } else {
        Syslog("���N�G�X�g�p�P�b�g�͕�������Ă��܂���");
    }
	return FALSE;
}

static BOOL
Responded(HTRANS hTrans)
{
	return FALSE;
}

static void
GetModuleTitle(char* pszGet, UINT cbGet) {
	static char szModuleTitle[] = MY_NAME;
	if(sizeof(szModuleTitle) >= cbGet) {
        return;
    }
	lstrcpy(pszGet, szModuleTitle);
}

static long
GetModuleVersion()
{
	return MAKELONG(0, 1);
}

static BOOL CALLBACK
SetupDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    char szBuf[1024];

	switch(message) {
    case WM_INITDIALOG:
        wsprintf(szBuf, "%lu", g_uRagTime);
        SetDlgItemText(hwnd, IDE_RAGTIME, szBuf);
        return TRUE;
    case WM_COMMAND:
        if(LOWORD(wParam) == IDOK) {
            BOOL b;
            ULONG l = GetDlgItemInt(hwnd, IDE_RAGTIME, &b, FALSE);
            if (b) {
                g_uRagTime = l;
            }
            wsprintf(szBuf, "���O�^�C�� %lu", g_uRagTime);
            Syslog(szBuf);
            EndDialog(hwnd, IDOK);
        } else if(LOWORD(wParam) == IDCANCEL) {
            EndDialog(hwnd, IDCANCEL);
        }
	}
	return FALSE;
}

static void PropertyDialog(HWND hwnd)
{
	DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_MAIN), g_hwndModule,
              (DLGPROC) SetupDlgProc);
}

static void
EnumMenu(int i, char* pszGet, UINT cbGet) {
	char* psz = NULL;
	if(i == 0) {
		psz = MY_NAME;
	} else {
		return;
	}
	if(lstrlen(psz) >= (int)cbGet) {
        return;
    }
	lstrcpy(pszGet, psz);
	return;
}

void MenuSelected(long i) {
	if(i == 0) {
		DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_MAIN), g_hwndModule,
                  (DLGPROC)SetupDlgProc);
	}
}

static void
Closed(HTRANS hTrans)
{
}

void RequestPassed( HTRANS hTrans ) {
}

static LRESULT CALLBACK
WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message) {
		case WM_CREATE:
			g_hwndModule = hwnd;
			break;
	}
	
	return DefWindowProc(hwnd, message, wParam, lParam);
}

/* �����\�t�g�̏��������ɌĂяo����܂� */
DWORD
YdmInit(HWND hwndYdm)
{
	WNDCLASS wc;

	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szModuleClassName;
	if(!RegisterClass(&wc)) {
		return 0;
	}

	CreateWindowEx(WS_EX_TOOLWINDOW, g_szModuleClassName,
                   g_szModuleClassName,
                   WS_CHILD, 0, 0, 0, 0, hwndYdm, NULL, g_hInstance, NULL);
	return 0;
}

/* ����胂�W���[���̏I�����ɌĂяo����܂��B�K�v�ɉ����āA�������g��
 * �ݒ�֌W�̕ۑ��A�E�B���h�E�̔j���Ȃǂ����Ă��������B
 */
DWORD
YdmRelease(HWND hwndYdm)
{
	return 0;
}

/* ���N�G�X�g�C���X�|���X�Ȃǂ��������Ƃ��ɌĂяo�����֐��ł��B���b
 * �Z�[�W�ɂ���ĈӖ����قȂ�܂��B
 */
DWORD
YdmProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
    case YDM_GETWINDOWHANDLE:
        return (DWORD)GetWindowHandle();
    case YDM_REQUESTED:
        return (DWORD)Requested((HTRANS)wParam);
    case YDM_REQUESTPASSED:
        RequestPassed( (HTRANS)wParam );
        return 0;
    case YDM_RESPONDED:
        return (DWORD)Responded( (HTRANS)wParam );
    case YDM_CLOSED:
        Closed((HTRANS)wParam);
        return 0;
    case YDM_GETMODULETITLE:
        GetModuleTitle((char*)lParam, (UINT)wParam );
        return 0;
    case YDM_GETMODULEVERSION:
        return GetModuleVersion();
    case YDM_PROPERTYDIALOG:
        PropertyDialog((HWND)wParam);
        return 0;
    case YDM_ENUMMENU:
        EnumMenu((int)HIWORD(wParam), (char*)lParam, (UINT)LOWORD(wParam));
        return 0;
    case YDM_MENUSELECTED:
        MenuSelected((int)wParam);
        return 0;
	}
	return 0;
}

