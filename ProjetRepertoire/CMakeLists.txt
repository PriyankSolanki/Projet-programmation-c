cmake_minimum_required(VERSION 3.29)
project(projetRepertoire C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(projetRepertoire
        src/main.c
        src/repertoire.c
        src/inputChecker.c
        include/repertoire.h
        include/inputChecker.h)
