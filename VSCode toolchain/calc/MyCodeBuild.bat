@echo off
call "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\vcvarsall.bat" x86     
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:Calculator.exe
cl.exe %compilerflags% Calculator.cpp /link %linkerflags%