//
// Created by Eden Bar on 26/05/2022.
//

#ifndef Y1S2PROJECT6_Q4_H
#define Y1S2PROJECT6_Q4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 100
#define MAX_STRING_SIZE 99

typedef unsigned char BYTE;

int stringBinSearch(char** strings, int size, char* str);
int binSearch(void* Arr, int Size, int ElemSize, void* Item, int (*compare)(void*, void*));

int intBinSearch(int* arr, int size, int intToFind);
int compareInt(void* num1, void* num2);
int compareString(void** s1, void** s2);
int* getIntArr(int* intSize);
void printIntArr(int* intArr, int intSize);
char** getStringArr(int* stringArrSize);
void freeMemory(int* intArr, int intSize, char** stringArr, int stringSize);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
void checkAllocation(void *ptr);

#endif //Y1S2PROJECT6_Q4_H
