cmake_minimum_required(VERSION 3.13)

project(lha32 C)

set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../work/UNLHA32)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../work/UNLHA32)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -W -Wformat=2 -Wcast-qual")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wwrite-strings")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wconversion -Wfloat-equal")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpointer-arith")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --exec-charset=cp932")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --input-charset=utf-8")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -l UNLHA32")

add_executable(lha32.exe main.c)
target_link_libraries(lha32.exe UNLHA32)
