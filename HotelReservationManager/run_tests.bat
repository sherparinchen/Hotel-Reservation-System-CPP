@echo off
echo Running automated example flow...
if not exist HotelReservation.exe (
  echo HotelReservation.exe not found. Run build.bat first.
  pause
  exit /b 1
)
:: sample input commands in tests/input.txt
type tests\input.txt | HotelReservation.exe
pause
