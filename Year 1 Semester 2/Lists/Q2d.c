//
// Created by Eden Bar on 14/03/2022.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//ListNode struct
typedef struct listNode{
    int* dataPtr;
    struct listNode* next;
}ListNode;

//List struct
typedef struct list
{
    ListNode* head;
    ListNode* tail;
}List;

//The required function
List merge(List lst1, List lst2);
void mergeRec(List* lst,ListNode* curr1 , ListNode* curr2);

//List functions:
void checkAllocation(void* ptr); //Allocation
void makeEmptyList(List* lst); //Making new list
bool isEmptyList(List *lst);//Checking if the list is empty
void freeList(List* lst); // free allocation of list
void printList(List* lst); //Printing lists
ListNode* createNewListNode(int data, ListNode* next); // create new list with given data
void insertDataToEndList(List* lst, int data); // Insert data to end
void insertNodeToEndList(List* lst, ListNode* newTail); // Insert Node to end

List getList(); // getting a list from the user

void main()
{

    List lst1, lst2, mergedList;

    lst1 = getList();
    lst2 = getList();

    mergedList = merge(lst1,lst2);

//    printf("Merged list:\n");
    printList(&mergedList);

    freeList(&mergedList);
}

List merge(List lst1, List lst2)
{
    List newLst;
    makeEmptyList(&newLst);

    mergeRec(&newLst,lst1.head, lst2.head);

    return newLst;
}

void mergeRec(List* lst,ListNode* curr1 , ListNode* curr2) {

    if (curr1 == NULL && curr2 == NULL)
        return;

    if (curr1 == NULL){
        insertNodeToEndList(lst, curr2);
        mergeRec(lst,curr1,curr2->next);
    }

    else if (curr2 == NULL){
        insertNodeToEndList(lst, curr1);
        mergeRec(lst,curr1->next,curr2);
    }

    else if (*(curr1->dataPtr) > *(curr2->dataPtr)) {
        insertNodeToEndList(lst, curr1);
        mergeRec(lst, curr1->next, curr2);
    } else {

        insertNodeToEndList(lst, curr2);
        mergeRec(lst, curr1, curr2->next);
    }


}

List getList()
{
    List res;
    int size, num, i;

    makeEmptyList(&res);

//    printf("Please enter the number of items to be entered:\n");
    scanf("%d", &size);

//    printf("Please enter the numbers:\n");
    for(i = 0; i < size; i++)
    {
        scanf("%d", &num);
        insertDataToEndList(&res, num);
    }

    return res;

}

void printList(List *lst)
{
    ListNode* curr = lst->head;
    while (curr != NULL)
    {
        printf("%d ", *(curr->dataPtr));
        curr = curr->next;
    }
    printf("\n");
}

void makeEmptyList(List* lst){
    lst->head = lst->tail = NULL;
}

bool isEmptyList(List *lst){
    if (lst->head == NULL)
        return true;

    return false;
}

void insertDataToEndList(List* lst, int data){
    ListNode *result = createNewListNode(data, NULL);

    insertNodeToEndList(lst, result);

}

void insertNodeToEndList(List *lst, ListNode *newTail) {

    if (isEmptyList(lst)) {
        lst->head = newTail;
        lst->tail = newTail;
    } else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void freeList(List *lst)
{
    ListNode *curr = (*lst).head, *next;

    while (curr != NULL) {
        next = curr->next;
        free(curr->dataPtr);
        free(curr);
        curr = next;
    }
}

void checkAllocation(void* ptr){
    if (ptr == NULL)
    {
        printf("Allocation error\n");
        exit(1);
    }
}

ListNode* createNewListNode(int data, ListNode* next){
    ListNode *result;

    result = (ListNode*)malloc(sizeof(ListNode));
    checkAllocation(result);

    result->dataPtr =(int *)malloc(sizeof(int));
    checkAllocation(result->dataPtr);

    *(result->dataPtr) = data;
    result->next = next;

    return result;

}

