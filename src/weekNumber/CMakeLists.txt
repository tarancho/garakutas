cmake_minimum_required(VERSION 3.13)

project(weeknum C)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

add_compile_options(-g -Wall -W -Wformat -Wcast-qual)
add_compile_options(-Wcast-align -Wwrite-strings)
add_compile_options(-Wconversion -Wfloat-equal)
add_compile_options(-Wpointer-arith)
add_compile_options(--input-charset=utf-8)
add_compile_options(--exec-charset=cp932)

add_compile_options(-Wformat-security)

# 以下の警告オプションは最後に無効にする。書式を指定できるコマンドなの
# で、意図した警告となりますが、対象部分以外の警告は確認するべきです。

#add_compile_options(-Wformat-nonliteral)

add_executable(weeknum.exe main.c)
install(TARGETS weeknum.exe DESTINATION bin)
