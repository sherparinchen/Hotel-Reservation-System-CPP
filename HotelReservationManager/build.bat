@echo off
setlocal enabledelayedexpansion

set FILES=
for %%f in (src\*.cpp) do set FILES=!FILES! %%f

g++ !FILES! -o program.exe
