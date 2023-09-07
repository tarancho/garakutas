@echo off
rem $Id$

rem コマンドプロンプトを開きます。Explorerの送るに登録しておく事を想定
rem しています。Windows 10 の場合の「送る」は以下にあります。
rem %USERPROFILE%\AppData\Roaming\Microsoft\Windows\SendTo

echo.

IF NOT "%1"=="" (
    call :CHG_DIRECTORY "%1"
    cd
)

rem cygwinのコマンドを使うので文字セットを設定しておく。文字コードは
rem UTF-8にします。SJISなファイルをcatする時とかは iconv を使うからいい
rem や。
SET LANG=ja_JP.UTF-8

cmd /k
goto :eof

:CHG_DIRECTORY
    cd /d "%1"
    if %errorlevel% EQU 0 (
        echo カレントディレクトリを切換えました:
        goto :eof
    )
    echo %1 は無効なディレクトリです。ファイルと仮定します。
    SET TGT= %~dp1
    cd /d "%TGT%"
    if %errorlevel% EQU 0 (
        echo カレントディレクトリを切換えました:
        goto :eof
    )
    echo %1 も %TGT% も有効なディレクトリではありません。
    goto :eof

rem Local Variables:
rem mode: cmd
rem coding: shift_jis-dos
rem End:
