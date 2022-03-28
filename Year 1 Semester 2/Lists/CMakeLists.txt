cmake_minimum_required(VERSION 3.20)
project(Y1S2Project3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Y1S2Project3 main.c Q1.c Q2a.c Q2b.c Q2c.c Q2d.c Q3a.c Q3c.c Q3d.c Q3e.c)

add_executable(Q1 Q1.c cmake-build-debug/Q3b.c)
add_executable(Q2a Q2a.c)
add_executable(Q2b Q2b.c)
add_executable(Q2c Q2c.c)
add_executable(Q2d Q2d.c)
add_executable(Q3a Q3a.c)
add_executable(Q3b cmake-build-debug/Q3b.c)
add_executable(Q3c Q3c.c)
add_executable(Q3e Q3e.c)