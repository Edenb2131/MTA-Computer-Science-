//
// Created by Eden Bar on 26/05/2022.
//

#ifndef Y1S2PROJECT6_Q3_H
#define Y1S2PROJECT6_Q3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 100
#define MAX_STRING_SIZE 99

typedef unsigned char BYTE;

void* scramble(void* arr, int ElemSize, int n, int* indArr);
int* getIntArr(int* intSize);
int* scrambleInt(int* intArr, int intSize, int* indArr);
void printIntArr(int* intArr, int intSize);
char** getStringArr(int* stringArrSize);
char** scrambleString(char** stringArr, int stringArrSize, int* indArr);
void printStringArr(char** stringArr, int stringArrSize);
void freeMemory(int* intArr, int* scrambleIntArr, int intSize, char** stringArr, char** scrambleStringArr,int stringSize);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
void checkAllocation(void *ptr);

#endif //Y1S2PROJECT6_Q3_H
