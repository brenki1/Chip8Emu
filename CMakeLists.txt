cmake_minimum_required(VERSION 3.27)
project(uai C)

set(CMAKE_C_STANDARD 23)

add_executable(uai main.c
        cpu.c
        processing.c
        processing.h)

target_link_libraries(uai "-lraylib -lGL -lm -lpthread -ldl -lrt -lX11")
