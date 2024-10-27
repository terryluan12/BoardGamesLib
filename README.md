# BoardGamesLib

This project was made after realizing that there were no publicly available board game libraries repos.
The intention of this library is to provide plug and play versions of various popular board games all within one repo!
Each library will publicly expose a Game class, a ConfigureBuilder class and a number of game specific enums and exceptions.
From there, if you want to use it for your backend or front end, you can use it directly or compile it to a .dll through CMake.


# Currently available Libraries
- [Dogan (Catan Clone)](dogan)

## Getting started

### Creating the .dll
Prerequisites: CMake
If you need a .dll to link, you only need to do the following:
 - Clone this library through your VCS of choice
 - Navigate to the root of this project 
 - Run the following code
   - `mkdir build`
   - `cd build`
   - `cmake ..`
   - `make`
 - The .dll library will now be found under `build/{BoardGameName}`

### C/C++
You can use any library in C, C++ by directly linking the .dll library to your app

### Python
You can use this library in Python by using SWIG. The library currently generates a python package under `build/languages/python`
