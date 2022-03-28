//
// Created by Eden Bar on 07/03/2022.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define END 0

//functions that get from the user the array
char** getStrArrayInput(unsigned int* str_array_size);

//get string input
char* getStr();

//prints the array
void printArray(char** str_array, int size);

//free memory allocation
void freeArray(char** str_array, int size);

//move indexs in str_array after deleting
void delCharAndUpdatingStrArray(char* str, int ind, char** ptr_to_chars_array);

//if string is empty
int delArrayFromStr(char** str_array, int size);

//move pointers left
void moveLeft(char **str_array, int size, int ind);

//given functions
char** setPtrToCharsArray(char** str_array);
unsigned int  RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array);


int main(){
    char** str_array;
    unsigned int str_array_size;
    char** ptr_to_chars_array;
    unsigned int res;

    str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)
    ptr_to_chars_array = setPtrToCharsArray(str_array);
    res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);
    printArray(str_array, (int)(str_array_size - res));

    // Free memory
    freeArray(str_array, (int)(str_array_size - res));
    free(ptr_to_chars_array);

    return END;
}
//get input from user
char** getStrArrayInput(unsigned int* str_array_size){
    int i, logSize = 0,phySize = 1;
    int numOfStr = 0, str_size  = 0;
    char* str;
    char** str_array =(char**)malloc(sizeof(char*)*phySize);

    if(str_array == NULL) //check memory allocation
        exit(1);

    scanf("%d",&numOfStr);

    while(logSize < numOfStr){
        str = getStr();
        str_size = (int)strlen(str);

        if(logSize == phySize){
            phySize *= 2;
            str_array = (char**)realloc(str_array, phySize * sizeof(char*));
            if(str_array == NULL)//check memory allocation
                exit(1);
        }

        str_array[logSize] = (char*)malloc(str_size*sizeof(char));
        if(str_array[logSize] == NULL)//check memory allocation
            exit(1);

        strcpy(str_array[logSize],str);

        logSize++;
    }


    *str_array_size = logSize;
    return str_array;

}
//getting strings
char* getStr() {
    int logSize = 0, phySize = 1;
    char ch;
    char* Str = (char*)malloc(phySize * sizeof(char));

    if(!Str)
        exit(1);

    scanf(" %c", &ch);
    while (ch != '\n') {
        if (logSize == phySize) {
            phySize *= 2;
            Str = (char*)realloc(Str, phySize * sizeof(char));
            if(!Str)
                exit(1);
        }
        Str[logSize] = ch;
        logSize++;
        scanf("%c", &ch);
    }
    Str[logSize] = '\0';
    Str = (char*)realloc(Str, (logSize + 1) * sizeof(char));

    return Str;
}

//move index in str_array after deleting
void delCharAndUpdatingStrArray(char* str, int ind, char** ptr_to_chars_array){
    int i, newInd = 0;
    char* ptr;

    for (i = ind; i < strlen(str); i++) {
        str[i] = str[i + 1];

        if (i != ind) {
            ptr = ptr_to_chars_array[newInd];
            while (ptr != NULL) {
                if (ptr == &str[i]) {
                    ptr -= sizeof(char);
                    ptr_to_chars_array[newInd] = ptr;
                }

                newInd++;
                ptr = ptr_to_chars_array[newInd];
            }
        }
        newInd = 0;
    }
}

//move pointers left
void moveLeft(char **str_array, int size, int ind){
    int i;

    for (i = ind; i < size - 1; i++) {
        strcpy(str_array[i], str_array[i + 1]);
    }

    free(str_array[size - 1]);
    str_array[size - 1] = NULL;
}

//deleting empty arrays
int delArrayFromStr(char** str_array, int size){
    int i, counter = 0;
    char* pos;

    for (i = 0; i < size - counter; i++) {
        pos = str_array[i];
        if (strlen(pos) == 0) {
            moveLeft(str_array, size - counter, i);
            counter++;
            i--;
        }
    }

    return counter;
}

//given function
unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char **ptr_to_chars_array){

    int i, j, tempStr_size,ind = 0, res = 0;
    char *tempStr, *currentCharAddress1, *pInd;

    pInd = ptr_to_chars_array[ind];


    while (pInd != NULL) {

        for (i = 0; i < str_array_size; i++) {
            tempStr = (*str_array)[i];
            tempStr_size = strlen(tempStr);

            for (j = 0; j <= tempStr_size; j++) {
                pInd = ptr_to_chars_array[ind];
                if (&tempStr[j] == pInd) { //if this is the pos we need to delete
                    delCharAndUpdatingStrArray(tempStr, j, ptr_to_chars_array);
                    ind++;
                }
            }
        }
    }

    res = delArrayFromStr(*str_array, (int)str_array_size);

    return res;

}
char** setPtrToCharsArray(char** str_array){
    char** res;
    int size, i;
    int str_array_row, str_array_col;


    scanf("%d", &size); // Get number of ptrs
    res = (char**)malloc(sizeof(char*)*(size+1)); // Add 1 for NULL at the end

    for (i = 0; i < size; i++){
        scanf(" %d", &str_array_row);
        scanf(" %d", &str_array_col);
        res[i] = str_array[str_array_row] + str_array_col;
    }

    res[size] = NULL; // Set the last one to NULL

    return res;
}

//print char array
void printArray(char** str_array, int size){
    int i;

    for(i= 0 ; i < size; i++){
        printf("%s\n",str_array[i]);
    }

}

//free memory allocation
void freeArray(char** str_array, int size){
    int i;

    for (i = 0; i < size; i++) {
        free(str_array[i]);
        str_array[i] = NULL;
    }

    free(str_array);
}