cmake_minimum_required (VERSION 3.10)

project(garakuta C)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/..")

add_subdirectory(batkey)
add_subdirectory(CPU100)
add_subdirectory(crlf)
add_subdirectory(dedup)
add_subdirectory(ExSleep)
add_subdirectory(img2java)
add_subdirectory(lha32)
add_subdirectory(MegaFile)
add_subdirectory(TVMaker)
add_subdirectory(pi)
add_subdirectory(tee)
add_subdirectory(wlsfonts)
add_subdirectory(weekNumber)
