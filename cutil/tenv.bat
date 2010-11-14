cd .
echo off

rem #MinGW
set MAKEPATH=D:\Program Files\MinGW5.14\bin

rem #VC 2008
rem set MAKEPATH=D:\Microsoft Visual Studio 9.0\VC\bin

path %path%;%MAKEPATH%
echo make location : %MAKEPATH%
cmd