//
// Created by Eden Bar on 26/05/2022.
//

#include "Q3.h"


void* scramble(void* arr, int ElemSize, int n, int* indArr){

    void* newArr = malloc(n * ElemSize);
    int i;

    for(i = 0; i < n ; i ++)
        memcpy((BYTE*)newArr + (i * ElemSize),((BYTE*)arr + (indArr[i] * ElemSize)), ElemSize);

    return newArr;
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

int* scrambleInt(int* intArr, int intSize, int* indArr) {
    int* scrambledArr = (int*)scramble(intArr, sizeof(int), intSize, indArr);

    return scrambledArr;
}

void printIntArr(int* intArr, int intSize) {
    int i;

    for (i = 0; i < intSize; i++) {
        printf("%d ", intArr[i]);
    }
    printf("\n");
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

char** scrambleString(char** stringArr, int stringArrSize, int* indArr) {
    return (char**)scramble(stringArr, sizeof(char*), stringArrSize, indArr);
}

void printStringArr(char** stringArr, int stringArrSize) {
    for (int i = 0; i < stringArrSize; i++) {
        printf("%s\n", stringArr[i]);
    }
}

void freeMemory(int* intArr, int* scrambleIntArr, int intSize, char** stringArr, char** scrambleStringArr,int stringSize) {
    free(intArr);
    free(scrambleIntArr);
    for (int i = 0; i < stringSize; i++) {
        free(stringArr[i]);
    }
    free(stringArr);
    free(scrambleStringArr);
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