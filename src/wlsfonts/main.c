/* -*- mode: c; coding: sjis -*-
 * Time-stamp: <2006-11-15 20:24:45 tfuruka1>
 * Copyright (C) 2002, 2003, 2006 Tadamegu Furukawa
 * $Id: main.c,v 1.1 2006/11/15 12:08:04 tfuruka1 Exp $
 * $Name:  $
 *
 * �t�H���g��\�����邾���ł��B
 *
 *  �K�v�ȃ��C�u����: gdi32
 * 
 *  cl /W3 lsfont.c /link gdi32.lib
 *
 * $Log: main.c,v $
 * Revision 1.1  2006/11/15 12:08:04  tfuruka1
 * �V�K�ǉ�
 *
 */
#include <windows.h>
#include <stdio.h>

static BOOL bLongFormat = FALSE;

int CALLBACK EnumFontFamProc(
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

    printf("%s, ", lpelf->elfFullName);
    printf("%s, ", lpelf->elfStyle);

    // -- FontType
    printf("%x - ", FontType);
    printf("%s", (FontType & DEVICE_FONTTYPE) ? "DDevice " : "");
    printf("%s", (FontType & RASTER_FONTTYPE) ? "Raster " : "");
    printf("%s", (FontType & TRUETYPE_FONTTYPE) ? "TrueType" : "");
    if (bLongFormat) {
        lpLf = &lpelf->elfLogFont;

        printf(", %d, ", lpLf->lfHeight);
        printf("%d, ", lpLf->lfWidth);
        printf("%d, ", lpLf->lfEscapement);
        printf("%d, ", lpLf->lfOrientation);
        printf("%d, ", lpLf->lfWeight);
        printf("%s, ", lpLf->lfItalic ? "true" : "false");
        printf("%s, ", lpLf->lfUnderline ? "true" : "false");
        printf("%s, ", lpLf->lfStrikeOut ? "true" : "false");
        //-- �����Z�b�g
        printf("%x - ", lpLf->lfCharSet);
        printf("%s, ", ANSI_CHARSET == lpLf->lfCharSet ? "ANSI" :
               (OEM_CHARSET == lpLf->lfCharSet ? "OEM" :
                (SYMBOL_CHARSET == lpLf->lfCharSet ? "SYMBOL" :
                 (DEFAULT_CHARSET == lpLf->lfCharSet ? "DEFAULT" :
                  (SHIFTJIS_CHARSET == lpLf->lfCharSet ? "SJIS" :
                   "�s��")))));
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

int main(int argc, char *argv[])
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
    printf("�t�H���g��, �X�^�C��, ���");
    if (bLongFormat) {
        printf(", ����, ��, �s�p�x, �x�[�X���C���p�x, ����, "
               "�Α�, ����, �ŏ�, �����Z�b�g, �o�͐��x, �N���b�s���O���x, "
               "�o�͕i��, �s�b�`�ƃt�@�~��, ���̖�");
    }
    printf("\n");
    EnumFontFamilies(hDC, argv[i] ? argv[i] : NULL,
                     (FONTENUMPROC)EnumFontFamProc, 0);
    DeleteDC(hDC);
}
