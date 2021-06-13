cmake_minimum_required(VERSION 3.19)
project(the_donut C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(the_donut
        main.c)
