//
// Created by Eden Bar on 26/05/2022.
//

#ifndef Y1S2PROJECT6_Q2_H
#define Y1S2PROJECT6_Q2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_OF_BITS_IN_BYTE 8

typedef unsigned char BYTE;

int* filter(int* Numbers, int size, unsigned char* pred, int* new_size);
bool isBitOnByIndex(BYTE byte, unsigned int index);
int* xorFilter(int* Numbers, int size, unsigned char* pred1, unsigned char* pred2, int* new_size);

void checkMemory(void *ptr);

#endif //Y1S2PROJECT6_Q2_H
