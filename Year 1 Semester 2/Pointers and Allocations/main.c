#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}


//
// Created by Eden Bar on 06/03/2022.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct monom {
    int coefficient;    //המקדם
    int power;        // החזקה
}Monom;

//The required functions
Monom* getPolynom(unsigned int* polySize); // gets pollys
void printPolyMul(Monom* polynom1, int size1, Monom* polynom2, int size2); //multi pollys
void printPolySum(Monom* polynom1, int size1, Monom* polynom2, int size2);//sums pollys

//printing polymers function
void printPolynomial(Monom polynom1[], int size);

//Adding same power together
Monom* sumSamePower(Monom polynom1[], int* size);

//the merging functions
void copyArr(Monom src[], Monom dest[], int size);
void mergeDOWN(Monom a1[], int n1, Monom a2[], int n2, Monom res[]);
void mergeSortDOWN(Monom arr[], int size);


int main()
{
    Monom *polynom1, *polynom2;             // The input polynoms
    unsigned int polynom1Size,polynom2Size; // The size of each polynom

    printf("Please enter the first polynom:\n");
    polynom1 = getPolynom(&polynom1Size);   // get polynom 1

    printf("Please enter the second polynom:\n");
    polynom2 = getPolynom(&polynom2Size);   // get polynom 2

    printf("The multiplication of the polynoms is:\n"); // print the multiplication
    printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    printf("The sum of the polynoms is:\n"); // print the sum
    printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    free(polynom1); // releasing all memory allocations
    free(polynom2);
}

//Getting the polymers
Monom* getPolynom(unsigned int* polySize){
    int arrSize = 0, i;
    int arr[MAX_SIZE];
    char lastInput;
    Monom* poly;

    while (scanf("%d%c", &arr[arrSize], &lastInput)) {
        arrSize++;
        if (lastInput == '\n') {
            break;
        }
    }
    *polySize =(int) arrSize/2;
    poly = (Monom*)malloc(sizeof(Monom)*(*polySize));

    if(poly == NULL) //check if allocation failed
        exit(1);

    for (i = 0; i < arrSize; i++) {
        poly[i].coefficient = arr[2 * i];
        poly[i].power = arr[2 * i + 1];
    }

    return poly;
}

//multi pollys
void printPolyMul(Monom* polynom1, int size1, Monom* polynom2, int size2){

    int i,j,ind1 = 0 ,newSize = 0;
    newSize = size1 * size2;
    Monom* poly = (Monom*)malloc(sizeof(Monom)*newSize);

    if(poly == NULL) //check if allocation failed
        exit(1);


    for (i = 0; i < size1; i++) {
        for (j = 0; j < size2; j++) {
            poly[ind1].power = polynom1[i].power + polynom2[j].power;
            poly[ind1].coefficient = polynom1[i].coefficient * polynom2[j].coefficient;
            ind1++;
        }
    }

    mergeSortDOWN(poly,newSize);

    poly = sumSamePower(poly,&newSize);

    printPolynomial(poly,newSize);

    //free(poly);
}

//sums pollys
void printPolySum(Monom* polynom1, int size1, Monom* polynom2, int size2){
    int newSize = size1 + size2;;

    Monom* copyPoly1 = (Monom*)malloc(size1 * sizeof(Monom));
    Monom* copyPoly2 = (Monom*)malloc(size2 * sizeof(Monom));
    Monom* poly = (Monom*)malloc((newSize)*sizeof(Monom));

    if(copyPoly1 == NULL || copyPoly2 == NULL || poly == NULL) //check if allocation failed
        exit(1);

    copyArr(polynom1,copyPoly1,size1);
    copyArr(polynom2,copyPoly2,size2);

    mergeSortDOWN(copyPoly1,size1);
    mergeSortDOWN(copyPoly2,size2);

    //printf("size1: %d, size2: %d , newSize: %d  1\n",size1,size2,size1*size2);
    mergeDOWN(copyPoly1,size1,copyPoly2,size1,poly);
    //printf("size1: %d, size2: %d , newSize: %d 11\n",size1,size2,size1*size2);
    poly = sumSamePower(poly,&newSize);
    //printf("size1: %d, size2: %d , newSize: %d  111\n",size1,size2,size1*size2);
    printPolynomial(poly,newSize);

    //free(copyPoly1);
    //free(copyPoly2);
    //free(poly);
}

//Merging functions
void mergeDOWN(Monom a1[], int n1, Monom a2[], int n2, Monom res[]){

    int ind1, ind2, resInd;
    ind1 = ind2 = resInd = 0;

    while ((ind1 < n1) && (ind2 < n2)) {
        if (a1[ind1].power >= a2[ind2].power) {
            res[resInd].coefficient = a1[ind1].coefficient;
            res[resInd].power = a1[ind1].power;
            ind1++;
        }
        else {
            res[resInd].coefficient = a2[ind2].coefficient;
            res[resInd].power = a2[ind2].power;
            ind2++;
        }
        resInd++;
    }

    while (ind1 < n1) {
        res[resInd].coefficient = a1[ind1].coefficient;
        res[resInd].power = a1[ind1].power;
        ind1++;
        resInd++;
    }
    while (ind2 < n2) {
        res[resInd].coefficient = a2[ind2].coefficient;
        res[resInd].power = a2[ind2].power;
        ind2++;
        resInd++;
    }

}
void mergeSortDOWN(Monom arr[], int size) {
    int halfSize = size / 2;
    Monom* tmpArr;

    if (size <= 1) {
        return;
    }

    mergeSortDOWN(arr, halfSize);
    mergeSortDOWN(arr + halfSize, size - halfSize);

    tmpArr = (Monom*)malloc(size * sizeof(Monom));

    if (tmpArr == NULL) {
        exit(1);
    }

    mergeDOWN(arr, halfSize, arr + halfSize, size - halfSize, tmpArr);

    copyArr(tmpArr, arr, size);

    //free(tmpArr);


}
void copyArr(Monom src[], Monom dest[], int size)
{
    int i;

    for (i = 0; i < size; i++) {
        dest[i].coefficient = src[i].coefficient;
        dest[i].power = src[i].power;
    }
}

//printing polynomial function
void printPolynomial(Monom polynom1[], int size) {
    int i, currentCoefficient, currentPower;
    bool isFirst = true;

    for (i = 0; i < size; i++) {
        currentCoefficient = polynom1[i].coefficient;
        currentPower = polynom1[i].power;

        if (currentCoefficient != 0) {
            if (currentCoefficient > 0) {
                if (isFirst) {
                    isFirst = false;
                } else {
                    printf("+");
                }
            }

            if (currentCoefficient != 1) {
                if (currentCoefficient == -1 && currentPower != 0) {
                    printf("-");
                } else {
                    printf("%d", currentCoefficient);
                }
            }

            if (currentPower != 0) {
                printf("x");
            }
            if (currentPower != 0 && currentPower != 1) {
                printf("^%d", currentPower);
            }
        }
    }

    printf("\n");


}

//checking to see if have another power and adding them together
Monom* sumSamePower(Monom* polynom1, int* size) {
    int i, newSize = 0;
    int size1 = *size;
    Monom* newPoly = (Monom*)malloc((size1) * sizeof(Monom));

    if(newPoly == NULL) //check if allocation failed
        exit(1);

    for (i = 0; i < (*size); i++) {
        if (i == 0) {
            newPoly[newSize].power = polynom1[i].power;
            newPoly[newSize].coefficient = polynom1[i].coefficient;
            newSize++;
        } else {
            if (polynom1[i].power == newPoly[newSize - 1].power) {
                newPoly[newSize - 1].coefficient += polynom1[i].coefficient;
            }
            else
            {
                newPoly[newSize] = polynom1[i];
                newSize++;
            }
        }
    }
    *size = newSize;

    //free(polynom1); /////
    //newPoly = (Monom*)realloc(newPoly, (newSize * sizeof(Monom))); ////

    return newPoly;




}