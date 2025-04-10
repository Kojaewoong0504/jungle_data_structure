cmake_minimum_required(VERSION 3.30)
project(c_programing C)

set(CMAKE_C_STANDARD 11)

add_library(c_programing STATIC library.c
        main.c)
