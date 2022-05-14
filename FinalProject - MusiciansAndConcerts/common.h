#ifndef _COMMON_H
#define _COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISALLOWED_CHARS " ,.;:?!-\t'()[]{}<>~_"
#define SIZE_OF_HOUR_STRING 5
#define EMPTY_STRING ""
#define SPACE_STRING " "
#define NUM_OF_MINUTES_IN_AN_HOUR 60
#define INPUT_FILE_MAX_LINE_LENGTH 150
#define INSTRUMENT_NOT_FOUND NULL
#define INSTRUMENT_NOT_FOUND_INT -1
#define LEFT 0
#define RIGHT 1
#define TRUE_AS_CHAR '1'
#define FALSE_AS_CHAR '0'

typedef struct {
  int day, month, year;
  float hour;
} Date;

typedef struct stringsNestedArray {
  char** arr;
  int logSize;
  int phySize;
} StringsNestedArray;

void checkMemoryAllocation(void* ptr);
bool isFileOpened(FILE* f);
void trimNewLineChar(char* str);
void freeStringsNestedArrayObjArray(StringsNestedArray* strArr[], int strArrSize);
void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType);
bool isStringsEqual(char* str1, char* str2);
bool isLexicographicallySmaller(char* str1, char* str2);
char* scanInputWithUnknownSize();
int getNumberOfDigits(int integer);
char* integerToString(int integer, int integerLength);
float convertStringHourToFloat(char* str);
char* convertFloatHourToString(float hour);
void printHourAsString(float hour);

#endif // _COMMON_H