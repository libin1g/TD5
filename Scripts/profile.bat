@echo Setting environment for using portable tools.

@rem ----
@cd /d %~d0

@rem
@rem Root of  portable tools files.
@rem
@set HOME=%~dp0
@set HOME=%HOME:~0,-1%
@set ToolEnvDir=%HOME%\bin

@rem PATH
@if exist "%ToolEnvDir%" set PATH=%ToolEnvDir%;%PATH%
@if exist "%ToolEnvDir%\vim" set PATH=%ToolEnvDir%\vim\vim81;%PATH%
@rem Fix fatal python error: initfsencoding: unable to load the file system codec
@rem add enviroment PYTHONHOME 
@rem set %PYTHONHOME% and %PYTHONHOME%\Scripts to PATH
@if exist "%ToolEnvDir%\Python\Python37-32" set PYTHONHOME=%ToolEnvDir%\Python\Python37-32
@if exist "%PYTHONHOME%" set PATH=%PYTHONHOME%;%PATH%
@if exist "%PYTHONHOME%" set PATH=%PYTHONHOME%\Scripts;%PATH%
@rem Add LLVM to PATH
@if exist "%ToolEnvDir%\LLVM" set CLANG_ROOT=%ToolEnvDir%\LLVM
@if exist "%CLANG_ROOT%" set PATH=%CLANG_ROOT%\bin;%PATH%
@if exist "%ToolEnvDir%\cmake-3.14.0-rc2-win32-x86" set PATH=%ToolEnvDir%\cmake-3.14.0-rc2-win32-x86\bin;%PATH%
@rem Add Putty to PATH
@if exist "%ToolEnvDir%\PuTTY" set PATH=%ToolEnvDir%\PuTTY;%PATH%
@if exist "%ToolEnvDir%\OpenSSH" set PATH=%ToolEnvDir%\OpenSSH;%PATH%
@if exist "%ToolEnvDir%\7z1604-extra" set PATH=%ToolEnvDir%\7z1604-extra;%PATH%
@if exist "%ToolEnvDir%\curl-7.37.0-win32" set PATH=%ToolEnvDir%\curl-7.37.0-win32;%PATH%
@if exist "%ToolEnvDir%\WinDbg" set PATH=%ToolEnvDir%\WinDbg;%PATH%
@if exist "%ToolEnvDir%\net-snmp" set PATH=%ToolEnvDir%\net-snmp\bin;%PATH%
