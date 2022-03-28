//
// Created by Eden Bar on 09/12/2021.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10
#define MAX_INT_SIZE 10
#define FUNC_COUNT 9
#define EXIT 0

// Add your recursive functions declarations here

//getting a number and a digit and checking if the digit is showing an even number of times in the number
bool isEven(int num, int dig);

//getting x and y variables and checking to see how many paths are there to get to (0,0)
int howManyPaths(int x, int y);

//Getting the closest power of num to number
int biggestLowPower(int x, int num);

//Calculating thr sum of all numbers without the right one
int partSum(int num);

//Turing number to string
void intToStr(int num, char s[]);

//Making a new array (MaxPre...)and fill it until the n place with the max numver in numbers array
void fillMaxPrefixesArray (int numbers[], int n, int maxPrefixesArray[]);

//Changing the array the min number will be in the first place(number[0])
void getMinToStart (int numbers[], int n);

//Combing the two arrays into sortedArr2 sorted
void combineArrays (int sortedArr1[], int size1, int sortedArr2[], int size2);

//Returning how many numbers are really smaller the num
int countSmaller(int arr[], int start, int end, int num);

//function that turing a number if 1234 -> 4321
int turingNumber(int num);

// Testing functions
int readArray(int data[], int maxSize);
void printArray(int data[], int size);
void bubbleSort(int arr[], int size);
void swap(int arr[], int i, int j);
void checkQ1();
void checkQ2();
void checkQ3();
void checkQ4();
void checkQ5();
void checkQ6();
void checkQ7();
void checkQ8();
void checkQ9();


/*********** main - don't make any changes here !!! ***************************/
void main()
{
    int funcNum;
    bool exit = false;

    while (!exit)
    {
        printf("Enter the number of function you want to check (1-%d) or %d to exit the program: ", FUNC_COUNT, EXIT);
        scanf("%d", &funcNum);

        switch (funcNum)
        {
            case 1:
                checkQ1();
                break;
            case 2:
                checkQ2();
                break;
            case 3:
                checkQ3();
                break;
            case 4:
                checkQ4();
                break;
            case 5:
                checkQ5();
                break;
            case 6:
                checkQ6();
                break;
            case 7:
                checkQ7();
                break;
            case 8:
                checkQ8();
                break;
            case 9:
                checkQ9();
                break;
            case EXIT:
                exit = true;
                break;
            default:
                printf("Invalid choice.\n");
        }
        printf("\n");
    }

}

/***************** Testing functions - don't make any changes here!!! ***************/
void checkQ1()
{
    int num, dig;

    printf("Enter a positive integer: ");
    scanf("%d", &num);
    printf("Enter a digit: ");
    scanf("%d", &dig);
    if (isEven(num, dig))
    {
        printf("%d appears even number of times in %d\n", dig, num);
    }
    else
    {
        printf("%d appears odd number of times in %d\n", dig, num);
    }
}

void checkQ2()
{
    int x, y;

    printf("Enter two non-negative integers: ");
    scanf("%d%d", &x, &y);
    printf("There are %d paths from (0,0) to (%d,%d)\n", howManyPaths(x, y), x, y);
}

void checkQ3()
{
    int x, num;

    printf("Enter two positive integers: ");
    scanf("%d%d", &x, &num);
    printf("The biggest power of %d which is smaller than %d is %d\n", x, num, biggestLowPower(x, num));
}

void checkQ4()
{
    int num;

    printf("Enter a positive integer: ");
    scanf("%d", &num);
    printf("The partial sum of %d digits is %d\n", num, partSum(num));
}

void checkQ5()
{
    int num;
    char string[MAX_INT_SIZE + 1];

    printf("Enter a positive integer: ");
    scanf("%d", &num);
    intToStr(num, string);
    printf("The string representing the integer %d is %s\n", num, string);
}

void checkQ6()
{
    int numbers[SIZE];
    int maxPrefixes[SIZE];
    int size;

    size = readArray(numbers, SIZE);
    fillMaxPrefixesArray(numbers, size, maxPrefixes);
    printf("Max prefixes array: ");
    printArray(maxPrefixes, size);
}

void checkQ7()
{
    int numbers[SIZE];
    int size;

    size = readArray(numbers, SIZE);
    getMinToStart(numbers, size);
    printf("The minimal number is: %d\n", numbers[0]);

    // check if all other numbers are still inb array
    bubbleSort(numbers, size);
    printf("The sorted array: ");
    printArray(numbers, size);
}

void checkQ8()
{
    int arr1[SIZE], arr2[2 * SIZE];
    int size1, size2;

    size1 = readArray(arr1, SIZE);
    size2 = readArray(arr2, 2 * SIZE - size1);

    // sort arrays
    bubbleSort(arr1, size1);
    bubbleSort(arr2, size2);

    combineArrays(arr1, size1, arr2, size2);
    printf("The combined sorted array: ");
    printArray(arr2, size1 + size2);
}

void checkQ9()
{
    int numbers[SIZE];
    int size, num;

    // read numbers from user (assumption: numbers are different from each other)
    size = readArray(numbers, SIZE);
    bubbleSort(numbers, size);

    printf("Please enter an integer: ");
    scanf("%d", &num);

    printf("There are %d numbers in array that are smaller than %d\n", countSmaller(numbers, 0, size - 1, num), num);
}

// This function reads a series of integers from user into data array.
// The function will first ask the user to enter the number of integers he wishes
// to enter to array. If number is bigger than maxSize, then only the first masSize
// numbers will be read.
// The fucntion returns the arrays logical size (number of elements inserted into array).
int readArray(int data[], int maxSize)
{
    int count;
    int i;	// number of elements inserted into array

    printf("How many numbers would you like to enter to array ? (no more than %d) ", maxSize);
    scanf("%d", &count);
    if (count > maxSize)
    {
        count = maxSize;
    }
    printf("Please enter %d integers: ", count);

    for (i = 0; i < count; i++)
    {
        scanf("%d", &data[i]);	// read current input number
    }

    return count;
}

// This function prints the first size elements of data array (integers).
void printArray(int data[], int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// This functions sorts arr in increasing order using bubble sort algorithm
void bubbleSort(int arr[], int size)
{
    int i, j;

    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
}

void swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

/******************************* Recursive functions **************************/
// Add recursive functions implementation here


//getting a number and a digit and checking if the digit is showing an even number of times in the number
bool isEven(int num, int dig){

    if(num == 0)
        return true;

    if(num%10 == dig)
        return (!(isEven(num/10,dig)));
    return isEven(num/10,dig);

}

//getting x and y variables and checking to see how many paths are there to get to (0,0)
int howManyPaths(int x, int y){

    if(x == 0 || y == 0)
        return 1;

    return howManyPaths(x-1,y) + howManyPaths(x,y-1);

}

//Getting the closest power of num to number
int biggestLowPower(int x, int num){

    if(x > num)
        return 1;

    return biggestLowPower(x,num/x)*x;

}

//function that turing a number, if 1234 -> 4321
int turingNumber(int num){
//    printf("\n%d   ",num);
    int new=0;
    while(num > 0){
        new = new*10;
        new += num%10;
        num = num/10;
    }
//    printf("%d\n",new);
    return new;
}

//Calculating thr sum of all numbers without the right one
int partSum(int num){

    if(num < 10){
        return 0;
    }
    return (num /10) %10 + partSum(num/10);

//This is for me, dont worry/
//    int numFake = turingNumber(num);
//    printf("\nnum: %d     ",num);
//    printf("FakeNum: %d\n",numFake);
//    if(num < 10){
//        return 0;
//    }
//
//    return numFake%10 + partSum(turingNumber(numFake/10));

}

//function that will return how many numbers are in num(for 123 will return 3)
int howManyNumbers(int num){
    int counter = 0;
    if(num == 0)
        return 1;
    else {
        while (num > 0) {
            counter++;
            num = num / 10;
        }
    }
    return counter;
}

//Turing number to string
void intToStr(int num, char s[]){

//    int numFake = turingNumber(num);
    int numOfNum = howManyNumbers(num);

    if(numOfNum <= 1){
        s[numOfNum-1] = '0' + num;
        s[numOfNum] = '\0';
    }
    else{
        intToStr(num/10,s);

        char c = '0' + num % 10;
        s[numOfNum-1] = c;
        s[numOfNum] = '\0';

    }

//Please dont mind - just tried to something 1 3 4 7 8 13
//    if(num >= 10) {
//        char c = '0' + numFake % 10;
//        printf("\nc is:   %c  \n",c);
//        s[strlen(s)] = c;
//       printf("   %c  \n",s[strlen(s)]);
//
//        printf("\ns is: %s\n",s);
//        intToStr(turingNumber(numFake/10),s);
//    }
//
//    else{
//        char c = '0' + numFake % 10;
//        s[strlen(s)] = c;
//        printf("\nc is:   %c  \n",c);
//        s[strlen(s)+1] = '\0';
//        printf("\ns is: %s\n",s);
//        return;
//    }

}

//Making a new array (MaxPre...)and fill it until the n place with the max numver in numbers array
void fillMaxPrefixesArray (int numbers[], int n, int maxPrefixesArray[]){

    if(n == 1) {
        maxPrefixesArray[0] = numbers[0];
    }

    else {
        fillMaxPrefixesArray(numbers, n - 1, maxPrefixesArray);

        if (maxPrefixesArray[n - 2] > numbers[n - 1])
            maxPrefixesArray[n - 1] = maxPrefixesArray[n - 2];
        else
            maxPrefixesArray[n - 1] = numbers[n - 1];
    }


}

//Changing the array the min number will be in the first place(number[0])
void getMinToStart (int numbers[], int n){

    if(n == 0)
        return;
    else{
        getMinToStart(numbers, n - 1);
        if(numbers[0] > numbers[n-1])
            swap(numbers,0,n-1);
    }

}

//Combing the two arrays into sortedArr2 sorted
void combineArrays (int sortedArr1[], int size1, int sortedArr2[], int size2){

    if(size1 < 0)
        return ;
    else{

        combineArrays(sortedArr1,size1-1,sortedArr2,size2);

        sortedArr2[size2+size1] = sortedArr1[size1];

        bubbleSort(sortedArr2,(size1+size2));

    }

}

//Returning how many numbers are really smaller the num
int countSmaller(int arr[], int start, int end, int num){

    if(start > end)
        return 0;
    else{
        if(arr[end] < num)
            return countSmaller(arr,start,end -1, num) + 1;
        else
            return countSmaller(arr,start,end-1,num);


    }

}

