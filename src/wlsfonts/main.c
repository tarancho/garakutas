/* -*- mode: c; coding: utf-8 -*-
 * Copyright (C) 2002, 2003, 2006 Tadamegu Furukawa
 * $Id: main.c,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
 * $Name:  $
 *
 * フォントを表示するだけです。
 *
 *  必要なライブラリ: gdi32
 *
 *  cl /W3 lsfont.c /link gdi32.lib
 *
 * $Log: main.c,v $
 * Revision 1.1  2006/11/15 12:08:04  tfuruka1
 * 新規追加
 *
 */
#include <windows.h>
#include <stdio.h>

static BOOL bLongFormat = FALSE;

/*
 * 文字セット名称の取得。
 */
static const char *
getCharSetString(
    BYTE lfCharSet                              /* 文字セットコード */
    )
{
    static struct charset {
        BYTE lfCharSet;
        const char *lpszCharSet;
    } tbl[] = {
        {ANSI_CHARSET, "ANSI"},
        {BALTIC_CHARSET, "BALTIC"},
        {CHINESEBIG5_CHARSET, "CHINESEBIG5"},
        {DEFAULT_CHARSET, "DEFAULT"},
        {EASTEUROPE_CHARSET, "EASTEUROPE"},
        {GB2312_CHARSET, "GB2312"},
        {GREEK_CHARSET, "GREEK"},
        {HANGUL_CHARSET, "HANGUL"},
        {MAC_CHARSET, "MAC"},
        {OEM_CHARSET, "OEM"},
        {RUSSIAN_CHARSET, "RUSSIAN"},
        {SHIFTJIS_CHARSET, "SHIFTJIS"},
        {SYMBOL_CHARSET, "SYMBOL"},
        {TURKISH_CHARSET, "TURKISH"},
        {VIETNAMESE_CHARSET, "VIETNAMESE"},
        {JOHAB_CHARSET, "JOHAB"},
        {ARABIC_CHARSET, "ARABIC"},
        {HEBREW_CHARSET, "HEBREW"},
        {THAI_CHARSET, "THAI"}
    };
    static const char *lpszUnknown = "不明";

    for (size_t i = 0; i < sizeof(tbl) / sizeof(struct charset); i++) {
        if (lfCharSet == tbl[i].lfCharSet) {
            return tbl[i].lpszCharSet;
        }
    }
    return lpszUnknown;
}

int CALLBACK
EnumFontFamProc(
    ENUMLOGFONT FAR *lpelf,             // pointer to logical-font data
    NEWTEXTMETRIC FAR *lpntm,           // pointer to physical-font data
    int FontType,                       // type of font
    LPARAM lParam                       // address of application-defined data
    )
{
    LPLOGFONT lpLf;
    if (!lpelf) {
        return 0;
    }

    (void) lpntm;
    (void) lParam;

    printf("%s, ", lpelf->elfFullName);
    printf("%s, ", lpelf->elfStyle);

    // -- FontType
    printf("%x - ", FontType);
    printf("%s", (FontType & DEVICE_FONTTYPE) ? "Device " : "");
    printf("%s", (FontType & RASTER_FONTTYPE) ? "Raster " : "");
    printf("%s", (FontType & TRUETYPE_FONTTYPE) ? "TrueType" : "");
    if (bLongFormat) {
        lpLf = &lpelf->elfLogFont;

        printf(", %d, ", (int) lpLf->lfHeight);
        printf("%d, ", (int) lpLf->lfWidth);
        printf("%d, ", (int) lpLf->lfEscapement);
        printf("%d, ", (int) lpLf->lfOrientation);
        printf("%d, ", (int) lpLf->lfWeight);
        printf("%s, ", lpLf->lfItalic ? "true" : "false");
        printf("%s, ", lpLf->lfUnderline ? "true" : "false");
        printf("%s, ", lpLf->lfStrikeOut ? "true" : "false");
        //-- 文字セット
        printf("%02x - ", lpLf->lfCharSet);
        printf("%s, ", getCharSetString(lpLf->lfCharSet));
        //--
        printf("%x, ", lpLf->lfOutPrecision);
        printf("%x, ", lpLf->lfClipPrecision);
        printf("%x, ", lpLf->lfQuality);
        printf("%x, ", lpLf->lfPitchAndFamily);
        printf("%s", lpLf->lfFaceName);
    }

    printf("\n");
    return 1;
}

int
main(int argc, char *argv[])
{
    int i;
    HDC hDC = CreateDC("DISPLAY", NULL, NULL, NULL);

    for (i = 1; i < argc; i++) {
        if ('-' != *argv[i]) {
            break;
        }
        switch (*(argv[i] + 1)) {
        case 'l':
            bLongFormat = TRUE;
            break;
        default:
            fprintf(stderr, "Usage: wlsfonts [-l] [font fam name...]\n");
            break;
        }
    }
    printf("フォント名, スタイル, 種類");
    if (bLongFormat) {
        printf(", 高さ, 幅, 行角度, ベースライン角度, 太さ, "
               "斜体, 下線, 打消, 文字セット, 出力精度, クリッピング精度, "
               "出力品質, ピッチとファミリ, 書体名");
    }
    printf("\n");
    EnumFontFamilies(hDC, argv[i] ? argv[i] : NULL,
                     (FONTENUMPROC)EnumFontFamProc, 0);
    DeleteDC(hDC);
}
