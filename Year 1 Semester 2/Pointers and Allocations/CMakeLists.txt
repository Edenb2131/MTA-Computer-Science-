cmake_minimum_required(VERSION 3.20)
project(Y1S2project2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Y1S2project2 main.c project2-Q1A.c project2-Q1B.c project2-Q2.c meow.c project2-Q3.c)

add_executable(project2-Q1A project2-Q1A.c)
add_executable(project2-Q1B project2-Q1B.c)
add_executable(project2-Q2 project2-Q2.c)
add_executable(meow meow.c cmake-build-debug/meoweden.c)
add_executable(meoweden cmake-build-debug/meoweden.c)
add_executable(project2-Q3 project2-Q3.c)