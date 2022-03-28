//
// Created by Eden Bar on 17/03/2022.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//ListNode struct
typedef struct list_node
{
    char*  dataPtr;
    struct list_node*  next;
}ListNode;
//List struct
typedef struct list
{
    ListNode* head;
    ListNode* tail;
}List;
//Student struct
typedef struct  student
{
    List first;
    int grade;
} Student;

//List functions:
void checkAllocation(void* ptr); //Allocation
void makeEmptyList(List* lst); //Making new list
int isEmptyList(List lst);//Checking if the list is empty
void freeList(List lst); // free allocation of list
void printList(List lst); //Printing lists
ListNode* createNewListNode(char data, ListNode* next); // create new list with given data
void insertDataToEndList(List* lst, char data); // Insert data to end
void insertNodeToEndList(List* lst, ListNode* newTail); // Insert Node to end


void printStudent(Student* stu);
Student unScramble (List  lst);

void main()
{
    List lst;
    Student student;
    char ch;
    makeEmptyList(&lst);
    printf("Please enter the scrambled student:\n");
    ch = (char)getchar();
    while (ch != '\n')
    {
        insertDataToEndList(&lst, ch);
        ch = (char)getchar();
    }

    student = unScramble(lst);
    printStudent(&student);
    freeList((student.first));
}

void printList(List lst) {

    int i = 0;
    ListNode *curr;
    curr = lst.head;
    while (curr != NULL) {
        printf("%c ", *(curr->dataPtr)+i);
        curr = curr->next;
        i++;
    }

    printf("\n");

}

void makeEmptyList(List* lst){
    lst->head = lst->tail = NULL;
}

int isEmptyList(List lst){
    return (lst.head == NULL);
}

void insertDataToEndList(List* lst, char data){
    ListNode *result = createNewListNode(data, NULL);

    insertNodeToEndList(lst, result);

}

void insertNodeToEndList(List* lst, ListNode* newTail){
    newTail->next = NULL;

    if (isEmptyList(*lst))
        lst->head = lst->tail = newTail;
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void freeList(List lst){
    ListNode* curr = lst.head, *next;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void checkAllocation(void* ptr){
    if (ptr == NULL)
    {
        printf("Allocation error\n");
        exit(-1);
    }
}

ListNode* createNewListNode(char data, ListNode* next){
    ListNode *result;

    result = (ListNode*)malloc(sizeof(ListNode));
    checkAllocation(result);

    result->dataPtr =(char *)malloc(sizeof(char));
    checkAllocation(result->dataPtr);

    *result->dataPtr = data;
    result->next = next;

    return result;
}

void printStudent(Student *student)
{
    ListNode *current;
    current = student->first.head;
    printf("First name: ");
    while (current != NULL)
    {
        putchar(*current->dataPtr);
        current = current->next;
    }
    printf("\n");
    printf("Grade: %d\n", student->grade);
}

Student unScramble (List  lst){

    Student student ;
    ListNode* curr = lst.head;
    ListNode* next ;
    ListNode* before = NULL;
    student.first = lst;
    student.grade = 0; //needed to be initialize

    while(curr != NULL){
        next = curr->next;

        if( (*(curr->dataPtr) >= '0') && (*(curr->dataPtr) <= '9')){

            // multi the grade by 10 and adding the num we found
            student.grade = (student.grade*10) + (*(curr->dataPtr) - '0') ;

            free(curr->dataPtr); //this no longer needed
            free(curr);
            if (before != NULL)
                before->next = next;
        }

        else {
            if (before == NULL)
                student.first.head = curr;

            before = curr;
        }
        curr = next;
    }
    student.first.tail = before;
    return student;
}

