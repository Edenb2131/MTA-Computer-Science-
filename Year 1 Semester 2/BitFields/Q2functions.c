//
// Created by Eden Bar on 26/05/2022.
//

#include "Q2.h"

int* filter(int* Numbers, int size, unsigned char* pred, int* new_size) {

    int i, j;
    *new_size = 0;
    int *newNumbers = (int *) malloc(sizeof(int) * size);
    checkMemory(newNumbers);

    for (i = 0; i < size; i++) { // Looping for every int in numbers

        // Loop backwards from 7 to 0
        for (j = NUM_OF_BITS_IN_BYTE - 1; j >= 0; j--) {
            // Check if bit is on, on given index
            if (isBitOnByIndex(pred[i], NUM_OF_BITS_IN_BYTE - 1 - j)) {

                // append the correct number to the output array
                int num = Numbers[i * 8 + NUM_OF_BITS_IN_BYTE - 1 - j];
                newNumbers[*new_size] = num;
                (*new_size)++;
            }
        }

    }
    newNumbers = (int*)realloc(newNumbers , sizeof(int) * (*new_size));
    checkMemory(newNumbers);
    return newNumbers;
}

bool isBitOnByIndex(BYTE byte, unsigned int index) {

    BYTE mask = 0x01;
    mask <<= index;

    return (byte & mask) > 0; // if it is on then will return true , else false
}

int* xorFilter(int* Numbers, int size, unsigned char* pred1, unsigned char* pred2, int* new_size){

    int i, j;
    *new_size = 0;
    int *newNumbers = (int *) malloc(sizeof(int) * size);
    checkMemory(newNumbers);

    for (i = 0; i < size; i++) { // Looping for every int in numbers

        // Loop backwards from 7 to 0
        for (j = NUM_OF_BITS_IN_BYTE - 1; j >= 0; j--) {
            // Check if bit is on, on given index

            int sum = 0;
            sum += isBitOnByIndex(pred1[i], NUM_OF_BITS_IN_BYTE - 1 - j) + isBitOnByIndex(pred2[i], NUM_OF_BITS_IN_BYTE - 1 - j);
            if (sum == 1) {

                // append the correct number to the output array
                int num = Numbers[i * 8 + NUM_OF_BITS_IN_BYTE - 1 - j];
                newNumbers[*new_size] = num;
                (*new_size)++;
            }
        }

    }
    newNumbers = (int*)realloc(newNumbers , sizeof(int) * (*new_size));
    checkMemory(newNumbers);
    return newNumbers;

}

void checkMemory(void *ptr){
    if (ptr == NULL)
    {
        printf("Memory Allocation \n");
        exit(1);
    }
}