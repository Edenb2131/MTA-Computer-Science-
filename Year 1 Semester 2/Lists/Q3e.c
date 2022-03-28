//
// Created by Eden Bar on 21/03/2022.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NONE 1
#define EXIST 2
#define EXIST_ONCE 3

//Given typedefs
typedef struct XlistNode{
    int *xValue;
    struct Ylist *yList;
    struct XlistNode *previous;
    struct XlistNode *next;
}XListNode;

typedef struct YlistNode{
    int *yValue;
    struct YlistNode *next;
}YListNode;

typedef struct Ylist{
    YListNode *head;
    YListNode *tail;
}YList;

typedef struct list{
    XListNode *head;
    XListNode *tail;
}List;

//List functions
bool xExists(int x, List *lst); //checks if x value exits
void makeEmptyListX(List *lst); //Making empty list with x value
void makeEmptyListY(YList *lst); //Making empty list with y value
bool isEmptyListX(List *lst); //Checking if x list is empty
bool isEmptyListY(YList *lst);//Checking if y list is empty
void insertDataToEndListX(List *lst, int x);
XListNode *createNewXListNode(int x, XListNode *prev, XListNode *next);
void insertNodeToEndListX(List *lst, XListNode *tail);
void insertDataToEndListY(YList *lst, int y);
YListNode *createNewYListNode(int y, YListNode *next);
void insertNodeToEndListY(YList *lst, YListNode *tail);
void freeList(List *lst);
void checkMemoryAllocation(void *ptr);
void printList(List* lst);

//Given Functions
List getCoordList();
int insertCoordinate(List *coord_list, int x, int y);
unsigned int getPairOccurrences(List* coord_List, int x, int y);
unsigned int getXOccurrences(List *coord_list, int x);
int removeCoordinate(List *coord_list, int x, int y);


void main()
{
    List coordList;
    int x, y;
    int res;

    coordList = getCoordList();

// get the (x,y) to remove

    scanf("%d%d", &x, &y);

    res = removeCoordinate(&coordList, x, y);

    if(res == 1)

        printf("The point (%d,%d) didn't appear\n",x,y);

    else if(res == 2)

        printf("The point (%d,%d) has another occurrence\n",x,y);

    else if(res == 3)

        printf("The point (%d,%d) was the only point with this x\n",x,y);

    else

        printf("Other\n");

    printf("Updated list: ");

    printList(&coordList);

    freeList(&coordList);

}


List getCoordList(){

    List res;

    unsigned int size;
    unsigned int i;
    int x;
    int y;

    makeEmptyListX(&res);

    scanf("%u", &size);

    for (i = 0; i < size; i++)
    {
        scanf("%d%d", &x, &y);
        if (!xExists(x, &res))
            insertDataToEndListX(&res, x);


        insertDataToEndListY(res.tail->yList, y);
    }


    return res;
}

unsigned int getPairOccurrences(List *coord_List, int x, int y)
{
    XListNode *currX;
    YListNode * currY;
    int counter;

    currX = coord_List->head;

    while ((currX != NULL) && (*currX->xValue != x))
        currX = currX->next;

    counter = 0;

    if (currX != NULL) {

        currY = currX->yList->head;
        while (currY != NULL){

            if (*currY->yValue == y)
                counter++;

            currY = currY->next;
        }
    }
    return counter;
}

YListNode *createNewYListNode(int y, YListNode *next)
{
    YListNode *new;

    new = (YListNode *)malloc(sizeof(YListNode));
    checkMemoryAllocation(new);

    new->yValue = (int *)malloc(sizeof(int));
    checkMemoryAllocation(new->yValue);

    *new->yValue = y;
    new->next = next;

    return new;
}

unsigned int getXOccurrences(List* coord_list, int x){

    XListNode *currX;
    YListNode *currY;

    unsigned int counter;

    currX = coord_list->head;

    counter = 0;

    while (currX != NULL)
    {
        currY = currX->yList->head;
        if (*currX->xValue == x)
        {
            while (currY != NULL)
            {
                counter++;
                currY = currY->next;
            }
        }
        currX = currX->next;
    }
    return counter;
}

int insertCoordinate(List *coord_list, int x, int y)
{
    unsigned int res;
    XListNode *currX;
    XListNode *tempX;

    YListNode *currY;
    YListNode *prevY;
    YListNode *tempY;

    res = getPairOccurrences(coord_list, x, y);

    currX = coord_list->head;

    while ((currX != NULL) && (*currX->xValue < x))
    {
        currX = currX->next;
    }
    if (currX == NULL){
        insertDataToEndListX(coord_list, x);
        insertDataToEndListY(coord_list->tail->yList, y);
    }

    else if (*currX->xValue != x){

        tempX = createNewXListNode(x, currX, currX->next);
        currX->next = tempX;
        insertDataToEndListY(tempX->yList, y);
        currX = tempX->next;
        currX->previous = tempX;
    }

    else {
        currY = currX->yList->head;
        prevY = NULL;

        while ((currY != NULL) && (*currY->yValue < y)){

            prevY = currY;
            currY = currY->next;
        }

        tempY = createNewYListNode(y, currY);
        prevY->next = tempY;
    }

    if (res == 0)
        return NONE;
    else
        return EXIST;
}

int removeCoordinate(List *coord_list, int x, int y)
{
    unsigned int sum, num;

    XListNode *currX;
    YListNode *currY;
    YListNode *prevY;

    sum = getPairOccurrences(coord_list, x, y);
    if (sum == 0)
        return NONE;

    currX = coord_list->head;
    while (*currX->xValue != x)
        currX = currX->next;

    currY = currX->yList->head;
    prevY = NULL;

    while (*currY->yValue != y){
        prevY = currY;
        currY = currY->next;
    }

    if (prevY == NULL)
        currX->yList->head = currY->next;
    else
        prevY->next = currY->next;


    free(currY->yValue);
    free(currY);

    if (currX->yList->head == NULL){

        free(currX->xValue);
        free(currX->yList);
        if (coord_list->head == currX)
            coord_list->head = currX->next;

        else {
            currX->previous->next = currX->next;
            currX->next->previous = currX->previous;
        }
        free(currX);
    }
    num = getXOccurrences(coord_list, x);
    if ((sum > 1) && (num != 0))
        return EXIST;

    else if (num == 0)
        return EXIST_ONCE;

    else
        return 0;
}

void printList(List* lst) {
    XListNode *currX = lst->head;
    YListNode *currY;

    while (currX != NULL) {
        currY = currX->yList->head;
        while (currY != NULL) {
            printf("(%d,%d) ", *currX->xValue, *currY->yValue);
            currY = currY->next;
        }

        currX = currX->next;
    }

    printf("\n");
}

void makeEmptyListX(List *lst)
{

    lst->head = NULL;
    lst->tail = NULL;
}

void makeEmptyListY(YList *lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

bool isEmptyListX(List *lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

bool isEmptyListY(YList *lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

bool xExists(int x, List *lst)
{
    if (isEmptyListX(lst)) {
        return false;
    }
    else if (*lst->tail->xValue == x) {
        return true;
    }

    return false;
}

void insertDataToEndListX(List *lst, int x)
{
    XListNode *tail;
    tail = createNewXListNode(x, lst->tail, NULL);
    insertNodeToEndListX(lst, tail);
}

void insertNodeToEndListY(YList *lst, YListNode *tail)
{
    if (isEmptyListY(lst)){
        lst->head = lst->tail = tail;
    }
    else {
        lst->tail->next = lst->tail= tail;
    }
}

XListNode *createNewXListNode(int x, XListNode *prev, XListNode *next)
{
    XListNode *res;
    res = (XListNode *)malloc(sizeof(XListNode));
    checkMemoryAllocation(res);
    res->xValue = (int *)malloc(sizeof(int));
    checkMemoryAllocation(res->xValue);
    res->yList = (YList *)malloc(sizeof(YList));
    checkMemoryAllocation(res->yList);
    makeEmptyListY(res->yList);
    *res->xValue = x;
    res->previous = prev;
    res->next = next;
    return res;
}

void insertNodeToEndListX(List *lst, XListNode *tail)
{
    if (isEmptyListX(lst))
        lst->head = lst->tail =tail;

    else
        lst->tail->next = lst->tail = tail;;

}

void insertDataToEndListY(YList *lst, int y)
{
    YListNode *tail;
    tail = createNewYListNode(y, NULL);
    insertNodeToEndListY(lst, tail);
}

void freeList(List *lst)
{
    XListNode *currX;
    YListNode *currY;

    XListNode *tempX;
    YListNode *tempY;

    currX = lst->head;

    while (currX != NULL){

        tempX = currX->next;
        free(currX->xValue);
        currY = currX->yList->head;

        while (currY != NULL){
            tempY = currY->next;
            free(currY->yValue);
            free(currY);
            currY = tempY;
        }

        free(currX->yList);
        free(currX);
        currX = tempX;
    }
}

void checkMemoryAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Allocation failed!");
        exit(1);
    }
}


