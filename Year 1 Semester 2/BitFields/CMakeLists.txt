cmake_minimum_required(VERSION 3.20)
project(Y1S2project6 C)

set(CMAKE_C_STANDARD 99)

add_executable(Y1S2project6 main.c Q1main.c Q1functions.c Q1.h Q2main.c Q2functions.c Q2.h Q3main.c Q3functions.c Q3.h Q4main.c Q4functions.c Q4.h)

add_executable(Q1main Q1main.c
        Q1functions.c
        Q1.h)

add_executable(Q2main Q2main.c
        Q2functions.c
        Q2.h)
add_executable(Q3main Q3main.c
        Q3functions.c
        Q3.h)

add_executable(Q4main Q4main.c
        Q4functions.c
        Q4.h)