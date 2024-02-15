cmake_minimum_required(VERSION 3.13)

project(pi C)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

set(EXE_FILE ${PROJECT_NAME}.exe)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -W -Wformat=2 -Wcast-qual")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wwrite-strings")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion -Wfloat-equal")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpointer-arith")

message(${CMAKE_C_FLAGS})
add_executable(${EXE_FILE} main.c)
install(TARGETS ${EXE_FILE} DESTINATION bin)
