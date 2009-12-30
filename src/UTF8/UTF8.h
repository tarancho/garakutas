/* -*- mode: c++; coding: sjis; -*-
 * Copyright (C) 2007 Tadamegu Furukawa
 * $Id: UTF8.h,v 1.1 2009/12/30 09:12:18 tfuruka1 Exp $
 * $Name:  $
 *
 * UTF8�֘A�̃N���X
 *
 * $Log: UTF8.h,v $
 * Revision 1.1  2009/12/30 09:12:18  tfuruka1
 * �V�K�ǉ�
 *
 */
#ifndef _UTF8_H_
#define _UTF8_H_

#include <windows.h>
#include <stdio.h>

// �O���ϊ��e�[�u��
typedef struct {
    ULONG ucs;                                  // UCS�R�[�h(0=�X�g�b�p)
    ULONG sjis;                                 // SJIS�R�[�h
} UCS_GAIJI, *PUCS_GAIJI;

class UTF8 {
public:
    UTF8(void);
    ~UTF8(void);
    static LPTSTR toUTF8(ULONG ucs, LPTSTR lpszBuf);
    static ULONG toUCS2(LPTSTR lpszUTF8, int *lpcb);
    static LPTSTR toSJIS(LPTSTR lpszUTF8, LPTSTR lpszSJIS, int *lpcb);
    static void setGaijiTbl(UCS_GAIJI (*lpGaiji)[]);
private:
    static UCS_GAIJI (*m_gaijiTbl)[];
    static ULONG getSJISGaiji(ULONG ucs);
};

#endif
