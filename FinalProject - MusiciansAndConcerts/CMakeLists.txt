cmake_minimum_required(VERSION 3.20)
project(FinalProject C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mta_music_schedule
        common.c
        common.h
        concert.c
        concert.h
        ciList.c
        ciList.h
        main.c
        musician.c
        musician.h
        mpiList.c
        mpiList.h
        tree.c
        tree.h)
