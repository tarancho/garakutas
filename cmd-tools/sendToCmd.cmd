@echo off
rem $Id$

rem �R�}���h�v�����v�g���J���܂��BExplorer�̑���ɓo�^���Ă�������z��
rem ���Ă��܂��BWindows 10 �̏ꍇ�́u����v�͈ȉ��ɂ���܂��B
rem %USERPROFILE%\AppData\Roaming\Microsoft\Windows\SendTo

echo.

IF NOT "%1"=="" (
    call :CHG_DIRECTORY "%1"
    cd
)

rem cygwin�̃R�}���h���g���̂ŕ����Z�b�g��ݒ肵�Ă����B�����R�[�h��
rem UTF-8�ɂ��܂��BSJIS�ȃt�@�C����cat���鎞�Ƃ��� iconv ���g�����炢��
rem ��B
SET LANG=ja_JP.UTF-8

cmd /k
goto :eof

:CHG_DIRECTORY
    cd /d "%1"
    if %errorlevel% EQU 0 (
        echo �J�����g�f�B���N�g����؊����܂���:
        goto :eof
    )
    echo %1 �͖����ȃf�B���N�g���ł��B�t�@�C���Ɖ��肵�܂��B
    SET TGT= %~dp1
    cd /d "%TGT%"
    if %errorlevel% EQU 0 (
        echo �J�����g�f�B���N�g����؊����܂���:
        goto :eof
    )
    echo %1 �� %TGT% ���L���ȃf�B���N�g���ł͂���܂���B
    goto :eof

rem Local Variables:
rem mode: cmd
rem coding: shift_jis-dos
rem End:
