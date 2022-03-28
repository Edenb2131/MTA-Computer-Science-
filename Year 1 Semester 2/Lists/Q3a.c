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
unsigned int getPairOccurrences(List coord_List, int x, int y);

void main(){
    List coordList;

    int x, y;
    unsigned int res;

// The user will enter the number of points followed by the points.
// The pointes will be entered in a sorted fashion.
// i.e. first by the x value and then by y.
// for example (5 points): 5 1 2 1 5 2 7 3 3 3 8
// are: (1,2),(1,5),(2,7),(3,3),(3,8)

    coordList = getCoordList();

// get the (x,y) to look for
    scanf("%d%d", &x, &y);

    res = getPairOccurrences(coordList, x, y);

    printf("The point (%d,%d) appears %u times\n", x, y, res);

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

unsigned int getPairOccurrences(List coord_List, int x, int y)
{
    XListNode *currX;
    YListNode * currY;
    int counter;

    currX = coord_List.head;

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