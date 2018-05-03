@echo off
rem -- Run Vim with vim-command --
rem Usage: vimc [nativestartoption] {file1 [file2 file3...] [/cmd:Command [/arg:a1 [/arg:a2 /arg:a3]]]} 
rem     example: vimc -d file1 file2  /cmd:Filetag /arg:a1 /arg:a2 

setlocal
set VIM_EXE_DIR=C:\Program Files\Vim\vim80
if exist "%VIM%\vim80\gvim.exe" set VIM_EXE_DIR=%VIM%\vim80
if exist "%VIMRUNTIME%\gvim.exe" set VIM_EXE_DIR=%VIMRUNTIME%

if exist "%VIM_EXE_DIR%\gvim.exe" goto havevim
echo "%VIM_EXE_DIR%\gvim.exe" not found
goto eof

:havevim
rem collect the arguments in VIMARGS, VIMCMD and VIMCMDARGS
set VIMARGS=
set VIMCMD=
set VIMCMDARGS=
set VIMCMDPREFIX=/cmd
set VIMCMDARGSPREFIX=/arg
set SEPERATOR=@
set VIMNOFORK=
set vimcmdargc=10
:loopstart
if .%1==. goto loopend
if NOT .%1==.--nofork goto noforklongarg
set VIMNOFORK=1
:noforklongarg
if NOT .%1==.-f goto noforkarg
set VIMNOFORK=1
:noforkarg
set arg=%1
set prefix=
set suffix=
:lp
if .%arg% == . goto lpend
if .%arg:~0,1% ==.%SEPERATOR% (
    set suffix=%arg:~1%
    goto lpend
)
set prefix=%prefix%%arg:~0,1%
set "arg=%arg:~1%"
goto lp
:lpend
set arg=%1
rem echo ==================================
rem echo    arg: %arg%
rem echo prefix: %prefix%
rem echo suffix: %suffix%
rem pause
rem echo ..................................
:: only one vim command is available, parameter has a prefix (VIMCMDPREFIX)
:: for example /cmd=Filetag
if .%prefix%==.%VIMCMDPREFIX%  (
    set VIMCMD=%suffix%
) else (
    :: the command arguments size <10, argumensts has a prefix (VIMCMDARGSPREFIX)
    :: for example /arg1=a1 /arg2=a2
    if .%prefix%==.%VIMCMDARGSPREFIX% ( 
        set VIMCMDARGS=%VIMCMDARGS% %suffix%
        set /a vimcmdargc-=1 
    ) else (
        set VIMARGS=%VIMARGS% %arg%
    )
)
:: vim command argc is limited
if NOT .%vimcmdargc%==.0 (
    shift
) else (
    echo Too many arguments error!!! Vim command arguments <10. 
    pause
    goto eof
)
goto loopstart
:loopend

::splicing a full VIMARGS
if NOT ."%VIMCMD%"==.""  goto vimcmdwithoutarg
set VIMARGS=%VIMARGS%
goto prestart
:vimcmdwithoutarg
if NOT ."%VIMCMDARGS%"==.""  goto vimcmdwitharg 
set VIMARGS=%VIMARGS% -c "%VIMCMD%" 
goto prestart
:vimcmdwitharg
set VIMARGS=%VIMARGS% -c "%VIMCMD% %VIMCMDARGS%"
goto prestart

:prestart
rem echo ==================================
rem echo command line arguments: %VIMARGS% 
rem pause
rem echo ..................................
if .%OS%==.Windows_NT goto ntaction

if .%VIMNOFORK%==.1 goto nofork
start "%VIM_EXE_DIR%\gvim.exe" %VIMARGS%
goto eof

:nofork
start /w "%VIM_EXE_DIR%\gvim.exe" %VIMARGS%
goto eof

:ntaction
rem for WinNT
if .%VIMNOFORK%==.1 goto noforknt
start "dummy" /b "%VIM_EXE_DIR%\gvim.exe" %VIMARGS%
goto eof

:noforknt
start "dummy" /b /wait "%VIM_EXE_DIR%\gvim.exe" %VIMARGS%

:eof
set VIMARGS=
set VIMCMD=
set VIMCMDARGS=
set VIMNOFORK=
