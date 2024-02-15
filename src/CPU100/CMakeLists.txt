cmake_minimum_required(VERSION 3.13)

project(cpu100 C)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

add_compile_options(-g -Wall -W -Wformat=2 -Wcast-qual)
add_compile_options(-Wcast-align -Wwrite-strings)
add_compile_options(-Wconversion -Wfloat-equal)
add_compile_options(-Wpointer-arith)
add_compile_options(--input-charset=utf-8)
add_compile_options(--exec-charset=cp932)

add_executable(cpu100.exe main.c)
install(TARGETS cpu100.exe DESTINATION bin)
