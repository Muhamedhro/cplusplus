# CMakeList.txt : CMake project for cplusplus, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("cplusplus")

# Add source to this project's executable.
add_executable (cplusplus "cplusplus.cpp"  "Timer/Timer.cpp" "Timer/Timer.h"  )

# TODO: Add tests and install targets if needed.
