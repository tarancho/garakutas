@REM -*- coding: shift_jisx0213-dos; -*-
@echo off
echo $Id: batkey-sample.cmd,v 1.1 2006/11/15 12:08:03 tfuruka1 Exp $
echo $Name:  $
echo batkey���g�p�����T���v���ł��B

REM ---012345
batkey YyNnSs �������p�����ċX�����ł���([Y]es/[N]o/[S]kip)
IF ERRORLEVEL 6 GOTO ERROR
IF ERRORLEVEL 5 GOTO KEY-SKIP
IF ERRORLEVEL 4 GOTO KEY-SKIP
IF ERRORLEVEL 3 GOTO KEY-NO
IF ERRORLEVEL 2 GOTO KEY-NO

echo y ���I������܂����B
GOTO EXIT-CMD

:KEY-NO
    echo n ���I������܂����B
    GOTO EXIT-CMD
:KEY-SKIP
    echo s ���I������܂����B
    GOTO EXIT-CMD
:ERROR
    echo batkey�ŃG���[���������܂����B
    GOTO EXIT-CMD

:EXIT-CMD
    echo �����L�[���������ĉ������B
    pause > nul
    GOTO :EOF
