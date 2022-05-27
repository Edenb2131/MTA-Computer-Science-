//
// Created by Eden Bar on 26/05/2022.
//

#include "Q4.h"


int binSearch(void* Arr, int Size, int ElemSize, void* Item, int (*compare)(void*, void*)){
    int foundItem;
    bool found = false;
    int left = 0, right = Size -1, place;

    while(!found && left <= right){
        place = (right + left)/2 ;

        if(compare(((BYTE*)Arr + (place * ElemSize)), (BYTE*)Item) == 0)
            found = true;
        else if(compare(((BYTE*)Arr + (place * ElemSize)), (BYTE*)Item) < 0)
            left = place + 1;
        else
            right = place -1;
    }

    return found;
}

int intBinSearch(int* arr, int size, int intToFind){
    return binSearch(arr, size, sizeof(int), &intToFind, &compareInt);
}

int stringBinSearch(char** strings, int size, char* str){
    return binSearch(strings, size, sizeof(char*), &str, &compareString);
}

int compareInt(void* num1, void* num2){
    int a = *(int*)num1;
    int b = *(int*)num2;

    return (a-b);
}

int compareString(void** s1, void** s2){

    char* a = *(char**)s1;
    char* b = *(char**)s2;

    return strcmp(a,b);
}

int* getIntArr(int* intSize) {
    int arrLogSize = 0;
    int arrPhySize = 1;
    int* intArr = (int*)malloc(arrPhySize * sizeof(int));

    scanf("%d ", intSize);

    for (int i = 0; i < *intSize; i++) {
        intArr = increaseArraySizeIfFull(intArr, &arrLogSize, &arrPhySize, sizeof(int));
        scanf("%d", &intArr[arrLogSize]);
        arrLogSize++;
    }

    intArr = (int*)realloc(intArr, arrLogSize * sizeof(int));
    return intArr;
}

char** getStringArr(int* stringArrSize) {
    int arrLogSize = 0;
    int arrPhySize = 1;
    char** stringArr = (char**)malloc(arrPhySize * sizeof(char*));

    scanf("%d ", stringArrSize);

    for (int i = 0; i < *stringArrSize; i++) {
        stringArr = increaseArraySizeIfFull(stringArr, &arrLogSize, &arrPhySize, sizeof(char*));

        stringArr[arrLogSize] = (char*)malloc(MAX_STRING_SIZE * sizeof(char));
        checkAllocation(stringArr[arrLogSize]);

        gets(stringArr[arrLogSize]);

        arrLogSize++;
    }

    stringArr = (char**)realloc(stringArr, arrLogSize * sizeof(char*));
    return stringArr;
}

void printIntArr(int* intArr, int intSize) {
    int i;

    for (i = 0; i < intSize; i++) {
        printf("%d ", intArr[i]);
    }
    printf("\n");
}

void freeMemory(int* intArr, int intSize, char** stringArr,int stringSize) {
    int i;
    free(intArr);
    for (i = 0; i < stringSize; i++) {
        free(stringArr[i]);
    }
    free(stringArr);
}

void* increaseArraySizeIfFull(void* arr, int* logSize, int* phySize, unsigned long sizeOfType) {
    if (*logSize == *phySize) {
        (*phySize) *= 2;
        arr = realloc(arr, (*phySize) * sizeOfType);
        checkAllocation(arr);
    }

    return arr;
}

void checkAllocation(void *ptr){
    if (ptr == NULL)
    {
        printf("Memory Allocation \n");
        exit(1);
    }
}