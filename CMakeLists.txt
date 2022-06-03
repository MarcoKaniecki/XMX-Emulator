cmake_minimum_required(VERSION 3.22)
project(XMX_Emulator C)

set(CMAKE_C_STANDARD 99)

add_executable(XMX_Emulator
        main.c loader.c emulator.h memory_dump.c bus.c fetch.c)
# psw.c