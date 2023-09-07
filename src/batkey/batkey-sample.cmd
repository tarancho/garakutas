@REM -*- coding: shift_jisx0213-dos; -*-
@echo off
echo $Id: batkey-sample.cmd,v 1.1 2006/11/15 12:08:03 tfuruka1 Exp $
echo $Name:  $
echo batkeyを使用したサンプルです。

REM ---012345
batkey YyNnSs 処理を継続して宜しいですか([Y]es/[N]o/[S]kip)
IF ERRORLEVEL 6 GOTO ERROR
IF ERRORLEVEL 5 GOTO KEY-SKIP
IF ERRORLEVEL 4 GOTO KEY-SKIP
IF ERRORLEVEL 3 GOTO KEY-NO
IF ERRORLEVEL 2 GOTO KEY-NO

echo y が選択されました。
GOTO EXIT-CMD

:KEY-NO
    echo n が選択されました。
    GOTO EXIT-CMD
:KEY-SKIP
    echo s が選択されました。
    GOTO EXIT-CMD
:ERROR
    echo batkeyでエラーが発生しました。
    GOTO EXIT-CMD

:EXIT-CMD
    echo 何かキーを押下して下さい。
    pause > nul
    GOTO :EOF
