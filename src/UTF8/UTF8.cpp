/* -*- mode: c++; coding: sjis; -*-
 * Copyright (C) 2007 Tadamegu Furukawa
 * $Id: UTF8.cpp,v 1.1 2009/12/30 09:12:18 tfuruka1 Exp $
 * $Name:  $
 *
 * UTF-8関連のクラス
 *
 * $Log: UTF8.cpp,v $
 * Revision 1.1  2009/12/30 09:12:18  tfuruka1
 * 新規追加
 *
 */

#include "UTF8.H"

#define _U 0x80
static struct {
    ULONG begin;                                // 開始コード(UCS)
    ULONG end;                                  // 終了コード(UCS)
    long numOfByte;                             // バイト数(UTF)
    long u;                                     // 最初のコード(UTF)
    long bitMsk;                                // 最初のビットマスク(UTF)
} signTbl[] = {
    {0, 0x7f, 1, 0, 0x7f},
    {0x80, 0x7ff, 2, 0xc0, 0x1f},
    {0x800, 0xffff, 3, 0xe0, 0xf},
    {0x10000, 0x10ffff, 4, 0xf0, 7},
    {-1, -1, -1, -1, -1},                       // ストッパ
};

UCS_GAIJI (*UTF8::m_gaijiTbl)[] = NULL;

UTF8::UTF8(void)
{
}
UTF8::~UTF8(void)
{
}

void
UTF8::setGaijiTbl(UCS_GAIJI (*lpGaiji)[])
{
    m_gaijiTbl = lpGaiji;
}

ULONG
UTF8::getSJISGaiji(ULONG ucs)
{
    //外字が設定されていない場合
    if (!m_gaijiTbl) {
        return 0;
    }
    for (int i = 0; (*m_gaijiTbl)[i].ucs; i++) {
        if ((*m_gaijiTbl)[i].ucs == ucs) {
            return (*m_gaijiTbl)[i].sjis;
        }
    }
    return 0;
}

LPTSTR
UTF8::toUTF8(ULONG ucs, LPTSTR lpszBuf)
{
    int idx;
    int i;

    for (i = 0; signTbl[i].begin != -1; i++) {
        if ((signTbl[i].begin <= ucs) && (signTbl[i].end >= ucs)) {
            break;
        }
    }
    if (-1 == signTbl[i].begin) {
        *lpszBuf = '\0';
        return NULL;
    }
    idx = i;
    for (i = signTbl[idx].numOfByte - 1; i >= 0; i--) {
        int shift = (signTbl[idx].numOfByte - 1 - i) * 6;
        if (i) {
            *(lpszBuf + i) = (char) (_U + ((ucs >> shift) & 0x3f));
        } else {
            *(lpszBuf) = (char) (signTbl[idx].u
                                 + ((ucs >> shift) & signTbl[idx].bitMsk));
        }
    }
    *(lpszBuf + signTbl[idx].numOfByte) = '\0';
    return lpszBuf;
}

ULONG
UTF8::toUCS2(LPTSTR lpszUTF8, int *lpcb)
{
    int i;
    int idx;
    ULONG ucs = 0;

    for (i = 0; signTbl[i].begin != -1; i++) {
        BYTE u = (BYTE) ((lpszUTF8[0] & ~signTbl[i].bitMsk));
        if (u == (BYTE) (signTbl[i].u)) {
            break;
        }
    }
    if (-1 == signTbl[i].begin) {
        return -1L;
    }
    idx = i;

    // UFT-8のバイト数が想定より短かい場合はエラーとする
    if ((size_t) signTbl[idx].numOfByte > strlen(lpszUTF8)) {
        return -1L;
    }
    // UTF-8の一文字のバイト数を設定
    *lpcb = signTbl[idx].numOfByte;

    for (i = signTbl[idx].numOfByte - 1; i >= 0; i--) {
        BYTE u;
        BYTE v;
        int shift;

        shift = (signTbl[idx].numOfByte - 1 - i) * 6;
        if (i) {
            u = lpszUTF8[i] & 0xc0;
            if (u != _U) {
                // 符号が一致しない場合はエラーとする
                return -1L;
            }
            v = lpszUTF8[i] & 0x3f;
        } else {
            u = (BYTE) (lpszUTF8[i] & ~signTbl[idx].bitMsk);
            if (u != signTbl[idx].u) {
                // 符号が一致しない場合はエラーとする
                return -1L;
            }
            v = (BYTE) (lpszUTF8[i] & signTbl[idx].bitMsk);
        }
        ucs += ((ULONG)v << shift);
    }
    return ucs;
}

LPTSTR
UTF8::toSJIS(LPTSTR lpszUTF8, LPTSTR lpszSJIS, int *lpcbUTF)
{
    ULONG ucs;
    ULONG sjis;
    int len;
    USHORT wide[4];

    // UCS2に変換
    ucs = UTF8::toUCS2(lpszUTF8, lpcbUTF);

    // 変換エラーの場合は終了
    if (-1L == ucs) {
        *lpszSJIS = '\0';
        return lpszSJIS;
    }

    // 1バイト文字(US-ASCII)の場合は変換する必要なし
    if (1 == *lpcbUTF) {
        *lpszSJIS = (BYTE) ucs;
        *(lpszSJIS + 1) = '\0';
        return lpszSJIS;
    }

    // 外字登録されている場合
    if ((sjis = UTF8::getSJISGaiji(ucs))) {
        *lpszSJIS = (char) ((sjis >> 8) & 0xff);
        *(lpszSJIS + 1) = (char) (sjis & 0xff);
        *(lpszSJIS + 2) = '\0';
        return lpszSJIS;
    }

    // UTFからUnicodeへ変換
    len = MultiByteToWideChar(CP_UTF8, 0, lpszUTF8, *lpcbUTF, wide, 4);
    if (!len) {
        *lpszSJIS = '\0';
        return lpszSJIS;
    }
    // UnicodeからSJISへ変換
    len = WideCharToMultiByte(CP_ACP, 0, wide, len, lpszSJIS, 4, 0, 0);
    if (!len) {
        * lpszSJIS = '\0';
        return lpszSJIS;
    }
    *(lpszSJIS + len) = '\0';
    return lpszSJIS;
}

static void
simpleDump(LPBYTE lpBuf)
{
    for (int i = 0; i < (int) strlen((LPTSTR) lpBuf); i++) {
        printf(" %02x", *(lpBuf + i));
    }
}

static void
ucs2ToUTF8Test()
{
    static struct {
        LPTSTR szTitle;
        ULONG ucs;
        ULONG expected;
    } obj[] = {
        {"漢字(弌)", 0x5F0C, 0xE5BC8C},
        {"コード範囲外", 0x110000, 0},
        {"ASCII(A)", 'A', 'A'},
        {"Laten-extended(A~)外字変換含む", 0x100, 0xc480},
        {"半角カナ(ア)", 0xff71, 0xefbd1},
        {"BOM", 0xfeff, '?'},
        {"木の切株", 0x233b4, '?'},
        {NULL, 0, 0}
    };
    UCS_GAIJI gaiji[] = {{0x100, 'Å'}, {0, 0}};
    UCS_GAIJI (*pGaiji)[] = (UCS_GAIJI (*)[]) &gaiji;
    int cb;

    printf("UCS2→UFT-8→SJIS 変換テスト\n");
    UTF8::setGaijiTbl(pGaiji);
    for (int i = 0; obj[i].szTitle; i++) {
        char buf[8];
        char sjis[4];
        printf("\t%2d: %s\n"
               "\t    変換元コード: %x, 期待値: %x\n",
               i + 1, obj[i].szTitle,
               obj[i].ucs, obj[i].expected);
        UTF8::toUTF8(obj[i].ucs, buf);
        printf("\t    結果:");
        simpleDump((LPBYTE) buf);
        printf("\n\t    逆変換結果: %x", UTF8::toUCS2(buf, &cb));
        printf("\n\t    SJIS変換結果: %s\n", UTF8::toSJIS(buf, sjis, &cb));
    }
}

int
main(int argc, char *argv[])
{
    ucs2ToUTF8Test();
    return 0;
}
