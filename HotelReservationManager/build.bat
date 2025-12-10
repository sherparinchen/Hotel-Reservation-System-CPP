@echo off
setlocal enabledelayedexpansion

set FILES=
for %%f in (src\*.cpp) do set FILES=!FILES! %%f

g++ !FILES! -o DEU_Hotel_Reservation.exe
