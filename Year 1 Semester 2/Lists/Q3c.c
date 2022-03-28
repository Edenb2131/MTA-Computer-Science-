//
// Created by Eden Bar on 21/03/2022.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

//Given Functions
List getCoordList();
unsigned int getXOccurrences(List coord_list, int x);


void main()
{

    List coordList;
    int x;
    unsigned int res;

    coordList = getCoordList();

// get the (x,*) to look for
    scanf("%d", &x);

    res = getXOccurrences(coordList, x);

    printf("The point (%d,*) appears %u times\n", x, res);

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

unsigned int getXOccurrences(List coord_list, int x){

    XListNode *currX;
    YListNode *currY;

    unsigned int counter;

    currX = coord_list.head;

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