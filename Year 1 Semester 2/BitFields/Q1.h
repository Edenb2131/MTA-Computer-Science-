//
// Created by Eden Bar on 22/05/2022.
//

#ifndef Y1S2PROJECT6_Q1_H
#define Y1S2PROJECT6_Q1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_BYTES_IN_ID 4
#define NUM_OF_BYTES_IN_PHONE 5
#define FOUND 1
#define NOT_FOUND 0


typedef struct _client
{
    char id[9];     // “12345678”
    char phone[12]; // “054-1234567”
} Client;

typedef struct _short_client
{
    unsigned char short_id[4];
    unsigned char short_phone[5];
} Short_client;

// Required Functions
Short_client* createShortClientArr(int size);
char* searchClientByID(Short_client* arr,int n,char *id);

// Extra Functions for usability and easy to read
Client* createClientArr( int size);
Short_client* compressIdAndPhone(Client *cliArr, int size);
char *getID(unsigned char *byteID);
char *getPhoneNumber(unsigned char *bytePhone);

// Check and Free Functions
void checkMemory(void *ptr);
void freeClient(Client *client , int size);

#endif //Y1S2PROJECT6_Q1_H
