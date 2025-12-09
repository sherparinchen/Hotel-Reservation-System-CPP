@echo off
if not exist src (
  echo Source folder missing.
  pause
  exit /b 1
)
g++ -std=c++17 src/*.cpp -o HotelReservation.exe
if errorlevel 1 (
  echo Build failed.
  pause
) else (
  echo Build succeeded. Run HotelReservation.exe
)
