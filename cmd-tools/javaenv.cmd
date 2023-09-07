@echo $Id: javaenv.cmd 1335 2017-02-03 02:34:23Z tfuruka1 $
@echo $URL: http://10.16.25.26/svn/spot-pj/misc/trunk/cmd-tools/javaenv.cmd $
@echo off
echo 複数のJavaの実行環境の切換えを行ないます。
echo Explorerの送るに登録しておくと便利です。
echo.

rem ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

rem 以下は各自自分の環境に合せて修正して下さい。
rem ダブルクォートで括る必要はありません。

SET JDK6=C:\pleiades\java\6
SET JDK7=C:\pleiades\java\7
SET JDK8=C:\pleiades\java\8
SET JDK10=C:\pleiades\java\10
SET MAVEN_HOME=C:\apache-maven-3.6.1

rem ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
rem 以降は基本的に修正の必要はありません。

SET CMD=%SYSTEMROOT%\System32\cmd

IF NOT %1=="" (
    call :CHG_DIRECTORY "%1"
    cd
)

:LOOP
echo.
echo ==========
echo 6. JDK 6 - %JDK6%
echo 7. JDK 7 - %JDK7%
echo 8. JDK 8 - %JDK8%
echo a. JDK 10 - %JDK10%
echo q. quit
echo ==========

SET /P INPUT=入力して下さい:
IF "%INPUT%"=="q" goto :EOF
IF "%INPUT%"=="Q" goto :EOF
IF "%INPUT%"=="6" (
    call :SETENV "%JDK6%"
    goto :END_LOOP
)
IF "%INPUT%"=="7" (
    call :SETENV "%JDK7%"
    goto :END_LOOP
)
IF "%INPUT%"=="8" (
    call :SETENV "%JDK8%"
    goto :END_LOOP
)
IF "%INPUT%"=="a" (
    call :SETENV "%JDK10%"
    goto :END_LOOP
)

echo 入力値が不正です。
goto :LOOP

:END_LOOP
SET JDK6=
SET JDK7=
SET JDK8=
SET JDK10=
SET INPUT=

%CMD% /k
GOTO :EOF

:SETENV
    SET ARG=%~1
    SET JAVA_HOME=%ARG%
    SET PATH="%ARG%\bin";"%MAVEN_HOME%\bin";%PATH%
    SET JAVA_HOME
    SET MAVEN_HOME
    java -version
    %CMD% /c mvn --version
    SET ARG=
    goto :EOF

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