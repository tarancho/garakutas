cmake_minimum_required(VERSION 3.13)

project(dedup C)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

set(EXE_FILE ${PROJECT_NAME}.exe)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -W -Wformat=2 -Wcast-qual")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wwrite-strings")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion -Wfloat-equal")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpointer-arith")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --exec-charset=cp932")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --input-charset=utf-8")

add_executable(${EXE_FILE} main.c)
install(TARGETS ${EXE_FILE} DESTINATION bin)
