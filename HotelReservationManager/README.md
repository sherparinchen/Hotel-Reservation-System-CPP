# Hotel Reservation Manager (C++ CLI)

Simple C++17 CLI hotel reservation manager for course project.

## Features
- OOP design with inheritance for Room types.
- Caesar cipher (shift 3) for stored passwords.
- Admin and user login.
  - Default user: `deu` / `deu123`
  - Default admin: `admin` / `admin123`
- Admin can reserve on behalf of any user; users can reserve only for themselves.
- File I/O: guests.txt and reservations.txt persist data.
- Date validation (YYYY-MM-DD) and overlapping reservation checks.
- Robust exception handling to avoid crashes on bad input.
- Menu-driven numeric commands.
- build.bat compiles using g++ (Windows).
- run_tests.bat runs a sample flow using prepared input.

## Build & Run (Windows)
1. Open a terminal and make sure `g++` is on PATH.
2. Run `build.bat` to compile.
3. Run `HotelReservation.exe` to start the program.
4. Optionally run `run_tests.bat` to run a scripted example.

## Project layout
- src/ : all `.cpp` and `.hpp` source files.
- data/ : generated runtime files (guests.txt, reservations.txt).
- build.bat : compile script (Windows).
- run_tests.bat : runs the program with sample input.

## Notes for graders / students
- Code is split into four contributor `.cpp` files (member1..member4) so each member can claim work.
- `using namespace std;` is present in `.cpp` files to reduce `std::` noise per request.
- If you push to GitHub, add an appropriate `.gitignore` (not provided here).

