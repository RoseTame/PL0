cmake_minimum_required(VERSION 3.28)
project(PL0 C)

set(CMAKE_C_STANDARD 99)

add_executable(PL0 main.c
        pl0.h source.txt
)
