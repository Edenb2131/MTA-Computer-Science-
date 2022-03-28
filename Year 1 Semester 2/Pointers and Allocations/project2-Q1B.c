//
// Created by Eden Bar on 02/03/2022.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

//The function we require coding
void pointerSort(int* arr, unsigned int size,int ascend_flag, int*** pointers);

//merge sort func
void mergeUP(int a1[], int n1, int a2[], int n2, int res[]); //sorting up
void mergeSortUP(int arr[], int size);
void mergeDOWN(int a1[], int n1, int a2[], int n2, int res[]); //sorting down
void mergeSortDOWN(int arr[], int size);
void copyArr(int dest[], int src[], int size);

//printing the new Array
void printPointers(int **pointers,int size);



void main(){
    unsigned int size, i;
    int arr[SIZE];
    int ** pointers;
    int ascend_flag;

    printf("Please enter the number of items:\n");
    scanf("%u", &size);

    for (i = 0; i<size; i++)
        scanf("%d", &arr[i]);

    scanf("%d", &ascend_flag);
    pointerSort(arr, size, ascend_flag, &pointers);
    printf("The sorted array:\n"); //Print the sorted array
    printPointers(pointers, size);
    free(pointers);

}

//merge sort functions
void mergeSortUP(int arr[], int size)
{
    int* tmpArr = NULL;
    if (size <= 1)
        return;

    mergeSortUP(arr, size / 2);
    mergeSortUP(arr + size / 2, size - size / 2);

    tmpArr = (int*)malloc(size * sizeof(int));
    if (tmpArr)
    {
        mergeUP(arr, size / 2, arr + size / 2, size - size / 2, tmpArr);
        copyArr(arr, tmpArr, size); // copy values from tmpArr to arr
        free(tmpArr);
    }
    else
    {
        printf("Memory allocation failure!!!\n");
        exit(1);	// end program immediately with code 1 (indicating an error)
    }
}
void mergeUP(int a1[], int n1, int a2[], int n2, int res[])
{
    int ind1, ind2, resInd;
    ind1 = ind2 = resInd = 0;

    while ((ind1 < n1) && (ind2 < n2)) {
        if (a1[ind1] <= a2[ind2]) {
            res[resInd] = a1[ind1];
            ind1++;
        }
        else {
            res[resInd] = a2[ind2];
            ind2++;
        }
        resInd++;
    }

    while (ind1 < n1) {
        res[resInd] = a1[ind1];
        ind1++;
        resInd++;
    }
    while (ind2 < n2) {
        res[resInd] = a2[ind2];
        ind2++;
        resInd++;
    }
}
void mergeDOWN(int a1[], int n1, int a2[], int n2, int res[]){

    int ind1, ind2, resInd;
    ind1 = ind2 = resInd = 0;

    while ((ind1 < n1) && (ind2 < n2)) {
        if (a1[ind1] >= a2[ind2]) {
            res[resInd] = a1[ind1];
            ind1++;
        }
        else {
            res[resInd] = a2[ind2];
            ind2++;
        }
        resInd++;
    }

    while (ind1 < n1) {
        res[resInd] = a1[ind1];
        ind1++;
        resInd++;
    }
    while (ind2 < n2) {
        res[resInd] = a2[ind2];
        ind2++;
        resInd++;
    }
}
void mergeSortDOWN(int arr[], int size)
{
    int* tmpArr = NULL;
    if (size <= 1)
        return;

    mergeSortDOWN(arr, size / 2);
    mergeSortDOWN(arr + size / 2, size - size / 2);

    tmpArr = (int*)malloc(size * sizeof(int));
    if (tmpArr)
    {
        mergeDOWN(arr, size / 2, arr + size / 2, size - size / 2, tmpArr);
        copyArr(arr, tmpArr, size); // copy values from tmpArr to arr
        free(tmpArr);
    }
    else
    {
        printf("Memory allocation failure!!!\n");
        exit(1);	// end program immediately with code 1 (indicating an error)
    }
}
void copyArr(int dest[], int src[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        dest[i] = src[i];
}

//The function we require coding
void pointerSort(int* arr, unsigned int size,int ascend_flag, int*** pointers)
{
    int i;
    *pointers = (int**)malloc(sizeof(int*)*size);

    if(ascend_flag == 1) {
        mergeSortUP(arr, (int)size);
    }
    else
        mergeSortDOWN(arr, (int)size);

    for(i = 0; i < size; i++)
        *(*pointers+i) = &(arr[i]);

}

//printing the new Array
void printPointers(int **pointers,int size){
    int i;
    int* ptr = *pointers;
    for(i = 0; i< size; i++)
        printf("%d ",ptr[i]);
    printf("\n");
}

