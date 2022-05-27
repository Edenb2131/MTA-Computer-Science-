//
// Created by Eden Bar on 22/05/2022.
//

#include "Q1.h"

Short_client* createShortClientArr(int size){

    Client *cliArr = createClientArr( size);

    getchar(); // Clearing the buffer

    Short_client *shArr = compressIdAndPhone(cliArr,size);

    //freeClient(cliArr,size);
    free(cliArr);
    cliArr = NULL;

    return shArr;
}

Client* createClientArr(int size){
    int i;
    Client *cliArr = (Client*)malloc(sizeof(Client) * size);
    checkMemory(cliArr);

    for(i = 0; i < size; i++){
        //printf("Please enter ID number \n");
        scanf("%s" , cliArr[i].id);

        //printf("Please enter phone number \n");
        scanf("%s" , cliArr[i].phone);

    }

    return cliArr;
}

void compressId(Client cliArr, Short_client *shArr){
    int i = 0, j = 0;
    unsigned char num1, num2;
    for (i = 0; i < NUM_OF_BYTES_IN_ID; i++){
        num1 = ((cliArr.id[j] - '0') << 4); // 00000000 --> XXXX0000
        num2 = (cliArr.id[j + 1] - '0'); // 00000000 --> 0000YYYY
        shArr->short_id[i] =  num1 | num2 ; // 00000000 --> XXXXYYYY

        j += 2;
    }
}

void compressPhone(Client cliArr, Short_client *shArr){
    int i = 0, j = 0;
    unsigned char num1;

    for (i = 0; i < NUM_OF_BYTES_IN_PHONE; i++)
    {
        if (j == 2){ // We got to "-" in the phone number
            shArr->short_phone[i] = ((cliArr.phone[j] - '0') << 4);// 00000000 --> XXXX0000
            j += 2;

            // jumping 2 slots
            num1 = (cliArr.phone[j] - '0');
            shArr->short_phone[i] |= num1; // 00000000 --> XXXXYYYY
            j++;
        }
        else{ // Same system as compressing ID
            shArr->short_phone[i] = ((cliArr.phone[j] - '0') << 4) | (cliArr.phone[j + 1] - '0');
            j += 2;
        }
    }
}
//
Short_client* compressIdAndPhone(Client *cliArr, int size) {
    int i = 0;
    Short_client *shArr = (Short_client*)malloc((sizeof(Short_client) * size));
    checkMemory(shArr);


    for (i = 0; i < size; i++){
        compressId(cliArr[i], &shArr[i]);   // Getting the ID
        compressPhone(cliArr[i], &shArr[i]);// Getting the Phone
    }

    return shArr;
}

char* searchClientByID(Short_client* arr,int n, char *id){

    int i;
    int found = NOT_FOUND;

    for (i = 0; i < n && (found != FOUND); i++){
        if (strcmp(getID(arr[i].short_id), id) == 0)
            found = FOUND; // break

    }

    if (found == NOT_FOUND)
        return NULL;

    else
        return getPhoneNumber(arr[i - 1].short_phone);
}


char *getID(unsigned char *byteID){

    char *id;
    int i = 0, j = 0;
    short mask; // the reason we are using short here is to efficiently extract the id from the byteID

    id = (char *)malloc(9 * sizeof(char)); // Transforming if back to char[9]
    checkMemory(id);

    mask = 0xF; // 0000 0000 - 0000 1111

    for (i = 0; i < NUM_OF_BYTES_IN_ID; i++)
    {
        id[j] = ((byteID[i] >> 4) & mask) + '0';  // 0000 0000 - XXXX 1111
        j++;

        id[j] = (byteID[i] & mask) + '0';         // 0000 0000 - XXXX YYYY
        j++;
    }

    id[j] = '\0';
    return id;

}

char *getPhoneNumber(unsigned char *bytePhone){

    char *phone;
    int i = 0, j = 0;
    short mask;

    phone = (char *)malloc(12 * sizeof(char)); // allocation 12 chars because "05X-XXXXXXX"
    checkMemory(phone);

    mask = 0xF;// 0000 0000 - 0000 1111

    //Same concept as getID
    for (i = 0; i < NUM_OF_BYTES_IN_PHONE ; i++)
    {
        phone[j] = (char)(((bytePhone[i] >> 4) & mask) + '0');
        j++;

        if (j == 3) // Means we got to "-" skipping over and filling it later
            j++;

        phone[j] = (char)((bytePhone[i] & mask) + '0');
        j++;
    }

    phone[3] = '-';
    phone[j] = '\0';

    return phone;
}

void checkMemory(void *ptr){
    if (ptr == NULL)
    {
        printf("Memory Allocation \n");
        exit(1);
    }
}

void freeClient(Client *client, int size){
    int i;
    for(i = 0 ; i < size ; i++) {
        free(client + i);
    }
}
